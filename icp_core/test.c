/*
 * test.c
 *
 *  Created on: 2013/03/21
 *      Author: RyzeVia
 */

#include "libicp.h"

void main_serv(int, char**);
void main_clie(int, char**);

int main(int argc, char** argv){

	if(strcmp(argv[1], "s") == 0){
		main_serv(argc, argv);
	}else{
		main_clie(argc, argv);
	}

	return EXIT_SUCCESS;
}


void main_serv(int argc, char** argv){
	ICP_info_t info;
	ICP_serv_info_t sinfo;

	ICP_exec_coprocess(ICP_ROLE_ONEOFTHE_JOB | ICP_ROLE_ONEOFTHE_NODE);
	ICP_server_init_ob(&info, &sinfo, "./frdb");
	ICP_server_main(&info, &sinfo, "./frdb");

}

void main_clie(int argc, char** argv){
	ICP_info_t info;
	int i;
	int *a;

	a = &i;

	ICP_client_init_ob(&info, "./cp", 0, 1);
	ICP_set_client_leader(&info);

	ICP_registration_data(&info, a, a+1);
	ICP_timestamp_init(&info);
	for(i = 0; i < 10000; i++){
		sleep(1);
		fprintf(stdout, "%d\n", i);
		ICP_poll_event(&info);
	}


	ICP_client_fini(&info, 1);

}
