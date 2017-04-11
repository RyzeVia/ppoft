/*
 * ICP_handler.c
 *
 *  Created on: 2013/01/16
 *      Author: RyzeVia
 */
//#define DEBUG_ENABLE
//#define DEBUG_LEVEL 60

#include "libicp.h"

void ICP_sendhdl_cli_renew_iter(ICP_info_t *info){
	char buf[MAX_ICP_PAYLOAD];

	ICP_PRE_PROC(__FUNCTION__);
	snprintf(buf, MAX_ICP_PAYLOAD,
			"%d,%d,%ld,%d,%ld",
			info->iter_current,
			TSPRINTF(&(info->tcalc_value)),
			TSPRINTF(&(info->tcp_value)));
	ICP_publish_to_srv(info, "ICP_RENEW_ITER", buf);
	ICP_POST_PROC(__FUNCTION__);

}

void ICP_sendhdl_cli_process_join(ICP_info_t *info){
	char buf[MAX_ICP_PAYLOAD];
	char hostname[MAX_ICP_HOSTNAME];

	ICP_PRE_PROC(__FUNCTION__);
	gethostname(hostname, MAX_ICP_HOSTNAME);
	snprintf(buf, MAX_ICP_PAYLOAD,
			"%s", hostname);
	ICP_publish_to_srv(info, "ICP_PROCESS_JOIN", buf);
	ICP_POST_PROC(__FUNCTION__);

}

void ICP_sendhdl_srv_optimized_iter(ICP_info_t *info, int iter_offset, int iter_stride){
	char buf[MAX_ICP_PAYLOAD];
	ICP_PRE_PROC(__FUNCTION__);
	snprintf(buf, MAX_ICP_PAYLOAD,
			"%d,%d",
			iter_offset,
			iter_stride);
	ICP_publish_to_cli(info, "ICP_OPTIMIZED_ITER", buf);

	ICP_POST_PROC(__FUNCTION__);
}

void ICP_sendhdl_cli_comm_finalize(ICP_info_t *info){
	char buf[MAX_ICP_PAYLOAD];
	ICP_PRE_PROC(__FUNCTION__);
	buf[0] = 0;
	ICP_publish_to_srv(info, "ICP_COMM_FINALIZE", buf);
	ICP_POST_PROC(__FUNCTION__);
}

void ICP_sendhdl_srv_comm_finalize(ICP_info_t *info){
	char buf[MAX_ICP_PAYLOAD];
	ICP_PRE_PROC(__FUNCTION__);
	buf[0] = 0;
	ICP_publish_to_cli(info, "ICP_COMM_FINALIZE", buf);
	ICP_POST_PROC(__FUNCTION__);
}

int ICP_recvhdl_srv_renew_iter(ICP_info_t *info, char* payload){
	struct timespec ts_cp = {0,0}, ts_calc = {0,0};
	int iter_id;
	int new_iter_stride;
	int new_iter_offset;
	ICP_PRE_PROC(__FUNCTION__);

	DEBUGF(50, "PAYLOAD=%s\n", payload);

	sscanf(payload,
			"%d,%d,%ld,%d,%ld",
			&iter_id,
			TSSCANF(&ts_calc),
			TSSCANF(&ts_cp));

	DEBUGF(50, "ts_cp %d, %ld\n", TSPRINTF(&ts_cp));

	ts_cp.tv_nsec = ts_cp.tv_nsec/1000;

	ICP_opt_get_iter(info->sinfo->fr_current, iter_id, &ts_calc, &ts_cp, &new_iter_offset, &new_iter_stride);
	ICP_sendhdl_srv_optimized_iter(info, new_iter_offset, new_iter_stride);

	ICP_POST_PROC(__FUNCTION__);
	return ICP_HDL_SUCCESS;

}

int ICP_recvhdl_srv_process_join(ICP_info_t *info, char* payload){
	char hostname[MAX_ICP_HOSTNAME];
	ICP_PRE_PROC(__FUNCTION__);

	sscanf(payload,
			"%s", hostname);

	ICP_pftp_addproc(info->sinfo, hostname);

	ICP_POST_PROC(__FUNCTION__);
	return ICP_HDL_SUCCESS;

}


/* This function used with polling method.
 * Then, as soon as client got #iteration change message, it can apply.*/
int ICP_recvhdl_cli_optimized_iter(ICP_info_t *info, char* payload){
	ICP_PRE_PROC(__FUNCTION__);
	sscanf(payload,
			"%d,%d",
			&(info->iter_offset),
			&(info->iter_stride));

	ICP_POST_PROC(__FUNCTION__);
	return ICP_HDL_SUCCESS;

}

int ICP_recvhdl_srvcli_comm_finalize(){
	ICP_PRE_PROC(__FUNCTION__);
	ICP_POST_PROC(__FUNCTION__);
	return ICP_HDL_INVALID;
}

#define IF_SICP_CHK_SIG(sig,sig_p) if(strncmp(sig, sig_p, strlen(sig_p)) == 0)
int ICP_handle_clientmsg(ICP_info_t *info, char* sig, char* payload){
	int status = ICP_HDL_SUCCESS;
	ICP_PRE_PROC(__FUNCTION__);

	IF_SICP_CHK_SIG(sig, "ICP_RENEW_ITER"){
		status = ICP_recvhdl_srv_renew_iter(info, payload);
	}
	else IF_SICP_CHK_SIG(sig, "ICP_PROCESS_JOIN"){
		status = ICP_recvhdl_srv_process_join(info, payload);
	}
	else IF_SICP_CHK_SIG(sig, "ICP_COMM_FINALIZE"){
		status = ICP_recvhdl_srvcli_comm_finalize();
	}
	else{
		status = ICP_HDL_FAILURE;
		ERRORF("Unexpected SIGNAL from SERVER.\n");
		ERROR_EXIT();
	}

	ICP_POST_PROC(__FUNCTION__);
	return status;
}

int ICP_handle_servermsg(ICP_info_t *info, char* sig, char* payload){
	int status = ICP_HDL_SUCCESS;
	ICP_PRE_PROC(__FUNCTION__);

	IF_SICP_CHK_SIG(sig, "ICP_OPTIMIZED_ITER"){
		status = ICP_recvhdl_cli_optimized_iter(info, payload);
	}
	else IF_SICP_CHK_SIG(sig, "ICP_COMM_FINALIZE"){
		status = ICP_recvhdl_srvcli_comm_finalize();
	}
	else{
		status = ICP_HDL_FAILURE;
		ERRORF("Unexpected SIGNAL from CLIENT.\n");
		ERROR_EXIT();
	}

	ICP_POST_PROC(__FUNCTION__);
	return status;

}
#undef IF_SICP_CHK_SIG
