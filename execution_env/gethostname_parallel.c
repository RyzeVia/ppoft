/*
 * gethostname_parallel.c
 *
 *  Created on: 2013/12/03
 *      Author: RyzeVia
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char** argv){
        int rank, size, filesize, namelen;
        MPI_File sf;
        MPI_Status st;
        char buf[MPI_MAX_PROCESSOR_NAME];
        char buf2[MPI_MAX_PROCESSOR_NAME+32];

        if(argc < 1){ exit(EXIT_FAILURE); }

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Get_processor_name(buf, &namelen);

        sprintf(buf2, "%s\t%s\n", buf, argv[1]);

        MPI_File_open(MPI_COMM_WORLD, "hostnames", MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &sf);

        MPI_File_write_shared(sf, buf2, strlen(buf2), MPI_CHAR, &st);

        MPI_File_close(&sf);

        MPI_Finalize();

        return EXIT_SUCCESS;

}
