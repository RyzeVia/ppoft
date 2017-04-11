/*
 * ICP_debug.c
 *
 *  Created on: 2012/11/20
 *      Author: RyzeVia
 */

#include "libicp.h"

/* ICP_debug: pre-post debugging function
 * if ICP_PREPOST was defined, following function called at
 * Entering/Exiting function.
 *
 * if you want to make this application as product,
 * please delete ICP_PREPOST on libicp.h
 */

#define PRINT_EACH_FUNCTION(fn, caption) \
	if(strcmp(funcname, fn) == 0) { \
		fprintf(stderr, "[%d]%s: %s\n", getpid(), caption, fn); \
	}

int ICP_pre_procedure(const char* funcname) {
	char* cap = "ENTER";

//	PRINT_EACH_FUNCTION(funcname, cap);

//	PRINT_EACH_FUNCTION("ICP_write_data", cap);
//	PRINT_EACH_FUNCTION("ICP_sendhdl_cli_process_join", cap);
//	PRINT_EACH_FUNCTION("ICP_pftp_addproc", cap);
//	PRINT_EACH_FUNCTION("ICP_poll_event", cap);
//	PRINT_EACH_FUNCTION("ICP_read_data", cap);
//	PRINT_EACH_FUNCTION("ICP_recvhdl_srv_process_join", cap);
//	PRINT_EACH_FUNCTION("ICP_handle_clientmsg", cap);
//	PRINT_EACH_FUNCTION("ICP_handle_servermsg", cap);

	PRINT_EACH_FUNCTION("ICP_client_enable", cap);
	PRINT_EACH_FUNCTION("ICP_data_init", cap);
	PRINT_EACH_FUNCTION("ICP_poll_event", cap);
	PRINT_EACH_FUNCTION("ICP_set_fr", cap);

	return EXIT_SUCCESS;
}

int ICP_post_procedure(const char* funcname) {

	char* cap = "EXIT";

//	PRINT_EACH_FUNCTION(funcname, cap);

//	PRINT_EACH_FUNCTION("ICP_write_data", cap);
//	PRINT_EACH_FUNCTION("ICP_sendhdl_cli_process_join", cap);
//	PRINT_EACH_FUNCTION("ICP_pftp_addproc", cap);
//	PRINT_EACH_FUNCTION("ICP_read_data", cap);
//	PRINT_EACH_FUNCTION("ICP_recvhdl_srv_process_join", cap);
//	PRINT_EACH_FUNCTION("ICP_handle_clientmsg", cap);
//	PRINT_EACH_FUNCTION("ICP_handle_servermsg", cap);

	return EXIT_SUCCESS;
}
#undef PRINT_EACH_FUNCTION
