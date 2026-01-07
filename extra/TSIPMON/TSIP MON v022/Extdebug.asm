;--------------------------------------------------------
; File Created by SDCC : FreeWare ANSI-C Compiler
; Version 2.6.0 #4309 (Jul 28 2006)
; This file generated Sun Dec 28 11:32:36 2008
;--------------------------------------------------------
	.module Extdebug
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _Fault_Msg_Query_PARM_3
	.globl _Fault_Msg_Query_PARM_2
	.globl _ALARM_MSG
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
	.globl _Fault_Msg_Query
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
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area	OSEG    (OVR,DATA)
LFault_Msg_Query$buf$1$1==.
_Fault_Msg_Query_PARM_2::
	.ds 2
LFault_Msg_Query$msg$1$1==.
_Fault_Msg_Query_PARM_3::
	.ds 2
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
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
FExtdebug$fault_query_ndx$0$0==.
_fault_query_ndx:
	.ds 1
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
;Allocation info for local variables in function 'Fault_Msg_Query'
;------------------------------------------------------------
;buf                       Allocated with name '_Fault_Msg_Query_PARM_2'
;msg                       Allocated with name '_Fault_Msg_Query_PARM_3'
;Test_Result               Allocated to registers r2 r3 
;i                         Allocated to registers r4 
;j                         Allocated to registers 
;------------------------------------------------------------
	G$Fault_Msg_Query$0$0 ==.
	C$Extdebug.c$100$0$0 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:100: bit Fault_Msg_Query( uint Test_Result, uchar TXRX_STORAGE_CLASS *buf,
;	-----------------------------------------
;	 function Fault_Msg_Query
;	-----------------------------------------
_Fault_Msg_Query:
	ar2 = 0x02
	ar3 = 0x03
	ar4 = 0x04
	ar5 = 0x05
	ar6 = 0x06
	ar7 = 0x07
	ar0 = 0x00
	ar1 = 0x01
;	genReceive
	mov	r2,dpl
	mov	r3,dph
	C$Extdebug.c$106$1$1 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:106: if( Test_Result == 0 )
;	genIfx
	mov	a,r2
	orl	a,r3
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
	C$Extdebug.c$107$1$1 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:107: return( FALSE );
;	genRet
;	Peephole 181	changed mov to clr
	jnz	00102$
;	Peephole 300	removed redundant label 00131$
;	Peephole 256.b	removed redundant clr a
	add	a,#0xff
;	Peephole 251.a	replaced ljmp to ret with ret
	ret
00102$:
	C$Extdebug.c$109$1$1 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:109: if( fault_query_ndx > 15 )
;	genAssign
	mov	dptr,#_fault_query_ndx
	movx	a,@dptr
;	genCmpGt
;	genCmp
;	genIfxJump
;	Peephole 108.a	removed ljmp by inverse jump logic
;	Peephole 132.b	optimized genCmpGt by inverse logic (acc differs)
	mov  r4,a
;	Peephole 177.a	removed redundant mov
	add	a,#0xff - 0x0F
	jnc	00125$
;	Peephole 300	removed redundant label 00132$
	C$Extdebug.c$110$1$1 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:110: fault_query_ndx = 0;
;	genAssign
	mov	dptr,#_fault_query_ndx
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
	C$Extdebug.c$111$1$1 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:111: while( !(Test_Result & j<<fault_query_ndx) ){
00125$:
;	genAssign
	mov	r4,#0x00
00108$:
;	genAssign
	mov	dptr,#_fault_query_ndx
	movx	a,@dptr
	mov	r5,a
;	genLeftShift
	mov	b,r5
	inc	b
	mov	r6,#0x01
	mov	r7,#0x00
	sjmp	00134$
00133$:
	mov	a,r6
;	Peephole 254	optimized left shift
	add	a,r6
	mov	r6,a
	mov	a,r7
	rlc	a
	mov	r7,a
00134$:
	djnz	b,00133$
;	genAnd
	mov	a,r2
	anl	ar6,a
	mov	a,r3
	anl	ar7,a
;	genIfx
	mov	a,r6
	orl	a,r7
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
	jnz	00110$
;	Peephole 300	removed redundant label 00135$
	C$Extdebug.c$112$2$2 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:112: fault_query_ndx++;
;	genPlus
	mov	dptr,#_fault_query_ndx
;     genPlusIncr
	mov	a,#0x01
;	Peephole 236.a	used r5 instead of ar5
	add	a,r5
	movx	@dptr,a
	C$Extdebug.c$113$2$2 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:113: if( fault_query_ndx >= NUM_MSG || i++ >= NUM_MSG ){
;	genAssign
	mov	dptr,#_fault_query_ndx
	movx	a,@dptr
	mov	r6,a
;	genCmpLt
;	genCmp
	cjne	r6,#0x10,00136$
00136$:
;	genIfxJump
;	Peephole 108.a	removed ljmp by inverse jump logic
	jnc	00105$
;	Peephole 300	removed redundant label 00137$
;	genAssign
	mov	ar6,r4
;	genPlus
;     genPlusIncr
	inc	r4
;	genCmpLt
;	genCmp
	cjne	r6,#0x10,00138$
00138$:
;	genIfxJump
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 160.a	removed sjmp by inverse jump logic
	jc	00108$
;	Peephole 300	removed redundant label 00139$
00105$:
	C$Extdebug.c$114$3$3 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:114: fault_query_ndx = 0;
;	genAssign
	mov	dptr,#_fault_query_ndx
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
	C$Extdebug.c$115$3$3 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:115: return( FALSE );
;	genRet
;	Peephole 181	changed mov to clr
	clr	a
	add	a,#0xff
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 251.b	replaced sjmp to ret with ret
	ret
00110$:
	C$Extdebug.c$120$1$1 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:120: if( *(msg+MSG_LEN*fault_query_ndx) == NULL_CHAR ){
;	genMult
;	genMultOneByte
	mov	a,r5
	mov	b,#0x11
	mul	ab
;	genPlus
	add	a,_Fault_Msg_Query_PARM_3
	mov	r2,a
	mov	a,(_Fault_Msg_Query_PARM_3 + 1)
	addc	a,b
	mov	r3,a
;	genPointerGet
;	genCodePointerGet
	mov	dpl,r2
	mov	dph,r3
	clr	a
	movc	a,@a+dptr
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
	jnz	00129$
;	Peephole 300	removed redundant label 00140$
	C$Extdebug.c$121$2$4 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:121: fault_query_ndx++;
;	genPlus
	mov	dptr,#_fault_query_ndx
;     genPlusIncr
	mov	a,#0x01
;	Peephole 236.a	used r5 instead of ar5
	add	a,r5
	movx	@dptr,a
	C$Extdebug.c$122$2$4 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:122: buf[0] = NULL_CHAR;
;	genAssign
	mov	dpl,_Fault_Msg_Query_PARM_2
	mov	dph,(_Fault_Msg_Query_PARM_2 + 1)
;	genPointerSet
;     genFarPointerSet
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
	C$Extdebug.c$123$2$4 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:123: return( FALSE );
;	genRet
;	Peephole 181	changed mov to clr
	clr	a
	add	a,#0xff
	C$Extdebug.c$126$1$1 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:126: for( i=0; i<MSG_LEN; i++ ){
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 251.b	replaced sjmp to ret with ret
	ret
00129$:
;	genAssign
	mov	r2,#0x00
00115$:
;	genCmpLt
;	genCmp
	cjne	r2,#0x11,00141$
00141$:
;	genIfxJump
;	Peephole 108.a	removed ljmp by inverse jump logic
	jnc	00118$
;	Peephole 300	removed redundant label 00142$
	C$Extdebug.c$127$2$5 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:127: buf[i] = *(msg+MSG_LEN*fault_query_ndx+i);
;	genPlus
;	Peephole 236.g	used r2 instead of ar2
	mov	a,r2
	add	a,_Fault_Msg_Query_PARM_2
	mov	r3,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,(_Fault_Msg_Query_PARM_2 + 1)
	mov	r4,a
;	genAssign
	mov	dptr,#_fault_query_ndx
	movx	a,@dptr
;	genMult
;	genMultOneByte
	mov	r5,a
;	Peephole 105	removed redundant mov
	mov	b,#0x11
	mul	ab
;	genPlus
	add	a,_Fault_Msg_Query_PARM_3
	mov	r5,a
;	Peephole 240	use clr instead of addc a,#0
	clr	a
	addc	a,(_Fault_Msg_Query_PARM_3 + 1)
	mov	r6,a
;	genPlus
;	Peephole 236.g	used r2 instead of ar2
	mov	a,r2
;	Peephole 236.a	used r5 instead of ar5
	add	a,r5
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
;	Peephole 236.b	used r6 instead of ar6
	addc	a,r6
	mov	dph,a
;	genPointerGet
;	genCodePointerGet
	clr	a
	movc	a,@a+dptr
;	genPointerSet
;     genFarPointerSet
	mov	r5,a
	mov	dpl,r3
	mov	dph,r4
;	Peephole 136	removed redundant move
	movx	@dptr,a
	C$Extdebug.c$128$2$5 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:128: if( buf[i] == NULL_CHAR )
;	genIfx
	mov	a,r5
;	genIfxJump
;	Peephole 108.c	removed ljmp by inverse jump logic
	jz	00118$
;	Peephole 300	removed redundant label 00143$
	C$Extdebug.c$126$1$1 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:126: for( i=0; i<MSG_LEN; i++ ){
;	genPlus
;     genPlusIncr
	inc	r2
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00115$
00118$:
	C$Extdebug.c$131$1$1 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:131: fault_query_ndx++;
;	genAssign
	mov	dptr,#_fault_query_ndx
	movx	a,@dptr
	mov	r2,a
;	genPlus
	mov	dptr,#_fault_query_ndx
;     genPlusIncr
	mov	a,#0x01
;	Peephole 236.a	used r2 instead of ar2
	add	a,r2
	movx	@dptr,a
	C$Extdebug.c$133$1$1 ==.
;	C:/SDCC/GPSMon/dev/Extdebug.c:133: return( TRUE );
;	genRet
	mov	a,#0x01
	add	a,#0xff
;	Peephole 300	removed redundant label 00119$
	C$Extdebug.c$134$1$1 ==.
	XG$Fault_Msg_Query$0$0 ==.
	ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
G$ALARM_MSG$0$0 == .
_ALARM_MSG:
	.ascii "ROM Checksum Err"
	.db 0x00
	.ascii "RAM Check Failed"
	.db 0x00
	.ascii "PowerSupply Fail"
	.db 0x00
	.ascii "FPGA Check Fail "
	.db 0x00
	.ascii "VCO at rail"
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x0C
	.ascii "VCO Near Rail"
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x0C
	.ascii "Antenna Open"
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x0C
	.ascii "Antenna Shorted"
	.db 0x00
	.db 0x00
	.ascii "Not Tracking Sat"
	.db 0x00
	.ascii "Not Disciplining"
	.db 0x00
	.ascii "Survey In Progrs"
	.db 0x00
	.ascii "No Stored Pos"
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x0C
	.ascii "Leap Sec Pending"
	.db 0x00
	.ascii "Test Mode"
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x0C
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.ascii "x"
	.db 0x01
	.ascii ">"
	.db 0x00
	.db 0x0C
	.db 0x00
	.db 0x02
	.db 0x00
	.db 0x8A
	.db 0x01
	.db 0x0C
	.db 0x01
	.db 0x01
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.area XINIT   (CODE)
FExtdebug$__xinit_fault_query_ndx$0$0 == .
__xinit__fault_query_ndx:
	.db #0x00
