/*! \file tsip.h \brief TSIP (Trimble Standard Interface Protocol) function library. */
//*****************************************************************************
//
// File Name    : 'tsip.h'
// Title        : TSIP (Trimble Standard Interface Protocol) function library
// Author       : Pascal Stang - Copyright (C) 2002
// Created      : 2002.08.27
// Revised      : 2002.08.27
// Version      : 0.1
// Target MCU   : Atmel AVR Series
// Editor Tabs  : 4
//
// NOTE: This code is currently below version 1.0, and therefore is considered
// to be lacking in some functionality or documentation, or may not be fully
// tested.  Nonetheless, you can expect most functions to work.
//
// This code is distributed under the GNU Public License
//      which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************

#ifndef TSIP_H
#define TSIP_H

#include "global.h"

// constants/macros/typdefs
// packet delimiters
static const uint8_t DLE=                 0x10
static const uint8_t ETX=                0x03
// packet types
// command packets
static const uint8_t TSIPTYPE_SET_IO_OPTIONS=0x35
// byte 0
#define POS_XYZ_ECEF        0   // outputs 0x42 and 0x83 packets
#define POS_LLA             1   // outputs 0x4A and 0x84 packets
#define POS_ALT             2   // outputs 0x4A/0x84 and 0x8F-17/0x8F-18
#define ALT_REF_MSL         3   // bit cleared = HAE Reference datum
#define POS_DBL_PRECISION   4   // bit cleared = single precision
#define SUPER_PACKETS       5   // 0x8F-17,0x8F-18,0x8F-20
// byte 1
#define VEL_ECEF            0   // outputs 0x43
#define VEL_ENU             1   // outputs 0x56
// byte 2
#define TIME_UTC            0   // 0/1 time format GPS/UTC
// byte 3
#define RAWDATA             0   // outputs 0x5A packets 
#define RAWDATA_FILTER      1   // 0/1 raw data unfiltered/filtered 
#define SIGNAL_DBHZ         3   // 0/1 signal strength in AMU/dBHz

// report packets
static const uint8_t TSIPTYPE_GPSTIME        0x41
static const uint8_t TSIPTYPE_POSFIX_XYZ_SP  0x42
static const uint8_t TSIPTYPE_VELFIX_XYZ     0x43
static const uint8_t TSIPTYPE_SATSIGLEVEL    0x47
static const uint8_t TSIPTYPE_GPSSYSMESSAGE  0x48
static const uint8_t TSIPTYPE_POSFIX_LLA_SP  0x4A
static const uint8_t TSIPTYPE_VELFIX_ENU     0x56
static const uint8_t TSIPTYPE_SATTRACKSTAT   0x5C
static const uint8_t TSIPTYPE_RAWDATA        0x5A
static const uint8_t TSIPTYPE_GPSSUBCODE     0x6F
static const uint8_t TSIPTYPE_POSFIX_XYZ_DP  0x83
static const uint8_t TSIPTYPE_POSFIX_LLA_DP  0x84


// functions
void tsipInit(void (*txbytefunc)(unsigned char c));
void tsipSendPacket(uint8_t tsipType, uint8_t dataLength, uint8_t* data);
uint8_t tsipProcess(cBuffer* rxBuffer);
void tsipGpsDataPrint(void);

// packet processing functions
void tsipProcessGPSTIME(uint8_t* packet);
void tsipProcessPOSFIX_XYZ_SP(uint8_t* packet);
void tsipProcessVELFIX_XYZ(uint8_t* packet);
void tsipProcessPOSFIX_LLA_SP(uint8_t* packet);
void tsipProcessVELFIX_ENU(uint8_t* packet);

#endif