;--------------------------------------------------------
; File Created by SDCC : FreeWare ANSI-C Compiler
; Version 2.6.0 #4309 (Jul 28 2006)
; This file generated Sun Dec 28 11:32:34 2008
;--------------------------------------------------------
	.module lcd_if
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _SPIF
	.globl _WCOL
	.globl _MODF
	.globl _RXOVRN
	.globl _NSSMD1
	.globl _NSSMD0
	.globl _TXBMT
	.globl _SPIEN
	.globl _AD0EN
	.globl _AD0TM
	.globl _AD0INT
	.globl _AD0BUSY
	.globl _AD0WINT
	.globl _AD0CM2
	.globl _AD0CM1
	.globl _AD0CM0
	.globl _CF
	.globl _CR
	.globl _CCF2
	.globl _CCF1
	.globl _CCF0
	.globl _CY
	.globl _AC
	.globl _F0
	.globl _RS1
	.globl _RS0
	.globl _OV
	.globl _F1
	.globl _PARITY
	.globl _TF2H
	.globl _TF2
	.globl _TF2L
	.globl _TF2LEN
	.globl _TF2CEN
	.globl _T2SPLIT
	.globl _TR2
	.globl _T2XCLK
	.globl _MASTER
	.globl _TXMODE
	.globl _STA
	.globl _STO
	.globl _ACKRQ
	.globl _ARBLOST
	.globl _ACK
	.globl _SI
	.globl _PSPI0
	.globl _PT2
	.globl _PS0
	.globl _PS
	.globl _PT1
	.globl _PX1
	.globl _PT0
	.globl _PX0
	.globl _EA
	.globl _ESPI0
	.globl _ET2
	.globl _ES0
	.globl _ES
	.globl _ET1
	.globl _EX1
	.globl _ET0
	.globl _EX0
	.globl _P2_7
	.globl _P2_6
	.globl _P2_5
	.globl _P2_4
	.globl _P2_3
	.globl _P2_2
	.globl _P2_1
	.globl _P2_0
	.globl _S0MODE
	.globl _SM0
	.globl _MCE0
	.globl _SM2
	.globl _REN0
	.globl _REN
	.globl _TB80
	.globl _TB8
	.globl _RB80
	.globl _RB8
	.globl _TI0
	.globl _TI
	.globl _RI0
	.globl _RI
	.globl _P1_7
	.globl _P1_6
	.globl _P1_5
	.globl _P1_4
	.globl _P1_3
	.globl _P1_2
	.globl _P1_1
	.globl _P1_0
	.globl _TF1
	.globl _TR1
	.globl _TF0
	.globl _TR0
	.globl _IE1
	.globl _IT1
	.globl _IE0
	.globl _IT0
	.globl _P0_7
	.globl _P0_6
	.globl _P0_5
	.globl _P0_4
	.globl _P0_3
	.globl _P0_2
	.globl _P0_1
	.globl _P0_0
	.globl _PCA0CP2
	.globl _PCA0CP1
	.globl _PCA0CP0
	.globl _PCA0
	.globl _ADC0LT
	.globl _ADC0GT
	.globl _ADC0
	.globl _IDA0
	.globl _TMR3RL
	.globl _TMR3
	.globl _TMR2RL
	.globl _RCAP2
	.globl _TMR2
	.globl _TMR1
	.globl _TMR0
	.globl _VDM0CN
	.globl _PCA0CPH0
	.globl _PCA0CPL0
	.globl _PCA0H
	.globl _PCA0L
	.globl _SPI0CN
	.globl _EIP1
	.globl _P1MDIN
	.globl _P1MODE
	.globl _P0MDIN
	.globl _P0MODE
	.globl _B
	.globl _RSTSRC
	.globl _PCA0CPH2
	.globl _PCA0CPL2
	.globl _PCA0CPH1
	.globl _PCA0CPL1
	.globl _ADC0CN
	.globl _EIE1
	.globl _INT01CF
	.globl _IT01CF
	.globl _OSCLCN
	.globl _XBR1
	.globl _XBR0
	.globl _ACC
	.globl _PCA0CPM2
	.globl _PCA0CPM1
	.globl _PCA0CPM0
	.globl _PCA0MD
	.globl _PCA0CN
	.globl _P1SKIP
	.globl _P0SKIP
	.globl _REF0CN
	.globl _PSW
	.globl _TMR2H
	.globl _TH2
	.globl _TMR2L
	.globl _TL2
	.globl _TMR2RLH
	.globl _RCAP2H
	.globl _TMR2RLL
	.globl _RCAP2L
	.globl _TMR2CN
	.globl _T2CON
	.globl _ADC0LTH
	.globl _ADC0LTL
	.globl _ADC0GTH
	.globl _ADC0GTL
	.globl _SMB0DAT
	.globl _SMB0CF
	.globl _SMB0CN
	.globl _ADC0H
	.globl _ADC0L
	.globl _ADC0CF
	.globl _AMX0P
	.globl _AMX0N
	.globl _IDA0CN
	.globl _IP
	.globl _FLKEY
	.globl _FLSCL
	.globl _OSCICL
	.globl _OSCICN
	.globl _OSCXCN
	.globl __XPAGE
	.globl _EMI0CN
	.globl _CLKSEL
	.globl _IE
	.globl _P2MDOUT
	.globl _P1MDOUT
	.globl _P0MDOUT
	.globl _SPI0DAT
	.globl _SPI0CKR
	.globl _SPI0CFG
	.globl _P2
	.globl _CPT0MX
	.globl _CPT0MD
	.globl _CPT0CN
	.globl _SBUF0
	.globl _SBUF
	.globl _SCON0
	.globl _SCON
	.globl _IDA0H
	.globl _IDA0L
	.globl _TMR3H
	.globl _TMR3L
	.globl _TMR3RLH
	.globl _TMR3RLL
	.globl _TMR3CN
	.globl _P1
	.globl _PSCTL
	.globl _CKCON
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _P0
	.globl _printCode2LCD_PARM_3
	.globl _printCode2LCD_PARM_2
	.globl _printLCD_PARM_3
	.globl _printLCD_PARM_2
	.globl _InitLCD
	.globl _ClearLCD
	.globl _printLCD
	.globl _printCode2LCD
	.globl _IRWriteLCD
	.globl _DRWriteLCD
	.globl _WaitLCD
	.globl _SetLCDIn
	.globl _SetLCDOut
	.globl _ClockEn
	.globl _SetLCDRs
	.globl _ClrLCDRs
	.globl _SetLCDRw
	.globl _ClrLCDRw
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (DATA)
G$P0$0$0 == 0x0080
_P0	=	0x0080
G$SP$0$0 == 0x0081
_SP	=	0x0081
G$DPL$0$0 == 0x0082
_DPL	=	0x0082
G$DPH$0$0 == 0x0083
_DPH	=	0x0083
G$PCON$0$0 == 0x0087
_PCON	=	0x0087
G$TCON$0$0 == 0x0088
_TCON	=	0x0088
G$TMOD$0$0 == 0x0089
_TMOD	=	0x0089
G$TL0$0$0 == 0x008a
_TL0	=	0x008a
G$TL1$0$0 == 0x008b
_TL1	=	0x008b
G$TH0$0$0 == 0x008c
_TH0	=	0x008c
G$TH1$0$0 == 0x008d
_TH1	=	0x008d
G$CKCON$0$0 == 0x008e
_CKCON	=	0x008e
G$PSCTL$0$0 == 0x008f
_PSCTL	=	0x008f
G$P1$0$0 == 0x0090
_P1	=	0x0090
G$TMR3CN$0$0 == 0x0091
_TMR3CN	=	0x0091
G$TMR3RLL$0$0 == 0x0092
_TMR3RLL	=	0x0092
G$TMR3RLH$0$0 == 0x0093
_TMR3RLH	=	0x0093
G$TMR3L$0$0 == 0x0094
_TMR3L	=	0x0094
G$TMR3H$0$0 == 0x0095
_TMR3H	=	0x0095
G$IDA0L$0$0 == 0x0096
_IDA0L	=	0x0096
G$IDA0H$0$0 == 0x0097
_IDA0H	=	0x0097
G$SCON$0$0 == 0x0098
_SCON	=	0x0098
G$SCON0$0$0 == 0x0098
_SCON0	=	0x0098
G$SBUF$0$0 == 0x0099
_SBUF	=	0x0099
G$SBUF0$0$0 == 0x0099
_SBUF0	=	0x0099
G$CPT0CN$0$0 == 0x009b
_CPT0CN	=	0x009b
G$CPT0MD$0$0 == 0x009d
_CPT0MD	=	0x009d
G$CPT0MX$0$0 == 0x009f
_CPT0MX	=	0x009f
G$P2$0$0 == 0x00a0
_P2	=	0x00a0
G$SPI0CFG$0$0 == 0x00a1
_SPI0CFG	=	0x00a1
G$SPI0CKR$0$0 == 0x00a2
_SPI0CKR	=	0x00a2
G$SPI0DAT$0$0 == 0x00a3
_SPI0DAT	=	0x00a3
G$P0MDOUT$0$0 == 0x00a4
_P0MDOUT	=	0x00a4
G$P1MDOUT$0$0 == 0x00a5
_P1MDOUT	=	0x00a5
G$P2MDOUT$0$0 == 0x00a6
_P2MDOUT	=	0x00a6
G$IE$0$0 == 0x00a8
_IE	=	0x00a8
G$CLKSEL$0$0 == 0x00a9
_CLKSEL	=	0x00a9
G$EMI0CN$0$0 == 0x00aa
_EMI0CN	=	0x00aa
G$_XPAGE$0$0 == 0x00aa
__XPAGE	=	0x00aa
G$OSCXCN$0$0 == 0x00b1
_OSCXCN	=	0x00b1
G$OSCICN$0$0 == 0x00b2
_OSCICN	=	0x00b2
G$OSCICL$0$0 == 0x00b3
_OSCICL	=	0x00b3
G$FLSCL$0$0 == 0x00b6
_FLSCL	=	0x00b6
G$FLKEY$0$0 == 0x00b7
_FLKEY	=	0x00b7
G$IP$0$0 == 0x00b8
_IP	=	0x00b8
G$IDA0CN$0$0 == 0x00b9
_IDA0CN	=	0x00b9
G$AMX0N$0$0 == 0x00ba
_AMX0N	=	0x00ba
G$AMX0P$0$0 == 0x00bb
_AMX0P	=	0x00bb
G$ADC0CF$0$0 == 0x00bc
_ADC0CF	=	0x00bc
G$ADC0L$0$0 == 0x00bd
_ADC0L	=	0x00bd
G$ADC0H$0$0 == 0x00be
_ADC0H	=	0x00be
G$SMB0CN$0$0 == 0x00c0
_SMB0CN	=	0x00c0
G$SMB0CF$0$0 == 0x00c1
_SMB0CF	=	0x00c1
G$SMB0DAT$0$0 == 0x00c2
_SMB0DAT	=	0x00c2
G$ADC0GTL$0$0 == 0x00c3
_ADC0GTL	=	0x00c3
G$ADC0GTH$0$0 == 0x00c4
_ADC0GTH	=	0x00c4
G$ADC0LTL$0$0 == 0x00c5
_ADC0LTL	=	0x00c5
G$ADC0LTH$0$0 == 0x00c6
_ADC0LTH	=	0x00c6
G$T2CON$0$0 == 0x00c8
_T2CON	=	0x00c8
G$TMR2CN$0$0 == 0x00c8
_TMR2CN	=	0x00c8
G$RCAP2L$0$0 == 0x00ca
_RCAP2L	=	0x00ca
G$TMR2RLL$0$0 == 0x00ca
_TMR2RLL	=	0x00ca
G$RCAP2H$0$0 == 0x00cb
_RCAP2H	=	0x00cb
G$TMR2RLH$0$0 == 0x00cb
_TMR2RLH	=	0x00cb
G$TL2$0$0 == 0x00cc
_TL2	=	0x00cc
G$TMR2L$0$0 == 0x00cc
_TMR2L	=	0x00cc
G$TH2$0$0 == 0x00cd
_TH2	=	0x00cd
G$TMR2H$0$0 == 0x00cd
_TMR2H	=	0x00cd
G$PSW$0$0 == 0x00d0
_PSW	=	0x00d0
G$REF0CN$0$0 == 0x00d1
_REF0CN	=	0x00d1
G$P0SKIP$0$0 == 0x00d4
_P0SKIP	=	0x00d4
G$P1SKIP$0$0 == 0x00d5
_P1SKIP	=	0x00d5
G$PCA0CN$0$0 == 0x00d8
_PCA0CN	=	0x00d8
G$PCA0MD$0$0 == 0x00d9
_PCA0MD	=	0x00d9
G$PCA0CPM0$0$0 == 0x00da
_PCA0CPM0	=	0x00da
G$PCA0CPM1$0$0 == 0x00db
_PCA0CPM1	=	0x00db
G$PCA0CPM2$0$0 == 0x00dc
_PCA0CPM2	=	0x00dc
G$ACC$0$0 == 0x00e0
_ACC	=	0x00e0
G$XBR0$0$0 == 0x00e1
_XBR0	=	0x00e1
G$XBR1$0$0 == 0x00e2
_XBR1	=	0x00e2
G$OSCLCN$0$0 == 0x00e3
_OSCLCN	=	0x00e3
G$IT01CF$0$0 == 0x00e4
_IT01CF	=	0x00e4
G$INT01CF$0$0 == 0x00e4
_INT01CF	=	0x00e4
G$EIE1$0$0 == 0x00e6
_EIE1	=	0x00e6
G$ADC0CN$0$0 == 0x00e8
_ADC0CN	=	0x00e8
G$PCA0CPL1$0$0 == 0x00e9
_PCA0CPL1	=	0x00e9
G$PCA0CPH1$0$0 == 0x00ea
_PCA0CPH1	=	0x00ea
G$PCA0CPL2$0$0 == 0x00eb
_PCA0CPL2	=	0x00eb
G$PCA0CPH2$0$0 == 0x00ec
_PCA0CPH2	=	0x00ec
G$RSTSRC$0$0 == 0x00ef
_RSTSRC	=	0x00ef
G$B$0$0 == 0x00f0
_B	=	0x00f0
G$P0MODE$0$0 == 0x00f1
_P0MODE	=	0x00f1
G$P0MDIN$0$0 == 0x00f1
_P0MDIN	=	0x00f1
G$P1MODE$0$0 == 0x00f2
_P1MODE	=	0x00f2
G$P1MDIN$0$0 == 0x00f2
_P1MDIN	=	0x00f2
G$EIP1$0$0 == 0x00f6
_EIP1	=	0x00f6
G$SPI0CN$0$0 == 0x00f8
_SPI0CN	=	0x00f8
G$PCA0L$0$0 == 0x00f9
_PCA0L	=	0x00f9
G$PCA0H$0$0 == 0x00fa
_PCA0H	=	0x00fa
G$PCA0CPL0$0$0 == 0x00fb
_PCA0CPL0	=	0x00fb
G$PCA0CPH0$0$0 == 0x00fc
_PCA0CPH0	=	0x00fc
G$VDM0CN$0$0 == 0x00ff
_VDM0CN	=	0x00ff
G$TMR0$0$0 == 0x8c8a
_TMR0	=	0x8c8a
G$TMR1$0$0 == 0x8d8b
_TMR1	=	0x8d8b
G$TMR2$0$0 == 0xcdcc
_TMR2	=	0xcdcc
G$RCAP2$0$0 == 0xcbca
_RCAP2	=	0xcbca
G$TMR2RL$0$0 == 0xcbca
_TMR2RL	=	0xcbca
G$TMR3$0$0 == 0x9594
_TMR3	=	0x9594
G$TMR3RL$0$0 == 0x9392
_TMR3RL	=	0x9392
G$IDA0$0$0 == 0x9796
_IDA0	=	0x9796
G$ADC0$0$0 == 0xbebd
_ADC0	=	0xbebd
G$ADC0GT$0$0 == 0xc4c3
_ADC0GT	=	0xc4c3
G$ADC0LT$0$0 == 0xc6c5
_ADC0LT	=	0xc6c5
G$PCA0$0$0 == 0xfaf9
_PCA0	=	0xfaf9
G$PCA0CP0$0$0 == 0xfcfb
_PCA0CP0	=	0xfcfb
G$PCA0CP1$0$0 == 0xeae9
_PCA0CP1	=	0xeae9
G$PCA0CP2$0$0 == 0xeceb
_PCA0CP2	=	0xeceb
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (DATA)
G$P0_0$0$0 == 0x0080
_P0_0	=	0x0080
G$P0_1$0$0 == 0x0081
_P0_1	=	0x0081
G$P0_2$0$0 == 0x0082
_P0_2	=	0x0082
G$P0_3$0$0 == 0x0083
_P0_3	=	0x0083
G$P0_4$0$0 == 0x0084
_P0_4	=	0x0084
G$P0_5$0$0 == 0x0085
_P0_5	=	0x0085
G$P0_6$0$0 == 0x0086
_P0_6	=	0x0086
G$P0_7$0$0 == 0x0087
_P0_7	=	0x0087
G$IT0$0$0 == 0x0088
_IT0	=	0x0088
G$IE0$0$0 == 0x0089
_IE0	=	0x0089
G$IT1$0$0 == 0x008a
_IT1	=	0x008a
G$IE1$0$0 == 0x008b
_IE1	=	0x008b
G$TR0$0$0 == 0x008c
_TR0	=	0x008c
G$TF0$0$0 == 0x008d
_TF0	=	0x008d
G$TR1$0$0 == 0x008e
_TR1	=	0x008e
G$TF1$0$0 == 0x008f
_TF1	=	0x008f
G$P1_0$0$0 == 0x0090
_P1_0	=	0x0090
G$P1_1$0$0 == 0x0091
_P1_1	=	0x0091
G$P1_2$0$0 == 0x0092
_P1_2	=	0x0092
G$P1_3$0$0 == 0x0093
_P1_3	=	0x0093
G$P1_4$0$0 == 0x0094
_P1_4	=	0x0094
G$P1_5$0$0 == 0x0095
_P1_5	=	0x0095
G$P1_6$0$0 == 0x0096
_P1_6	=	0x0096
G$P1_7$0$0 == 0x0097
_P1_7	=	0x0097
G$RI$0$0 == 0x0098
_RI	=	0x0098
G$RI0$0$0 == 0x0098
_RI0	=	0x0098
G$TI$0$0 == 0x0099
_TI	=	0x0099
G$TI0$0$0 == 0x0099
_TI0	=	0x0099
G$RB8$0$0 == 0x009a
_RB8	=	0x009a
G$RB80$0$0 == 0x009a
_RB80	=	0x009a
G$TB8$0$0 == 0x009b
_TB8	=	0x009b
G$TB80$0$0 == 0x009b
_TB80	=	0x009b
G$REN$0$0 == 0x009c
_REN	=	0x009c
G$REN0$0$0 == 0x009c
_REN0	=	0x009c
G$SM2$0$0 == 0x009d
_SM2	=	0x009d
G$MCE0$0$0 == 0x009d
_MCE0	=	0x009d
G$SM0$0$0 == 0x009f
_SM0	=	0x009f
G$S0MODE$0$0 == 0x009f
_S0MODE	=	0x009f
G$P2_0$0$0 == 0x00a0
_P2_0	=	0x00a0
G$P2_1$0$0 == 0x00a1
_P2_1	=	0x00a1
G$P2_2$0$0 == 0x00a2
_P2_2	=	0x00a2
G$P2_3$0$0 == 0x00a3
_P2_3	=	0x00a3
G$P2_4$0$0 == 0x00a4
_P2_4	=	0x00a4
G$P2_5$0$0 == 0x00a5
_P2_5	=	0x00a5
G$P2_6$0$0 == 0x00a6
_P2_6	=	0x00a6
G$P2_7$0$0 == 0x00a7
_P2_7	=	0x00a7
G$EX0$0$0 == 0x00a8
_EX0	=	0x00a8
G$ET0$0$0 == 0x00a9
_ET0	=	0x00a9
G$EX1$0$0 == 0x00aa
_EX1	=	0x00aa
G$ET1$0$0 == 0x00ab
_ET1	=	0x00ab
G$ES$0$0 == 0x00ac
_ES	=	0x00ac
G$ES0$0$0 == 0x00ac
_ES0	=	0x00ac
G$ET2$0$0 == 0x00ad
_ET2	=	0x00ad
G$ESPI0$0$0 == 0x00ae
_ESPI0	=	0x00ae
G$EA$0$0 == 0x00af
_EA	=	0x00af
G$PX0$0$0 == 0x00b8
_PX0	=	0x00b8
G$PT0$0$0 == 0x00b9
_PT0	=	0x00b9
G$PX1$0$0 == 0x00ba
_PX1	=	0x00ba
G$PT1$0$0 == 0x00bb
_PT1	=	0x00bb
G$PS$0$0 == 0x00bc
_PS	=	0x00bc
G$PS0$0$0 == 0x00bc
_PS0	=	0x00bc
G$PT2$0$0 == 0x00bd
_PT2	=	0x00bd
G$PSPI0$0$0 == 0x00be
_PSPI0	=	0x00be
G$SI$0$0 == 0x00c0
_SI	=	0x00c0
G$ACK$0$0 == 0x00c1
_ACK	=	0x00c1
G$ARBLOST$0$0 == 0x00c2
_ARBLOST	=	0x00c2
G$ACKRQ$0$0 == 0x00c3
_ACKRQ	=	0x00c3
G$STO$0$0 == 0x00c4
_STO	=	0x00c4
G$STA$0$0 == 0x00c5
_STA	=	0x00c5
G$TXMODE$0$0 == 0x00c6
_TXMODE	=	0x00c6
G$MASTER$0$0 == 0x00c7
_MASTER	=	0x00c7
G$T2XCLK$0$0 == 0x00c8
_T2XCLK	=	0x00c8
G$TR2$0$0 == 0x00ca
_TR2	=	0x00ca
G$T2SPLIT$0$0 == 0x00cb
_T2SPLIT	=	0x00cb
G$TF2CEN$0$0 == 0x00cd
_TF2CEN	=	0x00cd
G$TF2LEN$0$0 == 0x00cd
_TF2LEN	=	0x00cd
G$TF2L$0$0 == 0x00ce
_TF2L	=	0x00ce
G$TF2$0$0 == 0x00cf
_TF2	=	0x00cf
G$TF2H$0$0 == 0x00cf
_TF2H	=	0x00cf
G$PARITY$0$0 == 0x00d0
_PARITY	=	0x00d0
G$F1$0$0 == 0x00d1
_F1	=	0x00d1
G$OV$0$0 == 0x00d2
_OV	=	0x00d2
G$RS0$0$0 == 0x00d3
_RS0	=	0x00d3
G$RS1$0$0 == 0x00d4
_RS1	=	0x00d4
G$F0$0$0 == 0x00d5
_F0	=	0x00d5
G$AC$0$0 == 0x00d6
_AC	=	0x00d6
G$CY$0$0 == 0x00d7
_CY	=	0x00d7
G$CCF0$0$0 == 0x00d8
_CCF0	=	0x00d8
G$CCF1$0$0 == 0x00d9
_CCF1	=	0x00d9
G$CCF2$0$0 == 0x00da
_CCF2	=	0x00da
G$CR$0$0 == 0x00de
_CR	=	0x00de
G$CF$0$0 == 0x00df
_CF	=	0x00df
G$AD0CM0$0$0 == 0x00e8
_AD0CM0	=	0x00e8
G$AD0CM1$0$0 == 0x00e9
_AD0CM1	=	0x00e9
G$AD0CM2$0$0 == 0x00ea
_AD0CM2	=	0x00ea
G$AD0WINT$0$0 == 0x00eb
_AD0WINT	=	0x00eb
G$AD0BUSY$0$0 == 0x00ec
_AD0BUSY	=	0x00ec
G$AD0INT$0$0 == 0x00ed
_AD0INT	=	0x00ed
G$AD0TM$0$0 == 0x00ee
_AD0TM	=	0x00ee
G$AD0EN$0$0 == 0x00ef
_AD0EN	=	0x00ef
G$SPIEN$0$0 == 0x00f8
_SPIEN	=	0x00f8
G$TXBMT$0$0 == 0x00f9
_TXBMT	=	0x00f9
G$NSSMD0$0$0 == 0x00fa
_NSSMD0	=	0x00fa
G$NSSMD1$0$0 == 0x00fb
_NSSMD1	=	0x00fb
G$RXOVRN$0$0 == 0x00fc
_RXOVRN	=	0x00fc
G$MODF$0$0 == 0x00fd
_MODF	=	0x00fd
G$WCOL$0$0 == 0x00fe
_WCOL	=	0x00fe
G$SPIF$0$0 == 0x00ff
_SPIF	=	0x00ff
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
LprintLCD$chr_ptr$1$1==.
_printLCD_PARM_2:
	.ds 2
LprintLCD$offset$1$1==.
_printLCD_PARM_3:
	.ds 1
LprintCode2LCD$chr_ptr$1$1==.
_printCode2LCD_PARM_2:
	.ds 2
LprintCode2LCD$offset$1$1==.
_printCode2LCD_PARM_3:
	.ds 1
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area	OSEG    (OVR,DATA)
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
LWaitLCD$bi$1$1==.
_WaitLCD_bi_1_1:
	.ds 1
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'InitLCD'
;------------------------------------------------------------
;------------------------------------------------------------
	G$InitLCD$0$0 ==.
	C$lcd_if.c$164$0$0 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:164: void InitLCD( void ){
;	-----------------------------------------
;	 function InitLCD
;	-----------------------------------------
_InitLCD:
	ar2 = 0x02
	ar3 = 0x03
	ar4 = 0x04
	ar5 = 0x05
	ar6 = 0x06
	ar7 = 0x07
	ar0 = 0x00
	ar1 = 0x01
	C$lcd_if.c$173$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:173: WaitTicks( 15 );        // Wait more than 15ms
;	genCall
;	Peephole 182.b	used 16 bit load of dptr
	mov	dptr,#0x000F
	lcall	_WaitTicks
	C$lcd_if.c$174$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:174: LCD_PORT = LCD_INIT_1;  // Startup Sequence
;	genAssign
	mov	_P1,#0x30
	C$lcd_if.c$175$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:175: ClockEn();				// raise E, wait >100uS, lower E
;	genCall
	lcall	_ClockEn
	C$lcd_if.c$176$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:176: WaitTicks( 5 );         // Wait more than 4.1ms
;	genCall
;	Peephole 182.b	used 16 bit load of dptr
	mov	dptr,#0x0005
	lcall	_WaitTicks
	C$lcd_if.c$177$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:177: ClockEn();  
;	genCall
	lcall	_ClockEn
	C$lcd_if.c$178$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:178: WaitTicks( 1 );         // Wait more than 0.1ms
;	genCall
;	Peephole 182.b	used 16 bit load of dptr
	mov	dptr,#0x0001
	lcall	_WaitTicks
	C$lcd_if.c$179$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:179: ClockEn();    
;	genCall
	lcall	_ClockEn
	C$lcd_if.c$180$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:180: LCD_PORT = LCD_INIT_2;
;	genAssign
	mov	_P1,#0x20
	C$lcd_if.c$181$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:181: ClockEn();
;	genCall
	lcall	_ClockEn
	C$lcd_if.c$182$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:182: WaitTicks( 1 );         // Wait more than 0.1ms
;	genCall
;	Peephole 182.b	used 16 bit load of dptr
	mov	dptr,#0x0001
	lcall	_WaitTicks
	C$lcd_if.c$186$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:186: IRWriteLCD( 0x28 );   	// Function Set
;	genCall
	mov	dpl,#0x28
	lcall	_IRWriteLCD
	C$lcd_if.c$188$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:188: IRWriteLCD( 0x0C );   	// Display on/off control
;	genCall
	mov	dpl,#0x0C
	lcall	_IRWriteLCD
	C$lcd_if.c$190$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:190: IRWriteLCD( 0x06 );   	// Entry Mode Set
;	genCall
	mov	dpl,#0x06
	lcall	_IRWriteLCD
	C$lcd_if.c$192$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:192: IRWriteLCD( 0x01 );   	// Clear Display
;	genCall
	mov	dpl,#0x01
	lcall	_IRWriteLCD
	C$lcd_if.c$193$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:193: WaitTicks( 2 );         // Wait more than 1.64ms
;	genCall
;	Peephole 182.b	used 16 bit load of dptr
	mov	dptr,#0x0002
	C$lcd_if.c$195$1$1 ==.
	XG$InitLCD$0$0 ==.
;	Peephole 253.b	replaced lcall/ret with ljmp
	ljmp	_WaitTicks
;
;------------------------------------------------------------
;Allocation info for local variables in function 'ClearLCD'
;------------------------------------------------------------
;line                      Allocated to registers r2 
;i                         Allocated to registers r3 
;------------------------------------------------------------
	G$ClearLCD$0$0 ==.
	C$lcd_if.c$204$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:204: void ClearLCD( uchar line ){
;	-----------------------------------------
;	 function ClearLCD
;	-----------------------------------------
_ClearLCD:
;	genReceive
	mov	r2,dpl
	C$lcd_if.c$208$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:208: if( line == 3 ){
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x03,00112$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00125$
;	Peephole 300	removed redundant label 00126$
	C$lcd_if.c$210$2$2 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:210: IRWriteLCD( 0x01 );
;	genCall
	mov	dpl,#0x01
	lcall	_IRWriteLCD
	C$lcd_if.c$212$2$2 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:212: WaitTicks( 10 );
;	genCall
;	Peephole 182.b	used 16 bit load of dptr
	mov	dptr,#0x000A
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 251.b	replaced sjmp to ret with ret
;	Peephole 253.a	replaced lcall/ret with ljmp
	ljmp	_WaitTicks
00112$:
	C$lcd_if.c$215$2$3 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:215: if( line & 1 ){
;	genAnd
	mov	a,r2
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	acc.0,00105$
;	Peephole 300	removed redundant label 00127$
	C$lcd_if.c$217$3$4 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:217: IRWriteLCD( 0x80 );
;	genCall
	mov	dpl,#0x80
	push	ar2
	lcall	_IRWriteLCD
	pop	ar2
	C$lcd_if.c$218$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:218: while( i < LCD_SIZE ){
;	genAssign
	mov	r3,#0x00
00101$:
;	genCmpLt
;	genCmp
	cjne	r3,#0x10,00128$
00128$:
;	genIfxJump
;	Peephole 108.a	removed ljmp by inverse jump logic
	jnc	00105$
;	Peephole 300	removed redundant label 00129$
	C$lcd_if.c$219$4$5 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:219: WaitLCD();
;	genCall
	push	ar2
	push	ar3
	lcall	_WaitLCD
	pop	ar3
	pop	ar2
	clr	a
	rlc	a
	C$lcd_if.c$220$4$5 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:220: DRWriteLCD( ' ' );
;	genCall
	mov	dpl,#0x20
	push	ar2
	push	ar3
	lcall	_DRWriteLCD
	pop	ar3
	pop	ar2
	C$lcd_if.c$221$4$5 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:221: i++;
;	genPlus
;     genPlusIncr
	inc	r3
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00101$
00105$:
	C$lcd_if.c$224$2$3 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:224: if( line & 2 ){
;	genAnd
	mov	a,r2
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	acc.1,00114$
;	Peephole 300	removed redundant label 00130$
	C$lcd_if.c$226$3$6 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:226: IRWriteLCD( 0xC0 );
;	genCall
	mov	dpl,#0xC0
	lcall	_IRWriteLCD
	C$lcd_if.c$228$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:228: while( i < LCD_SIZE ){
;	genAssign
	mov	r2,#0x00
00106$:
;	genCmpLt
;	genCmp
	cjne	r2,#0x10,00131$
00131$:
;	genIfxJump
;	Peephole 108.a	removed ljmp by inverse jump logic
	jnc	00114$
;	Peephole 300	removed redundant label 00132$
	C$lcd_if.c$229$4$7 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:229: WaitLCD();
;	genCall
	push	ar2
	lcall	_WaitLCD
	pop	ar2
	clr	a
	rlc	a
	C$lcd_if.c$230$4$7 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:230: DRWriteLCD( ' ' );
;	genCall
	mov	dpl,#0x20
	push	ar2
	lcall	_DRWriteLCD
	pop	ar2
	C$lcd_if.c$231$4$7 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:231: i++;
;	genPlus
;     genPlusIncr
	inc	r2
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00106$
00114$:
	C$lcd_if.c$235$1$1 ==.
	XG$ClearLCD$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'printLCD'
;------------------------------------------------------------
;chr_ptr                   Allocated with name '_printLCD_PARM_2'
;offset                    Allocated with name '_printLCD_PARM_3'
;line                      Allocated to registers r2 
;------------------------------------------------------------
	G$printLCD$0$0 ==.
	C$lcd_if.c$246$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:246: void printLCD( uchar line, uchar LCD_STORAGE_CLASS *chr_ptr, uchar offset ){
;	-----------------------------------------
;	 function printLCD
;	-----------------------------------------
_printLCD:
;	genReceive
	mov	r2,dpl
	C$lcd_if.c$249$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:249: if( line == 1 )
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x01,00102$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00113$
;	Peephole 300	removed redundant label 00114$
	C$lcd_if.c$250$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:250: IRWriteLCD( 0x80 + offset );	// address of left-most character to print
;	genPlus
;     genPlusIncr
	mov	a,#0x80
	add	a,_printLCD_PARM_3
	mov	dpl,a
;	genCall
	lcall	_IRWriteLCD
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00103$
00102$:
	C$lcd_if.c$252$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:252: IRWriteLCD( 0xC0 + offset );
;	genPlus
;     genPlusIncr
	mov	a,#0xC0
	add	a,_printLCD_PARM_3
	mov	dpl,a
;	genCall
	lcall	_IRWriteLCD
00103$:
	C$lcd_if.c$255$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:255: chr_ptr--;
;	genMinus
;	genMinusDec
	dec	_printLCD_PARM_2
	mov	a,#0xff
	cjne	a,_printLCD_PARM_2,00115$
	dec	(_printLCD_PARM_2 + 1)
00115$:
	C$lcd_if.c$256$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:256: while( *(++chr_ptr) != '\0' ){
;	genAssign
	mov	r2,_printLCD_PARM_2
	mov	r3,(_printLCD_PARM_2 + 1)
00104$:
;	genPlus
;     genPlusIncr
	inc	r2
	cjne	r2,#0x00,00116$
	inc	r3
00116$:
;	genPointerGet
;	genFarPointerGet
	mov	dpl,r2
	mov	dph,r3
	movx	a,@dptr
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
	mov	r4,a
;	Peephole 115.b	jump optimization
	jz	00107$
;	Peephole 300	removed redundant label 00117$
	C$lcd_if.c$257$2$2 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:257: WaitLCD();
;	genCall
	push	ar2
	push	ar3
	lcall	_WaitLCD
	pop	ar3
	pop	ar2
	clr	a
	rlc	a
	C$lcd_if.c$258$2$2 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:258: DRWriteLCD( *chr_ptr );
;	genPointerGet
;	genFarPointerGet
	mov	dpl,r2
	mov	dph,r3
	movx	a,@dptr
;	genCall
	mov	r4,a
;	Peephole 244.c	loading dpl from a instead of r4
	mov	dpl,a
	push	ar2
	push	ar3
	lcall	_DRWriteLCD
	pop	ar3
	pop	ar2
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00104$
00107$:
	C$lcd_if.c$262$1$1 ==.
	XG$printLCD$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'printCode2LCD'
;------------------------------------------------------------
;chr_ptr                   Allocated with name '_printCode2LCD_PARM_2'
;offset                    Allocated with name '_printCode2LCD_PARM_3'
;line                      Allocated to registers r2 
;------------------------------------------------------------
	G$printCode2LCD$0$0 ==.
	C$lcd_if.c$269$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:269: void printCode2LCD( uchar line, uchar code *chr_ptr, uchar offset ){
;	-----------------------------------------
;	 function printCode2LCD
;	-----------------------------------------
_printCode2LCD:
;	genReceive
	mov	r2,dpl
	C$lcd_if.c$272$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:272: if( line == 1 )
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x01,00102$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00112$
;	Peephole 300	removed redundant label 00113$
	C$lcd_if.c$273$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:273: IRWriteLCD( 0x80 + offset );
;	genPlus
;     genPlusIncr
	mov	a,#0x80
	add	a,_printCode2LCD_PARM_3
	mov	dpl,a
;	genCall
	lcall	_IRWriteLCD
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00110$
00102$:
	C$lcd_if.c$275$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:275: IRWriteLCD( 0xC0 + offset );
;	genPlus
;     genPlusIncr
	mov	a,#0xC0
	add	a,_printCode2LCD_PARM_3
	mov	dpl,a
;	genCall
	lcall	_IRWriteLCD
	C$lcd_if.c$279$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:279: do{
00110$:
;	genAssign
	mov	r2,_printCode2LCD_PARM_2
	mov	r3,(_printCode2LCD_PARM_2 + 1)
00104$:
	C$lcd_if.c$280$2$2 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:280: WaitLCD();
;	genCall
	push	ar2
	push	ar3
	lcall	_WaitLCD
	pop	ar3
	pop	ar2
	clr	a
	rlc	a
	C$lcd_if.c$281$2$2 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:281: DRWriteLCD( *chr_ptr++ );
;	genPointerGet
;	genCodePointerGet
	mov	dpl,r2
	mov	dph,r3
	clr	a
	movc	a,@a+dptr
	mov	r4,a
	inc	dptr
	mov	r2,dpl
	mov	r3,dph
;	genCall
	mov	dpl,r4
	push	ar2
	push	ar3
	lcall	_DRWriteLCD
	pop	ar3
	pop	ar2
	C$lcd_if.c$282$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:282: }while( *chr_ptr != '\0' );
;	genPointerGet
;	genCodePointerGet
	mov	dpl,r2
	mov	dph,r3
	clr	a
	movc	a,@a+dptr
;	genCmpEq
;	gencjneshort
	mov	r4,a
;	Peephole 115.b	jump optimization
	jz	00115$
;	Peephole 300	removed redundant label 00114$
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00104$
00115$:
;	Peephole 300	removed redundant label 00107$
	C$lcd_if.c$284$1$1 ==.
	XG$printCode2LCD$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'IRWriteLCD'
;------------------------------------------------------------
;outbyte                   Allocated to registers r2 
;i                         Allocated to registers r3 
;------------------------------------------------------------
	G$IRWriteLCD$0$0 ==.
	C$lcd_if.c$299$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:299: void IRWriteLCD( uchar outbyte){
;	-----------------------------------------
;	 function IRWriteLCD
;	-----------------------------------------
_IRWriteLCD:
;	genReceive
	mov	r2,dpl
	C$lcd_if.c$305$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:305: SetLCDOut();                // Configs Port bits to output
;	genCall
	push	ar2
	lcall	_SetLCDOut
	pop	ar2
	C$lcd_if.c$306$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:306: i = i & 0xf0;               // Strip low nibble
;	genAnd
	mov	a,#0xF0
	anl	a,r2
	mov	r3,a
	C$lcd_if.c$310$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:310: LCD_PORT = i;               // Write high nibble
;	genAssign
	mov	_P1,r3
	C$lcd_if.c$311$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:311: ClrLCDRs();                 // Instruction
;	genCall
	push	ar2
	lcall	_ClrLCDRs
	pop	ar2
	C$lcd_if.c$312$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:312: ClrLCDRw();                 // Write
;	genCall
	push	ar2
	lcall	_ClrLCDRw
	pop	ar2
	C$lcd_if.c$313$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:313: ClockEn();                	// Trigger
;	genCall
	push	ar2
	lcall	_ClockEn
	pop	ar2
	C$lcd_if.c$317$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:317: i = (i & 0x0f);             // Strip high nibble
;	genAnd
	mov	a,#0x0F
	anl	a,r2
	C$lcd_if.c$319$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:319: i = i*16;					// Shift low nibble to high
;	genLeftShift
;	genLeftShiftLiteral
;	genlshOne
	mov	r3,a
;	Peephole 105	removed redundant mov
	swap	a
	anl	a,#0xf0
	mov	_P1,a
	C$lcd_if.c$322$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:322: ClrLCDRs();                 // Instruction
;	genCall
	lcall	_ClrLCDRs
	C$lcd_if.c$323$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:323: ClrLCDRw();                 // Write
;	genCall
	lcall	_ClrLCDRw
	C$lcd_if.c$324$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:324: ClockEn();
;	genCall
	C$lcd_if.c$326$1$1 ==.
	XG$IRWriteLCD$0$0 ==.
;	Peephole 253.b	replaced lcall/ret with ljmp
	ljmp	_ClockEn
;
;------------------------------------------------------------
;Allocation info for local variables in function 'DRWriteLCD'
;------------------------------------------------------------
;outbyte                   Allocated to registers r2 
;i                         Allocated to registers r3 
;------------------------------------------------------------
	G$DRWriteLCD$0$0 ==.
	C$lcd_if.c$333$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:333: void DRWriteLCD( uchar outbyte){
;	-----------------------------------------
;	 function DRWriteLCD
;	-----------------------------------------
_DRWriteLCD:
;	genReceive
	mov	r2,dpl
	C$lcd_if.c$339$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:339: SetLCDOut();                // Configs Port bits to output
;	genCall
	push	ar2
	lcall	_SetLCDOut
	pop	ar2
	C$lcd_if.c$340$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:340: i = i & 0xf0;               // Strip low nibble
;	genAnd
	mov	a,#0xF0
	anl	a,r2
	mov	r3,a
	C$lcd_if.c$344$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:344: LCD_PORT = i;               // Write high nibble
;	genAssign
	mov	_P1,r3
	C$lcd_if.c$345$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:345: SetLCDRs();                 // Data
;	genCall
	push	ar2
	lcall	_SetLCDRs
	pop	ar2
	C$lcd_if.c$346$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:346: ClrLCDRw();                 // Write
;	genCall
	push	ar2
	lcall	_ClrLCDRw
	pop	ar2
	C$lcd_if.c$347$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:347: ClockEn();
;	genCall
	push	ar2
	lcall	_ClockEn
	pop	ar2
	C$lcd_if.c$351$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:351: i = (i & 0x0f);             // Strip high nibble
;	genAnd
	mov	a,#0x0F
	anl	a,r2
	C$lcd_if.c$353$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:353: i = i*16;					// Shift low to high
;	genLeftShift
;	genLeftShiftLiteral
;	genlshOne
	mov	r3,a
;	Peephole 105	removed redundant mov
	swap	a
	anl	a,#0xf0
	mov	_P1,a
	C$lcd_if.c$356$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:356: SetLCDRs();                 // Data
;	genCall
	lcall	_SetLCDRs
	C$lcd_if.c$357$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:357: ClrLCDRw();                 // Write
;	genCall
	lcall	_ClrLCDRw
	C$lcd_if.c$358$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:358: ClockEn();
;	genCall
	C$lcd_if.c$360$1$1 ==.
	XG$DRWriteLCD$0$0 ==.
;	Peephole 253.b	replaced lcall/ret with ljmp
	ljmp	_ClockEn
;
;------------------------------------------------------------
;Allocation info for local variables in function 'WaitLCD'
;------------------------------------------------------------
;i                         Allocated to registers r2 
;------------------------------------------------------------
	G$WaitLCD$0$0 ==.
	C$lcd_if.c$371$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:371: bit WaitLCD( void ){
;	-----------------------------------------
;	 function WaitLCD
;	-----------------------------------------
_WaitLCD:
	C$lcd_if.c$383$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:383: SetLCDIn();		// set busy flag line as input
;	genCall
	lcall	_SetLCDIn
	C$lcd_if.c$384$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:384: ClrLCDRs();		// instruction
;	genCall
	lcall	_ClrLCDRs
	C$lcd_if.c$385$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:385: SetLCDRw();		// set display to *talk* mode
;	genCall
	lcall	_SetLCDRw
	C$lcd_if.c$388$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:388: for( i=0; i<5; i++ )	// wait 1uS
00112$:
;	genAssign
	mov	r2,#0x05
00106$:
;	genDjnz
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 205	optimized misc jump sequence
	djnz	r2,00106$
;	Peephole 300	removed redundant label 00120$
;	Peephole 300	removed redundant label 00121$
	C$lcd_if.c$390$2$2 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:390: LCD_EN = 1;
;	genAssign
	setb	_P1_2
	C$lcd_if.c$391$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:391: for( i=0; i<5; i++ )	// wait 1uS
;	genAssign
	mov	r2,#0x05
00109$:
;	genDjnz
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 205	optimized misc jump sequence
	djnz	r2,00109$
;	Peephole 300	removed redundant label 00122$
;	Peephole 300	removed redundant label 00123$
	C$lcd_if.c$393$2$2 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:393: bi = BUSY_FLAG;
;	genAssign
	mov	c,_P1_7
	mov	_WaitLCD_bi_1_1,c
	C$lcd_if.c$395$2$2 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:395: LCD_EN = 0;
;	genAssign
	clr	_P1_2
	C$lcd_if.c$396$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:396: }while( bi ); //&& !bt );     // We wait here until BF goes low
;	genIfx
;	genIfxJump
;	Peephole 108.e	removed ljmp by inverse jump logic
	jb	_WaitLCD_bi_1_1,00112$
;	Peephole 300	removed redundant label 00124$
	C$lcd_if.c$400$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:400: ClrLCDRw();		// set display back to *listen* mode (default)
;	genCall
	lcall	_ClrLCDRw
	C$lcd_if.c$402$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:402: return( bi );
;	genRet
	clr	a
	mov	c,_WaitLCD_bi_1_1
	rlc	a
	add	a,#0xff
;	Peephole 300	removed redundant label 00110$
	C$lcd_if.c$404$1$1 ==.
	XG$WaitLCD$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'SetLCDIn'
;------------------------------------------------------------
;------------------------------------------------------------
	G$SetLCDIn$0$0 ==.
	C$lcd_if.c$415$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:415: void SetLCDIn( void ){
;	-----------------------------------------
;	 function SetLCDIn
;	-----------------------------------------
_SetLCDIn:
	C$lcd_if.c$423$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:423: BUSY_FLAG = 1;			// write 1 to make pin an input
;	genAssign
	setb	_P1_7
;	Peephole 300	removed redundant label 00101$
	C$lcd_if.c$426$1$1 ==.
	XG$SetLCDIn$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'SetLCDOut'
;------------------------------------------------------------
;------------------------------------------------------------
	G$SetLCDOut$0$0 ==.
	C$lcd_if.c$436$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:436: void SetLCDOut( void ){
;	-----------------------------------------
;	 function SetLCDOut
;	-----------------------------------------
_SetLCDOut:
	C$lcd_if.c$445$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:445: } // end SetLCDOut()
;	Peephole 300	removed redundant label 00101$
	C$lcd_if.c$445$1$1 ==.
	XG$SetLCDOut$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'ClockEn'
;------------------------------------------------------------
;i                         Allocated to registers r2 
;------------------------------------------------------------
	G$ClockEn$0$0 ==.
	C$lcd_if.c$450$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:450: void ClockEn( void ){
;	-----------------------------------------
;	 function ClockEn
;	-----------------------------------------
_ClockEn:
	C$lcd_if.c$454$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:454: LCD_EN = 1;
;	genAssign
	setb	_P1_2
	C$lcd_if.c$457$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:457: for( i=0; i<5; i++ )
;	genAssign
	mov	r2,#0x05
00103$:
;	genDjnz
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 205	optimized misc jump sequence
	djnz	r2,00103$
;	Peephole 300	removed redundant label 00109$
;	Peephole 300	removed redundant label 00110$
	C$lcd_if.c$459$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:459: LCD_EN = 0;
;	genAssign
	clr	_P1_2
;	Peephole 300	removed redundant label 00104$
	C$lcd_if.c$461$1$1 ==.
	XG$ClockEn$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'SetLCDRs'
;------------------------------------------------------------
;------------------------------------------------------------
	G$SetLCDRs$0$0 ==.
	C$lcd_if.c$468$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:468: void SetLCDRs( void ){
;	-----------------------------------------
;	 function SetLCDRs
;	-----------------------------------------
_SetLCDRs:
	C$lcd_if.c$471$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:471: LCD_RS = 1;
;	genAssign
	setb	_P1_0
;	Peephole 300	removed redundant label 00101$
	C$lcd_if.c$473$1$1 ==.
	XG$SetLCDRs$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'ClrLCDRs'
;------------------------------------------------------------
;------------------------------------------------------------
	G$ClrLCDRs$0$0 ==.
	C$lcd_if.c$480$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:480: void ClrLCDRs( void ){
;	-----------------------------------------
;	 function ClrLCDRs
;	-----------------------------------------
_ClrLCDRs:
	C$lcd_if.c$483$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:483: LCD_RS = 0;
;	genAssign
	clr	_P1_0
;	Peephole 300	removed redundant label 00101$
	C$lcd_if.c$485$1$1 ==.
	XG$ClrLCDRs$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'SetLCDRw'
;------------------------------------------------------------
;------------------------------------------------------------
	G$SetLCDRw$0$0 ==.
	C$lcd_if.c$492$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:492: void SetLCDRw( void ){
;	-----------------------------------------
;	 function SetLCDRw
;	-----------------------------------------
_SetLCDRw:
	C$lcd_if.c$495$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:495: LCD_RW = 1;
;	genAssign
	setb	_P1_1
;	Peephole 300	removed redundant label 00101$
	C$lcd_if.c$497$1$1 ==.
	XG$SetLCDRw$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'ClrLCDRw'
;------------------------------------------------------------
;------------------------------------------------------------
	G$ClrLCDRw$0$0 ==.
	C$lcd_if.c$504$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:504: void ClrLCDRw( void ){
;	-----------------------------------------
;	 function ClrLCDRw
;	-----------------------------------------
_ClrLCDRw:
	C$lcd_if.c$507$1$1 ==.
;	C:/SDCC/GPSMon/dev/lcd_if.c:507: LCD_RW = 0;
;	genAssign
	clr	_P1_1
;	Peephole 300	removed redundant label 00101$
	C$lcd_if.c$509$1$1 ==.
	XG$ClrLCDRw$0$0 ==.
	ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
