/*
 ***************************************************************************
 *	Trimble part number:  40536
 ***************************************************************************
 *
 * Trimble Navigation, Ltd.
 * OEM Products Development Group
 * P.O. Box 3642
 * 645 North Mary Avenue
 * Sunnyvale, California 94088-3642
 *
 * Corporate Headquarter:
 *    Telephone:  (408) 481-8000
 *    Fax:        (408) 481-6005
 *
 * Technical Support Center:
 *    Telephone:  (800) 767-4822	(U.S. and Canada)
 *                (408) 481-6940    (outside U.S. and Canada)
 *    Fax:        (408) 481-6020
 *    BBS:        (408) 481-7800
 *    e-mail:     trimble_support@trimble.com
 *
 * *************************************************************************
 *
 * Vers	Date		   Changes										 			Author
 * ----	---------   ----------------------------------------	   ----------
 * v1.40
 * 7.12 15 jun 99   	matched 7.12 manual									pvwl
 *	0.99d	9/15/99		split from TSIP_IFC.C, added features for
 *							Lassen LP, version 7.82								pah
 * *************************************************************************
 *
 * This header file contains definitions for general TSIP structures and
 * prototypes for general functions.
 *
 * This source code is supplied without warranty and is intended only as
 * sample source code for exercising the TSIP interface.  We do appreciate
 * comments and try to support the software as much as possible.
 *
 * Developers of new applications are encouraged to use the functions
 * defined in T_PARSER.C, and T_FORMAT.C
 *
 * *************************************************************************
 *
 */

/*******************        PROTOYPES            *****************/

/*
 * This routine sends a command to the receiver, applying DLE control bytes.
 * It calls a function sendb() that must be supplied by the user.
 */

 void send_cmd
	(TSIPPKT *cmd, short sendb(unsigned char bb));

/**/
/* prototypes for command-encode primitives with suffix convention:  */
/* c = clear, s = set, q = query, e = enable, d = disable            */
void cmd_0x1Dc (TSIPPKT *cmd);
void cmd_0x1Ds (TSIPPKT *cmd,
	float offset);
void cmd_0x1E  (TSIPPKT *cmd,
	unsigned char reset_type);
void cmd_0x1F  (TSIPPKT *cmd);
void cmd_0x20  (TSIPPKT *cmd, unsigned char sv_prn);
void cmd_0x21  (TSIPPKT *cmd);
void cmd_0x22  (TSIPPKT *cmd,
	unsigned char nav_code);
void cmd_0x23  (TSIPPKT *cmd,
	float pos_ECEF[3]);
void cmd_0x24  (TSIPPKT *cmd);
void cmd_0x25  (TSIPPKT *cmd);
void cmd_0x26  (TSIPPKT *cmd);
void cmd_0x27  (TSIPPKT *cmd);
void cmd_0x28  (TSIPPKT *cmd);
void cmd_0x29  (TSIPPKT *cmd);
void cmd_0x2As  (TSIPPKT *cmd,
	float alt);
void cmd_0x2Ad  (TSIPPKT *cmd);
void cmd_0x2Aq  (TSIPPKT *cmd);
void cmd_0x2B  (TSIPPKT *cmd,
	float lat,
	float lon,
	float alt);
void cmd_0x2Cq (TSIPPKT *cmd);
void cmd_0x2Cs (TSIPPKT *cmd,
	unsigned char dyn_code,
	float elev_mask,
	float snr,
	float dop_mask,
	float dop_switch);
void cmd_0x2D  (TSIPPKT *cmd);
void cmd_0x2E  (TSIPPKT *cmd,
	float time_of_week,
	short week_num);
void cmd_0x2F  (TSIPPKT *cmd);
void cmd_0x31  (TSIPPKT *cmd,
	float ECEF_pos[3]);
void cmd_0x32  (TSIPPKT *cmd, 
	float lat,
	float lon,
	float alt);
void cmd_0x35q (TSIPPKT *cmd);
void cmd_0x35s (TSIPPKT *cmd, 
	unsigned char pos_code,
	unsigned char vel_code,
	unsigned char time_code,
	unsigned char opts_code);
void cmd_0x37  (TSIPPKT *cmd);
void cmd_0x38q (TSIPPKT *cmd, 
	unsigned char data_type,
	unsigned char sv_prn);
void cmd_0x38s (TSIPPKT *cmd, 
	unsigned char data_type,
	unsigned char sv_prn,
	unsigned char data_length,
	unsigned char *databuf);
void cmd_0x39  (TSIPPKT *cmd,
	unsigned char op_code,
	unsigned char sv_prn);
void cmd_0x3A  (TSIPPKT *cmd,
	unsigned char sv_prn);
void cmd_0x3B  (TSIPPKT *cmd, 
	unsigned char sv_prn);
void cmd_0x3C  (TSIPPKT *cmd, 
	unsigned char sv_prn);
void cmd_0x3Dq (TSIPPKT *cmd);
void cmd_0x3Ds (TSIPPKT *cmd, 
	unsigned char baud_out,
	unsigned char baud_inp,
	unsigned char char_code,
	unsigned char stopbitcode,
	unsigned char output_mode,
	unsigned char input_mode);
void cmd_0x3E  (TSIPPKT *cmd);
void cmd_0x62q (TSIPPKT *cmd);
void cmd_0x62s (TSIPPKT *cmd,
	unsigned char dgps_mode);
void cmd_0x65  (TSIPPKT *cmd,
	unsigned char sv_prn);
void cmd_0x6Eq (TSIPPKT *cmd,
	unsigned char subcode);
void cmd_0x6Ed (TSIPPKT *cmd,
	unsigned char subcode);
void cmd_0x6Es (TSIPPKT *cmd,
	unsigned char subcode,
	unsigned char interval);
void cmd_0x70q  (TSIPPKT *cmd);
void cmd_0x70s  (TSIPPKT *cmd,
	unsigned char dyn_switch,
	unsigned char static_switch,
	unsigned char alt_switch,
	unsigned char extra) ;
void cmd_0x71q (TSIPPKT *cmd);
void cmd_0x71s (TSIPPKT *cmd,
	short pf,
	TSIP_POS_FILT_PARMS *params);
void cmd_0x73q (TSIPPKT *cmd);
void cmd_0x73c (TSIPPKT *cmd);
void cmd_0x73d (TSIPPKT *cmd);
void cmd_0x73s (TSIPPKT *cmd,
	float alt_filter_parm);
void cmd_0x77q (TSIPPKT *cmd);
void cmd_0x77s (TSIPPKT *cmd,
	short dgps_max_age);
void cmd_0x7A_0s (TSIPPKT *cmd,
	unsigned char nmea_interval,
	unsigned long nmea_mask);
void cmd_0x7A_0q (TSIPPKT *cmd) ;
void cmd_0x8E03q (TSIPPKT *cmd);
void cmd_0x8E03s (TSIPPKT *cmd,
	unsigned char baud_out,
	unsigned char baud_inp,
	unsigned char char_code,
	unsigned char stopbitcode,
	unsigned char output_mode,
	unsigned char input_mode);
void cmd_0x8E15q (TSIPPKT *cmd);
void cmd_0x8E15s (TSIPPKT *cmd, unsigned char datum_index);
void cmd_0x8E15s_2 (TSIPPKT *cmd, double datum_parms[5]);
void cmd_0x8E19q (TSIPPKT *cmd);
void cmd_0x8E19d (TSIPPKT *cmd);
void cmd_0x8E19e (TSIPPKT *cmd);
void cmd_0x8E20q (TSIPPKT *cmd);
void cmd_0x8E20d (TSIPPKT *cmd);
void cmd_0x8E20e (TSIPPKT *cmd);
void cmd_0x8E24q (TSIPPKT *cmd);
void cmd_0x8E24s (TSIPPKT *cmd,
	short shutdown_in,
	short shutdown_len);
void cmd_0x8E25q (TSIPPKT *cmd);
void cmd_0x8E25s  (TSIPPKT *cmd,
	short mode_mask);
void cmd_0x8E26s (TSIPPKT *cmd);
void cmd_0x8E27q (TSIPPKT *cmd);
void cmd_0x8E27s  (TSIPPKT *cmd,
	unsigned long ST_period,
	short 		  ST_awake_time);
void cmd_0x8E40q (TSIPPKT *cmd);
void cmd_0x8E40s (TSIPPKT *cmd,
	unsigned char Flags,
	unsigned char HeartBeatSentence,
   short TopOfHourOffset,
	short Frequency,
   char VehicleID[4]);
void cmd_0x8E  (TSIPPKT *cmd,
	unsigned char hexbyte[],
	unsigned char hexnum);
void cmd_0xBBq (TSIPPKT *cmd,
	unsigned char subcode) ;
void cmd_0xBBs (TSIPPKT *cmd,
	TSIP_RCVR_CFG *TsipxBB) ;
void cmd_0xBCs (TSIPPKT *cmd,
	unsigned char port_num,
	unsigned char in_baud,
	unsigned char out_baud,
	unsigned char data_bits,
	unsigned char parity,
	unsigned char stop_bits,
	unsigned char flow_control,
	unsigned char bReserved1,
	unsigned char bReserved2,
	unsigned char reserved);
void cmd_0xBCq (TSIPPKT *cmd, unsigned char port_num);
void cmd_0xxx (TSIPPKT *cmd,
	unsigned char hexcode, unsigned char hexbyte[], unsigned char hexnum);
