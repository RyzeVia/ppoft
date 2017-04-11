#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "mpi.h"

//#define HOSTNAME_DEBUG

MPI_Comm MPI_COMM_SMALLER_WORLD = MPI_COMM_WORLD;
MPI_Comm PARENT_INTERCOMM = MPI_COMM_NULL;
MPI_Comm SPAWN_INTERCOMM = MPI_COMM_WORLD;
static int spawned = 0;
static int initialized = 0;

void spawn_debug_start(char* funcname){
	printf("[%d] Called %s on spawnlib\n", getpid(), funcname);
}


void spawn_init(){
  int    rank = -1, size= -1, namelen= -1, max_namelen= -1;
  char   processor_name[MPI_MAX_PROCESSOR_NAME];
  MPI_Comm comm, newcomm;
  int i= -1, j= -1;
  char *p = NULL;


//  fprintf(stderr, "START Spawn\n");

  comm = MPI_COMM_WORLD;
  PMPI_Comm_size(comm,&size);
  PMPI_Comm_rank(comm,&rank);
  PMPI_Get_processor_name(processor_name,&namelen);
  p = strchr(processor_name, ':');
  if(p){
    *p = 0;
  }
  PMPI_Allreduce(&namelen, &max_namelen, 1, MPI_INT, MPI_MAX, comm);

  int *rank_map = (int *)malloc(sizeof(int) * size * 2);

//  fprintf(stderr, "Ranking branch\n");


  if(rank == 0){
    char *processor_names = (char *)malloc(max_namelen * size);
    PMPI_Gather(processor_name, max_namelen, MPI_CHAR,
                processor_names, max_namelen, MPI_CHAR,
                0, comm);
    int size0 = 0;
    int size1 = 0;
    for(i = 0; i < size; ++ i){
      int newname = 1;
      for(j = 0; j < i; ++ j){
        if(!strncmp(processor_names + max_namelen*i, processor_names + max_namelen*j, max_namelen)){
          newname = 0;
          break;
        }
      }
      if(newname){
        rank_map[2*i] = 1;
        rank_map[2*i+1] = size1 ++;
      } else {
        rank_map[2*i] = 0;
        rank_map[2*i+1] = size0 ++;
      }
    }
#ifdef HOSTNAME_DEBUG
    for(i = 0; i < size; ++ i){
      printf("%d: %d@%d %.*s\n", i, rank_map[2*i + 1], rank_map[2*i], max_namelen, processor_names + max_namelen*i);
    }
    //printf("%d\n", max_namelen);
#endif
    free(processor_names);
  }else{
    PMPI_Gather(processor_name, max_namelen, MPI_CHAR,
                0, max_namelen, MPI_CHAR,
                0, comm);
  }
  PMPI_Bcast(rank_map, 2 * size, MPI_INT, 0, comm);

  PMPI_Comm_split(comm, rank_map[2*rank], rank_map[2*rank + 1], &newcomm);
  int remote_leader = -1;
  MPI_Comm intercomm;
  for(i = 0; i < size; ++ i){
    if((rank_map[2*rank] != rank_map[2*i]) &&
       (rank_map[2*i+1] == 0)){
      remote_leader = i;
      break;
    }
  }
  MPI_COMM_SMALLER_WORLD = newcomm;
  PMPI_Intercomm_create(newcomm, 0, comm, remote_leader, 0, &intercomm);
  if(rank_map[2*rank] == 1){
    PARENT_INTERCOMM = intercomm;
    int flag;
    //MPI_Allreduce(&spawned, &flag, 1, MPI_INT, MPI_MAX, intercomm);
	PMPI_Allreduce(&spawned, &flag, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    spawned = 1;
    if(!flag){
      MPI_Finalize();
      exit(0);
    }
  }else{
    SPAWN_INTERCOMM = intercomm;
  }
  free(rank_map);

  //fprintf(stderr, "Finish init\n");

  initialized = 1;
  return;
}

int spawn_comm_get_parent(MPI_Comm *parent){
	  *parent = PARENT_INTERCOMM;
	  return MPI_SUCCESS;
}

void spawn_fini(){
	  if(!spawned){
	    int flag;
	    //MPI_Allreduce(&spawned, &flag, 1, MPI_INT, MPI_MAX, SPAWN_INTERCOMM);
		PMPI_Allreduce(&spawned, &flag, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
	  }
}

int spawn_exec(MPI_Comm *intercomm){
	int flag;
	*intercomm = SPAWN_INTERCOMM;
	spawned = 1;
	//MPI_Allreduce(&spawned, &flag, 1, MPI_INT, MPI_MAX, SPAWN_INTERCOMM);
	PMPI_Allreduce(&spawned, &flag, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

	return MPI_SUCCESS;
}

int MPI_Comm_get_parent(MPI_Comm *parent){
	spawn_debug_start(__FUNCTION__);
	if(initialized == 1){
		return spawn_comm_get_parent(parent);
	}
	return PMPI_Comm_get_parent(parent);
}


#ifdef SPT_MPI_OVERWRAP
int MPI_Finalize(){
	spawn_fini();
	return PMPI_Finalize();
}

int MPI_Init(int *argc, char ***argv){
  int r = PMPI_Init(argc, argv);
  spawn_init();
  return r;
}
int MPI_Init_thread(int *argc, char ***argv, int required, int *provided){
  int r = PMPI_Init_thread(argc, argv, required, provided);
  spawn_init();
  return r;
}

int MPI_Comm_get_parent(MPI_Comm *parent){
  return spawn_comm_get_parent(parent);
}

#ifdef MPICH_VERSION
int MPI_Comm_spawn(const char *command, char *argv[], int maxprocs, MPI_Info info, int root,
                   MPI_Comm comm, MPI_Comm *intercomm, int array_of_errcodes[]){
#else
int MPI_Comm_spawn(char *command, char **argv, int maxprocs, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *intercomm, int *array_of_errcodes){
#endif
  return spawn_exec(intercom);
}
#ifdef MPICH_VERSION
int MPI_Comm_spawn_multiple(int count, char *array_of_commands[], char **array_of_argv[], const int array_of_maxprocs[], const MPI_Info array_of_info[],int root, MPI_Comm comm, MPI_Comm *intercomm, int array_of_errcodes[]){
#else
int MPI_Comm_spawn_multiple(int count, char **array_of_commands, char ***array_of_argv, int *array_of_maxprocs, MPI_Info *array_of_info, int root, MPI_Comm comm, MPI_Comm *intercomm, int *array_of_errcodes){
#endif
	return spawn_exec(intercom);
}

#endif


