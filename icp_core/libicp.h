/*
 * libicp.h
 *
 *  Created on: 2012/11/13
 *      Author: RyzeVia
 */

#ifndef LIBICP_H_
#define LIBICP_H_

//#define ICP_PREPOST
//#define ICP_DMG_MPIIO_MODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <math.h>



#ifdef _WIN32
	#include <winsock.h>
#else
	#include <unistd.h>
	#include <sys/types.h>
	#include <fcntl.h>
#endif

// This ifdef for debugging. On compile, "cpio.h" is used everytime.
#if defined(ICP_DMG_MPIIO_MODE)
	#include "cpio/mpiio/cpio.h"
#else
	#include "cpio.h"
#endif

#include "utilmacros.h"

#include "libxpt.h"
#include "libcfr.h"

#ifndef CPIO_TYPEDEF
	#define CPIO_TYPEDEF
#endif

#define ICP_TRUE	XPT_TRUE
#define ICP_FALSE	XPT_FALSE

#define ICP_UNDEF_UINT	-999

#define ICP_RENEW_CALC_DIFF	0x1
#define ICP_RENEW_CALC_RATE 0x2
#define ICP_RENEW_CP_DIFF	0x4
#define ICP_RENEW_CP_RATE	0x8
#define ICP_RENEW_CALC	(ICP_RENEW_CALC_DIFF + ICP_RENEW_CALC_RATE)
#define ICP_RENEW_CP	(ICP_RENEW_CP_DIFF + ICP_RENEW_CP_RATE)
#define ICP_RENEW_DIFF	(ICP_RENEW_CALC_DIFF + ICP_RENEW_CP_DIFF)
#define ICP_RENEW_RATE	(ICP_RENEW_CALC_RATE + ICP_RENEW_CP_RATE)
#define ICP_RENEW_ALL	(ICP_RENEW_DIFF + ICP_RENEW_RATE)

#define ICP_ROLE_ONEOFTHE_WORLD XPT_ROLE_ONEOFTHE_WORLD
#define ICP_ROLE_ONEOFTHE_JOB	XPT_ROLE_ONEOFTHE_JOB
#define ICP_ROLE_ONEOFTHE_NODE	XPT_ROLE_ONEOFTHE_NODE
#define ICP_ROLE_OTHERS			XPT_ROLE_OTHERS

#define ICP_HDL_SUCCESS	(0)
#define ICP_HDL_FAILURE	(-1)
#define ICP_HDL_INVALID	(1)
#define ICP_HDL_EXTENDS (2)

#define ICP_SERVER_POLE_INTERVAL	1

#define ICP_SRV2CLI		"ICP_SRV2CLI"
#define ICP_CLI2SRV		"ICP_CLI2SRV"
#define ICP_CLI2CLI		"ICP_CLI2CLI" // have not use it
#define ICP_TOALL		"ICP_TOALL"
#define ICP_MSG_MODE	"INFO"

#define MAX_ICP_SIGLEN		18
#define MAX_ICP_PAYLOAD		(MAX_XPT_PAYLOAD-MAX_ICP_SIGLEN-14) //"cmd= payload= " = 14char
#define MAX_ICP_FILENAME	32
#define MAX_ICP_FILETAG		32
#define MAX_ICP_FILEITER	32
#define MAX_ICP_CKPTNAME	(MAX_ICP_FILENAME+MAX_ICP_FILETAG+MAX_ICP_FILEITER)
#define MAX_ICP_HOSTNAME	256
#define MAX_ICP_FRDB_LINE	(MAX_ICP_HOSTNAME + MAX_ICP_FILENAME)
#define MAX_ICP_COPRO_PID	4

#ifdef ICP_PREPOST
#define ICP_PRE_PROC(funcname) ICP_pre_procedure(funcname)
#define ICP_POST_PROC(funcname) ICP_post_procedure(funcname)
#else
#define ICP_PRE_PROC(funcname)
#define ICP_POST_PROC(funcname)
#endif

#define DEF_ICP_RECALC_MODE	ICP_RENEW_RATE
#define DEF_ICP_RECALC_EPS_RATE			0.5
#define DEF_ICP_RECALC_EPS_DIFF_SEC		100
#define DEF_ICP_RECALC_EPS_DIFF_NSEC	0
#define DEF_ICP_SERVER_PERIOD	1
#define DEF_ICP_CKPTNAME	"icp_ckpt"
#define DEF_ICP_CONFFILE	"icp_conf"
#define DEF_ICP_ROOTIP		"127.0.0.1"


#define ICP_ASSERT_PMODE(p_info, mode) \
	do {\
		if ((p_info)->pmode != (mode)) {\
			ERROR_LOC("Inapplicable function call on this process mode.");\
			exit(EXIT_FAILURE);\
		}\
	}while(0)

typedef enum ICP_procmode_ {
	ICP_PM_UNDEF,
	ICP_PM_CLIENT,
	ICP_PM_SERVER,
	MAX_ICP_PM,
} ICP_procmode_t;

typedef struct ICP_value_{
	int size;				// Byte
	char* start;			// starting pointer
} ICP_value_t;

typedef struct ICP_serv_info_ {

	double fr_current;	// failure rate for optimization
						// if the system use coordinated method,
						// this <fr> is summation of all of the subscribed processes.
	char frdbname[MAX_ICP_FILENAME];		// data base name
	int		ncopro;		// number of coprocess
	int		coppid[MAX_ICP_COPRO_PID]; // coprocesses' pid

} ICP_serv_info_t;

typedef struct ICP_info_ {

	XPT_info_t	xptinfo;	// handler of XPT
	ICP_serv_info_t* sinfo;	// if the proc is server, then sinfo structure pointer in here
	ICP_procmode_t pmode;	// Client is checkpointed process, Server is process decided checkpoint interval
	int	nvalue; 			// How many value does checkpointed on process
	int nregistered;		// How many value does registered for checkpointing
	ICP_value_t *cpvalue;	// checkpointed data
	int cpsize;				// checkpoint size for one process
	char filename[MAX_ICP_FILENAME]; // checkpoint filename base
	int filetag;			// checkpoint filename extension tag (use for MPI_Rank etc.)
	int restart;			// 0: nomal execute, 1: branch to restart

	/* FIXME(Ryze 2012/11/29): struct ICP_info_
	 * Following values for iteration management do need packing to structure ??
	 */
	struct timespec tstart_stamp; 	// time stamp on start
	struct timespec tcalc_stamp;	// time stamp on finishing calculation
	struct timespec tcp_stamp;		// time stamp on finishing checkpoint
	struct timespec tcalc_value;	// time for calculation
	struct timespec tcp_value;		// time for checkpoint
	struct timespec tcalc_current;	// current time for calculation with current offset/stride
	struct timespec tcp_current;	// current time for checkpoint with current offset/stride

	int iter_current;			// current iteration number pointer
	int iter_offset;			// checkpoint iteration offset
	int iter_stride;			// checkpoint iteration stride
	int recalc_mode;			// which threshold invoke iteration renewal (see definition of ICP_RENEW_XXX)
	double recalc_eps_rate;			// iteration renewal threshold (rate)
	struct timespec recalc_eps_diff;		// iteration renewal threshold (value)

	int is_client_leader;	// If this flag turned on, this process is leader (master of job process)

	int cpwait;		// for debug

	CPIO_TYPEDEF;

} ICP_info_t;


/* API LIST */

// ICP_base.c
//static int SICP_info_init_value(ICP_info_t *info);
//static int SICP_server_info_init_value(ICP_serv_info_t *sinfo);
//static void SICP_load_configure();
//void SICP_xpt_init(ICP_info_t info, ICP_procmode_t mode);
int ICP_client_init(ICP_info_t *info);
int ICP_client_enable(ICP_info_t *info, char* filename, int tag, int nckpt);
int ICP_client_ready(ICP_info_t *info);
int ICP_client_disable(ICP_info_t *info);
int ICP_server_init(ICP_info_t *info, ICP_serv_info_t *sinfo, char* frdbname);
int ICP_client_init_ob(ICP_info_t *sh, char* filename, int tag, int nckptdata);
int ICP_server_init_ob(ICP_info_t *sh, ICP_serv_info_t *sinfo, char* dbfilename);
int ICP_publish_to_cli(ICP_info_t *sh, char* signal, char* payload);
int ICP_publish_to_srv(ICP_info_t *sh, char* signal, char* payload);
int ICP_publish_to_all(ICP_info_t *sh, char* signal, char* payload);
//static void SICP_decode_payload(char* allpayload, char* signal, char* payload);
int ICP_poll_event(ICP_info_t *sh);
void ICP_set_client_leader(ICP_info_t *info);
void ICP_set_filename(ICP_info_t *info, char* filename);
void ICP_set_filetag(ICP_info_t *info, int tag);
void ICP_set_frdbfilename(ICP_serv_info_t *sinfo, char* filename);
void ICP_exec_coprocess(int process_role);
void ICP_killnwait_coprocess(int process_role);
void ICP_execcomp_coprocess();
//void SICP_info_free(ICP_info_t *info);
void ICP_client_fini(ICP_info_t *info, int lastfini);
void ICP_server_fini(ICP_info_t *info);
void ICP_set_fr(ICP_serv_info_t *sinfo, double fr);

// ICP_datamanage.c
int ICP_data_init(ICP_info_t *info, int ndata);
int ICP_registration_data(ICP_info_t *info, void* start, int count, int size_of_type);
int ICP_write_data(ICP_info_t *info);
int ICP_read_data(ICP_info_t *info);
int ICP_data_fini(ICP_info_t *info);
int ICP_data_ready(ICP_info_t *info);

// ICP_debug.c
int ICP_pre_procedure(const char* funcname);
int ICP_post_procedure(const char* funcname);

// ICP_failurerate_db.c
int ICP_frdb_search(char* dbname, char* hostname, double* fr);
void SICP_file_lock(FILE* fp, int cmd);
void ICP_file_readlock(FILE* fp);
void ICP_file_writelock(FILE* fp);
void ICP_file_unlock(FILE* fp);
int SICP_frdb_search_joinedname_byfp(FILE* fp, char* hostname);
void SICP_frdb_make_flagfilename(char* dbname, char* output);
int ICP_frdb_push_joinedname(char* dbname, char* hostname);
int ICP_frdb_search_joinedname(char* dbname, char* hostname);
void ICP_frdb_delete_flagfile(char* frdbname);

// ICP_handler.c
void ICP_sendhdl_cli_renew_iter(ICP_info_t *info);
void ICP_sendhdl_cli_process_join(ICP_info_t *info);
void ICP_sendhdl_srv_optimized_iter(ICP_info_t *info, int iter_offset, int iter_stride);
void ICP_sendhdl_cli_comm_finalize(ICP_info_t *info);
void ICP_sendhdl_srv_comm_finalize(ICP_info_t *info);
int ICP_recvhdl_srv_renew_iter(ICP_info_t *info, char* payload);
int ICP_recvhdl_srv_process_join(ICP_info_t *info, char* payload);
int ICP_recvhdl_cli_optimized_iter(ICP_info_t *info, char* payload);
int ICP_recvhdl_srvcli_comm_finalize();
int ICP_handle_clientmsg(ICP_info_t *info, char* sig, char* payload);
int ICP_handle_servermsg(ICP_info_t *info, char* sig, char* payload);

// ICP_optimize.c
void ICP_opt_get_iter(double fr, int iter, struct timespec *calc, struct timespec *cp, int *iter_offset, int *iter_stride);

// ICP_pftp.c
void ICP_pftp_addproc(ICP_serv_info_t *sinfo, char* hostname);
void ICP_pftp_make_filename(ICP_info_t *info, char* result, int withtag);
void ICP_pftp_cli_preckpt(ICP_info_t *info);
void ICP_pftp_cli_postckpt(ICP_info_t *info);

// ICP_scheduler_client.c
void ICP_timestamp_init(ICP_info_t *info);
void ICP_timestamp_start_cp(ICP_info_t *info);
void ICP_timestamp_finish_cp(ICP_info_t *info);
int ICP_send_elapsed(ICP_info_t *info, int iter_id);
void ICP_send_processjoin(ICP_info_t *info);
int ICP_checkpoint(ICP_info_t *info);
int ICP_restart(ICP_info_t *info);

// ICP_server.c
void ICP_server_main(ICP_info_t *info, ICP_serv_info_t *sinfo);
int ICP_server_main_immediate(ICP_info_t *info, ICP_serv_info_t *sinfo);

//static int SICP_is_ckpt_iteration(ICP_info_t *info);
//static int SICP_cond_overdiff(struct timespec *a, struct timespec *b, struct timespec *diff);
//static int SICP_cond_overrate(struct timespec *a, struct timespec *b, double *rate);
//static int SICP_condition_iterrenewal(ICP_info_t * info);




#include "libicp_gval.h"

#endif /* LIBICP_H_ */
