;--------------------------------------------------------
; File Created by SDCC : FreeWare ANSI-C Compiler
; Version 2.6.0 #4309 (Jul 28 2006)
; This file generated Thu Jan 01 19:40:10 2009
;--------------------------------------------------------
	.module TSIPMon
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _TimerStart_PARM_2
	.globl _prompt
	.globl _LCDInitMsg
	.globl _VersionMsg
	.globl _DiscActivity
	.globl _GPSDecodeStatus
	.globl _DiscMode
	.globl _RxMode
	.globl _Month
	.globl _Timer_3_Overflow
	.globl _Comparator
	.globl _Programmable_Counter_Array
	.globl _ADC0_End_of_Conversion
	.globl _ADC0_Window_Comparator
	.globl _SMB0
	.globl _SPI0
	.globl _Timer_1_Overflow
	.globl _External_Interrupt_1
	.globl _External_Interrupt_0
	.globl _SioIntService
	.globl _Timer2_ISR
	.globl _main
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
	.globl _TxRxBuf
	.globl _lcdbuf
	.globl _Alarms
	.globl _err1
	.globl _func1
	.globl _func2
	.globl _switch1
	.globl _switch2
	.globl _Tx_In_Progress
	.globl _Rx_Pending
	.globl _ticks
	.globl _Timer
	.globl _Port_Init
	.globl _Timer2_Init
	.globl _WaitTicks
	.globl _TimerStart
	.globl _TimerRunning
	.globl _TimerReset
	.globl _TimerReady
	.globl _UART0_Init
	.globl _ProcessRxMsg
	.globl _PrimaryTiming
	.globl _SupplementalTiming
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
	.area REG_BANK_2	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
G$Timer$0$0==.
_Timer::
	.ds 9
FTSIPMon$TxRx_State$0$0==.
_TxRx_State:
	.ds 1
FTSIPMon$TxRx_Count$0$0==.
_TxRx_Count:
	.ds 1
G$ticks$0$0==.
_ticks::
	.ds 2
FTSIPMon$p_TxRx_Buf$0$0==.
_p_TxRx_Buf:
	.ds 2
LPrimaryTiming$yr$1$1==.
_PrimaryTiming_yr_1_1:
	.ds 2
LSupplementalTiming$mode$1$1==.
_SupplementalTiming_mode_1_1:
	.ds 1
LSupplementalTiming$RxBuf$1$1==.
_SupplementalTiming_RxBuf_1_1:
	.ds 2
LSupplementalTiming$temp$1$1==.
_SupplementalTiming_temp_1_1:
	.ds 4
LSupplementalTiming$val$1$1==.
_SupplementalTiming_val_1_1:
	.ds 1
LSupplementalTiming$fval$1$1==.
_SupplementalTiming_fval_1_1:
	.ds 2
LSupplementalTiming$sloc1$1$0==.
_SupplementalTiming_sloc1_1_0:
	.ds 4
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area	OSEG    (OVR,DATA)
	.area	OSEG    (OVR,DATA)
	.area	OSEG    (OVR,DATA)
LTimerStart$num_ticks$1$1==.
_TimerStart_PARM_2::
	.ds 2
	.area	OSEG    (OVR,DATA)
	.area	OSEG    (OVR,DATA)
	.area	OSEG    (OVR,DATA)
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG	(DATA)
__start__stack:
	.ds	1

;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
G$Rx_Pending$0$0==.
_Rx_Pending::
	.ds 1
G$Tx_In_Progress$0$0==.
_Tx_In_Progress::
	.ds 1
G$switch2$0$0==.
_switch2::
	.ds 1
G$switch1$0$0==.
_switch1::
	.ds 1
G$func2$0$0==.
_func2::
	.ds 1
G$func1$0$0==.
_func1::
	.ds 1
G$err1$0$0==.
_err1::
	.ds 1
LSioIntService$bEvenDLE$1$1==.
_SioIntService_bEvenDLE_1_1:
	.ds 1
LSupplementalTiming$b$1$1==.
_SupplementalTiming_b_1_1:
	.ds 1
LSupplementalTiming$c$1$1==.
_SupplementalTiming_c_1_1:
	.ds 1
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
G$Alarms$0$0==.
_Alarms::
	.ds 2
G$lcdbuf$0$0==.
_lcdbuf::
	.ds 17
G$TxRxBuf$0$0==.
_TxRxBuf::
	.ds 85
LProcessRxMsg$pBuf$1$1==.
_ProcessRxMsg_pBuf_1_1:
	.ds 85
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
; interrupt vector 
;--------------------------------------------------------
	.area HOME    (CODE)
__interrupt_vect:
	ljmp	__sdcc_gsinit_startup
	ljmp	_External_Interrupt_0
	.ds	5
	reti
	.ds	7
	ljmp	_External_Interrupt_1
	.ds	5
	ljmp	_Timer_1_Overflow
	.ds	5
	ljmp	_SioIntService
	.ds	5
	ljmp	_Timer2_ISR
	.ds	5
	ljmp	_SPI0
	.ds	5
	ljmp	_SMB0
	.ds	5
	reti
	.ds	7
	ljmp	_ADC0_Window_Comparator
	.ds	5
	ljmp	_ADC0_End_of_Conversion
	.ds	5
	ljmp	_Programmable_Counter_Array
	.ds	5
	ljmp	_Comparator
	.ds	5
	reti
	.ds	7
	ljmp	_Timer_3_Overflow
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
	.globl __sdcc_gsinit_startup
	.globl __sdcc_program_startup
	.globl __start__stack
	.globl __mcs51_genXINIT
	.globl __mcs51_genXRAMCLEAR
	.globl __mcs51_genRAMCLEAR
;------------------------------------------------------------
;Allocation info for local variables in function 'SupplementalTiming'
;------------------------------------------------------------
;mode                      Allocated with name '_SupplementalTiming_mode_1_1'
;RxBuf                     Allocated with name '_SupplementalTiming_RxBuf_1_1'
;temp                      Allocated with name '_SupplementalTiming_temp_1_1'
;val                       Allocated with name '_SupplementalTiming_val_1_1'
;fval                      Allocated with name '_SupplementalTiming_fval_1_1'
;sloc0                     Allocated with name '_SupplementalTiming_sloc0_1_0'
;sloc1                     Allocated with name '_SupplementalTiming_sloc1_1_0'
;------------------------------------------------------------
	G$SupplementalTiming$0$0 ==.
	C$TSIPMon.c$769$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:769: static bit b = FALSE;
;	genAssign
	clr	_SupplementalTiming_b_1_1
	C$TSIPMon.c$770$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:770: static bit c = FALSE;
;	genAssign
	clr	_SupplementalTiming_c_1_1
	C$TSIPMon.c$777$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:777: static char mode = -1;
;	genAssign
	mov	_SupplementalTiming_mode_1_1,#0xFF
	G$Timer_3_Overflow$0$0 ==.
	C$TSIPMon.c$207$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:207: uint ticks = 0;
;	genAssign
	clr	a
	mov	_ticks,a
	mov	(_ticks + 1),a
	.area GSFINAL (CODE)
	ljmp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area CSEG    (CODE)
__sdcc_program_startup:
	lcall	_main
;	return from main will lock up
	sjmp .
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;------------------------------------------------------------
	G$main$0$0 ==.
	C$TSIPMon.c$221$0$0 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:221: void main( void ){
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
	ar2 = 0x02
	ar3 = 0x03
	ar4 = 0x04
	ar5 = 0x05
	ar6 = 0x06
	ar7 = 0x07
	ar0 = 0x00
	ar1 = 0x01
	C$TSIPMon.c$223$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:223: PCA0MD &= ~0x40;					// Clear watchdog timer enable
;	genAnd
	anl	_PCA0MD,#0xBF
	C$TSIPMon.c$225$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:225: Timer2_Init();						// Initialize the Timer2
;	genCall
	lcall	_Timer2_Init
	C$TSIPMon.c$226$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:226: Port_Init();						// Init Ports
;	genCall
	lcall	_Port_Init
	C$TSIPMon.c$227$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:227: UART0_Init();
;	genCall
	lcall	_UART0_Init
	C$TSIPMon.c$228$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:228: EA = TRUE;							// Enable global interrupts
;	genAssign
	setb	_EA
	C$TSIPMon.c$229$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:229: LED = 0;							// turn ON LED
;	genAssign
	clr	_P1_3
	C$TSIPMon.c$230$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:230: LED2 = 1;							// turn ON LED2
;	genAssign
	setb	_P0_7
	C$TSIPMon.c$231$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:231: LED1 = 1;							// turn ON LED1
;	genAssign
	setb	_P0_3
	C$TSIPMon.c$232$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:232: TimerStart( SYS_TIMER, 500 );		// wait for display to wake up
;	genAssign
	mov	_TimerStart_PARM_2,#0xF4
	mov	(_TimerStart_PARM_2 + 1),#0x01
;	genCall
	mov	dpl,#0x00
	lcall	_TimerStart
	C$TSIPMon.c$233$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:233: while( !TimerReady( SYS_TIMER ))
00101$:
;	genCall
	mov	dpl,#0x00
	lcall	_TimerReady
;	genIfx
;	genIfxJump
;	Peephole 108.c	removed ljmp by inverse jump logic
;	Peephole 128	jump optimization
	jnc	00101$
;	Peephole 300	removed redundant label 00130$
	C$TSIPMon.c$235$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:235: InitLCD();							// Init LCD Controller
;	genCall
	lcall	_InitLCD
	C$TSIPMon.c$236$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:236: ClearLCD( 3 );						// Clear display
;	genCall
	mov	dpl,#0x03
	lcall	_ClearLCD
	C$TSIPMon.c$237$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:237: printCode2LCD( 1, VersionMsg, 0 );
;	genAddrOf
	mov	_printCode2LCD_PARM_2,#_VersionMsg
	mov	(_printCode2LCD_PARM_2 + 1),#(_VersionMsg >> 8)
;	genAssign
	mov	_printCode2LCD_PARM_3,#0x00
;	genCall
	mov	dpl,#0x01
	lcall	_printCode2LCD
	C$TSIPMon.c$238$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:238: printCode2LCD( 2, LCDInitMsg, 0 );
;	genAddrOf
	mov	_printCode2LCD_PARM_2,#_LCDInitMsg
	mov	(_printCode2LCD_PARM_2 + 1),#(_LCDInitMsg >> 8)
;	genAssign
	mov	_printCode2LCD_PARM_3,#0x00
;	genCall
	mov	dpl,#0x02
	lcall	_printCode2LCD
	C$TSIPMon.c$240$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:240: TimerStart( SYS_TIMER, 1500 );
;	genAssign
	mov	_TimerStart_PARM_2,#0xDC
	mov	(_TimerStart_PARM_2 + 1),#0x05
;	genCall
	mov	dpl,#0x00
	lcall	_TimerStart
	C$TSIPMon.c$241$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:241: while( !TimerReady( SYS_TIMER ))
00104$:
;	genCall
	mov	dpl,#0x00
	lcall	_TimerReady
;	genIfx
;	genIfxJump
;	Peephole 108.c	removed ljmp by inverse jump logic
;	Peephole 128	jump optimization
	jnc	00104$
;	Peephole 300	removed redundant label 00131$
	C$TSIPMon.c$243$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:243: ClearLCD( 3 );
;	genCall
	mov	dpl,#0x03
	lcall	_ClearLCD
	C$TSIPMon.c$244$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:244: LED2 = 0;							// turn OFF LED2
;	genAssign
	clr	_P0_7
	C$TSIPMon.c$245$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:245: LED1 = 0;							// turn OFF LED1
;	genAssign
	clr	_P0_3
	C$TSIPMon.c$246$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:246: func2 = FALSE;
;	genAssign
	clr	_func2
	C$TSIPMon.c$247$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:247: func1 = FALSE;
;	genAssign
	clr	_func1
	C$TSIPMon.c$248$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:248: err1 = FALSE;
;	genAssign
	clr	_err1
	C$TSIPMon.c$250$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:250: printCode2LCD( 1, "Waiting for GPS", 0 );
;	genAddrOf
	mov	_printCode2LCD_PARM_2,#__str_0
	mov	(_printCode2LCD_PARM_2 + 1),#(__str_0 >> 8)
;	genAssign
	mov	_printCode2LCD_PARM_3,#0x00
;	genCall
	mov	dpl,#0x01
	lcall	_printCode2LCD
	C$TSIPMon.c$251$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:251: TimerStart( SYS_TIMER, 2500 );
;	genAssign
	mov	_TimerStart_PARM_2,#0xC4
	mov	(_TimerStart_PARM_2 + 1),#0x09
;	genCall
	mov	dpl,#0x00
	lcall	_TimerStart
	C$TSIPMon.c$252$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:252: LED = 1;							// turn OFF LED
;	genAssign
	setb	_P1_3
	C$TSIPMon.c$253$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:253: TimerStart( SWITCH_TIMER, 50 );		// switch timer
;	genAssign
	mov	_TimerStart_PARM_2,#0x32
	clr	a
	mov	(_TimerStart_PARM_2 + 1),a
;	genCall
	mov	dpl,#0x02
	lcall	_TimerStart
	C$TSIPMon.c$255$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:255: while( 1 ){							// Loop forever
00117$:
	C$TSIPMon.c$256$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:256: if( Rx_Pending ){
;	genIfx
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	_Rx_Pending,00108$
;	Peephole 300	removed redundant label 00132$
	C$TSIPMon.c$257$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:257: TimerReset( SYS_TIMER );
;	genCall
	mov	dpl,#0x00
	lcall	_TimerReset
	C$TSIPMon.c$258$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:258: ProcessRxMsg();
;	genCall
	lcall	_ProcessRxMsg
	C$TSIPMon.c$259$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:259: TimerStart( SYS_TIMER, 1200 );
;	genAssign
	mov	_TimerStart_PARM_2,#0xB0
	mov	(_TimerStart_PARM_2 + 1),#0x04
;	genCall
	mov	dpl,#0x00
	lcall	_TimerStart
	C$TSIPMon.c$260$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:260: err1 = FALSE;
;	genAssign
	clr	_err1
00108$:
	C$TSIPMon.c$262$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:262: if( TimerReady( SYS_TIMER )){
;	genCall
	mov	dpl,#0x00
	lcall	_TimerReady
;	genIfx
;	genIfxJump
;	Peephole 108.c	removed ljmp by inverse jump logic
;	Peephole 128	jump optimization
	jnc	00113$
;	Peephole 300	removed redundant label 00133$
	C$TSIPMon.c$263$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:263: if( !err1 ){
;	genIfx
;	genIfxJump
;	Peephole 108.e	removed ljmp by inverse jump logic
	jb	_err1,00110$
;	Peephole 300	removed redundant label 00134$
	C$TSIPMon.c$264$4$5 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:264: TimerStart( SYS_TIMER, 1200 );
;	genAssign
	mov	_TimerStart_PARM_2,#0xB0
	mov	(_TimerStart_PARM_2 + 1),#0x04
;	genCall
	mov	dpl,#0x00
	lcall	_TimerStart
	C$TSIPMon.c$265$4$5 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:265: printCode2LCD( 1, "   No Message   ", 0 );
;	genAddrOf
	mov	_printCode2LCD_PARM_2,#__str_1
	mov	(_printCode2LCD_PARM_2 + 1),#(__str_1 >> 8)
;	genAssign
	mov	_printCode2LCD_PARM_3,#0x00
;	genCall
	mov	dpl,#0x01
	lcall	_printCode2LCD
	C$TSIPMon.c$267$4$5 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:267: err1 = TRUE;
;	genAssign
	setb	_err1
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00113$
00110$:
	C$TSIPMon.c$269$4$6 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:269: TimerStart( SYS_TIMER, 500 );
;	genAssign
	mov	_TimerStart_PARM_2,#0xF4
	mov	(_TimerStart_PARM_2 + 1),#0x01
;	genCall
	mov	dpl,#0x00
	lcall	_TimerStart
	C$TSIPMon.c$270$4$6 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:270: ClearLCD( 3 );
;	genCall
	mov	dpl,#0x03
	lcall	_ClearLCD
	C$TSIPMon.c$271$4$6 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:271: err1 = FALSE;
;	genAssign
	clr	_err1
00113$:
	C$TSIPMon.c$275$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:275: if( TimerReady( SWITCH_TIMER )){
;	genCall
	mov	dpl,#0x02
	lcall	_TimerReady
;	genIfx
;	genIfxJump
;	Peephole 108.c	removed ljmp by inverse jump logic
;	Peephole 128	jump optimization
	jnc	00117$
;	Peephole 300	removed redundant label 00135$
	C$TSIPMon.c$276$3$7 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:276: switch1 = 1;
;	genAssign
	setb	_switch1
	C$TSIPMon.c$277$3$7 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:277: switch2 = 1;
;	genAssign
	setb	_switch2
	C$TSIPMon.c$278$3$7 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:278: TimerReset( SWITCH_TIMER );
;	genCall
	mov	dpl,#0x02
	lcall	_TimerReset
;	Peephole 112.b	changed ljmp to sjmp
	C$TSIPMon.c$282$1$1 ==.
	XG$main$0$0 ==.
	sjmp	00117$
;	Peephole 259.a	removed redundant label 00119$ and ret
;
;------------------------------------------------------------
;Allocation info for local variables in function 'Port_Init'
;------------------------------------------------------------
;------------------------------------------------------------
	G$Port_Init$0$0 ==.
	C$TSIPMon.c$310$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:310: void Port_Init( void ){
;	-----------------------------------------
;	 function Port_Init
;	-----------------------------------------
_Port_Init:
	C$TSIPMon.c$312$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:312: P0SKIP    = 0x01;					// P0.0 -> Vref
;	genAssign
	mov	_P0SKIP,#0x01
	C$TSIPMon.c$313$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:313: P0MDOUT = 0x98;						// Tx, LED2, LED1 are push-pull
;	genAssign
	mov	_P0MDOUT,#0x98
	C$TSIPMon.c$314$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:314: XBR0 = 0x01;						// enable UART
;	genAssign
	mov	_XBR0,#0x01
	C$TSIPMon.c$315$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:315: XBR1 = 0x40;                        // Enable crossbar
;	genAssign
	mov	_XBR1,#0x40
	C$TSIPMon.c$317$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:317: P1MDOUT = 0x7F;						// make LCD_PORT push-pull (except busy flag) v021
;	genAssign
	mov	_P1MDOUT,#0x7F
	C$TSIPMon.c$320$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:320: IE        |= 0x05;		// enable /INT0 and /INT1
;	genOr
	orl	_IE,#0x05
	C$TSIPMon.c$321$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:321: IT01CF    = 0x21;		// /INT0 and /INT1 active low, P0.1 and P0.2 respectively
;	genAssign
	mov	_IT01CF,#0x21
	C$TSIPMon.c$328$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:328: IT0 = 1;	// /INT0 edge triggered
;	genAssign
	setb	_IT0
	C$TSIPMon.c$329$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:329: IT1 = 1;	// /INT1 edge triggered
;	genAssign
	setb	_IT1
;	Peephole 300	removed redundant label 00101$
	C$TSIPMon.c$333$1$1 ==.
	XG$Port_Init$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'Timer2_Init'
;------------------------------------------------------------
;i                         Allocated to registers r2 
;------------------------------------------------------------
	G$Timer2_Init$0$0 ==.
	C$TSIPMon.c$348$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:348: void Timer2_Init( void ){
;	-----------------------------------------
;	 function Timer2_Init
;	-----------------------------------------
_Timer2_Init:
	C$TSIPMon.c$352$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:352: CKCON &= ~0x60;                     // Timer2 uses SYSCLK/12
;	genAnd
	anl	_CKCON,#0x9F
	C$TSIPMon.c$353$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:353: TMR2CN &= ~0x01;					// Set bit 0 low, select SYSCLK/12
;	genAnd
	anl	_TMR2CN,#0xFE
	C$TSIPMon.c$355$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:355: TMR2RL = TIMER2_RELOAD;             // Reload value to be used in Timer2
;	genAssign
	mov	_TMR2RL,#0x02
	mov	(_TMR2RL >> 8),#0xFE
	C$TSIPMon.c$356$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:356: TMR2 = TMR2RL;                      // Init the Timer2 register
;	genAssign
	mov	_TMR2,_TMR2RL
	mov	(_TMR2 >> 8),(_TMR2RL >> 8)
	C$TSIPMon.c$358$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:358: TMR2CN = 0x04;                      // Enable Timer2 in auto-reload mode
;	genAssign
	mov	_TMR2CN,#0x04
	C$TSIPMon.c$359$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:359: ET2 = 1;                            // Timer2 interrupt enabled
;	genAssign
	setb	_ET2
	C$TSIPMon.c$361$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:361: for( i = 0; i < NUM_TIMERS; i++ ){	// Initialize software timers.
;	genAssign
	mov	r2,#0x03
00103$:
	C$TSIPMon.c$362$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:362: Timer[i].Status = 0;
;	genMinus
;	genMinusDec
	mov	a,r2
	dec	a
;	genMult
;	genMultOneByte
	mov	r3,a
;	Peephole 105	removed redundant mov
	mov	b,#0x03
	mul	ab
;	genPlus
	add	a,#_Timer
	mov	r0,a
;	genPlus
;     genPlusIncr
	mov	a,#0x02
;	Peephole 236.a	used r0 instead of ar0
	add	a,r0
;	genPointerSet
;	genNearPointerSet
;	Peephole 239	used a instead of acc
	mov	r1,a
	mov	@r1,#0x00
	C$TSIPMon.c$363$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:363: Timer[i].WaitTime = 0;
;	genPointerSet
;	genNearPointerSet
	mov	@r0,#0x00
	inc	r0
	mov	@r0,#0x00
	dec	r0
;	genAssign
	mov	ar2,r3
	C$TSIPMon.c$361$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:361: for( i = 0; i < NUM_TIMERS; i++ ){	// Initialize software timers.
;	genIfx
	mov	a,r2
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
	jnz	00103$
;	Peephole 300	removed redundant label 00108$
;	Peephole 300	removed redundant label 00104$
	C$TSIPMon.c$366$2$2 ==.
	XG$Timer2_Init$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'Timer2_ISR'
;------------------------------------------------------------
;i                         Allocated to registers r2 
;------------------------------------------------------------
	G$Timer2_ISR$0$0 ==.
	C$TSIPMon.c$380$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:380: void Timer2_ISR( void ) interrupt 5{
;	-----------------------------------------
;	 function Timer2_ISR
;	-----------------------------------------
_Timer2_ISR:
	push	acc
	push	b
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	push	ar0
	push	psw
	mov	psw,#0x00
	C$TSIPMon.c$385$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:385: TF2H = 0;                           	// Reset Interrupt
;	genAssign
	clr	_TF2H
	C$TSIPMon.c$386$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:386: if( ticks > 0 )
;	genIfx
	mov	a,_ticks
	orl	a,(_ticks + 1)
;	genIfxJump
;	Peephole 108.c	removed ljmp by inverse jump logic
	jz	00115$
;	Peephole 300	removed redundant label 00117$
	C$TSIPMon.c$387$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:387: ticks--;
;	genMinus
;	genMinusDec
	dec	_ticks
	mov	a,#0xff
	cjne	a,_ticks,00118$
	dec	(_ticks + 1)
00118$:
	C$TSIPMon.c$388$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:388: for( i = 0; i < NUM_TIMERS; i++ ){		// Cycle through all timers, to update.
00115$:
;	genAssign
	mov	r2,#0x00
00106$:
;	genCmpLt
;	genCmp
	cjne	r2,#0x03,00119$
00119$:
;	genIfxJump
;	Peephole 108.a	removed ljmp by inverse jump logic
	jnc	00110$
;	Peephole 300	removed redundant label 00120$
	C$TSIPMon.c$389$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:389: if( Timer[i].WaitTime > 0 ){		// Is it Expired?
;	genMult
;	genMultOneByte
	mov	a,r2
	mov	b,#0x03
	mul	ab
;	genPlus
	mov	r3,a
;	Peephole 177.b	removed redundant mov
	add	a,#_Timer
	mov	r0,a
;	genPointerGet
;	genNearPointerGet
	mov	ar4,@r0
	inc	r0
	mov	ar5,@r0
	dec	r0
;	genIfx
	mov	a,r4
	orl	a,r5
;	genIfxJump
;	Peephole 108.c	removed ljmp by inverse jump logic
	jz	00104$
;	Peephole 300	removed redundant label 00121$
	C$TSIPMon.c$390$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:390: Timer[i].WaitTime--;			// No: Count it down.
;	genMinus
;	genMinusDec
	dec	r4
	cjne	r4,#0xff,00122$
	dec	r5
00122$:
;	genPointerSet
;	genNearPointerSet
	mov	@r0,ar4
	inc	r0
	mov	@r0,ar5
	dec	r0
	C$TSIPMon.c$391$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:391: Timer[i].Status = TIMER_STATUS_RUNNING;
;	genPlus
;	Peephole 236.g	used r3 instead of ar3
	mov	a,r3
	add	a,#_Timer
;	genPlus
;     genPlusIncr
	add	a,#0x02
;	genPointerSet
;	genNearPointerSet
;	Peephole 239	used a instead of acc
	mov	r0,a
	mov	@r0,#0x01
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00108$
00104$:
	C$TSIPMon.c$393$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:393: Timer[i].Status = TIMER_STATUS_READY;
;	genPlus
;	Peephole 236.g	used r3 instead of ar3
	mov	a,r3
	add	a,#_Timer
;	genPlus
;     genPlusIncr
	add	a,#0x02
;	genPointerSet
;	genNearPointerSet
;	Peephole 239	used a instead of acc
	mov	r0,a
	mov	@r0,#0x00
00108$:
	C$TSIPMon.c$388$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:388: for( i = 0; i < NUM_TIMERS; i++ ){		// Cycle through all timers, to update.
;	genPlus
;     genPlusIncr
	inc	r2
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00106$
00110$:
	pop	psw
	pop	ar0
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
	pop	b
	pop	acc
	C$TSIPMon.c$397$1$1 ==.
	XG$Timer2_ISR$0$0 ==.
	reti
;	eliminated unneeded push/pop ar1
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;------------------------------------------------------------
;Allocation info for local variables in function 'WaitTicks'
;------------------------------------------------------------
;delay                     Allocated to registers r2 r3 
;------------------------------------------------------------
	G$WaitTicks$0$0 ==.
	C$TSIPMon.c$404$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:404: void WaitTicks( uint delay){
;	-----------------------------------------
;	 function WaitTicks
;	-----------------------------------------
_WaitTicks:
;	genReceive
	mov	r2,dpl
	mov	r3,dph
	C$TSIPMon.c$406$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:406: EA = FALSE;
;	genAssign
	clr	_EA
	C$TSIPMon.c$407$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:407: ticks = delay;
;	genAssign
	mov	_ticks,r2
	mov	(_ticks + 1),r3
	C$TSIPMon.c$408$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:408: EA = TRUE;
;	genAssign
	setb	_EA
	C$TSIPMon.c$409$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:409: while( ticks > 0 )
00101$:
;	genIfx
	mov	a,_ticks
	orl	a,(_ticks + 1)
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
	jnz	00101$
;	Peephole 300	removed redundant label 00107$
;	Peephole 300	removed redundant label 00104$
	C$TSIPMon.c$412$1$1 ==.
	XG$WaitTicks$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'TimerStart'
;------------------------------------------------------------
;num_ticks                 Allocated with name '_TimerStart_PARM_2'
;timer_num                 Allocated to registers r2 
;------------------------------------------------------------
	G$TimerStart$0$0 ==.
	C$TSIPMon.c$424$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:424: void TimerStart( uchar timer_num, uint num_ticks ){
;	-----------------------------------------
;	 function TimerStart
;	-----------------------------------------
_TimerStart:
;	genReceive
	mov	r2,dpl
	C$TSIPMon.c$426$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:426: INT_DISABLE;
;	genAssign
	clr	_ET0
	C$TSIPMon.c$428$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:428: Timer[timer_num].WaitTime	= num_ticks;
;	genMult
;	genMultOneByte
	mov	a,r2
	mov	b,#0x03
	mul	ab
;	genPlus
	mov	r2,a
;	Peephole 177.b	removed redundant mov
	add	a,#_Timer
;	genPointerSet
;	genNearPointerSet
;	Peephole 239	used a instead of acc
	mov	r0,a
	mov	@r0,_TimerStart_PARM_2
	inc	r0
	mov	@r0,(_TimerStart_PARM_2 + 1)
	C$TSIPMon.c$429$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:429: Timer[timer_num].Status	= TIMER_STATUS_RUNNING;
;	genPlus
;	Peephole 236.g	used r2 instead of ar2
	mov	a,r2
	add	a,#_Timer
;	genPlus
;     genPlusIncr
	add	a,#0x02
;	genPointerSet
;	genNearPointerSet
;	Peephole 239	used a instead of acc
	mov	r0,a
	mov	@r0,#0x01
	C$TSIPMon.c$431$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:431: INT_ENABLE;
;	genAssign
	setb	_ET0
;	Peephole 300	removed redundant label 00101$
	C$TSIPMon.c$433$1$1 ==.
	XG$TimerStart$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'TimerRunning'
;------------------------------------------------------------
;timer_num                 Allocated to registers r2 
;------------------------------------------------------------
	G$TimerRunning$0$0 ==.
	C$TSIPMon.c$439$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:439: bit TimerRunning( uchar timer_num ){
;	-----------------------------------------
;	 function TimerRunning
;	-----------------------------------------
_TimerRunning:
;	genReceive
	C$TSIPMon.c$441$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:441: return( (Timer[timer_num].Status == TIMER_STATUS_RUNNING)?TRUE:FALSE );
;	genMult
;	genMultOneByte
;	peephole 177.g	optimized mov sequence
	mov	a,dpl
	mov	r2,a
	mov	b,#0x03
	mul	ab
;	genPlus
	add	a,#_Timer
;	genPlus
;     genPlusIncr
	add	a,#0x02
	mov	r0,a
;	genPointerGet
;	genNearPointerGet
	mov	ar2,@r0
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x01,00103$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00106$
;	Peephole 300	removed redundant label 00107$
;	genAssign
	mov	r2,#0x01
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00104$
00103$:
;	genAssign
	mov	r2,#0x00
00104$:
;	genRet
	mov	a,r2
	add	a,#0xff
;	Peephole 300	removed redundant label 00101$
	C$TSIPMon.c$443$1$1 ==.
	XG$TimerRunning$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'TimerReset'
;------------------------------------------------------------
;timer_num                 Allocated to registers r2 
;------------------------------------------------------------
	G$TimerReset$0$0 ==.
	C$TSIPMon.c$449$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:449: void TimerReset( uchar timer_num ){
;	-----------------------------------------
;	 function TimerReset
;	-----------------------------------------
_TimerReset:
;	genReceive
	mov	r2,dpl
	C$TSIPMon.c$451$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:451: INT_DISABLE;
;	genAssign
	clr	_ET0
	C$TSIPMon.c$452$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:452: Timer[timer_num].WaitTime	= 0;
;	genMult
;	genMultOneByte
	mov	a,r2
	mov	b,#0x03
	mul	ab
;	genPlus
	mov	r2,a
;	Peephole 177.b	removed redundant mov
	add	a,#_Timer
;	genPointerSet
;	genNearPointerSet
;	Peephole 239	used a instead of acc
	mov	r0,a
	mov	@r0,#0x00
	inc	r0
	mov	@r0,#0x00
	C$TSIPMon.c$453$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:453: Timer[timer_num].Status	= TIMER_STATUS_STOPPED;
;	genPlus
;	Peephole 236.g	used r2 instead of ar2
	mov	a,r2
	add	a,#_Timer
;	genPlus
;     genPlusIncr
	add	a,#0x02
;	genPointerSet
;	genNearPointerSet
;	Peephole 239	used a instead of acc
	mov	r0,a
	mov	@r0,#0x02
	C$TSIPMon.c$454$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:454: INT_ENABLE;
;	genAssign
	setb	_ET0
;	Peephole 300	removed redundant label 00101$
	C$TSIPMon.c$456$1$1 ==.
	XG$TimerReset$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'TimerReady'
;------------------------------------------------------------
;timer_num                 Allocated to registers r2 
;------------------------------------------------------------
	G$TimerReady$0$0 ==.
	C$TSIPMon.c$461$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:461: bit TimerReady( uchar timer_num ){
;	-----------------------------------------
;	 function TimerReady
;	-----------------------------------------
_TimerReady:
;	genReceive
	C$TSIPMon.c$463$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:463: if( Timer[timer_num].Status == TIMER_STATUS_READY )
;	genMult
;	genMultOneByte
;	peephole 177.g	optimized mov sequence
	mov	a,dpl
	mov	r2,a
	mov	b,#0x03
	mul	ab
;	genPlus
	add	a,#_Timer
;	genPlus
;     genPlusIncr
	add	a,#0x02
	mov	r0,a
;	genPointerGet
;	genNearPointerGet
	mov	a,@r0
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
	jnz	00102$
;	Peephole 300	removed redundant label 00107$
	C$TSIPMon.c$464$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:464: return( TRUE );
;	genRet
	mov	a,#0x01
	add	a,#0xff
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 251.b	replaced sjmp to ret with ret
	ret
00102$:
	C$TSIPMon.c$466$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:466: return( FALSE );
;	genRet
;	Peephole 181	changed mov to clr
	clr	a
	add	a,#0xff
;	Peephole 300	removed redundant label 00104$
	C$TSIPMon.c$468$1$1 ==.
	XG$TimerReady$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'UART0_Init'
;------------------------------------------------------------
;------------------------------------------------------------
	G$UART0_Init$0$0 ==.
	C$TSIPMon.c$483$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:483: void UART0_Init( void ){
;	-----------------------------------------
;	 function UART0_Init
;	-----------------------------------------
_UART0_Init:
	C$TSIPMon.c$485$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:485: SCON0 = 0x10;                       // SCON0: 8-bit variable bit rate
;	genAssign
	mov	_SCON0,#0x10
	C$TSIPMon.c$495$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:495: TH1 =  (unsigned char) -(SYSCLK/BAUDRATE/2);
;	genAssign
	mov	_TH1,#0x61
	C$TSIPMon.c$496$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:496: CKCON &= ~0x0B;                  // T1M = 1; SCA1:0 = xx
;	genAnd
	anl	_CKCON,#0xF4
	C$TSIPMon.c$497$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:497: CKCON |=  0x08; 
;	genOr
	orl	_CKCON,#0x08
	C$TSIPMon.c$512$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:512: TL1 = TH1;                          // Init Timer1
;	genAssign
	mov	_TL1,_TH1
	C$TSIPMon.c$513$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:513: TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
;	genAnd
	anl	_TMOD,#0x0F
	C$TSIPMon.c$514$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:514: TMOD |=  0x20;
;	genOr
	orl	_TMOD,#0x20
	C$TSIPMon.c$515$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:515: TR1 = 1;                            // START Timer1
;	genAssign
	setb	_TR1
	C$TSIPMon.c$516$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:516: TI0 = 1;                            // Indicate TX0 ready
;	genAssign
	setb	_TI0
	C$TSIPMon.c$524$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:524: RI0 = FALSE;		// turn off any pending receive interrupt
;	genAssign
	clr	_RI0
	C$TSIPMon.c$525$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:525: REN0 = TRUE;		// UART0 receive enable
;	genAssign
	setb	_REN0
	C$TSIPMon.c$526$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:526: ES0 = TRUE;         // UART0 interrupt enable
;	genAssign
	setb	_ES0
;	Peephole 300	removed redundant label 00110$
	C$TSIPMon.c$528$1$1 ==.
	XG$UART0_Init$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'SioIntService'
;------------------------------------------------------------
;tchar                     Allocated to registers r2 
;------------------------------------------------------------
	G$SioIntService$0$0 ==.
	C$TSIPMon.c$534$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:534: void SioIntService( void ) interrupt INTERRUPT_UART0 using SIO_REG_BANK {
;	-----------------------------------------
;	 function SioIntService
;	-----------------------------------------
_SioIntService:
	ar2 = 0x12
	ar3 = 0x13
	ar4 = 0x14
	ar5 = 0x15
	ar6 = 0x16
	ar7 = 0x17
	ar0 = 0x10
	ar1 = 0x11
	push	acc
	push	dpl
	push	dph
	push	psw
	mov	psw,#0x10
	C$TSIPMon.c$541$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:541: if( RI0 ){
;	genIfx
;	genIfxJump
	jb	_RI0,00181$
	ljmp	00154$
00181$:
	C$TSIPMon.c$542$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:542: tchar = SBUF0;	// & PARITY_MASK;
;	genAssign
	mov	r2,_SBUF0
	C$TSIPMon.c$543$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:543: RI0 = FALSE;
;	genAssign
	clr	_RI0
	C$TSIPMon.c$546$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:546: if( TxRx_Count > TXRX_BUF_LEN - 1 ) {
;	genCmpGt
;	genCmp
;	genIfxJump
;	Peephole 108.a	removed ljmp by inverse jump logic
;	Peephole 132.b	optimized genCmpGt by inverse logic (acc differs)
	mov	a,_TxRx_Count
	add	a,#0xff - 0x54
	jnc	00102$
;	Peephole 300	removed redundant label 00182$
	C$TSIPMon.c$547$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:547: TxRx_State = WAIT_FOR_START;
;	genAssign
	mov	_TxRx_State,#0x00
	C$TSIPMon.c$548$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:548: TxRx_Count = 0;
;	genAssign
	mov	_TxRx_Count,#0x00
	C$TSIPMon.c$549$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:549: return;
;	genRet
	ljmp	00156$
00102$:
	C$TSIPMon.c$552$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:552: switch( TxRx_State ){
;	genCmpGt
;	genCmp
;	genIfxJump
;	Peephole 132.b	optimized genCmpGt by inverse logic (acc differs)
	mov	a,_TxRx_State
	add	a,#0xff - 0x05
	jnc	00183$
	ljmp	00137$
00183$:
;	genJumpTab
	mov	a,_TxRx_State
;	Peephole 254	optimized left shift
	add	a,_TxRx_State
	add	a,_TxRx_State
	mov	dptr,#00184$
	jmp	@a+dptr
00184$:
	ljmp	00103$
	ljmp	00109$
	ljmp	00113$
	ljmp	00117$
	ljmp	00121$
	ljmp	00126$
	C$TSIPMon.c$553$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:553: case WAIT_FOR_START:
00103$:
	C$TSIPMon.c$556$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:556: if( tchar == DLE ){
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x10,00107$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00185$
;	Peephole 300	removed redundant label 00186$
	C$TSIPMon.c$558$4$5 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:558: TxRxBuf[TxRx_Count++] = tchar;
;	genAssign
	mov	_TxRx_Count,#0x01
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#_TxRxBuf
	mov	a,r2
	movx	@dptr,a
	C$TSIPMon.c$559$4$5 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:559: TxRx_State = WAIT_FOR_ID;
;	genAssign
	mov	_TxRx_State,#0x04
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00108$
00107$:
	C$TSIPMon.c$560$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:560: }else if( tchar != ETX ){
;	genCmpEq
;	gencjneshort
	cjne	r2,#0x03,00187$
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00108$
00187$:
	C$TSIPMon.c$561$4$6 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:561: TxRx_State = WAIT_FOR_DLE_ETX;
;	genAssign
	mov	_TxRx_State,#0x01
	C$TSIPMon.c$562$4$6 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:562: Rx_Pending = FALSE;
;	genAssign
	clr	_Rx_Pending
	C$TSIPMon.c$563$4$6 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:563: TxRx_Count = 0;
;	genAssign
	mov	_TxRx_Count,#0x00
00108$:
	C$TSIPMon.c$565$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:565: bEvenDLE = FALSE;
;	genAssign
	clr	_SioIntService_bEvenDLE_1_1
	C$TSIPMon.c$566$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:566: break;
	ljmp	00155$
	C$TSIPMon.c$568$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:568: case WAIT_FOR_DLE_ETX:
00109$:
	C$TSIPMon.c$569$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:569: if( tchar == DLE )
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x10,00111$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00188$
;	Peephole 300	removed redundant label 00189$
	C$TSIPMon.c$570$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:570: TxRx_State = WAIT_FOR_ETX;
;	genAssign
	mov	_TxRx_State,#0x02
	ljmp	00155$
00111$:
	C$TSIPMon.c$572$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:572: TxRx_State = WAIT_FOR_START;
;	genAssign
	mov	_TxRx_State,#0x00
	C$TSIPMon.c$573$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:573: break;
	ljmp	00155$
	C$TSIPMon.c$575$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:575: case WAIT_FOR_ETX:  // rarely happens
00113$:
	C$TSIPMon.c$576$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:576: if( tchar == ETX )	
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x03,00115$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00190$
;	Peephole 300	removed redundant label 00191$
	C$TSIPMon.c$578$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:578: TxRx_State = WAIT_FOR_DLE;
;	genAssign
	mov	_TxRx_State,#0x03
	ljmp	00155$
00115$:
	C$TSIPMon.c$580$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:580: TxRx_State = WAIT_FOR_START;
;	genAssign
	mov	_TxRx_State,#0x00
	C$TSIPMon.c$581$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:581: break;
	ljmp	00155$
	C$TSIPMon.c$583$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:583: case WAIT_FOR_DLE:
00117$:
	C$TSIPMon.c$584$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:584: if( tchar == DLE ){
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x10,00119$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00192$
;	Peephole 300	removed redundant label 00193$
	C$TSIPMon.c$586$4$7 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:586: TxRxBuf[TxRx_Count++] = tchar;
;	genAssign
	mov	_TxRx_Count,#0x01
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#_TxRxBuf
	mov	a,r2
	movx	@dptr,a
	C$TSIPMon.c$587$4$7 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:587: TxRx_State = WAIT_FOR_ID;
;	genAssign
	mov	_TxRx_State,#0x04
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00120$
00119$:
	C$TSIPMon.c$589$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:589: TxRx_State = WAIT_FOR_START;
;	genAssign
	mov	_TxRx_State,#0x00
00120$:
	C$TSIPMon.c$590$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:590: bEvenDLE = FALSE;
;	genAssign
	clr	_SioIntService_bEvenDLE_1_1
	C$TSIPMon.c$591$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:591: break;
	ljmp	00155$
	C$TSIPMon.c$593$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:593: case WAIT_FOR_ID: // never happens
00121$:
	C$TSIPMon.c$594$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:594: if( tchar == DLE || tchar == ETX ){
;	genCmpEq
;	gencjneshort
	cjne	r2,#0x10,00194$
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00122$
00194$:
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x03,00123$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00195$
;	Peephole 300	removed redundant label 00196$
00122$:
	C$TSIPMon.c$595$4$8 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:595: TxRx_State = WAIT_FOR_START;
;	genAssign
	mov	_TxRx_State,#0x00
	C$TSIPMon.c$596$4$8 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:596: TxRx_Count = 0;
;	genAssign
	mov	_TxRx_Count,#0x00
	ljmp	00155$
00123$:
	C$TSIPMon.c$598$4$9 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:598: TxRx_State = WAIT_FOR_END_MSG;
;	genAssign
	mov	_TxRx_State,#0x05
	C$TSIPMon.c$599$4$9 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:599: TxRxBuf[TxRx_Count++] = tchar;
;	genAssign
	mov	r3,_TxRx_Count
;	genPlus
;     genPlusIncr
	inc	_TxRx_Count
;	genPlus
;	Peephole 236.g	used r3 instead of ar3
	mov	a,r3
	add	a,#_TxRxBuf
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,#(_TxRxBuf >> 8)
	mov	dph,a
;	genPointerSet
;     genFarPointerSet
	mov	a,r2
	movx	@dptr,a
	C$TSIPMon.c$601$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:601: break;
	ljmp	00155$
	C$TSIPMon.c$603$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:603: case WAIT_FOR_END_MSG:
00126$:
	C$TSIPMon.c$604$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:604: if( tchar == DLE && TxRxBuf[TxRx_Count-1] == DLE && !bEvenDLE ){
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x10,00133$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00197$
;	Peephole 300	removed redundant label 00198$
;	genMinus
;	genMinusDec
	mov	a,_TxRx_Count
	dec	a
;	genPlus
	add	a,#_TxRxBuf
	mov	dpl,a
;	Peephole 240	use clr instead of addc a,#0
	clr	a
	addc	a,#(_TxRxBuf >> 8)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r3,a
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r3,#0x10,00133$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00199$
;	Peephole 300	removed redundant label 00200$
;	genIfx
;	genIfxJump
;	Peephole 108.e	removed ljmp by inverse jump logic
	jb	_SioIntService_bEvenDLE_1_1,00133$
;	Peephole 300	removed redundant label 00201$
	C$TSIPMon.c$606$4$10 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:606: bEvenDLE = TRUE;
;	genAssign
	setb	_SioIntService_bEvenDLE_1_1
	ljmp	00155$
00133$:
	C$TSIPMon.c$607$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:607: }else if( tchar == ETX && TxRxBuf[TxRx_Count-1] == DLE && !bEvenDLE ){
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x03,00128$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00202$
;	Peephole 300	removed redundant label 00203$
;	genMinus
;	genMinusDec
	mov	a,_TxRx_Count
	dec	a
;	genPlus
	add	a,#_TxRxBuf
	mov	dpl,a
;	Peephole 240	use clr instead of addc a,#0
	clr	a
	addc	a,#(_TxRxBuf >> 8)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r3,a
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r3,#0x10,00128$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00204$
;	Peephole 300	removed redundant label 00205$
;	genIfx
;	genIfxJump
;	Peephole 108.e	removed ljmp by inverse jump logic
	jb	_SioIntService_bEvenDLE_1_1,00128$
;	Peephole 300	removed redundant label 00206$
	C$TSIPMon.c$610$4$11 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:610: Rx_Pending = TRUE;
;	genAssign
	setb	_Rx_Pending
	C$TSIPMon.c$611$4$11 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:611: TxRxBuf[TxRx_Count] = '\0';
;	genPlus
	mov	a,_TxRx_Count
	add	a,#_TxRxBuf
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,#(_TxRxBuf >> 8)
	mov	dph,a
;	genPointerSet
;     genFarPointerSet
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
	C$TSIPMon.c$612$4$11 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:612: TxRx_State = WAIT_FOR_DLE;
;	genAssign
	mov	_TxRx_State,#0x03
	ljmp	00155$
00128$:
	C$TSIPMon.c$616$4$12 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:616: TxRxBuf[TxRx_Count++] = tchar;
;	genAssign
	mov	r3,_TxRx_Count
;	genPlus
;     genPlusIncr
	inc	_TxRx_Count
;	genPlus
;	Peephole 236.g	used r3 instead of ar3
	mov	a,r3
	add	a,#_TxRxBuf
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,#(_TxRxBuf >> 8)
	mov	dph,a
;	genPointerSet
;     genFarPointerSet
	mov	a,r2
	movx	@dptr,a
	C$TSIPMon.c$617$4$12 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:617: bEvenDLE = FALSE;
;	genAssign
	clr	_SioIntService_bEvenDLE_1_1
	C$TSIPMon.c$619$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:619: break;
	C$TSIPMon.c$621$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:621: default:
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00155$
00137$:
	C$TSIPMon.c$622$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:622: TxRx_State = WAIT_FOR_START;
;	genAssign
	mov	_TxRx_State,#0x00
	C$TSIPMon.c$624$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:624: }
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00155$
00154$:
	C$TSIPMon.c$628$2$13 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:628: if( TI0 ){
;	genIfx
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	C$TSIPMon.c$629$3$14 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:629: TI0 = FALSE;
;	genAssign
;	Peephole 250.a	using atomic test and clear
	jbc	_TI0,00207$
	sjmp	00155$
00207$:
	C$TSIPMon.c$631$3$14 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:631: if( !Tx_In_Progress ){
;	genIfx
;	genIfxJump
;	Peephole 108.e	removed ljmp by inverse jump logic
	jb	_Tx_In_Progress,00140$
;	Peephole 300	removed redundant label 00208$
	C$TSIPMon.c$632$4$15 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:632: RI0 = FALSE;
;	genAssign
	clr	_RI0
	C$TSIPMon.c$633$4$15 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:633: Tx_In_Progress = FALSE;
;	genAssign
	clr	_Tx_In_Progress
	C$TSIPMon.c$634$4$15 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:634: Rx_Pending = FALSE;
;	genAssign
	clr	_Rx_Pending
	C$TSIPMon.c$635$4$15 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:635: return;
;	genRet
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00156$
00140$:
	C$TSIPMon.c$637$3$14 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:637: switch( TxRx_State ){
;	genCmpEq
;	gencjneshort
	mov	a,_TxRx_State
	cjne	a,#0x06,00209$
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00141$
00209$:
;	genCmpEq
;	gencjneshort
	mov	a,_TxRx_State
;	Peephole 112.b	changed ljmp to sjmp
	C$TSIPMon.c$639$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:639: case SEND_HDR:
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	a,#0x07,00155$
	sjmp	00142$
;	Peephole 300	removed redundant label 00210$
00141$:
	C$TSIPMon.c$640$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:640: SBUF0 = DLE;
;	genAssign
	mov	_SBUF0,#0x10
	C$TSIPMon.c$641$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:641: TxRx_State = SEND_MSG;
;	genAssign
	mov	_TxRx_State,#0x07
	C$TSIPMon.c$642$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:642: TxRx_Count--;
;	genMinus
;	genMinusDec
	dec	_TxRx_Count
	C$TSIPMon.c$643$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:643: p_TxRx_Buf = TxRxBuf+1;
;	genPlus
;     genPlusIncr
	mov	a,#0x01
	add	a,#_TxRxBuf
	mov	_p_TxRx_Buf,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,#(_TxRxBuf >> 8)
	mov	(_p_TxRx_Buf + 1),a
	C$TSIPMon.c$644$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:644: bEvenDLE = FALSE;
;	genAssign
	clr	_SioIntService_bEvenDLE_1_1
	C$TSIPMon.c$645$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:645: break;
	C$TSIPMon.c$647$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:647: case SEND_MSG:
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00155$
00142$:
	C$TSIPMon.c$648$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:648: tchar = *p_TxRx_Buf;
;	genAssign
	mov	dpl,_p_TxRx_Buf
	mov	dph,(_p_TxRx_Buf + 1)
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r2,a
	C$TSIPMon.c$649$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:649: SBUF0 = tchar;
;	genAssign
	mov	_SBUF0,r2
	C$TSIPMon.c$650$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:650: if( tchar == DLE && !bEvenDLE && TxRx_Count > 1 ){
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x10,00144$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00211$
;	Peephole 300	removed redundant label 00212$
;	genIfx
;	genIfxJump
;	Peephole 108.e	removed ljmp by inverse jump logic
	jb	_SioIntService_bEvenDLE_1_1,00144$
;	Peephole 300	removed redundant label 00213$
;	genCmpGt
;	genCmp
;	genIfxJump
;	Peephole 108.a	removed ljmp by inverse jump logic
;	Peephole 132.b	optimized genCmpGt by inverse logic (acc differs)
	mov	a,_TxRx_Count
	add	a,#0xff - 0x01
	jnc	00144$
;	Peephole 300	removed redundant label 00214$
	C$TSIPMon.c$652$5$17 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:652: bEvenDLE = TRUE;
;	genAssign
	setb	_SioIntService_bEvenDLE_1_1
	C$TSIPMon.c$653$5$17 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:653: return;
;	genRet
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00156$
00144$:
	C$TSIPMon.c$655$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:655: p_TxRx_Buf++;
;	genPlus
;     genPlusIncr
	inc	_p_TxRx_Buf
	clr	a
	cjne	a,_p_TxRx_Buf,00215$
	inc	(_p_TxRx_Buf + 1)
00215$:
	C$TSIPMon.c$656$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:656: bEvenDLE = FALSE;
;	genAssign
	clr	_SioIntService_bEvenDLE_1_1
	C$TSIPMon.c$657$4$16 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:657: if( TxRx_Count-- == 0 ){
;	genAssign
	mov	r2,_TxRx_Count
;	genMinus
;	genMinusDec
	dec	_TxRx_Count
;	genIfx
	mov	a,r2
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
	jnz	00155$
;	Peephole 300	removed redundant label 00216$
	C$TSIPMon.c$658$5$18 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:658: Tx_In_Progress = FALSE;
;	genAssign
	clr	_Tx_In_Progress
	C$TSIPMon.c$659$5$18 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:659: TxRx_Count = 0;
;	genAssign
	mov	_TxRx_Count,#0x00
	C$TSIPMon.c$665$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:665: }
00155$:
	C$TSIPMon.c$669$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:669: return;
;	genRet
00156$:
	pop	psw
	pop	dph
	pop	dpl
	pop	acc
	C$TSIPMon.c$672$1$1 ==.
	XG$SioIntService$0$0 ==.
	reti
;	eliminated unneeded push/pop b
;------------------------------------------------------------
;Allocation info for local variables in function 'ProcessRxMsg'
;------------------------------------------------------------
;i                         Allocated to registers r4 
;id                        Allocated to registers r2 
;id2                       Allocated to registers r3 
;pBuf                      Allocated with name '_ProcessRxMsg_pBuf_1_1'
;------------------------------------------------------------
	G$ProcessRxMsg$0$0 ==.
	C$TSIPMon.c$677$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:677: void ProcessRxMsg( void ){
;	-----------------------------------------
;	 function ProcessRxMsg
;	-----------------------------------------
_ProcessRxMsg:
	ar2 = 0x02
	ar3 = 0x03
	ar4 = 0x04
	ar5 = 0x05
	ar6 = 0x06
	ar7 = 0x07
	ar0 = 0x00
	ar1 = 0x01
	C$TSIPMon.c$683$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:683: id = TxRxBuf[IO_BUF_ID_INDEX];
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_TxRxBuf + 0x0001)
	movx	a,@dptr
	mov	r2,a
	C$TSIPMon.c$684$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:684: id2 = TxRxBuf[IO_BUF_ID2_INDEX];
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_TxRxBuf + 0x0002)
	movx	a,@dptr
	mov	r3,a
	C$TSIPMon.c$685$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:685: for( i=2; i<TxRx_Count; i++)
;	genAssign
	mov	r4,#0x02
00108$:
;	genCmpLt
;	genCmp
	clr	c
	mov	a,r4
	subb	a,_TxRx_Count
;	genIfxJump
;	Peephole 108.a	removed ljmp by inverse jump logic
	jnc	00111$
;	Peephole 300	removed redundant label 00120$
	C$TSIPMon.c$686$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:686: pBuf[i-2] = TxRxBuf[i];
;	genMinus
;	genMinusDec
	mov	a,r4
	add	a,#0xfe
;	genPlus
	add	a,#_ProcessRxMsg_pBuf_1_1
	mov	r5,a
;	Peephole 240	use clr instead of addc a,#0
	clr	a
	addc	a,#(_ProcessRxMsg_pBuf_1_1 >> 8)
	mov	r6,a
;	genPlus
;	Peephole 236.g	used r4 instead of ar4
	mov	a,r4
	add	a,#_TxRxBuf
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,#(_TxRxBuf >> 8)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
;	genPointerSet
;     genFarPointerSet
	mov	r7,a
	mov	dpl,r5
	mov	dph,r6
;	Peephole 136	removed redundant move
	movx	@dptr,a
	C$TSIPMon.c$685$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:685: for( i=2; i<TxRx_Count; i++)
;	genPlus
;     genPlusIncr
	inc	r4
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00108$
00111$:
	C$TSIPMon.c$687$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:687: Rx_Pending = FALSE;
;	genAssign
	clr	_Rx_Pending
	C$TSIPMon.c$689$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:689: switch( id ){
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x8F,00112$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00121$
;	Peephole 300	removed redundant label 00122$
	C$TSIPMon.c$691$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:691: switch( id2 ){
;	genCmpEq
;	gencjneshort
	cjne	r3,#0xAB,00123$
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00102$
00123$:
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
	C$TSIPMon.c$692$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:692: case PRIMARY_TIMING_PCKT:
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r3,#0xAC,00112$
	sjmp	00103$
;	Peephole 300	removed redundant label 00124$
00102$:
	C$TSIPMon.c$693$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:693: PrimaryTiming( pBuf );
;	genCall
;	Peephole 182.a	used 16 bit load of DPTR
	mov	dptr,#_ProcessRxMsg_pBuf_1_1
	C$TSIPMon.c$694$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:694: break;
	C$TSIPMon.c$696$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:696: case SUPPLEMENTAL_TIMING_PCKT:
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 251.b	replaced sjmp to ret with ret
;	Peephole 253.a	replaced lcall/ret with ljmp
	ljmp	_PrimaryTiming
00103$:
	C$TSIPMon.c$697$3$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:697: SupplementalTiming( pBuf );
;	genCall
;	Peephole 182.a	used 16 bit load of DPTR
	mov	dptr,#_ProcessRxMsg_pBuf_1_1
	C$TSIPMon.c$705$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:705: }
	C$TSIPMon.c$707$1$1 ==.
	XG$ProcessRxMsg$0$0 ==.
;	Peephole 253.c	replaced lcall with ljmp
	ljmp	_SupplementalTiming
00112$:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'PrimaryTiming'
;------------------------------------------------------------
;RxBuf                     Allocated to registers r2 r3 
;sec                       Allocated to registers r4 
;min                       Allocated to registers r4 
;hr                        Allocated to registers r4 
;dom                       Allocated to registers r4 
;mo                        Allocated to registers r4 
;yr                        Allocated with name '_PrimaryTiming_yr_1_1'
;------------------------------------------------------------
	G$PrimaryTiming$0$0 ==.
	C$TSIPMon.c$713$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:713: void PrimaryTiming( uchar TXRX_STORAGE_CLASS *RxBuf ){
;	-----------------------------------------
;	 function PrimaryTiming
;	-----------------------------------------
_PrimaryTiming:
;	genReceive
	mov	r2,dpl
	mov	r3,dph
	C$TSIPMon.c$720$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:720: sec = *(RxBuf+10);
;	genPlus
;     genPlusIncr
	mov	a,#0x0A
;	Peephole 236.a	used r2 instead of ar2
	add	a,r2
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
;	Peephole 236.b	used r3 instead of ar3
	addc	a,r3
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r4,a
	C$TSIPMon.c$721$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:721: UnsignedToAscii( (uint)sec, lcdbuf+6, 2 );
;	genCast
	mov	r5,#0x00
;	genPlus
;     genPlusIncr
	mov	a,#0x06
	add	a,#_lcdbuf
	mov	_UnsignedToAscii_PARM_2,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,#(_lcdbuf >> 8)
	mov	(_UnsignedToAscii_PARM_2 + 1),a
;	genAssign
	mov	_UnsignedToAscii_PARM_3,#0x02
;	genCall
	mov	dpl,r4
	mov	dph,r5
	push	ar2
	push	ar3
	lcall	_UnsignedToAscii
	pop	ar3
	pop	ar2
	C$TSIPMon.c$722$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:722: if( lcdbuf[6] == ' ' ) lcdbuf[6] = '0';
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_lcdbuf + 0x0006)
	movx	a,@dptr
	mov	r4,a
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r4,#0x20,00102$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00118$
;	Peephole 300	removed redundant label 00119$
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#(_lcdbuf + 0x0006)
	mov	a,#0x30
	movx	@dptr,a
00102$:
	C$TSIPMon.c$723$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:723: lcdbuf[8] = ' ';
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#(_lcdbuf + 0x0008)
	mov	a,#0x20
	movx	@dptr,a
	C$TSIPMon.c$724$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:724: min = *(RxBuf+11);
;	genPlus
;     genPlusIncr
	mov	a,#0x0B
;	Peephole 236.a	used r2 instead of ar2
	add	a,r2
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
;	Peephole 236.b	used r3 instead of ar3
	addc	a,r3
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r4,a
	C$TSIPMon.c$725$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:725: UnsignedToAscii( (uint)min, lcdbuf+3, 2 );
;	genCast
	mov	r5,#0x00
;	genPlus
;     genPlusIncr
	mov	a,#0x03
	add	a,#_lcdbuf
	mov	_UnsignedToAscii_PARM_2,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,#(_lcdbuf >> 8)
	mov	(_UnsignedToAscii_PARM_2 + 1),a
;	genAssign
	mov	_UnsignedToAscii_PARM_3,#0x02
;	genCall
	mov	dpl,r4
	mov	dph,r5
	push	ar2
	push	ar3
	lcall	_UnsignedToAscii
	pop	ar3
	pop	ar2
	C$TSIPMon.c$726$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:726: if( lcdbuf[3] == ' ' ) lcdbuf[3] = '0';
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_lcdbuf + 0x0003)
	movx	a,@dptr
	mov	r4,a
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r4,#0x20,00104$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00120$
;	Peephole 300	removed redundant label 00121$
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#(_lcdbuf + 0x0003)
	mov	a,#0x30
	movx	@dptr,a
00104$:
	C$TSIPMon.c$727$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:727: lcdbuf[5] = ':';
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#(_lcdbuf + 0x0005)
	mov	a,#0x3A
	movx	@dptr,a
	C$TSIPMon.c$728$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:728: hr = *(RxBuf+12);
;	genPlus
;     genPlusIncr
	mov	a,#0x0C
;	Peephole 236.a	used r2 instead of ar2
	add	a,r2
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
;	Peephole 236.b	used r3 instead of ar3
	addc	a,r3
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r4,a
	C$TSIPMon.c$729$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:729: UnsignedToAscii( (uint)hr, lcdbuf, 2 );
;	genCast
	mov	r5,#0x00
;	genAssign
	mov	_UnsignedToAscii_PARM_2,#_lcdbuf
	mov	(_UnsignedToAscii_PARM_2 + 1),#(_lcdbuf >> 8)
;	genAssign
	mov	_UnsignedToAscii_PARM_3,#0x02
;	genCall
	mov	dpl,r4
	mov	dph,r5
	push	ar2
	push	ar3
	lcall	_UnsignedToAscii
	pop	ar3
	pop	ar2
	C$TSIPMon.c$730$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:730: if( lcdbuf[0] == ' ' ) lcdbuf[0] = '0';
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#_lcdbuf
	movx	a,@dptr
	mov	r4,a
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r4,#0x20,00106$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00122$
;	Peephole 300	removed redundant label 00123$
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#_lcdbuf
	mov	a,#0x30
	movx	@dptr,a
00106$:
	C$TSIPMon.c$731$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:731: lcdbuf[2] = ':';
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#(_lcdbuf + 0x0002)
	mov	a,#0x3A
	movx	@dptr,a
	C$TSIPMon.c$732$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:732: dom = *(RxBuf+13);
;	genPlus
;     genPlusIncr
	mov	a,#0x0D
;	Peephole 236.a	used r2 instead of ar2
	add	a,r2
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
;	Peephole 236.b	used r3 instead of ar3
	addc	a,r3
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r4,a
	C$TSIPMon.c$733$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:733: UnsignedToAscii( (uint)dom, lcdbuf+9, 2 );
;	genCast
	mov	r5,#0x00
;	genPlus
;     genPlusIncr
	mov	a,#0x09
	add	a,#_lcdbuf
	mov	_UnsignedToAscii_PARM_2,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,#(_lcdbuf >> 8)
	mov	(_UnsignedToAscii_PARM_2 + 1),a
;	genAssign
	mov	_UnsignedToAscii_PARM_3,#0x02
;	genCall
	mov	dpl,r4
	mov	dph,r5
	push	ar2
	push	ar3
	lcall	_UnsignedToAscii
	pop	ar3
	pop	ar2
	C$TSIPMon.c$736$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:736: if( lcdbuf[9] == ' ' ) lcdbuf[9] = '0';
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_lcdbuf + 0x0009)
	movx	a,@dptr
	mov	r4,a
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r4,#0x20,00108$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00124$
;	Peephole 300	removed redundant label 00125$
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#(_lcdbuf + 0x0009)
	mov	a,#0x30
	movx	@dptr,a
00108$:
	C$TSIPMon.c$738$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:738: mo = (*(RxBuf+14)-1)*3;
;	genPlus
;     genPlusIncr
	mov	a,#0x0E
;	Peephole 236.a	used r2 instead of ar2
	add	a,r2
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
;	Peephole 236.b	used r3 instead of ar3
	addc	a,r3
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
;	genMinus
;	genMinusDec
	mov	r4,a
;	Peephole 105	removed redundant mov
	dec	a
;	genMult
;	genMultOneByte
	mov	b,#0x03
	mul	ab
	C$TSIPMon.c$739$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:739: lcdbuf[11] = Month[mo];
;	genPlus
	mov	r4,a
;	Peephole 177.b	removed redundant mov
;	Peephole 181	changed mov to clr
;	genPointerGet
;	genCodePointerGet
;	Peephole 186.d	optimized movc sequence
	mov	dptr,#_Month
	movc	a,@a+dptr
;	genPointerSet
;     genFarPointerSet
	mov	r5,a
	mov	dptr,#(_lcdbuf + 0x000b)
;	Peephole 100	removed redundant mov
	movx	@dptr,a
	C$TSIPMon.c$740$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:740: lcdbuf[12] = Month[mo+1];
;	genPlus
;     genPlusIncr
	mov	a,#0x01
;	Peephole 236.a	used r4 instead of ar4
	add	a,r4
;	genPlus
;	Peephole 240	use clr instead of addc a,#0
;	genPointerGet
;	genCodePointerGet
;	Peephole 186.d	optimized movc sequence
	mov	dptr,#_Month
	movc	a,@a+dptr
;	genPointerSet
;     genFarPointerSet
	mov	r5,a
	mov	dptr,#(_lcdbuf + 0x000c)
;	Peephole 100	removed redundant mov
	movx	@dptr,a
	C$TSIPMon.c$741$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:741: lcdbuf[13] = Month[mo+2];
;	genPlus
;     genPlusIncr
	mov	a,#0x02
;	Peephole 236.a	used r4 instead of ar4
	add	a,r4
;	genPlus
;	Peephole 240	use clr instead of addc a,#0
;	genPointerGet
;	genCodePointerGet
;	Peephole 186.d	optimized movc sequence
	mov	dptr,#_Month
	movc	a,@a+dptr
;	genPointerSet
;     genFarPointerSet
	mov	r5,a
	mov	dptr,#(_lcdbuf + 0x000d)
;	Peephole 100	removed redundant mov
	movx	@dptr,a
	C$TSIPMon.c$742$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:742: yr.b.hi = *(RxBuf+15);
;	genPlus
;     genPlusIncr
	mov	a,#0x0F
;	Peephole 236.a	used r2 instead of ar2
	add	a,r2
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
;	Peephole 236.b	used r3 instead of ar3
	addc	a,r3
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r5,a
;	genPointerSet
;	genNearPointerSet
;	genDataPointerSet
	mov	(_PrimaryTiming_yr_1_1 + 0x0001),r5
	C$TSIPMon.c$743$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:743: yr.b.lo = *(RxBuf+16);
;	genPlus
;     genPlusIncr
	mov	a,#0x10
;	Peephole 236.a	used r2 instead of ar2
	add	a,r2
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
;	Peephole 236.b	used r3 instead of ar3
	addc	a,r3
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
;	genPointerSet
;	genNearPointerSet
;	genDataPointerSet
	C$TSIPMon.c$745$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:745: mo = yr.u - 2000;
;	genAssign
;	genCast
;	Peephole 177.a	removed redundant mov
;	genMinus
	mov	r2,a
	mov	_PrimaryTiming_yr_1_1,r2
;	Peephole 177.d	removed redundant move
	add	a,#0x30
	mov	r4,a
	C$TSIPMon.c$746$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:746: UnsignedToAscii( (uint)mo, lcdbuf+14, 2 );
;	genCast
	mov	r2,#0x00
;	genPlus
;     genPlusIncr
	mov	a,#0x0E
	add	a,#_lcdbuf
	mov	_UnsignedToAscii_PARM_2,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,#(_lcdbuf >> 8)
	mov	(_UnsignedToAscii_PARM_2 + 1),a
;	genAssign
	mov	_UnsignedToAscii_PARM_3,#0x02
;	genCall
	mov	dpl,r4
	mov	dph,r2
	lcall	_UnsignedToAscii
	C$TSIPMon.c$747$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:747: if( lcdbuf[14] == ' ' ) lcdbuf[14] = '0';
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_lcdbuf + 0x000e)
	movx	a,@dptr
	mov	r2,a
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x20,00110$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00126$
;	Peephole 300	removed redundant label 00127$
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#(_lcdbuf + 0x000e)
	mov	a,#0x30
	movx	@dptr,a
00110$:
	C$TSIPMon.c$748$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:748: lcdbuf[16] = '\0';
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#(_lcdbuf + 0x0010)
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
;	Peephole 300	removed redundant label 00111$
	C$TSIPMon.c$758$1$1 ==.
	XG$PrimaryTiming$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'SupplementalTiming'
;------------------------------------------------------------
;mode                      Allocated with name '_SupplementalTiming_mode_1_1'
;RxBuf                     Allocated with name '_SupplementalTiming_RxBuf_1_1'
;temp                      Allocated with name '_SupplementalTiming_temp_1_1'
;val                       Allocated with name '_SupplementalTiming_val_1_1'
;fval                      Allocated with name '_SupplementalTiming_fval_1_1'
;sloc0                     Allocated with name '_SupplementalTiming_sloc0_1_0'
;sloc1                     Allocated with name '_SupplementalTiming_sloc1_1_0'
;------------------------------------------------------------
	G$SupplementalTiming$0$0 ==.
	C$TSIPMon.c$764$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:764: void SupplementalTiming( uchar TXRX_STORAGE_CLASS *RxBuf ){
;	-----------------------------------------
;	 function SupplementalTiming
;	-----------------------------------------
_SupplementalTiming:
;	genReceive
	mov	_SupplementalTiming_RxBuf_1_1,dpl
	mov	(_SupplementalTiming_RxBuf_1_1 + 1),dph
	C$TSIPMon.c$786$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:786: printLCD( 1, lcdbuf, 0 );	// print 1st line
;	genAddrOf
	mov	_printLCD_PARM_2,#_lcdbuf
	mov	(_printLCD_PARM_2 + 1),#(_lcdbuf >> 8)
;	genAssign
	mov	_printLCD_PARM_3,#0x00
;	genCall
	mov	dpl,#0x01
	lcall	_printLCD
	C$TSIPMon.c$791$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:791: Alarms.b.hi = RxBuf[10];
;	genPlus
;     genPlusIncr
	mov	a,#0x0A
	add	a,_SupplementalTiming_RxBuf_1_1
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
;	genPointerSet
;     genFarPointerSet
	mov	r4,a
	mov	dptr,#(_Alarms + 0x0001)
;	Peephole 100	removed redundant mov
	movx	@dptr,a
	C$TSIPMon.c$792$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:792: Alarms.b.lo = RxBuf[11];
;	genPlus
;     genPlusIncr
	mov	a,#0x0B
	add	a,_SupplementalTiming_RxBuf_1_1
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
;	genPointerSet
;     genFarPointerSet
	mov	r4,a
	mov	dptr,#_Alarms
;	Peephole 100	removed redundant mov
	movx	@dptr,a
	C$TSIPMon.c$794$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:794: Alarms.u = Alarms.u<<5;
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#_Alarms
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
;	genLeftShift
;	genLeftShiftLiteral
;	genlshTwo
	mov	r5,a
;	Peephole 105	removed redundant mov
	swap	a
	rl	a
	anl	a,#0xe0
	xch	a,r4
	swap	a
	rl	a
	xch	a,r4
	xrl	a,r4
	xch	a,r4
	anl	a,#0xe0
	xch	a,r4
	xrl	a,r4
	mov	r5,a
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#_Alarms
	mov	a,r4
	movx	@dptr,a
	inc	dptr
	mov	a,r5
	movx	@dptr,a
	C$TSIPMon.c$796$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:796: Alarms.b.lo |= RxBuf[9];
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#_Alarms
	movx	a,@dptr
	mov	r4,a
;	genPlus
;     genPlusIncr
	mov	a,#0x09
	add	a,_SupplementalTiming_RxBuf_1_1
	mov	r5,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
	mov	r6,a
;	genPointerGet
;	genFarPointerGet
	mov	dpl,r5
	mov	dph,r6
	movx	a,@dptr
;	genOr
	mov	r7,a
;	Peephole 105	removed redundant mov
	orl	ar4,a
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#_Alarms
	mov	a,r4
	movx	@dptr,a
	C$TSIPMon.c$799$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:799: c = !c;  // only change display every 2nd time thru ( about every 2 seconds)
;	genNot
	cpl	_SupplementalTiming_c_1_1
	C$TSIPMon.c$800$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:800: if( c )
;	genIfx
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	_SupplementalTiming_c_1_1,00102$
;	Peephole 300	removed redundant label 00143$
	C$TSIPMon.c$801$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:801: return;
;	genRet
;	Peephole 251.a	replaced ljmp to ret with ret
	ret
00102$:
	C$TSIPMon.c$803$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:803: ClearLCD( 2 );
;	genCall
	mov	dpl,#0x02
	push	ar5
	push	ar6
	lcall	_ClearLCD
	pop	ar6
	pop	ar5
	C$TSIPMon.c$804$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:804: if( Alarms.u != 0 && mode == NUM_DISPLAY_MODES - 1 ){
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#_Alarms
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
;	genCmpEq
;	gencjneshort
	cjne	r4,#0x00,00144$
	cjne	r7,#0x00,00144$
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00108$
00144$:
;	genCmpEq
;	gencjneshort
	mov	a,_SupplementalTiming_mode_1_1
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	a,#0x05,00108$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00145$
;	Peephole 300	removed redundant label 00146$
	C$TSIPMon.c$805$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:805: b = Fault_Msg_Query( Alarms.u, lcdbuf, ALARM_MSG[0] );
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#_Alarms
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
;	genAddrOf
	mov	_Fault_Msg_Query_PARM_2,#_lcdbuf
	mov	(_Fault_Msg_Query_PARM_2 + 1),#(_lcdbuf >> 8)
;	genAddrOf
	mov	_Fault_Msg_Query_PARM_3,#_ALARM_MSG
	mov	(_Fault_Msg_Query_PARM_3 + 1),#(_ALARM_MSG >> 8)
;	genCall
	mov	dpl,r4
	mov	dph,r7
	push	ar5
	push	ar6
	lcall	_Fault_Msg_Query
	mov	_SupplementalTiming_b_1_1,c
	pop	ar6
	pop	ar5
	C$TSIPMon.c$806$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:806: if( b )
;	genIfx
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	_SupplementalTiming_b_1_1,00104$
;	Peephole 300	removed redundant label 00147$
	C$TSIPMon.c$807$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:807: printLCD( 2, lcdbuf, 0 ); 
;	genAddrOf
	mov	_printLCD_PARM_2,#_lcdbuf
	mov	(_printLCD_PARM_2 + 1),#(_lcdbuf >> 8)
;	genAssign
	mov	_printLCD_PARM_3,#0x00
;	genCall
	mov	dpl,#0x02
	push	ar5
	push	ar6
	lcall	_printLCD
	pop	ar6
	pop	ar5
00104$:
	C$TSIPMon.c$808$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:808: if( RxBuf[9] != 0 ) // if critical alarm, keep showing it
;	genPointerGet
;	genFarPointerGet
	mov	dpl,r5
	mov	dph,r6
	movx	a,@dptr
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
	mov	r5,a
;	Peephole 115.b	jump optimization
	jz	00108$
;	Peephole 300	removed redundant label 00148$
	C$TSIPMon.c$809$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:809: return;        
;	genRet
;	Peephole 251.a	replaced ljmp to ret with ret
	ret
00108$:
	C$TSIPMon.c$812$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:812: if( !b ){
;	genIfx
;	genIfxJump
	jnb	_SupplementalTiming_b_1_1,00149$
;	Peephole 251.a	replaced ljmp to ret with ret
	ret
00149$:
	C$TSIPMon.c$813$2$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:813: if( ++mode >= NUM_DISPLAY_MODES )
;	genPlus
;     genPlusIncr
	inc	_SupplementalTiming_mode_1_1
;	genCmpLt
;	genCmp
	clr	c
	mov	a,_SupplementalTiming_mode_1_1
	xrl	a,#0x80
	subb	a,#0x86
;	genIfxJump
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 160.a	removed sjmp by inverse jump logic
	jc	00111$
;	Peephole 300	removed redundant label 00150$
	C$TSIPMon.c$814$2$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:814: mode = 0;
;	genAssign
	mov	_SupplementalTiming_mode_1_1,#0x00
00111$:
	C$TSIPMon.c$816$2$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:816: val = 28;
;	genAssign
	mov	_SupplementalTiming_val_1_1,#0x1C
	C$TSIPMon.c$817$2$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:817: fval = 10000;
;	genAssign
	mov	_SupplementalTiming_fval_1_1,#0x10
	mov	(_SupplementalTiming_fval_1_1 + 1),#0x27
	C$TSIPMon.c$818$2$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:818: switch( mode ){
;	genCmpLt
;	genCmp
	mov	a,_SupplementalTiming_mode_1_1
;	genIfxJump
	jnb	acc.7,00151$
	ljmp	00125$
00151$:
;	genCmpGt
;	genCmp
	clr	c
;	Peephole 159	avoided xrl during execution
	mov	a,#(0x05 ^ 0x80)
	mov	b,_SupplementalTiming_mode_1_1
	xrl	b,#0x80
	subb	a,b
;	genIfxJump
	jnc	00152$
	ljmp	00125$
00152$:
;	genJumpTab
	mov	a,_SupplementalTiming_mode_1_1
;	Peephole 254	optimized left shift
	add	a,_SupplementalTiming_mode_1_1
	add	a,_SupplementalTiming_mode_1_1
	mov	dptr,#00153$
	jmp	@a+dptr
00153$:
	ljmp	00112$
	ljmp	00113$
	ljmp	00114$
	ljmp	00115$
	ljmp	00116$
	ljmp	00117$
	C$TSIPMon.c$819$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:819: case 0:	// disciplining mode
00112$:
	C$TSIPMon.c$820$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:820: strcpy( lcdbuf , DiscMode[RxBuf[2]]);
;	genPlus
;     genPlusIncr
	mov	dpl,_SupplementalTiming_RxBuf_1_1
	mov	dph,(_SupplementalTiming_RxBuf_1_1 + 1)
	inc	dptr
	inc	dptr
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
;	genMult
;	genMultOneByte
	mov	r7,a
;	Peephole 105	removed redundant mov
	mov	b,#0x11
	mul	ab
;	genPlus
	add	a,#_DiscMode
	mov	r2,a
;	Peephole 240	use clr instead of addc a,#0
	clr	a
	addc	a,#(_DiscMode >> 8)
	mov	r3,a
;	genCast
	mov	_strcpy_PARM_2,r2
	mov	(_strcpy_PARM_2 + 1),r3
	mov	(_strcpy_PARM_2 + 2),#0x80
;	genCall
;	Peephole 182.a	used 16 bit load of DPTR
	mov	dptr,#_lcdbuf
	mov	b,#0x00
	lcall	_strcpy
	C$TSIPMon.c$821$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:821: break;
	ljmp	00125$
	C$TSIPMon.c$823$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:823: case 1:	// Discipling Activity
00113$:
	C$TSIPMon.c$824$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:824: strcpy( lcdbuf , DiscActivity[RxBuf[13]]);
;	genPlus
;     genPlusIncr
	mov	a,#0x0D
	add	a,_SupplementalTiming_RxBuf_1_1
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
;	genMult
;	genMultOneByte
	mov	r7,a
;	Peephole 105	removed redundant mov
	mov	b,#0x11
	mul	ab
;	genPlus
	add	a,#_DiscActivity
	mov	r2,a
;	Peephole 240	use clr instead of addc a,#0
	clr	a
	addc	a,#(_DiscActivity >> 8)
	mov	r3,a
;	genCast
	mov	_strcpy_PARM_2,r2
	mov	(_strcpy_PARM_2 + 1),r3
	mov	(_strcpy_PARM_2 + 2),#0x80
;	genCall
;	Peephole 182.a	used 16 bit load of DPTR
	mov	dptr,#_lcdbuf
	mov	b,#0x00
	lcall	_strcpy
	C$TSIPMon.c$825$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:825: break;
	ljmp	00125$
	C$TSIPMon.c$827$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:827: case 2:	// Receiver mode
00114$:
	C$TSIPMon.c$828$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:828: strcpy( lcdbuf , RxMode[RxBuf[1]]);
;	genPlus
;     genPlusIncr
	mov	dpl,_SupplementalTiming_RxBuf_1_1
	mov	dph,(_SupplementalTiming_RxBuf_1_1 + 1)
	inc	dptr
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
;	genMult
;	genMultOneByte
	mov	r7,a
;	Peephole 105	removed redundant mov
	mov	b,#0x11
	mul	ab
;	genPlus
	add	a,#_RxMode
	mov	r2,a
;	Peephole 240	use clr instead of addc a,#0
	clr	a
	addc	a,#(_RxMode >> 8)
	mov	r3,a
;	genCast
	mov	_strcpy_PARM_2,r2
	mov	(_strcpy_PARM_2 + 1),r3
	mov	(_strcpy_PARM_2 + 2),#0x80
;	genCall
;	Peephole 182.a	used 16 bit load of DPTR
	mov	dptr,#_lcdbuf
	mov	b,#0x00
	lcall	_strcpy
	C$TSIPMon.c$829$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:829: break;
	ljmp	00125$
	C$TSIPMon.c$831$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:831: case 3:	// GPS Decode Status
00115$:
	C$TSIPMon.c$832$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:832: strcpy( lcdbuf , GPSDecodeStatus[RxBuf[12]]);
;	genPlus
;     genPlusIncr
	mov	a,#0x0C
	add	a,_SupplementalTiming_RxBuf_1_1
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
;	genMult
;	genMultOneByte
	mov	r7,a
;	Peephole 105	removed redundant mov
	mov	b,#0x11
	mul	ab
;	genPlus
	add	a,#_GPSDecodeStatus
	mov	r2,a
	mov	a,#(_GPSDecodeStatus >> 8)
	addc	a,b
	mov	r3,a
;	genCast
	mov	_strcpy_PARM_2,r2
	mov	(_strcpy_PARM_2 + 1),r3
	mov	(_strcpy_PARM_2 + 2),#0x80
;	genCall
;	Peephole 182.a	used 16 bit load of DPTR
	mov	dptr,#_lcdbuf
	mov	b,#0x00
	lcall	_strcpy
	C$TSIPMon.c$833$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:833: break;
	ljmp	00125$
	C$TSIPMon.c$835$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:835: case 4:	// RxBuf[32-35] is temperature (float)
00116$:
	C$TSIPMon.c$836$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:836: val = 32;
;	genAssign
	mov	_SupplementalTiming_val_1_1,#0x20
	C$TSIPMon.c$837$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:837: fval = 100;
;	genAssign
	mov	_SupplementalTiming_fval_1_1,#0x64
	clr	a
	mov	(_SupplementalTiming_fval_1_1 + 1),a
	C$TSIPMon.c$840$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:840: case 5:	// RxBuf[28-31] is DAC Voltage (float)
00117$:
	C$TSIPMon.c$841$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:841: temp.b.hhi = RxBuf[val];
;	genPlus
	mov	a,_SupplementalTiming_val_1_1
	add	a,_SupplementalTiming_RxBuf_1_1
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r7,a
;	genPointerSet
;	genNearPointerSet
;	genDataPointerSet
	mov	(_SupplementalTiming_temp_1_1 + 0x0003),r7
	C$TSIPMon.c$842$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:842: temp.b.hi = RxBuf[val+1];
;	genCast
	mov	r7,_SupplementalTiming_val_1_1
	mov	r5,#0x00
;	genPlus
;     genPlusIncr
	mov	a,#0x01
;	Peephole 236.a	used r7 instead of ar7
	add	a,r7
	mov	r6,a
;	Peephole 181	changed mov to clr
	clr	a
;	Peephole 236.b	used r5 instead of ar5
	addc	a,r5
	mov	r2,a
;	genPlus
;	Peephole 236.g	used r6 instead of ar6
	mov	a,r6
	add	a,_SupplementalTiming_RxBuf_1_1
	mov	dpl,a
;	Peephole 236.g	used r2 instead of ar2
	mov	a,r2
	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r2,a
;	genPointerSet
;	genNearPointerSet
;	genDataPointerSet
	mov	(_SupplementalTiming_temp_1_1 + 0x0002),r2
	C$TSIPMon.c$843$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:843: temp.b.lo = RxBuf[val+2];
;	genPlus
;     genPlusIncr
	mov	a,#0x02
;	Peephole 236.a	used r7 instead of ar7
	add	a,r7
	mov	r2,a
;	Peephole 181	changed mov to clr
	clr	a
;	Peephole 236.b	used r5 instead of ar5
	addc	a,r5
	mov	r3,a
;	genPlus
;	Peephole 236.g	used r2 instead of ar2
	mov	a,r2
	add	a,_SupplementalTiming_RxBuf_1_1
	mov	dpl,a
;	Peephole 236.g	used r3 instead of ar3
	mov	a,r3
	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r2,a
;	genPointerSet
;	genNearPointerSet
;	genDataPointerSet
	mov	(_SupplementalTiming_temp_1_1 + 0x0001),r2
	C$TSIPMon.c$844$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:844: temp.b.llo = RxBuf[val+3];
;	genPlus
;     genPlusIncr
	mov	a,#0x03
;	Peephole 236.a	used r7 instead of ar7
	add	a,r7
	mov	r7,a
;	Peephole 181	changed mov to clr
	clr	a
;	Peephole 236.b	used r5 instead of ar5
	addc	a,r5
	mov	r5,a
;	genPlus
;	Peephole 236.g	used r7 instead of ar7
	mov	a,r7
	add	a,_SupplementalTiming_RxBuf_1_1
	mov	dpl,a
;	Peephole 236.g	used r5 instead of ar5
	mov	a,r5
	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r2,a
;	genPointerSet
;	genNearPointerSet
;	genDataPointerSet
	mov	_SupplementalTiming_temp_1_1,r2
	C$TSIPMon.c$846$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:846: val = temp.f;
;	genAssign
;	genCall
	mov	dpl,_SupplementalTiming_temp_1_1
	mov	dph,(_SupplementalTiming_temp_1_1 + 1)
	mov	b,(_SupplementalTiming_temp_1_1 + 2)
	mov	a,(_SupplementalTiming_temp_1_1 + 3)
	lcall	___fs2uchar
	mov	_SupplementalTiming_val_1_1,dpl
	C$TSIPMon.c$847$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:847: fval = ((temp.f - val) * fval);
;	genPointerGet
;	genNearPointerGet
;	genDataPointerGet
	mov	_SupplementalTiming_sloc1_1_0,_SupplementalTiming_temp_1_1
	mov	(_SupplementalTiming_sloc1_1_0 + 1),(_SupplementalTiming_temp_1_1 + 1)
	mov	(_SupplementalTiming_sloc1_1_0 + 2),(_SupplementalTiming_temp_1_1 + 2)
	mov	(_SupplementalTiming_sloc1_1_0 + 3),(_SupplementalTiming_temp_1_1 + 3)
;	genCast
	mov	r7,_SupplementalTiming_val_1_1
	mov	r4,#0x00
;	genCall
	mov	dpl,r7
	mov	dph,r4
	lcall	___sint2fs
	mov	r4,dpl
	mov	r7,dph
	mov	r2,b
	mov	r3,a
;	genIpush
	push	ar4
	push	ar7
	push	ar2
	push	ar3
;	genCall
	mov	dpl,_SupplementalTiming_sloc1_1_0
	mov	dph,(_SupplementalTiming_sloc1_1_0 + 1)
	mov	b,(_SupplementalTiming_sloc1_1_0 + 2)
	mov	a,(_SupplementalTiming_sloc1_1_0 + 3)
	lcall	___fssub
	mov	_SupplementalTiming_sloc1_1_0,dpl
	mov	(_SupplementalTiming_sloc1_1_0 + 1),dph
	mov	(_SupplementalTiming_sloc1_1_0 + 2),b
	mov	(_SupplementalTiming_sloc1_1_0 + 3),a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
;	genCall
	mov	dpl,_SupplementalTiming_fval_1_1
	mov	dph,(_SupplementalTiming_fval_1_1 + 1)
	lcall	___uint2fs
	mov	r6,dpl
	mov	r7,dph
	mov	r2,b
	mov	r3,a
;	genIpush
	push	ar6
	push	ar7
	push	ar2
	push	ar3
;	genCall
	mov	dpl,_SupplementalTiming_sloc1_1_0
	mov	dph,(_SupplementalTiming_sloc1_1_0 + 1)
	mov	b,(_SupplementalTiming_sloc1_1_0 + 2)
	mov	a,(_SupplementalTiming_sloc1_1_0 + 3)
	lcall	___fsmul
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
;	genCall
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	___fs2uint
	mov	_SupplementalTiming_fval_1_1,dpl
	mov	(_SupplementalTiming_fval_1_1 + 1),dph
	C$TSIPMon.c$853$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:853: strcpy( lcdbuf, prompt[mode-4] );
;	genMinus
;	genMinusDec
	mov	a,_SupplementalTiming_mode_1_1
	add	a,#0xfc
;	genMult
;	genMultOneByte
	mov	b,#0x09
	mul	ab
;	genPlus
	add	a,#_prompt
	mov	r2,a
;	Peephole 240	use clr instead of addc a,#0
	clr	a
	addc	a,#(_prompt >> 8)
	mov	r3,a
;	genCast
	mov	_strcpy_PARM_2,r2
	mov	(_strcpy_PARM_2 + 1),r3
	mov	(_strcpy_PARM_2 + 2),#0x80
;	genCall
;	Peephole 182.a	used 16 bit load of DPTR
	mov	dptr,#_lcdbuf
	mov	b,#0x00
	lcall	_strcpy
	C$TSIPMon.c$854$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:854: UnsignedToAscii( val, lcdbuf+6, 3 );
;	genCast
	mov	r4,_SupplementalTiming_val_1_1
	mov	r2,#0x00
;	genPlus
;     genPlusIncr
	mov	a,#0x06
	add	a,#_lcdbuf
	mov	_UnsignedToAscii_PARM_2,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,#(_lcdbuf >> 8)
	mov	(_UnsignedToAscii_PARM_2 + 1),a
;	genAssign
	mov	_UnsignedToAscii_PARM_3,#0x03
;	genCall
	mov	dpl,r4
	mov	dph,r2
	lcall	_UnsignedToAscii
	C$TSIPMon.c$855$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:855: lcdbuf[9] = '.';
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#(_lcdbuf + 0x0009)
	mov	a,#0x2E
	movx	@dptr,a
	C$TSIPMon.c$856$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:856: UnsignedToAscii( fval, lcdbuf+10, 2 + 2*(mode-4) );
;	genPlus
;     genPlusIncr
	mov	a,#0x0A
	add	a,#_lcdbuf
	mov	_UnsignedToAscii_PARM_2,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,#(_lcdbuf >> 8)
	mov	(_UnsignedToAscii_PARM_2 + 1),a
;	genMinus
;	genMinusDec
	mov	a,_SupplementalTiming_mode_1_1
	add	a,#0xfc
;	genLeftShift
;	genLeftShiftLiteral
;	genlshOne
;	Peephole 105	removed redundant mov
;	Peephole 204	removed redundant mov
	add	a,acc
;	genPlus
;     genPlusIncr
;	Peephole 236.a	used r2 instead of ar2
	mov	r2,a
;	Peephole 214	reduced some extra moves
	add	a,#0x02
	mov	_UnsignedToAscii_PARM_3,a
;	genCall
	mov	dpl,_SupplementalTiming_fval_1_1
	mov	dph,(_SupplementalTiming_fval_1_1 + 1)
	lcall	_UnsignedToAscii
	C$TSIPMon.c$858$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:858: for( val=0; val<3; val++ ){
;	genAssign
	mov	r2,#0x00
00121$:
;	genCmpLt
;	genCmp
	cjne	r2,#0x03,00154$
00154$:
;	genIfxJump
;	Peephole 108.a	removed ljmp by inverse jump logic
	jnc	00125$
;	Peephole 300	removed redundant label 00155$
	C$TSIPMon.c$859$4$5 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:859: if( lcdbuf[10+val] == ' ' ) 
;	genPlus
;     genPlusIncr
	mov	a,#0x0A
;	Peephole 236.a	used r2 instead of ar2
	add	a,r2
;	genPlus
	add	a,#_lcdbuf
	mov	dpl,a
;	Peephole 240	use clr instead of addc a,#0
	clr	a
	addc	a,#(_lcdbuf >> 8)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r3,a
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r3,#0x20,00125$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00156$
;	Peephole 300	removed redundant label 00157$
	C$TSIPMon.c$860$4$5 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:860: lcdbuf[10+val] = '0';
;	genPlus
;     genPlusIncr
	mov	a,#0x0A
;	Peephole 236.a	used r2 instead of ar2
	add	a,r2
;	genPlus
	add	a,#_lcdbuf
	mov	dpl,a
;	Peephole 240	use clr instead of addc a,#0
	clr	a
	addc	a,#(_lcdbuf >> 8)
	mov	dph,a
;	genPointerSet
;     genFarPointerSet
	mov	a,#0x30
	movx	@dptr,a
	C$TSIPMon.c$858$3$4 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:858: for( val=0; val<3; val++ ){
;	genPlus
;     genPlusIncr
	inc	r2
	C$TSIPMon.c$866$2$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:866: } // switch( mode )
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00121$
00125$:
	C$TSIPMon.c$867$2$3 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:867: printLCD( 2, lcdbuf, 0 );
;	genAddrOf
	mov	_printLCD_PARM_2,#_lcdbuf
	mov	(_printLCD_PARM_2 + 1),#(_lcdbuf >> 8)
;	genAssign
	mov	_printLCD_PARM_3,#0x00
;	genCall
	mov	dpl,#0x02
	C$TSIPMon.c$870$2$1 ==.
	XG$SupplementalTiming$0$0 ==.
;	Peephole 253.b	replaced lcall/ret with ljmp
	ljmp	_printLCD
;
;------------------------------------------------------------
;Allocation info for local variables in function 'External_Interrupt_0'
;------------------------------------------------------------
;------------------------------------------------------------
	G$External_Interrupt_0$0$0 ==.
	C$TSIPMon.c$876$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:876: void External_Interrupt_0( void ) interrupt 0{
;	-----------------------------------------
;	 function External_Interrupt_0
;	-----------------------------------------
_External_Interrupt_0:
	push	acc
	push	b
	push	dpl
	push	dph
	push	(0+2)
	push	(0+3)
	push	(0+4)
	push	(0+5)
	push	(0+6)
	push	(0+7)
	push	(0+0)
	push	(0+1)
	push	psw
	mov	psw,#0x00
;	genIfx
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	C$TSIPMon.c$881$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:881: switch2 = 0;
;	genAssign
;	Peephole 250.a	using atomic test and clear
	jbc	_switch2,00106$
	sjmp	00103$
00106$:
	C$TSIPMon.c$882$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:882: func2 = !LED2;
;	genNot
	mov	c,_P0_7
	cpl	c
	C$TSIPMon.c$883$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:883: LED2 = func2;
;	genAssign
	mov  _func2,c
;	Peephole 177.a	removed redundant mov
	mov	_P0_7,c
	C$TSIPMon.c$884$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:884: TimerStart( SWITCH_TIMER, 50 );	// to reset switch2 to 1
;	genAssign
	mov	_TimerStart_PARM_2,#0x32
	clr	a
	mov	(_TimerStart_PARM_2 + 1),a
;	genCall
	mov	dpl,#0x02
	lcall	_TimerStart
00103$:
	pop	psw
	pop	(0+1)
	pop	(0+0)
	pop	(0+7)
	pop	(0+6)
	pop	(0+5)
	pop	(0+4)
	pop	(0+3)
	pop	(0+2)
	pop	dph
	pop	dpl
	pop	b
	pop	acc
	C$TSIPMon.c$887$2$1 ==.
	XG$External_Interrupt_0$0$0 ==.
	reti
;------------------------------------------------------------
;Allocation info for local variables in function 'External_Interrupt_1'
;------------------------------------------------------------
;------------------------------------------------------------
	G$External_Interrupt_1$0$0 ==.
	C$TSIPMon.c$893$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:893: void External_Interrupt_1( void ) interrupt 2{
;	-----------------------------------------
;	 function External_Interrupt_1
;	-----------------------------------------
_External_Interrupt_1:
	push	acc
	push	b
	push	dpl
	push	dph
	push	(0+2)
	push	(0+3)
	push	(0+4)
	push	(0+5)
	push	(0+6)
	push	(0+7)
	push	(0+0)
	push	(0+1)
	push	psw
	mov	psw,#0x00
;	genIfx
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	_switch1,00104$
;	Peephole 300	removed redundant label 00108$
	C$TSIPMon.c$896$1$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:896: if( switch1 != 0 && !TimerRunning( SWITCH_TIMER )){
;	genCall
	mov	dpl,#0x02
	lcall	_TimerRunning
;	genIfx
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
;	Peephole 129.a	jump optimization
	jc	00104$
;	Peephole 300	removed redundant label 00109$
	C$TSIPMon.c$898$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:898: switch1 = 0;
;	genAssign
	clr	_switch1
	C$TSIPMon.c$899$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:899: func1 = TRUE;
;	genAssign
	setb	_func1
	C$TSIPMon.c$904$2$2 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:904: TimerStart( SWITCH_TIMER, 150 );	// to reset switch1 to 1
;	genAssign
	mov	_TimerStart_PARM_2,#0x96
	clr	a
	mov	(_TimerStart_PARM_2 + 1),a
;	genCall
	mov	dpl,#0x02
	lcall	_TimerStart
00104$:
	pop	psw
	pop	(0+1)
	pop	(0+0)
	pop	(0+7)
	pop	(0+6)
	pop	(0+5)
	pop	(0+4)
	pop	(0+3)
	pop	(0+2)
	pop	dph
	pop	dpl
	pop	b
	pop	acc
	C$TSIPMon.c$907$2$1 ==.
	XG$External_Interrupt_1$0$0 ==.
	reti
;------------------------------------------------------------
;Allocation info for local variables in function 'Timer_1_Overflow'
;------------------------------------------------------------
;------------------------------------------------------------
	G$Timer_1_Overflow$0$0 ==.
	C$TSIPMon.c$915$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:915: void Timer_1_Overflow( void ) interrupt 3{}
;	-----------------------------------------
;	 function Timer_1_Overflow
;	-----------------------------------------
_Timer_1_Overflow:
;	Peephole 300	removed redundant label 00101$
	C$TSIPMon.c$915$2$1 ==.
	XG$Timer_1_Overflow$0$0 ==.
	reti
;	eliminated unneeded push/pop psw
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;	eliminated unneeded push/pop acc
;------------------------------------------------------------
;Allocation info for local variables in function 'SPI0'
;------------------------------------------------------------
;------------------------------------------------------------
	G$SPI0$0$0 ==.
	C$TSIPMon.c$918$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:918: void SPI0( void ) interrupt 6{}
;	-----------------------------------------
;	 function SPI0
;	-----------------------------------------
_SPI0:
;	Peephole 300	removed redundant label 00101$
	C$TSIPMon.c$918$2$1 ==.
	XG$SPI0$0$0 ==.
	reti
;	eliminated unneeded push/pop psw
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;	eliminated unneeded push/pop acc
;------------------------------------------------------------
;Allocation info for local variables in function 'SMB0'
;------------------------------------------------------------
;------------------------------------------------------------
	G$SMB0$0$0 ==.
	C$TSIPMon.c$919$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:919: void SMB0( void ) interrupt 7{}
;	-----------------------------------------
;	 function SMB0
;	-----------------------------------------
_SMB0:
;	Peephole 300	removed redundant label 00101$
	C$TSIPMon.c$919$2$1 ==.
	XG$SMB0$0$0 ==.
	reti
;	eliminated unneeded push/pop psw
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;	eliminated unneeded push/pop acc
;------------------------------------------------------------
;Allocation info for local variables in function 'ADC0_Window_Comparator'
;------------------------------------------------------------
;------------------------------------------------------------
	G$ADC0_Window_Comparator$0$0 ==.
	C$TSIPMon.c$921$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:921: void ADC0_Window_Comparator( void ) interrupt 9{}
;	-----------------------------------------
;	 function ADC0_Window_Comparator
;	-----------------------------------------
_ADC0_Window_Comparator:
;	Peephole 300	removed redundant label 00101$
	C$TSIPMon.c$921$2$1 ==.
	XG$ADC0_Window_Comparator$0$0 ==.
	reti
;	eliminated unneeded push/pop psw
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;	eliminated unneeded push/pop acc
;------------------------------------------------------------
;Allocation info for local variables in function 'ADC0_End_of_Conversion'
;------------------------------------------------------------
;------------------------------------------------------------
	G$ADC0_End_of_Conversion$0$0 ==.
	C$TSIPMon.c$922$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:922: void ADC0_End_of_Conversion( void ) interrupt 10{}
;	-----------------------------------------
;	 function ADC0_End_of_Conversion
;	-----------------------------------------
_ADC0_End_of_Conversion:
;	Peephole 300	removed redundant label 00101$
	C$TSIPMon.c$922$2$1 ==.
	XG$ADC0_End_of_Conversion$0$0 ==.
	reti
;	eliminated unneeded push/pop psw
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;	eliminated unneeded push/pop acc
;------------------------------------------------------------
;Allocation info for local variables in function 'Programmable_Counter_Array'
;------------------------------------------------------------
;------------------------------------------------------------
	G$Programmable_Counter_Array$0$0 ==.
	C$TSIPMon.c$923$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:923: void Programmable_Counter_Array( void ) interrupt 11{}
;	-----------------------------------------
;	 function Programmable_Counter_Array
;	-----------------------------------------
_Programmable_Counter_Array:
;	Peephole 300	removed redundant label 00101$
	C$TSIPMon.c$923$2$1 ==.
	XG$Programmable_Counter_Array$0$0 ==.
	reti
;	eliminated unneeded push/pop psw
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;	eliminated unneeded push/pop acc
;------------------------------------------------------------
;Allocation info for local variables in function 'Comparator'
;------------------------------------------------------------
;------------------------------------------------------------
	G$Comparator$0$0 ==.
	C$TSIPMon.c$924$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:924: void Comparator( void ) interrupt 12{}
;	-----------------------------------------
;	 function Comparator
;	-----------------------------------------
_Comparator:
;	Peephole 300	removed redundant label 00101$
	C$TSIPMon.c$924$2$1 ==.
	XG$Comparator$0$0 ==.
	reti
;	eliminated unneeded push/pop psw
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;	eliminated unneeded push/pop acc
;------------------------------------------------------------
;Allocation info for local variables in function 'Timer_3_Overflow'
;------------------------------------------------------------
;------------------------------------------------------------
	G$Timer_3_Overflow$0$0 ==.
	C$TSIPMon.c$926$2$1 ==.
;	C:/SDCC/GPSMon/dev/TSIPMon.c:926: void Timer_3_Overflow( void ) interrupt 14{}
;	-----------------------------------------
;	 function Timer_3_Overflow
;	-----------------------------------------
_Timer_3_Overflow:
;	Peephole 300	removed redundant label 00101$
	C$TSIPMon.c$926$2$1 ==.
	XG$Timer_3_Overflow$0$0 ==.
	reti
;	eliminated unneeded push/pop psw
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;	eliminated unneeded push/pop acc
	.area CSEG    (CODE)
	.area CONST   (CODE)
G$Month$0$0 == .
_Month:
	.ascii "JanFebMarAprMayJunJulAugSepOctNovDec"
	.db 0x00
G$RxMode$0$0 == .
_RxMode:
	.ascii "RX: Auto 2D/3D"
	.db 0x00
	.db 0x00
	.db 0x00
	.ascii "RX: Single Sat"
	.db 0x00
	.db 0x00
	.db 0x00
	.ascii "RX: Unknown!!!"
	.db 0x00
	.db 0x00
	.db 0x00
	.ascii "RX: Horiz. (2D)"
	.db 0x00
	.db 0x00
	.ascii "RX: Full Pos(3D)"
	.db 0x00
	.ascii "RX: DGPS Refer"
	.db 0x00
	.db 0x00
	.db 0x00
	.ascii "RX: Clk Hold(2D)"
	.db 0x00
	.ascii "RX: Overdet Clk"
	.db 0x00
	.db 0x00
G$DiscMode$0$0 == .
_DiscMode:
	.ascii "MODE: Normal"
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x0C
	.ascii "MODE: Power-Up"
	.db 0x00
	.db 0x00
	.db 0x00
	.ascii "MODE: Auto Hldvr"
	.db 0x00
	.ascii "MODE: Man. Hldvr"
	.db 0x00
	.ascii "MODE: Recovery"
	.db 0x00
	.db 0x00
	.db 0x00
	.ascii "MODE: Unknown!!!"
	.db 0x00
	.ascii "MODE: Disabled"
	.db 0x00
	.db 0x00
	.db 0x00
G$GPSDecodeStatus$0$0 == .
_GPSDecodeStatus:
	.ascii "GPS: Doing Fixes"
	.db 0x00
	.ascii "GPS: No GPS Time"
	.db 0x00
	.ascii "GPS: Unknown!!!"
	.db 0x00
	.db 0x00
	.ascii "GPS: PDOP to HI"
	.db 0x00
	.db 0x00
	.ascii "GPS: Unknown!!!"
	.db 0x00
	.db 0x00
	.ascii "GPS: Unknown!!!"
	.db 0x00
	.db 0x00
	.ascii "GPS: Unknown!!!"
	.db 0x00
	.db 0x00
	.ascii "GPS: Unknown!!!"
	.db 0x00
	.db 0x00
	.ascii "GPS: No Use SATS"
	.db 0x00
	.ascii "GPS: Only 1 SAT"
	.db 0x00
	.db 0x00
	.ascii "GPS: Only 2 SATS"
	.db 0x00
	.ascii "GPS: Only 3 SATS"
	.db 0x00
	.ascii "GPS: SAT Unusabl"
	.db 0x00
	.ascii "GPS: Unknown!!!"
	.db 0x00
	.db 0x00
	.ascii "GPS: Unknown!!!"
	.db 0x00
	.db 0x00
	.ascii "GPS: Unknown!!!"
	.db 0x00
	.db 0x00
	.ascii "GPS: TRIAM Rejec"
	.db 0x00
G$DiscActivity$0$0 == .
_DiscActivity:
	.ascii "ACT: Phase Lock"
	.db 0x00
	.db 0x00
	.ascii "ACT: Osc Warmup"
	.db 0x00
	.db 0x00
	.ascii "ACT: Freq Lock"
	.db 0x00
	.db 0x00
	.db 0x00
	.ascii "ACT: Placing PPS"
	.db 0x00
	.ascii "ACT: Init. loop"
	.db 0x00
	.db 0x00
	.ascii "ACT: Compensate"
	.db 0x00
	.db 0x00
	.ascii "ACT: Inactive"
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x0C
	.ascii "ACT: Unknown!!!"
	.db 0x00
	.db 0x00
	.ascii "ACT: Recovery LP"
	.db 0x00
G$VersionMsg$0$0 == .
_VersionMsg:
	.ascii " TSIPMon v0.2.2 "
	.db 0x00
G$LCDInitMsg$0$0 == .
_LCDInitMsg:
	.ascii " www.ko4bb.com  "
	.db 0x00
G$prompt$0$0 == .
_prompt:
	.ascii "TEMP:  "
	.db 0x00
	.db 0x00
	.ascii "DAC V: "
	.db 0x00
	.db 0x00
FTSIPMon$_str_0$0$0 == .
__str_0:
	.ascii "Waiting for GPS"
	.db 0x00
FTSIPMon$_str_1$0$0 == .
__str_1:
	.ascii "   No Message   "
	.db 0x00
	.area XINIT   (CODE)
