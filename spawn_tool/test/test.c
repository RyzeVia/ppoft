/*
 * test.c
 *
 *  Created on: 2013/04/10
 *      Author: RyzeVia
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int SMICP_is_spawned_process() {
	MPI_Comm comm;
	MPI_Comm_get_parent(&comm);

	return (comm != MPI_COMM_NULL );

}

int main(int argc, char** argv){

	int i;
	int rank;
	MPI_Comm newcom;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(SMICP_is_spawned_process()){
		printf("SPAWNED %d\n", rank);
	}else{
		printf("PARENT %d\n", rank);
		MPI_Comm_spawn(NULL, NULL, 0, 0, 0, 0, &newcom, NULL);
	}

	MPI_Finalize();
}
