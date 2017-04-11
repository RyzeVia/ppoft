#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


int main(int argc,char *argv[]) {
  int    rank, size, namelen;
  char   processor_name[MPI_MAX_PROCESSOR_NAME];
  MPI_Comm intercomm;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Get_processor_name(processor_name,&namelen);

  // check if spawned
  MPI_Comm_get_parent(&intercomm);
  if(intercomm != MPI_COMM_NULL){
    // Children
    int inter_size, inter_rank;
    MPI_Comm_size(intercomm, &inter_size);
    MPI_Comm_rank(intercomm, &inter_rank);
    printf("Child %d/%d %d/%d [%s]\n", rank, size, inter_rank, inter_size, processor_name);
/*    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    printf("Child %d/%d %d/%d [%s]\n", rank, size, inter_rank, inter_size, processor_name);
 */ } else {
    // Parents
    printf("Parent Comm %d/%d [%s]\n", rank, size, processor_name);
    //system("env | sort");
  
    int numprocs = 7;
    int errors[numprocs];
    MPI_Info info;
    MPI_Info_create(&info);
    MPI_Comm_spawn(*argv, argv, numprocs, info,
		   0, MPI_COMM_WORLD, &intercomm, errors);
//    MPI_Comm_spawn(NULL,NULL,NULL,NULL,
//		   0, MPI_COMM_WORLD, &intercomm, errors);
    int inter_size, inter_rank, inter_rsize;
    MPI_Comm_size(intercomm, &inter_size);
    MPI_Comm_rank(intercomm, &inter_rank);
    MPI_Comm_remote_size(intercomm, &inter_rsize);
    printf("Parent Intercomm %d/%d rsize=%d\n", inter_rank, inter_size, inter_rsize);
/*    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    printf("Parent %d/%d Intercomm %d/%d rsize=%d\n", rank, size, inter_rank, inter_size, inter_rsize);
*/
  }
  MPI_Finalize();
  return 0;
}
