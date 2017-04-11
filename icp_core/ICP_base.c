/*

 * ICP_base.c
 *
 *  Created on: 2012/11/13
 *      Author: RyzeVia
 */

#include "libicp.h"

/* INFO: Comment outed value's initialization is obsoleted
 * because caller of this function initialize by practical use value
 * (not a temporal value like -1, NULL, 0, ...) before or after the function is called.
 */
static int SICP_info_init_value(ICP_info_t *info) {
//	memset(info->xptinfo, 0, sizeof(XPT_info_t));
//	info->pmode = ICP_PM_UNDEF;
	info->nvalue = ICP_UNDEF_UINT;
	info->nregistered = ICP_UNDEF_UINT;
	info->cpvalue = NULL;
	info->cpsize = 0;
	(info->filename)[0] = '\0';
	tsclear(&(info->tstart_stamp));
	tsclear(&(info->tcalc_stamp));
	tsclear(&(info->tcp_stamp));
	tsclear(&(info->tcalc_value));
	tsclear(&(info->tcp_value));
	tsclear(&(info->tcalc_current));
	tsclear(&(info->tcp_current));
	info->iter_current = 0;
	info->iter_offset = 0;
	info->iter_stride = 1000;
	info->recalc_mode = DEF_ICP_RECALC_MODE;
	info->recalc_eps_rate = DEF_ICP_RECALC_EPS_RATE;
	info->recalc_eps_diff.tv_sec = DEF_ICP_RECALC_EPS_DIFF_SEC;
	info->recalc_eps_diff.tv_nsec = DEF_ICP_RECALC_EPS_DIFF_NSEC;
	info->is_client_leader = ICP_UNDEF_UINT;
	info->cpwait = 0;

	return ICP_TRUE;
}

static int SICP_server_info_init_value(ICP_serv_info_t *sinfo) {
	sinfo->fr_current = 0.0;
	sinfo->frdbname[0] = '\0';
	sinfo->ncopro = 0;

	return ICP_TRUE;
}

static void SICP_load_configure() {
	char *cfile;

	cfile = CFR_getvalue("ICP_CONFIG_FILE", DEF_ICP_CONFFILE);
//	printf("%s\n", cfile);
	CFR_setenv_from_file(cfile, "%[^=]=%s");

	return;

}

void HICP_sigint(int sig){
	ICP_killnwait_coprocess(ICP_ROLE_OTHERS);
	fprintf(stderr, "receive SIGINT or SIGTERM\n");
	exit(EXIT_FAILURE);
}

static void SICP_signal_init(){
	struct sigaction sa;
	sigset_t saset;

	sigemptyset(&saset);
	sigaddset(&saset, SIGINT);
	sigaddset(&saset, SIGTERM);

	sa.sa_handler = HICP_sigint;
	sa.sa_mask = saset;
	sa.sa_flags = SA_RESETHAND;

	sigaction(SIGINT, &sa, NULL);
	/* for openMPI, every process reset by SIGTERM */
	sigaction(SIGTERM, &sa, NULL);
}


void SICP_xpt_init(ICP_info_t *info, ICP_procmode_t mode){
	XPT_info_t *xptinfo;
	char* event_name;

	SICP_load_configure();
	SICP_info_init_value(info);

	setenv("XPT_ROOT_IP", CFR_getvalue("ICP_ROOT_IP", DEF_ICP_ROOTIP), 1);

	event_name = CFR_getvalue("ICP_EVENTNAME", NULL);
	xptinfo = &(info->xptinfo);
	info->pmode = mode;

	DEBUGF(DEBUG_LEVEL_INFO, "[%d] Invoke XPT_init, pmode=%d\n", getpid(), mode);


	XPT_init(xptinfo, event_name);

//	DEBUGF(DEBUG_LEVEL_INFO, "[%d] finish XPT_init\n", getpid());

	XPT_phdl_init(xptinfo, 2);

//	DEBUGF(DEBUG_LEVEL_INFO, "[%d] finish XPT_phdl_init\n", getpid());


	XPT_pull_subscribe(xptinfo, ICP_TOALL, NULL );

//	DEBUGF(DEBUG_LEVEL_INFO, "[%d] finish subscribing\n", getpid());

	XPT_declare_publishable_events(xptinfo, ICP_TOALL, ICP_MSG_MODE);

//	DEBUGF(DEBUG_LEVEL_INFO, "[%d] finish publish register\n", getpid());


	if(mode == ICP_PM_CLIENT){
		XPT_pull_subscribe(xptinfo, ICP_SRV2CLI, NULL );
		XPT_declare_publishable_events(xptinfo, ICP_CLI2SRV, ICP_MSG_MODE);
	}else if(mode == ICP_PM_SERVER){
		SICP_signal_init();
		XPT_pull_subscribe(xptinfo, ICP_CLI2SRV, NULL );
		XPT_declare_publishable_events(xptinfo, ICP_SRV2CLI, ICP_MSG_MODE);
	}
}

int ICP_client_init(ICP_info_t *info){
	char* cpwait;

	ICP_PRE_PROC(__FUNCTION__);
	SICP_xpt_init(info, ICP_PM_CLIENT);
	if((cpwait = CFR_getvalue("ICP_TEST_CPWAIT", NULL)) != NULL){
		info->cpwait = atoi(cpwait);
	}

	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;
}

int ICP_client_enable(ICP_info_t *info, char* filename, int tag, int nckpt){
	int retval;
	char *iter;

	ICP_PRE_PROC(__FUNCTION__);
	if((filename = CFR_getvalue("ICP_CKPTNAME", filename)) == NULL){
		filename = DEF_ICP_CKPTNAME;
	}
	strncpy(info->filename, filename, MAX_ICP_FILENAME);
	info->filetag = tag;

	if(CFR_getvalue("ICP_RESTART_FLAG", NULL) != NULL){
		iter = CFR_getvalue("ICP_RESTART_ITER", "-1");
		info->iter_current = atoi(iter);
		info->restart = 1;
//		printf("restart!?\n");
	}else{
		info->restart = 0;
	}

	retval = ICP_data_init(info, nckpt);

// Move to server task
//	if(tag == 0){
//		ICP_send_processjoin(info);
//	}

	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;

}

int ICP_client_ready(ICP_info_t *info){
	ICP_PRE_PROC(__FUNCTION__);
	ICP_data_ready(info);

	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;

}

int ICP_client_disable(ICP_info_t *info){
	ICP_PRE_PROC(__FUNCTION__);
	ICP_data_fini(info);

	ICP_POST_PROC(__FUNCTION__);

	return ICP_TRUE;
}

int ICP_subscribe_extention(ICP_info_t *info, char* signal, char* extra_attribute){
	return XPT_pull_subscribe(&(info->xptinfo), signal, extra_attribute);
}

int ICP_publish_extention(ICP_info_t *info, char* signal, char* serverity){
	return XPT_declare_publishable_events(&(info->xptinfo), signal, serverity);
}

int ICP_server_init(ICP_info_t *info, ICP_serv_info_t *sinfo, char* frdbname){
	ICP_PRE_PROC(__FUNCTION__);

	SICP_xpt_init(info, ICP_PM_SERVER);

	SICP_server_info_init_value(sinfo);
	info->sinfo = sinfo;
	strncpy(sinfo->frdbname, frdbname, MAX_ICP_FILENAME);
	ICP_frdb_delete_flagfile(frdbname);


	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;

}


/* Obsoluted Function XXX_ob */
int ICP_client_init_ob(ICP_info_t *sh, char* filename, int tag, int nckptdata) {
	XPT_info_t *xptinfo;
	int retval;
	char* event_name;
	char* cpwait;
	char *iter;

	ICP_PRE_PROC(__FUNCTION__);

	SICP_load_configure();
	SICP_info_init_value(sh);


	if((filename = CFR_getvalue("ICP_CKPTNAME", filename)) == NULL){
		filename = DEF_ICP_CKPTNAME;
	}
	strncpy(sh->filename, filename, MAX_ICP_FILENAME);
	sh->filetag = tag;

	/* Note: info->iter_current is tentative value for fix the restart filename.
	 * on reading data, this re-load from restart file.
	 */
	if(CFR_getvalue("ICP_RESTART_FLAG", NULL) != NULL){
		iter = CFR_getvalue("ICP_RESTART_ITER", "-1");
		sh->iter_current = atoi(iter);
		sh->restart = 1;
//		printf("restart!?\n");
	}else{
		sh->restart = 0;
	}

	if((cpwait = CFR_getvalue("ICP_TEST_CPWAIT", NULL)) != NULL){
		sh->cpwait = atoi(cpwait);
	}

	event_name = CFR_getvalue("ICP_EVENTNAME", NULL);
	xptinfo = &(sh->xptinfo);
	sh->pmode = ICP_PM_CLIENT;
	XPT_init(xptinfo, event_name);
	XPT_phdl_init(xptinfo, 2);
	XPT_pull_subscribe(xptinfo, ICP_SRV2CLI, NULL );
	XPT_pull_subscribe(xptinfo, ICP_TOALL, NULL );
	XPT_declare_publishable_events(xptinfo, ICP_CLI2SRV, ICP_MSG_MODE);
	XPT_declare_publishable_events(xptinfo, ICP_TOALL, ICP_MSG_MODE);

	retval = ICP_data_init(sh, nckptdata);

	if(tag == 0){
		ICP_send_processjoin(sh);
	}

	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;
}

int ICP_server_init_ob(ICP_info_t *sh, ICP_serv_info_t *sinfo, char* dbfilename) {
	XPT_info_t *xptinfo;
	char* event_name;

	ICP_PRE_PROC(__FUNCTION__);

	SICP_info_init_value(sh);
	SICP_server_info_init_value(sinfo);
	sh->sinfo = sinfo;
	strncpy(sinfo->frdbname, dbfilename, MAX_ICP_FILENAME);
	xptinfo = &(sh->xptinfo);
	sh->pmode = ICP_PM_SERVER;

	event_name = CFR_getvalue("ICP_EVENTNAME", NULL);
	XPT_init(xptinfo, event_name);

	XPT_phdl_init(xptinfo, 2);
	XPT_pull_subscribe(xptinfo, ICP_CLI2SRV, NULL );
	XPT_pull_subscribe(xptinfo, ICP_TOALL, NULL );
	XPT_declare_publishable_events(xptinfo, ICP_SRV2CLI, ICP_MSG_MODE);
	XPT_declare_publishable_events(xptinfo, ICP_TOALL, ICP_MSG_MODE);

	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;
}

static int SICP_publish(XPT_info_t *sh, char* msgtype, char* signal,
		char* payload) {
	char pl[MAX_XPT_PAYLOAD];

	DEBUGF(50 , "publish: cmd=%s payload=%s\n", signal, payload);

	if (signal != NULL ) {
		sprintf(pl, "cmd=%s payload=%s", signal, payload);
	} else {
		ERRORF("Publish API needs signal character\n");
		ERROR_EXIT();
	}
	return XPT_publish(sh, msgtype, 1, pl);
}

int ICP_publish_to_cli(ICP_info_t *sh, char* signal, char* payload) {
	int res;
	XPT_info_t *info = &(sh->xptinfo);

	ICP_PRE_PROC(__FUNCTION__);

	res = SICP_publish(info, ICP_SRV2CLI, signal, payload);

	ICP_POST_PROC(__FUNCTION__);
	return res;
}

int ICP_publish_to_srv(ICP_info_t *sh, char* signal, char* payload) {
	int res;
	XPT_info_t *info = &(sh->xptinfo);

	ICP_PRE_PROC(__FUNCTION__);

	res = SICP_publish(info, ICP_CLI2SRV, signal, payload);

	ICP_POST_PROC(__FUNCTION__);
	return res;
}

int ICP_publish_to_all(ICP_info_t *sh, char* signal, char* payload) {
	int res;
	XPT_info_t *info = &(sh->xptinfo);

	ICP_PRE_PROC(__FUNCTION__);

	res = SICP_publish(info, ICP_TOALL, signal, payload);

	ICP_POST_PROC(__FUNCTION__);
	return res;
}

void SICP_decode_payload(char* allpayload, char* signal, char* payload) {
	int rv;
	if (signal == NULL ) {
		ERRORF("Decode API needs signal character space\n");
		ERROR_EXIT();
	}
	if (payload != NULL ) {
		rv = sscanf(allpayload, "cmd=%s payload=%s", signal, payload);
		if (rv > 2) {
			payload[0] = 0;
		}
	} else {
		sscanf(allpayload, "cmd=%s", signal);
	}
}

void ICP_decode_payload(ICP_info_t *info, char* signal, char* payload){
	ICP_PRE_PROC(__FUNCTION__);
	SICP_decode_payload(XPT_poll_get_payload(&(info->xptinfo)), signal, payload);
	ICP_POST_PROC(__FUNCTION__);
}

int ICP_poll_event(ICP_info_t *sh) {
	XPT_info_t *info = &(sh->xptinfo);
	char sig[MAX_ICP_SIGLEN];
	char payload[MAX_ICP_PAYLOAD];
	int result = ICP_HDL_SUCCESS;

	ICP_PRE_PROC(__FUNCTION__);

	XPT_POLL(info) {
		DEBUGF(DEBUG_LEVEL_TRIVIAL, "[%d] Polling got %s: %s\n", getpid(), info->pulled_event, XPT_poll_get_payload(info));

		XPT_CHECK(info, ICP_CLI2SRV) {
			SICP_decode_payload(XPT_poll_get_payload(info), sig, payload);
			result = ICP_handle_clientmsg(sh, sig, payload);
			XPT_CHECKED(info);
		} else XPT_CHECK(info, ICP_SRV2CLI) {
			SICP_decode_payload(XPT_poll_get_payload(info), sig, payload);
			result = ICP_handle_servermsg(sh, sig, payload);
			XPT_CHECKED(info);
		} else {
			result = ICP_HDL_EXTENDS;
			ICP_POST_PROC(__FUNCTION__);
			return result;
		}

		if(result != ICP_HDL_SUCCESS){
			break;
		}

	}

	if(sh->pmode == ICP_PM_CLIENT){
		int retrest, retcp;
		retrest = ICP_restart(sh);
		retcp = ICP_checkpoint(sh);

		DEBUGF(DEBUG_LEVEL_TRIVIAL, "[%d] leader flag %d, restart %d, cp %d\n", sh->is_client_leader, getpid(), retrest, retcp);

		if((sh->is_client_leader == 1) && ((retrest == 1) || (retcp == 1))){
			ICP_send_elapsed(sh, 0);
		}

	}else{
		DEBUGF(DEBUG_LEVEL_TRIVIAL, "[%d] Server polling\n", getpid());
	}
	sh->iter_current++;
	ICP_POST_PROC(__FUNCTION__);
	return result;
}


void ICP_set_client_leader(ICP_info_t *info){
	info->is_client_leader = 1;
}


void ICP_set_filename(ICP_info_t *info, char* filename) {
	ICP_PRE_PROC(__FUNCTION__);

	strncpy(info->filename, filename, MAX_ICP_FILENAME);
	ICP_POST_PROC(__FUNCTION__);

}

void ICP_set_filetag(ICP_info_t *info, int tag) {
	ICP_PRE_PROC(__FUNCTION__);
	info->filetag = tag;

	ICP_POST_PROC(__FUNCTION__);

}

void ICP_set_frdbfilename(ICP_serv_info_t *sinfo, char* filename) {
	ICP_PRE_PROC(__FUNCTION__);
	strncpy(sinfo->frdbname, filename, MAX_ICP_FILENAME);
	ICP_POST_PROC(__FUNCTION__);

}

void ICP_set_fr(ICP_serv_info_t *sinfo, double fr){
	ICP_PRE_PROC(__FUNCTION__);
	sinfo->fr_current = fr;

	ICP_POST_PROC(__FUNCTION__);

}

void ICP_exec_coprocess(int process_role) {
	ICP_PRE_PROC(__FUNCTION__);

	setenv("XPT_ROOT_IP", CFR_getvalue("ICP_ROOT_IP", DEF_ICP_ROOTIP), 1);

	XPT_exec_coprocess(process_role);


	ICP_POST_PROC(__FUNCTION__);

}

void ICP_killnwait_coprocess(int process_role){
	ICP_PRE_PROC(__FUNCTION__);
	XPT_killnwait_coprocess(process_role);

	ICP_POST_PROC(__FUNCTION__);

}

void ICP_execcomp_coprocess(){
	XPT_coserver_exec_complete();
}

void SICP_info_free(ICP_info_t *info){
	ICP_data_fini(info);
}

void ICP_client_fini(ICP_info_t *info, int tag){
	if(tag == 0){
		ICP_sendhdl_cli_comm_finalize(info);
	}
	XPT_pull_unsubscribe(&(info->xptinfo));
//	SICP_info_free(info);
}

void ICP_server_fini(ICP_info_t *info){

}

