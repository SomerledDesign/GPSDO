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
 * 7.12a	15 jun 99  	matched 7.12 manual									pvwl
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
 * defined in T_PARSER.C and T_FORMAT.C
 *
 * *************************************************************************
 *
 */

/*******************        PROTOYPES            *****************/

/* functions to add a byte from the receiver and "unstuffs" it */
void tsip_input_proc (
	TSIPPKT *rpt, short newbyte);

/**/
/*  prototypes for report parsing primitives */
short rpt_0x3D (TSIPPKT *rpt,
	unsigned char *tx_baud_index,
	unsigned char *rx_baud_index,
	unsigned char *char_format_index,
	unsigned char *stop_bits,
	unsigned char *tx_mode_index,
	unsigned char *rx_mode_index);
short rpt_0x40 (TSIPPKT *rpt,
	unsigned char *sv_prn,
	short *week_num,
	float *t_zc,
	float *eccentricity,
	float *t_oa,
	float *i_0,
	float *OMEGA_dot,
	float *sqrt_A,
	float *OMEGA_0,
	float *omega,
	float *M_0);
short rpt_0x41 (TSIPPKT *rpt,
	float *time_of_week,
	float *UTC_offset,
	short *week_num);
short rpt_0x42 (TSIPPKT *rpt,
	float ECEF_pos[3],
	float *time_of_fix);
short rpt_0x43 (TSIPPKT *rpt,
	float ECEF_vel[3],
	float *freq_offset,
	float *time_of_fix);
short rpt_0x45 (TSIPPKT *rpt,
	unsigned char *major_nav_version,
	unsigned char *minor_nav_version,
	unsigned char *nav_day,
	unsigned char *nav_month,
	unsigned char *nav_year,
	unsigned char *major_dsp_version,
	unsigned char *minor_dsp_version,
	unsigned char *dsp_day,
	unsigned char *dsp_month,
	unsigned char *dsp_year);
short rpt_0x46 (TSIPPKT *rpt,
	unsigned char *status_code,
	unsigned char *error_code);
short rpt_0x47 (TSIPPKT *rpt,
	unsigned char *nsvs,
	unsigned char *sv_prn,
	float *snr);
short rpt_0x48 (TSIPPKT *rpt,
	unsigned char *message);
short rpt_0x49 (TSIPPKT *rpt,
	unsigned char *sv_health);
short rpt_0x4A (TSIPPKT *rpt,
	float *lat,
	float *lon,
	float *alt,
	float *clock_bias,
	float *time_of_fix);
short rpt_0x4A_2 (TSIPPKT *rpt,
	float *alt,
	float *dummy,
	unsigned char *alt_flag);
short rpt_0x4B (TSIPPKT *rpt,
	unsigned char *machine_id,
	unsigned char *status_1,
	unsigned char *status_2);
short rpt_0x4C (TSIPPKT *rpt,
	unsigned char *dyn_code,
	float *el_mask,
	float *snr_mask,
	float *dop_mask,
	float *dop_switch);
short rpt_0x4D (TSIPPKT *rpt,
	float *osc_offset);
short rpt_0x4E (TSIPPKT *rpt,
	unsigned char *response);
short rpt_0x4F (TSIPPKT *rpt,
	double *a0,
	float *a1,
	float *time_of_data,
	short *dt_ls,
	short *wn_t,
	short *wn_lsf,
	short *dn,
	short *dt_lsf);
short rpt_0x53 (TSIPPKT *rpt,
	float *a2d);
short rpt_0x54 (TSIPPKT *rpt,
	float *clock_bias,
	float *freq_offset,
	float *time_of_fix);
short rpt_0x55 (TSIPPKT *rpt,
	unsigned char *pos_code,
	unsigned char *vel_code,
	unsigned char *time_code,
	unsigned char *aux_code);
short rpt_0x56 (TSIPPKT *rpt,
	float vel_ENU[3],
	float *freq_offset,
	float *time_of_fix);
short rpt_0x57 (TSIPPKT *rpt,
	unsigned char *source_code,
	unsigned char *diag_code,
	short *week_num,
	float *time_of_fix);
short rpt_0x58 (TSIPPKT *rpt,
	unsigned char *op_code,
	unsigned char *data_type,
	unsigned char *sv_prn,
	unsigned char *data_length,
	unsigned char *data_packet);
short rpt_0x59 (TSIPPKT *rpt,
	unsigned char *code_type,
	unsigned char status_code[32]);
short rpt_0x5A (TSIPPKT *rpt,
	unsigned char *sv_prn,
	float *sample_length,
	float *signal_level,
	float *code_phase,
	float *Doppler,
	double *time_of_fix);
short rpt_0x5B (TSIPPKT *rpt,
	unsigned char *sv_prn,
	unsigned char *sv_health,
	unsigned char *sv_iode,
	unsigned char *fit_interval_flag,
	float *time_of_collection,
	float *time_of_eph,
	float *sv_accy);
short rpt_0x5C (TSIPPKT *rpt,
	unsigned char *sv_prn,
	unsigned char *slot,
	unsigned char *chan,
	unsigned char *acq_flag,
	unsigned char *eph_flag,
	float *signal_level,
	float *time_of_last_msmt,
	float *elev,
	float *azim,
	unsigned char *old_msmt_flag,
	unsigned char *integer_msec_flag,
	unsigned char *bad_data_flag,
	unsigned char *data_collect_flag);
short rpt_0x5E (TSIPPKT *rpt,
	unsigned char *num_reused_msmts,
	unsigned char *diff_Doppler_unavailable,
	unsigned char *fix_still_converging,
	unsigned char *num_old_msmts);
short rpt_0x6D (TSIPPKT *rpt,
	unsigned char *manual_mode,
	unsigned char *nsvs,
	unsigned char *ndim,
	unsigned char sv_prn[],
	float *pdop,
	float *hdop,
	float *vdop,
	float *tdop);
short rpt_0x6E (TSIPPKT *rpt,
	unsigned char *subcode,
	unsigned char *enable,
	unsigned char *interval);
short rpt_0x6F01 (TSIPPKT *rpt,
	struct cph1_msg_struct *cph);
short rpt_0x70	(TSIPPKT *rpt,
	unsigned char *dyn_switch,
	unsigned char *static_switch,
	unsigned char *alt_switch,
	unsigned char *extra) ;
short rpt_0x72 (TSIPPKT *rpt,
	short *pf,
	TSIP_POS_FILT_PARMS *params);
short rpt_0x74 (TSIPPKT *rpt,
	float *alt_filter_parm);
short rpt_0x78 (TSIPPKT *rpt,
	short *maxage);
short rpt_0x7B (TSIPPKT *rpt,
	unsigned char *subcode,
	unsigned char *interval,
	unsigned long *nmeamask);
short rpt_0x82 (TSIPPKT *rpt,
	unsigned char *diff_mode);
short rpt_0x83 (TSIPPKT *rpt,
	double ECEF_pos[3],
	double *clock_bias,
	float *time_of_fix);
short rpt_0x84 (TSIPPKT *rpt,
	double *lat,
	double *lon,
	double *alt,
	double *clock_bias,
	float *time_of_fix);
short rpt_0x85 (TSIPPKT *rpt,
	unsigned char *sv_prn,
	unsigned char *summary_status,
	unsigned char *station_health,
	unsigned char *SV_UDRE_parm,
	unsigned char *iode1,
	unsigned char *iode2,
	float *z_cnt_tow,
	float *range_corr,
	float *range_rate_corr,
	float *delta_range_corr);
short rpt_0x8F03 (TSIPPKT *rpt,
	unsigned char *tx_baud_index,
	unsigned char *rx_baud_index,
	unsigned char *char_format_index,
	unsigned char *stop_bits,
	unsigned char *tx_mode_index,
	unsigned char *rx_mode_index);
short rpt_0x8F14 (TSIPPKT *rpt,
	short *datum_idx,
	double datum_coeffs[5]);
short rpt_0x8F15 (TSIPPKT *rpt,
	short *datum_idx,
	double datum_coeffs[5]);
short rpt_0x8F17 (TSIPPKT *rpt,
	unsigned char *UTM_grid_letter,
	short *UTM_grid_number,
	float *UTM_northing_value,
	float *UTM_easting_value,
	float *UTM_altitude,
	float *clock_bias,
	float *time_of_fix);
short rpt_0x8F18 (TSIPPKT *rpt,
	unsigned char *UTM_grid_letter,
	short *UTM_grid_number,
	double *UTM_northing_value,
	double *UTM_easting_value,
	double *UTM_altitude,
	double *clock_bias,
	float *time_of_fix);
short rpt_0x8F19 (TSIPPKT *rpt,
	short *UTM_enabled);
short rpt_0x8F20 (TSIPPKT *rpt,
	unsigned char *subpacket_id,
	unsigned char *info,
	double *lat,
	double *lon,
	double *alt,
	double vel_enu[],
	double *time_of_fix,
	short *week_num,
	unsigned char *nsvs, unsigned char sv_prn[],
	short sv_IODC[],
	short *datum_index);
short rpt_0x8F23 (TSIPPKT *rpt,
		unsigned char *subpacket_id,
      unsigned long *TOW,
      unsigned short *week,
      unsigned char *UTC_Offset,
      unsigned char *fix_type,
      long *lat,
		unsigned long *lon,
      long *alt,
      short *east,
      short *north,
      short *up);
short rpt_0x8F24 (TSIPPKT *rpt,
	short *shutdown_in,
	short *shutdown_len);
short rpt_0x8F25 (TSIPPKT *rpt,
	short *mode_mask);
short rpt_0x8F26(TSIPPKT *rpt,
	unsigned long *see_write);
short rpt_0x8F27 (TSIPPKT *rpt,
	unsigned long *ST_period,
	short 		  *ST_awake_time);
short rpt_0x8F40 (TSIPPKT *rpt,
   	unsigned char *Flags,
      unsigned char *HeartBeatSentence,
      short *TopOfHourOffset,
      short *Frequency,
      char *VehicleID);
short rpt_0xBB	(TSIPPKT *rpt,
	TSIP_RCVR_CFG *TsipBB) ;
short rpt_0xBC   (TSIPPKT *rpt,
	unsigned char *port_num,
	unsigned char *in_baud,
	unsigned char *out_baud,
	unsigned char *data_bits,
	unsigned char *parity,
	unsigned char *stop_bits,
	unsigned char *flow_control,
	unsigned char *protocols_in,
	unsigned char *protocols_out,
	unsigned char *reserved);
