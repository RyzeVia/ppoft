/*
 * ICP_pftp.c
 *
 *  Created on: 2013/01/23
 *      Author: RyzeVia
 *
 *	*Parallel fault tolerant protocol definition
 *   This file use coordinated pftp.
 *
 */

#include "libicp.h"

/* Obsoluted: ICP_pftp_addproc */
void ICP_pftp_addproc(ICP_serv_info_t *sinfo, char* hostname){
	double node_fr;
	int ret;
	int push = 0;

	ICP_PRE_PROC(__FUNCTION__);
//	fprintf(stderr, "p in %s\n", sinfo->frdbname);

	if(ICP_frdb_search_joinedname(sinfo->frdbname, hostname) != 1){
		push = ICP_frdb_push_joinedname(sinfo->frdbname, hostname);
	}
//	fprintf(stderr, "p mid\n");

	if(push == 1){
		ret = ICP_frdb_search(sinfo->frdbname, hostname, &node_fr);
		sinfo->fr_current += node_fr;
	}

//	fprintf(stderr, "p out\n");
	ICP_POST_PROC(__FUNCTION__);

	return;
}

void ICP_pftp_make_filename(ICP_info_t *info, char* result, int withtag){

	ICP_PRE_PROC(__FUNCTION__);

	int iter = info->iter_current;
	char* fixediter;
	if((fixediter = CFR_getvalue("ICP_TEST_SINGLEGEN", NULL)) != NULL){
		iter = atoi(fixediter);
	}

	if(withtag == 0){
		if(info->iter_current == -1){
			snprintf(result, MAX_ICP_CKPTNAME, "%s", info->filename);
		}else{
			snprintf(result, MAX_ICP_CKPTNAME, "%s.%d", info->filename, iter);
		}
	}else{
		if(info->iter_current == -1){
			snprintf(result, MAX_ICP_CKPTNAME, "%s.%d", info->filename, info->filetag);
		}else{
			snprintf(result, MAX_ICP_CKPTNAME, "%s.%d.%d", info->filename, info->filetag, iter);
		}
	}
	ICP_POST_PROC(__FUNCTION__);

	return;

}

/*
 * TODO(Ryze): ICP_pftp_cli_pre/postckpt are for some extension like GC
 */
void ICP_pftp_cli_preckpt(ICP_info_t *info){
	ICP_PRE_PROC(__FUNCTION__);


	ICP_POST_PROC(__FUNCTION__);
}

void ICP_pftp_cli_postckpt(ICP_info_t *info){
	ICP_PRE_PROC(__FUNCTION__);


	ICP_POST_PROC(__FUNCTION__);
}

