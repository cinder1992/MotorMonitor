.title "my68k: exception vectors"
.cpu 68010

.section .vectors, "a"

	.dc.l _SSP /*Initial SSP*/
	.dc.l _start /*Entry point*/
	.dc.l _err_bomb /* Bus error */
	.dc.l _err_bomb /* Address error */
	.dc.l _err_bomb /* Illegal instruction */
	.dc.l _err_bomb /* Divide by Zero */
	.dc.l _err_bomb /* CHK */
	.dc.l _err_bomb /* TRAPV */
	.dc.l _err_bomb /* Privilege violation */
	.dc.l _err_bomb /* Trace */
	.dc.l _err_bomb /* Line 1010 */
	.dc.l _err_bomb /* Line 1111 */
	.dc.l 0 /* Reserved */
	.dc.l 0 /* Reserved */
	.dc.l _err_bomb /* Format error */
	.dc.l _err_bomb /* Uninitialized Vector */
	.ds.l 8,0 /* Reserved */
	.dc.l _err_bomb /* Spurrious interrupt */
	.ds.l 7,0 /* Autovector 1-7 */
	/* traps */
	.ds.l 16,0
	/* reserved vectors */
	.ds.l 16,0
	/* MFP interrupts (Int 0) */
	.dc.l 0 /* GP Interrupt 0 */
	.dc.l 0 /* GP Interrupt 1 */
	.dc.l 0 /* GP Interrupt 2 */
	.dc.l 0 /* GP Interrupt 3 */
	.dc.l 0 /* Timer C */
	.dc.l 0 /* Timer D */
	.dc.l 0 /* GP Interrupt 4 */
	.dc.l 0 /* GP Interrupt 5 */
	.dc.l 0 /* Timer B */
	.dc.l 0 /* xmit error */
	.dc.l _int_mfp_tx /* XMIT buffer empty */
	.dc.l 0 /* RX error */
	.dc.l _int_mfp_rx /* RX buffer full */
	.dc.l 0 /* timer A */
	.dc.l 0 /* GP Interrupt 6 */
	.dc.l _int_mfp_cts /* GP Interrupt 7 */
.end
