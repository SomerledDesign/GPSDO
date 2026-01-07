                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.6.0 #4309 (Jul 28 2006)
                              4 ; This file generated Thu Jan 01 19:10:22 2009
                              5 ;--------------------------------------------------------
                              6 	.module iconv
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
                            237 	.globl _UnsignedToAscii_PARM_3
                            238 	.globl _UnsignedToAscii_PARM_2
                            239 	.globl _AsciiToUnsigned_PARM_2
                            240 	.globl _AsciiToUnsigned
                            241 	.globl _UnsignedToAscii
                            242 ;--------------------------------------------------------
                            243 ; special function registers
                            244 ;--------------------------------------------------------
                            245 	.area RSEG    (DATA)
                    0080    246 G$P0$0$0 == 0x0080
                    0080    247 _P0	=	0x0080
                    0081    248 G$SP$0$0 == 0x0081
                    0081    249 _SP	=	0x0081
                    0082    250 G$DPL$0$0 == 0x0082
                    0082    251 _DPL	=	0x0082
                    0083    252 G$DPH$0$0 == 0x0083
                    0083    253 _DPH	=	0x0083
                    0087    254 G$PCON$0$0 == 0x0087
                    0087    255 _PCON	=	0x0087
                    0088    256 G$TCON$0$0 == 0x0088
                    0088    257 _TCON	=	0x0088
                    0089    258 G$TMOD$0$0 == 0x0089
                    0089    259 _TMOD	=	0x0089
                    008A    260 G$TL0$0$0 == 0x008a
                    008A    261 _TL0	=	0x008a
                    008B    262 G$TL1$0$0 == 0x008b
                    008B    263 _TL1	=	0x008b
                    008C    264 G$TH0$0$0 == 0x008c
                    008C    265 _TH0	=	0x008c
                    008D    266 G$TH1$0$0 == 0x008d
                    008D    267 _TH1	=	0x008d
                    008E    268 G$CKCON$0$0 == 0x008e
                    008E    269 _CKCON	=	0x008e
                    008F    270 G$PSCTL$0$0 == 0x008f
                    008F    271 _PSCTL	=	0x008f
                    0090    272 G$P1$0$0 == 0x0090
                    0090    273 _P1	=	0x0090
                    0091    274 G$TMR3CN$0$0 == 0x0091
                    0091    275 _TMR3CN	=	0x0091
                    0092    276 G$TMR3RLL$0$0 == 0x0092
                    0092    277 _TMR3RLL	=	0x0092
                    0093    278 G$TMR3RLH$0$0 == 0x0093
                    0093    279 _TMR3RLH	=	0x0093
                    0094    280 G$TMR3L$0$0 == 0x0094
                    0094    281 _TMR3L	=	0x0094
                    0095    282 G$TMR3H$0$0 == 0x0095
                    0095    283 _TMR3H	=	0x0095
                    0096    284 G$IDA0L$0$0 == 0x0096
                    0096    285 _IDA0L	=	0x0096
                    0097    286 G$IDA0H$0$0 == 0x0097
                    0097    287 _IDA0H	=	0x0097
                    0098    288 G$SCON$0$0 == 0x0098
                    0098    289 _SCON	=	0x0098
                    0098    290 G$SCON0$0$0 == 0x0098
                    0098    291 _SCON0	=	0x0098
                    0099    292 G$SBUF$0$0 == 0x0099
                    0099    293 _SBUF	=	0x0099
                    0099    294 G$SBUF0$0$0 == 0x0099
                    0099    295 _SBUF0	=	0x0099
                    009B    296 G$CPT0CN$0$0 == 0x009b
                    009B    297 _CPT0CN	=	0x009b
                    009D    298 G$CPT0MD$0$0 == 0x009d
                    009D    299 _CPT0MD	=	0x009d
                    009F    300 G$CPT0MX$0$0 == 0x009f
                    009F    301 _CPT0MX	=	0x009f
                    00A0    302 G$P2$0$0 == 0x00a0
                    00A0    303 _P2	=	0x00a0
                    00A1    304 G$SPI0CFG$0$0 == 0x00a1
                    00A1    305 _SPI0CFG	=	0x00a1
                    00A2    306 G$SPI0CKR$0$0 == 0x00a2
                    00A2    307 _SPI0CKR	=	0x00a2
                    00A3    308 G$SPI0DAT$0$0 == 0x00a3
                    00A3    309 _SPI0DAT	=	0x00a3
                    00A4    310 G$P0MDOUT$0$0 == 0x00a4
                    00A4    311 _P0MDOUT	=	0x00a4
                    00A5    312 G$P1MDOUT$0$0 == 0x00a5
                    00A5    313 _P1MDOUT	=	0x00a5
                    00A6    314 G$P2MDOUT$0$0 == 0x00a6
                    00A6    315 _P2MDOUT	=	0x00a6
                    00A8    316 G$IE$0$0 == 0x00a8
                    00A8    317 _IE	=	0x00a8
                    00A9    318 G$CLKSEL$0$0 == 0x00a9
                    00A9    319 _CLKSEL	=	0x00a9
                    00AA    320 G$EMI0CN$0$0 == 0x00aa
                    00AA    321 _EMI0CN	=	0x00aa
                    00AA    322 G$_XPAGE$0$0 == 0x00aa
                    00AA    323 __XPAGE	=	0x00aa
                    00B1    324 G$OSCXCN$0$0 == 0x00b1
                    00B1    325 _OSCXCN	=	0x00b1
                    00B2    326 G$OSCICN$0$0 == 0x00b2
                    00B2    327 _OSCICN	=	0x00b2
                    00B3    328 G$OSCICL$0$0 == 0x00b3
                    00B3    329 _OSCICL	=	0x00b3
                    00B6    330 G$FLSCL$0$0 == 0x00b6
                    00B6    331 _FLSCL	=	0x00b6
                    00B7    332 G$FLKEY$0$0 == 0x00b7
                    00B7    333 _FLKEY	=	0x00b7
                    00B8    334 G$IP$0$0 == 0x00b8
                    00B8    335 _IP	=	0x00b8
                    00B9    336 G$IDA0CN$0$0 == 0x00b9
                    00B9    337 _IDA0CN	=	0x00b9
                    00BA    338 G$AMX0N$0$0 == 0x00ba
                    00BA    339 _AMX0N	=	0x00ba
                    00BB    340 G$AMX0P$0$0 == 0x00bb
                    00BB    341 _AMX0P	=	0x00bb
                    00BC    342 G$ADC0CF$0$0 == 0x00bc
                    00BC    343 _ADC0CF	=	0x00bc
                    00BD    344 G$ADC0L$0$0 == 0x00bd
                    00BD    345 _ADC0L	=	0x00bd
                    00BE    346 G$ADC0H$0$0 == 0x00be
                    00BE    347 _ADC0H	=	0x00be
                    00C0    348 G$SMB0CN$0$0 == 0x00c0
                    00C0    349 _SMB0CN	=	0x00c0
                    00C1    350 G$SMB0CF$0$0 == 0x00c1
                    00C1    351 _SMB0CF	=	0x00c1
                    00C2    352 G$SMB0DAT$0$0 == 0x00c2
                    00C2    353 _SMB0DAT	=	0x00c2
                    00C3    354 G$ADC0GTL$0$0 == 0x00c3
                    00C3    355 _ADC0GTL	=	0x00c3
                    00C4    356 G$ADC0GTH$0$0 == 0x00c4
                    00C4    357 _ADC0GTH	=	0x00c4
                    00C5    358 G$ADC0LTL$0$0 == 0x00c5
                    00C5    359 _ADC0LTL	=	0x00c5
                    00C6    360 G$ADC0LTH$0$0 == 0x00c6
                    00C6    361 _ADC0LTH	=	0x00c6
                    00C8    362 G$T2CON$0$0 == 0x00c8
                    00C8    363 _T2CON	=	0x00c8
                    00C8    364 G$TMR2CN$0$0 == 0x00c8
                    00C8    365 _TMR2CN	=	0x00c8
                    00CA    366 G$RCAP2L$0$0 == 0x00ca
                    00CA    367 _RCAP2L	=	0x00ca
                    00CA    368 G$TMR2RLL$0$0 == 0x00ca
                    00CA    369 _TMR2RLL	=	0x00ca
                    00CB    370 G$RCAP2H$0$0 == 0x00cb
                    00CB    371 _RCAP2H	=	0x00cb
                    00CB    372 G$TMR2RLH$0$0 == 0x00cb
                    00CB    373 _TMR2RLH	=	0x00cb
                    00CC    374 G$TL2$0$0 == 0x00cc
                    00CC    375 _TL2	=	0x00cc
                    00CC    376 G$TMR2L$0$0 == 0x00cc
                    00CC    377 _TMR2L	=	0x00cc
                    00CD    378 G$TH2$0$0 == 0x00cd
                    00CD    379 _TH2	=	0x00cd
                    00CD    380 G$TMR2H$0$0 == 0x00cd
                    00CD    381 _TMR2H	=	0x00cd
                    00D0    382 G$PSW$0$0 == 0x00d0
                    00D0    383 _PSW	=	0x00d0
                    00D1    384 G$REF0CN$0$0 == 0x00d1
                    00D1    385 _REF0CN	=	0x00d1
                    00D4    386 G$P0SKIP$0$0 == 0x00d4
                    00D4    387 _P0SKIP	=	0x00d4
                    00D5    388 G$P1SKIP$0$0 == 0x00d5
                    00D5    389 _P1SKIP	=	0x00d5
                    00D8    390 G$PCA0CN$0$0 == 0x00d8
                    00D8    391 _PCA0CN	=	0x00d8
                    00D9    392 G$PCA0MD$0$0 == 0x00d9
                    00D9    393 _PCA0MD	=	0x00d9
                    00DA    394 G$PCA0CPM0$0$0 == 0x00da
                    00DA    395 _PCA0CPM0	=	0x00da
                    00DB    396 G$PCA0CPM1$0$0 == 0x00db
                    00DB    397 _PCA0CPM1	=	0x00db
                    00DC    398 G$PCA0CPM2$0$0 == 0x00dc
                    00DC    399 _PCA0CPM2	=	0x00dc
                    00E0    400 G$ACC$0$0 == 0x00e0
                    00E0    401 _ACC	=	0x00e0
                    00E1    402 G$XBR0$0$0 == 0x00e1
                    00E1    403 _XBR0	=	0x00e1
                    00E2    404 G$XBR1$0$0 == 0x00e2
                    00E2    405 _XBR1	=	0x00e2
                    00E3    406 G$OSCLCN$0$0 == 0x00e3
                    00E3    407 _OSCLCN	=	0x00e3
                    00E4    408 G$IT01CF$0$0 == 0x00e4
                    00E4    409 _IT01CF	=	0x00e4
                    00E4    410 G$INT01CF$0$0 == 0x00e4
                    00E4    411 _INT01CF	=	0x00e4
                    00E6    412 G$EIE1$0$0 == 0x00e6
                    00E6    413 _EIE1	=	0x00e6
                    00E8    414 G$ADC0CN$0$0 == 0x00e8
                    00E8    415 _ADC0CN	=	0x00e8
                    00E9    416 G$PCA0CPL1$0$0 == 0x00e9
                    00E9    417 _PCA0CPL1	=	0x00e9
                    00EA    418 G$PCA0CPH1$0$0 == 0x00ea
                    00EA    419 _PCA0CPH1	=	0x00ea
                    00EB    420 G$PCA0CPL2$0$0 == 0x00eb
                    00EB    421 _PCA0CPL2	=	0x00eb
                    00EC    422 G$PCA0CPH2$0$0 == 0x00ec
                    00EC    423 _PCA0CPH2	=	0x00ec
                    00EF    424 G$RSTSRC$0$0 == 0x00ef
                    00EF    425 _RSTSRC	=	0x00ef
                    00F0    426 G$B$0$0 == 0x00f0
                    00F0    427 _B	=	0x00f0
                    00F1    428 G$P0MODE$0$0 == 0x00f1
                    00F1    429 _P0MODE	=	0x00f1
                    00F1    430 G$P0MDIN$0$0 == 0x00f1
                    00F1    431 _P0MDIN	=	0x00f1
                    00F2    432 G$P1MODE$0$0 == 0x00f2
                    00F2    433 _P1MODE	=	0x00f2
                    00F2    434 G$P1MDIN$0$0 == 0x00f2
                    00F2    435 _P1MDIN	=	0x00f2
                    00F6    436 G$EIP1$0$0 == 0x00f6
                    00F6    437 _EIP1	=	0x00f6
                    00F8    438 G$SPI0CN$0$0 == 0x00f8
                    00F8    439 _SPI0CN	=	0x00f8
                    00F9    440 G$PCA0L$0$0 == 0x00f9
                    00F9    441 _PCA0L	=	0x00f9
                    00FA    442 G$PCA0H$0$0 == 0x00fa
                    00FA    443 _PCA0H	=	0x00fa
                    00FB    444 G$PCA0CPL0$0$0 == 0x00fb
                    00FB    445 _PCA0CPL0	=	0x00fb
                    00FC    446 G$PCA0CPH0$0$0 == 0x00fc
                    00FC    447 _PCA0CPH0	=	0x00fc
                    00FF    448 G$VDM0CN$0$0 == 0x00ff
                    00FF    449 _VDM0CN	=	0x00ff
                    8C8A    450 G$TMR0$0$0 == 0x8c8a
                    8C8A    451 _TMR0	=	0x8c8a
                    8D8B    452 G$TMR1$0$0 == 0x8d8b
                    8D8B    453 _TMR1	=	0x8d8b
                    CDCC    454 G$TMR2$0$0 == 0xcdcc
                    CDCC    455 _TMR2	=	0xcdcc
                    CBCA    456 G$RCAP2$0$0 == 0xcbca
                    CBCA    457 _RCAP2	=	0xcbca
                    CBCA    458 G$TMR2RL$0$0 == 0xcbca
                    CBCA    459 _TMR2RL	=	0xcbca
                    9594    460 G$TMR3$0$0 == 0x9594
                    9594    461 _TMR3	=	0x9594
                    9392    462 G$TMR3RL$0$0 == 0x9392
                    9392    463 _TMR3RL	=	0x9392
                    9796    464 G$IDA0$0$0 == 0x9796
                    9796    465 _IDA0	=	0x9796
                    BEBD    466 G$ADC0$0$0 == 0xbebd
                    BEBD    467 _ADC0	=	0xbebd
                    C4C3    468 G$ADC0GT$0$0 == 0xc4c3
                    C4C3    469 _ADC0GT	=	0xc4c3
                    C6C5    470 G$ADC0LT$0$0 == 0xc6c5
                    C6C5    471 _ADC0LT	=	0xc6c5
                    FAF9    472 G$PCA0$0$0 == 0xfaf9
                    FAF9    473 _PCA0	=	0xfaf9
                    FCFB    474 G$PCA0CP0$0$0 == 0xfcfb
                    FCFB    475 _PCA0CP0	=	0xfcfb
                    EAE9    476 G$PCA0CP1$0$0 == 0xeae9
                    EAE9    477 _PCA0CP1	=	0xeae9
                    ECEB    478 G$PCA0CP2$0$0 == 0xeceb
                    ECEB    479 _PCA0CP2	=	0xeceb
                            480 ;--------------------------------------------------------
                            481 ; special function bits
                            482 ;--------------------------------------------------------
                            483 	.area RSEG    (DATA)
                    0080    484 G$P0_0$0$0 == 0x0080
                    0080    485 _P0_0	=	0x0080
                    0081    486 G$P0_1$0$0 == 0x0081
                    0081    487 _P0_1	=	0x0081
                    0082    488 G$P0_2$0$0 == 0x0082
                    0082    489 _P0_2	=	0x0082
                    0083    490 G$P0_3$0$0 == 0x0083
                    0083    491 _P0_3	=	0x0083
                    0084    492 G$P0_4$0$0 == 0x0084
                    0084    493 _P0_4	=	0x0084
                    0085    494 G$P0_5$0$0 == 0x0085
                    0085    495 _P0_5	=	0x0085
                    0086    496 G$P0_6$0$0 == 0x0086
                    0086    497 _P0_6	=	0x0086
                    0087    498 G$P0_7$0$0 == 0x0087
                    0087    499 _P0_7	=	0x0087
                    0088    500 G$IT0$0$0 == 0x0088
                    0088    501 _IT0	=	0x0088
                    0089    502 G$IE0$0$0 == 0x0089
                    0089    503 _IE0	=	0x0089
                    008A    504 G$IT1$0$0 == 0x008a
                    008A    505 _IT1	=	0x008a
                    008B    506 G$IE1$0$0 == 0x008b
                    008B    507 _IE1	=	0x008b
                    008C    508 G$TR0$0$0 == 0x008c
                    008C    509 _TR0	=	0x008c
                    008D    510 G$TF0$0$0 == 0x008d
                    008D    511 _TF0	=	0x008d
                    008E    512 G$TR1$0$0 == 0x008e
                    008E    513 _TR1	=	0x008e
                    008F    514 G$TF1$0$0 == 0x008f
                    008F    515 _TF1	=	0x008f
                    0090    516 G$P1_0$0$0 == 0x0090
                    0090    517 _P1_0	=	0x0090
                    0091    518 G$P1_1$0$0 == 0x0091
                    0091    519 _P1_1	=	0x0091
                    0092    520 G$P1_2$0$0 == 0x0092
                    0092    521 _P1_2	=	0x0092
                    0093    522 G$P1_3$0$0 == 0x0093
                    0093    523 _P1_3	=	0x0093
                    0094    524 G$P1_4$0$0 == 0x0094
                    0094    525 _P1_4	=	0x0094
                    0095    526 G$P1_5$0$0 == 0x0095
                    0095    527 _P1_5	=	0x0095
                    0096    528 G$P1_6$0$0 == 0x0096
                    0096    529 _P1_6	=	0x0096
                    0097    530 G$P1_7$0$0 == 0x0097
                    0097    531 _P1_7	=	0x0097
                    0098    532 G$RI$0$0 == 0x0098
                    0098    533 _RI	=	0x0098
                    0098    534 G$RI0$0$0 == 0x0098
                    0098    535 _RI0	=	0x0098
                    0099    536 G$TI$0$0 == 0x0099
                    0099    537 _TI	=	0x0099
                    0099    538 G$TI0$0$0 == 0x0099
                    0099    539 _TI0	=	0x0099
                    009A    540 G$RB8$0$0 == 0x009a
                    009A    541 _RB8	=	0x009a
                    009A    542 G$RB80$0$0 == 0x009a
                    009A    543 _RB80	=	0x009a
                    009B    544 G$TB8$0$0 == 0x009b
                    009B    545 _TB8	=	0x009b
                    009B    546 G$TB80$0$0 == 0x009b
                    009B    547 _TB80	=	0x009b
                    009C    548 G$REN$0$0 == 0x009c
                    009C    549 _REN	=	0x009c
                    009C    550 G$REN0$0$0 == 0x009c
                    009C    551 _REN0	=	0x009c
                    009D    552 G$SM2$0$0 == 0x009d
                    009D    553 _SM2	=	0x009d
                    009D    554 G$MCE0$0$0 == 0x009d
                    009D    555 _MCE0	=	0x009d
                    009F    556 G$SM0$0$0 == 0x009f
                    009F    557 _SM0	=	0x009f
                    009F    558 G$S0MODE$0$0 == 0x009f
                    009F    559 _S0MODE	=	0x009f
                    00A0    560 G$P2_0$0$0 == 0x00a0
                    00A0    561 _P2_0	=	0x00a0
                    00A1    562 G$P2_1$0$0 == 0x00a1
                    00A1    563 _P2_1	=	0x00a1
                    00A2    564 G$P2_2$0$0 == 0x00a2
                    00A2    565 _P2_2	=	0x00a2
                    00A3    566 G$P2_3$0$0 == 0x00a3
                    00A3    567 _P2_3	=	0x00a3
                    00A4    568 G$P2_4$0$0 == 0x00a4
                    00A4    569 _P2_4	=	0x00a4
                    00A5    570 G$P2_5$0$0 == 0x00a5
                    00A5    571 _P2_5	=	0x00a5
                    00A6    572 G$P2_6$0$0 == 0x00a6
                    00A6    573 _P2_6	=	0x00a6
                    00A7    574 G$P2_7$0$0 == 0x00a7
                    00A7    575 _P2_7	=	0x00a7
                    00A8    576 G$EX0$0$0 == 0x00a8
                    00A8    577 _EX0	=	0x00a8
                    00A9    578 G$ET0$0$0 == 0x00a9
                    00A9    579 _ET0	=	0x00a9
                    00AA    580 G$EX1$0$0 == 0x00aa
                    00AA    581 _EX1	=	0x00aa
                    00AB    582 G$ET1$0$0 == 0x00ab
                    00AB    583 _ET1	=	0x00ab
                    00AC    584 G$ES$0$0 == 0x00ac
                    00AC    585 _ES	=	0x00ac
                    00AC    586 G$ES0$0$0 == 0x00ac
                    00AC    587 _ES0	=	0x00ac
                    00AD    588 G$ET2$0$0 == 0x00ad
                    00AD    589 _ET2	=	0x00ad
                    00AE    590 G$ESPI0$0$0 == 0x00ae
                    00AE    591 _ESPI0	=	0x00ae
                    00AF    592 G$EA$0$0 == 0x00af
                    00AF    593 _EA	=	0x00af
                    00B8    594 G$PX0$0$0 == 0x00b8
                    00B8    595 _PX0	=	0x00b8
                    00B9    596 G$PT0$0$0 == 0x00b9
                    00B9    597 _PT0	=	0x00b9
                    00BA    598 G$PX1$0$0 == 0x00ba
                    00BA    599 _PX1	=	0x00ba
                    00BB    600 G$PT1$0$0 == 0x00bb
                    00BB    601 _PT1	=	0x00bb
                    00BC    602 G$PS$0$0 == 0x00bc
                    00BC    603 _PS	=	0x00bc
                    00BC    604 G$PS0$0$0 == 0x00bc
                    00BC    605 _PS0	=	0x00bc
                    00BD    606 G$PT2$0$0 == 0x00bd
                    00BD    607 _PT2	=	0x00bd
                    00BE    608 G$PSPI0$0$0 == 0x00be
                    00BE    609 _PSPI0	=	0x00be
                    00C0    610 G$SI$0$0 == 0x00c0
                    00C0    611 _SI	=	0x00c0
                    00C1    612 G$ACK$0$0 == 0x00c1
                    00C1    613 _ACK	=	0x00c1
                    00C2    614 G$ARBLOST$0$0 == 0x00c2
                    00C2    615 _ARBLOST	=	0x00c2
                    00C3    616 G$ACKRQ$0$0 == 0x00c3
                    00C3    617 _ACKRQ	=	0x00c3
                    00C4    618 G$STO$0$0 == 0x00c4
                    00C4    619 _STO	=	0x00c4
                    00C5    620 G$STA$0$0 == 0x00c5
                    00C5    621 _STA	=	0x00c5
                    00C6    622 G$TXMODE$0$0 == 0x00c6
                    00C6    623 _TXMODE	=	0x00c6
                    00C7    624 G$MASTER$0$0 == 0x00c7
                    00C7    625 _MASTER	=	0x00c7
                    00C8    626 G$T2XCLK$0$0 == 0x00c8
                    00C8    627 _T2XCLK	=	0x00c8
                    00CA    628 G$TR2$0$0 == 0x00ca
                    00CA    629 _TR2	=	0x00ca
                    00CB    630 G$T2SPLIT$0$0 == 0x00cb
                    00CB    631 _T2SPLIT	=	0x00cb
                    00CD    632 G$TF2CEN$0$0 == 0x00cd
                    00CD    633 _TF2CEN	=	0x00cd
                    00CD    634 G$TF2LEN$0$0 == 0x00cd
                    00CD    635 _TF2LEN	=	0x00cd
                    00CE    636 G$TF2L$0$0 == 0x00ce
                    00CE    637 _TF2L	=	0x00ce
                    00CF    638 G$TF2$0$0 == 0x00cf
                    00CF    639 _TF2	=	0x00cf
                    00CF    640 G$TF2H$0$0 == 0x00cf
                    00CF    641 _TF2H	=	0x00cf
                    00D0    642 G$PARITY$0$0 == 0x00d0
                    00D0    643 _PARITY	=	0x00d0
                    00D1    644 G$F1$0$0 == 0x00d1
                    00D1    645 _F1	=	0x00d1
                    00D2    646 G$OV$0$0 == 0x00d2
                    00D2    647 _OV	=	0x00d2
                    00D3    648 G$RS0$0$0 == 0x00d3
                    00D3    649 _RS0	=	0x00d3
                    00D4    650 G$RS1$0$0 == 0x00d4
                    00D4    651 _RS1	=	0x00d4
                    00D5    652 G$F0$0$0 == 0x00d5
                    00D5    653 _F0	=	0x00d5
                    00D6    654 G$AC$0$0 == 0x00d6
                    00D6    655 _AC	=	0x00d6
                    00D7    656 G$CY$0$0 == 0x00d7
                    00D7    657 _CY	=	0x00d7
                    00D8    658 G$CCF0$0$0 == 0x00d8
                    00D8    659 _CCF0	=	0x00d8
                    00D9    660 G$CCF1$0$0 == 0x00d9
                    00D9    661 _CCF1	=	0x00d9
                    00DA    662 G$CCF2$0$0 == 0x00da
                    00DA    663 _CCF2	=	0x00da
                    00DE    664 G$CR$0$0 == 0x00de
                    00DE    665 _CR	=	0x00de
                    00DF    666 G$CF$0$0 == 0x00df
                    00DF    667 _CF	=	0x00df
                    00E8    668 G$AD0CM0$0$0 == 0x00e8
                    00E8    669 _AD0CM0	=	0x00e8
                    00E9    670 G$AD0CM1$0$0 == 0x00e9
                    00E9    671 _AD0CM1	=	0x00e9
                    00EA    672 G$AD0CM2$0$0 == 0x00ea
                    00EA    673 _AD0CM2	=	0x00ea
                    00EB    674 G$AD0WINT$0$0 == 0x00eb
                    00EB    675 _AD0WINT	=	0x00eb
                    00EC    676 G$AD0BUSY$0$0 == 0x00ec
                    00EC    677 _AD0BUSY	=	0x00ec
                    00ED    678 G$AD0INT$0$0 == 0x00ed
                    00ED    679 _AD0INT	=	0x00ed
                    00EE    680 G$AD0TM$0$0 == 0x00ee
                    00EE    681 _AD0TM	=	0x00ee
                    00EF    682 G$AD0EN$0$0 == 0x00ef
                    00EF    683 _AD0EN	=	0x00ef
                    00F8    684 G$SPIEN$0$0 == 0x00f8
                    00F8    685 _SPIEN	=	0x00f8
                    00F9    686 G$TXBMT$0$0 == 0x00f9
                    00F9    687 _TXBMT	=	0x00f9
                    00FA    688 G$NSSMD0$0$0 == 0x00fa
                    00FA    689 _NSSMD0	=	0x00fa
                    00FB    690 G$NSSMD1$0$0 == 0x00fb
                    00FB    691 _NSSMD1	=	0x00fb
                    00FC    692 G$RXOVRN$0$0 == 0x00fc
                    00FC    693 _RXOVRN	=	0x00fc
                    00FD    694 G$MODF$0$0 == 0x00fd
                    00FD    695 _MODF	=	0x00fd
                    00FE    696 G$WCOL$0$0 == 0x00fe
                    00FE    697 _WCOL	=	0x00fe
                    00FF    698 G$SPIF$0$0 == 0x00ff
                    00FF    699 _SPIF	=	0x00ff
                            700 ;--------------------------------------------------------
                            701 ; overlayable register banks
                            702 ;--------------------------------------------------------
                            703 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     704 	.ds 8
                            705 ;--------------------------------------------------------
                            706 ; internal ram data
                            707 ;--------------------------------------------------------
                            708 	.area DSEG    (DATA)
                    0000    709 LAsciiToUnsigned$p_int$1$1==.
   0018                     710 _AsciiToUnsigned_PARM_2:
   0018                     711 	.ds 3
                    0003    712 LUnsignedToAscii$pbuf$1$1==.
   001B                     713 _UnsignedToAscii_PARM_2:
   001B                     714 	.ds 2
                    0005    715 LUnsignedToAscii$nbdigits$1$1==.
   001D                     716 _UnsignedToAscii_PARM_3:
   001D                     717 	.ds 1
                            718 ;--------------------------------------------------------
                            719 ; overlayable items in internal ram 
                            720 ;--------------------------------------------------------
                            721 	.area OSEG    (OVR,DATA)
                            722 ;--------------------------------------------------------
                            723 ; indirectly addressable internal ram data
                            724 ;--------------------------------------------------------
                            725 	.area ISEG    (DATA)
                            726 ;--------------------------------------------------------
                            727 ; bit data
                            728 ;--------------------------------------------------------
                            729 	.area BSEG    (BIT)
                            730 ;--------------------------------------------------------
                            731 ; paged external ram data
                            732 ;--------------------------------------------------------
                            733 	.area PSEG    (PAG,XDATA)
                            734 ;--------------------------------------------------------
                            735 ; external ram data
                            736 ;--------------------------------------------------------
                            737 	.area XSEG    (XDATA)
                            738 ;--------------------------------------------------------
                            739 ; external initialized ram data
                            740 ;--------------------------------------------------------
                            741 	.area XISEG   (XDATA)
                            742 	.area HOME    (CODE)
                            743 	.area GSINIT0 (CODE)
                            744 	.area GSINIT1 (CODE)
                            745 	.area GSINIT2 (CODE)
                            746 	.area GSINIT3 (CODE)
                            747 	.area GSINIT4 (CODE)
                            748 	.area GSINIT5 (CODE)
                            749 	.area GSINIT  (CODE)
                            750 	.area GSFINAL (CODE)
                            751 	.area CSEG    (CODE)
                            752 ;--------------------------------------------------------
                            753 ; global & static initialisations
                            754 ;--------------------------------------------------------
                            755 	.area HOME    (CODE)
                            756 	.area GSINIT  (CODE)
                            757 	.area GSFINAL (CODE)
                            758 	.area GSINIT  (CODE)
                            759 ;--------------------------------------------------------
                            760 ; Home
                            761 ;--------------------------------------------------------
                            762 	.area HOME    (CODE)
                            763 	.area CSEG    (CODE)
                            764 ;--------------------------------------------------------
                            765 ; code
                            766 ;--------------------------------------------------------
                            767 	.area CSEG    (CODE)
                            768 ;------------------------------------------------------------
                            769 ;Allocation info for local variables in function 'AsciiToUnsigned'
                            770 ;------------------------------------------------------------
                            771 ;p_int                     Allocated with name '_AsciiToUnsigned_PARM_2'
                            772 ;p_ascii                   Allocated to registers r2 r3 
                            773 ;i                         Allocated to registers r7 
                            774 ;n                         Allocated to registers r4 
                            775 ;value                     Allocated to registers r5 r6 
                            776 ;------------------------------------------------------------
                    0000    777 	G$AsciiToUnsigned$0$0 ==.
                    0000    778 	C$iconv.c$61$0$0 ==.
                            779 ;	C:/SDCC/GPSMon/dev/iconv.c:61: uchar AsciiToUnsigned( uchar TXRX_STORAGE_CLASS *p_ascii, 
                            780 ;	-----------------------------------------
                            781 ;	 function AsciiToUnsigned
                            782 ;	-----------------------------------------
   0CA7                     783 _AsciiToUnsigned:
                    0002    784 	ar2 = 0x02
                    0003    785 	ar3 = 0x03
                    0004    786 	ar4 = 0x04
                    0005    787 	ar5 = 0x05
                    0006    788 	ar6 = 0x06
                    0007    789 	ar7 = 0x07
                    0000    790 	ar0 = 0x00
                    0001    791 	ar1 = 0x01
                            792 ;	genReceive
   0CA7 AA 82               793 	mov	r2,dpl
   0CA9 AB 83               794 	mov	r3,dph
                    0004    795 	C$iconv.c$64$1$0 ==.
                            796 ;	C:/SDCC/GPSMon/dev/iconv.c:64: uchar i = 0, n = 0;
                            797 ;	genAssign
   0CAB 7C 00               798 	mov	r4,#0x00
                    0006    799 	C$iconv.c$65$1$0 ==.
                            800 ;	C:/SDCC/GPSMon/dev/iconv.c:65: uint value = 0;
                            801 ;	genAssign
   0CAD 7D 00               802 	mov	r5,#0x00
   0CAF 7E 00               803 	mov	r6,#0x00
                    000A    804 	C$iconv.c$67$1$1 ==.
                            805 ;	C:/SDCC/GPSMon/dev/iconv.c:67: while( (i < (MAX_A2B_DIGITS+1) ) && (n < MAX_A2B_DIGITS) ){
                            806 ;	genAssign
   0CB1 7F 00               807 	mov	r7,#0x00
                            808 ;	genAssign
   0CB3                     809 00110$:
                            810 ;	genCmpLt
                            811 ;	genCmp
   0CB3 BF 06 00            812 	cjne	r7,#0x06,00128$
   0CB6                     813 00128$:
                            814 ;	genIfxJump
                            815 ;	Peephole 108.a	removed ljmp by inverse jump logic
   0CB6 50 5F               816 	jnc	00112$
                            817 ;	Peephole 300	removed redundant label 00129$
                            818 ;	genCmpLt
                            819 ;	genCmp
   0CB8 BC 05 00            820 	cjne	r4,#0x05,00130$
   0CBB                     821 00130$:
                            822 ;	genIfxJump
                            823 ;	Peephole 108.a	removed ljmp by inverse jump logic
   0CBB 50 5A               824 	jnc	00112$
                            825 ;	Peephole 300	removed redundant label 00131$
                    0016    826 	C$iconv.c$68$2$2 ==.
                            827 ;	C:/SDCC/GPSMon/dev/iconv.c:68: if( *p_ascii == '\0' )
                            828 ;	genPointerGet
                            829 ;	genFarPointerGet
   0CBD 8A 82               830 	mov	dpl,r2
   0CBF 8B 83               831 	mov	dph,r3
   0CC1 E0                  832 	movx	a,@dptr
                            833 ;	genIfx
   0CC2 F8                  834 	mov	r0,a
                            835 ;	Peephole 105	removed redundant mov
                            836 ;	genIfxJump
                            837 ;	Peephole 108.c	removed ljmp by inverse jump logic
   0CC3 60 52               838 	jz	00112$
                            839 ;	Peephole 300	removed redundant label 00132$
                    001E    840 	C$iconv.c$71$2$2 ==.
                            841 ;	C:/SDCC/GPSMon/dev/iconv.c:71: if( (*p_ascii < '0') || (*p_ascii > '9') ){
                            842 ;	genCmpLt
                            843 ;	genCmp
   0CC5 B8 30 00            844 	cjne	r0,#0x30,00133$
   0CC8                     845 00133$:
                            846 ;	genIfxJump
                            847 ;	Peephole 112.b	changed ljmp to sjmp
                            848 ;	Peephole 160.a	removed sjmp by inverse jump logic
   0CC8 40 05               849 	jc	00105$
                            850 ;	Peephole 300	removed redundant label 00134$
                            851 ;	genCmpGt
                            852 ;	genCmp
                            853 ;	genIfxJump
                            854 ;	Peephole 108.a	removed ljmp by inverse jump logic
                            855 ;	Peephole 132.b	optimized genCmpGt by inverse logic (acc differs)
   0CCA E8                  856 	mov	a,r0
   0CCB 24 C6               857 	add	a,#0xff - 0x39
   0CCD 50 0F               858 	jnc	00106$
                            859 ;	Peephole 300	removed redundant label 00135$
   0CCF                     860 00105$:
                    0028    861 	C$iconv.c$72$3$3 ==.
                            862 ;	C:/SDCC/GPSMon/dev/iconv.c:72: if( *p_ascii != ' ' )
                            863 ;	genPointerGet
                            864 ;	genFarPointerGet
   0CCF 8A 82               865 	mov	dpl,r2
   0CD1 8B 83               866 	mov	dph,r3
   0CD3 E0                  867 	movx	a,@dptr
   0CD4 F9                  868 	mov	r1,a
                            869 ;	genCmpEq
                            870 ;	gencjneshort
   0CD5 B9 20 02            871 	cjne	r1,#0x20,00136$
                            872 ;	Peephole 112.b	changed ljmp to sjmp
   0CD8 80 35               873 	sjmp	00107$
   0CDA                     874 00136$:
                    0033    875 	C$iconv.c$73$3$3 ==.
                            876 ;	C:/SDCC/GPSMon/dev/iconv.c:73: n = MAX_A2B_DIGITS;
                            877 ;	genAssign
   0CDA 7C 05               878 	mov	r4,#0x05
                            879 ;	Peephole 112.b	changed ljmp to sjmp
   0CDC 80 31               880 	sjmp	00107$
   0CDE                     881 00106$:
                    0037    882 	C$iconv.c$75$3$4 ==.
                            883 ;	C:/SDCC/GPSMon/dev/iconv.c:75: n++;
                            884 ;	genPlus
                            885 ;     genPlusIncr
   0CDE 0C                  886 	inc	r4
                    0038    887 	C$iconv.c$76$1$1 ==.
                            888 ;	C:/SDCC/GPSMon/dev/iconv.c:76: value *= 10;
                            889 ;	genAssign
   0CDF 75 41 0A            890 	mov	__mulint_PARM_2,#0x0A
   0CE2 E4                  891 	clr	a
   0CE3 F5 42               892 	mov	(__mulint_PARM_2 + 1),a
                            893 ;	genCall
   0CE5 8D 82               894 	mov	dpl,r5
   0CE7 8E 83               895 	mov	dph,r6
   0CE9 C0 02               896 	push	ar2
   0CEB C0 03               897 	push	ar3
   0CED C0 04               898 	push	ar4
   0CEF C0 07               899 	push	ar7
   0CF1 C0 00               900 	push	ar0
   0CF3 12 10 4B            901 	lcall	__mulint
   0CF6 AD 82               902 	mov	r5,dpl
   0CF8 AE 83               903 	mov	r6,dph
   0CFA D0 00               904 	pop	ar0
   0CFC D0 07               905 	pop	ar7
   0CFE D0 04               906 	pop	ar4
   0D00 D0 03               907 	pop	ar3
   0D02 D0 02               908 	pop	ar2
                    005D    909 	C$iconv.c$77$3$4 ==.
                            910 ;	C:/SDCC/GPSMon/dev/iconv.c:77: value += ( *p_ascii & ASCII_MASK );
                            911 ;	genAnd
   0D04 53 00 0F            912 	anl	ar0,#0x0F
                            913 ;	genCast
   0D07 79 00               914 	mov	r1,#0x00
                            915 ;	genPlus
                            916 ;	Peephole 236.g	used r0 instead of ar0
   0D09 E8                  917 	mov	a,r0
                            918 ;	Peephole 236.a	used r5 instead of ar5
   0D0A 2D                  919 	add	a,r5
   0D0B FD                  920 	mov	r5,a
                            921 ;	Peephole 236.g	used r1 instead of ar1
   0D0C E9                  922 	mov	a,r1
                            923 ;	Peephole 236.b	used r6 instead of ar6
   0D0D 3E                  924 	addc	a,r6
   0D0E FE                  925 	mov	r6,a
   0D0F                     926 00107$:
                    0068    927 	C$iconv.c$80$2$2 ==.
                            928 ;	C:/SDCC/GPSMon/dev/iconv.c:80: i++;
                            929 ;	genPlus
                            930 ;     genPlusIncr
   0D0F 0F                  931 	inc	r7
                    0069    932 	C$iconv.c$81$2$2 ==.
                            933 ;	C:/SDCC/GPSMon/dev/iconv.c:81: p_ascii++;
                            934 ;	genPlus
                            935 ;     genPlusIncr
   0D10 0A                  936 	inc	r2
                            937 ;	Peephole 112.b	changed ljmp to sjmp
                            938 ;	Peephole 243	avoided branch to sjmp
   0D11 BA 00 9F            939 	cjne	r2,#0x00,00110$
   0D14 0B                  940 	inc	r3
                            941 ;	Peephole 300	removed redundant label 00137$
   0D15 80 9C               942 	sjmp	00110$
   0D17                     943 00112$:
                    0070    944 	C$iconv.c$84$1$1 ==.
                            945 ;	C:/SDCC/GPSMon/dev/iconv.c:84: if( (*p_ascii == '\0') && (n > 0) ){
                            946 ;	genPointerGet
                            947 ;	genFarPointerGet
   0D17 8A 82               948 	mov	dpl,r2
   0D19 8B 83               949 	mov	dph,r3
   0D1B E0                  950 	movx	a,@dptr
                            951 ;	genIfxJump
                            952 ;	Peephole 108.b	removed ljmp by inverse jump logic
   0D1C 70 1C               953 	jnz	00114$
                            954 ;	Peephole 300	removed redundant label 00138$
                            955 ;	genIfx
   0D1E EC                  956 	mov	a,r4
                            957 ;	genIfxJump
                            958 ;	Peephole 108.c	removed ljmp by inverse jump logic
   0D1F 60 19               959 	jz	00114$
                            960 ;	Peephole 300	removed redundant label 00139$
                    007A    961 	C$iconv.c$85$2$5 ==.
                            962 ;	C:/SDCC/GPSMon/dev/iconv.c:85: *p_int = value;
                            963 ;	genAssign
   0D21 AA 18               964 	mov	r2,_AsciiToUnsigned_PARM_2
   0D23 AB 19               965 	mov	r3,(_AsciiToUnsigned_PARM_2 + 1)
   0D25 AC 1A               966 	mov	r4,(_AsciiToUnsigned_PARM_2 + 2)
                            967 ;	genPointerSet
                            968 ;	genGenPointerSet
   0D27 8A 82               969 	mov	dpl,r2
   0D29 8B 83               970 	mov	dph,r3
   0D2B 8C F0               971 	mov	b,r4
   0D2D ED                  972 	mov	a,r5
   0D2E 12 10 32            973 	lcall	__gptrput
   0D31 A3                  974 	inc	dptr
   0D32 EE                  975 	mov	a,r6
   0D33 12 10 32            976 	lcall	__gptrput
                    008F    977 	C$iconv.c$86$2$5 ==.
                            978 ;	C:/SDCC/GPSMon/dev/iconv.c:86: return( TRUE );
                            979 ;	genRet
   0D36 75 82 01            980 	mov	dpl,#0x01
                            981 ;	Peephole 112.b	changed ljmp to sjmp
                    0092    982 	C$iconv.c$88$1$1 ==.
                            983 ;	C:/SDCC/GPSMon/dev/iconv.c:88: return( FALSE );
                            984 ;	genRet
                    0092    985 	C$iconv.c$90$1$1 ==.
                    0092    986 	XG$AsciiToUnsigned$0$0 ==.
                            987 ;	Peephole 237.a	removed sjmp to ret
   0D39 22                  988 	ret
   0D3A                     989 00114$:
   0D3A 75 82 00            990 	mov	dpl,#0x00
                            991 ;	Peephole 300	removed redundant label 00117$
   0D3D 22                  992 	ret
                            993 ;------------------------------------------------------------
                            994 ;Allocation info for local variables in function 'UnsignedToAscii'
                            995 ;------------------------------------------------------------
                            996 ;pbuf                      Allocated with name '_UnsignedToAscii_PARM_2'
                            997 ;nbdigits                  Allocated with name '_UnsignedToAscii_PARM_3'
                            998 ;value                     Allocated to registers r2 r3 
                            999 ;ndx                       Allocated to registers r5 
                           1000 ;remainder                 Allocated to registers r1 r4 
                           1001 ;result                    Allocated to registers r7 r0 
                           1002 ;------------------------------------------------------------
                    0097   1003 	G$UnsignedToAscii$0$0 ==.
                    0097   1004 	C$iconv.c$99$1$1 ==.
                           1005 ;	C:/SDCC/GPSMon/dev/iconv.c:99: void UnsignedToAscii( uint value, 
                           1006 ;	-----------------------------------------
                           1007 ;	 function UnsignedToAscii
                           1008 ;	-----------------------------------------
   0D3E                    1009 _UnsignedToAscii:
                           1010 ;	genReceive
   0D3E AA 82              1011 	mov	r2,dpl
   0D40 AB 83              1012 	mov	r3,dph
                    009B   1013 	C$iconv.c$106$1$1 ==.
                           1014 ;	C:/SDCC/GPSMon/dev/iconv.c:106: ndx = nbdigits;
                           1015 ;	genAssign
                    009B   1016 	C$iconv.c$108$1$1 ==.
                           1017 ;	C:/SDCC/GPSMon/dev/iconv.c:108: *(pbuf+ndx--) = '\0';
                           1018 ;	genMinus
                           1019 ;	genMinusDec
   0D42 E5 1D              1020 	mov	a,_UnsignedToAscii_PARM_3
   0D44 14                 1021 	dec	a
   0D45 FD                 1022 	mov	r5,a
                           1023 ;	genPlus
   0D46 E5 1D              1024 	mov	a,_UnsignedToAscii_PARM_3
   0D48 25 1B              1025 	add	a,_UnsignedToAscii_PARM_2
   0D4A F5 82              1026 	mov	dpl,a
                           1027 ;	Peephole 181	changed mov to clr
   0D4C E4                 1028 	clr	a
   0D4D 35 1C              1029 	addc	a,(_UnsignedToAscii_PARM_2 + 1)
   0D4F F5 83              1030 	mov	dph,a
                           1031 ;	genPointerSet
                           1032 ;     genFarPointerSet
                           1033 ;	Peephole 181	changed mov to clr
   0D51 E4                 1034 	clr	a
   0D52 F0                 1035 	movx	@dptr,a
                           1036 ;	genAssign
   0D53 8D 06              1037 	mov	ar6,r5
   0D55                    1038 00103$:
                    00AE   1039 	C$iconv.c$109$1$1 ==.
                           1040 ;	C:/SDCC/GPSMon/dev/iconv.c:109: for( ; ndx>=0; ndx-- ){
                           1041 ;	genCmpLt
                           1042 ;	genCmp
   0D55 EE                 1043 	mov	a,r6
                           1044 ;	genIfxJump
                           1045 ;	Peephole 108.e	removed ljmp by inverse jump logic
   0D56 20 E7 63           1046 	jb	acc.7,00106$
                           1047 ;	Peephole 300	removed redundant label 00129$
                    00B2   1048 	C$iconv.c$110$1$1 ==.
                           1049 ;	C:/SDCC/GPSMon/dev/iconv.c:110: result = value / 10;
                           1050 ;	genAssign
   0D59 75 41 0A           1051 	mov	__divuint_PARM_2,#0x0A
   0D5C E4                 1052 	clr	a
   0D5D F5 42              1053 	mov	(__divuint_PARM_2 + 1),a
                           1054 ;	genCall
   0D5F 8A 82              1055 	mov	dpl,r2
   0D61 8B 83              1056 	mov	dph,r3
   0D63 C0 02              1057 	push	ar2
   0D65 C0 03              1058 	push	ar3
   0D67 C0 06              1059 	push	ar6
   0D69 12 0E CF           1060 	lcall	__divuint
   0D6C AF 82              1061 	mov	r7,dpl
   0D6E A8 83              1062 	mov	r0,dph
   0D70 D0 06              1063 	pop	ar6
   0D72 D0 03              1064 	pop	ar3
   0D74 D0 02              1065 	pop	ar2
                    00CF   1066 	C$iconv.c$111$1$1 ==.
                           1067 ;	C:/SDCC/GPSMon/dev/iconv.c:111: remainder = value - ( 10 * result );
                           1068 ;	genAssign
   0D76 75 41 0A           1069 	mov	__mulint_PARM_2,#0x0A
   0D79 E4                 1070 	clr	a
   0D7A F5 42              1071 	mov	(__mulint_PARM_2 + 1),a
                           1072 ;	genCall
   0D7C 8F 82              1073 	mov	dpl,r7
   0D7E 88 83              1074 	mov	dph,r0
   0D80 C0 02              1075 	push	ar2
   0D82 C0 03              1076 	push	ar3
   0D84 C0 06              1077 	push	ar6
   0D86 C0 07              1078 	push	ar7
   0D88 C0 00              1079 	push	ar0
   0D8A 12 10 4B           1080 	lcall	__mulint
   0D8D A9 82              1081 	mov	r1,dpl
   0D8F AC 83              1082 	mov	r4,dph
   0D91 D0 00              1083 	pop	ar0
   0D93 D0 07              1084 	pop	ar7
   0D95 D0 06              1085 	pop	ar6
   0D97 D0 03              1086 	pop	ar3
   0D99 D0 02              1087 	pop	ar2
                           1088 ;	genMinus
   0D9B EA                 1089 	mov	a,r2
   0D9C C3                 1090 	clr	c
                           1091 ;	Peephole 236.l	used r1 instead of ar1
   0D9D 99                 1092 	subb	a,r1
   0D9E F9                 1093 	mov	r1,a
   0D9F EB                 1094 	mov	a,r3
                           1095 ;	Peephole 236.l	used r4 instead of ar4
   0DA0 9C                 1096 	subb	a,r4
   0DA1 FC                 1097 	mov	r4,a
                    00FB   1098 	C$iconv.c$112$2$2 ==.
                           1099 ;	C:/SDCC/GPSMon/dev/iconv.c:112: value = result;
                           1100 ;	genAssign
   0DA2 8F 02              1101 	mov	ar2,r7
   0DA4 88 03              1102 	mov	ar3,r0
                    00FF   1103 	C$iconv.c$113$2$2 ==.
                           1104 ;	C:/SDCC/GPSMon/dev/iconv.c:113: *(pbuf+ndx) = ( remainder | '0' );
                           1105 ;	genPlus
                           1106 ;	Peephole 236.g	used r6 instead of ar6
   0DA6 EE                 1107 	mov	a,r6
   0DA7 25 1B              1108 	add	a,_UnsignedToAscii_PARM_2
   0DA9 F5 82              1109 	mov	dpl,a
                           1110 ;	Peephole 181	changed mov to clr
   0DAB E4                 1111 	clr	a
   0DAC 35 1C              1112 	addc	a,(_UnsignedToAscii_PARM_2 + 1)
   0DAE F5 83              1113 	mov	dph,a
                           1114 ;	genOr
   0DB0 43 01 30           1115 	orl	ar1,#0x30
                           1116 ;	genCast
                           1117 ;	genPointerSet
                           1118 ;     genFarPointerSet
   0DB3 E9                 1119 	mov	a,r1
   0DB4 F0                 1120 	movx	@dptr,a
                    010E   1121 	C$iconv.c$114$2$2 ==.
                           1122 ;	C:/SDCC/GPSMon/dev/iconv.c:114: if( value == 0 )
                           1123 ;	genIfx
   0DB5 EA                 1124 	mov	a,r2
   0DB6 4B                 1125 	orl	a,r3
                           1126 ;	genIfxJump
                           1127 ;	Peephole 108.c	removed ljmp by inverse jump logic
   0DB7 60 03              1128 	jz	00106$
                           1129 ;	Peephole 300	removed redundant label 00130$
                    0112   1130 	C$iconv.c$109$1$1 ==.
                           1131 ;	C:/SDCC/GPSMon/dev/iconv.c:109: for( ; ndx>=0; ndx-- ){
                           1132 ;	genMinus
                           1133 ;	genMinusDec
   0DB9 1E                 1134 	dec	r6
                           1135 ;	Peephole 112.b	changed ljmp to sjmp
   0DBA 80 99              1136 	sjmp	00103$
   0DBC                    1137 00106$:
                    0115   1138 	C$iconv.c$117$1$1 ==.
                           1139 ;	C:/SDCC/GPSMon/dev/iconv.c:117: if( value > 0 ){
                           1140 ;	genIfx
   0DBC EA                 1141 	mov	a,r2
   0DBD 4B                 1142 	orl	a,r3
                           1143 ;	genIfxJump
                           1144 ;	Peephole 108.c	removed ljmp by inverse jump logic
   0DBE 60 1B              1145 	jz	00108$
                           1146 ;	Peephole 300	removed redundant label 00131$
                    0119   1147 	C$iconv.c$119$2$3 ==.
                           1148 ;	C:/SDCC/GPSMon/dev/iconv.c:119: for( ndx=nbdigits-1; ndx>=0; --ndx )
                           1149 ;	genMinus
                           1150 ;	genMinusDec
   0DC0 E5 1D              1151 	mov	a,_UnsignedToAscii_PARM_3
   0DC2 14                 1152 	dec	a
   0DC3 FD                 1153 	mov	r5,a
                           1154 ;	genAssign
   0DC4 8D 02              1155 	mov	ar2,r5
   0DC6                    1156 00112$:
                           1157 ;	genCmpLt
                           1158 ;	genCmp
   0DC6 EA                 1159 	mov	a,r2
                           1160 ;	genIfxJump
                           1161 ;	Peephole 108.e	removed ljmp by inverse jump logic
   0DC7 20 E7 10           1162 	jb	acc.7,00115$
                           1163 ;	Peephole 300	removed redundant label 00132$
                    0123   1164 	C$iconv.c$120$2$3 ==.
                           1165 ;	C:/SDCC/GPSMon/dev/iconv.c:120: *(pbuf+ndx) = '?';
                           1166 ;	genPlus
                           1167 ;	Peephole 236.g	used r2 instead of ar2
   0DCA EA                 1168 	mov	a,r2
   0DCB 25 1B              1169 	add	a,_UnsignedToAscii_PARM_2
   0DCD F5 82              1170 	mov	dpl,a
                           1171 ;	Peephole 181	changed mov to clr
   0DCF E4                 1172 	clr	a
   0DD0 35 1C              1173 	addc	a,(_UnsignedToAscii_PARM_2 + 1)
   0DD2 F5 83              1174 	mov	dph,a
                           1175 ;	genPointerSet
                           1176 ;     genFarPointerSet
   0DD4 74 3F              1177 	mov	a,#0x3F
   0DD6 F0                 1178 	movx	@dptr,a
                    0130   1179 	C$iconv.c$119$2$3 ==.
                           1180 ;	C:/SDCC/GPSMon/dev/iconv.c:119: for( ndx=nbdigits-1; ndx>=0; --ndx )
                           1181 ;	genMinus
                           1182 ;	genMinusDec
   0DD7 1A                 1183 	dec	r2
                           1184 ;	Peephole 112.b	changed ljmp to sjmp
   0DD8 80 EC              1185 	sjmp	00112$
   0DDA                    1186 00115$:
                    0133   1187 	C$iconv.c$121$2$3 ==.
                           1188 ;	C:/SDCC/GPSMon/dev/iconv.c:121: return;
                           1189 ;	genRet
                           1190 ;	Peephole 112.b	changed ljmp to sjmp
                           1191 ;	Peephole 251.b	replaced sjmp to ret with ret
   0DDA 22                 1192 	ret
   0DDB                    1193 00108$:
                    0134   1194 	C$iconv.c$125$1$1 ==.
                           1195 ;	C:/SDCC/GPSMon/dev/iconv.c:125: ndx--;
                           1196 ;	genMinus
                           1197 ;	genMinusDec
   0DDB EE                 1198 	mov	a,r6
   0DDC 14                 1199 	dec	a
   0DDD FD                 1200 	mov	r5,a
                    0137   1201 	C$iconv.c$126$1$1 ==.
                           1202 ;	C:/SDCC/GPSMon/dev/iconv.c:126: while( ndx >= 0 )
                           1203 ;	genAssign
   0DDE 8D 02              1204 	mov	ar2,r5
   0DE0                    1205 00109$:
                           1206 ;	genCmpLt
                           1207 ;	genCmp
   0DE0 EA                 1208 	mov	a,r2
                           1209 ;	genIfxJump
                           1210 ;	Peephole 108.e	removed ljmp by inverse jump logic
   0DE1 20 E7 12           1211 	jb	acc.7,00116$
                           1212 ;	Peephole 300	removed redundant label 00133$
                    013D   1213 	C$iconv.c$127$1$1 ==.
                           1214 ;	C:/SDCC/GPSMon/dev/iconv.c:127: *(pbuf+ndx--) = ' ';
                           1215 ;	genAssign
   0DE4 8A 03              1216 	mov	ar3,r2
                           1217 ;	genMinus
                           1218 ;	genMinusDec
   0DE6 1A                 1219 	dec	r2
                           1220 ;	genPlus
                           1221 ;	Peephole 236.g	used r3 instead of ar3
   0DE7 EB                 1222 	mov	a,r3
   0DE8 25 1B              1223 	add	a,_UnsignedToAscii_PARM_2
   0DEA F5 82              1224 	mov	dpl,a
                           1225 ;	Peephole 181	changed mov to clr
   0DEC E4                 1226 	clr	a
   0DED 35 1C              1227 	addc	a,(_UnsignedToAscii_PARM_2 + 1)
   0DEF F5 83              1228 	mov	dph,a
                           1229 ;	genPointerSet
                           1230 ;     genFarPointerSet
   0DF1 74 20              1231 	mov	a,#0x20
   0DF3 F0                 1232 	movx	@dptr,a
                           1233 ;	Peephole 112.b	changed ljmp to sjmp
   0DF4 80 EA              1234 	sjmp	00109$
   0DF6                    1235 00116$:
                    014F   1236 	C$iconv.c$129$1$1 ==.
                    014F   1237 	XG$UnsignedToAscii$0$0 ==.
   0DF6 22                 1238 	ret
                           1239 	.area CSEG    (CODE)
                           1240 	.area CONST   (CODE)
                           1241 	.area XINIT   (CODE)
