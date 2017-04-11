/*
 * libmicp.h
 *
 *  Created on: 2013/01/29
 *      Author: RyzeVia
 */

#ifndef LIBMICP_H_
#define LIBMICP_H_

#include "utilmacros.h"

#include "libicp.h"
#include "libcfr.h"
#include "mpi.h"

/*
typedef enum MICP_procmode_ {
	MICP_PM_UNDEF,
	MICP_PM_CLIENT,
	MICP_PM_SERVER,
	MAX_MICP_PM,
} MICP_procmode_t;
*/
#define MICP_PM_UNDEF	0
#define MICP_PM_CLIENT	1
#define MICP_PM_SERVER	2

#define MICP_ROLE_ONEOFTHE_WORLD 	ICP_ROLE_ONEOFTHE_WORLD
#define MICP_ROLE_ONEOFTHE_JOB		ICP_ROLE_ONEOFTHE_JOB
#define MICP_ROLE_ONEOFTHE_NODE		ICP_ROLE_ONEOFTHE_NODE
#define MICP_ROLE_OTHERS			ICP_ROLE_OTHERS

#define DEF_MICP_CONFFILE	"micp_conf"
#define DEF_MICP_FLAGFILE	"micp_appfin"
#define DEF_MICP_FRDBFILE	"micp_fr"

typedef struct MICP_info_ {
	ICP_info_t info;
	ICP_serv_info_t sinfo;
	char hostname[MPI_MAX_PROCESSOR_NAME];
} MICP_info_t;

//MICP_base.c
//static int SMICP_is_spawned_process();
//static void SMICP_exec_server(MICP_info_t *minfo);
//static void SMICP_init_client(MICP_info_t *minfo, char* ckptname, int nckptdata);
//static void SMICP_load_configure();
int MICP_init(MICP_info_t *minfo);
void MICP_enable(MICP_info_t *minfo, char* ckptname, int nckptdata);
void MICP_disable(MICP_info_t *minfo);
int MICP_checkpoint_candidate(MICP_info_t *minfo);
void MICP_finalize(MICP_info_t *minfo, char* flagfile);
void MICP_registration_data(MICP_info_t *minfo, void *start, int count, int sizeoftype);
void MICP_ready(MICP_info_t *minfo);

#endif /* LIBMICP_H_ */
