/*
 * ICP_scheduler_client.c
 *
 *  Created on: 2012/11/27
 *      Author: RyzeVia
 */
//#define DEBUG_ENABLE
//#define DEBUG_LEVEL 60


#include "libicp.h"

void ICP_timestamp_init(ICP_info_t *info) {
	ICP_PRE_PROC(__FUNCTION__);

	clock_gettime(CLOCK_REALTIME, &(info->tstart_stamp));
	clock_gettime(CLOCK_REALTIME, &(info->tcp_stamp));

	ICP_POST_PROC(__FUNCTION__);
}

void ICP_timestamp_start_cp(ICP_info_t *info) {
	ICP_PRE_PROC(__FUNCTION__);

	clock_gettime(CLOCK_REALTIME, &(info->tcalc_stamp));
	tssub(&(info->tcalc_stamp), &(info->tcp_stamp), &(info->tcalc_value));

	DEBUGF(DEBUG_LEVEL_TRIVIAL, "info->tcalc_value = %lf\n", ts2dbl(&(info->tcalc_value)));

	ICP_POST_PROC(__FUNCTION__);
}

void ICP_timestamp_finish_cp(ICP_info_t *info) {
	ICP_PRE_PROC(__FUNCTION__);

	clock_gettime(CLOCK_REALTIME, &(info->tcp_stamp));
	tssub(&(info->tcp_stamp), &(info->tcalc_stamp), &(info->tcp_value));

	DEBUGF(DEBUG_LEVEL_TRIVIAL, "info->tcp_value = %lf\n", ts2dbl(&(info->tcp_value)));

	ICP_POST_PROC(__FUNCTION__);
}

static int SICP_cond_overdiff(struct timespec *a, struct timespec *b, struct timespec *diff) {
	struct timespec eps;
	tssub(a, b, &eps);
	tsabs(&eps, &eps);

	DEBUGF(DEBUG_LEVEL_TRIVIAL, "%d:%ld, %d:%ld.... eps/%d:%ld\n", TSPRINTF(a), TSPRINTF(b), TSPRINTF(&eps));

	return (tscmp(&eps, diff, >));
}

static int SICP_cond_overrate(struct timespec *a, struct timespec *b, double *rate) {
	struct timespec eps;
	double d_eps, d_a;
	tssub(a, b, &eps);
	tsabs(&eps, &eps);
	d_eps = ts2dbl(&eps);
	d_a = ts2dbl(a);

	DEBUGF(DEBUG_LEVEL_TRIVIAL, "%d:%ld, %d:%ld.... eps/%d:%ld\n", TSPRINTF(a), TSPRINTF(b), TSPRINTF(&eps));

	return ((d_eps / d_a) > *rate);
}


/*// can not use this macro because func( is not a token.
  // For a##b, a must be a token, b must be a token, and also a##b must be a token.
  // it works on gcc but got a error on -Wl.
#define IF_SICP_CHK_RECALC(term, cterm, method, cmethod) \
	if((info->recalc_mode && ICP_RENEW_##cterm##_##cmethod) \
	 && (SICP_cond_over##method##( \
			 &(info->t##term##_current), \
			 &(info->t##term##_value), \
			 &(info->recalc_eps_##method))))
*/
static int SICP_condition_iterrenewal(ICP_info_t * info) {
	if((info->recalc_mode && ICP_RENEW_CALC_DIFF) \
		 && (SICP_cond_overdiff(&(info->tcalc_current), \
				 &(info->tcalc_value), \
				 &(info->recalc_eps_diff)))){
		info->tcalc_current = info->tcalc_value;
		return 1;
	}
	if((info->recalc_mode && ICP_RENEW_CALC_RATE) \
		 && (SICP_cond_overrate(&(info->tcalc_current), \
				 &(info->tcalc_value), \
				 &(info->recalc_eps_rate)))){
		info->tcalc_current = info->tcalc_value;
		return 1;
	}
	if((info->recalc_mode && ICP_RENEW_CP_DIFF) \
		&& (SICP_cond_overdiff(&(info->tcp_current), \
				 &(info->tcp_value), \
				 &(info->recalc_eps_diff)))){
		info->tcp_current = info->tcp_value;
		return 1;
	}
	if((info->recalc_mode && ICP_RENEW_CP_RATE) \
		 && (SICP_cond_overrate(&(info->tcp_current), \
				 &(info->tcp_value), \
				 &(info->recalc_eps_rate)))){
		info->tcp_current = info->tcp_value;
		return 1;
	}
	return 0;
}
/*
#undef IF_SICP_CHK_RECALC(term, cterm, method, cmethod)
*/
int ICP_send_elapsed(ICP_info_t *info, int iter_id) {
	int res = 0;
	ICP_PRE_PROC(__FUNCTION__);

	if (SICP_condition_iterrenewal(info)) {
		res = 1;
		ICP_sendhdl_cli_renew_iter(info);
	}

	ICP_POST_PROC(__FUNCTION__);
	return res;
}

void ICP_send_processjoin(ICP_info_t *info) {
	ICP_sendhdl_cli_process_join(info);
}

static int SICP_is_ckpt_iteration(ICP_info_t *info) {
	int bool = 0;

	if(info->iter_current < info->iter_offset) {
		bool = 0;
	}
	else if(((info->iter_current - info->iter_offset) % info->iter_stride) == 0) {
		bool = 1;
	}
	return bool;
}

static int SICP_is_restart_iteration(ICP_info_t *info) {
	int bool = 0;

	if(info->restart == 1){
		bool = 1;
		info->restart = 0;
	}


	return bool;
}

int ICP_checkpoint(ICP_info_t *info) {
	int bool = 0;

	ICP_PRE_PROC(__FUNCTION__);

	ICP_pftp_cli_preckpt(info);

	ICP_timestamp_start_cp(info);
	if (SICP_is_ckpt_iteration(info)) {
		ICP_write_data(info);
		bool = 1;
	}
	ICP_timestamp_finish_cp(info);

	ICP_pftp_cli_postckpt(info);

	ICP_POST_PROC(__FUNCTION__);
	return bool;
}

int ICP_restart(ICP_info_t *info){
	int bool = 0;

	ICP_PRE_PROC(__FUNCTION__);

	if (SICP_is_restart_iteration(info)) {
		ICP_read_data(info);
		bool = 1;
	}

	ICP_POST_PROC(__FUNCTION__);

	return bool;
}



