/*
 * test.c
 *
 *  Created on: 2013/04/01
 *      Author: RyzeVia
 */
#define MEASURE_WTIME
#include <stdio.h>
#include <stdlib.h>
#include "libmicp.h"
#include "mpi.h"

int main(int argc, char** argv){
	MICP_info_t minfo;
	int i, rank;

	MPI_Init(&argc, &argv);
	MICP_init(&minfo);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

//	sleep(20);

	MICP_enable(&minfo, argv[0], 1);
	MICP_registration_data(&minfo, &i, 1, sizeof(int));
	MICP_ready(&minfo);
	for(i = 0; i < 100; i++){
		sleep(1);
		fprintf(stdout, "Rank[%d]: %d\n", rank, i);

		MICP_checkpoint_candidate(&minfo);
	}
	MICP_disable(&minfo);

	MICP_finalize(&minfo, "flag");
	MPI_Finalize();

	return EXIT_SUCCESS;
}
