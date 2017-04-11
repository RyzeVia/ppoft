/*
 * ICP_server.c
 *
 *  Created on: 2013/02/14
 *      Author: RyzeVia
 */
#include "libicp.h"

/* TODO (Ryze 2013/02/14): ICP_server_main
 *
 *
 */
void ICP_server_main(ICP_info_t *info, ICP_serv_info_t *sinfo) {

	while(ICP_poll_event(info) != ICP_HDL_INVALID){
		sleep(ICP_SERVER_POLE_INTERVAL);
	}

}

int ICP_server_main_immediate(ICP_info_t *info, ICP_serv_info_t *sinfo){
	return ICP_poll_event(info);
}
