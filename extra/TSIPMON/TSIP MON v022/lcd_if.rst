                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.6.0 #4309 (Jul 28 2006)
                              4 ; This file generated Sun Dec 28 11:32:34 2008
                              5 ;--------------------------------------------------------
                              6 	.module lcd_if
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _SPIF
                             13 	.globl _WCOL
                             14 	.globl _MODF
                             15 	.globl _RXOVRN
                             16 	.globl _NSSMD1
                             17 	.globl _NSSMD0
                             18 	.globl _TXBMT
                             19 	.globl _SPIEN
                             20 	.globl _AD0EN
                             21 	.globl _AD0TM
                             22 	.globl _AD0INT
                             23 	.globl _AD0BUSY
                             24 	.globl _AD0WINT
                             25 	.globl _AD0CM2
                             26 	.globl _AD0CM1
                             27 	.globl _AD0CM0
                             28 	.globl _CF
                             29 	.globl _CR
                             30 	.globl _CCF2
                             31 	.globl _CCF1
                             32 	.globl _CCF0
                             33 	.globl _CY
                             34 	.globl _AC
                             35 	.globl _F0
                             36 	.globl _RS1
                             37 	.globl _RS0
                             38 	.globl _OV
                             39 	.globl _F1
                             40 	.globl _PARITY
                             41 	.globl _TF2H
                             42 	.globl _TF2
                             43 	.globl _TF2L
                             44 	.globl _TF2LEN
                             45 	.globl _TF2CEN
                             46 	.globl _T2SPLIT
                             47 	.globl _TR2
                             48 	.globl _T2XCLK
                             49 	.globl _MASTER
                             50 	.globl _TXMODE
                             51 	.globl _STA
                             52 	.globl _STO
                             53 	.globl _ACKRQ
                             54 	.globl _ARBLOST
                             55 	.globl _ACK
                             56 	.globl _SI
                             57 	.globl _PSPI0
                             58 	.globl _PT2
                             59 	.globl _PS0
                             60 	.globl _PS
                             61 	.globl _PT1
                             62 	.globl _PX1
                             63 	.globl _PT0
                             64 	.globl _PX0
                             65 	.globl _EA
                             66 	.globl _ESPI0
                             67 	.globl _ET2
                             68 	.globl _ES0
                             69 	.globl _ES
                             70 	.globl _ET1
                             71 	.globl _EX1
                             72 	.globl _ET0
                             73 	.globl _EX0
                             74 	.globl _P2_7
                             75 	.globl _P2_6
                             76 	.globl _P2_5
                             77 	.globl _P2_4
                             78 	.globl _P2_3
                             79 	.globl _P2_2
                             80 	.globl _P2_1
                             81 	.globl _P2_0
                             82 	.globl _S0MODE
                             83 	.globl _SM0
                             84 	.globl _MCE0
                             85 	.globl _SM2
                             86 	.globl _REN0
                             87 	.globl _REN
                             88 	.globl _TB80
                             89 	.globl _TB8
                             90 	.globl _RB80
                             91 	.globl _RB8
                             92 	.globl _TI0
                             93 	.globl _TI
                             94 	.globl _RI0
                             95 	.globl _RI
                             96 	.globl _P1_7
                             97 	.globl _P1_6
                             98 	.globl _P1_5
                             99 	.globl _P1_4
                            100 	.globl _P1_3
                            101 	.globl _P1_2
                            102 	.globl _P1_1
                            103 	.globl _P1_0
                            104 	.globl _TF1
                            105 	.globl _TR1
                            106 	.globl _TF0
                            107 	.globl _TR0
                            108 	.globl _IE1
                            109 	.globl _IT1
                            110 	.globl _IE0
                            111 	.globl _IT0
                            112 	.globl _P0_7
                            113 	.globl _P0_6
                            114 	.globl _P0_5
                            115 	.globl _P0_4
                            116 	.globl _P0_3
                            117 	.globl _P0_2
                            118 	.globl _P0_1
                            119 	.globl _P0_0
                            120 	.globl _PCA0CP2
                            121 	.globl _PCA0CP1
                            122 	.globl _PCA0CP0
                            123 	.globl _PCA0
                            124 	.globl _ADC0LT
                            125 	.globl _ADC0GT
                            126 	.globl _ADC0
                            127 	.globl _IDA0
                            128 	.globl _TMR3RL
                            129 	.globl _TMR3
                            130 	.globl _TMR2RL
                            131 	.globl _RCAP2
                            132 	.globl _TMR2
                            133 	.globl _TMR1
                            134 	.globl _TMR0
                            135 	.globl _VDM0CN
                            136 	.globl _PCA0CPH0
                            137 	.globl _PCA0CPL0
                            138 	.globl _PCA0H
                            139 	.globl _PCA0L
                            140 	.globl _SPI0CN
                            141 	.globl _EIP1
                            142 	.globl _P1MDIN
                            143 	.globl _P1MODE
                            144 	.globl _P0MDIN
                            145 	.globl _P0MODE
                            146 	.globl _B
                            147 	.globl _RSTSRC
                            148 	.globl _PCA0CPH2
                            149 	.globl _PCA0CPL2
                            150 	.globl _PCA0CPH1
                            151 	.globl _PCA0CPL1
                            152 	.globl _ADC0CN
                            153 	.globl _EIE1
                            154 	.globl _INT01CF
                            155 	.globl _IT01CF
                            156 	.globl _OSCLCN
                            157 	.globl _XBR1
                            158 	.globl _XBR0
                            159 	.globl _ACC
                            160 	.globl _PCA0CPM2
                            161 	.globl _PCA0CPM1
                            162 	.globl _PCA0CPM0
                            163 	.globl _PCA0MD
                            164 	.globl _PCA0CN
                            165 	.globl _P1SKIP
                            166 	.globl _P0SKIP
                            167 	.globl _REF0CN
                            168 	.globl _PSW
                            169 	.globl _TMR2H
                            170 	.globl _TH2
                            171 	.globl _TMR2L
                            172 	.globl _TL2
                            173 	.globl _TMR2RLH
                            174 	.globl _RCAP2H
                            175 	.globl _TMR2RLL
                            176 	.globl _RCAP2L
                            177 	.globl _TMR2CN
                            178 	.globl _T2CON
                            179 	.globl _ADC0LTH
                            180 	.globl _ADC0LTL
                            181 	.globl _ADC0GTH
                            182 	.globl _ADC0GTL
                            183 	.globl _SMB0DAT
                            184 	.globl _SMB0CF
                            185 	.globl _SMB0CN
                            186 	.globl _ADC0H
                            187 	.globl _ADC0L
                            188 	.globl _ADC0CF
                            189 	.globl _AMX0P
                            190 	.globl _AMX0N
                            191 	.globl _IDA0CN
                            192 	.globl _IP
                            193 	.globl _FLKEY
                            194 	.globl _FLSCL
                            195 	.globl _OSCICL
                            196 	.globl _OSCICN
                            197 	.globl _OSCXCN
                            198 	.globl __XPAGE
                            199 	.globl _EMI0CN
                            200 	.globl _CLKSEL
                            201 	.globl _IE
                            202 	.globl _P2MDOUT
                            203 	.globl _P1MDOUT
                            204 	.globl _P0MDOUT
                            205 	.globl _SPI0DAT
                            206 	.globl _SPI0CKR
                            207 	.globl _SPI0CFG
                            208 	.globl _P2
                            209 	.globl _CPT0MX
                            210 	.globl _CPT0MD
                            211 	.globl _CPT0CN
                            212 	.globl _SBUF0
                            213 	.globl _SBUF
                            214 	.globl _SCON0
                            215 	.globl _SCON
                            216 	.globl _IDA0H
                            217 	.globl _IDA0L
                            218 	.globl _TMR3H
                            219 	.globl _TMR3L
                            220 	.globl _TMR3RLH
                            221 	.globl _TMR3RLL
                            222 	.globl _TMR3CN
                            223 	.globl _P1
                            224 	.globl _PSCTL
                            225 	.globl _CKCON
                            226 	.globl _TH1
                            227 	.globl _TH0
                            228 	.globl _TL1
                            229 	.globl _TL0
                            230 	.globl _TMOD
                            231 	.globl _TCON
                            232 	.globl _PCON
                            233 	.globl _DPH
                            234 	.globl _DPL
                            235 	.globl _SP
                            236 	.globl _P0
                            237 	.globl _printCode2LCD_PARM_3
                            238 	.globl _printCode2LCD_PARM_2
                            239 	.globl _printLCD_PARM_3
                            240 	.globl _printLCD_PARM_2
                            241 	.globl _InitLCD
                            242 	.globl _ClearLCD
                            243 	.globl _printLCD
                            244 	.globl _printCode2LCD
                            245 	.globl _IRWriteLCD
                            246 	.globl _DRWriteLCD
                            247 	.globl _WaitLCD
                            248 	.globl _SetLCDIn
                            249 	.globl _SetLCDOut
                            250 	.globl _ClockEn
                            251 	.globl _SetLCDRs
                            252 	.globl _ClrLCDRs
                            253 	.globl _SetLCDRw
                            254 	.globl _ClrLCDRw
                            255 ;--------------------------------------------------------
                            256 ; special function registers
                            257 ;--------------------------------------------------------
                            258 	.area RSEG    (DATA)
                    0080    259 G$P0$0$0 == 0x0080
                    0080    260 _P0	=	0x0080
                    0081    261 G$SP$0$0 == 0x0081
                    0081    262 _SP	=	0x0081
                    0082    263 G$DPL$0$0 == 0x0082
                    0082    264 _DPL	=	0x0082
                    0083    265 G$DPH$0$0 == 0x0083
                    0083    266 _DPH	=	0x0083
                    0087    267 G$PCON$0$0 == 0x0087
                    0087    268 _PCON	=	0x0087
                    0088    269 G$TCON$0$0 == 0x0088
                    0088    270 _TCON	=	0x0088
                    0089    271 G$TMOD$0$0 == 0x0089
                    0089    272 _TMOD	=	0x0089
                    008A    273 G$TL0$0$0 == 0x008a
                    008A    274 _TL0	=	0x008a
                    008B    275 G$TL1$0$0 == 0x008b
                    008B    276 _TL1	=	0x008b
                    008C    277 G$TH0$0$0 == 0x008c
                    008C    278 _TH0	=	0x008c
                    008D    279 G$TH1$0$0 == 0x008d
                    008D    280 _TH1	=	0x008d
                    008E    281 G$CKCON$0$0 == 0x008e
                    008E    282 _CKCON	=	0x008e
                    008F    283 G$PSCTL$0$0 == 0x008f
                    008F    284 _PSCTL	=	0x008f
                    0090    285 G$P1$0$0 == 0x0090
                    0090    286 _P1	=	0x0090
                    0091    287 G$TMR3CN$0$0 == 0x0091
                    0091    288 _TMR3CN	=	0x0091
                    0092    289 G$TMR3RLL$0$0 == 0x0092
                    0092    290 _TMR3RLL	=	0x0092
                    0093    291 G$TMR3RLH$0$0 == 0x0093
                    0093    292 _TMR3RLH	=	0x0093
                    0094    293 G$TMR3L$0$0 == 0x0094
                    0094    294 _TMR3L	=	0x0094
                    0095    295 G$TMR3H$0$0 == 0x0095
                    0095    296 _TMR3H	=	0x0095
                    0096    297 G$IDA0L$0$0 == 0x0096
                    0096    298 _IDA0L	=	0x0096
                    0097    299 G$IDA0H$0$0 == 0x0097
                    0097    300 _IDA0H	=	0x0097
                    0098    301 G$SCON$0$0 == 0x0098
                    0098    302 _SCON	=	0x0098
                    0098    303 G$SCON0$0$0 == 0x0098
                    0098    304 _SCON0	=	0x0098
                    0099    305 G$SBUF$0$0 == 0x0099
                    0099    306 _SBUF	=	0x0099
                    0099    307 G$SBUF0$0$0 == 0x0099
                    0099    308 _SBUF0	=	0x0099
                    009B    309 G$CPT0CN$0$0 == 0x009b
                    009B    310 _CPT0CN	=	0x009b
                    009D    311 G$CPT0MD$0$0 == 0x009d
                    009D    312 _CPT0MD	=	0x009d
                    009F    313 G$CPT0MX$0$0 == 0x009f
                    009F    314 _CPT0MX	=	0x009f
                    00A0    315 G$P2$0$0 == 0x00a0
                    00A0    316 _P2	=	0x00a0
                    00A1    317 G$SPI0CFG$0$0 == 0x00a1
                    00A1    318 _SPI0CFG	=	0x00a1
                    00A2    319 G$SPI0CKR$0$0 == 0x00a2
                    00A2    320 _SPI0CKR	=	0x00a2
                    00A3    321 G$SPI0DAT$0$0 == 0x00a3
                    00A3    322 _SPI0DAT	=	0x00a3
                    00A4    323 G$P0MDOUT$0$0 == 0x00a4
                    00A4    324 _P0MDOUT	=	0x00a4
                    00A5    325 G$P1MDOUT$0$0 == 0x00a5
                    00A5    326 _P1MDOUT	=	0x00a5
                    00A6    327 G$P2MDOUT$0$0 == 0x00a6
                    00A6    328 _P2MDOUT	=	0x00a6
                    00A8    329 G$IE$0$0 == 0x00a8
                    00A8    330 _IE	=	0x00a8
                    00A9    331 G$CLKSEL$0$0 == 0x00a9
                    00A9    332 _CLKSEL	=	0x00a9
                    00AA    333 G$EMI0CN$0$0 == 0x00aa
                    00AA    334 _EMI0CN	=	0x00aa
                    00AA    335 G$_XPAGE$0$0 == 0x00aa
                    00AA    336 __XPAGE	=	0x00aa
                    00B1    337 G$OSCXCN$0$0 == 0x00b1
                    00B1    338 _OSCXCN	=	0x00b1
                    00B2    339 G$OSCICN$0$0 == 0x00b2
                    00B2    340 _OSCICN	=	0x00b2
                    00B3    341 G$OSCICL$0$0 == 0x00b3
                    00B3    342 _OSCICL	=	0x00b3
                    00B6    343 G$FLSCL$0$0 == 0x00b6
                    00B6    344 _FLSCL	=	0x00b6
                    00B7    345 G$FLKEY$0$0 == 0x00b7
                    00B7    346 _FLKEY	=	0x00b7
                    00B8    347 G$IP$0$0 == 0x00b8
                    00B8    348 _IP	=	0x00b8
                    00B9    349 G$IDA0CN$0$0 == 0x00b9
                    00B9    350 _IDA0CN	=	0x00b9
                    00BA    351 G$AMX0N$0$0 == 0x00ba
                    00BA    352 _AMX0N	=	0x00ba
                    00BB    353 G$AMX0P$0$0 == 0x00bb
                    00BB    354 _AMX0P	=	0x00bb
                    00BC    355 G$ADC0CF$0$0 == 0x00bc
                    00BC    356 _ADC0CF	=	0x00bc
                    00BD    357 G$ADC0L$0$0 == 0x00bd
                    00BD    358 _ADC0L	=	0x00bd
                    00BE    359 G$ADC0H$0$0 == 0x00be
                    00BE    360 _ADC0H	=	0x00be
                    00C0    361 G$SMB0CN$0$0 == 0x00c0
                    00C0    362 _SMB0CN	=	0x00c0
                    00C1    363 G$SMB0CF$0$0 == 0x00c1
                    00C1    364 _SMB0CF	=	0x00c1
                    00C2    365 G$SMB0DAT$0$0 == 0x00c2
                    00C2    366 _SMB0DAT	=	0x00c2
                    00C3    367 G$ADC0GTL$0$0 == 0x00c3
                    00C3    368 _ADC0GTL	=	0x00c3
                    00C4    369 G$ADC0GTH$0$0 == 0x00c4
                    00C4    370 _ADC0GTH	=	0x00c4
                    00C5    371 G$ADC0LTL$0$0 == 0x00c5
                    00C5    372 _ADC0LTL	=	0x00c5
                    00C6    373 G$ADC0LTH$0$0 == 0x00c6
                    00C6    374 _ADC0LTH	=	0x00c6
                    00C8    375 G$T2CON$0$0 == 0x00c8
                    00C8    376 _T2CON	=	0x00c8
                    00C8    377 G$TMR2CN$0$0 == 0x00c8
                    00C8    378 _TMR2CN	=	0x00c8
                    00CA    379 G$RCAP2L$0$0 == 0x00ca
                    00CA    380 _RCAP2L	=	0x00ca
                    00CA    381 G$TMR2RLL$0$0 == 0x00ca
                    00CA    382 _TMR2RLL	=	0x00ca
                    00CB    383 G$RCAP2H$0$0 == 0x00cb
                    00CB    384 _RCAP2H	=	0x00cb
                    00CB    385 G$TMR2RLH$0$0 == 0x00cb
                    00CB    386 _TMR2RLH	=	0x00cb
                    00CC    387 G$TL2$0$0 == 0x00cc
                    00CC    388 _TL2	=	0x00cc
                    00CC    389 G$TMR2L$0$0 == 0x00cc
                    00CC    390 _TMR2L	=	0x00cc
                    00CD    391 G$TH2$0$0 == 0x00cd
                    00CD    392 _TH2	=	0x00cd
                    00CD    393 G$TMR2H$0$0 == 0x00cd
                    00CD    394 _TMR2H	=	0x00cd
                    00D0    395 G$PSW$0$0 == 0x00d0
                    00D0    396 _PSW	=	0x00d0
                    00D1    397 G$REF0CN$0$0 == 0x00d1
                    00D1    398 _REF0CN	=	0x00d1
                    00D4    399 G$P0SKIP$0$0 == 0x00d4
                    00D4    400 _P0SKIP	=	0x00d4
                    00D5    401 G$P1SKIP$0$0 == 0x00d5
                    00D5    402 _P1SKIP	=	0x00d5
                    00D8    403 G$PCA0CN$0$0 == 0x00d8
                    00D8    404 _PCA0CN	=	0x00d8
                    00D9    405 G$PCA0MD$0$0 == 0x00d9
                    00D9    406 _PCA0MD	=	0x00d9
                    00DA    407 G$PCA0CPM0$0$0 == 0x00da
                    00DA    408 _PCA0CPM0	=	0x00da
                    00DB    409 G$PCA0CPM1$0$0 == 0x00db
                    00DB    410 _PCA0CPM1	=	0x00db
                    00DC    411 G$PCA0CPM2$0$0 == 0x00dc
                    00DC    412 _PCA0CPM2	=	0x00dc
                    00E0    413 G$ACC$0$0 == 0x00e0
                    00E0    414 _ACC	=	0x00e0
                    00E1    415 G$XBR0$0$0 == 0x00e1
                    00E1    416 _XBR0	=	0x00e1
                    00E2    417 G$XBR1$0$0 == 0x00e2
                    00E2    418 _XBR1	=	0x00e2
                    00E3    419 G$OSCLCN$0$0 == 0x00e3
                    00E3    420 _OSCLCN	=	0x00e3
                    00E4    421 G$IT01CF$0$0 == 0x00e4
                    00E4    422 _IT01CF	=	0x00e4
                    00E4    423 G$INT01CF$0$0 == 0x00e4
                    00E4    424 _INT01CF	=	0x00e4
                    00E6    425 G$EIE1$0$0 == 0x00e6
                    00E6    426 _EIE1	=	0x00e6
                    00E8    427 G$ADC0CN$0$0 == 0x00e8
                    00E8    428 _ADC0CN	=	0x00e8
                    00E9    429 G$PCA0CPL1$0$0 == 0x00e9
                    00E9    430 _PCA0CPL1	=	0x00e9
                    00EA    431 G$PCA0CPH1$0$0 == 0x00ea
                    00EA    432 _PCA0CPH1	=	0x00ea
                    00EB    433 G$PCA0CPL2$0$0 == 0x00eb
                    00EB    434 _PCA0CPL2	=	0x00eb
                    00EC    435 G$PCA0CPH2$0$0 == 0x00ec
                    00EC    436 _PCA0CPH2	=	0x00ec
                    00EF    437 G$RSTSRC$0$0 == 0x00ef
                    00EF    438 _RSTSRC	=	0x00ef
                    00F0    439 G$B$0$0 == 0x00f0
                    00F0    440 _B	=	0x00f0
                    00F1    441 G$P0MODE$0$0 == 0x00f1
                    00F1    442 _P0MODE	=	0x00f1
                    00F1    443 G$P0MDIN$0$0 == 0x00f1
                    00F1    444 _P0MDIN	=	0x00f1
                    00F2    445 G$P1MODE$0$0 == 0x00f2
                    00F2    446 _P1MODE	=	0x00f2
                    00F2    447 G$P1MDIN$0$0 == 0x00f2
                    00F2    448 _P1MDIN	=	0x00f2
                    00F6    449 G$EIP1$0$0 == 0x00f6
                    00F6    450 _EIP1	=	0x00f6
                    00F8    451 G$SPI0CN$0$0 == 0x00f8
                    00F8    452 _SPI0CN	=	0x00f8
                    00F9    453 G$PCA0L$0$0 == 0x00f9
                    00F9    454 _PCA0L	=	0x00f9
                    00FA    455 G$PCA0H$0$0 == 0x00fa
                    00FA    456 _PCA0H	=	0x00fa
                    00FB    457 G$PCA0CPL0$0$0 == 0x00fb
                    00FB    458 _PCA0CPL0	=	0x00fb
                    00FC    459 G$PCA0CPH0$0$0 == 0x00fc
                    00FC    460 _PCA0CPH0	=	0x00fc
                    00FF    461 G$VDM0CN$0$0 == 0x00ff
                    00FF    462 _VDM0CN	=	0x00ff
                    8C8A    463 G$TMR0$0$0 == 0x8c8a
                    8C8A    464 _TMR0	=	0x8c8a
                    8D8B    465 G$TMR1$0$0 == 0x8d8b
                    8D8B    466 _TMR1	=	0x8d8b
                    CDCC    467 G$TMR2$0$0 == 0xcdcc
                    CDCC    468 _TMR2	=	0xcdcc
                    CBCA    469 G$RCAP2$0$0 == 0xcbca
                    CBCA    470 _RCAP2	=	0xcbca
                    CBCA    471 G$TMR2RL$0$0 == 0xcbca
                    CBCA    472 _TMR2RL	=	0xcbca
                    9594    473 G$TMR3$0$0 == 0x9594
                    9594    474 _TMR3	=	0x9594
                    9392    475 G$TMR3RL$0$0 == 0x9392
                    9392    476 _TMR3RL	=	0x9392
                    9796    477 G$IDA0$0$0 == 0x9796
                    9796    478 _IDA0	=	0x9796
                    BEBD    479 G$ADC0$0$0 == 0xbebd
                    BEBD    480 _ADC0	=	0xbebd
                    C4C3    481 G$ADC0GT$0$0 == 0xc4c3
                    C4C3    482 _ADC0GT	=	0xc4c3
                    C6C5    483 G$ADC0LT$0$0 == 0xc6c5
                    C6C5    484 _ADC0LT	=	0xc6c5
                    FAF9    485 G$PCA0$0$0 == 0xfaf9
                    FAF9    486 _PCA0	=	0xfaf9
                    FCFB    487 G$PCA0CP0$0$0 == 0xfcfb
                    FCFB    488 _PCA0CP0	=	0xfcfb
                    EAE9    489 G$PCA0CP1$0$0 == 0xeae9
                    EAE9    490 _PCA0CP1	=	0xeae9
                    ECEB    491 G$PCA0CP2$0$0 == 0xeceb
                    ECEB    492 _PCA0CP2	=	0xeceb
                            493 ;--------------------------------------------------------
                            494 ; special function bits
                            495 ;--------------------------------------------------------
                            496 	.area RSEG    (DATA)
                    0080    497 G$P0_0$0$0 == 0x0080
                    0080    498 _P0_0	=	0x0080
                    0081    499 G$P0_1$0$0 == 0x0081
                    0081    500 _P0_1	=	0x0081
                    0082    501 G$P0_2$0$0 == 0x0082
                    0082    502 _P0_2	=	0x0082
                    0083    503 G$P0_3$0$0 == 0x0083
                    0083    504 _P0_3	=	0x0083
                    0084    505 G$P0_4$0$0 == 0x0084
                    0084    506 _P0_4	=	0x0084
                    0085    507 G$P0_5$0$0 == 0x0085
                    0085    508 _P0_5	=	0x0085
                    0086    509 G$P0_6$0$0 == 0x0086
                    0086    510 _P0_6	=	0x0086
                    0087    511 G$P0_7$0$0 == 0x0087
                    0087    512 _P0_7	=	0x0087
                    0088    513 G$IT0$0$0 == 0x0088
                    0088    514 _IT0	=	0x0088
                    0089    515 G$IE0$0$0 == 0x0089
                    0089    516 _IE0	=	0x0089
                    008A    517 G$IT1$0$0 == 0x008a
                    008A    518 _IT1	=	0x008a
                    008B    519 G$IE1$0$0 == 0x008b
                    008B    520 _IE1	=	0x008b
                    008C    521 G$TR0$0$0 == 0x008c
                    008C    522 _TR0	=	0x008c
                    008D    523 G$TF0$0$0 == 0x008d
                    008D    524 _TF0	=	0x008d
                    008E    525 G$TR1$0$0 == 0x008e
                    008E    526 _TR1	=	0x008e
                    008F    527 G$TF1$0$0 == 0x008f
                    008F    528 _TF1	=	0x008f
                    0090    529 G$P1_0$0$0 == 0x0090
                    0090    530 _P1_0	=	0x0090
                    0091    531 G$P1_1$0$0 == 0x0091
                    0091    532 _P1_1	=	0x0091
                    0092    533 G$P1_2$0$0 == 0x0092
                    0092    534 _P1_2	=	0x0092
                    0093    535 G$P1_3$0$0 == 0x0093
                    0093    536 _P1_3	=	0x0093
                    0094    537 G$P1_4$0$0 == 0x0094
                    0094    538 _P1_4	=	0x0094
                    0095    539 G$P1_5$0$0 == 0x0095
                    0095    540 _P1_5	=	0x0095
                    0096    541 G$P1_6$0$0 == 0x0096
                    0096    542 _P1_6	=	0x0096
                    0097    543 G$P1_7$0$0 == 0x0097
                    0097    544 _P1_7	=	0x0097
                    0098    545 G$RI$0$0 == 0x0098
                    0098    546 _RI	=	0x0098
                    0098    547 G$RI0$0$0 == 0x0098
                    0098    548 _RI0	=	0x0098
                    0099    549 G$TI$0$0 == 0x0099
                    0099    550 _TI	=	0x0099
                    0099    551 G$TI0$0$0 == 0x0099
                    0099    552 _TI0	=	0x0099
                    009A    553 G$RB8$0$0 == 0x009a
                    009A    554 _RB8	=	0x009a
                    009A    555 G$RB80$0$0 == 0x009a
                    009A    556 _RB80	=	0x009a
                    009B    557 G$TB8$0$0 == 0x009b
                    009B    558 _TB8	=	0x009b
                    009B    559 G$TB80$0$0 == 0x009b
                    009B    560 _TB80	=	0x009b
                    009C    561 G$REN$0$0 == 0x009c
                    009C    562 _REN	=	0x009c
                    009C    563 G$REN0$0$0 == 0x009c
                    009C    564 _REN0	=	0x009c
                    009D    565 G$SM2$0$0 == 0x009d
                    009D    566 _SM2	=	0x009d
                    009D    567 G$MCE0$0$0 == 0x009d
                    009D    568 _MCE0	=	0x009d
                    009F    569 G$SM0$0$0 == 0x009f
                    009F    570 _SM0	=	0x009f
                    009F    571 G$S0MODE$0$0 == 0x009f
                    009F    572 _S0MODE	=	0x009f
                    00A0    573 G$P2_0$0$0 == 0x00a0
                    00A0    574 _P2_0	=	0x00a0
                    00A1    575 G$P2_1$0$0 == 0x00a1
                    00A1    576 _P2_1	=	0x00a1
                    00A2    577 G$P2_2$0$0 == 0x00a2
                    00A2    578 _P2_2	=	0x00a2
                    00A3    579 G$P2_3$0$0 == 0x00a3
                    00A3    580 _P2_3	=	0x00a3
                    00A4    581 G$P2_4$0$0 == 0x00a4
                    00A4    582 _P2_4	=	0x00a4
                    00A5    583 G$P2_5$0$0 == 0x00a5
                    00A5    584 _P2_5	=	0x00a5
                    00A6    585 G$P2_6$0$0 == 0x00a6
                    00A6    586 _P2_6	=	0x00a6
                    00A7    587 G$P2_7$0$0 == 0x00a7
                    00A7    588 _P2_7	=	0x00a7
                    00A8    589 G$EX0$0$0 == 0x00a8
                    00A8    590 _EX0	=	0x00a8
                    00A9    591 G$ET0$0$0 == 0x00a9
                    00A9    592 _ET0	=	0x00a9
                    00AA    593 G$EX1$0$0 == 0x00aa
                    00AA    594 _EX1	=	0x00aa
                    00AB    595 G$ET1$0$0 == 0x00ab
                    00AB    596 _ET1	=	0x00ab
                    00AC    597 G$ES$0$0 == 0x00ac
                    00AC    598 _ES	=	0x00ac
                    00AC    599 G$ES0$0$0 == 0x00ac
                    00AC    600 _ES0	=	0x00ac
                    00AD    601 G$ET2$0$0 == 0x00ad
                    00AD    602 _ET2	=	0x00ad
                    00AE    603 G$ESPI0$0$0 == 0x00ae
                    00AE    604 _ESPI0	=	0x00ae
                    00AF    605 G$EA$0$0 == 0x00af
                    00AF    606 _EA	=	0x00af
                    00B8    607 G$PX0$0$0 == 0x00b8
                    00B8    608 _PX0	=	0x00b8
                    00B9    609 G$PT0$0$0 == 0x00b9
                    00B9    610 _PT0	=	0x00b9
                    00BA    611 G$PX1$0$0 == 0x00ba
                    00BA    612 _PX1	=	0x00ba
                    00BB    613 G$PT1$0$0 == 0x00bb
                    00BB    614 _PT1	=	0x00bb
                    00BC    615 G$PS$0$0 == 0x00bc
                    00BC    616 _PS	=	0x00bc
                    00BC    617 G$PS0$0$0 == 0x00bc
                    00BC    618 _PS0	=	0x00bc
                    00BD    619 G$PT2$0$0 == 0x00bd
                    00BD    620 _PT2	=	0x00bd
                    00BE    621 G$PSPI0$0$0 == 0x00be
                    00BE    622 _PSPI0	=	0x00be
                    00C0    623 G$SI$0$0 == 0x00c0
                    00C0    624 _SI	=	0x00c0
                    00C1    625 G$ACK$0$0 == 0x00c1
                    00C1    626 _ACK	=	0x00c1
                    00C2    627 G$ARBLOST$0$0 == 0x00c2
                    00C2    628 _ARBLOST	=	0x00c2
                    00C3    629 G$ACKRQ$0$0 == 0x00c3
                    00C3    630 _ACKRQ	=	0x00c3
                    00C4    631 G$STO$0$0 == 0x00c4
                    00C4    632 _STO	=	0x00c4
                    00C5    633 G$STA$0$0 == 0x00c5
                    00C5    634 _STA	=	0x00c5
                    00C6    635 G$TXMODE$0$0 == 0x00c6
                    00C6    636 _TXMODE	=	0x00c6
                    00C7    637 G$MASTER$0$0 == 0x00c7
                    00C7    638 _MASTER	=	0x00c7
                    00C8    639 G$T2XCLK$0$0 == 0x00c8
                    00C8    640 _T2XCLK	=	0x00c8
                    00CA    641 G$TR2$0$0 == 0x00ca
                    00CA    642 _TR2	=	0x00ca
                    00CB    643 G$T2SPLIT$0$0 == 0x00cb
                    00CB    644 _T2SPLIT	=	0x00cb
                    00CD    645 G$TF2CEN$0$0 == 0x00cd
                    00CD    646 _TF2CEN	=	0x00cd
                    00CD    647 G$TF2LEN$0$0 == 0x00cd
                    00CD    648 _TF2LEN	=	0x00cd
                    00CE    649 G$TF2L$0$0 == 0x00ce
                    00CE    650 _TF2L	=	0x00ce
                    00CF    651 G$TF2$0$0 == 0x00cf
                    00CF    652 _TF2	=	0x00cf
                    00CF    653 G$TF2H$0$0 == 0x00cf
                    00CF    654 _TF2H	=	0x00cf
                    00D0    655 G$PARITY$0$0 == 0x00d0
                    00D0    656 _PARITY	=	0x00d0
                    00D1    657 G$F1$0$0 == 0x00d1
                    00D1    658 _F1	=	0x00d1
                    00D2    659 G$OV$0$0 == 0x00d2
                    00D2    660 _OV	=	0x00d2
                    00D3    661 G$RS0$0$0 == 0x00d3
                    00D3    662 _RS0	=	0x00d3
                    00D4    663 G$RS1$0$0 == 0x00d4
                    00D4    664 _RS1	=	0x00d4
                    00D5    665 G$F0$0$0 == 0x00d5
                    00D5    666 _F0	=	0x00d5
                    00D6    667 G$AC$0$0 == 0x00d6
                    00D6    668 _AC	=	0x00d6
                    00D7    669 G$CY$0$0 == 0x00d7
                    00D7    670 _CY	=	0x00d7
                    00D8    671 G$CCF0$0$0 == 0x00d8
                    00D8    672 _CCF0	=	0x00d8
                    00D9    673 G$CCF1$0$0 == 0x00d9
                    00D9    674 _CCF1	=	0x00d9
                    00DA    675 G$CCF2$0$0 == 0x00da
                    00DA    676 _CCF2	=	0x00da
                    00DE    677 G$CR$0$0 == 0x00de
                    00DE    678 _CR	=	0x00de
                    00DF    679 G$CF$0$0 == 0x00df
                    00DF    680 _CF	=	0x00df
                    00E8    681 G$AD0CM0$0$0 == 0x00e8
                    00E8    682 _AD0CM0	=	0x00e8
                    00E9    683 G$AD0CM1$0$0 == 0x00e9
                    00E9    684 _AD0CM1	=	0x00e9
                    00EA    685 G$AD0CM2$0$0 == 0x00ea
                    00EA    686 _AD0CM2	=	0x00ea
                    00EB    687 G$AD0WINT$0$0 == 0x00eb
                    00EB    688 _AD0WINT	=	0x00eb
                    00EC    689 G$AD0BUSY$0$0 == 0x00ec
                    00EC    690 _AD0BUSY	=	0x00ec
                    00ED    691 G$AD0INT$0$0 == 0x00ed
                    00ED    692 _AD0INT	=	0x00ed
                    00EE    693 G$AD0TM$0$0 == 0x00ee
                    00EE    694 _AD0TM	=	0x00ee
                    00EF    695 G$AD0EN$0$0 == 0x00ef
                    00EF    696 _AD0EN	=	0x00ef
                    00F8    697 G$SPIEN$0$0 == 0x00f8
                    00F8    698 _SPIEN	=	0x00f8
                    00F9    699 G$TXBMT$0$0 == 0x00f9
                    00F9    700 _TXBMT	=	0x00f9
                    00FA    701 G$NSSMD0$0$0 == 0x00fa
                    00FA    702 _NSSMD0	=	0x00fa
                    00FB    703 G$NSSMD1$0$0 == 0x00fb
                    00FB    704 _NSSMD1	=	0x00fb
                    00FC    705 G$RXOVRN$0$0 == 0x00fc
                    00FC    706 _RXOVRN	=	0x00fc
                    00FD    707 G$MODF$0$0 == 0x00fd
                    00FD    708 _MODF	=	0x00fd
                    00FE    709 G$WCOL$0$0 == 0x00fe
                    00FE    710 _WCOL	=	0x00fe
                    00FF    711 G$SPIF$0$0 == 0x00ff
                    00FF    712 _SPIF	=	0x00ff
                            713 ;--------------------------------------------------------
                            714 ; overlayable register banks
                            715 ;--------------------------------------------------------
                            716 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     717 	.ds 8
                            718 ;--------------------------------------------------------
                            719 ; internal ram data
                            720 ;--------------------------------------------------------
                            721 	.area DSEG    (DATA)
                    0000    722 LprintLCD$chr_ptr$1$1==.
   0008                     723 _printLCD_PARM_2:
   0008                     724 	.ds 2
                    0002    725 LprintLCD$offset$1$1==.
   000A                     726 _printLCD_PARM_3:
   000A                     727 	.ds 1
                    0003    728 LprintCode2LCD$chr_ptr$1$1==.
   000B                     729 _printCode2LCD_PARM_2:
   000B                     730 	.ds 2
                    0005    731 LprintCode2LCD$offset$1$1==.
   000D                     732 _printCode2LCD_PARM_3:
   000D                     733 	.ds 1
                            734 ;--------------------------------------------------------
                            735 ; overlayable items in internal ram 
                            736 ;--------------------------------------------------------
                            737 	.area	OSEG    (OVR,DATA)
                            738 ;--------------------------------------------------------
                            739 ; indirectly addressable internal ram data
                            740 ;--------------------------------------------------------
                            741 	.area ISEG    (DATA)
                            742 ;--------------------------------------------------------
                            743 ; bit data
                            744 ;--------------------------------------------------------
                            745 	.area BSEG    (BIT)
                    0000    746 LWaitLCD$bi$1$1==.
   000A                     747 _WaitLCD_bi_1_1:
   000A                     748 	.ds 1
                            749 ;--------------------------------------------------------
                            750 ; paged external ram data
                            751 ;--------------------------------------------------------
                            752 	.area PSEG    (PAG,XDATA)
                            753 ;--------------------------------------------------------
                            754 ; external ram data
                            755 ;--------------------------------------------------------
                            756 	.area XSEG    (XDATA)
                            757 ;--------------------------------------------------------
                            758 ; external initialized ram data
                            759 ;--------------------------------------------------------
                            760 	.area XISEG   (XDATA)
                            761 	.area HOME    (CODE)
                            762 	.area GSINIT0 (CODE)
                            763 	.area GSINIT1 (CODE)
                            764 	.area GSINIT2 (CODE)
                            765 	.area GSINIT3 (CODE)
                            766 	.area GSINIT4 (CODE)
                            767 	.area GSINIT5 (CODE)
                            768 	.area GSINIT  (CODE)
                            769 	.area GSFINAL (CODE)
                            770 	.area CSEG    (CODE)
                            771 ;--------------------------------------------------------
                            772 ; global & static initialisations
                            773 ;--------------------------------------------------------
                            774 	.area HOME    (CODE)
                            775 	.area GSINIT  (CODE)
                            776 	.area GSFINAL (CODE)
                            777 	.area GSINIT  (CODE)
                            778 ;--------------------------------------------------------
                            779 ; Home
                            780 ;--------------------------------------------------------
                            781 	.area HOME    (CODE)
                            782 	.area CSEG    (CODE)
                            783 ;--------------------------------------------------------
                            784 ; code
                            785 ;--------------------------------------------------------
                            786 	.area CSEG    (CODE)
                            787 ;------------------------------------------------------------
                            788 ;Allocation info for local variables in function 'InitLCD'
                            789 ;------------------------------------------------------------
                            790 ;------------------------------------------------------------
                    0000    791 	G$InitLCD$0$0 ==.
                    0000    792 	C$lcd_if.c$164$0$0 ==.
                            793 ;	C:/SDCC/GPSMon/dev/lcd_if.c:164: void InitLCD( void ){
                            794 ;	-----------------------------------------
                            795 ;	 function InitLCD
                            796 ;	-----------------------------------------
   0AA3                     797 _InitLCD:
                    0002    798 	ar2 = 0x02
                    0003    799 	ar3 = 0x03
                    0004    800 	ar4 = 0x04
                    0005    801 	ar5 = 0x05
                    0006    802 	ar6 = 0x06
                    0007    803 	ar7 = 0x07
                    0000    804 	ar0 = 0x00
                    0001    805 	ar1 = 0x01
                    0000    806 	C$lcd_if.c$173$1$1 ==.
                            807 ;	C:/SDCC/GPSMon/dev/lcd_if.c:173: WaitTicks( 15 );        // Wait more than 15ms
                            808 ;	genCall
                            809 ;	Peephole 182.b	used 16 bit load of dptr
   0AA3 90 00 0F            810 	mov	dptr,#0x000F
   0AA6 12 02 A9            811 	lcall	_WaitTicks
                    0006    812 	C$lcd_if.c$174$1$1 ==.
                            813 ;	C:/SDCC/GPSMon/dev/lcd_if.c:174: LCD_PORT = LCD_INIT_1;  // Startup Sequence
                            814 ;	genAssign
   0AA9 75 90 30            815 	mov	_P1,#0x30
                    0009    816 	C$lcd_if.c$175$1$1 ==.
                            817 ;	C:/SDCC/GPSMon/dev/lcd_if.c:175: ClockEn();				// raise E, wait >100uS, lower E
                            818 ;	genCall
   0AAC 12 0C 92            819 	lcall	_ClockEn
                    000C    820 	C$lcd_if.c$176$1$1 ==.
                            821 ;	C:/SDCC/GPSMon/dev/lcd_if.c:176: WaitTicks( 5 );         // Wait more than 4.1ms
                            822 ;	genCall
                            823 ;	Peephole 182.b	used 16 bit load of dptr
   0AAF 90 00 05            824 	mov	dptr,#0x0005
   0AB2 12 02 A9            825 	lcall	_WaitTicks
                    0012    826 	C$lcd_if.c$177$1$1 ==.
                            827 ;	C:/SDCC/GPSMon/dev/lcd_if.c:177: ClockEn();  
                            828 ;	genCall
   0AB5 12 0C 92            829 	lcall	_ClockEn
                    0015    830 	C$lcd_if.c$178$1$1 ==.
                            831 ;	C:/SDCC/GPSMon/dev/lcd_if.c:178: WaitTicks( 1 );         // Wait more than 0.1ms
                            832 ;	genCall
                            833 ;	Peephole 182.b	used 16 bit load of dptr
   0AB8 90 00 01            834 	mov	dptr,#0x0001
   0ABB 12 02 A9            835 	lcall	_WaitTicks
                    001B    836 	C$lcd_if.c$179$1$1 ==.
                            837 ;	C:/SDCC/GPSMon/dev/lcd_if.c:179: ClockEn();    
                            838 ;	genCall
   0ABE 12 0C 92            839 	lcall	_ClockEn
                    001E    840 	C$lcd_if.c$180$1$1 ==.
                            841 ;	C:/SDCC/GPSMon/dev/lcd_if.c:180: LCD_PORT = LCD_INIT_2;
                            842 ;	genAssign
   0AC1 75 90 20            843 	mov	_P1,#0x20
                    0021    844 	C$lcd_if.c$181$1$1 ==.
                            845 ;	C:/SDCC/GPSMon/dev/lcd_if.c:181: ClockEn();
                            846 ;	genCall
   0AC4 12 0C 92            847 	lcall	_ClockEn
                    0024    848 	C$lcd_if.c$182$1$1 ==.
                            849 ;	C:/SDCC/GPSMon/dev/lcd_if.c:182: WaitTicks( 1 );         // Wait more than 0.1ms
                            850 ;	genCall
                            851 ;	Peephole 182.b	used 16 bit load of dptr
   0AC7 90 00 01            852 	mov	dptr,#0x0001
   0ACA 12 02 A9            853 	lcall	_WaitTicks
                    002A    854 	C$lcd_if.c$186$1$1 ==.
                            855 ;	C:/SDCC/GPSMon/dev/lcd_if.c:186: IRWriteLCD( 0x28 );   	// Function Set
                            856 ;	genCall
   0ACD 75 82 28            857 	mov	dpl,#0x28
   0AD0 12 0B FC            858 	lcall	_IRWriteLCD
                    0030    859 	C$lcd_if.c$188$1$1 ==.
                            860 ;	C:/SDCC/GPSMon/dev/lcd_if.c:188: IRWriteLCD( 0x0C );   	// Display on/off control
                            861 ;	genCall
   0AD3 75 82 0C            862 	mov	dpl,#0x0C
   0AD6 12 0B FC            863 	lcall	_IRWriteLCD
                    0036    864 	C$lcd_if.c$190$1$1 ==.
                            865 ;	C:/SDCC/GPSMon/dev/lcd_if.c:190: IRWriteLCD( 0x06 );   	// Entry Mode Set
                            866 ;	genCall
   0AD9 75 82 06            867 	mov	dpl,#0x06
   0ADC 12 0B FC            868 	lcall	_IRWriteLCD
                    003C    869 	C$lcd_if.c$192$1$1 ==.
                            870 ;	C:/SDCC/GPSMon/dev/lcd_if.c:192: IRWriteLCD( 0x01 );   	// Clear Display
                            871 ;	genCall
   0ADF 75 82 01            872 	mov	dpl,#0x01
   0AE2 12 0B FC            873 	lcall	_IRWriteLCD
                    0042    874 	C$lcd_if.c$193$1$1 ==.
                            875 ;	C:/SDCC/GPSMon/dev/lcd_if.c:193: WaitTicks( 2 );         // Wait more than 1.64ms
                            876 ;	genCall
                            877 ;	Peephole 182.b	used 16 bit load of dptr
   0AE5 90 00 02            878 	mov	dptr,#0x0002
                    0045    879 	C$lcd_if.c$195$1$1 ==.
                    0045    880 	XG$InitLCD$0$0 ==.
                            881 ;	Peephole 253.b	replaced lcall/ret with ljmp
   0AE8 02 02 A9            882 	ljmp	_WaitTicks
                            883 ;
                            884 ;------------------------------------------------------------
                            885 ;Allocation info for local variables in function 'ClearLCD'
                            886 ;------------------------------------------------------------
                            887 ;line                      Allocated to registers r2 
                            888 ;i                         Allocated to registers r3 
                            889 ;------------------------------------------------------------
                    0048    890 	G$ClearLCD$0$0 ==.
                    0048    891 	C$lcd_if.c$204$1$1 ==.
                            892 ;	C:/SDCC/GPSMon/dev/lcd_if.c:204: void ClearLCD( uchar line ){
                            893 ;	-----------------------------------------
                            894 ;	 function ClearLCD
                            895 ;	-----------------------------------------
   0AEB                     896 _ClearLCD:
                            897 ;	genReceive
   0AEB AA 82               898 	mov	r2,dpl
                    004A    899 	C$lcd_if.c$208$1$1 ==.
                            900 ;	C:/SDCC/GPSMon/dev/lcd_if.c:208: if( line == 3 ){
                            901 ;	genCmpEq
                            902 ;	gencjneshort
                            903 ;	Peephole 112.b	changed ljmp to sjmp
                            904 ;	Peephole 198.b	optimized misc jump sequence
   0AED BA 03 0C            905 	cjne	r2,#0x03,00112$
                            906 ;	Peephole 200.b	removed redundant sjmp
                            907 ;	Peephole 300	removed redundant label 00125$
                            908 ;	Peephole 300	removed redundant label 00126$
                    004D    909 	C$lcd_if.c$210$2$2 ==.
                            910 ;	C:/SDCC/GPSMon/dev/lcd_if.c:210: IRWriteLCD( 0x01 );
                            911 ;	genCall
   0AF0 75 82 01            912 	mov	dpl,#0x01
   0AF3 12 0B FC            913 	lcall	_IRWriteLCD
                    0053    914 	C$lcd_if.c$212$2$2 ==.
                            915 ;	C:/SDCC/GPSMon/dev/lcd_if.c:212: WaitTicks( 10 );
                            916 ;	genCall
                            917 ;	Peephole 182.b	used 16 bit load of dptr
   0AF6 90 00 0A            918 	mov	dptr,#0x000A
                            919 ;	Peephole 112.b	changed ljmp to sjmp
                            920 ;	Peephole 251.b	replaced sjmp to ret with ret
                            921 ;	Peephole 253.a	replaced lcall/ret with ljmp
   0AF9 02 02 A9            922 	ljmp	_WaitTicks
   0AFC                     923 00112$:
                    0059    924 	C$lcd_if.c$215$2$3 ==.
                            925 ;	C:/SDCC/GPSMon/dev/lcd_if.c:215: if( line & 1 ){
                            926 ;	genAnd
   0AFC EA                  927 	mov	a,r2
                            928 ;	genIfxJump
                            929 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0AFD 30 E0 2F            930 	jnb	acc.0,00105$
                            931 ;	Peephole 300	removed redundant label 00127$
                    005D    932 	C$lcd_if.c$217$3$4 ==.
                            933 ;	C:/SDCC/GPSMon/dev/lcd_if.c:217: IRWriteLCD( 0x80 );
                            934 ;	genCall
   0B00 75 82 80            935 	mov	dpl,#0x80
   0B03 C0 02               936 	push	ar2
   0B05 12 0B FC            937 	lcall	_IRWriteLCD
   0B08 D0 02               938 	pop	ar2
                    0067    939 	C$lcd_if.c$218$1$1 ==.
                            940 ;	C:/SDCC/GPSMon/dev/lcd_if.c:218: while( i < LCD_SIZE ){
                            941 ;	genAssign
   0B0A 7B 00               942 	mov	r3,#0x00
   0B0C                     943 00101$:
                            944 ;	genCmpLt
                            945 ;	genCmp
   0B0C BB 10 00            946 	cjne	r3,#0x10,00128$
   0B0F                     947 00128$:
                            948 ;	genIfxJump
                            949 ;	Peephole 108.a	removed ljmp by inverse jump logic
   0B0F 50 1E               950 	jnc	00105$
                            951 ;	Peephole 300	removed redundant label 00129$
                    006E    952 	C$lcd_if.c$219$4$5 ==.
                            953 ;	C:/SDCC/GPSMon/dev/lcd_if.c:219: WaitLCD();
                            954 ;	genCall
   0B11 C0 02               955 	push	ar2
   0B13 C0 03               956 	push	ar3
   0B15 12 0C 68            957 	lcall	_WaitLCD
   0B18 D0 03               958 	pop	ar3
   0B1A D0 02               959 	pop	ar2
   0B1C E4                  960 	clr	a
   0B1D 33                  961 	rlc	a
                    007B    962 	C$lcd_if.c$220$4$5 ==.
                            963 ;	C:/SDCC/GPSMon/dev/lcd_if.c:220: DRWriteLCD( ' ' );
                            964 ;	genCall
   0B1E 75 82 20            965 	mov	dpl,#0x20
   0B21 C0 02               966 	push	ar2
   0B23 C0 03               967 	push	ar3
   0B25 12 0C 32            968 	lcall	_DRWriteLCD
   0B28 D0 03               969 	pop	ar3
   0B2A D0 02               970 	pop	ar2
                    0089    971 	C$lcd_if.c$221$4$5 ==.
                            972 ;	C:/SDCC/GPSMon/dev/lcd_if.c:221: i++;
                            973 ;	genPlus
                            974 ;     genPlusIncr
   0B2C 0B                  975 	inc	r3
                            976 ;	Peephole 112.b	changed ljmp to sjmp
   0B2D 80 DD               977 	sjmp	00101$
   0B2F                     978 00105$:
                    008C    979 	C$lcd_if.c$224$2$3 ==.
                            980 ;	C:/SDCC/GPSMon/dev/lcd_if.c:224: if( line & 2 ){
                            981 ;	genAnd
   0B2F EA                  982 	mov	a,r2
                            983 ;	genIfxJump
                            984 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0B30 30 E1 23            985 	jnb	acc.1,00114$
                            986 ;	Peephole 300	removed redundant label 00130$
                    0090    987 	C$lcd_if.c$226$3$6 ==.
                            988 ;	C:/SDCC/GPSMon/dev/lcd_if.c:226: IRWriteLCD( 0xC0 );
                            989 ;	genCall
   0B33 75 82 C0            990 	mov	dpl,#0xC0
   0B36 12 0B FC            991 	lcall	_IRWriteLCD
                    0096    992 	C$lcd_if.c$228$1$1 ==.
                            993 ;	C:/SDCC/GPSMon/dev/lcd_if.c:228: while( i < LCD_SIZE ){
                            994 ;	genAssign
   0B39 7A 00               995 	mov	r2,#0x00
   0B3B                     996 00106$:
                            997 ;	genCmpLt
                            998 ;	genCmp
   0B3B BA 10 00            999 	cjne	r2,#0x10,00131$
   0B3E                    1000 00131$:
                           1001 ;	genIfxJump
                           1002 ;	Peephole 108.a	removed ljmp by inverse jump logic
   0B3E 50 16              1003 	jnc	00114$
                           1004 ;	Peephole 300	removed redundant label 00132$
                    009D   1005 	C$lcd_if.c$229$4$7 ==.
                           1006 ;	C:/SDCC/GPSMon/dev/lcd_if.c:229: WaitLCD();
                           1007 ;	genCall
   0B40 C0 02              1008 	push	ar2
   0B42 12 0C 68           1009 	lcall	_WaitLCD
   0B45 D0 02              1010 	pop	ar2
   0B47 E4                 1011 	clr	a
   0B48 33                 1012 	rlc	a
                    00A6   1013 	C$lcd_if.c$230$4$7 ==.
                           1014 ;	C:/SDCC/GPSMon/dev/lcd_if.c:230: DRWriteLCD( ' ' );
                           1015 ;	genCall
   0B49 75 82 20           1016 	mov	dpl,#0x20
   0B4C C0 02              1017 	push	ar2
   0B4E 12 0C 32           1018 	lcall	_DRWriteLCD
   0B51 D0 02              1019 	pop	ar2
                    00B0   1020 	C$lcd_if.c$231$4$7 ==.
                           1021 ;	C:/SDCC/GPSMon/dev/lcd_if.c:231: i++;
                           1022 ;	genPlus
                           1023 ;     genPlusIncr
   0B53 0A                 1024 	inc	r2
                           1025 ;	Peephole 112.b	changed ljmp to sjmp
   0B54 80 E5              1026 	sjmp	00106$
   0B56                    1027 00114$:
                    00B3   1028 	C$lcd_if.c$235$1$1 ==.
                    00B3   1029 	XG$ClearLCD$0$0 ==.
   0B56 22                 1030 	ret
                           1031 ;------------------------------------------------------------
                           1032 ;Allocation info for local variables in function 'printLCD'
                           1033 ;------------------------------------------------------------
                           1034 ;chr_ptr                   Allocated with name '_printLCD_PARM_2'
                           1035 ;offset                    Allocated with name '_printLCD_PARM_3'
                           1036 ;line                      Allocated to registers r2 
                           1037 ;------------------------------------------------------------
                    00B4   1038 	G$printLCD$0$0 ==.
                    00B4   1039 	C$lcd_if.c$246$1$1 ==.
                           1040 ;	C:/SDCC/GPSMon/dev/lcd_if.c:246: void printLCD( uchar line, uchar LCD_STORAGE_CLASS *chr_ptr, uchar offset ){
                           1041 ;	-----------------------------------------
                           1042 ;	 function printLCD
                           1043 ;	-----------------------------------------
   0B57                    1044 _printLCD:
                           1045 ;	genReceive
   0B57 AA 82              1046 	mov	r2,dpl
                    00B6   1047 	C$lcd_if.c$249$1$1 ==.
                           1048 ;	C:/SDCC/GPSMon/dev/lcd_if.c:249: if( line == 1 )
                           1049 ;	genCmpEq
                           1050 ;	gencjneshort
                           1051 ;	Peephole 112.b	changed ljmp to sjmp
                           1052 ;	Peephole 198.b	optimized misc jump sequence
   0B59 BA 01 0B           1053 	cjne	r2,#0x01,00102$
                           1054 ;	Peephole 200.b	removed redundant sjmp
                           1055 ;	Peephole 300	removed redundant label 00113$
                           1056 ;	Peephole 300	removed redundant label 00114$
                    00B9   1057 	C$lcd_if.c$250$1$1 ==.
                           1058 ;	C:/SDCC/GPSMon/dev/lcd_if.c:250: IRWriteLCD( 0x80 + offset );	// address of left-most character to print
                           1059 ;	genPlus
                           1060 ;     genPlusIncr
   0B5C 74 80              1061 	mov	a,#0x80
   0B5E 25 0A              1062 	add	a,_printLCD_PARM_3
   0B60 F5 82              1063 	mov	dpl,a
                           1064 ;	genCall
   0B62 12 0B FC           1065 	lcall	_IRWriteLCD
                           1066 ;	Peephole 112.b	changed ljmp to sjmp
   0B65 80 09              1067 	sjmp	00103$
   0B67                    1068 00102$:
                    00C4   1069 	C$lcd_if.c$252$1$1 ==.
                           1070 ;	C:/SDCC/GPSMon/dev/lcd_if.c:252: IRWriteLCD( 0xC0 + offset );
                           1071 ;	genPlus
                           1072 ;     genPlusIncr
   0B67 74 C0              1073 	mov	a,#0xC0
   0B69 25 0A              1074 	add	a,_printLCD_PARM_3
   0B6B F5 82              1075 	mov	dpl,a
                           1076 ;	genCall
   0B6D 12 0B FC           1077 	lcall	_IRWriteLCD
   0B70                    1078 00103$:
                    00CD   1079 	C$lcd_if.c$255$1$1 ==.
                           1080 ;	C:/SDCC/GPSMon/dev/lcd_if.c:255: chr_ptr--;
                           1081 ;	genMinus
                           1082 ;	genMinusDec
   0B70 15 08              1083 	dec	_printLCD_PARM_2
   0B72 74 FF              1084 	mov	a,#0xff
   0B74 B5 08 02           1085 	cjne	a,_printLCD_PARM_2,00115$
   0B77 15 09              1086 	dec	(_printLCD_PARM_2 + 1)
   0B79                    1087 00115$:
                    00D6   1088 	C$lcd_if.c$256$1$1 ==.
                           1089 ;	C:/SDCC/GPSMon/dev/lcd_if.c:256: while( *(++chr_ptr) != '\0' ){
                           1090 ;	genAssign
   0B79 AA 08              1091 	mov	r2,_printLCD_PARM_2
   0B7B AB 09              1092 	mov	r3,(_printLCD_PARM_2 + 1)
   0B7D                    1093 00104$:
                           1094 ;	genPlus
                           1095 ;     genPlusIncr
   0B7D 0A                 1096 	inc	r2
   0B7E BA 00 01           1097 	cjne	r2,#0x00,00116$
   0B81 0B                 1098 	inc	r3
   0B82                    1099 00116$:
                           1100 ;	genPointerGet
                           1101 ;	genFarPointerGet
   0B82 8A 82              1102 	mov	dpl,r2
   0B84 8B 83              1103 	mov	dph,r3
   0B86 E0                 1104 	movx	a,@dptr
                           1105 ;	genCmpEq
                           1106 ;	gencjneshort
                           1107 ;	Peephole 112.b	changed ljmp to sjmp
   0B87 FC                 1108 	mov	r4,a
                           1109 ;	Peephole 115.b	jump optimization
   0B88 60 22              1110 	jz	00107$
                           1111 ;	Peephole 300	removed redundant label 00117$
                    00E7   1112 	C$lcd_if.c$257$2$2 ==.
                           1113 ;	C:/SDCC/GPSMon/dev/lcd_if.c:257: WaitLCD();
                           1114 ;	genCall
   0B8A C0 02              1115 	push	ar2
   0B8C C0 03              1116 	push	ar3
   0B8E 12 0C 68           1117 	lcall	_WaitLCD
   0B91 D0 03              1118 	pop	ar3
   0B93 D0 02              1119 	pop	ar2
   0B95 E4                 1120 	clr	a
   0B96 33                 1121 	rlc	a
                    00F4   1122 	C$lcd_if.c$258$2$2 ==.
                           1123 ;	C:/SDCC/GPSMon/dev/lcd_if.c:258: DRWriteLCD( *chr_ptr );
                           1124 ;	genPointerGet
                           1125 ;	genFarPointerGet
   0B97 8A 82              1126 	mov	dpl,r2
   0B99 8B 83              1127 	mov	dph,r3
   0B9B E0                 1128 	movx	a,@dptr
                           1129 ;	genCall
   0B9C FC                 1130 	mov	r4,a
                           1131 ;	Peephole 244.c	loading dpl from a instead of r4
   0B9D F5 82              1132 	mov	dpl,a
   0B9F C0 02              1133 	push	ar2
   0BA1 C0 03              1134 	push	ar3
   0BA3 12 0C 32           1135 	lcall	_DRWriteLCD
   0BA6 D0 03              1136 	pop	ar3
   0BA8 D0 02              1137 	pop	ar2
                           1138 ;	Peephole 112.b	changed ljmp to sjmp
   0BAA 80 D1              1139 	sjmp	00104$
   0BAC                    1140 00107$:
                    0109   1141 	C$lcd_if.c$262$1$1 ==.
                    0109   1142 	XG$printLCD$0$0 ==.
   0BAC 22                 1143 	ret
                           1144 ;------------------------------------------------------------
                           1145 ;Allocation info for local variables in function 'printCode2LCD'
                           1146 ;------------------------------------------------------------
                           1147 ;chr_ptr                   Allocated with name '_printCode2LCD_PARM_2'
                           1148 ;offset                    Allocated with name '_printCode2LCD_PARM_3'
                           1149 ;line                      Allocated to registers r2 
                           1150 ;------------------------------------------------------------
                    010A   1151 	G$printCode2LCD$0$0 ==.
                    010A   1152 	C$lcd_if.c$269$1$1 ==.
                           1153 ;	C:/SDCC/GPSMon/dev/lcd_if.c:269: void printCode2LCD( uchar line, uchar code *chr_ptr, uchar offset ){
                           1154 ;	-----------------------------------------
                           1155 ;	 function printCode2LCD
                           1156 ;	-----------------------------------------
   0BAD                    1157 _printCode2LCD:
                           1158 ;	genReceive
   0BAD AA 82              1159 	mov	r2,dpl
                    010C   1160 	C$lcd_if.c$272$1$1 ==.
                           1161 ;	C:/SDCC/GPSMon/dev/lcd_if.c:272: if( line == 1 )
                           1162 ;	genCmpEq
                           1163 ;	gencjneshort
                           1164 ;	Peephole 112.b	changed ljmp to sjmp
                           1165 ;	Peephole 198.b	optimized misc jump sequence
   0BAF BA 01 0B           1166 	cjne	r2,#0x01,00102$
                           1167 ;	Peephole 200.b	removed redundant sjmp
                           1168 ;	Peephole 300	removed redundant label 00112$
                           1169 ;	Peephole 300	removed redundant label 00113$
                    010F   1170 	C$lcd_if.c$273$1$1 ==.
                           1171 ;	C:/SDCC/GPSMon/dev/lcd_if.c:273: IRWriteLCD( 0x80 + offset );
                           1172 ;	genPlus
                           1173 ;     genPlusIncr
   0BB2 74 80              1174 	mov	a,#0x80
   0BB4 25 0D              1175 	add	a,_printCode2LCD_PARM_3
   0BB6 F5 82              1176 	mov	dpl,a
                           1177 ;	genCall
   0BB8 12 0B FC           1178 	lcall	_IRWriteLCD
                           1179 ;	Peephole 112.b	changed ljmp to sjmp
   0BBB 80 09              1180 	sjmp	00110$
   0BBD                    1181 00102$:
                    011A   1182 	C$lcd_if.c$275$1$1 ==.
                           1183 ;	C:/SDCC/GPSMon/dev/lcd_if.c:275: IRWriteLCD( 0xC0 + offset );
                           1184 ;	genPlus
                           1185 ;     genPlusIncr
   0BBD 74 C0              1186 	mov	a,#0xC0
   0BBF 25 0D              1187 	add	a,_printCode2LCD_PARM_3
   0BC1 F5 82              1188 	mov	dpl,a
                           1189 ;	genCall
   0BC3 12 0B FC           1190 	lcall	_IRWriteLCD
                    0123   1191 	C$lcd_if.c$279$1$1 ==.
                           1192 ;	C:/SDCC/GPSMon/dev/lcd_if.c:279: do{
   0BC6                    1193 00110$:
                           1194 ;	genAssign
   0BC6 AA 0B              1195 	mov	r2,_printCode2LCD_PARM_2
   0BC8 AB 0C              1196 	mov	r3,(_printCode2LCD_PARM_2 + 1)
   0BCA                    1197 00104$:
                    0127   1198 	C$lcd_if.c$280$2$2 ==.
                           1199 ;	C:/SDCC/GPSMon/dev/lcd_if.c:280: WaitLCD();
                           1200 ;	genCall
   0BCA C0 02              1201 	push	ar2
   0BCC C0 03              1202 	push	ar3
   0BCE 12 0C 68           1203 	lcall	_WaitLCD
   0BD1 D0 03              1204 	pop	ar3
   0BD3 D0 02              1205 	pop	ar2
   0BD5 E4                 1206 	clr	a
   0BD6 33                 1207 	rlc	a
                    0134   1208 	C$lcd_if.c$281$2$2 ==.
                           1209 ;	C:/SDCC/GPSMon/dev/lcd_if.c:281: DRWriteLCD( *chr_ptr++ );
                           1210 ;	genPointerGet
                           1211 ;	genCodePointerGet
   0BD7 8A 82              1212 	mov	dpl,r2
   0BD9 8B 83              1213 	mov	dph,r3
   0BDB E4                 1214 	clr	a
   0BDC 93                 1215 	movc	a,@a+dptr
   0BDD FC                 1216 	mov	r4,a
   0BDE A3                 1217 	inc	dptr
   0BDF AA 82              1218 	mov	r2,dpl
   0BE1 AB 83              1219 	mov	r3,dph
                           1220 ;	genCall
   0BE3 8C 82              1221 	mov	dpl,r4
   0BE5 C0 02              1222 	push	ar2
   0BE7 C0 03              1223 	push	ar3
   0BE9 12 0C 32           1224 	lcall	_DRWriteLCD
   0BEC D0 03              1225 	pop	ar3
   0BEE D0 02              1226 	pop	ar2
                    014D   1227 	C$lcd_if.c$282$1$1 ==.
                           1228 ;	C:/SDCC/GPSMon/dev/lcd_if.c:282: }while( *chr_ptr != '\0' );
                           1229 ;	genPointerGet
                           1230 ;	genCodePointerGet
   0BF0 8A 82              1231 	mov	dpl,r2
   0BF2 8B 83              1232 	mov	dph,r3
   0BF4 E4                 1233 	clr	a
   0BF5 93                 1234 	movc	a,@a+dptr
                           1235 ;	genCmpEq
                           1236 ;	gencjneshort
   0BF6 FC                 1237 	mov	r4,a
                           1238 ;	Peephole 115.b	jump optimization
   0BF7 60 02              1239 	jz	00115$
                           1240 ;	Peephole 300	removed redundant label 00114$
                           1241 ;	Peephole 112.b	changed ljmp to sjmp
   0BF9 80 CF              1242 	sjmp	00104$
   0BFB                    1243 00115$:
                           1244 ;	Peephole 300	removed redundant label 00107$
                    0158   1245 	C$lcd_if.c$284$1$1 ==.
                    0158   1246 	XG$printCode2LCD$0$0 ==.
   0BFB 22                 1247 	ret
                           1248 ;------------------------------------------------------------
                           1249 ;Allocation info for local variables in function 'IRWriteLCD'
                           1250 ;------------------------------------------------------------
                           1251 ;outbyte                   Allocated to registers r2 
                           1252 ;i                         Allocated to registers r3 
                           1253 ;------------------------------------------------------------
                    0159   1254 	G$IRWriteLCD$0$0 ==.
                    0159   1255 	C$lcd_if.c$299$1$1 ==.
                           1256 ;	C:/SDCC/GPSMon/dev/lcd_if.c:299: void IRWriteLCD( uchar outbyte){
                           1257 ;	-----------------------------------------
                           1258 ;	 function IRWriteLCD
                           1259 ;	-----------------------------------------
   0BFC                    1260 _IRWriteLCD:
                           1261 ;	genReceive
   0BFC AA 82              1262 	mov	r2,dpl
                    015B   1263 	C$lcd_if.c$305$1$1 ==.
                           1264 ;	C:/SDCC/GPSMon/dev/lcd_if.c:305: SetLCDOut();                // Configs Port bits to output
                           1265 ;	genCall
   0BFE C0 02              1266 	push	ar2
   0C00 12 0C 91           1267 	lcall	_SetLCDOut
   0C03 D0 02              1268 	pop	ar2
                    0162   1269 	C$lcd_if.c$306$1$1 ==.
                           1270 ;	C:/SDCC/GPSMon/dev/lcd_if.c:306: i = i & 0xf0;               // Strip low nibble
                           1271 ;	genAnd
   0C05 74 F0              1272 	mov	a,#0xF0
   0C07 5A                 1273 	anl	a,r2
   0C08 FB                 1274 	mov	r3,a
                    0166   1275 	C$lcd_if.c$310$1$1 ==.
                           1276 ;	C:/SDCC/GPSMon/dev/lcd_if.c:310: LCD_PORT = i;               // Write high nibble
                           1277 ;	genAssign
   0C09 8B 90              1278 	mov	_P1,r3
                    0168   1279 	C$lcd_if.c$311$1$1 ==.
                           1280 ;	C:/SDCC/GPSMon/dev/lcd_if.c:311: ClrLCDRs();                 // Instruction
                           1281 ;	genCall
   0C0B C0 02              1282 	push	ar2
   0C0D 12 0C 9E           1283 	lcall	_ClrLCDRs
   0C10 D0 02              1284 	pop	ar2
                    016F   1285 	C$lcd_if.c$312$1$1 ==.
                           1286 ;	C:/SDCC/GPSMon/dev/lcd_if.c:312: ClrLCDRw();                 // Write
                           1287 ;	genCall
   0C12 C0 02              1288 	push	ar2
   0C14 12 0C A4           1289 	lcall	_ClrLCDRw
   0C17 D0 02              1290 	pop	ar2
                    0176   1291 	C$lcd_if.c$313$1$1 ==.
                           1292 ;	C:/SDCC/GPSMon/dev/lcd_if.c:313: ClockEn();                	// Trigger
                           1293 ;	genCall
   0C19 C0 02              1294 	push	ar2
   0C1B 12 0C 92           1295 	lcall	_ClockEn
   0C1E D0 02              1296 	pop	ar2
                    017D   1297 	C$lcd_if.c$317$1$1 ==.
                           1298 ;	C:/SDCC/GPSMon/dev/lcd_if.c:317: i = (i & 0x0f);             // Strip high nibble
                           1299 ;	genAnd
   0C20 74 0F              1300 	mov	a,#0x0F
   0C22 5A                 1301 	anl	a,r2
                    0180   1302 	C$lcd_if.c$319$1$1 ==.
                           1303 ;	C:/SDCC/GPSMon/dev/lcd_if.c:319: i = i*16;					// Shift low nibble to high
                           1304 ;	genLeftShift
                           1305 ;	genLeftShiftLiteral
                           1306 ;	genlshOne
   0C23 FB                 1307 	mov	r3,a
                           1308 ;	Peephole 105	removed redundant mov
   0C24 C4                 1309 	swap	a
   0C25 54 F0              1310 	anl	a,#0xf0
   0C27 F5 90              1311 	mov	_P1,a
                    0186   1312 	C$lcd_if.c$322$1$1 ==.
                           1313 ;	C:/SDCC/GPSMon/dev/lcd_if.c:322: ClrLCDRs();                 // Instruction
                           1314 ;	genCall
   0C29 12 0C 9E           1315 	lcall	_ClrLCDRs
                    0189   1316 	C$lcd_if.c$323$1$1 ==.
                           1317 ;	C:/SDCC/GPSMon/dev/lcd_if.c:323: ClrLCDRw();                 // Write
                           1318 ;	genCall
   0C2C 12 0C A4           1319 	lcall	_ClrLCDRw
                    018C   1320 	C$lcd_if.c$324$1$1 ==.
                           1321 ;	C:/SDCC/GPSMon/dev/lcd_if.c:324: ClockEn();
                           1322 ;	genCall
                    018C   1323 	C$lcd_if.c$326$1$1 ==.
                    018C   1324 	XG$IRWriteLCD$0$0 ==.
                           1325 ;	Peephole 253.b	replaced lcall/ret with ljmp
   0C2F 02 0C 92           1326 	ljmp	_ClockEn
                           1327 ;
                           1328 ;------------------------------------------------------------
                           1329 ;Allocation info for local variables in function 'DRWriteLCD'
                           1330 ;------------------------------------------------------------
                           1331 ;outbyte                   Allocated to registers r2 
                           1332 ;i                         Allocated to registers r3 
                           1333 ;------------------------------------------------------------
                    018F   1334 	G$DRWriteLCD$0$0 ==.
                    018F   1335 	C$lcd_if.c$333$1$1 ==.
                           1336 ;	C:/SDCC/GPSMon/dev/lcd_if.c:333: void DRWriteLCD( uchar outbyte){
                           1337 ;	-----------------------------------------
                           1338 ;	 function DRWriteLCD
                           1339 ;	-----------------------------------------
   0C32                    1340 _DRWriteLCD:
                           1341 ;	genReceive
   0C32 AA 82              1342 	mov	r2,dpl
                    0191   1343 	C$lcd_if.c$339$1$1 ==.
                           1344 ;	C:/SDCC/GPSMon/dev/lcd_if.c:339: SetLCDOut();                // Configs Port bits to output
                           1345 ;	genCall
   0C34 C0 02              1346 	push	ar2
   0C36 12 0C 91           1347 	lcall	_SetLCDOut
   0C39 D0 02              1348 	pop	ar2
                    0198   1349 	C$lcd_if.c$340$1$1 ==.
                           1350 ;	C:/SDCC/GPSMon/dev/lcd_if.c:340: i = i & 0xf0;               // Strip low nibble
                           1351 ;	genAnd
   0C3B 74 F0              1352 	mov	a,#0xF0
   0C3D 5A                 1353 	anl	a,r2
   0C3E FB                 1354 	mov	r3,a
                    019C   1355 	C$lcd_if.c$344$1$1 ==.
                           1356 ;	C:/SDCC/GPSMon/dev/lcd_if.c:344: LCD_PORT = i;               // Write high nibble
                           1357 ;	genAssign
   0C3F 8B 90              1358 	mov	_P1,r3
                    019E   1359 	C$lcd_if.c$345$1$1 ==.
                           1360 ;	C:/SDCC/GPSMon/dev/lcd_if.c:345: SetLCDRs();                 // Data
                           1361 ;	genCall
   0C41 C0 02              1362 	push	ar2
   0C43 12 0C 9B           1363 	lcall	_SetLCDRs
   0C46 D0 02              1364 	pop	ar2
                    01A5   1365 	C$lcd_if.c$346$1$1 ==.
                           1366 ;	C:/SDCC/GPSMon/dev/lcd_if.c:346: ClrLCDRw();                 // Write
                           1367 ;	genCall
   0C48 C0 02              1368 	push	ar2
   0C4A 12 0C A4           1369 	lcall	_ClrLCDRw
   0C4D D0 02              1370 	pop	ar2
                    01AC   1371 	C$lcd_if.c$347$1$1 ==.
                           1372 ;	C:/SDCC/GPSMon/dev/lcd_if.c:347: ClockEn();
                           1373 ;	genCall
   0C4F C0 02              1374 	push	ar2
   0C51 12 0C 92           1375 	lcall	_ClockEn
   0C54 D0 02              1376 	pop	ar2
                    01B3   1377 	C$lcd_if.c$351$1$1 ==.
                           1378 ;	C:/SDCC/GPSMon/dev/lcd_if.c:351: i = (i & 0x0f);             // Strip high nibble
                           1379 ;	genAnd
   0C56 74 0F              1380 	mov	a,#0x0F
   0C58 5A                 1381 	anl	a,r2
                    01B6   1382 	C$lcd_if.c$353$1$1 ==.
                           1383 ;	C:/SDCC/GPSMon/dev/lcd_if.c:353: i = i*16;					// Shift low to high
                           1384 ;	genLeftShift
                           1385 ;	genLeftShiftLiteral
                           1386 ;	genlshOne
   0C59 FB                 1387 	mov	r3,a
                           1388 ;	Peephole 105	removed redundant mov
   0C5A C4                 1389 	swap	a
   0C5B 54 F0              1390 	anl	a,#0xf0
   0C5D F5 90              1391 	mov	_P1,a
                    01BC   1392 	C$lcd_if.c$356$1$1 ==.
                           1393 ;	C:/SDCC/GPSMon/dev/lcd_if.c:356: SetLCDRs();                 // Data
                           1394 ;	genCall
   0C5F 12 0C 9B           1395 	lcall	_SetLCDRs
                    01BF   1396 	C$lcd_if.c$357$1$1 ==.
                           1397 ;	C:/SDCC/GPSMon/dev/lcd_if.c:357: ClrLCDRw();                 // Write
                           1398 ;	genCall
   0C62 12 0C A4           1399 	lcall	_ClrLCDRw
                    01C2   1400 	C$lcd_if.c$358$1$1 ==.
                           1401 ;	C:/SDCC/GPSMon/dev/lcd_if.c:358: ClockEn();
                           1402 ;	genCall
                    01C2   1403 	C$lcd_if.c$360$1$1 ==.
                    01C2   1404 	XG$DRWriteLCD$0$0 ==.
                           1405 ;	Peephole 253.b	replaced lcall/ret with ljmp
   0C65 02 0C 92           1406 	ljmp	_ClockEn
                           1407 ;
                           1408 ;------------------------------------------------------------
                           1409 ;Allocation info for local variables in function 'WaitLCD'
                           1410 ;------------------------------------------------------------
                           1411 ;i                         Allocated to registers r2 
                           1412 ;------------------------------------------------------------
                    01C5   1413 	G$WaitLCD$0$0 ==.
                    01C5   1414 	C$lcd_if.c$371$1$1 ==.
                           1415 ;	C:/SDCC/GPSMon/dev/lcd_if.c:371: bit WaitLCD( void ){
                           1416 ;	-----------------------------------------
                           1417 ;	 function WaitLCD
                           1418 ;	-----------------------------------------
   0C68                    1419 _WaitLCD:
                    01C5   1420 	C$lcd_if.c$383$1$1 ==.
                           1421 ;	C:/SDCC/GPSMon/dev/lcd_if.c:383: SetLCDIn();		// set busy flag line as input
                           1422 ;	genCall
   0C68 12 0C 8E           1423 	lcall	_SetLCDIn
                    01C8   1424 	C$lcd_if.c$384$1$1 ==.
                           1425 ;	C:/SDCC/GPSMon/dev/lcd_if.c:384: ClrLCDRs();		// instruction
                           1426 ;	genCall
   0C6B 12 0C 9E           1427 	lcall	_ClrLCDRs
                    01CB   1428 	C$lcd_if.c$385$1$1 ==.
                           1429 ;	C:/SDCC/GPSMon/dev/lcd_if.c:385: SetLCDRw();		// set display to *talk* mode
                           1430 ;	genCall
   0C6E 12 0C A1           1431 	lcall	_SetLCDRw
                    01CE   1432 	C$lcd_if.c$388$1$1 ==.
                           1433 ;	C:/SDCC/GPSMon/dev/lcd_if.c:388: for( i=0; i<5; i++ )	// wait 1uS
   0C71                    1434 00112$:
                           1435 ;	genAssign
   0C71 7A 05              1436 	mov	r2,#0x05
   0C73                    1437 00106$:
                           1438 ;	genDjnz
                           1439 ;	Peephole 112.b	changed ljmp to sjmp
                           1440 ;	Peephole 205	optimized misc jump sequence
   0C73 DA FE              1441 	djnz	r2,00106$
                           1442 ;	Peephole 300	removed redundant label 00120$
                           1443 ;	Peephole 300	removed redundant label 00121$
                    01D2   1444 	C$lcd_if.c$390$2$2 ==.
                           1445 ;	C:/SDCC/GPSMon/dev/lcd_if.c:390: LCD_EN = 1;
                           1446 ;	genAssign
   0C75 D2 92              1447 	setb	_P1_2
                    01D4   1448 	C$lcd_if.c$391$1$1 ==.
                           1449 ;	C:/SDCC/GPSMon/dev/lcd_if.c:391: for( i=0; i<5; i++ )	// wait 1uS
                           1450 ;	genAssign
   0C77 7A 05              1451 	mov	r2,#0x05
   0C79                    1452 00109$:
                           1453 ;	genDjnz
                           1454 ;	Peephole 112.b	changed ljmp to sjmp
                           1455 ;	Peephole 205	optimized misc jump sequence
   0C79 DA FE              1456 	djnz	r2,00109$
                           1457 ;	Peephole 300	removed redundant label 00122$
                           1458 ;	Peephole 300	removed redundant label 00123$
                    01D8   1459 	C$lcd_if.c$393$2$2 ==.
                           1460 ;	C:/SDCC/GPSMon/dev/lcd_if.c:393: bi = BUSY_FLAG;
                           1461 ;	genAssign
   0C7B A2 97              1462 	mov	c,_P1_7
   0C7D 92 0A              1463 	mov	_WaitLCD_bi_1_1,c
                    01DC   1464 	C$lcd_if.c$395$2$2 ==.
                           1465 ;	C:/SDCC/GPSMon/dev/lcd_if.c:395: LCD_EN = 0;
                           1466 ;	genAssign
   0C7F C2 92              1467 	clr	_P1_2
                    01DE   1468 	C$lcd_if.c$396$1$1 ==.
                           1469 ;	C:/SDCC/GPSMon/dev/lcd_if.c:396: }while( bi ); //&& !bt );     // We wait here until BF goes low
                           1470 ;	genIfx
                           1471 ;	genIfxJump
                           1472 ;	Peephole 108.e	removed ljmp by inverse jump logic
   0C81 20 0A ED           1473 	jb	_WaitLCD_bi_1_1,00112$
                           1474 ;	Peephole 300	removed redundant label 00124$
                    01E1   1475 	C$lcd_if.c$400$1$1 ==.
                           1476 ;	C:/SDCC/GPSMon/dev/lcd_if.c:400: ClrLCDRw();		// set display back to *listen* mode (default)
                           1477 ;	genCall
   0C84 12 0C A4           1478 	lcall	_ClrLCDRw
                    01E4   1479 	C$lcd_if.c$402$1$1 ==.
                           1480 ;	C:/SDCC/GPSMon/dev/lcd_if.c:402: return( bi );
                           1481 ;	genRet
   0C87 E4                 1482 	clr	a
   0C88 A2 0A              1483 	mov	c,_WaitLCD_bi_1_1
   0C8A 33                 1484 	rlc	a
   0C8B 24 FF              1485 	add	a,#0xff
                           1486 ;	Peephole 300	removed redundant label 00110$
                    01EA   1487 	C$lcd_if.c$404$1$1 ==.
                    01EA   1488 	XG$WaitLCD$0$0 ==.
   0C8D 22                 1489 	ret
                           1490 ;------------------------------------------------------------
                           1491 ;Allocation info for local variables in function 'SetLCDIn'
                           1492 ;------------------------------------------------------------
                           1493 ;------------------------------------------------------------
                    01EB   1494 	G$SetLCDIn$0$0 ==.
                    01EB   1495 	C$lcd_if.c$415$1$1 ==.
                           1496 ;	C:/SDCC/GPSMon/dev/lcd_if.c:415: void SetLCDIn( void ){
                           1497 ;	-----------------------------------------
                           1498 ;	 function SetLCDIn
                           1499 ;	-----------------------------------------
   0C8E                    1500 _SetLCDIn:
                    01EB   1501 	C$lcd_if.c$423$1$1 ==.
                           1502 ;	C:/SDCC/GPSMon/dev/lcd_if.c:423: BUSY_FLAG = 1;			// write 1 to make pin an input
                           1503 ;	genAssign
   0C8E D2 97              1504 	setb	_P1_7
                           1505 ;	Peephole 300	removed redundant label 00101$
                    01ED   1506 	C$lcd_if.c$426$1$1 ==.
                    01ED   1507 	XG$SetLCDIn$0$0 ==.
   0C90 22                 1508 	ret
                           1509 ;------------------------------------------------------------
                           1510 ;Allocation info for local variables in function 'SetLCDOut'
                           1511 ;------------------------------------------------------------
                           1512 ;------------------------------------------------------------
                    01EE   1513 	G$SetLCDOut$0$0 ==.
                    01EE   1514 	C$lcd_if.c$436$1$1 ==.
                           1515 ;	C:/SDCC/GPSMon/dev/lcd_if.c:436: void SetLCDOut( void ){
                           1516 ;	-----------------------------------------
                           1517 ;	 function SetLCDOut
                           1518 ;	-----------------------------------------
   0C91                    1519 _SetLCDOut:
                    01EE   1520 	C$lcd_if.c$445$1$1 ==.
                           1521 ;	C:/SDCC/GPSMon/dev/lcd_if.c:445: } // end SetLCDOut()
                           1522 ;	Peephole 300	removed redundant label 00101$
                    01EE   1523 	C$lcd_if.c$445$1$1 ==.
                    01EE   1524 	XG$SetLCDOut$0$0 ==.
   0C91 22                 1525 	ret
                           1526 ;------------------------------------------------------------
                           1527 ;Allocation info for local variables in function 'ClockEn'
                           1528 ;------------------------------------------------------------
                           1529 ;i                         Allocated to registers r2 
                           1530 ;------------------------------------------------------------
                    01EF   1531 	G$ClockEn$0$0 ==.
                    01EF   1532 	C$lcd_if.c$450$1$1 ==.
                           1533 ;	C:/SDCC/GPSMon/dev/lcd_if.c:450: void ClockEn( void ){
                           1534 ;	-----------------------------------------
                           1535 ;	 function ClockEn
                           1536 ;	-----------------------------------------
   0C92                    1537 _ClockEn:
                    01EF   1538 	C$lcd_if.c$454$1$1 ==.
                           1539 ;	C:/SDCC/GPSMon/dev/lcd_if.c:454: LCD_EN = 1;
                           1540 ;	genAssign
   0C92 D2 92              1541 	setb	_P1_2
                    01F1   1542 	C$lcd_if.c$457$1$1 ==.
                           1543 ;	C:/SDCC/GPSMon/dev/lcd_if.c:457: for( i=0; i<5; i++ )
                           1544 ;	genAssign
   0C94 7A 05              1545 	mov	r2,#0x05
   0C96                    1546 00103$:
                           1547 ;	genDjnz
                           1548 ;	Peephole 112.b	changed ljmp to sjmp
                           1549 ;	Peephole 205	optimized misc jump sequence
   0C96 DA FE              1550 	djnz	r2,00103$
                           1551 ;	Peephole 300	removed redundant label 00109$
                           1552 ;	Peephole 300	removed redundant label 00110$
                    01F5   1553 	C$lcd_if.c$459$1$1 ==.
                           1554 ;	C:/SDCC/GPSMon/dev/lcd_if.c:459: LCD_EN = 0;
                           1555 ;	genAssign
   0C98 C2 92              1556 	clr	_P1_2
                           1557 ;	Peephole 300	removed redundant label 00104$
                    01F7   1558 	C$lcd_if.c$461$1$1 ==.
                    01F7   1559 	XG$ClockEn$0$0 ==.
   0C9A 22                 1560 	ret
                           1561 ;------------------------------------------------------------
                           1562 ;Allocation info for local variables in function 'SetLCDRs'
                           1563 ;------------------------------------------------------------
                           1564 ;------------------------------------------------------------
                    01F8   1565 	G$SetLCDRs$0$0 ==.
                    01F8   1566 	C$lcd_if.c$468$1$1 ==.
                           1567 ;	C:/SDCC/GPSMon/dev/lcd_if.c:468: void SetLCDRs( void ){
                           1568 ;	-----------------------------------------
                           1569 ;	 function SetLCDRs
                           1570 ;	-----------------------------------------
   0C9B                    1571 _SetLCDRs:
                    01F8   1572 	C$lcd_if.c$471$1$1 ==.
                           1573 ;	C:/SDCC/GPSMon/dev/lcd_if.c:471: LCD_RS = 1;
                           1574 ;	genAssign
   0C9B D2 90              1575 	setb	_P1_0
                           1576 ;	Peephole 300	removed redundant label 00101$
                    01FA   1577 	C$lcd_if.c$473$1$1 ==.
                    01FA   1578 	XG$SetLCDRs$0$0 ==.
   0C9D 22                 1579 	ret
                           1580 ;------------------------------------------------------------
                           1581 ;Allocation info for local variables in function 'ClrLCDRs'
                           1582 ;------------------------------------------------------------
                           1583 ;------------------------------------------------------------
                    01FB   1584 	G$ClrLCDRs$0$0 ==.
                    01FB   1585 	C$lcd_if.c$480$1$1 ==.
                           1586 ;	C:/SDCC/GPSMon/dev/lcd_if.c:480: void ClrLCDRs( void ){
                           1587 ;	-----------------------------------------
                           1588 ;	 function ClrLCDRs
                           1589 ;	-----------------------------------------
   0C9E                    1590 _ClrLCDRs:
                    01FB   1591 	C$lcd_if.c$483$1$1 ==.
                           1592 ;	C:/SDCC/GPSMon/dev/lcd_if.c:483: LCD_RS = 0;
                           1593 ;	genAssign
   0C9E C2 90              1594 	clr	_P1_0
                           1595 ;	Peephole 300	removed redundant label 00101$
                    01FD   1596 	C$lcd_if.c$485$1$1 ==.
                    01FD   1597 	XG$ClrLCDRs$0$0 ==.
   0CA0 22                 1598 	ret
                           1599 ;------------------------------------------------------------
                           1600 ;Allocation info for local variables in function 'SetLCDRw'
                           1601 ;------------------------------------------------------------
                           1602 ;------------------------------------------------------------
                    01FE   1603 	G$SetLCDRw$0$0 ==.
                    01FE   1604 	C$lcd_if.c$492$1$1 ==.
                           1605 ;	C:/SDCC/GPSMon/dev/lcd_if.c:492: void SetLCDRw( void ){
                           1606 ;	-----------------------------------------
                           1607 ;	 function SetLCDRw
                           1608 ;	-----------------------------------------
   0CA1                    1609 _SetLCDRw:
                    01FE   1610 	C$lcd_if.c$495$1$1 ==.
                           1611 ;	C:/SDCC/GPSMon/dev/lcd_if.c:495: LCD_RW = 1;
                           1612 ;	genAssign
   0CA1 D2 91              1613 	setb	_P1_1
                           1614 ;	Peephole 300	removed redundant label 00101$
                    0200   1615 	C$lcd_if.c$497$1$1 ==.
                    0200   1616 	XG$SetLCDRw$0$0 ==.
   0CA3 22                 1617 	ret
                           1618 ;------------------------------------------------------------
                           1619 ;Allocation info for local variables in function 'ClrLCDRw'
                           1620 ;------------------------------------------------------------
                           1621 ;------------------------------------------------------------
                    0201   1622 	G$ClrLCDRw$0$0 ==.
                    0201   1623 	C$lcd_if.c$504$1$1 ==.
                           1624 ;	C:/SDCC/GPSMon/dev/lcd_if.c:504: void ClrLCDRw( void ){
                           1625 ;	-----------------------------------------
                           1626 ;	 function ClrLCDRw
                           1627 ;	-----------------------------------------
   0CA4                    1628 _ClrLCDRw:
                    0201   1629 	C$lcd_if.c$507$1$1 ==.
                           1630 ;	C:/SDCC/GPSMon/dev/lcd_if.c:507: LCD_RW = 0;
                           1631 ;	genAssign
   0CA4 C2 91              1632 	clr	_P1_1
                           1633 ;	Peephole 300	removed redundant label 00101$
                    0203   1634 	C$lcd_if.c$509$1$1 ==.
                    0203   1635 	XG$ClrLCDRw$0$0 ==.
   0CA6 22                 1636 	ret
                           1637 	.area CSEG    (CODE)
                           1638 	.area CONST   (CODE)
                           1639 	.area XINIT   (CODE)
