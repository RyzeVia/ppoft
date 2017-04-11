/*
 * ICP_fortran.c
 *
 *  Created on: 2012/11/27
 *      Author: RyzeVia
 */

#include "libicp.h"

/* expired ?? */

/* icp_info_table[*chdl]:
 *  On fortran, it is difficult to use value of structure
 *  Then it convert to index
 */
static void sficp_info_init(ICP_info_t* table, int size){
	static int once_execute = 0;
	if(once_execute == 0){
		CALLOC(ICP_info_t*, icp_info_table, size, sizeof(ICP_info_t));
		once_execute = 1;
	}
	return;
}

int ficp_client_init(int *chdl, int *size){
	sficp_info_init(icp_info_table, *size);
	return ICP_client_init(&(icp_info_table[*chdl]));
}

int ficp_server_init(int *chdl, int *size){
	sficp_info_init(icp_info_table, *size);
	return ICP_server_init(&(icp_info_table[*chdl]));
}

int ficp_write_data(int *chdl){
	return ICP_write_data(&(icp_info_table[*chdl]));
}

int ficp_read_data(int *chdl){
	return ICP_read_data(&(icp_info_table[*chdl]));
}
