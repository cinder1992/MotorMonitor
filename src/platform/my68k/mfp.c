#include <stddef.h>
#include "platform/my68k/mfp.h"

#define MAX_BUF_SIZE 16

static volatile unsigned char* mfp = MFP_BASE;

typedef struct ring_buffer_s {
	unsigned char buf[MAX_BUF_SIZE];
	volatile int ridx;
	volatile int widx;
} ring_buffer_t;

ring_buffer_t txbuf, rxbuf;

inline static void buff_push(ring_buffer_t* bptr, char chr) {
	while((bptr->widx + 1) % MAX_BUF_SIZE == bptr->ridx); //Wait for a space in the buffer
	bptr->buf[bptr->widx] = chr;
	bptr->widx = (bptr->widx + 1) % MAX_BUF_SIZE ;
}

inline static unsigned char buff_pop(ring_buffer_t* bptr) {
	unsigned char tmp;
	while(bptr->ridx == bptr->widx); //wait for a character to arrive
	tmp = bptr->buf[bptr->ridx];
	bptr->ridx = (bptr->ridx + 1) % MAX_BUF_SIZE;
	return tmp;
}

inline static int buff_push_nb(ring_buffer_t* bptr, unsigned char chr) {
	if((bptr->widx + 1) % MAX_BUF_SIZE == bptr->ridx) {
		return 0; //buffer is full
	}
	bptr->buf[bptr->widx] = chr;
	bptr->widx = (bptr->widx + 1) % MAX_BUF_SIZE;
	return 1;
}

inline static int buff_pop_nb(ring_buffer_t* bptr, volatile unsigned char* chr) {
	if(bptr->ridx == bptr->widx) {
		return 0; //buffer is empty
	}
	*chr = bptr->buf[bptr->ridx];
	bptr->ridx = (bptr->ridx + 1) % MAX_BUF_SIZE;
	return 1;
}

inline static int buff_full(ring_buffer_t* bptr) {
	return(bptr->widx + 1) % MAX_BUF_SIZE == bptr->ridx;
}

inline static int buff_empty(ring_buffer_t* bptr) {
	return bptr->widx == bptr->ridx;
}

void __attribute__((interrupt)) int_mfp_tx(void) {
	if(!buff_empty(&txbuf)) {
		buff_pop_nb(&txbuf, &mfp[MFP_UDR]);
	}
}

void __attribute__((interrupt)) int_mfp_rx(void) {
	if(((rxbuf.widx+2) & 15) == rxbuf.ridx) {
		//disable RTS
		mfp[MFP_GPDR] |= 0b01000000;
	}
	buff_push_nb(&rxbuf, mfp[MFP_UDR]);
}

void __attribute__((interrupt)) int_mfp_cts(void) {
	//disable cts interrupt before changing MFP_AER
	mfp[MFP_IERA] &= 0b01111111;
	if(mfp[MFP_AER] & 0b10000000) { //interrupt triggered by rising edge
		mfp[MFP_AER] &= 0b01111111; // FALLING edge trigger
		mfp[MFP_IMRA] |= 0b00000100; // unmask TX interrupt
	} else { //interrupt triggered by falling edge
		//mask off tx interrupt immediately to prevent overflow
		mfp[MFP_IMRA] &= 0b11111011;
		mfp[MFP_AER] |= 0b10000000; // RISING edge trigger
	}
	mfp[MFP_IERA] |= 0b10000000; //enable CTS interrupt
}

void mfp_init(void) {
	//setup GPIO for RTS/CTS

	mfp[MFP_DDR] = 0x40; //GPIO6 is output, all others input
	mfp[MFP_GPDR] = 0x40; //set GPIO6 high

	//AER is already set up to respond to falling edge
	//Setup timer D for RS232
	mfp[MFP_TDDR] = 0x03; //count to 3 (9600 baud)
	mfp[MFP_TCDCR] = 0x01; //prescale divide-by 4 on timer D, timer C disabled
	//setup interrupts
	mfp[MFP_VR] = 0x40; //vector offset
	mfp[MFP_IMRA] = 0x94; //unmask GPIO7, RCV, and XMIT interrupts
	mfp[MFP_UCR] = 0x88; //async, 8 bits, 1 stop bit, no parity
	mfp[MFP_RSR] = 0x03; //enable receiver
	mfp[MFP_TSR] = 0x01; //enable transmitter
	mfp[MFP_IERA] = 0x94;
}

void mfp_putc(char byte) {
	if(mfp[MFP_TSR] & 0x80) {
		mfp[MFP_UDR] = byte;
	} else {
		buff_push(&txbuf, byte);
	}
}

unsigned char mfp_getc(void) {
	if(buff_empty(&rxbuf)) {
		mfp[MFP_GPDR] &= 0b10111111;
	}
	return buff_pop(&rxbuf);
}
