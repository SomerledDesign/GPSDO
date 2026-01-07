                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.6.0 #4309 (Jul 28 2006)
                              4 ; This file generated Mon Apr 09 19:34:07 2012
                              5 ;--------------------------------------------------------
                              6 	.module TSIPMon
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _TimerStart_PARM_2
                             13 	.globl _prompt
                             14 	.globl _LCDInitMsg
                             15 	.globl _VersionMsg
                             16 	.globl _DiscActivity
                             17 	.globl _GPSDecodeStatus
                             18 	.globl _DiscMode
                             19 	.globl _RxMode
                             20 	.globl _DIM
                             21 	.globl _Month
                             22 	.globl _Timer_3_Overflow
                             23 	.globl _Comparator
                             24 	.globl _Programmable_Counter_Array
                             25 	.globl _ADC0_End_of_Conversion
                             26 	.globl _ADC0_Window_Comparator
                             27 	.globl _SMB0
                             28 	.globl _SPI0
                             29 	.globl _Timer_1_Overflow
                             30 	.globl _External_Interrupt_1
                             31 	.globl _External_Interrupt_0
                             32 	.globl _SioIntService
                             33 	.globl _Timer2_ISR
                             34 	.globl _main
                             35 	.globl _SPIF
                             36 	.globl _WCOL
                             37 	.globl _MODF
                             38 	.globl _RXOVRN
                             39 	.globl _NSSMD1
                             40 	.globl _NSSMD0
                             41 	.globl _TXBMT
                             42 	.globl _SPIEN
                             43 	.globl _AD0EN
                             44 	.globl _AD0TM
                             45 	.globl _AD0INT
                             46 	.globl _AD0BUSY
                             47 	.globl _AD0WINT
                             48 	.globl _AD0CM2
                             49 	.globl _AD0CM1
                             50 	.globl _AD0CM0
                             51 	.globl _CF
                             52 	.globl _CR
                             53 	.globl _CCF2
                             54 	.globl _CCF1
                             55 	.globl _CCF0
                             56 	.globl _CY
                             57 	.globl _AC
                             58 	.globl _F0
                             59 	.globl _RS1
                             60 	.globl _RS0
                             61 	.globl _OV
                             62 	.globl _F1
                             63 	.globl _PARITY
                             64 	.globl _TF2H
                             65 	.globl _TF2
                             66 	.globl _TF2L
                             67 	.globl _TF2LEN
                             68 	.globl _TF2CEN
                             69 	.globl _T2SPLIT
                             70 	.globl _TR2
                             71 	.globl _T2XCLK
                             72 	.globl _MASTER
                             73 	.globl _TXMODE
                             74 	.globl _STA
                             75 	.globl _STO
                             76 	.globl _ACKRQ
                             77 	.globl _ARBLOST
                             78 	.globl _ACK
                             79 	.globl _SI
                             80 	.globl _PSPI0
                             81 	.globl _PT2
                             82 	.globl _PS0
                             83 	.globl _PS
                             84 	.globl _PT1
                             85 	.globl _PX1
                             86 	.globl _PT0
                             87 	.globl _PX0
                             88 	.globl _EA
                             89 	.globl _ESPI0
                             90 	.globl _ET2
                             91 	.globl _ES0
                             92 	.globl _ES
                             93 	.globl _ET1
                             94 	.globl _EX1
                             95 	.globl _ET0
                             96 	.globl _EX0
                             97 	.globl _P2_7
                             98 	.globl _P2_6
                             99 	.globl _P2_5
                            100 	.globl _P2_4
                            101 	.globl _P2_3
                            102 	.globl _P2_2
                            103 	.globl _P2_1
                            104 	.globl _P2_0
                            105 	.globl _S0MODE
                            106 	.globl _SM0
                            107 	.globl _MCE0
                            108 	.globl _SM2
                            109 	.globl _REN0
                            110 	.globl _REN
                            111 	.globl _TB80
                            112 	.globl _TB8
                            113 	.globl _RB80
                            114 	.globl _RB8
                            115 	.globl _TI0
                            116 	.globl _TI
                            117 	.globl _RI0
                            118 	.globl _RI
                            119 	.globl _P1_7
                            120 	.globl _P1_6
                            121 	.globl _P1_5
                            122 	.globl _P1_4
                            123 	.globl _P1_3
                            124 	.globl _P1_2
                            125 	.globl _P1_1
                            126 	.globl _P1_0
                            127 	.globl _TF1
                            128 	.globl _TR1
                            129 	.globl _TF0
                            130 	.globl _TR0
                            131 	.globl _IE1
                            132 	.globl _IT1
                            133 	.globl _IE0
                            134 	.globl _IT0
                            135 	.globl _P0_7
                            136 	.globl _P0_6
                            137 	.globl _P0_5
                            138 	.globl _P0_4
                            139 	.globl _P0_3
                            140 	.globl _P0_2
                            141 	.globl _P0_1
                            142 	.globl _P0_0
                            143 	.globl _PCA0CP2
                            144 	.globl _PCA0CP1
                            145 	.globl _PCA0CP0
                            146 	.globl _PCA0
                            147 	.globl _ADC0LT
                            148 	.globl _ADC0GT
                            149 	.globl _ADC0
                            150 	.globl _IDA0
                            151 	.globl _TMR3RL
                            152 	.globl _TMR3
                            153 	.globl _TMR2RL
                            154 	.globl _RCAP2
                            155 	.globl _TMR2
                            156 	.globl _TMR1
                            157 	.globl _TMR0
                            158 	.globl _VDM0CN
                            159 	.globl _PCA0CPH0
                            160 	.globl _PCA0CPL0
                            161 	.globl _PCA0H
                            162 	.globl _PCA0L
                            163 	.globl _SPI0CN
                            164 	.globl _EIP1
                            165 	.globl _P1MDIN
                            166 	.globl _P1MODE
                            167 	.globl _P0MDIN
                            168 	.globl _P0MODE
                            169 	.globl _B
                            170 	.globl _RSTSRC
                            171 	.globl _PCA0CPH2
                            172 	.globl _PCA0CPL2
                            173 	.globl _PCA0CPH1
                            174 	.globl _PCA0CPL1
                            175 	.globl _ADC0CN
                            176 	.globl _EIE1
                            177 	.globl _INT01CF
                            178 	.globl _IT01CF
                            179 	.globl _OSCLCN
                            180 	.globl _XBR1
                            181 	.globl _XBR0
                            182 	.globl _ACC
                            183 	.globl _PCA0CPM2
                            184 	.globl _PCA0CPM1
                            185 	.globl _PCA0CPM0
                            186 	.globl _PCA0MD
                            187 	.globl _PCA0CN
                            188 	.globl _P1SKIP
                            189 	.globl _P0SKIP
                            190 	.globl _REF0CN
                            191 	.globl _PSW
                            192 	.globl _TMR2H
                            193 	.globl _TH2
                            194 	.globl _TMR2L
                            195 	.globl _TL2
                            196 	.globl _TMR2RLH
                            197 	.globl _RCAP2H
                            198 	.globl _TMR2RLL
                            199 	.globl _RCAP2L
                            200 	.globl _TMR2CN
                            201 	.globl _T2CON
                            202 	.globl _ADC0LTH
                            203 	.globl _ADC0LTL
                            204 	.globl _ADC0GTH
                            205 	.globl _ADC0GTL
                            206 	.globl _SMB0DAT
                            207 	.globl _SMB0CF
                            208 	.globl _SMB0CN
                            209 	.globl _ADC0H
                            210 	.globl _ADC0L
                            211 	.globl _ADC0CF
                            212 	.globl _AMX0P
                            213 	.globl _AMX0N
                            214 	.globl _IDA0CN
                            215 	.globl _IP
                            216 	.globl _FLKEY
                            217 	.globl _FLSCL
                            218 	.globl _OSCICL
                            219 	.globl _OSCICN
                            220 	.globl _OSCXCN
                            221 	.globl __XPAGE
                            222 	.globl _EMI0CN
                            223 	.globl _CLKSEL
                            224 	.globl _IE
                            225 	.globl _P2MDOUT
                            226 	.globl _P1MDOUT
                            227 	.globl _P0MDOUT
                            228 	.globl _SPI0DAT
                            229 	.globl _SPI0CKR
                            230 	.globl _SPI0CFG
                            231 	.globl _P2
                            232 	.globl _CPT0MX
                            233 	.globl _CPT0MD
                            234 	.globl _CPT0CN
                            235 	.globl _SBUF0
                            236 	.globl _SBUF
                            237 	.globl _SCON0
                            238 	.globl _SCON
                            239 	.globl _IDA0H
                            240 	.globl _IDA0L
                            241 	.globl _TMR3H
                            242 	.globl _TMR3L
                            243 	.globl _TMR3RLH
                            244 	.globl _TMR3RLL
                            245 	.globl _TMR3CN
                            246 	.globl _P1
                            247 	.globl _PSCTL
                            248 	.globl _CKCON
                            249 	.globl _TH1
                            250 	.globl _TH0
                            251 	.globl _TL1
                            252 	.globl _TL0
                            253 	.globl _TMOD
                            254 	.globl _TCON
                            255 	.globl _PCON
                            256 	.globl _DPH
                            257 	.globl _DPL
                            258 	.globl _SP
                            259 	.globl _P0
                            260 	.globl _TxRxBuf
                            261 	.globl _lcdbuf
                            262 	.globl _Alarms
                            263 	.globl _err1
                            264 	.globl _func1
                            265 	.globl _func2
                            266 	.globl _switch1
                            267 	.globl _switch2
                            268 	.globl _Tx_In_Progress
                            269 	.globl _Rx_Pending
                            270 	.globl _ticks
                            271 	.globl _gpsoffset
                            272 	.globl _tz
                            273 	.globl _Timer
                            274 	.globl _Port_Init
                            275 	.globl _Timer2_Init
                            276 	.globl _WaitTicks
                            277 	.globl _TimerStart
                            278 	.globl _TimerRunning
                            279 	.globl _TimerReset
                            280 	.globl _TimerReady
                            281 	.globl _UART0_Init
                            282 	.globl _ProcessRxMsg
                            283 	.globl _PrimaryTiming
                            284 	.globl _SupplementalTiming
                            285 	.globl _clr_LCDBuf
                            286 ;--------------------------------------------------------
                            287 ; special function registers
                            288 ;--------------------------------------------------------
                            289 	.area RSEG    (DATA)
                    0080    290 G$P0$0$0 == 0x0080
                    0080    291 _P0	=	0x0080
                    0081    292 G$SP$0$0 == 0x0081
                    0081    293 _SP	=	0x0081
                    0082    294 G$DPL$0$0 == 0x0082
                    0082    295 _DPL	=	0x0082
                    0083    296 G$DPH$0$0 == 0x0083
                    0083    297 _DPH	=	0x0083
                    0087    298 G$PCON$0$0 == 0x0087
                    0087    299 _PCON	=	0x0087
                    0088    300 G$TCON$0$0 == 0x0088
                    0088    301 _TCON	=	0x0088
                    0089    302 G$TMOD$0$0 == 0x0089
                    0089    303 _TMOD	=	0x0089
                    008A    304 G$TL0$0$0 == 0x008a
                    008A    305 _TL0	=	0x008a
                    008B    306 G$TL1$0$0 == 0x008b
                    008B    307 _TL1	=	0x008b
                    008C    308 G$TH0$0$0 == 0x008c
                    008C    309 _TH0	=	0x008c
                    008D    310 G$TH1$0$0 == 0x008d
                    008D    311 _TH1	=	0x008d
                    008E    312 G$CKCON$0$0 == 0x008e
                    008E    313 _CKCON	=	0x008e
                    008F    314 G$PSCTL$0$0 == 0x008f
                    008F    315 _PSCTL	=	0x008f
                    0090    316 G$P1$0$0 == 0x0090
                    0090    317 _P1	=	0x0090
                    0091    318 G$TMR3CN$0$0 == 0x0091
                    0091    319 _TMR3CN	=	0x0091
                    0092    320 G$TMR3RLL$0$0 == 0x0092
                    0092    321 _TMR3RLL	=	0x0092
                    0093    322 G$TMR3RLH$0$0 == 0x0093
                    0093    323 _TMR3RLH	=	0x0093
                    0094    324 G$TMR3L$0$0 == 0x0094
                    0094    325 _TMR3L	=	0x0094
                    0095    326 G$TMR3H$0$0 == 0x0095
                    0095    327 _TMR3H	=	0x0095
                    0096    328 G$IDA0L$0$0 == 0x0096
                    0096    329 _IDA0L	=	0x0096
                    0097    330 G$IDA0H$0$0 == 0x0097
                    0097    331 _IDA0H	=	0x0097
                    0098    332 G$SCON$0$0 == 0x0098
                    0098    333 _SCON	=	0x0098
                    0098    334 G$SCON0$0$0 == 0x0098
                    0098    335 _SCON0	=	0x0098
                    0099    336 G$SBUF$0$0 == 0x0099
                    0099    337 _SBUF	=	0x0099
                    0099    338 G$SBUF0$0$0 == 0x0099
                    0099    339 _SBUF0	=	0x0099
                    009B    340 G$CPT0CN$0$0 == 0x009b
                    009B    341 _CPT0CN	=	0x009b
                    009D    342 G$CPT0MD$0$0 == 0x009d
                    009D    343 _CPT0MD	=	0x009d
                    009F    344 G$CPT0MX$0$0 == 0x009f
                    009F    345 _CPT0MX	=	0x009f
                    00A0    346 G$P2$0$0 == 0x00a0
                    00A0    347 _P2	=	0x00a0
                    00A1    348 G$SPI0CFG$0$0 == 0x00a1
                    00A1    349 _SPI0CFG	=	0x00a1
                    00A2    350 G$SPI0CKR$0$0 == 0x00a2
                    00A2    351 _SPI0CKR	=	0x00a2
                    00A3    352 G$SPI0DAT$0$0 == 0x00a3
                    00A3    353 _SPI0DAT	=	0x00a3
                    00A4    354 G$P0MDOUT$0$0 == 0x00a4
                    00A4    355 _P0MDOUT	=	0x00a4
                    00A5    356 G$P1MDOUT$0$0 == 0x00a5
                    00A5    357 _P1MDOUT	=	0x00a5
                    00A6    358 G$P2MDOUT$0$0 == 0x00a6
                    00A6    359 _P2MDOUT	=	0x00a6
                    00A8    360 G$IE$0$0 == 0x00a8
                    00A8    361 _IE	=	0x00a8
                    00A9    362 G$CLKSEL$0$0 == 0x00a9
                    00A9    363 _CLKSEL	=	0x00a9
                    00AA    364 G$EMI0CN$0$0 == 0x00aa
                    00AA    365 _EMI0CN	=	0x00aa
                    00AA    366 G$_XPAGE$0$0 == 0x00aa
                    00AA    367 __XPAGE	=	0x00aa
                    00B1    368 G$OSCXCN$0$0 == 0x00b1
                    00B1    369 _OSCXCN	=	0x00b1
                    00B2    370 G$OSCICN$0$0 == 0x00b2
                    00B2    371 _OSCICN	=	0x00b2
                    00B3    372 G$OSCICL$0$0 == 0x00b3
                    00B3    373 _OSCICL	=	0x00b3
                    00B6    374 G$FLSCL$0$0 == 0x00b6
                    00B6    375 _FLSCL	=	0x00b6
                    00B7    376 G$FLKEY$0$0 == 0x00b7
                    00B7    377 _FLKEY	=	0x00b7
                    00B8    378 G$IP$0$0 == 0x00b8
                    00B8    379 _IP	=	0x00b8
                    00B9    380 G$IDA0CN$0$0 == 0x00b9
                    00B9    381 _IDA0CN	=	0x00b9
                    00BA    382 G$AMX0N$0$0 == 0x00ba
                    00BA    383 _AMX0N	=	0x00ba
                    00BB    384 G$AMX0P$0$0 == 0x00bb
                    00BB    385 _AMX0P	=	0x00bb
                    00BC    386 G$ADC0CF$0$0 == 0x00bc
                    00BC    387 _ADC0CF	=	0x00bc
                    00BD    388 G$ADC0L$0$0 == 0x00bd
                    00BD    389 _ADC0L	=	0x00bd
                    00BE    390 G$ADC0H$0$0 == 0x00be
                    00BE    391 _ADC0H	=	0x00be
                    00C0    392 G$SMB0CN$0$0 == 0x00c0
                    00C0    393 _SMB0CN	=	0x00c0
                    00C1    394 G$SMB0CF$0$0 == 0x00c1
                    00C1    395 _SMB0CF	=	0x00c1
                    00C2    396 G$SMB0DAT$0$0 == 0x00c2
                    00C2    397 _SMB0DAT	=	0x00c2
                    00C3    398 G$ADC0GTL$0$0 == 0x00c3
                    00C3    399 _ADC0GTL	=	0x00c3
                    00C4    400 G$ADC0GTH$0$0 == 0x00c4
                    00C4    401 _ADC0GTH	=	0x00c4
                    00C5    402 G$ADC0LTL$0$0 == 0x00c5
                    00C5    403 _ADC0LTL	=	0x00c5
                    00C6    404 G$ADC0LTH$0$0 == 0x00c6
                    00C6    405 _ADC0LTH	=	0x00c6
                    00C8    406 G$T2CON$0$0 == 0x00c8
                    00C8    407 _T2CON	=	0x00c8
                    00C8    408 G$TMR2CN$0$0 == 0x00c8
                    00C8    409 _TMR2CN	=	0x00c8
                    00CA    410 G$RCAP2L$0$0 == 0x00ca
                    00CA    411 _RCAP2L	=	0x00ca
                    00CA    412 G$TMR2RLL$0$0 == 0x00ca
                    00CA    413 _TMR2RLL	=	0x00ca
                    00CB    414 G$RCAP2H$0$0 == 0x00cb
                    00CB    415 _RCAP2H	=	0x00cb
                    00CB    416 G$TMR2RLH$0$0 == 0x00cb
                    00CB    417 _TMR2RLH	=	0x00cb
                    00CC    418 G$TL2$0$0 == 0x00cc
                    00CC    419 _TL2	=	0x00cc
                    00CC    420 G$TMR2L$0$0 == 0x00cc
                    00CC    421 _TMR2L	=	0x00cc
                    00CD    422 G$TH2$0$0 == 0x00cd
                    00CD    423 _TH2	=	0x00cd
                    00CD    424 G$TMR2H$0$0 == 0x00cd
                    00CD    425 _TMR2H	=	0x00cd
                    00D0    426 G$PSW$0$0 == 0x00d0
                    00D0    427 _PSW	=	0x00d0
                    00D1    428 G$REF0CN$0$0 == 0x00d1
                    00D1    429 _REF0CN	=	0x00d1
                    00D4    430 G$P0SKIP$0$0 == 0x00d4
                    00D4    431 _P0SKIP	=	0x00d4
                    00D5    432 G$P1SKIP$0$0 == 0x00d5
                    00D5    433 _P1SKIP	=	0x00d5
                    00D8    434 G$PCA0CN$0$0 == 0x00d8
                    00D8    435 _PCA0CN	=	0x00d8
                    00D9    436 G$PCA0MD$0$0 == 0x00d9
                    00D9    437 _PCA0MD	=	0x00d9
                    00DA    438 G$PCA0CPM0$0$0 == 0x00da
                    00DA    439 _PCA0CPM0	=	0x00da
                    00DB    440 G$PCA0CPM1$0$0 == 0x00db
                    00DB    441 _PCA0CPM1	=	0x00db
                    00DC    442 G$PCA0CPM2$0$0 == 0x00dc
                    00DC    443 _PCA0CPM2	=	0x00dc
                    00E0    444 G$ACC$0$0 == 0x00e0
                    00E0    445 _ACC	=	0x00e0
                    00E1    446 G$XBR0$0$0 == 0x00e1
                    00E1    447 _XBR0	=	0x00e1
                    00E2    448 G$XBR1$0$0 == 0x00e2
                    00E2    449 _XBR1	=	0x00e2
                    00E3    450 G$OSCLCN$0$0 == 0x00e3
                    00E3    451 _OSCLCN	=	0x00e3
                    00E4    452 G$IT01CF$0$0 == 0x00e4
                    00E4    453 _IT01CF	=	0x00e4
                    00E4    454 G$INT01CF$0$0 == 0x00e4
                    00E4    455 _INT01CF	=	0x00e4
                    00E6    456 G$EIE1$0$0 == 0x00e6
                    00E6    457 _EIE1	=	0x00e6
                    00E8    458 G$ADC0CN$0$0 == 0x00e8
                    00E8    459 _ADC0CN	=	0x00e8
                    00E9    460 G$PCA0CPL1$0$0 == 0x00e9
                    00E9    461 _PCA0CPL1	=	0x00e9
                    00EA    462 G$PCA0CPH1$0$0 == 0x00ea
                    00EA    463 _PCA0CPH1	=	0x00ea
                    00EB    464 G$PCA0CPL2$0$0 == 0x00eb
                    00EB    465 _PCA0CPL2	=	0x00eb
                    00EC    466 G$PCA0CPH2$0$0 == 0x00ec
                    00EC    467 _PCA0CPH2	=	0x00ec
                    00EF    468 G$RSTSRC$0$0 == 0x00ef
                    00EF    469 _RSTSRC	=	0x00ef
                    00F0    470 G$B$0$0 == 0x00f0
                    00F0    471 _B	=	0x00f0
                    00F1    472 G$P0MODE$0$0 == 0x00f1
                    00F1    473 _P0MODE	=	0x00f1
                    00F1    474 G$P0MDIN$0$0 == 0x00f1
                    00F1    475 _P0MDIN	=	0x00f1
                    00F2    476 G$P1MODE$0$0 == 0x00f2
                    00F2    477 _P1MODE	=	0x00f2
                    00F2    478 G$P1MDIN$0$0 == 0x00f2
                    00F2    479 _P1MDIN	=	0x00f2
                    00F6    480 G$EIP1$0$0 == 0x00f6
                    00F6    481 _EIP1	=	0x00f6
                    00F8    482 G$SPI0CN$0$0 == 0x00f8
                    00F8    483 _SPI0CN	=	0x00f8
                    00F9    484 G$PCA0L$0$0 == 0x00f9
                    00F9    485 _PCA0L	=	0x00f9
                    00FA    486 G$PCA0H$0$0 == 0x00fa
                    00FA    487 _PCA0H	=	0x00fa
                    00FB    488 G$PCA0CPL0$0$0 == 0x00fb
                    00FB    489 _PCA0CPL0	=	0x00fb
                    00FC    490 G$PCA0CPH0$0$0 == 0x00fc
                    00FC    491 _PCA0CPH0	=	0x00fc
                    00FF    492 G$VDM0CN$0$0 == 0x00ff
                    00FF    493 _VDM0CN	=	0x00ff
                    8C8A    494 G$TMR0$0$0 == 0x8c8a
                    8C8A    495 _TMR0	=	0x8c8a
                    8D8B    496 G$TMR1$0$0 == 0x8d8b
                    8D8B    497 _TMR1	=	0x8d8b
                    CDCC    498 G$TMR2$0$0 == 0xcdcc
                    CDCC    499 _TMR2	=	0xcdcc
                    CBCA    500 G$RCAP2$0$0 == 0xcbca
                    CBCA    501 _RCAP2	=	0xcbca
                    CBCA    502 G$TMR2RL$0$0 == 0xcbca
                    CBCA    503 _TMR2RL	=	0xcbca
                    9594    504 G$TMR3$0$0 == 0x9594
                    9594    505 _TMR3	=	0x9594
                    9392    506 G$TMR3RL$0$0 == 0x9392
                    9392    507 _TMR3RL	=	0x9392
                    9796    508 G$IDA0$0$0 == 0x9796
                    9796    509 _IDA0	=	0x9796
                    BEBD    510 G$ADC0$0$0 == 0xbebd
                    BEBD    511 _ADC0	=	0xbebd
                    C4C3    512 G$ADC0GT$0$0 == 0xc4c3
                    C4C3    513 _ADC0GT	=	0xc4c3
                    C6C5    514 G$ADC0LT$0$0 == 0xc6c5
                    C6C5    515 _ADC0LT	=	0xc6c5
                    FAF9    516 G$PCA0$0$0 == 0xfaf9
                    FAF9    517 _PCA0	=	0xfaf9
                    FCFB    518 G$PCA0CP0$0$0 == 0xfcfb
                    FCFB    519 _PCA0CP0	=	0xfcfb
                    EAE9    520 G$PCA0CP1$0$0 == 0xeae9
                    EAE9    521 _PCA0CP1	=	0xeae9
                    ECEB    522 G$PCA0CP2$0$0 == 0xeceb
                    ECEB    523 _PCA0CP2	=	0xeceb
                            524 ;--------------------------------------------------------
                            525 ; special function bits
                            526 ;--------------------------------------------------------
                            527 	.area RSEG    (DATA)
                    0080    528 G$P0_0$0$0 == 0x0080
                    0080    529 _P0_0	=	0x0080
                    0081    530 G$P0_1$0$0 == 0x0081
                    0081    531 _P0_1	=	0x0081
                    0082    532 G$P0_2$0$0 == 0x0082
                    0082    533 _P0_2	=	0x0082
                    0083    534 G$P0_3$0$0 == 0x0083
                    0083    535 _P0_3	=	0x0083
                    0084    536 G$P0_4$0$0 == 0x0084
                    0084    537 _P0_4	=	0x0084
                    0085    538 G$P0_5$0$0 == 0x0085
                    0085    539 _P0_5	=	0x0085
                    0086    540 G$P0_6$0$0 == 0x0086
                    0086    541 _P0_6	=	0x0086
                    0087    542 G$P0_7$0$0 == 0x0087
                    0087    543 _P0_7	=	0x0087
                    0088    544 G$IT0$0$0 == 0x0088
                    0088    545 _IT0	=	0x0088
                    0089    546 G$IE0$0$0 == 0x0089
                    0089    547 _IE0	=	0x0089
                    008A    548 G$IT1$0$0 == 0x008a
                    008A    549 _IT1	=	0x008a
                    008B    550 G$IE1$0$0 == 0x008b
                    008B    551 _IE1	=	0x008b
                    008C    552 G$TR0$0$0 == 0x008c
                    008C    553 _TR0	=	0x008c
                    008D    554 G$TF0$0$0 == 0x008d
                    008D    555 _TF0	=	0x008d
                    008E    556 G$TR1$0$0 == 0x008e
                    008E    557 _TR1	=	0x008e
                    008F    558 G$TF1$0$0 == 0x008f
                    008F    559 _TF1	=	0x008f
                    0090    560 G$P1_0$0$0 == 0x0090
                    0090    561 _P1_0	=	0x0090
                    0091    562 G$P1_1$0$0 == 0x0091
                    0091    563 _P1_1	=	0x0091
                    0092    564 G$P1_2$0$0 == 0x0092
                    0092    565 _P1_2	=	0x0092
                    0093    566 G$P1_3$0$0 == 0x0093
                    0093    567 _P1_3	=	0x0093
                    0094    568 G$P1_4$0$0 == 0x0094
                    0094    569 _P1_4	=	0x0094
                    0095    570 G$P1_5$0$0 == 0x0095
                    0095    571 _P1_5	=	0x0095
                    0096    572 G$P1_6$0$0 == 0x0096
                    0096    573 _P1_6	=	0x0096
                    0097    574 G$P1_7$0$0 == 0x0097
                    0097    575 _P1_7	=	0x0097
                    0098    576 G$RI$0$0 == 0x0098
                    0098    577 _RI	=	0x0098
                    0098    578 G$RI0$0$0 == 0x0098
                    0098    579 _RI0	=	0x0098
                    0099    580 G$TI$0$0 == 0x0099
                    0099    581 _TI	=	0x0099
                    0099    582 G$TI0$0$0 == 0x0099
                    0099    583 _TI0	=	0x0099
                    009A    584 G$RB8$0$0 == 0x009a
                    009A    585 _RB8	=	0x009a
                    009A    586 G$RB80$0$0 == 0x009a
                    009A    587 _RB80	=	0x009a
                    009B    588 G$TB8$0$0 == 0x009b
                    009B    589 _TB8	=	0x009b
                    009B    590 G$TB80$0$0 == 0x009b
                    009B    591 _TB80	=	0x009b
                    009C    592 G$REN$0$0 == 0x009c
                    009C    593 _REN	=	0x009c
                    009C    594 G$REN0$0$0 == 0x009c
                    009C    595 _REN0	=	0x009c
                    009D    596 G$SM2$0$0 == 0x009d
                    009D    597 _SM2	=	0x009d
                    009D    598 G$MCE0$0$0 == 0x009d
                    009D    599 _MCE0	=	0x009d
                    009F    600 G$SM0$0$0 == 0x009f
                    009F    601 _SM0	=	0x009f
                    009F    602 G$S0MODE$0$0 == 0x009f
                    009F    603 _S0MODE	=	0x009f
                    00A0    604 G$P2_0$0$0 == 0x00a0
                    00A0    605 _P2_0	=	0x00a0
                    00A1    606 G$P2_1$0$0 == 0x00a1
                    00A1    607 _P2_1	=	0x00a1
                    00A2    608 G$P2_2$0$0 == 0x00a2
                    00A2    609 _P2_2	=	0x00a2
                    00A3    610 G$P2_3$0$0 == 0x00a3
                    00A3    611 _P2_3	=	0x00a3
                    00A4    612 G$P2_4$0$0 == 0x00a4
                    00A4    613 _P2_4	=	0x00a4
                    00A5    614 G$P2_5$0$0 == 0x00a5
                    00A5    615 _P2_5	=	0x00a5
                    00A6    616 G$P2_6$0$0 == 0x00a6
                    00A6    617 _P2_6	=	0x00a6
                    00A7    618 G$P2_7$0$0 == 0x00a7
                    00A7    619 _P2_7	=	0x00a7
                    00A8    620 G$EX0$0$0 == 0x00a8
                    00A8    621 _EX0	=	0x00a8
                    00A9    622 G$ET0$0$0 == 0x00a9
                    00A9    623 _ET0	=	0x00a9
                    00AA    624 G$EX1$0$0 == 0x00aa
                    00AA    625 _EX1	=	0x00aa
                    00AB    626 G$ET1$0$0 == 0x00ab
                    00AB    627 _ET1	=	0x00ab
                    00AC    628 G$ES$0$0 == 0x00ac
                    00AC    629 _ES	=	0x00ac
                    00AC    630 G$ES0$0$0 == 0x00ac
                    00AC    631 _ES0	=	0x00ac
                    00AD    632 G$ET2$0$0 == 0x00ad
                    00AD    633 _ET2	=	0x00ad
                    00AE    634 G$ESPI0$0$0 == 0x00ae
                    00AE    635 _ESPI0	=	0x00ae
                    00AF    636 G$EA$0$0 == 0x00af
                    00AF    637 _EA	=	0x00af
                    00B8    638 G$PX0$0$0 == 0x00b8
                    00B8    639 _PX0	=	0x00b8
                    00B9    640 G$PT0$0$0 == 0x00b9
                    00B9    641 _PT0	=	0x00b9
                    00BA    642 G$PX1$0$0 == 0x00ba
                    00BA    643 _PX1	=	0x00ba
                    00BB    644 G$PT1$0$0 == 0x00bb
                    00BB    645 _PT1	=	0x00bb
                    00BC    646 G$PS$0$0 == 0x00bc
                    00BC    647 _PS	=	0x00bc
                    00BC    648 G$PS0$0$0 == 0x00bc
                    00BC    649 _PS0	=	0x00bc
                    00BD    650 G$PT2$0$0 == 0x00bd
                    00BD    651 _PT2	=	0x00bd
                    00BE    652 G$PSPI0$0$0 == 0x00be
                    00BE    653 _PSPI0	=	0x00be
                    00C0    654 G$SI$0$0 == 0x00c0
                    00C0    655 _SI	=	0x00c0
                    00C1    656 G$ACK$0$0 == 0x00c1
                    00C1    657 _ACK	=	0x00c1
                    00C2    658 G$ARBLOST$0$0 == 0x00c2
                    00C2    659 _ARBLOST	=	0x00c2
                    00C3    660 G$ACKRQ$0$0 == 0x00c3
                    00C3    661 _ACKRQ	=	0x00c3
                    00C4    662 G$STO$0$0 == 0x00c4
                    00C4    663 _STO	=	0x00c4
                    00C5    664 G$STA$0$0 == 0x00c5
                    00C5    665 _STA	=	0x00c5
                    00C6    666 G$TXMODE$0$0 == 0x00c6
                    00C6    667 _TXMODE	=	0x00c6
                    00C7    668 G$MASTER$0$0 == 0x00c7
                    00C7    669 _MASTER	=	0x00c7
                    00C8    670 G$T2XCLK$0$0 == 0x00c8
                    00C8    671 _T2XCLK	=	0x00c8
                    00CA    672 G$TR2$0$0 == 0x00ca
                    00CA    673 _TR2	=	0x00ca
                    00CB    674 G$T2SPLIT$0$0 == 0x00cb
                    00CB    675 _T2SPLIT	=	0x00cb
                    00CD    676 G$TF2CEN$0$0 == 0x00cd
                    00CD    677 _TF2CEN	=	0x00cd
                    00CD    678 G$TF2LEN$0$0 == 0x00cd
                    00CD    679 _TF2LEN	=	0x00cd
                    00CE    680 G$TF2L$0$0 == 0x00ce
                    00CE    681 _TF2L	=	0x00ce
                    00CF    682 G$TF2$0$0 == 0x00cf
                    00CF    683 _TF2	=	0x00cf
                    00CF    684 G$TF2H$0$0 == 0x00cf
                    00CF    685 _TF2H	=	0x00cf
                    00D0    686 G$PARITY$0$0 == 0x00d0
                    00D0    687 _PARITY	=	0x00d0
                    00D1    688 G$F1$0$0 == 0x00d1
                    00D1    689 _F1	=	0x00d1
                    00D2    690 G$OV$0$0 == 0x00d2
                    00D2    691 _OV	=	0x00d2
                    00D3    692 G$RS0$0$0 == 0x00d3
                    00D3    693 _RS0	=	0x00d3
                    00D4    694 G$RS1$0$0 == 0x00d4
                    00D4    695 _RS1	=	0x00d4
                    00D5    696 G$F0$0$0 == 0x00d5
                    00D5    697 _F0	=	0x00d5
                    00D6    698 G$AC$0$0 == 0x00d6
                    00D6    699 _AC	=	0x00d6
                    00D7    700 G$CY$0$0 == 0x00d7
                    00D7    701 _CY	=	0x00d7
                    00D8    702 G$CCF0$0$0 == 0x00d8
                    00D8    703 _CCF0	=	0x00d8
                    00D9    704 G$CCF1$0$0 == 0x00d9
                    00D9    705 _CCF1	=	0x00d9
                    00DA    706 G$CCF2$0$0 == 0x00da
                    00DA    707 _CCF2	=	0x00da
                    00DE    708 G$CR$0$0 == 0x00de
                    00DE    709 _CR	=	0x00de
                    00DF    710 G$CF$0$0 == 0x00df
                    00DF    711 _CF	=	0x00df
                    00E8    712 G$AD0CM0$0$0 == 0x00e8
                    00E8    713 _AD0CM0	=	0x00e8
                    00E9    714 G$AD0CM1$0$0 == 0x00e9
                    00E9    715 _AD0CM1	=	0x00e9
                    00EA    716 G$AD0CM2$0$0 == 0x00ea
                    00EA    717 _AD0CM2	=	0x00ea
                    00EB    718 G$AD0WINT$0$0 == 0x00eb
                    00EB    719 _AD0WINT	=	0x00eb
                    00EC    720 G$AD0BUSY$0$0 == 0x00ec
                    00EC    721 _AD0BUSY	=	0x00ec
                    00ED    722 G$AD0INT$0$0 == 0x00ed
                    00ED    723 _AD0INT	=	0x00ed
                    00EE    724 G$AD0TM$0$0 == 0x00ee
                    00EE    725 _AD0TM	=	0x00ee
                    00EF    726 G$AD0EN$0$0 == 0x00ef
                    00EF    727 _AD0EN	=	0x00ef
                    00F8    728 G$SPIEN$0$0 == 0x00f8
                    00F8    729 _SPIEN	=	0x00f8
                    00F9    730 G$TXBMT$0$0 == 0x00f9
                    00F9    731 _TXBMT	=	0x00f9
                    00FA    732 G$NSSMD0$0$0 == 0x00fa
                    00FA    733 _NSSMD0	=	0x00fa
                    00FB    734 G$NSSMD1$0$0 == 0x00fb
                    00FB    735 _NSSMD1	=	0x00fb
                    00FC    736 G$RXOVRN$0$0 == 0x00fc
                    00FC    737 _RXOVRN	=	0x00fc
                    00FD    738 G$MODF$0$0 == 0x00fd
                    00FD    739 _MODF	=	0x00fd
                    00FE    740 G$WCOL$0$0 == 0x00fe
                    00FE    741 _WCOL	=	0x00fe
                    00FF    742 G$SPIF$0$0 == 0x00ff
                    00FF    743 _SPIF	=	0x00ff
                            744 ;--------------------------------------------------------
                            745 ; overlayable register banks
                            746 ;--------------------------------------------------------
                            747 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     748 	.ds 8
                            749 	.area REG_BANK_2	(REL,OVR,DATA)
   0010                     750 	.ds 8
                            751 ;--------------------------------------------------------
                            752 ; internal ram data
                            753 ;--------------------------------------------------------
                            754 	.area DSEG    (DATA)
                    0000    755 G$Timer$0$0==.
   0022                     756 _Timer::
   0022                     757 	.ds 9
                    0009    758 FTSIPMon$TxRx_State$0$0==.
   002B                     759 _TxRx_State:
   002B                     760 	.ds 1
                    000A    761 FTSIPMon$TxRx_Count$0$0==.
   002C                     762 _TxRx_Count:
   002C                     763 	.ds 1
                    000B    764 G$tz$0$0==.
   002D                     765 _tz::
   002D                     766 	.ds 1
                    000C    767 G$gpsoffset$0$0==.
   002E                     768 _gpsoffset::
   002E                     769 	.ds 1
                    000D    770 G$ticks$0$0==.
   002F                     771 _ticks::
   002F                     772 	.ds 2
                    000F    773 FTSIPMon$p_TxRx_Buf$0$0==.
   0031                     774 _p_TxRx_Buf:
   0031                     775 	.ds 2
                    0011    776 LPrimaryTiming$sec$1$1==.
   0033                     777 _PrimaryTiming_sec_1_1:
   0033                     778 	.ds 1
                    0012    779 LPrimaryTiming$min$1$1==.
   0034                     780 _PrimaryTiming_min_1_1:
   0034                     781 	.ds 1
                    0013    782 LPrimaryTiming$dom$1$1==.
   0035                     783 _PrimaryTiming_dom_1_1:
   0035                     784 	.ds 1
                    0014    785 LPrimaryTiming$yr$1$1==.
   0036                     786 _PrimaryTiming_yr_1_1:
   0036                     787 	.ds 2
                    0016    788 LSupplementalTiming$mode$1$1==.
   0038                     789 _SupplementalTiming_mode_1_1:
   0038                     790 	.ds 1
                    0017    791 LSupplementalTiming$RxBuf$1$1==.
   0039                     792 _SupplementalTiming_RxBuf_1_1:
   0039                     793 	.ds 2
                    0019    794 LSupplementalTiming$temp$1$1==.
   003B                     795 _SupplementalTiming_temp_1_1:
   003B                     796 	.ds 4
                    001D    797 LSupplementalTiming$val$1$1==.
   003F                     798 _SupplementalTiming_val_1_1:
   003F                     799 	.ds 1
                    001E    800 LSupplementalTiming$fval$1$1==.
   0040                     801 _SupplementalTiming_fval_1_1:
   0040                     802 	.ds 2
                    0020    803 LSupplementalTiming$sloc1$1$0==.
   0042                     804 _SupplementalTiming_sloc1_1_0:
   0042                     805 	.ds 4
                            806 ;--------------------------------------------------------
                            807 ; overlayable items in internal ram 
                            808 ;--------------------------------------------------------
                            809 	.area	OSEG    (OVR,DATA)
                            810 	.area	OSEG    (OVR,DATA)
                            811 	.area	OSEG    (OVR,DATA)
                    0000    812 LTimerStart$num_ticks$1$1==.
   000E                     813 _TimerStart_PARM_2::
   000E                     814 	.ds 2
                            815 	.area	OSEG    (OVR,DATA)
                            816 	.area	OSEG    (OVR,DATA)
                            817 	.area	OSEG    (OVR,DATA)
                            818 	.area	OSEG    (OVR,DATA)
                            819 ;--------------------------------------------------------
                            820 ; Stack segment in internal ram 
                            821 ;--------------------------------------------------------
                            822 	.area	SSEG	(DATA)
   004C                     823 __start__stack:
   004C                     824 	.ds	1
                            825 
                            826 ;--------------------------------------------------------
                            827 ; indirectly addressable internal ram data
                            828 ;--------------------------------------------------------
                            829 	.area ISEG    (DATA)
                            830 ;--------------------------------------------------------
                            831 ; bit data
                            832 ;--------------------------------------------------------
                            833 	.area BSEG    (BIT)
                    0000    834 G$Rx_Pending$0$0==.
   0000                     835 _Rx_Pending::
   0000                     836 	.ds 1
                    0001    837 G$Tx_In_Progress$0$0==.
   0001                     838 _Tx_In_Progress::
   0001                     839 	.ds 1
                    0002    840 G$switch2$0$0==.
   0002                     841 _switch2::
   0002                     842 	.ds 1
                    0003    843 G$switch1$0$0==.
   0003                     844 _switch1::
   0003                     845 	.ds 1
                    0004    846 G$func2$0$0==.
   0004                     847 _func2::
   0004                     848 	.ds 1
                    0005    849 G$func1$0$0==.
   0005                     850 _func1::
   0005                     851 	.ds 1
                    0006    852 G$err1$0$0==.
   0006                     853 _err1::
   0006                     854 	.ds 1
                    0007    855 LSioIntService$bEvenDLE$1$1==.
   0007                     856 _SioIntService_bEvenDLE_1_1:
   0007                     857 	.ds 1
                    0008    858 LSupplementalTiming$b$1$1==.
   0008                     859 _SupplementalTiming_b_1_1:
   0008                     860 	.ds 1
                    0009    861 LSupplementalTiming$c$1$1==.
   0009                     862 _SupplementalTiming_c_1_1:
   0009                     863 	.ds 1
                            864 ;--------------------------------------------------------
                            865 ; paged external ram data
                            866 ;--------------------------------------------------------
                            867 	.area PSEG    (PAG,XDATA)
                            868 ;--------------------------------------------------------
                            869 ; external ram data
                            870 ;--------------------------------------------------------
                            871 	.area XSEG    (XDATA)
                    0000    872 G$Alarms$0$0==.
   0000                     873 _Alarms::
   0000                     874 	.ds 2
                    0002    875 G$lcdbuf$0$0==.
   0002                     876 _lcdbuf::
   0002                     877 	.ds 21
                    0017    878 G$TxRxBuf$0$0==.
   0017                     879 _TxRxBuf::
   0017                     880 	.ds 85
                    006C    881 LProcessRxMsg$pBuf$1$1==.
   006C                     882 _ProcessRxMsg_pBuf_1_1:
   006C                     883 	.ds 85
                            884 ;--------------------------------------------------------
                            885 ; external initialized ram data
                            886 ;--------------------------------------------------------
                            887 	.area XISEG   (XDATA)
                            888 	.area HOME    (CODE)
                            889 	.area GSINIT0 (CODE)
                            890 	.area GSINIT1 (CODE)
                            891 	.area GSINIT2 (CODE)
                            892 	.area GSINIT3 (CODE)
                            893 	.area GSINIT4 (CODE)
                            894 	.area GSINIT5 (CODE)
                            895 	.area GSINIT  (CODE)
                            896 	.area GSFINAL (CODE)
                            897 	.area CSEG    (CODE)
                            898 ;--------------------------------------------------------
                            899 ; interrupt vector 
                            900 ;--------------------------------------------------------
                            901 	.area HOME    (CODE)
   0000                     902 __interrupt_vect:
   0000 02 00 76            903 	ljmp	__sdcc_gsinit_startup
   0003 02 0B BC            904 	ljmp	_External_Interrupt_0
   0006                     905 	.ds	5
   000B 32                  906 	reti
   000C                     907 	.ds	7
   0013 02 0C 05            908 	ljmp	_External_Interrupt_1
   0016                     909 	.ds	5
   001B 02 0C 58            910 	ljmp	_Timer_1_Overflow
   001E                     911 	.ds	5
   0023 02 03 C6            912 	ljmp	_SioIntService
   0026                     913 	.ds	5
   002B 02 02 B7            914 	ljmp	_Timer2_ISR
   002E                     915 	.ds	5
   0033 02 0C 59            916 	ljmp	_SPI0
   0036                     917 	.ds	5
   003B 02 0C 5A            918 	ljmp	_SMB0
   003E                     919 	.ds	5
   0043 32                  920 	reti
   0044                     921 	.ds	7
   004B 02 0C 5B            922 	ljmp	_ADC0_Window_Comparator
   004E                     923 	.ds	5
   0053 02 0C 5C            924 	ljmp	_ADC0_End_of_Conversion
   0056                     925 	.ds	5
   005B 02 0C 5D            926 	ljmp	_Programmable_Counter_Array
   005E                     927 	.ds	5
   0063 02 0C 5E            928 	ljmp	_Comparator
   0066                     929 	.ds	5
   006B 32                  930 	reti
   006C                     931 	.ds	7
   0073 02 0C 5F            932 	ljmp	_Timer_3_Overflow
                            933 ;--------------------------------------------------------
                            934 ; global & static initialisations
                            935 ;--------------------------------------------------------
                            936 	.area HOME    (CODE)
                            937 	.area GSINIT  (CODE)
                            938 	.area GSFINAL (CODE)
                            939 	.area GSINIT  (CODE)
                            940 	.globl __sdcc_gsinit_startup
                            941 	.globl __sdcc_program_startup
                            942 	.globl __start__stack
                            943 	.globl __mcs51_genXINIT
                            944 	.globl __mcs51_genXRAMCLEAR
                            945 	.globl __mcs51_genRAMCLEAR
                            946 ;------------------------------------------------------------
                            947 ;Allocation info for local variables in function 'SupplementalTiming'
                            948 ;------------------------------------------------------------
                            949 ;mode                      Allocated with name '_SupplementalTiming_mode_1_1'
                            950 ;RxBuf                     Allocated with name '_SupplementalTiming_RxBuf_1_1'
                            951 ;temp                      Allocated with name '_SupplementalTiming_temp_1_1'
                            952 ;val                       Allocated with name '_SupplementalTiming_val_1_1'
                            953 ;fval                      Allocated with name '_SupplementalTiming_fval_1_1'
                            954 ;sloc0                     Allocated with name '_SupplementalTiming_sloc0_1_0'
                            955 ;sloc1                     Allocated with name '_SupplementalTiming_sloc1_1_0'
                            956 ;------------------------------------------------------------
                    0000    957 	G$SupplementalTiming$0$0 ==.
                    0000    958 	C$TSIPMon.c$896$2$1 ==.
                            959 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:896: static bit b = FALSE;
                            960 ;	genAssign
   00CF C2 08               961 	clr	_SupplementalTiming_b_1_1
                    0002    962 	C$TSIPMon.c$897$2$1 ==.
                            963 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:897: static bit c = FALSE;
                            964 ;	genAssign
   00D1 C2 09               965 	clr	_SupplementalTiming_c_1_1
                    0004    966 	C$TSIPMon.c$904$2$1 ==.
                            967 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:904: static char mode = -1;
                            968 ;	genAssign
   00D3 75 38 FF            969 	mov	_SupplementalTiming_mode_1_1,#0xFF
                    0007    970 	G$Timer_3_Overflow$0$0 ==.
                    0007    971 	C$TSIPMon.c$181$2$1 ==.
                            972 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:181: char tz = TIME_ZONE;	
                            973 ;	genAssign
   00D6 75 2D FA            974 	mov	_tz,#0xFA
                    000A    975 	G$Timer_3_Overflow$0$0 ==.
                    000A    976 	C$TSIPMon.c$216$2$1 ==.
                            977 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:216: uint ticks = 0;
                            978 ;	genAssign
   00D9 E4                  979 	clr	a
   00DA F5 2F               980 	mov	_ticks,a
   00DC F5 30               981 	mov	(_ticks + 1),a
                            982 	.area GSFINAL (CODE)
   00DE 02 00 E1            983 	ljmp	__sdcc_program_startup
                            984 ;--------------------------------------------------------
                            985 ; Home
                            986 ;--------------------------------------------------------
                            987 	.area HOME    (CODE)
                            988 	.area CSEG    (CODE)
   00E1                     989 __sdcc_program_startup:
   00E1 12 00 E6            990 	lcall	_main
                            991 ;	return from main will lock up
   00E4 80 FE               992 	sjmp .
                            993 ;--------------------------------------------------------
                            994 ; code
                            995 ;--------------------------------------------------------
                            996 	.area CSEG    (CODE)
                            997 ;------------------------------------------------------------
                            998 ;Allocation info for local variables in function 'main'
                            999 ;------------------------------------------------------------
                           1000 ;------------------------------------------------------------
                    0005   1001 	G$main$0$0 ==.
                    0005   1002 	C$TSIPMon.c$229$0$0 ==.
                           1003 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:229: void main( void ){
                           1004 ;	-----------------------------------------
                           1005 ;	 function main
                           1006 ;	-----------------------------------------
   00E6                    1007 _main:
                    0002   1008 	ar2 = 0x02
                    0003   1009 	ar3 = 0x03
                    0004   1010 	ar4 = 0x04
                    0005   1011 	ar5 = 0x05
                    0006   1012 	ar6 = 0x06
                    0007   1013 	ar7 = 0x07
                    0000   1014 	ar0 = 0x00
                    0001   1015 	ar1 = 0x01
                    0005   1016 	C$TSIPMon.c$231$1$1 ==.
                           1017 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:231: PCA0MD &= ~0x40;					// Clear watchdog timer enable
                           1018 ;	genAnd
   00E6 53 D9 BF           1019 	anl	_PCA0MD,#0xBF
                    0008   1020 	C$TSIPMon.c$233$1$1 ==.
                           1021 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:233: Timer2_Init();						// Initialize the Timer2
                           1022 ;	genCall
   00E9 12 02 82           1023 	lcall	_Timer2_Init
                    000B   1024 	C$TSIPMon.c$234$1$1 ==.
                           1025 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:234: Port_Init();						// Init Ports
                           1026 ;	genCall
   00EC 12 02 68           1027 	lcall	_Port_Init
                    000E   1028 	C$TSIPMon.c$235$1$1 ==.
                           1029 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:235: UART0_Init();
                           1030 ;	genCall
   00EF 12 03 A6           1031 	lcall	_UART0_Init
                    0011   1032 	C$TSIPMon.c$236$1$1 ==.
                           1033 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:236: EA = TRUE;							// Enable global interrupts
                           1034 ;	genAssign
   00F2 D2 AF              1035 	setb	_EA
                    0013   1036 	C$TSIPMon.c$237$1$1 ==.
                           1037 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:237: LED = 0;							// turn ON LED
                           1038 ;	genAssign
   00F4 C2 93              1039 	clr	_P1_3
                    0015   1040 	C$TSIPMon.c$239$1$1 ==.
                           1041 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:239: LED1 = 1;							// turn ON LED1
                           1042 ;	genAssign
   00F6 D2 83              1043 	setb	_P0_3
                    0017   1044 	C$TSIPMon.c$240$1$1 ==.
                           1045 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:240: TimerStart( SYS_TIMER, 500 );		// wait for display to wake up
                           1046 ;	genAssign
   00F8 75 0E F4           1047 	mov	_TimerStart_PARM_2,#0xF4
   00FB 75 0F 01           1048 	mov	(_TimerStart_PARM_2 + 1),#0x01
                           1049 ;	genCall
   00FE 75 82 00           1050 	mov	dpl,#0x00
   0101 12 03 39           1051 	lcall	_TimerStart
                    0023   1052 	C$TSIPMon.c$241$1$1 ==.
                           1053 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:241: while( !TimerReady( SYS_TIMER ))
   0104                    1054 00101$:
                           1055 ;	genCall
   0104 75 82 00           1056 	mov	dpl,#0x00
   0107 12 03 8E           1057 	lcall	_TimerReady
                           1058 ;	genIfx
                           1059 ;	genIfxJump
                           1060 ;	Peephole 108.c	removed ljmp by inverse jump logic
                           1061 ;	Peephole 128	jump optimization
   010A 50 F8              1062 	jnc	00101$
                           1063 ;	Peephole 300	removed redundant label 00143$
                    002B   1064 	C$TSIPMon.c$243$1$1 ==.
                           1065 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:243: InitLCD();							// Init LCD Controller
                           1066 ;	genCall
   010C 12 0C 60           1067 	lcall	_InitLCD
                    002E   1068 	C$TSIPMon.c$244$1$1 ==.
                           1069 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:244: ClearLCD( 3 );						// Clear display
                           1070 ;	genCall
   010F 75 82 03           1071 	mov	dpl,#0x03
   0112 12 0C A8           1072 	lcall	_ClearLCD
                    0034   1073 	C$TSIPMon.c$245$1$1 ==.
                           1074 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:245: printCode2LCD( 1, VersionMsg, 0 );
                           1075 ;	genAddrOf
   0115 75 0B BA           1076 	mov	_printCode2LCD_PARM_2,#_VersionMsg
   0118 75 0C 17           1077 	mov	(_printCode2LCD_PARM_2 + 1),#(_VersionMsg >> 8)
                           1078 ;	genAssign
   011B 75 0D 00           1079 	mov	_printCode2LCD_PARM_3,#0x00
                           1080 ;	genCall
   011E 75 82 01           1081 	mov	dpl,#0x01
   0121 12 0D 6A           1082 	lcall	_printCode2LCD
                    0043   1083 	C$TSIPMon.c$246$1$1 ==.
                           1084 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:246: printCode2LCD( 2, LCDInitMsg, 0 );
                           1085 ;	genAddrOf
   0124 75 0B CF           1086 	mov	_printCode2LCD_PARM_2,#_LCDInitMsg
   0127 75 0C 17           1087 	mov	(_printCode2LCD_PARM_2 + 1),#(_LCDInitMsg >> 8)
                           1088 ;	genAssign
   012A 75 0D 00           1089 	mov	_printCode2LCD_PARM_3,#0x00
                           1090 ;	genCall
   012D 75 82 02           1091 	mov	dpl,#0x02
   0130 12 0D 6A           1092 	lcall	_printCode2LCD
                    0052   1093 	C$TSIPMon.c$248$1$1 ==.
                           1094 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:248: TimerStart( SYS_TIMER, 1500 );
                           1095 ;	genAssign
   0133 75 0E DC           1096 	mov	_TimerStart_PARM_2,#0xDC
   0136 75 0F 05           1097 	mov	(_TimerStart_PARM_2 + 1),#0x05
                           1098 ;	genCall
   0139 75 82 00           1099 	mov	dpl,#0x00
   013C 12 03 39           1100 	lcall	_TimerStart
                    005E   1101 	C$TSIPMon.c$249$1$1 ==.
                           1102 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:249: while( !TimerReady( SYS_TIMER ))
   013F                    1103 00104$:
                           1104 ;	genCall
   013F 75 82 00           1105 	mov	dpl,#0x00
   0142 12 03 8E           1106 	lcall	_TimerReady
                           1107 ;	genIfx
                           1108 ;	genIfxJump
                           1109 ;	Peephole 108.c	removed ljmp by inverse jump logic
                           1110 ;	Peephole 128	jump optimization
   0145 50 F8              1111 	jnc	00104$
                           1112 ;	Peephole 300	removed redundant label 00144$
                    0066   1113 	C$TSIPMon.c$251$1$1 ==.
                           1114 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:251: ClearLCD( 3 );
                           1115 ;	genCall
   0147 75 82 03           1116 	mov	dpl,#0x03
   014A 12 0C A8           1117 	lcall	_ClearLCD
                           1118 ;	genIfx
                           1119 ;	genIfxJump
                           1120 ;	Peephole 112.b	changed ljmp to sjmp
                           1121 ;	Peephole 160.f	removed sjmp by inverse jump logic
   014D 30 86 73           1122 	jnb	_P0_6,00111$
                           1123 ;	Peephole 300	removed redundant label 00145$
                    006F   1124 	C$TSIPMon.c$254$2$2 ==.
                           1125 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:254: strcpy( lcdbuf, "Time Zone : " );
                           1126 ;	genCast
   0150 75 46 F6           1127 	mov	_strcpy_PARM_2,#__str_0
   0153 75 47 17           1128 	mov	(_strcpy_PARM_2 + 1),#(__str_0 >> 8)
   0156 75 48 80           1129 	mov	(_strcpy_PARM_2 + 2),#0x80
                           1130 ;	genCall
                           1131 ;	Peephole 182.a	used 16 bit load of DPTR
   0159 90 00 02           1132 	mov	dptr,#_lcdbuf
   015C 75 F0 00           1133 	mov	b,#0x00
   015F 12 11 96           1134 	lcall	_strcpy
                    0081   1135 	C$TSIPMon.c$255$2$2 ==.
                           1136 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:255: CharToAscii( tz, lcdbuf+12, 3 );
                           1137 ;	genPlus
                           1138 ;     genPlusIncr
   0162 74 0C              1139 	mov	a,#0x0C
   0164 24 02              1140 	add	a,#_lcdbuf
   0166 F5 46              1141 	mov	_CharToAscii_PARM_2,a
                           1142 ;	Peephole 181	changed mov to clr
   0168 E4                 1143 	clr	a
   0169 34 00              1144 	addc	a,#(_lcdbuf >> 8)
   016B F5 47              1145 	mov	(_CharToAscii_PARM_2 + 1),a
                           1146 ;	genAssign
   016D 75 48 03           1147 	mov	_CharToAscii_PARM_3,#0x03
                           1148 ;	genCall
   0170 85 2D 82           1149 	mov	dpl,_tz
   0173 12 0F B4           1150 	lcall	_CharToAscii
                    0095   1151 	C$TSIPMon.c$256$2$2 ==.
                           1152 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:256: printLCD( 1, lcdbuf, 0 );
                           1153 ;	genAddrOf
   0176 75 08 02           1154 	mov	_printLCD_PARM_2,#_lcdbuf
   0179 75 09 00           1155 	mov	(_printLCD_PARM_2 + 1),#(_lcdbuf >> 8)
                           1156 ;	genAssign
   017C 75 0A 00           1157 	mov	_printLCD_PARM_3,#0x00
                           1158 ;	genCall
   017F 75 82 01           1159 	mov	dpl,#0x01
   0182 12 0D 14           1160 	lcall	_printLCD
                    00A4   1161 	C$TSIPMon.c$257$2$2 ==.
                           1162 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:257: strcpy( lcdbuf, "GPS offset: Auto" );
                           1163 ;	genCast
   0185 75 46 03           1164 	mov	_strcpy_PARM_2,#__str_1
   0188 75 47 18           1165 	mov	(_strcpy_PARM_2 + 1),#(__str_1 >> 8)
   018B 75 48 80           1166 	mov	(_strcpy_PARM_2 + 2),#0x80
                           1167 ;	genCall
                           1168 ;	Peephole 182.a	used 16 bit load of DPTR
   018E 90 00 02           1169 	mov	dptr,#_lcdbuf
   0191 75 F0 00           1170 	mov	b,#0x00
   0194 12 11 96           1171 	lcall	_strcpy
                    00B6   1172 	C$TSIPMon.c$259$2$2 ==.
                           1173 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:259: printLCD( 2, lcdbuf, 0 );
                           1174 ;	genAddrOf
   0197 75 08 02           1175 	mov	_printLCD_PARM_2,#_lcdbuf
   019A 75 09 00           1176 	mov	(_printLCD_PARM_2 + 1),#(_lcdbuf >> 8)
                           1177 ;	genAssign
   019D 75 0A 00           1178 	mov	_printLCD_PARM_3,#0x00
                           1179 ;	genCall
   01A0 75 82 02           1180 	mov	dpl,#0x02
   01A3 12 0D 14           1181 	lcall	_printLCD
                    00C5   1182 	C$TSIPMon.c$260$2$2 ==.
                           1183 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:260: TimerStart( SYS_TIMER, 1500 );
                           1184 ;	genAssign
   01A6 75 0E DC           1185 	mov	_TimerStart_PARM_2,#0xDC
   01A9 75 0F 05           1186 	mov	(_TimerStart_PARM_2 + 1),#0x05
                           1187 ;	genCall
   01AC 75 82 00           1188 	mov	dpl,#0x00
   01AF 12 03 39           1189 	lcall	_TimerStart
                    00D1   1190 	C$TSIPMon.c$261$2$2 ==.
                           1191 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:261: while( !TimerReady( SYS_TIMER ))
   01B2                    1192 00107$:
                           1193 ;	genCall
   01B2 75 82 00           1194 	mov	dpl,#0x00
   01B5 12 03 8E           1195 	lcall	_TimerReady
                           1196 ;	genIfx
                           1197 ;	genIfxJump
                           1198 ;	Peephole 108.c	removed ljmp by inverse jump logic
                           1199 ;	Peephole 128	jump optimization
   01B8 50 F8              1200 	jnc	00107$
                           1201 ;	Peephole 300	removed redundant label 00146$
                    00D9   1202 	C$TSIPMon.c$263$2$2 ==.
                           1203 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:263: ClearLCD( 3 );
                           1204 ;	genCall
   01BA 75 82 03           1205 	mov	dpl,#0x03
   01BD 12 0C A8           1206 	lcall	_ClearLCD
                    00DF   1207 	C$TSIPMon.c$267$2$2 ==.
                           1208 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:267: clr_LCDBuf();
                           1209 ;	genCall
   01C0 12 0B 98           1210 	lcall	_clr_LCDBuf
   01C3                    1211 00111$:
                    00E2   1212 	C$TSIPMon.c$272$1$1 ==.
                           1213 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:272: LED1 = 0;							// turn OFF LED1
                           1214 ;	genAssign
   01C3 C2 83              1215 	clr	_P0_3
                    00E4   1216 	C$TSIPMon.c$273$1$1 ==.
                           1217 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:273: func2 = FALSE;
                           1218 ;	genAssign
   01C5 C2 04              1219 	clr	_func2
                    00E6   1220 	C$TSIPMon.c$274$1$1 ==.
                           1221 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:274: func1 = FALSE;
                           1222 ;	genAssign
   01C7 C2 05              1223 	clr	_func1
                    00E8   1224 	C$TSIPMon.c$275$1$1 ==.
                           1225 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:275: err1 = FALSE;
                           1226 ;	genAssign
   01C9 C2 06              1227 	clr	_err1
                    00EA   1228 	C$TSIPMon.c$277$1$1 ==.
                           1229 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:277: printCode2LCD( 1, "Waiting for GPS", 0 );
                           1230 ;	genAddrOf
   01CB 75 0B 14           1231 	mov	_printCode2LCD_PARM_2,#__str_2
   01CE 75 0C 18           1232 	mov	(_printCode2LCD_PARM_2 + 1),#(__str_2 >> 8)
                           1233 ;	genAssign
   01D1 75 0D 00           1234 	mov	_printCode2LCD_PARM_3,#0x00
                           1235 ;	genCall
   01D4 75 82 01           1236 	mov	dpl,#0x01
   01D7 12 0D 6A           1237 	lcall	_printCode2LCD
                    00F9   1238 	C$TSIPMon.c$278$1$1 ==.
                           1239 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:278: TimerStart( SYS_TIMER, 1500 );
                           1240 ;	genAssign
   01DA 75 0E DC           1241 	mov	_TimerStart_PARM_2,#0xDC
   01DD 75 0F 05           1242 	mov	(_TimerStart_PARM_2 + 1),#0x05
                           1243 ;	genCall
   01E0 75 82 00           1244 	mov	dpl,#0x00
   01E3 12 03 39           1245 	lcall	_TimerStart
                    0105   1246 	C$TSIPMon.c$279$1$1 ==.
                           1247 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:279: while( !TimerReady( SYS_TIMER ))
   01E6                    1248 00112$:
                           1249 ;	genCall
   01E6 75 82 00           1250 	mov	dpl,#0x00
   01E9 12 03 8E           1251 	lcall	_TimerReady
                           1252 ;	genIfx
                           1253 ;	genIfxJump
                           1254 ;	Peephole 108.c	removed ljmp by inverse jump logic
                           1255 ;	Peephole 128	jump optimization
   01EC 50 F8              1256 	jnc	00112$
                           1257 ;	Peephole 300	removed redundant label 00147$
                    010D   1258 	C$TSIPMon.c$281$1$1 ==.
                           1259 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:281: LED = 1;							// turn OFF LED
                           1260 ;	genAssign
   01EE D2 93              1261 	setb	_P1_3
                    010F   1262 	C$TSIPMon.c$282$1$1 ==.
                           1263 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:282: TimerStart( SWITCH_TIMER, 50 );		// switch timer
                           1264 ;	genAssign
   01F0 75 0E 32           1265 	mov	_TimerStart_PARM_2,#0x32
   01F3 E4                 1266 	clr	a
   01F4 F5 0F              1267 	mov	(_TimerStart_PARM_2 + 1),a
                           1268 ;	genCall
   01F6 75 82 02           1269 	mov	dpl,#0x02
   01F9 12 03 39           1270 	lcall	_TimerStart
                    011B   1271 	C$TSIPMon.c$284$1$1 ==.
                           1272 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:284: while( 1 ){							// Loop forever
   01FC                    1273 00125$:
                    011B   1274 	C$TSIPMon.c$285$2$3 ==.
                           1275 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:285: if( Rx_Pending ){
                           1276 ;	genIfx
                           1277 ;	genIfxJump
                           1278 ;	Peephole 108.d	removed ljmp by inverse jump logic
   01FC 30 00 17           1279 	jnb	_Rx_Pending,00116$
                           1280 ;	Peephole 300	removed redundant label 00148$
                    011E   1281 	C$TSIPMon.c$286$3$4 ==.
                           1282 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:286: TimerReset( SYS_TIMER );
                           1283 ;	genCall
   01FF 75 82 00           1284 	mov	dpl,#0x00
   0202 12 03 71           1285 	lcall	_TimerReset
                    0124   1286 	C$TSIPMon.c$287$3$4 ==.
                           1287 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:287: ProcessRxMsg();
                           1288 ;	genCall
   0205 12 05 5D           1289 	lcall	_ProcessRxMsg
                    0127   1290 	C$TSIPMon.c$288$3$4 ==.
                           1291 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:288: TimerStart( SYS_TIMER, 1200 );
                           1292 ;	genAssign
   0208 75 0E B0           1293 	mov	_TimerStart_PARM_2,#0xB0
   020B 75 0F 04           1294 	mov	(_TimerStart_PARM_2 + 1),#0x04
                           1295 ;	genCall
   020E 75 82 00           1296 	mov	dpl,#0x00
   0211 12 03 39           1297 	lcall	_TimerStart
                    0133   1298 	C$TSIPMon.c$289$3$4 ==.
                           1299 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:289: err1 = FALSE;
                           1300 ;	genAssign
   0214 C2 06              1301 	clr	_err1
   0216                    1302 00116$:
                    0135   1303 	C$TSIPMon.c$291$2$3 ==.
                           1304 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:291: if( TimerReady( SYS_TIMER )){
                           1305 ;	genCall
   0216 75 82 00           1306 	mov	dpl,#0x00
   0219 12 03 8E           1307 	lcall	_TimerReady
                           1308 ;	genIfx
                           1309 ;	genIfxJump
                           1310 ;	Peephole 108.c	removed ljmp by inverse jump logic
                           1311 ;	Peephole 128	jump optimization
   021C 50 36              1312 	jnc	00121$
                           1313 ;	Peephole 300	removed redundant label 00149$
                    013D   1314 	C$TSIPMon.c$292$3$5 ==.
                           1315 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:292: if( !err1 ){
                           1316 ;	genIfx
                           1317 ;	genIfxJump
                           1318 ;	Peephole 108.e	removed ljmp by inverse jump logic
   021E 20 06 1F           1319 	jb	_err1,00118$
                           1320 ;	Peephole 300	removed redundant label 00150$
                    0140   1321 	C$TSIPMon.c$293$4$6 ==.
                           1322 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:293: TimerStart( SYS_TIMER, 1200 );
                           1323 ;	genAssign
   0221 75 0E B0           1324 	mov	_TimerStart_PARM_2,#0xB0
   0224 75 0F 04           1325 	mov	(_TimerStart_PARM_2 + 1),#0x04
                           1326 ;	genCall
   0227 75 82 00           1327 	mov	dpl,#0x00
   022A 12 03 39           1328 	lcall	_TimerStart
                    014C   1329 	C$TSIPMon.c$294$4$6 ==.
                           1330 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:294: printCode2LCD( 1, "   No Message   ", 0 );
                           1331 ;	genAddrOf
   022D 75 0B 24           1332 	mov	_printCode2LCD_PARM_2,#__str_3
   0230 75 0C 18           1333 	mov	(_printCode2LCD_PARM_2 + 1),#(__str_3 >> 8)
                           1334 ;	genAssign
   0233 75 0D 00           1335 	mov	_printCode2LCD_PARM_3,#0x00
                           1336 ;	genCall
   0236 75 82 01           1337 	mov	dpl,#0x01
   0239 12 0D 6A           1338 	lcall	_printCode2LCD
                    015B   1339 	C$TSIPMon.c$296$4$6 ==.
                           1340 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:296: err1 = TRUE;
                           1341 ;	genAssign
   023C D2 06              1342 	setb	_err1
                           1343 ;	Peephole 112.b	changed ljmp to sjmp
   023E 80 14              1344 	sjmp	00121$
   0240                    1345 00118$:
                    015F   1346 	C$TSIPMon.c$298$4$7 ==.
                           1347 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:298: TimerStart( SYS_TIMER, 500 );
                           1348 ;	genAssign
   0240 75 0E F4           1349 	mov	_TimerStart_PARM_2,#0xF4
   0243 75 0F 01           1350 	mov	(_TimerStart_PARM_2 + 1),#0x01
                           1351 ;	genCall
   0246 75 82 00           1352 	mov	dpl,#0x00
   0249 12 03 39           1353 	lcall	_TimerStart
                    016B   1354 	C$TSIPMon.c$299$4$7 ==.
                           1355 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:299: ClearLCD( 3 );
                           1356 ;	genCall
   024C 75 82 03           1357 	mov	dpl,#0x03
   024F 12 0C A8           1358 	lcall	_ClearLCD
                    0171   1359 	C$TSIPMon.c$300$4$7 ==.
                           1360 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:300: err1 = FALSE;
                           1361 ;	genAssign
   0252 C2 06              1362 	clr	_err1
   0254                    1363 00121$:
                    0173   1364 	C$TSIPMon.c$304$2$3 ==.
                           1365 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:304: if( TimerReady( SWITCH_TIMER )){
                           1366 ;	genCall
   0254 75 82 02           1367 	mov	dpl,#0x02
   0257 12 03 8E           1368 	lcall	_TimerReady
                           1369 ;	genIfx
                           1370 ;	genIfxJump
                           1371 ;	Peephole 108.c	removed ljmp by inverse jump logic
                           1372 ;	Peephole 128	jump optimization
   025A 50 A0              1373 	jnc	00125$
                           1374 ;	Peephole 300	removed redundant label 00151$
                    017B   1375 	C$TSIPMon.c$305$3$8 ==.
                           1376 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:305: switch1 = 1;
                           1377 ;	genAssign
   025C D2 03              1378 	setb	_switch1
                    017D   1379 	C$TSIPMon.c$306$3$8 ==.
                           1380 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:306: switch2 = 1;
                           1381 ;	genAssign
   025E D2 02              1382 	setb	_switch2
                    017F   1383 	C$TSIPMon.c$307$3$8 ==.
                           1384 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:307: TimerReset( SWITCH_TIMER );
                           1385 ;	genCall
   0260 75 82 02           1386 	mov	dpl,#0x02
   0263 12 03 71           1387 	lcall	_TimerReset
                           1388 ;	Peephole 112.b	changed ljmp to sjmp
                    0185   1389 	C$TSIPMon.c$311$1$1 ==.
                    0185   1390 	XG$main$0$0 ==.
   0266 80 94              1391 	sjmp	00125$
                           1392 ;	Peephole 259.a	removed redundant label 00127$ and ret
                           1393 ;
                           1394 ;------------------------------------------------------------
                           1395 ;Allocation info for local variables in function 'Port_Init'
                           1396 ;------------------------------------------------------------
                           1397 ;------------------------------------------------------------
                    0187   1398 	G$Port_Init$0$0 ==.
                    0187   1399 	C$TSIPMon.c$341$1$1 ==.
                           1400 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:341: void Port_Init( void ){
                           1401 ;	-----------------------------------------
                           1402 ;	 function Port_Init
                           1403 ;	-----------------------------------------
   0268                    1404 _Port_Init:
                    0187   1405 	C$TSIPMon.c$343$1$1 ==.
                           1406 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:343: P0SKIP    = 0x01;					// P0.0 -> Vref
                           1407 ;	genAssign
   0268 75 D4 01           1408 	mov	_P0SKIP,#0x01
                    018A   1409 	C$TSIPMon.c$345$1$1 ==.
                           1410 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:345: P0MDOUT = 0x18;						// Tx, LED1 are push-pull
                           1411 ;	genAssign
   026B 75 A4 18           1412 	mov	_P0MDOUT,#0x18
                    018D   1413 	C$TSIPMon.c$346$1$1 ==.
                           1414 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:346: XBR0 = 0x01;						// enable UART
                           1415 ;	genAssign
   026E 75 E1 01           1416 	mov	_XBR0,#0x01
                    0190   1417 	C$TSIPMon.c$347$1$1 ==.
                           1418 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:347: XBR1 = 0x40;                        // Enable crossbar
                           1419 ;	genAssign
   0271 75 E2 40           1420 	mov	_XBR1,#0x40
                    0193   1421 	C$TSIPMon.c$349$1$1 ==.
                           1422 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:349: P1MDOUT = 0x7F;						// make LCD_PORT push-pull (except busy flag) v021
                           1423 ;	genAssign
   0274 75 A5 7F           1424 	mov	_P1MDOUT,#0x7F
                    0196   1425 	C$TSIPMon.c$352$1$1 ==.
                           1426 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:352: IE        |= 0x05;		// enable /INT0 and /INT1
                           1427 ;	genOr
   0277 43 A8 05           1428 	orl	_IE,#0x05
                    0199   1429 	C$TSIPMon.c$353$1$1 ==.
                           1430 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:353: IT01CF    = 0x21;		// /INT0 and /INT1 active low, P0.1 and P0.2 respectively
                           1431 ;	genAssign
   027A 75 E4 21           1432 	mov	_IT01CF,#0x21
                    019C   1433 	C$TSIPMon.c$360$1$1 ==.
                           1434 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:360: IT0 = 1;	// /INT0 edge triggered
                           1435 ;	genAssign
   027D D2 88              1436 	setb	_IT0
                    019E   1437 	C$TSIPMon.c$361$1$1 ==.
                           1438 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:361: IT1 = 1;	// /INT1 edge triggered
                           1439 ;	genAssign
   027F D2 8A              1440 	setb	_IT1
                           1441 ;	Peephole 300	removed redundant label 00101$
                    01A0   1442 	C$TSIPMon.c$365$1$1 ==.
                    01A0   1443 	XG$Port_Init$0$0 ==.
   0281 22                 1444 	ret
                           1445 ;------------------------------------------------------------
                           1446 ;Allocation info for local variables in function 'Timer2_Init'
                           1447 ;------------------------------------------------------------
                           1448 ;i                         Allocated to registers r2 
                           1449 ;------------------------------------------------------------
                    01A1   1450 	G$Timer2_Init$0$0 ==.
                    01A1   1451 	C$TSIPMon.c$380$1$1 ==.
                           1452 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:380: void Timer2_Init( void ){
                           1453 ;	-----------------------------------------
                           1454 ;	 function Timer2_Init
                           1455 ;	-----------------------------------------
   0282                    1456 _Timer2_Init:
                    01A1   1457 	C$TSIPMon.c$384$1$1 ==.
                           1458 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:384: CKCON &= ~0x60;                     // Timer2 uses SYSCLK/12
                           1459 ;	genAnd
   0282 53 8E 9F           1460 	anl	_CKCON,#0x9F
                    01A4   1461 	C$TSIPMon.c$385$1$1 ==.
                           1462 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:385: TMR2CN &= ~0x01;					// Set bit 0 low, select SYSCLK/12
                           1463 ;	genAnd
   0285 53 C8 FE           1464 	anl	_TMR2CN,#0xFE
                    01A7   1465 	C$TSIPMon.c$387$1$1 ==.
                           1466 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:387: TMR2RL = TIMER2_RELOAD;             // Reload value to be used in Timer2
                           1467 ;	genAssign
   0288 75 CA 02           1468 	mov	_TMR2RL,#0x02
   028B 75 CB FE           1469 	mov	(_TMR2RL >> 8),#0xFE
                    01AD   1470 	C$TSIPMon.c$388$1$1 ==.
                           1471 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:388: TMR2 = TMR2RL;                      // Init the Timer2 register
                           1472 ;	genAssign
   028E 85 CA CC           1473 	mov	_TMR2,_TMR2RL
   0291 85 CB CD           1474 	mov	(_TMR2 >> 8),(_TMR2RL >> 8)
                    01B3   1475 	C$TSIPMon.c$390$1$1 ==.
                           1476 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:390: TMR2CN = 0x04;                      // Enable Timer2 in auto-reload mode
                           1477 ;	genAssign
   0294 75 C8 04           1478 	mov	_TMR2CN,#0x04
                    01B6   1479 	C$TSIPMon.c$391$1$1 ==.
                           1480 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:391: ET2 = 1;                            // Timer2 interrupt enabled
                           1481 ;	genAssign
   0297 D2 AD              1482 	setb	_ET2
                    01B8   1483 	C$TSIPMon.c$393$1$1 ==.
                           1484 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:393: for( i = 0; i < NUM_TIMERS; i++ ){	// Initialize software timers.
                           1485 ;	genAssign
   0299 7A 03              1486 	mov	r2,#0x03
   029B                    1487 00103$:
                    01BA   1488 	C$TSIPMon.c$394$2$2 ==.
                           1489 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:394: Timer[i].Status = 0;
                           1490 ;	genMinus
                           1491 ;	genMinusDec
   029B EA                 1492 	mov	a,r2
   029C 14                 1493 	dec	a
                           1494 ;	genMult
                           1495 ;	genMultOneByte
   029D FB                 1496 	mov	r3,a
                           1497 ;	Peephole 105	removed redundant mov
   029E 75 F0 03           1498 	mov	b,#0x03
   02A1 A4                 1499 	mul	ab
                           1500 ;	genPlus
   02A2 24 22              1501 	add	a,#_Timer
   02A4 F8                 1502 	mov	r0,a
                           1503 ;	genPlus
                           1504 ;     genPlusIncr
   02A5 74 02              1505 	mov	a,#0x02
                           1506 ;	Peephole 236.a	used r0 instead of ar0
   02A7 28                 1507 	add	a,r0
                           1508 ;	genPointerSet
                           1509 ;	genNearPointerSet
                           1510 ;	Peephole 239	used a instead of acc
   02A8 F9                 1511 	mov	r1,a
   02A9 77 00              1512 	mov	@r1,#0x00
                    01CA   1513 	C$TSIPMon.c$395$2$2 ==.
                           1514 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:395: Timer[i].WaitTime = 0;
                           1515 ;	genPointerSet
                           1516 ;	genNearPointerSet
   02AB 76 00              1517 	mov	@r0,#0x00
   02AD 08                 1518 	inc	r0
   02AE 76 00              1519 	mov	@r0,#0x00
   02B0 18                 1520 	dec	r0
                           1521 ;	genAssign
   02B1 8B 02              1522 	mov	ar2,r3
                    01D2   1523 	C$TSIPMon.c$393$2$2 ==.
                           1524 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:393: for( i = 0; i < NUM_TIMERS; i++ ){	// Initialize software timers.
                           1525 ;	genIfx
   02B3 EA                 1526 	mov	a,r2
                           1527 ;	genIfxJump
                           1528 ;	Peephole 108.b	removed ljmp by inverse jump logic
   02B4 70 E5              1529 	jnz	00103$
                           1530 ;	Peephole 300	removed redundant label 00108$
                           1531 ;	Peephole 300	removed redundant label 00104$
                    01D5   1532 	C$TSIPMon.c$398$2$2 ==.
                    01D5   1533 	XG$Timer2_Init$0$0 ==.
   02B6 22                 1534 	ret
                           1535 ;------------------------------------------------------------
                           1536 ;Allocation info for local variables in function 'Timer2_ISR'
                           1537 ;------------------------------------------------------------
                           1538 ;i                         Allocated to registers r2 
                           1539 ;------------------------------------------------------------
                    01D6   1540 	G$Timer2_ISR$0$0 ==.
                    01D6   1541 	C$TSIPMon.c$412$2$2 ==.
                           1542 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:412: void Timer2_ISR( void ) interrupt 5{
                           1543 ;	-----------------------------------------
                           1544 ;	 function Timer2_ISR
                           1545 ;	-----------------------------------------
   02B7                    1546 _Timer2_ISR:
   02B7 C0 E0              1547 	push	acc
   02B9 C0 F0              1548 	push	b
   02BB C0 02              1549 	push	ar2
   02BD C0 03              1550 	push	ar3
   02BF C0 04              1551 	push	ar4
   02C1 C0 05              1552 	push	ar5
   02C3 C0 00              1553 	push	ar0
   02C5 C0 D0              1554 	push	psw
   02C7 75 D0 00           1555 	mov	psw,#0x00
                    01E9   1556 	C$TSIPMon.c$417$1$1 ==.
                           1557 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:417: TF2H = 0;                           	// Reset Interrupt
                           1558 ;	genAssign
   02CA C2 CF              1559 	clr	_TF2H
                    01EB   1560 	C$TSIPMon.c$418$1$1 ==.
                           1561 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:418: if( ticks > 0 )
                           1562 ;	genIfx
   02CC E5 2F              1563 	mov	a,_ticks
   02CE 45 30              1564 	orl	a,(_ticks + 1)
                           1565 ;	genIfxJump
                           1566 ;	Peephole 108.c	removed ljmp by inverse jump logic
   02D0 60 09              1567 	jz	00115$
                           1568 ;	Peephole 300	removed redundant label 00117$
                    01F1   1569 	C$TSIPMon.c$419$1$1 ==.
                           1570 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:419: ticks--;
                           1571 ;	genMinus
                           1572 ;	genMinusDec
   02D2 15 2F              1573 	dec	_ticks
   02D4 74 FF              1574 	mov	a,#0xff
   02D6 B5 2F 02           1575 	cjne	a,_ticks,00118$
   02D9 15 30              1576 	dec	(_ticks + 1)
   02DB                    1577 00118$:
                    01FA   1578 	C$TSIPMon.c$420$1$1 ==.
                           1579 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:420: for( i = 0; i < NUM_TIMERS; i++ ){		// Cycle through all timers, to update.
   02DB                    1580 00115$:
                           1581 ;	genAssign
   02DB 7A 00              1582 	mov	r2,#0x00
   02DD                    1583 00106$:
                           1584 ;	genCmpLt
                           1585 ;	genCmp
   02DD BA 03 00           1586 	cjne	r2,#0x03,00119$
   02E0                    1587 00119$:
                           1588 ;	genIfxJump
                           1589 ;	Peephole 108.a	removed ljmp by inverse jump logic
   02E0 50 33              1590 	jnc	00110$
                           1591 ;	Peephole 300	removed redundant label 00120$
                    0201   1592 	C$TSIPMon.c$421$2$2 ==.
                           1593 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:421: if( Timer[i].WaitTime > 0 ){		// Is it Expired?
                           1594 ;	genMult
                           1595 ;	genMultOneByte
   02E2 EA                 1596 	mov	a,r2
   02E3 75 F0 03           1597 	mov	b,#0x03
   02E6 A4                 1598 	mul	ab
                           1599 ;	genPlus
   02E7 FB                 1600 	mov	r3,a
                           1601 ;	Peephole 177.b	removed redundant mov
   02E8 24 22              1602 	add	a,#_Timer
   02EA F8                 1603 	mov	r0,a
                           1604 ;	genPointerGet
                           1605 ;	genNearPointerGet
   02EB 86 04              1606 	mov	ar4,@r0
   02ED 08                 1607 	inc	r0
   02EE 86 05              1608 	mov	ar5,@r0
   02F0 18                 1609 	dec	r0
                           1610 ;	genIfx
   02F1 EC                 1611 	mov	a,r4
   02F2 4D                 1612 	orl	a,r5
                           1613 ;	genIfxJump
                           1614 ;	Peephole 108.c	removed ljmp by inverse jump logic
   02F3 60 15              1615 	jz	00104$
                           1616 ;	Peephole 300	removed redundant label 00121$
                    0214   1617 	C$TSIPMon.c$422$3$3 ==.
                           1618 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:422: Timer[i].WaitTime--;			// No: Count it down.
                           1619 ;	genMinus
                           1620 ;	genMinusDec
   02F5 1C                 1621 	dec	r4
   02F6 BC FF 01           1622 	cjne	r4,#0xff,00122$
   02F9 1D                 1623 	dec	r5
   02FA                    1624 00122$:
                           1625 ;	genPointerSet
                           1626 ;	genNearPointerSet
   02FA A6 04              1627 	mov	@r0,ar4
   02FC 08                 1628 	inc	r0
   02FD A6 05              1629 	mov	@r0,ar5
   02FF 18                 1630 	dec	r0
                    021F   1631 	C$TSIPMon.c$423$3$3 ==.
                           1632 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:423: Timer[i].Status = TIMER_STATUS_RUNNING;
                           1633 ;	genPlus
                           1634 ;	Peephole 236.g	used r3 instead of ar3
   0300 EB                 1635 	mov	a,r3
   0301 24 22              1636 	add	a,#_Timer
                           1637 ;	genPlus
                           1638 ;     genPlusIncr
   0303 24 02              1639 	add	a,#0x02
                           1640 ;	genPointerSet
                           1641 ;	genNearPointerSet
                           1642 ;	Peephole 239	used a instead of acc
   0305 F8                 1643 	mov	r0,a
   0306 76 01              1644 	mov	@r0,#0x01
                           1645 ;	Peephole 112.b	changed ljmp to sjmp
   0308 80 08              1646 	sjmp	00108$
   030A                    1647 00104$:
                    0229   1648 	C$TSIPMon.c$425$3$4 ==.
                           1649 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:425: Timer[i].Status = TIMER_STATUS_READY;
                           1650 ;	genPlus
                           1651 ;	Peephole 236.g	used r3 instead of ar3
   030A EB                 1652 	mov	a,r3
   030B 24 22              1653 	add	a,#_Timer
                           1654 ;	genPlus
                           1655 ;     genPlusIncr
   030D 24 02              1656 	add	a,#0x02
                           1657 ;	genPointerSet
                           1658 ;	genNearPointerSet
                           1659 ;	Peephole 239	used a instead of acc
   030F F8                 1660 	mov	r0,a
   0310 76 00              1661 	mov	@r0,#0x00
   0312                    1662 00108$:
                    0231   1663 	C$TSIPMon.c$420$1$1 ==.
                           1664 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:420: for( i = 0; i < NUM_TIMERS; i++ ){		// Cycle through all timers, to update.
                           1665 ;	genPlus
                           1666 ;     genPlusIncr
   0312 0A                 1667 	inc	r2
                           1668 ;	Peephole 112.b	changed ljmp to sjmp
   0313 80 C8              1669 	sjmp	00106$
   0315                    1670 00110$:
   0315 D0 D0              1671 	pop	psw
   0317 D0 00              1672 	pop	ar0
   0319 D0 05              1673 	pop	ar5
   031B D0 04              1674 	pop	ar4
   031D D0 03              1675 	pop	ar3
   031F D0 02              1676 	pop	ar2
   0321 D0 F0              1677 	pop	b
   0323 D0 E0              1678 	pop	acc
                    0244   1679 	C$TSIPMon.c$429$1$1 ==.
                    0244   1680 	XG$Timer2_ISR$0$0 ==.
   0325 32                 1681 	reti
                           1682 ;	eliminated unneeded push/pop ar1
                           1683 ;	eliminated unneeded push/pop dpl
                           1684 ;	eliminated unneeded push/pop dph
                           1685 ;------------------------------------------------------------
                           1686 ;Allocation info for local variables in function 'WaitTicks'
                           1687 ;------------------------------------------------------------
                           1688 ;delay                     Allocated to registers r2 r3 
                           1689 ;------------------------------------------------------------
                    0245   1690 	G$WaitTicks$0$0 ==.
                    0245   1691 	C$TSIPMon.c$436$1$1 ==.
                           1692 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:436: void WaitTicks( uint delay){
                           1693 ;	-----------------------------------------
                           1694 ;	 function WaitTicks
                           1695 ;	-----------------------------------------
   0326                    1696 _WaitTicks:
                           1697 ;	genReceive
   0326 AA 82              1698 	mov	r2,dpl
   0328 AB 83              1699 	mov	r3,dph
                    0249   1700 	C$TSIPMon.c$438$1$1 ==.
                           1701 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:438: EA = FALSE;
                           1702 ;	genAssign
   032A C2 AF              1703 	clr	_EA
                    024B   1704 	C$TSIPMon.c$439$1$1 ==.
                           1705 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:439: ticks = delay;
                           1706 ;	genAssign
   032C 8A 2F              1707 	mov	_ticks,r2
   032E 8B 30              1708 	mov	(_ticks + 1),r3
                    024F   1709 	C$TSIPMon.c$440$1$1 ==.
                           1710 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:440: EA = TRUE;
                           1711 ;	genAssign
   0330 D2 AF              1712 	setb	_EA
                    0251   1713 	C$TSIPMon.c$441$1$1 ==.
                           1714 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:441: while( ticks > 0 )
   0332                    1715 00101$:
                           1716 ;	genIfx
   0332 E5 2F              1717 	mov	a,_ticks
   0334 45 30              1718 	orl	a,(_ticks + 1)
                           1719 ;	genIfxJump
                           1720 ;	Peephole 108.b	removed ljmp by inverse jump logic
   0336 70 FA              1721 	jnz	00101$
                           1722 ;	Peephole 300	removed redundant label 00107$
                           1723 ;	Peephole 300	removed redundant label 00104$
                    0257   1724 	C$TSIPMon.c$444$1$1 ==.
                    0257   1725 	XG$WaitTicks$0$0 ==.
   0338 22                 1726 	ret
                           1727 ;------------------------------------------------------------
                           1728 ;Allocation info for local variables in function 'TimerStart'
                           1729 ;------------------------------------------------------------
                           1730 ;num_ticks                 Allocated with name '_TimerStart_PARM_2'
                           1731 ;timer_num                 Allocated to registers r2 
                           1732 ;------------------------------------------------------------
                    0258   1733 	G$TimerStart$0$0 ==.
                    0258   1734 	C$TSIPMon.c$456$1$1 ==.
                           1735 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:456: void TimerStart( uchar timer_num, uint num_ticks ){
                           1736 ;	-----------------------------------------
                           1737 ;	 function TimerStart
                           1738 ;	-----------------------------------------
   0339                    1739 _TimerStart:
                           1740 ;	genReceive
   0339 AA 82              1741 	mov	r2,dpl
                    025A   1742 	C$TSIPMon.c$458$1$1 ==.
                           1743 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:458: INT_DISABLE;
                           1744 ;	genAssign
   033B C2 A9              1745 	clr	_ET0
                    025C   1746 	C$TSIPMon.c$460$1$1 ==.
                           1747 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:460: Timer[timer_num].WaitTime	= num_ticks;
                           1748 ;	genMult
                           1749 ;	genMultOneByte
   033D EA                 1750 	mov	a,r2
   033E 75 F0 03           1751 	mov	b,#0x03
   0341 A4                 1752 	mul	ab
                           1753 ;	genPlus
   0342 FA                 1754 	mov	r2,a
                           1755 ;	Peephole 177.b	removed redundant mov
   0343 24 22              1756 	add	a,#_Timer
                           1757 ;	genPointerSet
                           1758 ;	genNearPointerSet
                           1759 ;	Peephole 239	used a instead of acc
   0345 F8                 1760 	mov	r0,a
   0346 A6 0E              1761 	mov	@r0,_TimerStart_PARM_2
   0348 08                 1762 	inc	r0
   0349 A6 0F              1763 	mov	@r0,(_TimerStart_PARM_2 + 1)
                    026A   1764 	C$TSIPMon.c$461$1$1 ==.
                           1765 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:461: Timer[timer_num].Status	= TIMER_STATUS_RUNNING;
                           1766 ;	genPlus
                           1767 ;	Peephole 236.g	used r2 instead of ar2
   034B EA                 1768 	mov	a,r2
   034C 24 22              1769 	add	a,#_Timer
                           1770 ;	genPlus
                           1771 ;     genPlusIncr
   034E 24 02              1772 	add	a,#0x02
                           1773 ;	genPointerSet
                           1774 ;	genNearPointerSet
                           1775 ;	Peephole 239	used a instead of acc
   0350 F8                 1776 	mov	r0,a
   0351 76 01              1777 	mov	@r0,#0x01
                    0272   1778 	C$TSIPMon.c$463$1$1 ==.
                           1779 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:463: INT_ENABLE;
                           1780 ;	genAssign
   0353 D2 A9              1781 	setb	_ET0
                           1782 ;	Peephole 300	removed redundant label 00101$
                    0274   1783 	C$TSIPMon.c$465$1$1 ==.
                    0274   1784 	XG$TimerStart$0$0 ==.
   0355 22                 1785 	ret
                           1786 ;------------------------------------------------------------
                           1787 ;Allocation info for local variables in function 'TimerRunning'
                           1788 ;------------------------------------------------------------
                           1789 ;timer_num                 Allocated to registers r2 
                           1790 ;------------------------------------------------------------
                    0275   1791 	G$TimerRunning$0$0 ==.
                    0275   1792 	C$TSIPMon.c$471$1$1 ==.
                           1793 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:471: bit TimerRunning( uchar timer_num ){
                           1794 ;	-----------------------------------------
                           1795 ;	 function TimerRunning
                           1796 ;	-----------------------------------------
   0356                    1797 _TimerRunning:
                           1798 ;	genReceive
                    0275   1799 	C$TSIPMon.c$473$1$1 ==.
                           1800 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:473: return( (Timer[timer_num].Status == TIMER_STATUS_RUNNING)?TRUE:FALSE );
                           1801 ;	genMult
                           1802 ;	genMultOneByte
                           1803 ;	peephole 177.g	optimized mov sequence
   0356 E5 82              1804 	mov	a,dpl
   0358 FA                 1805 	mov	r2,a
   0359 75 F0 03           1806 	mov	b,#0x03
   035C A4                 1807 	mul	ab
                           1808 ;	genPlus
   035D 24 22              1809 	add	a,#_Timer
                           1810 ;	genPlus
                           1811 ;     genPlusIncr
   035F 24 02              1812 	add	a,#0x02
   0361 F8                 1813 	mov	r0,a
                           1814 ;	genPointerGet
                           1815 ;	genNearPointerGet
   0362 86 02              1816 	mov	ar2,@r0
                           1817 ;	genCmpEq
                           1818 ;	gencjneshort
                           1819 ;	Peephole 112.b	changed ljmp to sjmp
                           1820 ;	Peephole 198.b	optimized misc jump sequence
   0364 BA 01 04           1821 	cjne	r2,#0x01,00103$
                           1822 ;	Peephole 200.b	removed redundant sjmp
                           1823 ;	Peephole 300	removed redundant label 00106$
                           1824 ;	Peephole 300	removed redundant label 00107$
                           1825 ;	genAssign
   0367 7A 01              1826 	mov	r2,#0x01
                           1827 ;	Peephole 112.b	changed ljmp to sjmp
   0369 80 02              1828 	sjmp	00104$
   036B                    1829 00103$:
                           1830 ;	genAssign
   036B 7A 00              1831 	mov	r2,#0x00
   036D                    1832 00104$:
                           1833 ;	genRet
   036D EA                 1834 	mov	a,r2
   036E 24 FF              1835 	add	a,#0xff
                           1836 ;	Peephole 300	removed redundant label 00101$
                    028F   1837 	C$TSIPMon.c$475$1$1 ==.
                    028F   1838 	XG$TimerRunning$0$0 ==.
   0370 22                 1839 	ret
                           1840 ;------------------------------------------------------------
                           1841 ;Allocation info for local variables in function 'TimerReset'
                           1842 ;------------------------------------------------------------
                           1843 ;timer_num                 Allocated to registers r2 
                           1844 ;------------------------------------------------------------
                    0290   1845 	G$TimerReset$0$0 ==.
                    0290   1846 	C$TSIPMon.c$481$1$1 ==.
                           1847 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:481: void TimerReset( uchar timer_num ){
                           1848 ;	-----------------------------------------
                           1849 ;	 function TimerReset
                           1850 ;	-----------------------------------------
   0371                    1851 _TimerReset:
                           1852 ;	genReceive
   0371 AA 82              1853 	mov	r2,dpl
                    0292   1854 	C$TSIPMon.c$483$1$1 ==.
                           1855 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:483: INT_DISABLE;
                           1856 ;	genAssign
   0373 C2 A9              1857 	clr	_ET0
                    0294   1858 	C$TSIPMon.c$484$1$1 ==.
                           1859 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:484: Timer[timer_num].WaitTime	= 0;
                           1860 ;	genMult
                           1861 ;	genMultOneByte
   0375 EA                 1862 	mov	a,r2
   0376 75 F0 03           1863 	mov	b,#0x03
   0379 A4                 1864 	mul	ab
                           1865 ;	genPlus
   037A FA                 1866 	mov	r2,a
                           1867 ;	Peephole 177.b	removed redundant mov
   037B 24 22              1868 	add	a,#_Timer
                           1869 ;	genPointerSet
                           1870 ;	genNearPointerSet
                           1871 ;	Peephole 239	used a instead of acc
   037D F8                 1872 	mov	r0,a
   037E 76 00              1873 	mov	@r0,#0x00
   0380 08                 1874 	inc	r0
   0381 76 00              1875 	mov	@r0,#0x00
                    02A2   1876 	C$TSIPMon.c$485$1$1 ==.
                           1877 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:485: Timer[timer_num].Status	= TIMER_STATUS_STOPPED;
                           1878 ;	genPlus
                           1879 ;	Peephole 236.g	used r2 instead of ar2
   0383 EA                 1880 	mov	a,r2
   0384 24 22              1881 	add	a,#_Timer
                           1882 ;	genPlus
                           1883 ;     genPlusIncr
   0386 24 02              1884 	add	a,#0x02
                           1885 ;	genPointerSet
                           1886 ;	genNearPointerSet
                           1887 ;	Peephole 239	used a instead of acc
   0388 F8                 1888 	mov	r0,a
   0389 76 02              1889 	mov	@r0,#0x02
                    02AA   1890 	C$TSIPMon.c$486$1$1 ==.
                           1891 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:486: INT_ENABLE;
                           1892 ;	genAssign
   038B D2 A9              1893 	setb	_ET0
                           1894 ;	Peephole 300	removed redundant label 00101$
                    02AC   1895 	C$TSIPMon.c$488$1$1 ==.
                    02AC   1896 	XG$TimerReset$0$0 ==.
   038D 22                 1897 	ret
                           1898 ;------------------------------------------------------------
                           1899 ;Allocation info for local variables in function 'TimerReady'
                           1900 ;------------------------------------------------------------
                           1901 ;timer_num                 Allocated to registers r2 
                           1902 ;------------------------------------------------------------
                    02AD   1903 	G$TimerReady$0$0 ==.
                    02AD   1904 	C$TSIPMon.c$493$1$1 ==.
                           1905 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:493: bit TimerReady( uchar timer_num ){
                           1906 ;	-----------------------------------------
                           1907 ;	 function TimerReady
                           1908 ;	-----------------------------------------
   038E                    1909 _TimerReady:
                           1910 ;	genReceive
                    02AD   1911 	C$TSIPMon.c$495$1$1 ==.
                           1912 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:495: if( Timer[timer_num].Status == TIMER_STATUS_READY )
                           1913 ;	genMult
                           1914 ;	genMultOneByte
                           1915 ;	peephole 177.g	optimized mov sequence
   038E E5 82              1916 	mov	a,dpl
   0390 FA                 1917 	mov	r2,a
   0391 75 F0 03           1918 	mov	b,#0x03
   0394 A4                 1919 	mul	ab
                           1920 ;	genPlus
   0395 24 22              1921 	add	a,#_Timer
                           1922 ;	genPlus
                           1923 ;     genPlusIncr
   0397 24 02              1924 	add	a,#0x02
   0399 F8                 1925 	mov	r0,a
                           1926 ;	genPointerGet
                           1927 ;	genNearPointerGet
   039A E6                 1928 	mov	a,@r0
                           1929 ;	genIfxJump
                           1930 ;	Peephole 108.b	removed ljmp by inverse jump logic
   039B 70 05              1931 	jnz	00102$
                           1932 ;	Peephole 300	removed redundant label 00107$
                    02BC   1933 	C$TSIPMon.c$496$1$1 ==.
                           1934 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:496: return( TRUE );
                           1935 ;	genRet
   039D 74 01              1936 	mov	a,#0x01
   039F 24 FF              1937 	add	a,#0xff
                           1938 ;	Peephole 112.b	changed ljmp to sjmp
                           1939 ;	Peephole 251.b	replaced sjmp to ret with ret
   03A1 22                 1940 	ret
   03A2                    1941 00102$:
                    02C1   1942 	C$TSIPMon.c$498$1$1 ==.
                           1943 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:498: return( FALSE );
                           1944 ;	genRet
                           1945 ;	Peephole 181	changed mov to clr
   03A2 E4                 1946 	clr	a
   03A3 24 FF              1947 	add	a,#0xff
                           1948 ;	Peephole 300	removed redundant label 00104$
                    02C4   1949 	C$TSIPMon.c$500$1$1 ==.
                    02C4   1950 	XG$TimerReady$0$0 ==.
   03A5 22                 1951 	ret
                           1952 ;------------------------------------------------------------
                           1953 ;Allocation info for local variables in function 'UART0_Init'
                           1954 ;------------------------------------------------------------
                           1955 ;------------------------------------------------------------
                    02C5   1956 	G$UART0_Init$0$0 ==.
                    02C5   1957 	C$TSIPMon.c$515$1$1 ==.
                           1958 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:515: void UART0_Init( void ){
                           1959 ;	-----------------------------------------
                           1960 ;	 function UART0_Init
                           1961 ;	-----------------------------------------
   03A6                    1962 _UART0_Init:
                    02C5   1963 	C$TSIPMon.c$517$1$1 ==.
                           1964 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:517: SCON0 = 0x10;                       // SCON0: 8-bit variable bit rate
                           1965 ;	genAssign
   03A6 75 98 10           1966 	mov	_SCON0,#0x10
                    02C8   1967 	C$TSIPMon.c$527$2$2 ==.
                           1968 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:527: TH1 =  (unsigned char) -(SYSCLK/BAUDRATE/2);
                           1969 ;	genAssign
   03A9 75 8D 61           1970 	mov	_TH1,#0x61
                    02CB   1971 	C$TSIPMon.c$528$2$2 ==.
                           1972 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:528: CKCON &= ~0x0B;                  // T1M = 1; SCA1:0 = xx
                           1973 ;	genAnd
   03AC 53 8E F4           1974 	anl	_CKCON,#0xF4
                    02CE   1975 	C$TSIPMon.c$529$2$2 ==.
                           1976 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:529: CKCON |=  0x08; 
                           1977 ;	genOr
   03AF 43 8E 08           1978 	orl	_CKCON,#0x08
                    02D1   1979 	C$TSIPMon.c$544$1$1 ==.
                           1980 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:544: TL1 = TH1;                          // Init Timer1
                           1981 ;	genAssign
   03B2 85 8D 8B           1982 	mov	_TL1,_TH1
                    02D4   1983 	C$TSIPMon.c$545$1$1 ==.
                           1984 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:545: TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
                           1985 ;	genAnd
   03B5 53 89 0F           1986 	anl	_TMOD,#0x0F
                    02D7   1987 	C$TSIPMon.c$546$1$1 ==.
                           1988 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:546: TMOD |=  0x20;
                           1989 ;	genOr
   03B8 43 89 20           1990 	orl	_TMOD,#0x20
                    02DA   1991 	C$TSIPMon.c$547$1$1 ==.
                           1992 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:547: TR1 = 1;                            // START Timer1
                           1993 ;	genAssign
   03BB D2 8E              1994 	setb	_TR1
                    02DC   1995 	C$TSIPMon.c$548$1$1 ==.
                           1996 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:548: TI0 = 1;                            // Indicate TX0 ready
                           1997 ;	genAssign
   03BD D2 99              1998 	setb	_TI0
                    02DE   1999 	C$TSIPMon.c$556$1$1 ==.
                           2000 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:556: RI0 = FALSE;		// turn off any pending receive interrupt
                           2001 ;	genAssign
   03BF C2 98              2002 	clr	_RI0
                    02E0   2003 	C$TSIPMon.c$557$1$1 ==.
                           2004 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:557: REN0 = TRUE;		// UART0 receive enable
                           2005 ;	genAssign
   03C1 D2 9C              2006 	setb	_REN0
                    02E2   2007 	C$TSIPMon.c$558$1$1 ==.
                           2008 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:558: ES0 = TRUE;         // UART0 interrupt enable
                           2009 ;	genAssign
   03C3 D2 AC              2010 	setb	_ES0
                           2011 ;	Peephole 300	removed redundant label 00110$
                    02E4   2012 	C$TSIPMon.c$560$1$1 ==.
                    02E4   2013 	XG$UART0_Init$0$0 ==.
   03C5 22                 2014 	ret
                           2015 ;------------------------------------------------------------
                           2016 ;Allocation info for local variables in function 'SioIntService'
                           2017 ;------------------------------------------------------------
                           2018 ;tchar                     Allocated to registers r2 
                           2019 ;------------------------------------------------------------
                    02E5   2020 	G$SioIntService$0$0 ==.
                    02E5   2021 	C$TSIPMon.c$566$1$1 ==.
                           2022 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:566: void SioIntService( void ) interrupt INTERRUPT_UART0 using SIO_REG_BANK {
                           2023 ;	-----------------------------------------
                           2024 ;	 function SioIntService
                           2025 ;	-----------------------------------------
   03C6                    2026 _SioIntService:
                    0012   2027 	ar2 = 0x12
                    0013   2028 	ar3 = 0x13
                    0014   2029 	ar4 = 0x14
                    0015   2030 	ar5 = 0x15
                    0016   2031 	ar6 = 0x16
                    0017   2032 	ar7 = 0x17
                    0010   2033 	ar0 = 0x10
                    0011   2034 	ar1 = 0x11
   03C6 C0 E0              2035 	push	acc
   03C8 C0 82              2036 	push	dpl
   03CA C0 83              2037 	push	dph
   03CC C0 D0              2038 	push	psw
   03CE 75 D0 10           2039 	mov	psw,#0x10
                    02F0   2040 	C$TSIPMon.c$573$1$1 ==.
                           2041 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:573: if( RI0 ){
                           2042 ;	genIfx
                           2043 ;	genIfxJump
   03D1 20 98 03           2044 	jb	_RI0,00181$
   03D4 02 04 EF           2045 	ljmp	00154$
   03D7                    2046 00181$:
                    02F6   2047 	C$TSIPMon.c$574$2$2 ==.
                           2048 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:574: tchar = SBUF0;	// & PARITY_MASK;
                           2049 ;	genAssign
   03D7 AA 99              2050 	mov	r2,_SBUF0
                    02F8   2051 	C$TSIPMon.c$575$2$2 ==.
                           2052 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:575: RI0 = FALSE;
                           2053 ;	genAssign
   03D9 C2 98              2054 	clr	_RI0
                    02FA   2055 	C$TSIPMon.c$578$2$2 ==.
                           2056 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:578: if( TxRx_Count > TXRX_BUF_LEN - 1 ) {
                           2057 ;	genCmpGt
                           2058 ;	genCmp
                           2059 ;	genIfxJump
                           2060 ;	Peephole 108.a	removed ljmp by inverse jump logic
                           2061 ;	Peephole 132.b	optimized genCmpGt by inverse logic (acc differs)
   03DB E5 2C              2062 	mov	a,_TxRx_Count
   03DD 24 AB              2063 	add	a,#0xff - 0x54
   03DF 50 09              2064 	jnc	00102$
                           2065 ;	Peephole 300	removed redundant label 00182$
                    0300   2066 	C$TSIPMon.c$579$3$3 ==.
                           2067 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:579: TxRx_State = WAIT_FOR_START;
                           2068 ;	genAssign
   03E1 75 2B 00           2069 	mov	_TxRx_State,#0x00
                    0303   2070 	C$TSIPMon.c$580$3$3 ==.
                           2071 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:580: TxRx_Count = 0;
                           2072 ;	genAssign
   03E4 75 2C 00           2073 	mov	_TxRx_Count,#0x00
                    0306   2074 	C$TSIPMon.c$581$3$3 ==.
                           2075 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:581: return;
                           2076 ;	genRet
   03E7 02 05 54           2077 	ljmp	00156$
   03EA                    2078 00102$:
                    0309   2079 	C$TSIPMon.c$584$2$2 ==.
                           2080 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:584: switch( TxRx_State ){
                           2081 ;	genCmpGt
                           2082 ;	genCmp
                           2083 ;	genIfxJump
                           2084 ;	Peephole 132.b	optimized genCmpGt by inverse logic (acc differs)
   03EA E5 2B              2085 	mov	a,_TxRx_State
   03EC 24 FA              2086 	add	a,#0xff - 0x05
   03EE 50 03              2087 	jnc	00183$
   03F0 02 04 EA           2088 	ljmp	00137$
   03F3                    2089 00183$:
                           2090 ;	genJumpTab
   03F3 E5 2B              2091 	mov	a,_TxRx_State
                           2092 ;	Peephole 254	optimized left shift
   03F5 25 2B              2093 	add	a,_TxRx_State
   03F7 25 2B              2094 	add	a,_TxRx_State
   03F9 90 03 FD           2095 	mov	dptr,#00184$
   03FC 73                 2096 	jmp	@a+dptr
   03FD                    2097 00184$:
   03FD 02 04 0F           2098 	ljmp	00103$
   0400 02 04 31           2099 	ljmp	00109$
   0403 02 04 40           2100 	ljmp	00113$
   0406 02 04 4F           2101 	ljmp	00117$
   0409 02 04 67           2102 	ljmp	00121$
   040C 02 04 8E           2103 	ljmp	00126$
                    032E   2104 	C$TSIPMon.c$585$3$4 ==.
                           2105 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:585: case WAIT_FOR_START:
   040F                    2106 00103$:
                    032E   2107 	C$TSIPMon.c$588$3$4 ==.
                           2108 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:588: if( tchar == DLE ){
                           2109 ;	genCmpEq
                           2110 ;	gencjneshort
                           2111 ;	Peephole 112.b	changed ljmp to sjmp
                           2112 ;	Peephole 198.b	optimized misc jump sequence
   040F BA 10 0D           2113 	cjne	r2,#0x10,00107$
                           2114 ;	Peephole 200.b	removed redundant sjmp
                           2115 ;	Peephole 300	removed redundant label 00185$
                           2116 ;	Peephole 300	removed redundant label 00186$
                    0331   2117 	C$TSIPMon.c$590$4$5 ==.
                           2118 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:590: TxRxBuf[TxRx_Count++] = tchar;
                           2119 ;	genAssign
   0412 75 2C 01           2120 	mov	_TxRx_Count,#0x01
                           2121 ;	genPointerSet
                           2122 ;     genFarPointerSet
   0415 90 00 17           2123 	mov	dptr,#_TxRxBuf
   0418 EA                 2124 	mov	a,r2
   0419 F0                 2125 	movx	@dptr,a
                    0339   2126 	C$TSIPMon.c$591$4$5 ==.
                           2127 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:591: TxRx_State = WAIT_FOR_ID;
                           2128 ;	genAssign
   041A 75 2B 04           2129 	mov	_TxRx_State,#0x04
                           2130 ;	Peephole 112.b	changed ljmp to sjmp
   041D 80 0D              2131 	sjmp	00108$
   041F                    2132 00107$:
                    033E   2133 	C$TSIPMon.c$592$3$4 ==.
                           2134 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:592: }else if( tchar != ETX ){
                           2135 ;	genCmpEq
                           2136 ;	gencjneshort
   041F BA 03 02           2137 	cjne	r2,#0x03,00187$
                           2138 ;	Peephole 112.b	changed ljmp to sjmp
   0422 80 08              2139 	sjmp	00108$
   0424                    2140 00187$:
                    0343   2141 	C$TSIPMon.c$593$4$6 ==.
                           2142 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:593: TxRx_State = WAIT_FOR_DLE_ETX;
                           2143 ;	genAssign
   0424 75 2B 01           2144 	mov	_TxRx_State,#0x01
                    0346   2145 	C$TSIPMon.c$594$4$6 ==.
                           2146 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:594: Rx_Pending = FALSE;
                           2147 ;	genAssign
   0427 C2 00              2148 	clr	_Rx_Pending
                    0348   2149 	C$TSIPMon.c$595$4$6 ==.
                           2150 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:595: TxRx_Count = 0;
                           2151 ;	genAssign
   0429 75 2C 00           2152 	mov	_TxRx_Count,#0x00
   042C                    2153 00108$:
                    034B   2154 	C$TSIPMon.c$597$3$4 ==.
                           2155 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:597: bEvenDLE = FALSE;
                           2156 ;	genAssign
   042C C2 07              2157 	clr	_SioIntService_bEvenDLE_1_1
                    034D   2158 	C$TSIPMon.c$598$3$4 ==.
                           2159 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:598: break;
   042E 02 05 54           2160 	ljmp	00155$
                    0350   2161 	C$TSIPMon.c$600$3$4 ==.
                           2162 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:600: case WAIT_FOR_DLE_ETX:
   0431                    2163 00109$:
                    0350   2164 	C$TSIPMon.c$601$3$4 ==.
                           2165 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:601: if( tchar == DLE )
                           2166 ;	genCmpEq
                           2167 ;	gencjneshort
                           2168 ;	Peephole 112.b	changed ljmp to sjmp
                           2169 ;	Peephole 198.b	optimized misc jump sequence
   0431 BA 10 06           2170 	cjne	r2,#0x10,00111$
                           2171 ;	Peephole 200.b	removed redundant sjmp
                           2172 ;	Peephole 300	removed redundant label 00188$
                           2173 ;	Peephole 300	removed redundant label 00189$
                    0353   2174 	C$TSIPMon.c$602$3$4 ==.
                           2175 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:602: TxRx_State = WAIT_FOR_ETX;
                           2176 ;	genAssign
   0434 75 2B 02           2177 	mov	_TxRx_State,#0x02
   0437 02 05 54           2178 	ljmp	00155$
   043A                    2179 00111$:
                    0359   2180 	C$TSIPMon.c$604$3$4 ==.
                           2181 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:604: TxRx_State = WAIT_FOR_START;
                           2182 ;	genAssign
   043A 75 2B 00           2183 	mov	_TxRx_State,#0x00
                    035C   2184 	C$TSIPMon.c$605$3$4 ==.
                           2185 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:605: break;
   043D 02 05 54           2186 	ljmp	00155$
                    035F   2187 	C$TSIPMon.c$607$3$4 ==.
                           2188 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:607: case WAIT_FOR_ETX:  // rarely happens
   0440                    2189 00113$:
                    035F   2190 	C$TSIPMon.c$608$3$4 ==.
                           2191 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:608: if( tchar == ETX )	
                           2192 ;	genCmpEq
                           2193 ;	gencjneshort
                           2194 ;	Peephole 112.b	changed ljmp to sjmp
                           2195 ;	Peephole 198.b	optimized misc jump sequence
   0440 BA 03 06           2196 	cjne	r2,#0x03,00115$
                           2197 ;	Peephole 200.b	removed redundant sjmp
                           2198 ;	Peephole 300	removed redundant label 00190$
                           2199 ;	Peephole 300	removed redundant label 00191$
                    0362   2200 	C$TSIPMon.c$610$3$4 ==.
                           2201 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:610: TxRx_State = WAIT_FOR_DLE;
                           2202 ;	genAssign
   0443 75 2B 03           2203 	mov	_TxRx_State,#0x03
   0446 02 05 54           2204 	ljmp	00155$
   0449                    2205 00115$:
                    0368   2206 	C$TSIPMon.c$612$3$4 ==.
                           2207 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:612: TxRx_State = WAIT_FOR_START;
                           2208 ;	genAssign
   0449 75 2B 00           2209 	mov	_TxRx_State,#0x00
                    036B   2210 	C$TSIPMon.c$613$3$4 ==.
                           2211 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:613: break;
   044C 02 05 54           2212 	ljmp	00155$
                    036E   2213 	C$TSIPMon.c$615$3$4 ==.
                           2214 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:615: case WAIT_FOR_DLE:
   044F                    2215 00117$:
                    036E   2216 	C$TSIPMon.c$616$3$4 ==.
                           2217 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:616: if( tchar == DLE ){
                           2218 ;	genCmpEq
                           2219 ;	gencjneshort
                           2220 ;	Peephole 112.b	changed ljmp to sjmp
                           2221 ;	Peephole 198.b	optimized misc jump sequence
   044F BA 10 0D           2222 	cjne	r2,#0x10,00119$
                           2223 ;	Peephole 200.b	removed redundant sjmp
                           2224 ;	Peephole 300	removed redundant label 00192$
                           2225 ;	Peephole 300	removed redundant label 00193$
                    0371   2226 	C$TSIPMon.c$618$4$7 ==.
                           2227 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:618: TxRxBuf[TxRx_Count++] = tchar;
                           2228 ;	genAssign
   0452 75 2C 01           2229 	mov	_TxRx_Count,#0x01
                           2230 ;	genPointerSet
                           2231 ;     genFarPointerSet
   0455 90 00 17           2232 	mov	dptr,#_TxRxBuf
   0458 EA                 2233 	mov	a,r2
   0459 F0                 2234 	movx	@dptr,a
                    0379   2235 	C$TSIPMon.c$619$4$7 ==.
                           2236 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:619: TxRx_State = WAIT_FOR_ID;
                           2237 ;	genAssign
   045A 75 2B 04           2238 	mov	_TxRx_State,#0x04
                           2239 ;	Peephole 112.b	changed ljmp to sjmp
   045D 80 03              2240 	sjmp	00120$
   045F                    2241 00119$:
                    037E   2242 	C$TSIPMon.c$621$3$4 ==.
                           2243 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:621: TxRx_State = WAIT_FOR_START;
                           2244 ;	genAssign
   045F 75 2B 00           2245 	mov	_TxRx_State,#0x00
   0462                    2246 00120$:
                    0381   2247 	C$TSIPMon.c$622$3$4 ==.
                           2248 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:622: bEvenDLE = FALSE;
                           2249 ;	genAssign
   0462 C2 07              2250 	clr	_SioIntService_bEvenDLE_1_1
                    0383   2251 	C$TSIPMon.c$623$3$4 ==.
                           2252 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:623: break;
   0464 02 05 54           2253 	ljmp	00155$
                    0386   2254 	C$TSIPMon.c$625$3$4 ==.
                           2255 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:625: case WAIT_FOR_ID: // never happens
   0467                    2256 00121$:
                    0386   2257 	C$TSIPMon.c$626$3$4 ==.
                           2258 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:626: if( tchar == DLE || tchar == ETX ){
                           2259 ;	genCmpEq
                           2260 ;	gencjneshort
   0467 BA 10 02           2261 	cjne	r2,#0x10,00194$
                           2262 ;	Peephole 112.b	changed ljmp to sjmp
   046A 80 03              2263 	sjmp	00122$
   046C                    2264 00194$:
                           2265 ;	genCmpEq
                           2266 ;	gencjneshort
                           2267 ;	Peephole 112.b	changed ljmp to sjmp
                           2268 ;	Peephole 198.b	optimized misc jump sequence
   046C BA 03 09           2269 	cjne	r2,#0x03,00123$
                           2270 ;	Peephole 200.b	removed redundant sjmp
                           2271 ;	Peephole 300	removed redundant label 00195$
                           2272 ;	Peephole 300	removed redundant label 00196$
   046F                    2273 00122$:
                    038E   2274 	C$TSIPMon.c$627$4$8 ==.
                           2275 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:627: TxRx_State = WAIT_FOR_START;
                           2276 ;	genAssign
   046F 75 2B 00           2277 	mov	_TxRx_State,#0x00
                    0391   2278 	C$TSIPMon.c$628$4$8 ==.
                           2279 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:628: TxRx_Count = 0;
                           2280 ;	genAssign
   0472 75 2C 00           2281 	mov	_TxRx_Count,#0x00
   0475 02 05 54           2282 	ljmp	00155$
   0478                    2283 00123$:
                    0397   2284 	C$TSIPMon.c$630$4$9 ==.
                           2285 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:630: TxRx_State = WAIT_FOR_END_MSG;
                           2286 ;	genAssign
   0478 75 2B 05           2287 	mov	_TxRx_State,#0x05
                    039A   2288 	C$TSIPMon.c$631$4$9 ==.
                           2289 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:631: TxRxBuf[TxRx_Count++] = tchar;
                           2290 ;	genAssign
   047B AB 2C              2291 	mov	r3,_TxRx_Count
                           2292 ;	genPlus
                           2293 ;     genPlusIncr
   047D 05 2C              2294 	inc	_TxRx_Count
                           2295 ;	genPlus
                           2296 ;	Peephole 236.g	used r3 instead of ar3
   047F EB                 2297 	mov	a,r3
   0480 24 17              2298 	add	a,#_TxRxBuf
   0482 F5 82              2299 	mov	dpl,a
                           2300 ;	Peephole 181	changed mov to clr
   0484 E4                 2301 	clr	a
   0485 34 00              2302 	addc	a,#(_TxRxBuf >> 8)
   0487 F5 83              2303 	mov	dph,a
                           2304 ;	genPointerSet
                           2305 ;     genFarPointerSet
   0489 EA                 2306 	mov	a,r2
   048A F0                 2307 	movx	@dptr,a
                    03AA   2308 	C$TSIPMon.c$633$3$4 ==.
                           2309 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:633: break;
   048B 02 05 54           2310 	ljmp	00155$
                    03AD   2311 	C$TSIPMon.c$635$3$4 ==.
                           2312 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:635: case WAIT_FOR_END_MSG:
   048E                    2313 00126$:
                    03AD   2314 	C$TSIPMon.c$636$3$4 ==.
                           2315 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:636: if( tchar == DLE && TxRxBuf[TxRx_Count-1] == DLE && !bEvenDLE ){
                           2316 ;	genCmpEq
                           2317 ;	gencjneshort
                           2318 ;	Peephole 112.b	changed ljmp to sjmp
                           2319 ;	Peephole 198.b	optimized misc jump sequence
   048E BA 10 19           2320 	cjne	r2,#0x10,00133$
                           2321 ;	Peephole 200.b	removed redundant sjmp
                           2322 ;	Peephole 300	removed redundant label 00197$
                           2323 ;	Peephole 300	removed redundant label 00198$
                           2324 ;	genMinus
                           2325 ;	genMinusDec
   0491 E5 2C              2326 	mov	a,_TxRx_Count
   0493 14                 2327 	dec	a
                           2328 ;	genPlus
   0494 24 17              2329 	add	a,#_TxRxBuf
   0496 F5 82              2330 	mov	dpl,a
                           2331 ;	Peephole 240	use clr instead of addc a,#0
   0498 E4                 2332 	clr	a
   0499 34 00              2333 	addc	a,#(_TxRxBuf >> 8)
   049B F5 83              2334 	mov	dph,a
                           2335 ;	genPointerGet
                           2336 ;	genFarPointerGet
   049D E0                 2337 	movx	a,@dptr
   049E FB                 2338 	mov	r3,a
                           2339 ;	genCmpEq
                           2340 ;	gencjneshort
                           2341 ;	Peephole 112.b	changed ljmp to sjmp
                           2342 ;	Peephole 198.b	optimized misc jump sequence
   049F BB 10 08           2343 	cjne	r3,#0x10,00133$
                           2344 ;	Peephole 200.b	removed redundant sjmp
                           2345 ;	Peephole 300	removed redundant label 00199$
                           2346 ;	Peephole 300	removed redundant label 00200$
                           2347 ;	genIfx
                           2348 ;	genIfxJump
                           2349 ;	Peephole 108.e	removed ljmp by inverse jump logic
   04A2 20 07 05           2350 	jb	_SioIntService_bEvenDLE_1_1,00133$
                           2351 ;	Peephole 300	removed redundant label 00201$
                    03C4   2352 	C$TSIPMon.c$638$4$10 ==.
                           2353 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:638: bEvenDLE = TRUE;
                           2354 ;	genAssign
   04A5 D2 07              2355 	setb	_SioIntService_bEvenDLE_1_1
   04A7 02 05 54           2356 	ljmp	00155$
   04AA                    2357 00133$:
                    03C9   2358 	C$TSIPMon.c$639$3$4 ==.
                           2359 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:639: }else if( tchar == ETX && TxRxBuf[TxRx_Count-1] == DLE && !bEvenDLE ){
                           2360 ;	genCmpEq
                           2361 ;	gencjneshort
                           2362 ;	Peephole 112.b	changed ljmp to sjmp
                           2363 ;	Peephole 198.b	optimized misc jump sequence
   04AA BA 03 29           2364 	cjne	r2,#0x03,00128$
                           2365 ;	Peephole 200.b	removed redundant sjmp
                           2366 ;	Peephole 300	removed redundant label 00202$
                           2367 ;	Peephole 300	removed redundant label 00203$
                           2368 ;	genMinus
                           2369 ;	genMinusDec
   04AD E5 2C              2370 	mov	a,_TxRx_Count
   04AF 14                 2371 	dec	a
                           2372 ;	genPlus
   04B0 24 17              2373 	add	a,#_TxRxBuf
   04B2 F5 82              2374 	mov	dpl,a
                           2375 ;	Peephole 240	use clr instead of addc a,#0
   04B4 E4                 2376 	clr	a
   04B5 34 00              2377 	addc	a,#(_TxRxBuf >> 8)
   04B7 F5 83              2378 	mov	dph,a
                           2379 ;	genPointerGet
                           2380 ;	genFarPointerGet
   04B9 E0                 2381 	movx	a,@dptr
   04BA FB                 2382 	mov	r3,a
                           2383 ;	genCmpEq
                           2384 ;	gencjneshort
                           2385 ;	Peephole 112.b	changed ljmp to sjmp
                           2386 ;	Peephole 198.b	optimized misc jump sequence
   04BB BB 10 18           2387 	cjne	r3,#0x10,00128$
                           2388 ;	Peephole 200.b	removed redundant sjmp
                           2389 ;	Peephole 300	removed redundant label 00204$
                           2390 ;	Peephole 300	removed redundant label 00205$
                           2391 ;	genIfx
                           2392 ;	genIfxJump
                           2393 ;	Peephole 108.e	removed ljmp by inverse jump logic
   04BE 20 07 15           2394 	jb	_SioIntService_bEvenDLE_1_1,00128$
                           2395 ;	Peephole 300	removed redundant label 00206$
                    03E0   2396 	C$TSIPMon.c$642$4$11 ==.
                           2397 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:642: Rx_Pending = TRUE;
                           2398 ;	genAssign
   04C1 D2 00              2399 	setb	_Rx_Pending
                    03E2   2400 	C$TSIPMon.c$643$4$11 ==.
                           2401 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:643: TxRxBuf[TxRx_Count] = '\0';
                           2402 ;	genPlus
   04C3 E5 2C              2403 	mov	a,_TxRx_Count
   04C5 24 17              2404 	add	a,#_TxRxBuf
   04C7 F5 82              2405 	mov	dpl,a
                           2406 ;	Peephole 181	changed mov to clr
   04C9 E4                 2407 	clr	a
   04CA 34 00              2408 	addc	a,#(_TxRxBuf >> 8)
   04CC F5 83              2409 	mov	dph,a
                           2410 ;	genPointerSet
                           2411 ;     genFarPointerSet
                           2412 ;	Peephole 181	changed mov to clr
   04CE E4                 2413 	clr	a
   04CF F0                 2414 	movx	@dptr,a
                    03EF   2415 	C$TSIPMon.c$644$4$11 ==.
                           2416 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:644: TxRx_State = WAIT_FOR_DLE;
                           2417 ;	genAssign
   04D0 75 2B 03           2418 	mov	_TxRx_State,#0x03
   04D3 02 05 54           2419 	ljmp	00155$
   04D6                    2420 00128$:
                    03F5   2421 	C$TSIPMon.c$648$4$12 ==.
                           2422 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:648: TxRxBuf[TxRx_Count++] = tchar;
                           2423 ;	genAssign
   04D6 AB 2C              2424 	mov	r3,_TxRx_Count
                           2425 ;	genPlus
                           2426 ;     genPlusIncr
   04D8 05 2C              2427 	inc	_TxRx_Count
                           2428 ;	genPlus
                           2429 ;	Peephole 236.g	used r3 instead of ar3
   04DA EB                 2430 	mov	a,r3
   04DB 24 17              2431 	add	a,#_TxRxBuf
   04DD F5 82              2432 	mov	dpl,a
                           2433 ;	Peephole 181	changed mov to clr
   04DF E4                 2434 	clr	a
   04E0 34 00              2435 	addc	a,#(_TxRxBuf >> 8)
   04E2 F5 83              2436 	mov	dph,a
                           2437 ;	genPointerSet
                           2438 ;     genFarPointerSet
   04E4 EA                 2439 	mov	a,r2
   04E5 F0                 2440 	movx	@dptr,a
                    0405   2441 	C$TSIPMon.c$649$4$12 ==.
                           2442 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:649: bEvenDLE = FALSE;
                           2443 ;	genAssign
   04E6 C2 07              2444 	clr	_SioIntService_bEvenDLE_1_1
                    0407   2445 	C$TSIPMon.c$651$3$4 ==.
                           2446 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:651: break;
                    0407   2447 	C$TSIPMon.c$653$3$4 ==.
                           2448 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:653: default:
                           2449 ;	Peephole 112.b	changed ljmp to sjmp
   04E8 80 6A              2450 	sjmp	00155$
   04EA                    2451 00137$:
                    0409   2452 	C$TSIPMon.c$654$3$4 ==.
                           2453 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:654: TxRx_State = WAIT_FOR_START;
                           2454 ;	genAssign
   04EA 75 2B 00           2455 	mov	_TxRx_State,#0x00
                    040C   2456 	C$TSIPMon.c$656$1$1 ==.
                           2457 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:656: }
                           2458 ;	Peephole 112.b	changed ljmp to sjmp
   04ED 80 65              2459 	sjmp	00155$
   04EF                    2460 00154$:
                    040E   2461 	C$TSIPMon.c$660$2$13 ==.
                           2462 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:660: if( TI0 ){
                           2463 ;	genIfx
                           2464 ;	genIfxJump
                           2465 ;	Peephole 108.d	removed ljmp by inverse jump logic
                    040E   2466 	C$TSIPMon.c$661$3$14 ==.
                           2467 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:661: TI0 = FALSE;
                           2468 ;	genAssign
                           2469 ;	Peephole 250.a	using atomic test and clear
   04EF 10 99 02           2470 	jbc	_TI0,00207$
   04F2 80 60              2471 	sjmp	00155$
   04F4                    2472 00207$:
                    0413   2473 	C$TSIPMon.c$663$3$14 ==.
                           2474 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:663: if( !Tx_In_Progress ){
                           2475 ;	genIfx
                           2476 ;	genIfxJump
                           2477 ;	Peephole 108.e	removed ljmp by inverse jump logic
   04F4 20 01 08           2478 	jb	_Tx_In_Progress,00140$
                           2479 ;	Peephole 300	removed redundant label 00208$
                    0416   2480 	C$TSIPMon.c$664$4$15 ==.
                           2481 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:664: RI0 = FALSE;
                           2482 ;	genAssign
   04F7 C2 98              2483 	clr	_RI0
                    0418   2484 	C$TSIPMon.c$665$4$15 ==.
                           2485 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:665: Tx_In_Progress = FALSE;
                           2486 ;	genAssign
   04F9 C2 01              2487 	clr	_Tx_In_Progress
                    041A   2488 	C$TSIPMon.c$666$4$15 ==.
                           2489 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:666: Rx_Pending = FALSE;
                           2490 ;	genAssign
   04FB C2 00              2491 	clr	_Rx_Pending
                    041C   2492 	C$TSIPMon.c$667$4$15 ==.
                           2493 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:667: return;
                           2494 ;	genRet
                           2495 ;	Peephole 112.b	changed ljmp to sjmp
   04FD 80 55              2496 	sjmp	00156$
   04FF                    2497 00140$:
                    041E   2498 	C$TSIPMon.c$669$3$14 ==.
                           2499 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:669: switch( TxRx_State ){
                           2500 ;	genCmpEq
                           2501 ;	gencjneshort
   04FF E5 2B              2502 	mov	a,_TxRx_State
   0501 B4 06 02           2503 	cjne	a,#0x06,00209$
                           2504 ;	Peephole 112.b	changed ljmp to sjmp
   0504 80 07              2505 	sjmp	00141$
   0506                    2506 00209$:
                           2507 ;	genCmpEq
                           2508 ;	gencjneshort
   0506 E5 2B              2509 	mov	a,_TxRx_State
                           2510 ;	Peephole 112.b	changed ljmp to sjmp
                    0427   2511 	C$TSIPMon.c$671$4$16 ==.
                           2512 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:671: case SEND_HDR:
                           2513 ;	Peephole 112.b	changed ljmp to sjmp
                           2514 ;	Peephole 198.b	optimized misc jump sequence
   0508 B4 07 49           2515 	cjne	a,#0x07,00155$
   050B 80 17              2516 	sjmp	00142$
                           2517 ;	Peephole 300	removed redundant label 00210$
   050D                    2518 00141$:
                    042C   2519 	C$TSIPMon.c$672$4$16 ==.
                           2520 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:672: SBUF0 = DLE;
                           2521 ;	genAssign
   050D 75 99 10           2522 	mov	_SBUF0,#0x10
                    042F   2523 	C$TSIPMon.c$673$4$16 ==.
                           2524 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:673: TxRx_State = SEND_MSG;
                           2525 ;	genAssign
   0510 75 2B 07           2526 	mov	_TxRx_State,#0x07
                    0432   2527 	C$TSIPMon.c$674$4$16 ==.
                           2528 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:674: TxRx_Count--;
                           2529 ;	genMinus
                           2530 ;	genMinusDec
   0513 15 2C              2531 	dec	_TxRx_Count
                    0434   2532 	C$TSIPMon.c$675$4$16 ==.
                           2533 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:675: p_TxRx_Buf = TxRxBuf+1;
                           2534 ;	genPlus
                           2535 ;     genPlusIncr
   0515 74 01              2536 	mov	a,#0x01
   0517 24 17              2537 	add	a,#_TxRxBuf
   0519 F5 31              2538 	mov	_p_TxRx_Buf,a
                           2539 ;	Peephole 181	changed mov to clr
   051B E4                 2540 	clr	a
   051C 34 00              2541 	addc	a,#(_TxRxBuf >> 8)
   051E F5 32              2542 	mov	(_p_TxRx_Buf + 1),a
                    043F   2543 	C$TSIPMon.c$676$4$16 ==.
                           2544 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:676: bEvenDLE = FALSE;
                           2545 ;	genAssign
   0520 C2 07              2546 	clr	_SioIntService_bEvenDLE_1_1
                    0441   2547 	C$TSIPMon.c$677$4$16 ==.
                           2548 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:677: break;
                    0441   2549 	C$TSIPMon.c$679$4$16 ==.
                           2550 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:679: case SEND_MSG:
                           2551 ;	Peephole 112.b	changed ljmp to sjmp
   0522 80 30              2552 	sjmp	00155$
   0524                    2553 00142$:
                    0443   2554 	C$TSIPMon.c$680$4$16 ==.
                           2555 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:680: tchar = *p_TxRx_Buf;
                           2556 ;	genAssign
   0524 85 31 82           2557 	mov	dpl,_p_TxRx_Buf
   0527 85 32 83           2558 	mov	dph,(_p_TxRx_Buf + 1)
                           2559 ;	genPointerGet
                           2560 ;	genFarPointerGet
   052A E0                 2561 	movx	a,@dptr
   052B FA                 2562 	mov	r2,a
                    044B   2563 	C$TSIPMon.c$681$4$16 ==.
                           2564 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:681: SBUF0 = tchar;
                           2565 ;	genAssign
   052C 8A 99              2566 	mov	_SBUF0,r2
                    044D   2567 	C$TSIPMon.c$682$4$16 ==.
                           2568 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:682: if( tchar == DLE && !bEvenDLE && TxRx_Count > 1 ){
                           2569 ;	genCmpEq
                           2570 ;	gencjneshort
                           2571 ;	Peephole 112.b	changed ljmp to sjmp
                           2572 ;	Peephole 198.b	optimized misc jump sequence
   052E BA 10 0D           2573 	cjne	r2,#0x10,00144$
                           2574 ;	Peephole 200.b	removed redundant sjmp
                           2575 ;	Peephole 300	removed redundant label 00211$
                           2576 ;	Peephole 300	removed redundant label 00212$
                           2577 ;	genIfx
                           2578 ;	genIfxJump
                           2579 ;	Peephole 108.e	removed ljmp by inverse jump logic
   0531 20 07 0A           2580 	jb	_SioIntService_bEvenDLE_1_1,00144$
                           2581 ;	Peephole 300	removed redundant label 00213$
                           2582 ;	genCmpGt
                           2583 ;	genCmp
                           2584 ;	genIfxJump
                           2585 ;	Peephole 108.a	removed ljmp by inverse jump logic
                           2586 ;	Peephole 132.b	optimized genCmpGt by inverse logic (acc differs)
   0534 E5 2C              2587 	mov	a,_TxRx_Count
   0536 24 FE              2588 	add	a,#0xff - 0x01
   0538 50 04              2589 	jnc	00144$
                           2590 ;	Peephole 300	removed redundant label 00214$
                    0459   2591 	C$TSIPMon.c$684$5$17 ==.
                           2592 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:684: bEvenDLE = TRUE;
                           2593 ;	genAssign
   053A D2 07              2594 	setb	_SioIntService_bEvenDLE_1_1
                    045B   2595 	C$TSIPMon.c$685$5$17 ==.
                           2596 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:685: return;
                           2597 ;	genRet
                           2598 ;	Peephole 112.b	changed ljmp to sjmp
   053C 80 16              2599 	sjmp	00156$
   053E                    2600 00144$:
                    045D   2601 	C$TSIPMon.c$687$4$16 ==.
                           2602 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:687: p_TxRx_Buf++;
                           2603 ;	genPlus
                           2604 ;     genPlusIncr
   053E 05 31              2605 	inc	_p_TxRx_Buf
   0540 E4                 2606 	clr	a
   0541 B5 31 02           2607 	cjne	a,_p_TxRx_Buf,00215$
   0544 05 32              2608 	inc	(_p_TxRx_Buf + 1)
   0546                    2609 00215$:
                    0465   2610 	C$TSIPMon.c$688$4$16 ==.
                           2611 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:688: bEvenDLE = FALSE;
                           2612 ;	genAssign
   0546 C2 07              2613 	clr	_SioIntService_bEvenDLE_1_1
                    0467   2614 	C$TSIPMon.c$689$4$16 ==.
                           2615 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:689: if( TxRx_Count-- == 0 ){
                           2616 ;	genAssign
   0548 AA 2C              2617 	mov	r2,_TxRx_Count
                           2618 ;	genMinus
                           2619 ;	genMinusDec
   054A 15 2C              2620 	dec	_TxRx_Count
                           2621 ;	genIfx
   054C EA                 2622 	mov	a,r2
                           2623 ;	genIfxJump
                           2624 ;	Peephole 108.b	removed ljmp by inverse jump logic
   054D 70 05              2625 	jnz	00155$
                           2626 ;	Peephole 300	removed redundant label 00216$
                    046E   2627 	C$TSIPMon.c$690$5$18 ==.
                           2628 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:690: Tx_In_Progress = FALSE;
                           2629 ;	genAssign
   054F C2 01              2630 	clr	_Tx_In_Progress
                    0470   2631 	C$TSIPMon.c$691$5$18 ==.
                           2632 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:691: TxRx_Count = 0;
                           2633 ;	genAssign
   0551 75 2C 00           2634 	mov	_TxRx_Count,#0x00
                    0473   2635 	C$TSIPMon.c$697$1$1 ==.
                           2636 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:697: }
   0554                    2637 00155$:
                    0473   2638 	C$TSIPMon.c$701$1$1 ==.
                           2639 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:701: return;
                           2640 ;	genRet
   0554                    2641 00156$:
   0554 D0 D0              2642 	pop	psw
   0556 D0 83              2643 	pop	dph
   0558 D0 82              2644 	pop	dpl
   055A D0 E0              2645 	pop	acc
                    047B   2646 	C$TSIPMon.c$704$1$1 ==.
                    047B   2647 	XG$SioIntService$0$0 ==.
   055C 32                 2648 	reti
                           2649 ;	eliminated unneeded push/pop b
                           2650 ;------------------------------------------------------------
                           2651 ;Allocation info for local variables in function 'ProcessRxMsg'
                           2652 ;------------------------------------------------------------
                           2653 ;i                         Allocated to registers r4 
                           2654 ;id                        Allocated to registers r2 
                           2655 ;id2                       Allocated to registers r3 
                           2656 ;pBuf                      Allocated with name '_ProcessRxMsg_pBuf_1_1'
                           2657 ;------------------------------------------------------------
                    047C   2658 	G$ProcessRxMsg$0$0 ==.
                    047C   2659 	C$TSIPMon.c$709$1$1 ==.
                           2660 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:709: void ProcessRxMsg( void ){
                           2661 ;	-----------------------------------------
                           2662 ;	 function ProcessRxMsg
                           2663 ;	-----------------------------------------
   055D                    2664 _ProcessRxMsg:
                    0002   2665 	ar2 = 0x02
                    0003   2666 	ar3 = 0x03
                    0004   2667 	ar4 = 0x04
                    0005   2668 	ar5 = 0x05
                    0006   2669 	ar6 = 0x06
                    0007   2670 	ar7 = 0x07
                    0000   2671 	ar0 = 0x00
                    0001   2672 	ar1 = 0x01
                    047C   2673 	C$TSIPMon.c$715$1$1 ==.
                           2674 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:715: id = TxRxBuf[IO_BUF_ID_INDEX];
                           2675 ;	genPointerGet
                           2676 ;	genFarPointerGet
   055D 90 00 18           2677 	mov	dptr,#(_TxRxBuf + 0x0001)
   0560 E0                 2678 	movx	a,@dptr
   0561 FA                 2679 	mov	r2,a
                    0481   2680 	C$TSIPMon.c$716$1$1 ==.
                           2681 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:716: id2 = TxRxBuf[IO_BUF_ID2_INDEX];
                           2682 ;	genPointerGet
                           2683 ;	genFarPointerGet
   0562 90 00 19           2684 	mov	dptr,#(_TxRxBuf + 0x0002)
   0565 E0                 2685 	movx	a,@dptr
   0566 FB                 2686 	mov	r3,a
                    0486   2687 	C$TSIPMon.c$717$1$1 ==.
                           2688 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:717: for( i=2; i<TxRx_Count; i++)
                           2689 ;	genAssign
   0567 7C 02              2690 	mov	r4,#0x02
   0569                    2691 00108$:
                           2692 ;	genCmpLt
                           2693 ;	genCmp
   0569 C3                 2694 	clr	c
   056A EC                 2695 	mov	a,r4
   056B 95 2C              2696 	subb	a,_TxRx_Count
                           2697 ;	genIfxJump
                           2698 ;	Peephole 108.a	removed ljmp by inverse jump logic
   056D 50 1E              2699 	jnc	00111$
                           2700 ;	Peephole 300	removed redundant label 00120$
                    048E   2701 	C$TSIPMon.c$718$1$1 ==.
                           2702 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:718: pBuf[i-2] = TxRxBuf[i];
                           2703 ;	genMinus
                           2704 ;	genMinusDec
   056F EC                 2705 	mov	a,r4
   0570 24 FE              2706 	add	a,#0xfe
                           2707 ;	genPlus
   0572 24 6C              2708 	add	a,#_ProcessRxMsg_pBuf_1_1
   0574 FD                 2709 	mov	r5,a
                           2710 ;	Peephole 240	use clr instead of addc a,#0
   0575 E4                 2711 	clr	a
   0576 34 00              2712 	addc	a,#(_ProcessRxMsg_pBuf_1_1 >> 8)
   0578 FE                 2713 	mov	r6,a
                           2714 ;	genPlus
                           2715 ;	Peephole 236.g	used r4 instead of ar4
   0579 EC                 2716 	mov	a,r4
   057A 24 17              2717 	add	a,#_TxRxBuf
   057C F5 82              2718 	mov	dpl,a
                           2719 ;	Peephole 181	changed mov to clr
   057E E4                 2720 	clr	a
   057F 34 00              2721 	addc	a,#(_TxRxBuf >> 8)
   0581 F5 83              2722 	mov	dph,a
                           2723 ;	genPointerGet
                           2724 ;	genFarPointerGet
   0583 E0                 2725 	movx	a,@dptr
                           2726 ;	genPointerSet
                           2727 ;     genFarPointerSet
   0584 FF                 2728 	mov	r7,a
   0585 8D 82              2729 	mov	dpl,r5
   0587 8E 83              2730 	mov	dph,r6
                           2731 ;	Peephole 136	removed redundant move
   0589 F0                 2732 	movx	@dptr,a
                    04A9   2733 	C$TSIPMon.c$717$1$1 ==.
                           2734 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:717: for( i=2; i<TxRx_Count; i++)
                           2735 ;	genPlus
                           2736 ;     genPlusIncr
   058A 0C                 2737 	inc	r4
                           2738 ;	Peephole 112.b	changed ljmp to sjmp
   058B 80 DC              2739 	sjmp	00108$
   058D                    2740 00111$:
                    04AC   2741 	C$TSIPMon.c$719$1$1 ==.
                           2742 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:719: Rx_Pending = FALSE;
                           2743 ;	genAssign
   058D C2 00              2744 	clr	_Rx_Pending
                    04AE   2745 	C$TSIPMon.c$721$1$1 ==.
                           2746 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:721: switch( id ){
                           2747 ;	genCmpEq
                           2748 ;	gencjneshort
                           2749 ;	Peephole 112.b	changed ljmp to sjmp
                           2750 ;	Peephole 198.b	optimized misc jump sequence
   058F BA 8F 16           2751 	cjne	r2,#0x8F,00112$
                           2752 ;	Peephole 200.b	removed redundant sjmp
                           2753 ;	Peephole 300	removed redundant label 00121$
                           2754 ;	Peephole 300	removed redundant label 00122$
                    04B1   2755 	C$TSIPMon.c$723$2$2 ==.
                           2756 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:723: switch( id2 ){
                           2757 ;	genCmpEq
                           2758 ;	gencjneshort
   0592 BB AB 02           2759 	cjne	r3,#0xAB,00123$
                           2760 ;	Peephole 112.b	changed ljmp to sjmp
   0595 80 05              2761 	sjmp	00102$
   0597                    2762 00123$:
                           2763 ;	genCmpEq
                           2764 ;	gencjneshort
                           2765 ;	Peephole 112.b	changed ljmp to sjmp
                    04B6   2766 	C$TSIPMon.c$724$3$3 ==.
                           2767 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:724: case PRIMARY_TIMING_PCKT:
                           2768 ;	Peephole 112.b	changed ljmp to sjmp
                           2769 ;	Peephole 198.b	optimized misc jump sequence
   0597 BB AC 0E           2770 	cjne	r3,#0xAC,00112$
   059A 80 06              2771 	sjmp	00103$
                           2772 ;	Peephole 300	removed redundant label 00124$
   059C                    2773 00102$:
                    04BB   2774 	C$TSIPMon.c$725$3$3 ==.
                           2775 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:725: PrimaryTiming( pBuf );
                           2776 ;	genCall
                           2777 ;	Peephole 182.a	used 16 bit load of DPTR
   059C 90 00 6C           2778 	mov	dptr,#_ProcessRxMsg_pBuf_1_1
                    04BE   2779 	C$TSIPMon.c$726$3$3 ==.
                           2780 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:726: break;
                    04BE   2781 	C$TSIPMon.c$728$3$3 ==.
                           2782 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:728: case SUPPLEMENTAL_TIMING_PCKT:
                           2783 ;	Peephole 112.b	changed ljmp to sjmp
                           2784 ;	Peephole 251.b	replaced sjmp to ret with ret
                           2785 ;	Peephole 253.a	replaced lcall/ret with ljmp
   059F 02 05 A9           2786 	ljmp	_PrimaryTiming
   05A2                    2787 00103$:
                    04C1   2788 	C$TSIPMon.c$729$3$3 ==.
                           2789 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:729: SupplementalTiming( pBuf );
                           2790 ;	genCall
                           2791 ;	Peephole 182.a	used 16 bit load of DPTR
   05A2 90 00 6C           2792 	mov	dptr,#_ProcessRxMsg_pBuf_1_1
                    04C4   2793 	C$TSIPMon.c$737$1$1 ==.
                           2794 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:737: }
                    04C4   2795 	C$TSIPMon.c$739$1$1 ==.
                    04C4   2796 	XG$ProcessRxMsg$0$0 ==.
                           2797 ;	Peephole 253.c	replaced lcall with ljmp
   05A5 02 08 37           2798 	ljmp	_SupplementalTiming
   05A8                    2799 00112$:
   05A8 22                 2800 	ret
                           2801 ;------------------------------------------------------------
                           2802 ;Allocation info for local variables in function 'PrimaryTiming'
                           2803 ;------------------------------------------------------------
                           2804 ;RxBuf                     Allocated to registers r2 r3 
                           2805 ;sec                       Allocated with name '_PrimaryTiming_sec_1_1'
                           2806 ;min                       Allocated with name '_PrimaryTiming_min_1_1'
                           2807 ;hr                        Allocated to registers r7 
                           2808 ;dom                       Allocated with name '_PrimaryTiming_dom_1_1'
                           2809 ;mo                        Allocated to registers r5 
                           2810 ;y                         Allocated to registers r2 
                           2811 ;yr                        Allocated with name '_PrimaryTiming_yr_1_1'
                           2812 ;ctz                       Allocated to registers r4 
                           2813 ;------------------------------------------------------------
                    04C8   2814 	G$PrimaryTiming$0$0 ==.
                    04C8   2815 	C$TSIPMon.c$746$1$1 ==.
                           2816 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:746: void PrimaryTiming( uchar TXRX_STORAGE_CLASS *RxBuf ){
                           2817 ;	-----------------------------------------
                           2818 ;	 function PrimaryTiming
                           2819 ;	-----------------------------------------
   05A9                    2820 _PrimaryTiming:
                           2821 ;	genReceive
   05A9 AA 82              2822 	mov	r2,dpl
   05AB AB 83              2823 	mov	r3,dph
                    04CC   2824 	C$TSIPMon.c$753$1$1 ==.
                           2825 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:753: ctz = tz;
                           2826 ;	genAssign
   05AD AC 2D              2827 	mov	r4,_tz
                    04CE   2828 	C$TSIPMon.c$755$1$1 ==.
                           2829 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:755: yr.b.hi = *(RxBuf+7);
                           2830 ;	genPlus
                           2831 ;     genPlusIncr
   05AF 74 07              2832 	mov	a,#0x07
                           2833 ;	Peephole 236.a	used r2 instead of ar2
   05B1 2A                 2834 	add	a,r2
   05B2 F5 82              2835 	mov	dpl,a
                           2836 ;	Peephole 181	changed mov to clr
   05B4 E4                 2837 	clr	a
                           2838 ;	Peephole 236.b	used r3 instead of ar3
   05B5 3B                 2839 	addc	a,r3
   05B6 F5 83              2840 	mov	dph,a
                           2841 ;	genPointerGet
                           2842 ;	genFarPointerGet
   05B8 E0                 2843 	movx	a,@dptr
   05B9 FD                 2844 	mov	r5,a
                           2845 ;	genPointerSet
                           2846 ;	genNearPointerSet
                           2847 ;	genDataPointerSet
   05BA 8D 37              2848 	mov	(_PrimaryTiming_yr_1_1 + 0x0001),r5
                    04DB   2849 	C$TSIPMon.c$756$1$1 ==.
                           2850 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:756: yr.b.lo = *(RxBuf+8);
                           2851 ;	genPlus
                           2852 ;     genPlusIncr
   05BC 74 08              2853 	mov	a,#0x08
                           2854 ;	Peephole 236.a	used r2 instead of ar2
   05BE 2A                 2855 	add	a,r2
   05BF F5 82              2856 	mov	dpl,a
                           2857 ;	Peephole 181	changed mov to clr
   05C1 E4                 2858 	clr	a
                           2859 ;	Peephole 236.b	used r3 instead of ar3
   05C2 3B                 2860 	addc	a,r3
   05C3 F5 83              2861 	mov	dph,a
                           2862 ;	genPointerGet
                           2863 ;	genFarPointerGet
   05C5 E0                 2864 	movx	a,@dptr
   05C6 FD                 2865 	mov	r5,a
                           2866 ;	genPointerSet
                           2867 ;	genNearPointerSet
                           2868 ;	genDataPointerSet
   05C7 8D 36              2869 	mov	_PrimaryTiming_yr_1_1,r5
                    04E8   2870 	C$TSIPMon.c$757$1$1 ==.
                           2871 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:757: gpsoffset = yr.i;
                           2872 ;	genAssign
                           2873 ;	genCast
   05C9 85 36 2E           2874 	mov	_gpsoffset,_PrimaryTiming_yr_1_1
                    04EB   2875 	C$TSIPMon.c$760$1$1 ==.
                           2876 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:760: sec = *(RxBuf+10);
                           2877 ;	genPlus
                           2878 ;     genPlusIncr
   05CC 74 0A              2879 	mov	a,#0x0A
                           2880 ;	Peephole 236.a	used r2 instead of ar2
   05CE 2A                 2881 	add	a,r2
   05CF F5 82              2882 	mov	dpl,a
                           2883 ;	Peephole 181	changed mov to clr
   05D1 E4                 2884 	clr	a
                           2885 ;	Peephole 236.b	used r3 instead of ar3
   05D2 3B                 2886 	addc	a,r3
   05D3 F5 83              2887 	mov	dph,a
                           2888 ;	genPointerGet
                           2889 ;	genFarPointerGet
   05D5 E0                 2890 	movx	a,@dptr
   05D6 F5 33              2891 	mov	_PrimaryTiming_sec_1_1,a
                    04F7   2892 	C$TSIPMon.c$762$1$1 ==.
                           2893 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:762: min = *(RxBuf+11);
                           2894 ;	genPlus
                           2895 ;     genPlusIncr
   05D8 74 0B              2896 	mov	a,#0x0B
                           2897 ;	Peephole 236.a	used r2 instead of ar2
   05DA 2A                 2898 	add	a,r2
   05DB F5 82              2899 	mov	dpl,a
                           2900 ;	Peephole 181	changed mov to clr
   05DD E4                 2901 	clr	a
                           2902 ;	Peephole 236.b	used r3 instead of ar3
   05DE 3B                 2903 	addc	a,r3
   05DF F5 83              2904 	mov	dph,a
                           2905 ;	genPointerGet
                           2906 ;	genFarPointerGet
   05E1 E0                 2907 	movx	a,@dptr
   05E2 F5 34              2908 	mov	_PrimaryTiming_min_1_1,a
                    0503   2909 	C$TSIPMon.c$764$1$1 ==.
                           2910 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:764: hr = *(RxBuf+12);
                           2911 ;	genPlus
                           2912 ;     genPlusIncr
   05E4 74 0C              2913 	mov	a,#0x0C
                           2914 ;	Peephole 236.a	used r2 instead of ar2
   05E6 2A                 2915 	add	a,r2
   05E7 F5 82              2916 	mov	dpl,a
                           2917 ;	Peephole 181	changed mov to clr
   05E9 E4                 2918 	clr	a
                           2919 ;	Peephole 236.b	used r3 instead of ar3
   05EA 3B                 2920 	addc	a,r3
   05EB F5 83              2921 	mov	dph,a
                           2922 ;	genPointerGet
                           2923 ;	genFarPointerGet
   05ED E0                 2924 	movx	a,@dptr
   05EE FF                 2925 	mov	r7,a
                    050E   2926 	C$TSIPMon.c$766$1$1 ==.
                           2927 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:766: dom = *(RxBuf+13);
                           2928 ;	genPlus
                           2929 ;     genPlusIncr
   05EF 74 0D              2930 	mov	a,#0x0D
                           2931 ;	Peephole 236.a	used r2 instead of ar2
   05F1 2A                 2932 	add	a,r2
   05F2 F5 82              2933 	mov	dpl,a
                           2934 ;	Peephole 181	changed mov to clr
   05F4 E4                 2935 	clr	a
                           2936 ;	Peephole 236.b	used r3 instead of ar3
   05F5 3B                 2937 	addc	a,r3
   05F6 F5 83              2938 	mov	dph,a
                           2939 ;	genPointerGet
                           2940 ;	genFarPointerGet
   05F8 E0                 2941 	movx	a,@dptr
   05F9 F5 35              2942 	mov	_PrimaryTiming_dom_1_1,a
                    051A   2943 	C$TSIPMon.c$768$1$1 ==.
                           2944 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:768: mo = (*(RxBuf+14)-1)*3;	// note: mo starts at 0 (January)
                           2945 ;	genPlus
                           2946 ;     genPlusIncr
   05FB 74 0E              2947 	mov	a,#0x0E
                           2948 ;	Peephole 236.a	used r2 instead of ar2
   05FD 2A                 2949 	add	a,r2
   05FE F5 82              2950 	mov	dpl,a
                           2951 ;	Peephole 181	changed mov to clr
   0600 E4                 2952 	clr	a
                           2953 ;	Peephole 236.b	used r3 instead of ar3
   0601 3B                 2954 	addc	a,r3
   0602 F5 83              2955 	mov	dph,a
                           2956 ;	genPointerGet
                           2957 ;	genFarPointerGet
   0604 E0                 2958 	movx	a,@dptr
                           2959 ;	genMinus
                           2960 ;	genMinusDec
   0605 FD                 2961 	mov	r5,a
                           2962 ;	Peephole 105	removed redundant mov
   0606 14                 2963 	dec	a
                           2964 ;	genMult
                           2965 ;	genMultOneByte
   0607 75 F0 03           2966 	mov	b,#0x03
   060A A4                 2967 	mul	ab
   060B FD                 2968 	mov	r5,a
                    052B   2969 	C$TSIPMon.c$770$1$1 ==.
                           2970 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:770: yr.b.hi = *(RxBuf+15);
                           2971 ;	genPlus
                           2972 ;     genPlusIncr
   060C 74 0F              2973 	mov	a,#0x0F
                           2974 ;	Peephole 236.a	used r2 instead of ar2
   060E 2A                 2975 	add	a,r2
   060F F5 82              2976 	mov	dpl,a
                           2977 ;	Peephole 181	changed mov to clr
   0611 E4                 2978 	clr	a
                           2979 ;	Peephole 236.b	used r3 instead of ar3
   0612 3B                 2980 	addc	a,r3
   0613 F5 83              2981 	mov	dph,a
                           2982 ;	genPointerGet
                           2983 ;	genFarPointerGet
   0615 E0                 2984 	movx	a,@dptr
   0616 FE                 2985 	mov	r6,a
                           2986 ;	genPointerSet
                           2987 ;	genNearPointerSet
                           2988 ;	genDataPointerSet
   0617 8E 37              2989 	mov	(_PrimaryTiming_yr_1_1 + 0x0001),r6
                    0538   2990 	C$TSIPMon.c$771$1$1 ==.
                           2991 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:771: yr.b.lo = *(RxBuf+16);
                           2992 ;	genPlus
                           2993 ;     genPlusIncr
   0619 74 10              2994 	mov	a,#0x10
                           2995 ;	Peephole 236.a	used r2 instead of ar2
   061B 2A                 2996 	add	a,r2
   061C F5 82              2997 	mov	dpl,a
                           2998 ;	Peephole 181	changed mov to clr
   061E E4                 2999 	clr	a
                           3000 ;	Peephole 236.b	used r3 instead of ar3
   061F 3B                 3001 	addc	a,r3
   0620 F5 83              3002 	mov	dph,a
                           3003 ;	genPointerGet
                           3004 ;	genFarPointerGet
   0622 E0                 3005 	movx	a,@dptr
                           3006 ;	genPointerSet
                           3007 ;	genNearPointerSet
                           3008 ;	genDataPointerSet
                    0542   3009 	C$TSIPMon.c$773$1$1 ==.
                           3010 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:773: y = yr.u - 2000;
                           3011 ;	genAssign
                           3012 ;	genCast
                           3013 ;	Peephole 177.a	removed redundant mov
                           3014 ;	genMinus
   0623 FA                 3015 	mov	r2,a
   0624 8A 36              3016 	mov	_PrimaryTiming_yr_1_1,r2
                           3017 ;	Peephole 177.d	removed redundant move
   0626 24 30              3018 	add	a,#0x30
   0628 FA                 3019 	mov	r2,a
                           3020 ;	genIfx
                           3021 ;	genIfxJump
   0629 30 86 03           3022 	jnb	_P0_6,00168$
   062C 02 06 C3           3023 	ljmp	00128$
   062F                    3024 00168$:
                    054E   3025 	C$TSIPMon.c$778$2$2 ==.
                           3026 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:778: sec -= gpsoffset;
                           3027 ;	genMinus
   062F E5 33              3028 	mov	a,_PrimaryTiming_sec_1_1
   0631 C3                 3029 	clr	c
   0632 95 2E              3030 	subb	a,_gpsoffset
                    0553   3031 	C$TSIPMon.c$779$2$2 ==.
                           3032 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:779: if( sec < 0 ){
                           3033 ;	genCmpLt
                           3034 ;	genCmp
   0634 F5 33              3035 	mov	_PrimaryTiming_sec_1_1,a
                           3036 ;	Peephole 105	removed redundant mov
                           3037 ;	genIfxJump
                           3038 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0636 30 E7 1D           3039 	jnb	acc.7,00106$
                           3040 ;	Peephole 300	removed redundant label 00169$
                    0558   3041 	C$TSIPMon.c$780$3$3 ==.
                           3042 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:780: sec += 60;
                           3043 ;	genPlus
                           3044 ;     genPlusIncr
   0639 74 3C              3045 	mov	a,#0x3C
   063B 25 33              3046 	add	a,_PrimaryTiming_sec_1_1
   063D F5 33              3047 	mov	_PrimaryTiming_sec_1_1,a
                    055E   3048 	C$TSIPMon.c$781$3$3 ==.
                           3049 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:781: min--;
                           3050 ;	genMinus
                           3051 ;	genMinusDec
   063F 15 34              3052 	dec	_PrimaryTiming_min_1_1
                    0560   3053 	C$TSIPMon.c$782$3$3 ==.
                           3054 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:782: if( min < 0 ){
                           3055 ;	genCmpLt
                           3056 ;	genCmp
   0641 E5 34              3057 	mov	a,_PrimaryTiming_min_1_1
                           3058 ;	genIfxJump
                           3059 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0643 30 E7 10           3060 	jnb	acc.7,00106$
                           3061 ;	Peephole 300	removed redundant label 00170$
                    0565   3062 	C$TSIPMon.c$783$4$4 ==.
                           3063 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:783: min += 60;
                           3064 ;	genPlus
                           3065 ;     genPlusIncr
   0646 74 3C              3066 	mov	a,#0x3C
   0648 25 34              3067 	add	a,_PrimaryTiming_min_1_1
   064A F5 34              3068 	mov	_PrimaryTiming_min_1_1,a
                    056B   3069 	C$TSIPMon.c$784$4$4 ==.
                           3070 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:784: hr--;
                           3071 ;	genMinus
                           3072 ;	genMinusDec
   064C 1F                 3073 	dec	r7
                    056C   3074 	C$TSIPMon.c$785$4$4 ==.
                           3075 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:785: if( hr < 0 ){
                           3076 ;	genCmpLt
                           3077 ;	genCmp
   064D EF                 3078 	mov	a,r7
                           3079 ;	genIfxJump
                           3080 ;	Peephole 108.d	removed ljmp by inverse jump logic
   064E 30 E7 05           3081 	jnb	acc.7,00106$
                           3082 ;	Peephole 300	removed redundant label 00171$
                    0570   3083 	C$TSIPMon.c$786$5$5 ==.
                           3084 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:786: hr += 24;
                           3085 ;	genPlus
                           3086 ;     genPlusIncr
   0651 74 18              3087 	mov	a,#0x18
                           3088 ;	Peephole 236.a	used r7 instead of ar7
   0653 2F                 3089 	add	a,r7
   0654 FF                 3090 	mov	r7,a
                    0574   3091 	C$TSIPMon.c$787$5$5 ==.
                           3092 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:787: ctz--;
                           3093 ;	genMinus
                           3094 ;	genMinusDec
   0655 1C                 3095 	dec	r4
   0656                    3096 00106$:
                    0575   3097 	C$TSIPMon.c$793$2$2 ==.
                           3098 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:793: if( ctz > 0 ){
                           3099 ;	genCmpGt
                           3100 ;	genCmp
   0656 C3                 3101 	clr	c
                           3102 ;	Peephole 159	avoided xrl during execution
   0657 74 80              3103 	mov	a,#(0x00 ^ 0x80)
   0659 8C F0              3104 	mov	b,r4
   065B 63 F0 80           3105 	xrl	b,#0x80
   065E 95 F0              3106 	subb	a,b
                           3107 ;	genIfxJump
                           3108 ;	Peephole 108.a	removed ljmp by inverse jump logic
   0660 50 38              3109 	jnc	00116$
                           3110 ;	Peephole 300	removed redundant label 00172$
                    0581   3111 	C$TSIPMon.c$794$3$6 ==.
                           3112 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:794: hr += ctz;
                           3113 ;	genPlus
                           3114 ;	Peephole 236.g	used r4 instead of ar4
   0662 EC                 3115 	mov	a,r4
                           3116 ;	Peephole 236.a	used r7 instead of ar7
   0663 2F                 3117 	add	a,r7
   0664 FF                 3118 	mov	r7,a
                           3119 ;	genIfx
                           3120 ;	genIfxJump
                           3121 ;	Peephole 108.e	removed ljmp by inverse jump logic
   0665 20 87 01           3122 	jb	_P0_7,00108$
                           3123 ;	Peephole 300	removed redundant label 00173$
                    0587   3124 	C$TSIPMon.c$796$3$6 ==.
                           3125 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:796: hr++;
                           3126 ;	genPlus
                           3127 ;     genPlusIncr
   0668 0F                 3128 	inc	r7
   0669                    3129 00108$:
                    0588   3130 	C$TSIPMon.c$797$3$6 ==.
                           3131 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:797: if( hr > 23 ){
                           3132 ;	genCmpGt
                           3133 ;	genCmp
   0669 C3                 3134 	clr	c
                           3135 ;	Peephole 159	avoided xrl during execution
   066A 74 97              3136 	mov	a,#(0x17 ^ 0x80)
   066C 8F F0              3137 	mov	b,r7
   066E 63 F0 80           3138 	xrl	b,#0x80
   0671 95 F0              3139 	subb	a,b
                           3140 ;	genIfxJump
                           3141 ;	Peephole 108.a	removed ljmp by inverse jump logic
   0673 50 25              3142 	jnc	00116$
                           3143 ;	Peephole 300	removed redundant label 00174$
                    0594   3144 	C$TSIPMon.c$798$4$7 ==.
                           3145 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:798: hr -= 24;
                           3146 ;	genMinus
   0675 EF                 3147 	mov	a,r7
   0676 24 E8              3148 	add	a,#0xe8
   0678 FF                 3149 	mov	r7,a
                    0598   3150 	C$TSIPMon.c$799$4$7 ==.
                           3151 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:799: dom++;
                           3152 ;	genPlus
                           3153 ;     genPlusIncr
   0679 05 35              3154 	inc	_PrimaryTiming_dom_1_1
                    059A   3155 	C$TSIPMon.c$800$4$7 ==.
                           3156 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:800: if( (uchar)dom > DIM[mo] ){
                           3157 ;	genAssign
   067B AB 35              3158 	mov	r3,_PrimaryTiming_dom_1_1
                           3159 ;	genPlus
                           3160 ;	Peephole 236.g	used r5 instead of ar5
   067D ED                 3161 	mov	a,r5
                           3162 ;	Peephole 181	changed mov to clr
                           3163 ;	genPointerGet
                           3164 ;	genCodePointerGet
                           3165 ;	Peephole 186.d	optimized movc sequence
   067E 90 14 F5           3166 	mov	dptr,#_DIM
   0681 93                 3167 	movc	a,@a+dptr
                           3168 ;	genCmpGt
                           3169 ;	genCmp
   0682 FE                 3170 	mov	r6,a
   0683 C3                 3171 	clr	c
                           3172 ;	Peephole 106	removed redundant mov
   0684 9B                 3173 	subb	a,r3
                           3174 ;	genIfxJump
                           3175 ;	Peephole 108.a	removed ljmp by inverse jump logic
   0685 50 13              3176 	jnc	00116$
                           3177 ;	Peephole 300	removed redundant label 00175$
                    05A6   3178 	C$TSIPMon.c$802$5$8 ==.
                           3179 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:802: dom = 0;
                           3180 ;	genAssign
   0687 75 35 00           3181 	mov	_PrimaryTiming_dom_1_1,#0x00
                    05A9   3182 	C$TSIPMon.c$803$5$8 ==.
                           3183 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:803: mo++;
                           3184 ;	genPlus
                           3185 ;     genPlusIncr
   068A 0D                 3186 	inc	r5
                    05AA   3187 	C$TSIPMon.c$804$5$8 ==.
                           3188 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:804: if( mo > 11 ){
                           3189 ;	genCmpGt
                           3190 ;	genCmp
   068B C3                 3191 	clr	c
                           3192 ;	Peephole 159	avoided xrl during execution
   068C 74 8B              3193 	mov	a,#(0x0B ^ 0x80)
   068E 8D F0              3194 	mov	b,r5
   0690 63 F0 80           3195 	xrl	b,#0x80
   0693 95 F0              3196 	subb	a,b
                           3197 ;	genIfxJump
                           3198 ;	Peephole 108.a	removed ljmp by inverse jump logic
   0695 50 03              3199 	jnc	00116$
                           3200 ;	Peephole 300	removed redundant label 00176$
                    05B6   3201 	C$TSIPMon.c$805$6$9 ==.
                           3202 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:805: mo = 0;
                           3203 ;	genAssign
   0697 7D 00              3204 	mov	r5,#0x00
                    05B8   3205 	C$TSIPMon.c$806$6$9 ==.
                           3206 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:806: y++;
                           3207 ;	genPlus
                           3208 ;     genPlusIncr
   0699 0A                 3209 	inc	r2
   069A                    3210 00116$:
                    05B9   3211 	C$TSIPMon.c$811$2$2 ==.
                           3212 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:811: if( ctz < 0 ){
                           3213 ;	genCmpLt
                           3214 ;	genCmp
   069A EC                 3215 	mov	a,r4
                           3216 ;	genIfxJump
                           3217 ;	Peephole 108.d	removed ljmp by inverse jump logic
   069B 30 E7 25           3218 	jnb	acc.7,00128$
                           3219 ;	Peephole 300	removed redundant label 00177$
                    05BD   3220 	C$TSIPMon.c$812$3$10 ==.
                           3221 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:812: hr += ctz;
                           3222 ;	genPlus
                           3223 ;	Peephole 236.g	used r4 instead of ar4
   069E EC                 3224 	mov	a,r4
                           3225 ;	Peephole 236.a	used r7 instead of ar7
   069F 2F                 3226 	add	a,r7
   06A0 FF                 3227 	mov	r7,a
                           3228 ;	genIfx
                           3229 ;	genIfxJump
                           3230 ;	Peephole 108.e	removed ljmp by inverse jump logic
   06A1 20 87 01           3231 	jb	_P0_7,00118$
                           3232 ;	Peephole 300	removed redundant label 00178$
                    05C3   3233 	C$TSIPMon.c$814$3$10 ==.
                           3234 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:814: hr++;
                           3235 ;	genPlus
                           3236 ;     genPlusIncr
   06A4 0F                 3237 	inc	r7
   06A5                    3238 00118$:
                    05C4   3239 	C$TSIPMon.c$815$3$10 ==.
                           3240 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:815: if( hr < 0 ){
                           3241 ;	genCmpLt
                           3242 ;	genCmp
   06A5 EF                 3243 	mov	a,r7
                           3244 ;	genIfxJump
                           3245 ;	Peephole 108.d	removed ljmp by inverse jump logic
   06A6 30 E7 1A           3246 	jnb	acc.7,00128$
                           3247 ;	Peephole 300	removed redundant label 00179$
                    05C8   3248 	C$TSIPMon.c$816$4$11 ==.
                           3249 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:816: hr += 24;
                           3250 ;	genPlus
                           3251 ;     genPlusIncr
   06A9 74 18              3252 	mov	a,#0x18
                           3253 ;	Peephole 236.a	used r7 instead of ar7
   06AB 2F                 3254 	add	a,r7
   06AC FF                 3255 	mov	r7,a
                    05CC   3256 	C$TSIPMon.c$817$4$11 ==.
                           3257 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:817: dom--;
                           3258 ;	genMinus
                           3259 ;	genMinusDec
   06AD 15 35              3260 	dec	_PrimaryTiming_dom_1_1
                    05CE   3261 	C$TSIPMon.c$818$4$11 ==.
                           3262 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:818: if( dom < 0 ){
                           3263 ;	genCmpLt
                           3264 ;	genCmp
   06AF E5 35              3265 	mov	a,_PrimaryTiming_dom_1_1
                           3266 ;	genIfxJump
                           3267 ;	Peephole 108.d	removed ljmp by inverse jump logic
   06B1 30 E7 0F           3268 	jnb	acc.7,00128$
                           3269 ;	Peephole 300	removed redundant label 00180$
                    05D3   3270 	C$TSIPMon.c$819$5$12 ==.
                           3271 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:819: mo--;
                           3272 ;	genMinus
                           3273 ;	genMinusDec
   06B4 1D                 3274 	dec	r5
                    05D4   3275 	C$TSIPMon.c$820$5$12 ==.
                           3276 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:820: if( mo < 0 ){
                           3277 ;	genCmpLt
                           3278 ;	genCmp
   06B5 ED                 3279 	mov	a,r5
                           3280 ;	genIfxJump
                           3281 ;	Peephole 108.d	removed ljmp by inverse jump logic
   06B6 30 E7 03           3282 	jnb	acc.7,00120$
                           3283 ;	Peephole 300	removed redundant label 00181$
                    05D8   3284 	C$TSIPMon.c$821$6$13 ==.
                           3285 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:821: mo = 12;
                           3286 ;	genAssign
   06B9 7D 0C              3287 	mov	r5,#0x0C
                    05DA   3288 	C$TSIPMon.c$822$6$13 ==.
                           3289 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:822: y--;
                           3290 ;	genMinus
                           3291 ;	genMinusDec
   06BB 1A                 3292 	dec	r2
   06BC                    3293 00120$:
                    05DB   3294 	C$TSIPMon.c$824$5$12 ==.
                           3295 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:824: dom = DIM[mo];
                           3296 ;	genPlus
                           3297 ;	Peephole 236.g	used r5 instead of ar5
   06BC ED                 3298 	mov	a,r5
                           3299 ;	Peephole 181	changed mov to clr
                           3300 ;	genPointerGet
                           3301 ;	genCodePointerGet
                           3302 ;	Peephole 186.d	optimized movc sequence
   06BD 90 14 F5           3303 	mov	dptr,#_DIM
   06C0 93                 3304 	movc	a,@a+dptr
   06C1 F5 35              3305 	mov	_PrimaryTiming_dom_1_1,a
   06C3                    3306 00128$:
                    05E2   3307 	C$TSIPMon.c$832$1$1 ==.
                           3308 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:832: UnsignedToAscii( (uint)sec, lcdbuf+6, 2 );
                           3309 ;	genCast
                           3310 ;	peephole 177.h	optimized mov sequence
   06C3 E5 33              3311 	mov	a,_PrimaryTiming_sec_1_1
   06C5 FB                 3312 	mov	r3,a
   06C6 33                 3313 	rlc	a
   06C7 95 E0              3314 	subb	a,acc
   06C9 FC                 3315 	mov	r4,a
                           3316 ;	genPlus
                           3317 ;     genPlusIncr
   06CA 74 06              3318 	mov	a,#0x06
   06CC 24 02              3319 	add	a,#_lcdbuf
   06CE F5 1B              3320 	mov	_UnsignedToAscii_PARM_2,a
                           3321 ;	Peephole 181	changed mov to clr
   06D0 E4                 3322 	clr	a
   06D1 34 00              3323 	addc	a,#(_lcdbuf >> 8)
   06D3 F5 1C              3324 	mov	(_UnsignedToAscii_PARM_2 + 1),a
                           3325 ;	genAssign
   06D5 75 1D 02           3326 	mov	_UnsignedToAscii_PARM_3,#0x02
                           3327 ;	genCall
   06D8 8B 82              3328 	mov	dpl,r3
   06DA 8C 83              3329 	mov	dph,r4
   06DC C0 02              3330 	push	ar2
   06DE C0 05              3331 	push	ar5
   06E0 C0 07              3332 	push	ar7
   06E2 12 0E FB           3333 	lcall	_UnsignedToAscii
   06E5 D0 07              3334 	pop	ar7
   06E7 D0 05              3335 	pop	ar5
   06E9 D0 02              3336 	pop	ar2
                    060A   3337 	C$TSIPMon.c$833$1$1 ==.
                           3338 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:833: if( lcdbuf[6] == ' ' ) lcdbuf[6] = '0';
                           3339 ;	genPointerGet
                           3340 ;	genFarPointerGet
   06EB 90 00 08           3341 	mov	dptr,#(_lcdbuf + 0x0006)
   06EE E0                 3342 	movx	a,@dptr
   06EF FB                 3343 	mov	r3,a
                           3344 ;	genCmpEq
                           3345 ;	gencjneshort
                           3346 ;	Peephole 112.b	changed ljmp to sjmp
                           3347 ;	Peephole 198.b	optimized misc jump sequence
   06F0 BB 20 06           3348 	cjne	r3,#0x20,00130$
                           3349 ;	Peephole 200.b	removed redundant sjmp
                           3350 ;	Peephole 300	removed redundant label 00182$
                           3351 ;	Peephole 300	removed redundant label 00183$
                           3352 ;	genPointerSet
                           3353 ;     genFarPointerSet
   06F3 90 00 08           3354 	mov	dptr,#(_lcdbuf + 0x0006)
   06F6 74 30              3355 	mov	a,#0x30
   06F8 F0                 3356 	movx	@dptr,a
   06F9                    3357 00130$:
                    0618   3358 	C$TSIPMon.c$834$1$1 ==.
                           3359 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:834: lcdbuf[8] = ' ';
                           3360 ;	genPointerSet
                           3361 ;     genFarPointerSet
   06F9 90 00 0A           3362 	mov	dptr,#(_lcdbuf + 0x0008)
   06FC 74 20              3363 	mov	a,#0x20
   06FE F0                 3364 	movx	@dptr,a
                    061E   3365 	C$TSIPMon.c$836$1$1 ==.
                           3366 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:836: UnsignedToAscii( (uint)min, lcdbuf+3, 2 );
                           3367 ;	genCast
                           3368 ;	peephole 177.h	optimized mov sequence
   06FF E5 34              3369 	mov	a,_PrimaryTiming_min_1_1
   0701 FE                 3370 	mov	r6,a
   0702 33                 3371 	rlc	a
   0703 95 E0              3372 	subb	a,acc
   0705 FB                 3373 	mov	r3,a
                           3374 ;	genPlus
                           3375 ;     genPlusIncr
   0706 74 03              3376 	mov	a,#0x03
   0708 24 02              3377 	add	a,#_lcdbuf
   070A F5 1B              3378 	mov	_UnsignedToAscii_PARM_2,a
                           3379 ;	Peephole 181	changed mov to clr
   070C E4                 3380 	clr	a
   070D 34 00              3381 	addc	a,#(_lcdbuf >> 8)
   070F F5 1C              3382 	mov	(_UnsignedToAscii_PARM_2 + 1),a
                           3383 ;	genAssign
   0711 75 1D 02           3384 	mov	_UnsignedToAscii_PARM_3,#0x02
                           3385 ;	genCall
   0714 8E 82              3386 	mov	dpl,r6
   0716 8B 83              3387 	mov	dph,r3
   0718 C0 02              3388 	push	ar2
   071A C0 05              3389 	push	ar5
   071C C0 07              3390 	push	ar7
   071E 12 0E FB           3391 	lcall	_UnsignedToAscii
   0721 D0 07              3392 	pop	ar7
   0723 D0 05              3393 	pop	ar5
   0725 D0 02              3394 	pop	ar2
                    0646   3395 	C$TSIPMon.c$837$1$1 ==.
                           3396 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:837: if( lcdbuf[3] == ' ' ) lcdbuf[3] = '0';
                           3397 ;	genPointerGet
                           3398 ;	genFarPointerGet
   0727 90 00 05           3399 	mov	dptr,#(_lcdbuf + 0x0003)
   072A E0                 3400 	movx	a,@dptr
   072B FB                 3401 	mov	r3,a
                           3402 ;	genCmpEq
                           3403 ;	gencjneshort
                           3404 ;	Peephole 112.b	changed ljmp to sjmp
                           3405 ;	Peephole 198.b	optimized misc jump sequence
   072C BB 20 06           3406 	cjne	r3,#0x20,00132$
                           3407 ;	Peephole 200.b	removed redundant sjmp
                           3408 ;	Peephole 300	removed redundant label 00184$
                           3409 ;	Peephole 300	removed redundant label 00185$
                           3410 ;	genPointerSet
                           3411 ;     genFarPointerSet
   072F 90 00 05           3412 	mov	dptr,#(_lcdbuf + 0x0003)
   0732 74 30              3413 	mov	a,#0x30
   0734 F0                 3414 	movx	@dptr,a
   0735                    3415 00132$:
                    0654   3416 	C$TSIPMon.c$838$1$1 ==.
                           3417 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:838: lcdbuf[5] = ':';
                           3418 ;	genPointerSet
                           3419 ;     genFarPointerSet
   0735 90 00 07           3420 	mov	dptr,#(_lcdbuf + 0x0005)
   0738 74 3A              3421 	mov	a,#0x3A
   073A F0                 3422 	movx	@dptr,a
                    065A   3423 	C$TSIPMon.c$840$1$1 ==.
                           3424 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:840: UnsignedToAscii( (uint)hr, lcdbuf, 2 );
                           3425 ;	genCast
   073B EF                 3426 	mov	a,r7
   073C 33                 3427 	rlc	a
   073D 95 E0              3428 	subb	a,acc
   073F FB                 3429 	mov	r3,a
                           3430 ;	genAssign
   0740 75 1B 02           3431 	mov	_UnsignedToAscii_PARM_2,#_lcdbuf
   0743 75 1C 00           3432 	mov	(_UnsignedToAscii_PARM_2 + 1),#(_lcdbuf >> 8)
                           3433 ;	genAssign
   0746 75 1D 02           3434 	mov	_UnsignedToAscii_PARM_3,#0x02
                           3435 ;	genCall
   0749 8F 82              3436 	mov	dpl,r7
   074B 8B 83              3437 	mov	dph,r3
   074D C0 02              3438 	push	ar2
   074F C0 05              3439 	push	ar5
   0751 12 0E FB           3440 	lcall	_UnsignedToAscii
   0754 D0 05              3441 	pop	ar5
   0756 D0 02              3442 	pop	ar2
                    0677   3443 	C$TSIPMon.c$841$1$1 ==.
                           3444 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:841: if( lcdbuf[0] == ' ' ) lcdbuf[0] = '0';
                           3445 ;	genPointerGet
                           3446 ;	genFarPointerGet
   0758 90 00 02           3447 	mov	dptr,#_lcdbuf
   075B E0                 3448 	movx	a,@dptr
   075C FB                 3449 	mov	r3,a
                           3450 ;	genCmpEq
                           3451 ;	gencjneshort
                           3452 ;	Peephole 112.b	changed ljmp to sjmp
                           3453 ;	Peephole 198.b	optimized misc jump sequence
   075D BB 20 06           3454 	cjne	r3,#0x20,00134$
                           3455 ;	Peephole 200.b	removed redundant sjmp
                           3456 ;	Peephole 300	removed redundant label 00186$
                           3457 ;	Peephole 300	removed redundant label 00187$
                           3458 ;	genPointerSet
                           3459 ;     genFarPointerSet
   0760 90 00 02           3460 	mov	dptr,#_lcdbuf
   0763 74 30              3461 	mov	a,#0x30
   0765 F0                 3462 	movx	@dptr,a
   0766                    3463 00134$:
                    0685   3464 	C$TSIPMon.c$842$1$1 ==.
                           3465 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:842: lcdbuf[2] = ':';
                           3466 ;	genPointerSet
                           3467 ;     genFarPointerSet
   0766 90 00 04           3468 	mov	dptr,#(_lcdbuf + 0x0002)
   0769 74 3A              3469 	mov	a,#0x3A
   076B F0                 3470 	movx	@dptr,a
                    068B   3471 	C$TSIPMon.c$845$1$1 ==.
                           3472 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:845: UnsignedToAscii( (uint)dom, lcdbuf+9, 2 );
                           3473 ;	genCast
                           3474 ;	peephole 177.h	optimized mov sequence
   076C E5 35              3475 	mov	a,_PrimaryTiming_dom_1_1
   076E FE                 3476 	mov	r6,a
   076F 33                 3477 	rlc	a
   0770 95 E0              3478 	subb	a,acc
   0772 FB                 3479 	mov	r3,a
                           3480 ;	genPlus
                           3481 ;     genPlusIncr
   0773 74 09              3482 	mov	a,#0x09
   0775 24 02              3483 	add	a,#_lcdbuf
   0777 F5 1B              3484 	mov	_UnsignedToAscii_PARM_2,a
                           3485 ;	Peephole 181	changed mov to clr
   0779 E4                 3486 	clr	a
   077A 34 00              3487 	addc	a,#(_lcdbuf >> 8)
   077C F5 1C              3488 	mov	(_UnsignedToAscii_PARM_2 + 1),a
                           3489 ;	genAssign
   077E 75 1D 02           3490 	mov	_UnsignedToAscii_PARM_3,#0x02
                           3491 ;	genCall
   0781 8E 82              3492 	mov	dpl,r6
   0783 8B 83              3493 	mov	dph,r3
   0785 C0 02              3494 	push	ar2
   0787 C0 05              3495 	push	ar5
   0789 12 0E FB           3496 	lcall	_UnsignedToAscii
   078C D0 05              3497 	pop	ar5
   078E D0 02              3498 	pop	ar2
                    06AF   3499 	C$TSIPMon.c$847$1$1 ==.
                           3500 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:847: if( lcdbuf[9] == ' ' ) lcdbuf[9] = '0';
                           3501 ;	genPointerGet
                           3502 ;	genFarPointerGet
   0790 90 00 0B           3503 	mov	dptr,#(_lcdbuf + 0x0009)
   0793 E0                 3504 	movx	a,@dptr
   0794 FB                 3505 	mov	r3,a
                           3506 ;	genCmpEq
                           3507 ;	gencjneshort
                           3508 ;	Peephole 112.b	changed ljmp to sjmp
                           3509 ;	Peephole 198.b	optimized misc jump sequence
   0795 BB 20 06           3510 	cjne	r3,#0x20,00136$
                           3511 ;	Peephole 200.b	removed redundant sjmp
                           3512 ;	Peephole 300	removed redundant label 00188$
                           3513 ;	Peephole 300	removed redundant label 00189$
                           3514 ;	genPointerSet
                           3515 ;     genFarPointerSet
   0798 90 00 0B           3516 	mov	dptr,#(_lcdbuf + 0x0009)
   079B 74 30              3517 	mov	a,#0x30
   079D F0                 3518 	movx	@dptr,a
   079E                    3519 00136$:
                    06BD   3520 	C$TSIPMon.c$850$1$1 ==.
                           3521 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:850: lcdbuf[11] = Month[mo];
                           3522 ;	genPlus
                           3523 ;	Peephole 236.g	used r5 instead of ar5
   079E ED                 3524 	mov	a,r5
                           3525 ;	Peephole 181	changed mov to clr
                           3526 ;	genPointerGet
                           3527 ;	genCodePointerGet
                           3528 ;	Peephole 186.d	optimized movc sequence
   079F 90 14 D0           3529 	mov	dptr,#_Month
   07A2 93                 3530 	movc	a,@a+dptr
                           3531 ;	genPointerSet
                           3532 ;     genFarPointerSet
   07A3 FB                 3533 	mov	r3,a
   07A4 90 00 0D           3534 	mov	dptr,#(_lcdbuf + 0x000b)
                           3535 ;	Peephole 100	removed redundant mov
   07A7 F0                 3536 	movx	@dptr,a
                    06C7   3537 	C$TSIPMon.c$851$1$1 ==.
                           3538 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:851: lcdbuf[12] = Month[mo+1];
                           3539 ;	genPlus
                           3540 ;     genPlusIncr
   07A8 74 01              3541 	mov	a,#0x01
                           3542 ;	Peephole 236.a	used r5 instead of ar5
   07AA 2D                 3543 	add	a,r5
                           3544 ;	genPlus
                           3545 ;	Peephole 240	use clr instead of addc a,#0
                           3546 ;	genPointerGet
                           3547 ;	genCodePointerGet
                           3548 ;	Peephole 186.d	optimized movc sequence
   07AB 90 14 D0           3549 	mov	dptr,#_Month
   07AE 93                 3550 	movc	a,@a+dptr
                           3551 ;	genPointerSet
                           3552 ;     genFarPointerSet
   07AF FB                 3553 	mov	r3,a
   07B0 90 00 0E           3554 	mov	dptr,#(_lcdbuf + 0x000c)
                           3555 ;	Peephole 100	removed redundant mov
   07B3 F0                 3556 	movx	@dptr,a
                    06D3   3557 	C$TSIPMon.c$852$1$1 ==.
                           3558 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:852: lcdbuf[13] = Month[mo+2];
                           3559 ;	genPlus
                           3560 ;     genPlusIncr
   07B4 74 02              3561 	mov	a,#0x02
                           3562 ;	Peephole 236.a	used r5 instead of ar5
   07B6 2D                 3563 	add	a,r5
                           3564 ;	genPlus
                           3565 ;	Peephole 240	use clr instead of addc a,#0
                           3566 ;	genPointerGet
                           3567 ;	genCodePointerGet
                           3568 ;	Peephole 186.d	optimized movc sequence
   07B7 90 14 D0           3569 	mov	dptr,#_Month
   07BA 93                 3570 	movc	a,@a+dptr
                           3571 ;	genPointerSet
                           3572 ;     genFarPointerSet
   07BB FB                 3573 	mov	r3,a
   07BC 90 00 0F           3574 	mov	dptr,#(_lcdbuf + 0x000d)
                           3575 ;	Peephole 100	removed redundant mov
   07BF F0                 3576 	movx	@dptr,a
                    06DF   3577 	C$TSIPMon.c$855$1$1 ==.
                           3578 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:855: UnsignedToAscii( (uint)y, lcdbuf+14, 2 );
                           3579 ;	genCast
   07C0 EA                 3580 	mov	a,r2
   07C1 33                 3581 	rlc	a
   07C2 95 E0              3582 	subb	a,acc
   07C4 FB                 3583 	mov	r3,a
                           3584 ;	genPlus
                           3585 ;     genPlusIncr
   07C5 74 0E              3586 	mov	a,#0x0E
   07C7 24 02              3587 	add	a,#_lcdbuf
   07C9 F5 1B              3588 	mov	_UnsignedToAscii_PARM_2,a
                           3589 ;	Peephole 181	changed mov to clr
   07CB E4                 3590 	clr	a
   07CC 34 00              3591 	addc	a,#(_lcdbuf >> 8)
   07CE F5 1C              3592 	mov	(_UnsignedToAscii_PARM_2 + 1),a
                           3593 ;	genAssign
   07D0 75 1D 02           3594 	mov	_UnsignedToAscii_PARM_3,#0x02
                           3595 ;	genCall
   07D3 8A 82              3596 	mov	dpl,r2
   07D5 8B 83              3597 	mov	dph,r3
   07D7 12 0E FB           3598 	lcall	_UnsignedToAscii
                    06F9   3599 	C$TSIPMon.c$856$1$1 ==.
                           3600 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:856: if( lcdbuf[14] == ' ' ) lcdbuf[14] = '0';
                           3601 ;	genPointerGet
                           3602 ;	genFarPointerGet
   07DA 90 00 10           3603 	mov	dptr,#(_lcdbuf + 0x000e)
   07DD E0                 3604 	movx	a,@dptr
   07DE FA                 3605 	mov	r2,a
                           3606 ;	genCmpEq
                           3607 ;	gencjneshort
                           3608 ;	Peephole 112.b	changed ljmp to sjmp
                           3609 ;	Peephole 198.b	optimized misc jump sequence
   07DF BA 20 06           3610 	cjne	r2,#0x20,00138$
                           3611 ;	Peephole 200.b	removed redundant sjmp
                           3612 ;	Peephole 300	removed redundant label 00190$
                           3613 ;	Peephole 300	removed redundant label 00191$
                           3614 ;	genPointerSet
                           3615 ;     genFarPointerSet
   07E2 90 00 10           3616 	mov	dptr,#(_lcdbuf + 0x000e)
   07E5 74 30              3617 	mov	a,#0x30
   07E7 F0                 3618 	movx	@dptr,a
   07E8                    3619 00138$:
                    0707   3620 	C$TSIPMon.c$857$1$1 ==.
                           3621 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:857: lcdbuf[16] = '\0';
                           3622 ;	genPointerSet
                           3623 ;     genFarPointerSet
   07E8 90 00 12           3624 	mov	dptr,#(_lcdbuf + 0x0010)
                           3625 ;	Peephole 181	changed mov to clr
   07EB E4                 3626 	clr	a
   07EC F0                 3627 	movx	@dptr,a
                           3628 ;	genIfx
                           3629 ;	genIfxJump
                           3630 ;	Peephole 108.d	removed ljmp by inverse jump logic
   07ED 30 86 1E           3631 	jnb	_P0_6,00143$
                           3632 ;	Peephole 300	removed redundant label 00192$
                    070F   3633 	C$TSIPMon.c$860$2$14 ==.
                           3634 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:860: lcdbuf[16] = ' ';
                           3635 ;	genPointerSet
                           3636 ;     genFarPointerSet
   07F0 90 00 12           3637 	mov	dptr,#(_lcdbuf + 0x0010)
   07F3 74 20              3638 	mov	a,#0x20
   07F5 F0                 3639 	movx	@dptr,a
                    0715   3640 	C$TSIPMon.c$861$2$14 ==.
                           3641 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:861: lcdbuf[17] = 'G';
                           3642 ;	genPointerSet
                           3643 ;     genFarPointerSet
   07F6 90 00 13           3644 	mov	dptr,#(_lcdbuf + 0x0011)
   07F9 74 47              3645 	mov	a,#0x47
   07FB F0                 3646 	movx	@dptr,a
                    071B   3647 	C$TSIPMon.c$862$2$14 ==.
                           3648 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:862: lcdbuf[18] = 'P';
                           3649 ;	genPointerSet
                           3650 ;     genFarPointerSet
   07FC 90 00 14           3651 	mov	dptr,#(_lcdbuf + 0x0012)
   07FF 74 50              3652 	mov	a,#0x50
   0801 F0                 3653 	movx	@dptr,a
                    0721   3654 	C$TSIPMon.c$863$2$14 ==.
                           3655 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:863: lcdbuf[19] = 'S';
                           3656 ;	genPointerSet
                           3657 ;     genFarPointerSet
   0802 90 00 15           3658 	mov	dptr,#(_lcdbuf + 0x0013)
   0805 74 53              3659 	mov	a,#0x53
   0807 F0                 3660 	movx	@dptr,a
                    0727   3661 	C$TSIPMon.c$864$2$14 ==.
                           3662 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:864: lcdbuf[20] = '\0';
                           3663 ;	genPointerSet
                           3664 ;     genFarPointerSet
   0808 90 00 16           3665 	mov	dptr,#(_lcdbuf + 0x0014)
                           3666 ;	Peephole 181	changed mov to clr
   080B E4                 3667 	clr	a
   080C F0                 3668 	movx	@dptr,a
                           3669 ;	Peephole 112.b	changed ljmp to sjmp
                           3670 ;	Peephole 251.b	replaced sjmp to ret with ret
   080D 22                 3671 	ret
   080E                    3672 00143$:
                    072D   3673 	C$TSIPMon.c$866$2$15 ==.
                           3674 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:866: lcdbuf[16] = ' ';
                           3675 ;	genPointerSet
                           3676 ;     genFarPointerSet
   080E 90 00 12           3677 	mov	dptr,#(_lcdbuf + 0x0010)
   0811 74 20              3678 	mov	a,#0x20
   0813 F0                 3679 	movx	@dptr,a
                    0733   3680 	C$TSIPMon.c$867$2$15 ==.
                           3681 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:867: lcdbuf[17] = 'C';
                           3682 ;	genPointerSet
                           3683 ;     genFarPointerSet
   0814 90 00 13           3684 	mov	dptr,#(_lcdbuf + 0x0011)
   0817 74 43              3685 	mov	a,#0x43
   0819 F0                 3686 	movx	@dptr,a
                           3687 ;	genIfx
                           3688 ;	genIfxJump
                           3689 ;	Peephole 108.e	removed ljmp by inverse jump logic
   081A 20 87 08           3690 	jb	_P0_7,00140$
                           3691 ;	Peephole 300	removed redundant label 00193$
                    073C   3692 	C$TSIPMon.c$869$2$15 ==.
                           3693 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:869: lcdbuf[18] = 'D';
                           3694 ;	genPointerSet
                           3695 ;     genFarPointerSet
   081D 90 00 14           3696 	mov	dptr,#(_lcdbuf + 0x0012)
   0820 74 44              3697 	mov	a,#0x44
   0822 F0                 3698 	movx	@dptr,a
                           3699 ;	Peephole 112.b	changed ljmp to sjmp
   0823 80 06              3700 	sjmp	00141$
   0825                    3701 00140$:
                    0744   3702 	C$TSIPMon.c$871$2$15 ==.
                           3703 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:871: lcdbuf[18] = 'S';
                           3704 ;	genPointerSet
                           3705 ;     genFarPointerSet
   0825 90 00 14           3706 	mov	dptr,#(_lcdbuf + 0x0012)
   0828 74 53              3707 	mov	a,#0x53
   082A F0                 3708 	movx	@dptr,a
   082B                    3709 00141$:
                    074A   3710 	C$TSIPMon.c$872$2$15 ==.
                           3711 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:872: lcdbuf[19] = 'T';
                           3712 ;	genPointerSet
                           3713 ;     genFarPointerSet
   082B 90 00 15           3714 	mov	dptr,#(_lcdbuf + 0x0013)
   082E 74 54              3715 	mov	a,#0x54
   0830 F0                 3716 	movx	@dptr,a
                    0750   3717 	C$TSIPMon.c$873$2$15 ==.
                           3718 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:873: lcdbuf[20] = '\0';
                           3719 ;	genPointerSet
                           3720 ;     genFarPointerSet
   0831 90 00 16           3721 	mov	dptr,#(_lcdbuf + 0x0014)
                           3722 ;	Peephole 181	changed mov to clr
   0834 E4                 3723 	clr	a
   0835 F0                 3724 	movx	@dptr,a
                           3725 ;	Peephole 300	removed redundant label 00145$
                    0755   3726 	C$TSIPMon.c$884$1$1 ==.
                    0755   3727 	XG$PrimaryTiming$0$0 ==.
   0836 22                 3728 	ret
                           3729 ;------------------------------------------------------------
                           3730 ;Allocation info for local variables in function 'SupplementalTiming'
                           3731 ;------------------------------------------------------------
                           3732 ;mode                      Allocated with name '_SupplementalTiming_mode_1_1'
                           3733 ;RxBuf                     Allocated with name '_SupplementalTiming_RxBuf_1_1'
                           3734 ;temp                      Allocated with name '_SupplementalTiming_temp_1_1'
                           3735 ;val                       Allocated with name '_SupplementalTiming_val_1_1'
                           3736 ;fval                      Allocated with name '_SupplementalTiming_fval_1_1'
                           3737 ;sloc0                     Allocated with name '_SupplementalTiming_sloc0_1_0'
                           3738 ;sloc1                     Allocated with name '_SupplementalTiming_sloc1_1_0'
                           3739 ;------------------------------------------------------------
                    0756   3740 	G$SupplementalTiming$0$0 ==.
                    0756   3741 	C$TSIPMon.c$891$1$1 ==.
                           3742 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:891: void SupplementalTiming( uchar TXRX_STORAGE_CLASS *RxBuf ){
                           3743 ;	-----------------------------------------
                           3744 ;	 function SupplementalTiming
                           3745 ;	-----------------------------------------
   0837                    3746 _SupplementalTiming:
                           3747 ;	genReceive
   0837 85 82 39           3748 	mov	_SupplementalTiming_RxBuf_1_1,dpl
   083A 85 83 3A           3749 	mov	(_SupplementalTiming_RxBuf_1_1 + 1),dph
                    075C   3750 	C$TSIPMon.c$913$1$1 ==.
                           3751 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:913: printLCD( 1, lcdbuf, 0 );	// print 1st line
                           3752 ;	genAddrOf
   083D 75 08 02           3753 	mov	_printLCD_PARM_2,#_lcdbuf
   0840 75 09 00           3754 	mov	(_printLCD_PARM_2 + 1),#(_lcdbuf >> 8)
                           3755 ;	genAssign
   0843 75 0A 00           3756 	mov	_printLCD_PARM_3,#0x00
                           3757 ;	genCall
   0846 75 82 01           3758 	mov	dpl,#0x01
   0849 12 0D 14           3759 	lcall	_printLCD
                    076B   3760 	C$TSIPMon.c$918$1$1 ==.
                           3761 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:918: Alarms.b.hi = RxBuf[10];
                           3762 ;	genPlus
                           3763 ;     genPlusIncr
   084C 74 0A              3764 	mov	a,#0x0A
   084E 25 39              3765 	add	a,_SupplementalTiming_RxBuf_1_1
   0850 F5 82              3766 	mov	dpl,a
                           3767 ;	Peephole 181	changed mov to clr
   0852 E4                 3768 	clr	a
   0853 35 3A              3769 	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
   0855 F5 83              3770 	mov	dph,a
                           3771 ;	genPointerGet
                           3772 ;	genFarPointerGet
   0857 E0                 3773 	movx	a,@dptr
                           3774 ;	genPointerSet
                           3775 ;     genFarPointerSet
   0858 FC                 3776 	mov	r4,a
   0859 90 00 01           3777 	mov	dptr,#(_Alarms + 0x0001)
                           3778 ;	Peephole 100	removed redundant mov
   085C F0                 3779 	movx	@dptr,a
                    077C   3780 	C$TSIPMon.c$919$1$1 ==.
                           3781 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:919: Alarms.b.lo = RxBuf[11];
                           3782 ;	genPlus
                           3783 ;     genPlusIncr
   085D 74 0B              3784 	mov	a,#0x0B
   085F 25 39              3785 	add	a,_SupplementalTiming_RxBuf_1_1
   0861 F5 82              3786 	mov	dpl,a
                           3787 ;	Peephole 181	changed mov to clr
   0863 E4                 3788 	clr	a
   0864 35 3A              3789 	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
   0866 F5 83              3790 	mov	dph,a
                           3791 ;	genPointerGet
                           3792 ;	genFarPointerGet
   0868 E0                 3793 	movx	a,@dptr
                           3794 ;	genPointerSet
                           3795 ;     genFarPointerSet
   0869 FC                 3796 	mov	r4,a
   086A 90 00 00           3797 	mov	dptr,#_Alarms
                           3798 ;	Peephole 100	removed redundant mov
   086D F0                 3799 	movx	@dptr,a
                    078D   3800 	C$TSIPMon.c$921$1$1 ==.
                           3801 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:921: Alarms.u = Alarms.u<<5;
                           3802 ;	genPointerGet
                           3803 ;	genFarPointerGet
   086E 90 00 00           3804 	mov	dptr,#_Alarms
   0871 E0                 3805 	movx	a,@dptr
   0872 FC                 3806 	mov	r4,a
   0873 A3                 3807 	inc	dptr
   0874 E0                 3808 	movx	a,@dptr
                           3809 ;	genLeftShift
                           3810 ;	genLeftShiftLiteral
                           3811 ;	genlshTwo
   0875 FD                 3812 	mov	r5,a
                           3813 ;	Peephole 105	removed redundant mov
   0876 C4                 3814 	swap	a
   0877 23                 3815 	rl	a
   0878 54 E0              3816 	anl	a,#0xe0
   087A CC                 3817 	xch	a,r4
   087B C4                 3818 	swap	a
   087C 23                 3819 	rl	a
   087D CC                 3820 	xch	a,r4
   087E 6C                 3821 	xrl	a,r4
   087F CC                 3822 	xch	a,r4
   0880 54 E0              3823 	anl	a,#0xe0
   0882 CC                 3824 	xch	a,r4
   0883 6C                 3825 	xrl	a,r4
   0884 FD                 3826 	mov	r5,a
                           3827 ;	genPointerSet
                           3828 ;     genFarPointerSet
   0885 90 00 00           3829 	mov	dptr,#_Alarms
   0888 EC                 3830 	mov	a,r4
   0889 F0                 3831 	movx	@dptr,a
   088A A3                 3832 	inc	dptr
   088B ED                 3833 	mov	a,r5
   088C F0                 3834 	movx	@dptr,a
                    07AC   3835 	C$TSIPMon.c$923$1$1 ==.
                           3836 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:923: Alarms.b.lo |= RxBuf[9];
                           3837 ;	genPointerGet
                           3838 ;	genFarPointerGet
   088D 90 00 00           3839 	mov	dptr,#_Alarms
   0890 E0                 3840 	movx	a,@dptr
   0891 FC                 3841 	mov	r4,a
                           3842 ;	genPlus
                           3843 ;     genPlusIncr
   0892 74 09              3844 	mov	a,#0x09
   0894 25 39              3845 	add	a,_SupplementalTiming_RxBuf_1_1
   0896 FD                 3846 	mov	r5,a
                           3847 ;	Peephole 181	changed mov to clr
   0897 E4                 3848 	clr	a
   0898 35 3A              3849 	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
   089A FE                 3850 	mov	r6,a
                           3851 ;	genPointerGet
                           3852 ;	genFarPointerGet
   089B 8D 82              3853 	mov	dpl,r5
   089D 8E 83              3854 	mov	dph,r6
   089F E0                 3855 	movx	a,@dptr
                           3856 ;	genOr
   08A0 FF                 3857 	mov	r7,a
                           3858 ;	Peephole 105	removed redundant mov
   08A1 42 04              3859 	orl	ar4,a
                           3860 ;	genPointerSet
                           3861 ;     genFarPointerSet
   08A3 90 00 00           3862 	mov	dptr,#_Alarms
   08A6 EC                 3863 	mov	a,r4
   08A7 F0                 3864 	movx	@dptr,a
                    07C7   3865 	C$TSIPMon.c$926$1$1 ==.
                           3866 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:926: c = !c;  // only change display every 2nd time thru ( about every 2 seconds)
                           3867 ;	genNot
   08A8 B2 09              3868 	cpl	_SupplementalTiming_c_1_1
                    07C9   3869 	C$TSIPMon.c$927$1$1 ==.
                           3870 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:927: if( c )
                           3871 ;	genIfx
                           3872 ;	genIfxJump
                           3873 ;	Peephole 108.d	removed ljmp by inverse jump logic
   08AA 30 09 01           3874 	jnb	_SupplementalTiming_c_1_1,00102$
                           3875 ;	Peephole 300	removed redundant label 00143$
                    07CC   3876 	C$TSIPMon.c$928$1$1 ==.
                           3877 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:928: return;
                           3878 ;	genRet
                           3879 ;	Peephole 251.a	replaced ljmp to ret with ret
   08AD 22                 3880 	ret
   08AE                    3881 00102$:
                    07CD   3882 	C$TSIPMon.c$930$1$1 ==.
                           3883 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:930: ClearLCD( 2 );
                           3884 ;	genCall
   08AE 75 82 02           3885 	mov	dpl,#0x02
   08B1 C0 05              3886 	push	ar5
   08B3 C0 06              3887 	push	ar6
   08B5 12 0C A8           3888 	lcall	_ClearLCD
   08B8 D0 06              3889 	pop	ar6
   08BA D0 05              3890 	pop	ar5
                    07DB   3891 	C$TSIPMon.c$931$1$1 ==.
                           3892 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:931: if( Alarms.u != 0 && mode == NUM_DISPLAY_MODES - 1 ){
                           3893 ;	genPointerGet
                           3894 ;	genFarPointerGet
   08BC 90 00 00           3895 	mov	dptr,#_Alarms
   08BF E0                 3896 	movx	a,@dptr
   08C0 FC                 3897 	mov	r4,a
   08C1 A3                 3898 	inc	dptr
   08C2 E0                 3899 	movx	a,@dptr
   08C3 FF                 3900 	mov	r7,a
                           3901 ;	genCmpEq
                           3902 ;	gencjneshort
   08C4 BC 00 05           3903 	cjne	r4,#0x00,00144$
   08C7 BF 00 02           3904 	cjne	r7,#0x00,00144$
                           3905 ;	Peephole 112.b	changed ljmp to sjmp
   08CA 80 4D              3906 	sjmp	00108$
   08CC                    3907 00144$:
                           3908 ;	genCmpEq
                           3909 ;	gencjneshort
   08CC E5 38              3910 	mov	a,_SupplementalTiming_mode_1_1
                           3911 ;	Peephole 112.b	changed ljmp to sjmp
                           3912 ;	Peephole 198.b	optimized misc jump sequence
   08CE B4 05 48           3913 	cjne	a,#0x05,00108$
                           3914 ;	Peephole 200.b	removed redundant sjmp
                           3915 ;	Peephole 300	removed redundant label 00145$
                           3916 ;	Peephole 300	removed redundant label 00146$
                    07F0   3917 	C$TSIPMon.c$932$2$2 ==.
                           3918 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:932: b = Fault_Msg_Query( Alarms.u, lcdbuf, ALARM_MSG[0] );
                           3919 ;	genPointerGet
                           3920 ;	genFarPointerGet
   08D1 90 00 00           3921 	mov	dptr,#_Alarms
   08D4 E0                 3922 	movx	a,@dptr
   08D5 FC                 3923 	mov	r4,a
   08D6 A3                 3924 	inc	dptr
   08D7 E0                 3925 	movx	a,@dptr
   08D8 FF                 3926 	mov	r7,a
                           3927 ;	genAddrOf
   08D9 75 46 02           3928 	mov	_Fault_Msg_Query_PARM_2,#_lcdbuf
   08DC 75 47 00           3929 	mov	(_Fault_Msg_Query_PARM_2 + 1),#(_lcdbuf >> 8)
                           3930 ;	genAddrOf
   08DF 75 48 35           3931 	mov	_Fault_Msg_Query_PARM_3,#_ALARM_MSG
   08E2 75 49 18           3932 	mov	(_Fault_Msg_Query_PARM_3 + 1),#(_ALARM_MSG >> 8)
                           3933 ;	genCall
   08E5 8C 82              3934 	mov	dpl,r4
   08E7 8F 83              3935 	mov	dph,r7
   08E9 C0 05              3936 	push	ar5
   08EB C0 06              3937 	push	ar6
   08ED 12 10 95           3938 	lcall	_Fault_Msg_Query
   08F0 92 08              3939 	mov	_SupplementalTiming_b_1_1,c
   08F2 D0 06              3940 	pop	ar6
   08F4 D0 05              3941 	pop	ar5
                    0815   3942 	C$TSIPMon.c$933$2$2 ==.
                           3943 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:933: if( b )
                           3944 ;	genIfx
                           3945 ;	genIfxJump
                           3946 ;	Peephole 108.d	removed ljmp by inverse jump logic
   08F6 30 08 17           3947 	jnb	_SupplementalTiming_b_1_1,00104$
                           3948 ;	Peephole 300	removed redundant label 00147$
                    0818   3949 	C$TSIPMon.c$934$2$2 ==.
                           3950 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:934: printLCD( 2, lcdbuf, 0 ); 
                           3951 ;	genAddrOf
   08F9 75 08 02           3952 	mov	_printLCD_PARM_2,#_lcdbuf
   08FC 75 09 00           3953 	mov	(_printLCD_PARM_2 + 1),#(_lcdbuf >> 8)
                           3954 ;	genAssign
   08FF 75 0A 00           3955 	mov	_printLCD_PARM_3,#0x00
                           3956 ;	genCall
   0902 75 82 02           3957 	mov	dpl,#0x02
   0905 C0 05              3958 	push	ar5
   0907 C0 06              3959 	push	ar6
   0909 12 0D 14           3960 	lcall	_printLCD
   090C D0 06              3961 	pop	ar6
   090E D0 05              3962 	pop	ar5
   0910                    3963 00104$:
                    082F   3964 	C$TSIPMon.c$935$2$2 ==.
                           3965 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:935: if( RxBuf[9] != 0 ) // if critical alarm, keep showing it
                           3966 ;	genPointerGet
                           3967 ;	genFarPointerGet
   0910 8D 82              3968 	mov	dpl,r5
   0912 8E 83              3969 	mov	dph,r6
   0914 E0                 3970 	movx	a,@dptr
                           3971 ;	genCmpEq
                           3972 ;	gencjneshort
                           3973 ;	Peephole 112.b	changed ljmp to sjmp
   0915 FD                 3974 	mov	r5,a
                           3975 ;	Peephole 115.b	jump optimization
   0916 60 01              3976 	jz	00108$
                           3977 ;	Peephole 300	removed redundant label 00148$
                    0837   3978 	C$TSIPMon.c$936$2$2 ==.
                           3979 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:936: return;        
                           3980 ;	genRet
                           3981 ;	Peephole 251.a	replaced ljmp to ret with ret
   0918 22                 3982 	ret
   0919                    3983 00108$:
                    0838   3984 	C$TSIPMon.c$939$1$1 ==.
                           3985 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:939: if( !b ){
                           3986 ;	genIfx
                           3987 ;	genIfxJump
   0919 30 08 01           3988 	jnb	_SupplementalTiming_b_1_1,00149$
                           3989 ;	Peephole 251.a	replaced ljmp to ret with ret
   091C 22                 3990 	ret
   091D                    3991 00149$:
                    083C   3992 	C$TSIPMon.c$940$2$3 ==.
                           3993 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:940: if( ++mode >= NUM_DISPLAY_MODES )
                           3994 ;	genPlus
                           3995 ;     genPlusIncr
   091D 05 38              3996 	inc	_SupplementalTiming_mode_1_1
                           3997 ;	genCmpLt
                           3998 ;	genCmp
   091F C3                 3999 	clr	c
   0920 E5 38              4000 	mov	a,_SupplementalTiming_mode_1_1
   0922 64 80              4001 	xrl	a,#0x80
   0924 94 86              4002 	subb	a,#0x86
                           4003 ;	genIfxJump
                           4004 ;	Peephole 112.b	changed ljmp to sjmp
                           4005 ;	Peephole 160.a	removed sjmp by inverse jump logic
   0926 40 03              4006 	jc	00111$
                           4007 ;	Peephole 300	removed redundant label 00150$
                    0847   4008 	C$TSIPMon.c$941$2$3 ==.
                           4009 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:941: mode = 0;
                           4010 ;	genAssign
   0928 75 38 00           4011 	mov	_SupplementalTiming_mode_1_1,#0x00
   092B                    4012 00111$:
                    084A   4013 	C$TSIPMon.c$943$2$3 ==.
                           4014 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:943: val = 28;
                           4015 ;	genAssign
   092B 75 3F 1C           4016 	mov	_SupplementalTiming_val_1_1,#0x1C
                    084D   4017 	C$TSIPMon.c$944$2$3 ==.
                           4018 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:944: fval = 10000;
                           4019 ;	genAssign
   092E 75 40 10           4020 	mov	_SupplementalTiming_fval_1_1,#0x10
   0931 75 41 27           4021 	mov	(_SupplementalTiming_fval_1_1 + 1),#0x27
                    0853   4022 	C$TSIPMon.c$945$2$3 ==.
                           4023 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:945: switch( mode ){
                           4024 ;	genCmpLt
                           4025 ;	genCmp
   0934 E5 38              4026 	mov	a,_SupplementalTiming_mode_1_1
                           4027 ;	genIfxJump
   0936 30 E7 03           4028 	jnb	acc.7,00151$
   0939 02 0B 89           4029 	ljmp	00125$
   093C                    4030 00151$:
                           4031 ;	genCmpGt
                           4032 ;	genCmp
   093C C3                 4033 	clr	c
                           4034 ;	Peephole 159	avoided xrl during execution
   093D 74 85              4035 	mov	a,#(0x05 ^ 0x80)
   093F 85 38 F0           4036 	mov	b,_SupplementalTiming_mode_1_1
   0942 63 F0 80           4037 	xrl	b,#0x80
   0945 95 F0              4038 	subb	a,b
                           4039 ;	genIfxJump
   0947 50 03              4040 	jnc	00152$
   0949 02 0B 89           4041 	ljmp	00125$
   094C                    4042 00152$:
                           4043 ;	genJumpTab
   094C E5 38              4044 	mov	a,_SupplementalTiming_mode_1_1
                           4045 ;	Peephole 254	optimized left shift
   094E 25 38              4046 	add	a,_SupplementalTiming_mode_1_1
   0950 25 38              4047 	add	a,_SupplementalTiming_mode_1_1
   0952 90 09 56           4048 	mov	dptr,#00153$
   0955 73                 4049 	jmp	@a+dptr
   0956                    4050 00153$:
   0956 02 09 68           4051 	ljmp	00112$
   0959 02 09 90           4052 	ljmp	00113$
   095C 02 09 BB           4053 	ljmp	00114$
   095F 02 09 E2           4054 	ljmp	00115$
   0962 02 0A 0E           4055 	ljmp	00116$
   0965 02 0A 17           4056 	ljmp	00117$
                    0887   4057 	C$TSIPMon.c$946$3$4 ==.
                           4058 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:946: case 0:	// disciplining mode
   0968                    4059 00112$:
                    0887   4060 	C$TSIPMon.c$947$3$4 ==.
                           4061 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:947: strcpy( lcdbuf , DiscMode[RxBuf[2]]);
                           4062 ;	genPlus
                           4063 ;     genPlusIncr
   0968 85 39 82           4064 	mov	dpl,_SupplementalTiming_RxBuf_1_1
   096B 85 3A 83           4065 	mov	dph,(_SupplementalTiming_RxBuf_1_1 + 1)
   096E A3                 4066 	inc	dptr
   096F A3                 4067 	inc	dptr
                           4068 ;	genPointerGet
                           4069 ;	genFarPointerGet
   0970 E0                 4070 	movx	a,@dptr
                           4071 ;	genMult
                           4072 ;	genMultOneByte
   0971 FF                 4073 	mov	r7,a
                           4074 ;	Peephole 105	removed redundant mov
   0972 75 F0 11           4075 	mov	b,#0x11
   0975 A4                 4076 	mul	ab
                           4077 ;	genPlus
   0976 24 89              4078 	add	a,#_DiscMode
   0978 FA                 4079 	mov	r2,a
                           4080 ;	Peephole 240	use clr instead of addc a,#0
   0979 E4                 4081 	clr	a
   097A 34 15              4082 	addc	a,#(_DiscMode >> 8)
   097C FB                 4083 	mov	r3,a
                           4084 ;	genCast
   097D 8A 46              4085 	mov	_strcpy_PARM_2,r2
   097F 8B 47              4086 	mov	(_strcpy_PARM_2 + 1),r3
   0981 75 48 80           4087 	mov	(_strcpy_PARM_2 + 2),#0x80
                           4088 ;	genCall
                           4089 ;	Peephole 182.a	used 16 bit load of DPTR
   0984 90 00 02           4090 	mov	dptr,#_lcdbuf
   0987 75 F0 00           4091 	mov	b,#0x00
   098A 12 11 96           4092 	lcall	_strcpy
                    08AC   4093 	C$TSIPMon.c$948$3$4 ==.
                           4094 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:948: break;
   098D 02 0B 89           4095 	ljmp	00125$
                    08AF   4096 	C$TSIPMon.c$950$3$4 ==.
                           4097 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:950: case 1:	// Discipling Activity
   0990                    4098 00113$:
                    08AF   4099 	C$TSIPMon.c$951$3$4 ==.
                           4100 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:951: strcpy( lcdbuf , DiscActivity[RxBuf[13]]);
                           4101 ;	genPlus
                           4102 ;     genPlusIncr
   0990 74 0D              4103 	mov	a,#0x0D
   0992 25 39              4104 	add	a,_SupplementalTiming_RxBuf_1_1
   0994 F5 82              4105 	mov	dpl,a
                           4106 ;	Peephole 181	changed mov to clr
   0996 E4                 4107 	clr	a
   0997 35 3A              4108 	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
   0999 F5 83              4109 	mov	dph,a
                           4110 ;	genPointerGet
                           4111 ;	genFarPointerGet
   099B E0                 4112 	movx	a,@dptr
                           4113 ;	genMult
                           4114 ;	genMultOneByte
   099C FF                 4115 	mov	r7,a
                           4116 ;	Peephole 105	removed redundant mov
   099D 75 F0 11           4117 	mov	b,#0x11
   09A0 A4                 4118 	mul	ab
                           4119 ;	genPlus
   09A1 24 21              4120 	add	a,#_DiscActivity
   09A3 FA                 4121 	mov	r2,a
                           4122 ;	Peephole 240	use clr instead of addc a,#0
   09A4 E4                 4123 	clr	a
   09A5 34 17              4124 	addc	a,#(_DiscActivity >> 8)
   09A7 FB                 4125 	mov	r3,a
                           4126 ;	genCast
   09A8 8A 46              4127 	mov	_strcpy_PARM_2,r2
   09AA 8B 47              4128 	mov	(_strcpy_PARM_2 + 1),r3
   09AC 75 48 80           4129 	mov	(_strcpy_PARM_2 + 2),#0x80
                           4130 ;	genCall
                           4131 ;	Peephole 182.a	used 16 bit load of DPTR
   09AF 90 00 02           4132 	mov	dptr,#_lcdbuf
   09B2 75 F0 00           4133 	mov	b,#0x00
   09B5 12 11 96           4134 	lcall	_strcpy
                    08D7   4135 	C$TSIPMon.c$952$3$4 ==.
                           4136 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:952: break;
   09B8 02 0B 89           4137 	ljmp	00125$
                    08DA   4138 	C$TSIPMon.c$954$3$4 ==.
                           4139 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:954: case 2:	// Receiver mode
   09BB                    4140 00114$:
                    08DA   4141 	C$TSIPMon.c$955$3$4 ==.
                           4142 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:955: strcpy( lcdbuf , RxMode[RxBuf[1]]);
                           4143 ;	genPlus
                           4144 ;     genPlusIncr
   09BB 85 39 82           4145 	mov	dpl,_SupplementalTiming_RxBuf_1_1
   09BE 85 3A 83           4146 	mov	dph,(_SupplementalTiming_RxBuf_1_1 + 1)
   09C1 A3                 4147 	inc	dptr
                           4148 ;	genPointerGet
                           4149 ;	genFarPointerGet
   09C2 E0                 4150 	movx	a,@dptr
                           4151 ;	genMult
                           4152 ;	genMultOneByte
   09C3 FF                 4153 	mov	r7,a
                           4154 ;	Peephole 105	removed redundant mov
   09C4 75 F0 11           4155 	mov	b,#0x11
   09C7 A4                 4156 	mul	ab
                           4157 ;	genPlus
   09C8 24 01              4158 	add	a,#_RxMode
   09CA FA                 4159 	mov	r2,a
                           4160 ;	Peephole 240	use clr instead of addc a,#0
   09CB E4                 4161 	clr	a
   09CC 34 15              4162 	addc	a,#(_RxMode >> 8)
   09CE FB                 4163 	mov	r3,a
                           4164 ;	genCast
   09CF 8A 46              4165 	mov	_strcpy_PARM_2,r2
   09D1 8B 47              4166 	mov	(_strcpy_PARM_2 + 1),r3
   09D3 75 48 80           4167 	mov	(_strcpy_PARM_2 + 2),#0x80
                           4168 ;	genCall
                           4169 ;	Peephole 182.a	used 16 bit load of DPTR
   09D6 90 00 02           4170 	mov	dptr,#_lcdbuf
   09D9 75 F0 00           4171 	mov	b,#0x00
   09DC 12 11 96           4172 	lcall	_strcpy
                    08FE   4173 	C$TSIPMon.c$956$3$4 ==.
                           4174 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:956: break;
   09DF 02 0B 89           4175 	ljmp	00125$
                    0901   4176 	C$TSIPMon.c$958$3$4 ==.
                           4177 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:958: case 3:	// GPS Decode Status
   09E2                    4178 00115$:
                    0901   4179 	C$TSIPMon.c$959$3$4 ==.
                           4180 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:959: strcpy( lcdbuf , GPSDecodeStatus[RxBuf[12]]);
                           4181 ;	genPlus
                           4182 ;     genPlusIncr
   09E2 74 0C              4183 	mov	a,#0x0C
   09E4 25 39              4184 	add	a,_SupplementalTiming_RxBuf_1_1
   09E6 F5 82              4185 	mov	dpl,a
                           4186 ;	Peephole 181	changed mov to clr
   09E8 E4                 4187 	clr	a
   09E9 35 3A              4188 	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
   09EB F5 83              4189 	mov	dph,a
                           4190 ;	genPointerGet
                           4191 ;	genFarPointerGet
   09ED E0                 4192 	movx	a,@dptr
                           4193 ;	genMult
                           4194 ;	genMultOneByte
   09EE FF                 4195 	mov	r7,a
                           4196 ;	Peephole 105	removed redundant mov
   09EF 75 F0 11           4197 	mov	b,#0x11
   09F2 A4                 4198 	mul	ab
                           4199 ;	genPlus
   09F3 24 00              4200 	add	a,#_GPSDecodeStatus
   09F5 FA                 4201 	mov	r2,a
   09F6 74 16              4202 	mov	a,#(_GPSDecodeStatus >> 8)
   09F8 35 F0              4203 	addc	a,b
   09FA FB                 4204 	mov	r3,a
                           4205 ;	genCast
   09FB 8A 46              4206 	mov	_strcpy_PARM_2,r2
   09FD 8B 47              4207 	mov	(_strcpy_PARM_2 + 1),r3
   09FF 75 48 80           4208 	mov	(_strcpy_PARM_2 + 2),#0x80
                           4209 ;	genCall
                           4210 ;	Peephole 182.a	used 16 bit load of DPTR
   0A02 90 00 02           4211 	mov	dptr,#_lcdbuf
   0A05 75 F0 00           4212 	mov	b,#0x00
   0A08 12 11 96           4213 	lcall	_strcpy
                    092A   4214 	C$TSIPMon.c$960$3$4 ==.
                           4215 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:960: break;
   0A0B 02 0B 89           4216 	ljmp	00125$
                    092D   4217 	C$TSIPMon.c$962$3$4 ==.
                           4218 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:962: case 4:	// RxBuf[32-35] is temperature (float)
   0A0E                    4219 00116$:
                    092D   4220 	C$TSIPMon.c$963$3$4 ==.
                           4221 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:963: val = 32;
                           4222 ;	genAssign
   0A0E 75 3F 20           4223 	mov	_SupplementalTiming_val_1_1,#0x20
                    0930   4224 	C$TSIPMon.c$964$3$4 ==.
                           4225 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:964: fval = 100;
                           4226 ;	genAssign
   0A11 75 40 64           4227 	mov	_SupplementalTiming_fval_1_1,#0x64
   0A14 E4                 4228 	clr	a
   0A15 F5 41              4229 	mov	(_SupplementalTiming_fval_1_1 + 1),a
                    0936   4230 	C$TSIPMon.c$967$3$4 ==.
                           4231 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:967: case 5:	// RxBuf[28-31] is DAC Voltage (float)
   0A17                    4232 00117$:
                    0936   4233 	C$TSIPMon.c$968$3$4 ==.
                           4234 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:968: temp.b.hhi = RxBuf[val];
                           4235 ;	genPlus
   0A17 E5 3F              4236 	mov	a,_SupplementalTiming_val_1_1
   0A19 25 39              4237 	add	a,_SupplementalTiming_RxBuf_1_1
   0A1B F5 82              4238 	mov	dpl,a
                           4239 ;	Peephole 181	changed mov to clr
   0A1D E4                 4240 	clr	a
   0A1E 35 3A              4241 	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
   0A20 F5 83              4242 	mov	dph,a
                           4243 ;	genPointerGet
                           4244 ;	genFarPointerGet
   0A22 E0                 4245 	movx	a,@dptr
   0A23 FF                 4246 	mov	r7,a
                           4247 ;	genPointerSet
                           4248 ;	genNearPointerSet
                           4249 ;	genDataPointerSet
   0A24 8F 3E              4250 	mov	(_SupplementalTiming_temp_1_1 + 0x0003),r7
                    0945   4251 	C$TSIPMon.c$969$3$4 ==.
                           4252 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:969: temp.b.hi = RxBuf[val+1];
                           4253 ;	genCast
   0A26 AF 3F              4254 	mov	r7,_SupplementalTiming_val_1_1
   0A28 7D 00              4255 	mov	r5,#0x00
                           4256 ;	genPlus
                           4257 ;     genPlusIncr
   0A2A 74 01              4258 	mov	a,#0x01
                           4259 ;	Peephole 236.a	used r7 instead of ar7
   0A2C 2F                 4260 	add	a,r7
   0A2D FE                 4261 	mov	r6,a
                           4262 ;	Peephole 181	changed mov to clr
   0A2E E4                 4263 	clr	a
                           4264 ;	Peephole 236.b	used r5 instead of ar5
   0A2F 3D                 4265 	addc	a,r5
   0A30 FA                 4266 	mov	r2,a
                           4267 ;	genPlus
                           4268 ;	Peephole 236.g	used r6 instead of ar6
   0A31 EE                 4269 	mov	a,r6
   0A32 25 39              4270 	add	a,_SupplementalTiming_RxBuf_1_1
   0A34 F5 82              4271 	mov	dpl,a
                           4272 ;	Peephole 236.g	used r2 instead of ar2
   0A36 EA                 4273 	mov	a,r2
   0A37 35 3A              4274 	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
   0A39 F5 83              4275 	mov	dph,a
                           4276 ;	genPointerGet
                           4277 ;	genFarPointerGet
   0A3B E0                 4278 	movx	a,@dptr
   0A3C FA                 4279 	mov	r2,a
                           4280 ;	genPointerSet
                           4281 ;	genNearPointerSet
                           4282 ;	genDataPointerSet
   0A3D 8A 3D              4283 	mov	(_SupplementalTiming_temp_1_1 + 0x0002),r2
                    095E   4284 	C$TSIPMon.c$970$3$4 ==.
                           4285 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:970: temp.b.lo = RxBuf[val+2];
                           4286 ;	genPlus
                           4287 ;     genPlusIncr
   0A3F 74 02              4288 	mov	a,#0x02
                           4289 ;	Peephole 236.a	used r7 instead of ar7
   0A41 2F                 4290 	add	a,r7
   0A42 FA                 4291 	mov	r2,a
                           4292 ;	Peephole 181	changed mov to clr
   0A43 E4                 4293 	clr	a
                           4294 ;	Peephole 236.b	used r5 instead of ar5
   0A44 3D                 4295 	addc	a,r5
   0A45 FB                 4296 	mov	r3,a
                           4297 ;	genPlus
                           4298 ;	Peephole 236.g	used r2 instead of ar2
   0A46 EA                 4299 	mov	a,r2
   0A47 25 39              4300 	add	a,_SupplementalTiming_RxBuf_1_1
   0A49 F5 82              4301 	mov	dpl,a
                           4302 ;	Peephole 236.g	used r3 instead of ar3
   0A4B EB                 4303 	mov	a,r3
   0A4C 35 3A              4304 	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
   0A4E F5 83              4305 	mov	dph,a
                           4306 ;	genPointerGet
                           4307 ;	genFarPointerGet
   0A50 E0                 4308 	movx	a,@dptr
   0A51 FA                 4309 	mov	r2,a
                           4310 ;	genPointerSet
                           4311 ;	genNearPointerSet
                           4312 ;	genDataPointerSet
   0A52 8A 3C              4313 	mov	(_SupplementalTiming_temp_1_1 + 0x0001),r2
                    0973   4314 	C$TSIPMon.c$971$3$4 ==.
                           4315 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:971: temp.b.llo = RxBuf[val+3];
                           4316 ;	genPlus
                           4317 ;     genPlusIncr
   0A54 74 03              4318 	mov	a,#0x03
                           4319 ;	Peephole 236.a	used r7 instead of ar7
   0A56 2F                 4320 	add	a,r7
   0A57 FF                 4321 	mov	r7,a
                           4322 ;	Peephole 181	changed mov to clr
   0A58 E4                 4323 	clr	a
                           4324 ;	Peephole 236.b	used r5 instead of ar5
   0A59 3D                 4325 	addc	a,r5
   0A5A FD                 4326 	mov	r5,a
                           4327 ;	genPlus
                           4328 ;	Peephole 236.g	used r7 instead of ar7
   0A5B EF                 4329 	mov	a,r7
   0A5C 25 39              4330 	add	a,_SupplementalTiming_RxBuf_1_1
   0A5E F5 82              4331 	mov	dpl,a
                           4332 ;	Peephole 236.g	used r5 instead of ar5
   0A60 ED                 4333 	mov	a,r5
   0A61 35 3A              4334 	addc	a,(_SupplementalTiming_RxBuf_1_1 + 1)
   0A63 F5 83              4335 	mov	dph,a
                           4336 ;	genPointerGet
                           4337 ;	genFarPointerGet
   0A65 E0                 4338 	movx	a,@dptr
   0A66 FA                 4339 	mov	r2,a
                           4340 ;	genPointerSet
                           4341 ;	genNearPointerSet
                           4342 ;	genDataPointerSet
   0A67 8A 3B              4343 	mov	_SupplementalTiming_temp_1_1,r2
                    0988   4344 	C$TSIPMon.c$973$3$4 ==.
                           4345 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:973: val = temp.f;
                           4346 ;	genAssign
                           4347 ;	genCall
   0A69 85 3B 82           4348 	mov	dpl,_SupplementalTiming_temp_1_1
   0A6C 85 3C 83           4349 	mov	dph,(_SupplementalTiming_temp_1_1 + 1)
   0A6F 85 3D F0           4350 	mov	b,(_SupplementalTiming_temp_1_1 + 2)
   0A72 E5 3E              4351 	mov	a,(_SupplementalTiming_temp_1_1 + 3)
   0A74 12 14 08           4352 	lcall	___fs2uchar
   0A77 85 82 3F           4353 	mov	_SupplementalTiming_val_1_1,dpl
                    0999   4354 	C$TSIPMon.c$974$3$4 ==.
                           4355 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:974: fval = ((temp.f - val) * fval);
                           4356 ;	genPointerGet
                           4357 ;	genNearPointerGet
                           4358 ;	genDataPointerGet
   0A7A 85 3B 42           4359 	mov	_SupplementalTiming_sloc1_1_0,_SupplementalTiming_temp_1_1
   0A7D 85 3C 43           4360 	mov	(_SupplementalTiming_sloc1_1_0 + 1),(_SupplementalTiming_temp_1_1 + 1)
   0A80 85 3D 44           4361 	mov	(_SupplementalTiming_sloc1_1_0 + 2),(_SupplementalTiming_temp_1_1 + 2)
   0A83 85 3E 45           4362 	mov	(_SupplementalTiming_sloc1_1_0 + 3),(_SupplementalTiming_temp_1_1 + 3)
                           4363 ;	genCast
   0A86 AF 3F              4364 	mov	r7,_SupplementalTiming_val_1_1
   0A88 7C 00              4365 	mov	r4,#0x00
                           4366 ;	genCall
   0A8A 8F 82              4367 	mov	dpl,r7
   0A8C 8C 83              4368 	mov	dph,r4
   0A8E 12 13 5F           4369 	lcall	___sint2fs
   0A91 AC 82              4370 	mov	r4,dpl
   0A93 AF 83              4371 	mov	r7,dph
   0A95 AA F0              4372 	mov	r2,b
   0A97 FB                 4373 	mov	r3,a
                           4374 ;	genIpush
   0A98 C0 04              4375 	push	ar4
   0A9A C0 07              4376 	push	ar7
   0A9C C0 02              4377 	push	ar2
   0A9E C0 03              4378 	push	ar3
                           4379 ;	genCall
   0AA0 85 42 82           4380 	mov	dpl,_SupplementalTiming_sloc1_1_0
   0AA3 85 43 83           4381 	mov	dph,(_SupplementalTiming_sloc1_1_0 + 1)
   0AA6 85 44 F0           4382 	mov	b,(_SupplementalTiming_sloc1_1_0 + 2)
   0AA9 E5 45              4383 	mov	a,(_SupplementalTiming_sloc1_1_0 + 3)
   0AAB 12 11 62           4384 	lcall	___fssub
   0AAE 85 82 42           4385 	mov	_SupplementalTiming_sloc1_1_0,dpl
   0AB1 85 83 43           4386 	mov	(_SupplementalTiming_sloc1_1_0 + 1),dph
   0AB4 85 F0 44           4387 	mov	(_SupplementalTiming_sloc1_1_0 + 2),b
   0AB7 F5 45              4388 	mov	(_SupplementalTiming_sloc1_1_0 + 3),a
   0AB9 E5 81              4389 	mov	a,sp
   0ABB 24 FC              4390 	add	a,#0xfc
   0ABD F5 81              4391 	mov	sp,a
                           4392 ;	genCall
   0ABF 85 40 82           4393 	mov	dpl,_SupplementalTiming_fval_1_1
   0AC2 85 41 83           4394 	mov	dph,(_SupplementalTiming_fval_1_1 + 1)
   0AC5 12 13 6C           4395 	lcall	___uint2fs
   0AC8 AE 82              4396 	mov	r6,dpl
   0ACA AF 83              4397 	mov	r7,dph
   0ACC AA F0              4398 	mov	r2,b
   0ACE FB                 4399 	mov	r3,a
                           4400 ;	genIpush
   0ACF C0 06              4401 	push	ar6
   0AD1 C0 07              4402 	push	ar7
   0AD3 C0 02              4403 	push	ar2
   0AD5 C0 03              4404 	push	ar3
                           4405 ;	genCall
   0AD7 85 42 82           4406 	mov	dpl,_SupplementalTiming_sloc1_1_0
   0ADA 85 43 83           4407 	mov	dph,(_SupplementalTiming_sloc1_1_0 + 1)
   0ADD 85 44 F0           4408 	mov	b,(_SupplementalTiming_sloc1_1_0 + 2)
   0AE0 E5 45              4409 	mov	a,(_SupplementalTiming_sloc1_1_0 + 3)
   0AE2 12 11 D6           4410 	lcall	___fsmul
   0AE5 AA 82              4411 	mov	r2,dpl
   0AE7 AB 83              4412 	mov	r3,dph
   0AE9 AC F0              4413 	mov	r4,b
   0AEB FD                 4414 	mov	r5,a
   0AEC E5 81              4415 	mov	a,sp
   0AEE 24 FC              4416 	add	a,#0xfc
   0AF0 F5 81              4417 	mov	sp,a
                           4418 ;	genCall
   0AF2 8A 82              4419 	mov	dpl,r2
   0AF4 8B 83              4420 	mov	dph,r3
   0AF6 8C F0              4421 	mov	b,r4
   0AF8 ED                 4422 	mov	a,r5
   0AF9 12 13 78           4423 	lcall	___fs2uint
   0AFC 85 82 40           4424 	mov	_SupplementalTiming_fval_1_1,dpl
   0AFF 85 83 41           4425 	mov	(_SupplementalTiming_fval_1_1 + 1),dph
                    0A21   4426 	C$TSIPMon.c$980$3$4 ==.
                           4427 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:980: strcpy( lcdbuf, prompt[mode-4] );
                           4428 ;	genMinus
                           4429 ;	genMinusDec
   0B02 E5 38              4430 	mov	a,_SupplementalTiming_mode_1_1
   0B04 24 FC              4431 	add	a,#0xfc
                           4432 ;	genMult
                           4433 ;	genMultOneByte
   0B06 75 F0 09           4434 	mov	b,#0x09
   0B09 A4                 4435 	mul	ab
                           4436 ;	genPlus
   0B0A 24 E4              4437 	add	a,#_prompt
   0B0C FA                 4438 	mov	r2,a
                           4439 ;	Peephole 240	use clr instead of addc a,#0
   0B0D E4                 4440 	clr	a
   0B0E 34 17              4441 	addc	a,#(_prompt >> 8)
   0B10 FB                 4442 	mov	r3,a
                           4443 ;	genCast
   0B11 8A 46              4444 	mov	_strcpy_PARM_2,r2
   0B13 8B 47              4445 	mov	(_strcpy_PARM_2 + 1),r3
   0B15 75 48 80           4446 	mov	(_strcpy_PARM_2 + 2),#0x80
                           4447 ;	genCall
                           4448 ;	Peephole 182.a	used 16 bit load of DPTR
   0B18 90 00 02           4449 	mov	dptr,#_lcdbuf
   0B1B 75 F0 00           4450 	mov	b,#0x00
   0B1E 12 11 96           4451 	lcall	_strcpy
                    0A40   4452 	C$TSIPMon.c$981$3$4 ==.
                           4453 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:981: UnsignedToAscii( val, lcdbuf+6, 3 );
                           4454 ;	genCast
   0B21 AC 3F              4455 	mov	r4,_SupplementalTiming_val_1_1
   0B23 7A 00              4456 	mov	r2,#0x00
                           4457 ;	genPlus
                           4458 ;     genPlusIncr
   0B25 74 06              4459 	mov	a,#0x06
   0B27 24 02              4460 	add	a,#_lcdbuf
   0B29 F5 1B              4461 	mov	_UnsignedToAscii_PARM_2,a
                           4462 ;	Peephole 181	changed mov to clr
   0B2B E4                 4463 	clr	a
   0B2C 34 00              4464 	addc	a,#(_lcdbuf >> 8)
   0B2E F5 1C              4465 	mov	(_UnsignedToAscii_PARM_2 + 1),a
                           4466 ;	genAssign
   0B30 75 1D 03           4467 	mov	_UnsignedToAscii_PARM_3,#0x03
                           4468 ;	genCall
   0B33 8C 82              4469 	mov	dpl,r4
   0B35 8A 83              4470 	mov	dph,r2
   0B37 12 0E FB           4471 	lcall	_UnsignedToAscii
                    0A59   4472 	C$TSIPMon.c$982$3$4 ==.
                           4473 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:982: lcdbuf[9] = '.';
                           4474 ;	genPointerSet
                           4475 ;     genFarPointerSet
   0B3A 90 00 0B           4476 	mov	dptr,#(_lcdbuf + 0x0009)
   0B3D 74 2E              4477 	mov	a,#0x2E
   0B3F F0                 4478 	movx	@dptr,a
                    0A5F   4479 	C$TSIPMon.c$983$3$4 ==.
                           4480 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:983: UnsignedToAscii( fval, lcdbuf+10, 2 + 2*(mode-4) );
                           4481 ;	genPlus
                           4482 ;     genPlusIncr
   0B40 74 0A              4483 	mov	a,#0x0A
   0B42 24 02              4484 	add	a,#_lcdbuf
   0B44 F5 1B              4485 	mov	_UnsignedToAscii_PARM_2,a
                           4486 ;	Peephole 181	changed mov to clr
   0B46 E4                 4487 	clr	a
   0B47 34 00              4488 	addc	a,#(_lcdbuf >> 8)
   0B49 F5 1C              4489 	mov	(_UnsignedToAscii_PARM_2 + 1),a
                           4490 ;	genMinus
                           4491 ;	genMinusDec
   0B4B E5 38              4492 	mov	a,_SupplementalTiming_mode_1_1
   0B4D 24 FC              4493 	add	a,#0xfc
                           4494 ;	genLeftShift
                           4495 ;	genLeftShiftLiteral
                           4496 ;	genlshOne
                           4497 ;	Peephole 105	removed redundant mov
                           4498 ;	Peephole 204	removed redundant mov
   0B4F 25 E0              4499 	add	a,acc
                           4500 ;	genPlus
                           4501 ;     genPlusIncr
                           4502 ;	Peephole 236.a	used r2 instead of ar2
   0B51 FA                 4503 	mov	r2,a
                           4504 ;	Peephole 214	reduced some extra moves
   0B52 24 02              4505 	add	a,#0x02
   0B54 F5 1D              4506 	mov	_UnsignedToAscii_PARM_3,a
                           4507 ;	genCall
   0B56 85 40 82           4508 	mov	dpl,_SupplementalTiming_fval_1_1
   0B59 85 41 83           4509 	mov	dph,(_SupplementalTiming_fval_1_1 + 1)
   0B5C 12 0E FB           4510 	lcall	_UnsignedToAscii
                    0A7E   4511 	C$TSIPMon.c$985$2$1 ==.
                           4512 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:985: for( val=0; val<3; val++ ){
                           4513 ;	genAssign
   0B5F 7A 00              4514 	mov	r2,#0x00
   0B61                    4515 00121$:
                           4516 ;	genCmpLt
                           4517 ;	genCmp
   0B61 BA 03 00           4518 	cjne	r2,#0x03,00154$
   0B64                    4519 00154$:
                           4520 ;	genIfxJump
                           4521 ;	Peephole 108.a	removed ljmp by inverse jump logic
   0B64 50 23              4522 	jnc	00125$
                           4523 ;	Peephole 300	removed redundant label 00155$
                    0A85   4524 	C$TSIPMon.c$986$4$5 ==.
                           4525 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:986: if( lcdbuf[10+val] == ' ' ) 
                           4526 ;	genPlus
                           4527 ;     genPlusIncr
   0B66 74 0A              4528 	mov	a,#0x0A
                           4529 ;	Peephole 236.a	used r2 instead of ar2
   0B68 2A                 4530 	add	a,r2
                           4531 ;	genPlus
   0B69 24 02              4532 	add	a,#_lcdbuf
   0B6B F5 82              4533 	mov	dpl,a
                           4534 ;	Peephole 240	use clr instead of addc a,#0
   0B6D E4                 4535 	clr	a
   0B6E 34 00              4536 	addc	a,#(_lcdbuf >> 8)
   0B70 F5 83              4537 	mov	dph,a
                           4538 ;	genPointerGet
                           4539 ;	genFarPointerGet
   0B72 E0                 4540 	movx	a,@dptr
   0B73 FB                 4541 	mov	r3,a
                           4542 ;	genCmpEq
                           4543 ;	gencjneshort
                           4544 ;	Peephole 112.b	changed ljmp to sjmp
                           4545 ;	Peephole 198.b	optimized misc jump sequence
   0B74 BB 20 12           4546 	cjne	r3,#0x20,00125$
                           4547 ;	Peephole 200.b	removed redundant sjmp
                           4548 ;	Peephole 300	removed redundant label 00156$
                           4549 ;	Peephole 300	removed redundant label 00157$
                    0A96   4550 	C$TSIPMon.c$987$4$5 ==.
                           4551 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:987: lcdbuf[10+val] = '0';
                           4552 ;	genPlus
                           4553 ;     genPlusIncr
   0B77 74 0A              4554 	mov	a,#0x0A
                           4555 ;	Peephole 236.a	used r2 instead of ar2
   0B79 2A                 4556 	add	a,r2
                           4557 ;	genPlus
   0B7A 24 02              4558 	add	a,#_lcdbuf
   0B7C F5 82              4559 	mov	dpl,a
                           4560 ;	Peephole 240	use clr instead of addc a,#0
   0B7E E4                 4561 	clr	a
   0B7F 34 00              4562 	addc	a,#(_lcdbuf >> 8)
   0B81 F5 83              4563 	mov	dph,a
                           4564 ;	genPointerSet
                           4565 ;     genFarPointerSet
   0B83 74 30              4566 	mov	a,#0x30
   0B85 F0                 4567 	movx	@dptr,a
                    0AA5   4568 	C$TSIPMon.c$985$3$4 ==.
                           4569 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:985: for( val=0; val<3; val++ ){
                           4570 ;	genPlus
                           4571 ;     genPlusIncr
   0B86 0A                 4572 	inc	r2
                    0AA6   4573 	C$TSIPMon.c$993$2$3 ==.
                           4574 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:993: } // switch( mode )
                           4575 ;	Peephole 112.b	changed ljmp to sjmp
   0B87 80 D8              4576 	sjmp	00121$
   0B89                    4577 00125$:
                    0AA8   4578 	C$TSIPMon.c$994$2$3 ==.
                           4579 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:994: printLCD( 2, lcdbuf, 0 );
                           4580 ;	genAddrOf
   0B89 75 08 02           4581 	mov	_printLCD_PARM_2,#_lcdbuf
   0B8C 75 09 00           4582 	mov	(_printLCD_PARM_2 + 1),#(_lcdbuf >> 8)
                           4583 ;	genAssign
   0B8F 75 0A 00           4584 	mov	_printLCD_PARM_3,#0x00
                           4585 ;	genCall
   0B92 75 82 02           4586 	mov	dpl,#0x02
                    0AB4   4587 	C$TSIPMon.c$997$2$1 ==.
                    0AB4   4588 	XG$SupplementalTiming$0$0 ==.
                           4589 ;	Peephole 253.b	replaced lcall/ret with ljmp
   0B95 02 0D 14           4590 	ljmp	_printLCD
                           4591 ;
                           4592 ;------------------------------------------------------------
                           4593 ;Allocation info for local variables in function 'clr_LCDBuf'
                           4594 ;------------------------------------------------------------
                           4595 ;i                         Allocated to registers r2 
                           4596 ;------------------------------------------------------------
                    0AB7   4597 	G$clr_LCDBuf$0$0 ==.
                    0AB7   4598 	C$TSIPMon.c$1002$2$1 ==.
                           4599 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1002: void clr_LCDBuf( void ){
                           4600 ;	-----------------------------------------
                           4601 ;	 function clr_LCDBuf
                           4602 ;	-----------------------------------------
   0B98                    4603 _clr_LCDBuf:
                    0AB7   4604 	C$TSIPMon.c$1006$1$1 ==.
                           4605 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1006: for( i=0; i<LCD_SIZE; i++ )
                           4606 ;	genAssign
   0B98 7A 00              4607 	mov	r2,#0x00
   0B9A                    4608 00101$:
                           4609 ;	genCmpLt
                           4610 ;	genCmp
   0B9A BA 14 00           4611 	cjne	r2,#0x14,00110$
   0B9D                    4612 00110$:
                           4613 ;	genIfxJump
                           4614 ;	Peephole 108.a	removed ljmp by inverse jump logic
   0B9D 50 10              4615 	jnc	00104$
                           4616 ;	Peephole 300	removed redundant label 00111$
                    0ABE   4617 	C$TSIPMon.c$1007$1$1 ==.
                           4618 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1007: lcdbuf[i] = ' ';
                           4619 ;	genPlus
                           4620 ;	Peephole 236.g	used r2 instead of ar2
   0B9F EA                 4621 	mov	a,r2
   0BA0 24 02              4622 	add	a,#_lcdbuf
   0BA2 F5 82              4623 	mov	dpl,a
                           4624 ;	Peephole 181	changed mov to clr
   0BA4 E4                 4625 	clr	a
   0BA5 34 00              4626 	addc	a,#(_lcdbuf >> 8)
   0BA7 F5 83              4627 	mov	dph,a
                           4628 ;	genPointerSet
                           4629 ;     genFarPointerSet
   0BA9 74 20              4630 	mov	a,#0x20
   0BAB F0                 4631 	movx	@dptr,a
                    0ACB   4632 	C$TSIPMon.c$1006$1$1 ==.
                           4633 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1006: for( i=0; i<LCD_SIZE; i++ )
                           4634 ;	genPlus
                           4635 ;     genPlusIncr
   0BAC 0A                 4636 	inc	r2
                           4637 ;	Peephole 112.b	changed ljmp to sjmp
   0BAD 80 EB              4638 	sjmp	00101$
   0BAF                    4639 00104$:
                    0ACE   4640 	C$TSIPMon.c$1008$1$1 ==.
                           4641 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1008: lcdbuf[i] = '\0';
                           4642 ;	genPlus
                           4643 ;	Peephole 236.g	used r2 instead of ar2
   0BAF EA                 4644 	mov	a,r2
   0BB0 24 02              4645 	add	a,#_lcdbuf
   0BB2 F5 82              4646 	mov	dpl,a
                           4647 ;	Peephole 181	changed mov to clr
   0BB4 E4                 4648 	clr	a
   0BB5 34 00              4649 	addc	a,#(_lcdbuf >> 8)
   0BB7 F5 83              4650 	mov	dph,a
                           4651 ;	genPointerSet
                           4652 ;     genFarPointerSet
                           4653 ;	Peephole 181	changed mov to clr
   0BB9 E4                 4654 	clr	a
   0BBA F0                 4655 	movx	@dptr,a
                           4656 ;	Peephole 300	removed redundant label 00105$
                    0ADA   4657 	C$TSIPMon.c$1010$1$1 ==.
                    0ADA   4658 	XG$clr_LCDBuf$0$0 ==.
   0BBB 22                 4659 	ret
                           4660 ;------------------------------------------------------------
                           4661 ;Allocation info for local variables in function 'External_Interrupt_0'
                           4662 ;------------------------------------------------------------
                           4663 ;------------------------------------------------------------
                    0ADB   4664 	G$External_Interrupt_0$0$0 ==.
                    0ADB   4665 	C$TSIPMon.c$1017$1$1 ==.
                           4666 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1017: void External_Interrupt_0( void ) interrupt 0{
                           4667 ;	-----------------------------------------
                           4668 ;	 function External_Interrupt_0
                           4669 ;	-----------------------------------------
   0BBC                    4670 _External_Interrupt_0:
   0BBC C0 E0              4671 	push	acc
   0BBE C0 F0              4672 	push	b
   0BC0 C0 82              4673 	push	dpl
   0BC2 C0 83              4674 	push	dph
   0BC4 C0 02              4675 	push	(0+2)
   0BC6 C0 03              4676 	push	(0+3)
   0BC8 C0 04              4677 	push	(0+4)
   0BCA C0 05              4678 	push	(0+5)
   0BCC C0 06              4679 	push	(0+6)
   0BCE C0 07              4680 	push	(0+7)
   0BD0 C0 00              4681 	push	(0+0)
   0BD2 C0 01              4682 	push	(0+1)
   0BD4 C0 D0              4683 	push	psw
   0BD6 75 D0 00           4684 	mov	psw,#0x00
                           4685 ;	genIfx
                           4686 ;	genIfxJump
                           4687 ;	Peephole 108.d	removed ljmp by inverse jump logic
                    0AF8   4688 	C$TSIPMon.c$1022$2$2 ==.
                           4689 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1022: switch2 = 0;
                           4690 ;	genAssign
                           4691 ;	Peephole 250.a	using atomic test and clear
   0BD9 10 02 02           4692 	jbc	_switch2,00106$
   0BDC 80 0C              4693 	sjmp	00103$
   0BDE                    4694 00106$:
                    0AFD   4695 	C$TSIPMon.c$1025$2$2 ==.
                           4696 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1025: TimerStart( SWITCH_TIMER, 50 );	// to reset switch2 to 1
                           4697 ;	genAssign
   0BDE 75 0E 32           4698 	mov	_TimerStart_PARM_2,#0x32
   0BE1 E4                 4699 	clr	a
   0BE2 F5 0F              4700 	mov	(_TimerStart_PARM_2 + 1),a
                           4701 ;	genCall
   0BE4 75 82 02           4702 	mov	dpl,#0x02
   0BE7 12 03 39           4703 	lcall	_TimerStart
   0BEA                    4704 00103$:
   0BEA D0 D0              4705 	pop	psw
   0BEC D0 01              4706 	pop	(0+1)
   0BEE D0 00              4707 	pop	(0+0)
   0BF0 D0 07              4708 	pop	(0+7)
   0BF2 D0 06              4709 	pop	(0+6)
   0BF4 D0 05              4710 	pop	(0+5)
   0BF6 D0 04              4711 	pop	(0+4)
   0BF8 D0 03              4712 	pop	(0+3)
   0BFA D0 02              4713 	pop	(0+2)
   0BFC D0 83              4714 	pop	dph
   0BFE D0 82              4715 	pop	dpl
   0C00 D0 F0              4716 	pop	b
   0C02 D0 E0              4717 	pop	acc
                    0B23   4718 	C$TSIPMon.c$1028$2$1 ==.
                    0B23   4719 	XG$External_Interrupt_0$0$0 ==.
   0C04 32                 4720 	reti
                           4721 ;------------------------------------------------------------
                           4722 ;Allocation info for local variables in function 'External_Interrupt_1'
                           4723 ;------------------------------------------------------------
                           4724 ;------------------------------------------------------------
                    0B24   4725 	G$External_Interrupt_1$0$0 ==.
                    0B24   4726 	C$TSIPMon.c$1034$2$1 ==.
                           4727 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1034: void External_Interrupt_1( void ) interrupt 2{
                           4728 ;	-----------------------------------------
                           4729 ;	 function External_Interrupt_1
                           4730 ;	-----------------------------------------
   0C05                    4731 _External_Interrupt_1:
   0C05 C0 E0              4732 	push	acc
   0C07 C0 F0              4733 	push	b
   0C09 C0 82              4734 	push	dpl
   0C0B C0 83              4735 	push	dph
   0C0D C0 02              4736 	push	(0+2)
   0C0F C0 03              4737 	push	(0+3)
   0C11 C0 04              4738 	push	(0+4)
   0C13 C0 05              4739 	push	(0+5)
   0C15 C0 06              4740 	push	(0+6)
   0C17 C0 07              4741 	push	(0+7)
   0C19 C0 00              4742 	push	(0+0)
   0C1B C0 01              4743 	push	(0+1)
   0C1D C0 D0              4744 	push	psw
   0C1F 75 D0 00           4745 	mov	psw,#0x00
                           4746 ;	genIfx
                           4747 ;	genIfxJump
                           4748 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0C22 30 03 18           4749 	jnb	_switch1,00104$
                           4750 ;	Peephole 300	removed redundant label 00108$
                    0B44   4751 	C$TSIPMon.c$1037$1$1 ==.
                           4752 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1037: if( switch1 != 0 && !TimerRunning( SWITCH_TIMER )){
                           4753 ;	genCall
   0C25 75 82 02           4754 	mov	dpl,#0x02
   0C28 12 03 56           4755 	lcall	_TimerRunning
                           4756 ;	genIfx
                           4757 ;	genIfxJump
                           4758 ;	Peephole 108.b	removed ljmp by inverse jump logic
                           4759 ;	Peephole 129.a	jump optimization
   0C2B 40 10              4760 	jc	00104$
                           4761 ;	Peephole 300	removed redundant label 00109$
                    0B4C   4762 	C$TSIPMon.c$1039$2$2 ==.
                           4763 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1039: switch1 = 0;
                           4764 ;	genAssign
   0C2D C2 03              4765 	clr	_switch1
                    0B4E   4766 	C$TSIPMon.c$1040$2$2 ==.
                           4767 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1040: func1 = TRUE;
                           4768 ;	genAssign
   0C2F D2 05              4769 	setb	_func1
                    0B50   4770 	C$TSIPMon.c$1042$2$2 ==.
                           4771 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1042: TimerStart( SWITCH_TIMER, 150 );	// to reset switch1 to 1
                           4772 ;	genAssign
   0C31 75 0E 96           4773 	mov	_TimerStart_PARM_2,#0x96
   0C34 E4                 4774 	clr	a
   0C35 F5 0F              4775 	mov	(_TimerStart_PARM_2 + 1),a
                           4776 ;	genCall
   0C37 75 82 02           4777 	mov	dpl,#0x02
   0C3A 12 03 39           4778 	lcall	_TimerStart
   0C3D                    4779 00104$:
   0C3D D0 D0              4780 	pop	psw
   0C3F D0 01              4781 	pop	(0+1)
   0C41 D0 00              4782 	pop	(0+0)
   0C43 D0 07              4783 	pop	(0+7)
   0C45 D0 06              4784 	pop	(0+6)
   0C47 D0 05              4785 	pop	(0+5)
   0C49 D0 04              4786 	pop	(0+4)
   0C4B D0 03              4787 	pop	(0+3)
   0C4D D0 02              4788 	pop	(0+2)
   0C4F D0 83              4789 	pop	dph
   0C51 D0 82              4790 	pop	dpl
   0C53 D0 F0              4791 	pop	b
   0C55 D0 E0              4792 	pop	acc
                    0B76   4793 	C$TSIPMon.c$1045$2$1 ==.
                    0B76   4794 	XG$External_Interrupt_1$0$0 ==.
   0C57 32                 4795 	reti
                           4796 ;------------------------------------------------------------
                           4797 ;Allocation info for local variables in function 'Timer_1_Overflow'
                           4798 ;------------------------------------------------------------
                           4799 ;------------------------------------------------------------
                    0B77   4800 	G$Timer_1_Overflow$0$0 ==.
                    0B77   4801 	C$TSIPMon.c$1053$2$1 ==.
                           4802 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1053: void Timer_1_Overflow( void ) interrupt 3{}
                           4803 ;	-----------------------------------------
                           4804 ;	 function Timer_1_Overflow
                           4805 ;	-----------------------------------------
   0C58                    4806 _Timer_1_Overflow:
                           4807 ;	Peephole 300	removed redundant label 00101$
                    0B77   4808 	C$TSIPMon.c$1053$2$1 ==.
                    0B77   4809 	XG$Timer_1_Overflow$0$0 ==.
   0C58 32                 4810 	reti
                           4811 ;	eliminated unneeded push/pop psw
                           4812 ;	eliminated unneeded push/pop dpl
                           4813 ;	eliminated unneeded push/pop dph
                           4814 ;	eliminated unneeded push/pop b
                           4815 ;	eliminated unneeded push/pop acc
                           4816 ;------------------------------------------------------------
                           4817 ;Allocation info for local variables in function 'SPI0'
                           4818 ;------------------------------------------------------------
                           4819 ;------------------------------------------------------------
                    0B78   4820 	G$SPI0$0$0 ==.
                    0B78   4821 	C$TSIPMon.c$1056$2$1 ==.
                           4822 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1056: void SPI0( void ) interrupt 6{}
                           4823 ;	-----------------------------------------
                           4824 ;	 function SPI0
                           4825 ;	-----------------------------------------
   0C59                    4826 _SPI0:
                           4827 ;	Peephole 300	removed redundant label 00101$
                    0B78   4828 	C$TSIPMon.c$1056$2$1 ==.
                    0B78   4829 	XG$SPI0$0$0 ==.
   0C59 32                 4830 	reti
                           4831 ;	eliminated unneeded push/pop psw
                           4832 ;	eliminated unneeded push/pop dpl
                           4833 ;	eliminated unneeded push/pop dph
                           4834 ;	eliminated unneeded push/pop b
                           4835 ;	eliminated unneeded push/pop acc
                           4836 ;------------------------------------------------------------
                           4837 ;Allocation info for local variables in function 'SMB0'
                           4838 ;------------------------------------------------------------
                           4839 ;------------------------------------------------------------
                    0B79   4840 	G$SMB0$0$0 ==.
                    0B79   4841 	C$TSIPMon.c$1057$2$1 ==.
                           4842 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1057: void SMB0( void ) interrupt 7{}
                           4843 ;	-----------------------------------------
                           4844 ;	 function SMB0
                           4845 ;	-----------------------------------------
   0C5A                    4846 _SMB0:
                           4847 ;	Peephole 300	removed redundant label 00101$
                    0B79   4848 	C$TSIPMon.c$1057$2$1 ==.
                    0B79   4849 	XG$SMB0$0$0 ==.
   0C5A 32                 4850 	reti
                           4851 ;	eliminated unneeded push/pop psw
                           4852 ;	eliminated unneeded push/pop dpl
                           4853 ;	eliminated unneeded push/pop dph
                           4854 ;	eliminated unneeded push/pop b
                           4855 ;	eliminated unneeded push/pop acc
                           4856 ;------------------------------------------------------------
                           4857 ;Allocation info for local variables in function 'ADC0_Window_Comparator'
                           4858 ;------------------------------------------------------------
                           4859 ;------------------------------------------------------------
                    0B7A   4860 	G$ADC0_Window_Comparator$0$0 ==.
                    0B7A   4861 	C$TSIPMon.c$1059$2$1 ==.
                           4862 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1059: void ADC0_Window_Comparator( void ) interrupt 9{}
                           4863 ;	-----------------------------------------
                           4864 ;	 function ADC0_Window_Comparator
                           4865 ;	-----------------------------------------
   0C5B                    4866 _ADC0_Window_Comparator:
                           4867 ;	Peephole 300	removed redundant label 00101$
                    0B7A   4868 	C$TSIPMon.c$1059$2$1 ==.
                    0B7A   4869 	XG$ADC0_Window_Comparator$0$0 ==.
   0C5B 32                 4870 	reti
                           4871 ;	eliminated unneeded push/pop psw
                           4872 ;	eliminated unneeded push/pop dpl
                           4873 ;	eliminated unneeded push/pop dph
                           4874 ;	eliminated unneeded push/pop b
                           4875 ;	eliminated unneeded push/pop acc
                           4876 ;------------------------------------------------------------
                           4877 ;Allocation info for local variables in function 'ADC0_End_of_Conversion'
                           4878 ;------------------------------------------------------------
                           4879 ;------------------------------------------------------------
                    0B7B   4880 	G$ADC0_End_of_Conversion$0$0 ==.
                    0B7B   4881 	C$TSIPMon.c$1060$2$1 ==.
                           4882 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1060: void ADC0_End_of_Conversion( void ) interrupt 10{}
                           4883 ;	-----------------------------------------
                           4884 ;	 function ADC0_End_of_Conversion
                           4885 ;	-----------------------------------------
   0C5C                    4886 _ADC0_End_of_Conversion:
                           4887 ;	Peephole 300	removed redundant label 00101$
                    0B7B   4888 	C$TSIPMon.c$1060$2$1 ==.
                    0B7B   4889 	XG$ADC0_End_of_Conversion$0$0 ==.
   0C5C 32                 4890 	reti
                           4891 ;	eliminated unneeded push/pop psw
                           4892 ;	eliminated unneeded push/pop dpl
                           4893 ;	eliminated unneeded push/pop dph
                           4894 ;	eliminated unneeded push/pop b
                           4895 ;	eliminated unneeded push/pop acc
                           4896 ;------------------------------------------------------------
                           4897 ;Allocation info for local variables in function 'Programmable_Counter_Array'
                           4898 ;------------------------------------------------------------
                           4899 ;------------------------------------------------------------
                    0B7C   4900 	G$Programmable_Counter_Array$0$0 ==.
                    0B7C   4901 	C$TSIPMon.c$1061$2$1 ==.
                           4902 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1061: void Programmable_Counter_Array( void ) interrupt 11{}
                           4903 ;	-----------------------------------------
                           4904 ;	 function Programmable_Counter_Array
                           4905 ;	-----------------------------------------
   0C5D                    4906 _Programmable_Counter_Array:
                           4907 ;	Peephole 300	removed redundant label 00101$
                    0B7C   4908 	C$TSIPMon.c$1061$2$1 ==.
                    0B7C   4909 	XG$Programmable_Counter_Array$0$0 ==.
   0C5D 32                 4910 	reti
                           4911 ;	eliminated unneeded push/pop psw
                           4912 ;	eliminated unneeded push/pop dpl
                           4913 ;	eliminated unneeded push/pop dph
                           4914 ;	eliminated unneeded push/pop b
                           4915 ;	eliminated unneeded push/pop acc
                           4916 ;------------------------------------------------------------
                           4917 ;Allocation info for local variables in function 'Comparator'
                           4918 ;------------------------------------------------------------
                           4919 ;------------------------------------------------------------
                    0B7D   4920 	G$Comparator$0$0 ==.
                    0B7D   4921 	C$TSIPMon.c$1062$2$1 ==.
                           4922 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1062: void Comparator( void ) interrupt 12{}
                           4923 ;	-----------------------------------------
                           4924 ;	 function Comparator
                           4925 ;	-----------------------------------------
   0C5E                    4926 _Comparator:
                           4927 ;	Peephole 300	removed redundant label 00101$
                    0B7D   4928 	C$TSIPMon.c$1062$2$1 ==.
                    0B7D   4929 	XG$Comparator$0$0 ==.
   0C5E 32                 4930 	reti
                           4931 ;	eliminated unneeded push/pop psw
                           4932 ;	eliminated unneeded push/pop dpl
                           4933 ;	eliminated unneeded push/pop dph
                           4934 ;	eliminated unneeded push/pop b
                           4935 ;	eliminated unneeded push/pop acc
                           4936 ;------------------------------------------------------------
                           4937 ;Allocation info for local variables in function 'Timer_3_Overflow'
                           4938 ;------------------------------------------------------------
                           4939 ;------------------------------------------------------------
                    0B7E   4940 	G$Timer_3_Overflow$0$0 ==.
                    0B7E   4941 	C$TSIPMon.c$1064$2$1 ==.
                           4942 ;	C:/SDCC/GPSMon/dev/TSIPMon.c:1064: void Timer_3_Overflow( void ) interrupt 14{}
                           4943 ;	-----------------------------------------
                           4944 ;	 function Timer_3_Overflow
                           4945 ;	-----------------------------------------
   0C5F                    4946 _Timer_3_Overflow:
                           4947 ;	Peephole 300	removed redundant label 00101$
                    0B7E   4948 	C$TSIPMon.c$1064$2$1 ==.
                    0B7E   4949 	XG$Timer_3_Overflow$0$0 ==.
   0C5F 32                 4950 	reti
                           4951 ;	eliminated unneeded push/pop psw
                           4952 ;	eliminated unneeded push/pop dpl
                           4953 ;	eliminated unneeded push/pop dph
                           4954 ;	eliminated unneeded push/pop b
                           4955 ;	eliminated unneeded push/pop acc
                           4956 	.area CSEG    (CODE)
                           4957 	.area CONST   (CODE)
                    0000   4958 G$Month$0$0 == .
   14D0                    4959 _Month:
   14D0 4A 61 6E 46 65 62  4960 	.ascii "JanFebMarAprMayJunJulAugSepOctNovDec"
        4D 61 72 41 70 72
        4D 61 79 4A 75 6E
        4A 75 6C 41 75 67
        53 65 70 4F 63 74
        4E 6F 76 44 65 63
   14F4 00                 4961 	.db 0x00
                    0025   4962 G$DIM$0$0 == .
   14F5                    4963 _DIM:
   14F5 1F                 4964 	.db #0x1F
   14F6 1C                 4965 	.db #0x1C
   14F7 1F                 4966 	.db #0x1F
   14F8 1E                 4967 	.db #0x1E
   14F9 1F                 4968 	.db #0x1F
   14FA 1E                 4969 	.db #0x1E
   14FB 1F                 4970 	.db #0x1F
   14FC 1F                 4971 	.db #0x1F
   14FD 1E                 4972 	.db #0x1E
   14FE 1F                 4973 	.db #0x1F
   14FF 1E                 4974 	.db #0x1E
   1500 1F                 4975 	.db #0x1F
                    0031   4976 G$RxMode$0$0 == .
   1501                    4977 _RxMode:
   1501 52 58 3A 20 41 75  4978 	.ascii "RX: Auto 2D/3D"
        74 6F 20 32 44 2F
        33 44
   150F 00                 4979 	.db 0x00
   1510 00                 4980 	.db 0x00
   1511 00                 4981 	.db 0x00
   1512 52 58 3A 20 53 69  4982 	.ascii "RX: Single Sat"
        6E 67 6C 65 20 53
        61 74
   1520 00                 4983 	.db 0x00
   1521 00                 4984 	.db 0x00
   1522 00                 4985 	.db 0x00
   1523 52 58 3A 20 55 6E  4986 	.ascii "RX: Unknown!!!"
        6B 6E 6F 77 6E 21
        21 21
   1531 00                 4987 	.db 0x00
   1532 00                 4988 	.db 0x00
   1533 00                 4989 	.db 0x00
   1534 52 58 3A 20 48 6F  4990 	.ascii "RX: Horiz. (2D)"
        72 69 7A 2E 20 28
        32 44 29
   1543 00                 4991 	.db 0x00
   1544 00                 4992 	.db 0x00
   1545 52 58 3A 20 46 75  4993 	.ascii "RX: Full Pos(3D)"
        6C 6C 20 50 6F 73
        28 33 44 29
   1555 00                 4994 	.db 0x00
   1556 52 58 3A 20 44 47  4995 	.ascii "RX: DGPS Refer"
        50 53 20 52 65 66
        65 72
   1564 00                 4996 	.db 0x00
   1565 00                 4997 	.db 0x00
   1566 00                 4998 	.db 0x00
   1567 52 58 3A 20 43 6C  4999 	.ascii "RX: Clk Hold(2D)"
        6B 20 48 6F 6C 64
        28 32 44 29
   1577 00                 5000 	.db 0x00
   1578 52 58 3A 20 4F 76  5001 	.ascii "RX: Overdet Clk"
        65 72 64 65 74 20
        43 6C 6B
   1587 00                 5002 	.db 0x00
   1588 00                 5003 	.db 0x00
                    00B9   5004 G$DiscMode$0$0 == .
   1589                    5005 _DiscMode:
   1589 4D 4F 44 45 3A 20  5006 	.ascii "MODE: Normal"
        4E 6F 72 6D 61 6C
   1595 00                 5007 	.db 0x00
   1596 00                 5008 	.db 0x00
   1597 00                 5009 	.db 0x00
   1598 00                 5010 	.db 0x00
   1599 0C                 5011 	.db 0x0C
   159A 4D 4F 44 45 3A 20  5012 	.ascii "MODE: Power-Up"
        50 6F 77 65 72 2D
        55 70
   15A8 00                 5013 	.db 0x00
   15A9 00                 5014 	.db 0x00
   15AA 00                 5015 	.db 0x00
   15AB 4D 4F 44 45 3A 20  5016 	.ascii "MODE: Auto Hldvr"
        41 75 74 6F 20 48
        6C 64 76 72
   15BB 00                 5017 	.db 0x00
   15BC 4D 4F 44 45 3A 20  5018 	.ascii "MODE: Man. Hldvr"
        4D 61 6E 2E 20 48
        6C 64 76 72
   15CC 00                 5019 	.db 0x00
   15CD 4D 4F 44 45 3A 20  5020 	.ascii "MODE: Recovery"
        52 65 63 6F 76 65
        72 79
   15DB 00                 5021 	.db 0x00
   15DC 00                 5022 	.db 0x00
   15DD 00                 5023 	.db 0x00
   15DE 4D 4F 44 45 3A 20  5024 	.ascii "MODE: Unknown!!!"
        55 6E 6B 6E 6F 77
        6E 21 21 21
   15EE 00                 5025 	.db 0x00
   15EF 4D 4F 44 45 3A 20  5026 	.ascii "MODE: Disabled"
        44 69 73 61 62 6C
        65 64
   15FD 00                 5027 	.db 0x00
   15FE 00                 5028 	.db 0x00
   15FF 00                 5029 	.db 0x00
                    0130   5030 G$GPSDecodeStatus$0$0 == .
   1600                    5031 _GPSDecodeStatus:
   1600 47 50 53 3A 20 44  5032 	.ascii "GPS: Doing Fixes"
        6F 69 6E 67 20 46
        69 78 65 73
   1610 00                 5033 	.db 0x00
   1611 47 50 53 3A 20 4E  5034 	.ascii "GPS: No GPS Time"
        6F 20 47 50 53 20
        54 69 6D 65
   1621 00                 5035 	.db 0x00
   1622 47 50 53 3A 20 55  5036 	.ascii "GPS: Unknown!!!"
        6E 6B 6E 6F 77 6E
        21 21 21
   1631 00                 5037 	.db 0x00
   1632 00                 5038 	.db 0x00
   1633 47 50 53 3A 20 50  5039 	.ascii "GPS: PDOP to HI"
        44 4F 50 20 74 6F
        20 48 49
   1642 00                 5040 	.db 0x00
   1643 00                 5041 	.db 0x00
   1644 47 50 53 3A 20 55  5042 	.ascii "GPS: Unknown!!!"
        6E 6B 6E 6F 77 6E
        21 21 21
   1653 00                 5043 	.db 0x00
   1654 00                 5044 	.db 0x00
   1655 47 50 53 3A 20 55  5045 	.ascii "GPS: Unknown!!!"
        6E 6B 6E 6F 77 6E
        21 21 21
   1664 00                 5046 	.db 0x00
   1665 00                 5047 	.db 0x00
   1666 47 50 53 3A 20 55  5048 	.ascii "GPS: Unknown!!!"
        6E 6B 6E 6F 77 6E
        21 21 21
   1675 00                 5049 	.db 0x00
   1676 00                 5050 	.db 0x00
   1677 47 50 53 3A 20 55  5051 	.ascii "GPS: Unknown!!!"
        6E 6B 6E 6F 77 6E
        21 21 21
   1686 00                 5052 	.db 0x00
   1687 00                 5053 	.db 0x00
   1688 47 50 53 3A 20 4E  5054 	.ascii "GPS: No Use SATS"
        6F 20 55 73 65 20
        53 41 54 53
   1698 00                 5055 	.db 0x00
   1699 47 50 53 3A 20 4F  5056 	.ascii "GPS: Only 1 SAT"
        6E 6C 79 20 31 20
        53 41 54
   16A8 00                 5057 	.db 0x00
   16A9 00                 5058 	.db 0x00
   16AA 47 50 53 3A 20 4F  5059 	.ascii "GPS: Only 2 SATS"
        6E 6C 79 20 32 20
        53 41 54 53
   16BA 00                 5060 	.db 0x00
   16BB 47 50 53 3A 20 4F  5061 	.ascii "GPS: Only 3 SATS"
        6E 6C 79 20 33 20
        53 41 54 53
   16CB 00                 5062 	.db 0x00
   16CC 47 50 53 3A 20 53  5063 	.ascii "GPS: SAT Unusabl"
        41 54 20 55 6E 75
        73 61 62 6C
   16DC 00                 5064 	.db 0x00
   16DD 47 50 53 3A 20 55  5065 	.ascii "GPS: Unknown!!!"
        6E 6B 6E 6F 77 6E
        21 21 21
   16EC 00                 5066 	.db 0x00
   16ED 00                 5067 	.db 0x00
   16EE 47 50 53 3A 20 55  5068 	.ascii "GPS: Unknown!!!"
        6E 6B 6E 6F 77 6E
        21 21 21
   16FD 00                 5069 	.db 0x00
   16FE 00                 5070 	.db 0x00
   16FF 47 50 53 3A 20 55  5071 	.ascii "GPS: Unknown!!!"
        6E 6B 6E 6F 77 6E
        21 21 21
   170E 00                 5072 	.db 0x00
   170F 00                 5073 	.db 0x00
   1710 47 50 53 3A 20 54  5074 	.ascii "GPS: TRIAM Rejec"
        52 49 41 4D 20 52
        65 6A 65 63
   1720 00                 5075 	.db 0x00
                    0251   5076 G$DiscActivity$0$0 == .
   1721                    5077 _DiscActivity:
   1721 41 43 54 3A 20 50  5078 	.ascii "ACT: Phase Lock"
        68 61 73 65 20 4C
        6F 63 6B
   1730 00                 5079 	.db 0x00
   1731 00                 5080 	.db 0x00
   1732 41 43 54 3A 20 4F  5081 	.ascii "ACT: Osc Warmup"
        73 63 20 57 61 72
        6D 75 70
   1741 00                 5082 	.db 0x00
   1742 00                 5083 	.db 0x00
   1743 41 43 54 3A 20 46  5084 	.ascii "ACT: Freq Lock"
        72 65 71 20 4C 6F
        63 6B
   1751 00                 5085 	.db 0x00
   1752 00                 5086 	.db 0x00
   1753 00                 5087 	.db 0x00
   1754 41 43 54 3A 20 50  5088 	.ascii "ACT: Placing PPS"
        6C 61 63 69 6E 67
        20 50 50 53
   1764 00                 5089 	.db 0x00
   1765 41 43 54 3A 20 49  5090 	.ascii "ACT: Init. loop"
        6E 69 74 2E 20 6C
        6F 6F 70
   1774 00                 5091 	.db 0x00
   1775 00                 5092 	.db 0x00
   1776 41 43 54 3A 20 43  5093 	.ascii "ACT: Compensate"
        6F 6D 70 65 6E 73
        61 74 65
   1785 00                 5094 	.db 0x00
   1786 00                 5095 	.db 0x00
   1787 41 43 54 3A 20 49  5096 	.ascii "ACT: Inactive"
        6E 61 63 74 69 76
        65
   1794 00                 5097 	.db 0x00
   1795 00                 5098 	.db 0x00
   1796 00                 5099 	.db 0x00
   1797 0C                 5100 	.db 0x0C
   1798 41 43 54 3A 20 55  5101 	.ascii "ACT: Unknown!!!"
        6E 6B 6E 6F 77 6E
        21 21 21
   17A7 00                 5102 	.db 0x00
   17A8 00                 5103 	.db 0x00
   17A9 41 43 54 3A 20 52  5104 	.ascii "ACT: Recovery LP"
        65 63 6F 76 65 72
        79 20 4C 50
   17B9 00                 5105 	.db 0x00
                    02EA   5106 G$VersionMsg$0$0 == .
   17BA                    5107 _VersionMsg:
   17BA 20 54 53 49 50 4D  5108 	.ascii " TSIPMon v0.3.4     "
        6F 6E 20 76 30 2E
        33 2E 34 20 20 20
        20 20
   17CE 00                 5109 	.db 0x00
                    02FF   5110 G$LCDInitMsg$0$0 == .
   17CF                    5111 _LCDInitMsg:
   17CF 20 77 77 77 2E 6B  5112 	.ascii " www.ko4bb.com      "
        6F 34 62 62 2E 63
        6F 6D 20 20 20 20
        20 20
   17E3 00                 5113 	.db 0x00
                    0314   5114 G$prompt$0$0 == .
   17E4                    5115 _prompt:
   17E4 54 45 4D 50 3A 20  5116 	.ascii "TEMP:  "
        20
   17EB 00                 5117 	.db 0x00
   17EC 00                 5118 	.db 0x00
   17ED 44 41 43 20 56 3A  5119 	.ascii "DAC V: "
        20
   17F4 00                 5120 	.db 0x00
   17F5 00                 5121 	.db 0x00
                    0326   5122 FTSIPMon$_str_0$0$0 == .
   17F6                    5123 __str_0:
   17F6 54 69 6D 65 20 5A  5124 	.ascii "Time Zone : "
        6F 6E 65 20 3A 20
   1802 00                 5125 	.db 0x00
                    0333   5126 FTSIPMon$_str_1$0$0 == .
   1803                    5127 __str_1:
   1803 47 50 53 20 6F 66  5128 	.ascii "GPS offset: Auto"
        66 73 65 74 3A 20
        41 75 74 6F
   1813 00                 5129 	.db 0x00
                    0344   5130 FTSIPMon$_str_2$0$0 == .
   1814                    5131 __str_2:
   1814 57 61 69 74 69 6E  5132 	.ascii "Waiting for GPS"
        67 20 66 6F 72 20
        47 50 53
   1823 00                 5133 	.db 0x00
                    0354   5134 FTSIPMon$_str_3$0$0 == .
   1824                    5135 __str_3:
   1824 20 20 20 4E 6F 20  5136 	.ascii "   No Message   "
        4D 65 73 73 61 67
        65 20 20 20
   1834 00                 5137 	.db 0x00
                           5138 	.area XINIT   (CODE)
