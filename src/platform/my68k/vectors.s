.title "my68k: exception vectors"
.cpu 68010

.section .vectors, "a"

	.dc.l _SSP /*Initial SSP*/
	.dc.l _start /*Entry point*/
	.dc.l err_bomb /* Bus error */
	.dc.l err_bomb /* Address error */
	.dc.l err_bomb /* Illegal instruction */
	.dc.l err_bomb /* Divide by Zero */
	.dc.l err_bomb /* CHK */
	.dc.l err_bomb /* TRAPV */
	.dc.l err_bomb /* Privilege violation */
	.dc.l err_bomb /* Trace */
	.dc.l err_bomb /* Line 1010 */
	.dc.l err_bomb /* Line 1111 */
	.dc.l 0 /* Reserved */
	.dc.l 0 /* Reserved */
	.dc.l err_bomb /* Format error */
	.dc.l err_bomb /* Uninitialized Vector */
	.ds.l 8,0 /* Reserved */
	.dc.l err_bomb /* Spurrious interrupt */
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
	.dc.l int_mfp_tx /* XMIT buffer empty */
	.dc.l 0 /* RX error */
	.dc.l int_mfp_rx /* RX buffer full */
	.dc.l 0 /* timer A */
	.dc.l 0 /* GP Interrupt 6 */
	.dc.l int_mfp_cts /* GP Interrupt 7 */
.end
