/*
 * MICP_base.c
 *
 *  Created on: 2013/01/28
 *      Author: RyzeVia
 */
//#define DEBUG_ENABLE
//#define DEBUG_LEVEL 60
//#define MEASURE_WTIME

#include "libmicp.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netdb.h>


extern void spawn_init();
extern int spawn_comm_get_parent(MPI_Comm *parent);
extern void spawn_fini();
extern int spawn_exec(MPI_Comm *intercomm);

static int SMICP_is_spawned_process(MPI_Comm *comm){
	spawn_comm_get_parent(comm);

	return (*comm != MPI_COMM_NULL );

}


static void SMICP_spawn(MPI_Comm *newcom){
	spawn_exec(newcom);
}

static void SMICP_exec_coserver(MICP_info_t* minfo) {
	int rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		if (rank == 0) {
			ICP_exec_coprocess(ICP_ROLE_ONEOFTHE_JOB);
			MPI_Barrier(MPI_COMM_WORLD);
			ICP_exec_coprocess(ICP_ROLE_ONEOFTHE_NODE);
			MPI_Barrier(MPI_COMM_WORLD);
//			ICP_server_main(&(minfo->info), &(minfo->sinfo), dbfilename);
//			ICP_server_init(&(minfo->info), &(minfo->sinfo), dbfilename);

		} else {
			MPI_Barrier(MPI_COMM_WORLD);
			ICP_exec_coprocess(ICP_ROLE_ONEOFTHE_NODE);
			MPI_Barrier(MPI_COMM_WORLD);
		}

}



static void SMICP_stop_coserver(MICP_info_t *minfo){
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		ICP_killnwait_coprocess(ICP_ROLE_ONEOFTHE_JOB | ICP_ROLE_ONEOFTHE_NODE);
	} else {
//		MICP_finalize(minfo, 0);
//		MPI_Finalize();
		ICP_killnwait_coprocess(ICP_ROLE_ONEOFTHE_NODE);
	}

}

static void SMICP_init_server(MICP_info_t *minfo){
	int mpi_rank, rt;
	char *dbfilename, *ffrprint = NULL;
	double fr, rfr;


	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

//	if(mpi_rank == 0){
//		MWTIME_PRINT(stderr, "[S]: \n");
//	}

	dbfilename = CFR_getvalue("MICP_FR_DBFILE", DEF_MICP_FRDBFILE);
	ICP_server_init(&(minfo->info), &(minfo->sinfo), dbfilename);

	if(mpi_rank == 0){
		MWTIME_PRINT(stderr, "[M]: Finish ftb_join\n");
	}

	/* all MPI procs (server/client) synchronization */
	/* start client init */
//	PMPI_Barrier(MPI_COMM_WORLD);
//	MWTIME_PRINT(stderr, "[S]: Finish SPT Init");

	ffrprint = CFR_getvalue("MICP_TEST_CHK_ALLCPRATE", NULL);
	if(ffrprint != NULL){
		rfr = atof(ffrprint);
		if(mpi_rank == 0){
			DEBUGF(DEBUG_LEVEL_INFO, "[%d] Failure rate of all HW is %f\n", getpid(), rfr);
		}
	}else{
		rt = ICP_frdb_search(dbfilename, minfo->hostname, &fr);
		MPI_Reduce(&fr, &rfr, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		if(mpi_rank == 0){
			DEBUGF(DEBUG_LEVEL_INFO, "[%d] Failure rate of all HW is %f\n", getpid(), rfr);
		}
	}
	ICP_set_fr(&(minfo->sinfo), rfr);


	if(mpi_rank == 0){
		MWTIME_PRINT(stderr, "[M]: Finish frdb_manage\n");
	}

	/* finish initialization */
	PMPI_Barrier(MPI_COMM_WORLD);

	ICP_execcomp_coprocess();
}

static void SMICP_init_client(MICP_info_t *minfo){
	int mpi_rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
//	PMPI_Barrier(MPI_COMM_WORLD);
	ICP_client_init(&(minfo->info));
	DEBUGF(DEBUG_LEVEL_INFO, "[%d][S][rank:%d] Finish client_init\n", getpid(), mpi_rank);
	if(mpi_rank == 0){
		ICP_set_client_leader(&(minfo->info));
	}

	/* all MPI procs (server/client) synchronization */
	PMPI_Barrier(MPI_COMM_WORLD);
}

static void SMICP_load_configure() {
	char *cfile;

	cfile = CFR_getvalue("MICP_CONFIG_FILE", DEF_MICP_CONFFILE);
	CFR_setenv_from_file(cfile, "%[^=]=%s");

	return;

}

int MICP_init(MICP_info_t *minfo) {
	MPI_Comm newcom = MPI_COMM_WORLD;
	MPI_Comm parent = MPI_COMM_NULL;
	int mpi_rank, mpi_rank_og;
	static int procmode = MICP_PM_UNDEF;
	char pn[MPI_MAX_PROCESSOR_NAME];
	char sn[MPI_MAX_PROCESSOR_NAME];
//	int nlen = MPI_MAX_PROCESSOR_NAME;
//	int poll_return;
//	char signal[MAX_ICP_SIGLEN], payload[MAX_ICP_PAYLOAD];

	//sleep(20);

	DEBUGF(DEBUG_LEVEL_TRIVIAL, "START MICP Init.\n");
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank_og);
	if(mpi_rank_og == 0){
		MWTIME_PRINT(stderr, "[M] All start\n");
	}

	spawn_init();

	if(mpi_rank_og == 0){
		MWTIME_PRINT(stderr, "[M] Finish spt_ini\n");
	}

	SMICP_load_configure();
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);


	//MPI_Get_processor_name(pn, &nlen);
	gethostname(minfo->hostname, MPI_MAX_PROCESSOR_NAME);

	//Get root IPADDR
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(minfo->hostname, "0", &hints, &res);
	getnameinfo(res->ai_addr, res->ai_addrlen, pn, MPI_MAX_PROCESSOR_NAME, sn, MPI_MAX_PROCESSOR_NAME, NI_NUMERICHOST|NI_NUMERICSERV);
	DEBUGF(DEBUG_LEVEL_TRIVIAL, "[%d][X][rank:%d/%d] hostname:%s, ip:%s\n", getpid(), mpi_rank, mpi_rank_og, minfo->hostname, pn);

	if (SMICP_is_spawned_process(&parent) && (procmode == MICP_PM_UNDEF)) {
		DEBUGF(DEBUG_LEVEL_TRIVIAL, "[%d][M][rank:%d/%d] start managing branch\n", getpid(), mpi_rank, mpi_rank_og);
		if(mpi_rank == 0){
			MWTIME_PRINT(stderr, "[M]: Finish get_env\n");
		}
		MPI_Bcast(pn, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, 0, MPI_COMM_WORLD);
		DEBUGF(DEBUG_LEVEL_TRIVIAL, "[%d][M][rank:%d/%d] hostname:%s, rootip:%s\n", getpid(), mpi_rank, mpi_rank_og, minfo->hostname, pn);

		if(mpi_rank == 0){
			PMPI_Send(pn, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, 0, 1, parent);
		}

		setenv("ICP_ROOT_IP", pn, 1);

		if(mpi_rank == 0){
			MWTIME_PRINT(stderr, "[M]: Finish env_bcast\n");
		}

		/* synchronize only servers */
		procmode = MICP_PM_SERVER;
		SMICP_exec_coserver(minfo);

		if(mpi_rank == 0){
			MWTIME_PRINT(stderr, "[M]: Finish ftb_const\n");
		}


		DEBUGF(DEBUG_LEVEL_TRIVIAL, "[%d][M][rank:%d/%d] finish coserver invoking\n", getpid(), mpi_rank, mpi_rank_og);

		/* synchronization */
		SMICP_init_server(minfo);

		if(mpi_rank == 0){
			MWTIME_PRINT(stderr, "[M]: Finish sync_ready\n");
		}

		if(mpi_rank == 0){
			/* FIXME: NEW COLLECTIVE HANDLER REGISTER */
			ICP_server_main(&(minfo->info), &(minfo->sinfo));
/*			while((poll_return = ICP_server_main_immediate(&(minfo->info), &(minfo->sinfo))) != ICP_HDL_INVALID){
				if(poll_return == ICP_HDL_EXTENDS){
					ICP_decode_payload(&(minfo->info), signal, payload);
					MICP_collective_handler(signal, payload);
				}
				sleep(ICP_SERVER_POLE_INTERVAL);
			}
*/		}

		MPI_Barrier(MPI_COMM_WORLD);

		SMICP_stop_coserver(minfo);
		MPI_Finalize();
		exit(EXIT_SUCCESS);
		/* does not through down from here without any error */

	} else {
		DEBUGF(DEBUG_LEVEL_TRIVIAL, "[%d][S][rank:%d/%d] start application branch\n", getpid(), mpi_rank, mpi_rank_og);
		SMICP_spawn(&newcom);

		if(mpi_rank == 0){
			MPI_Status state;
			PMPI_Recv(pn, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, 0, 1, newcom, &state);
		}
		MPI_Bcast(pn, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, 0, MPI_COMM_WORLD);
		DEBUGF(DEBUG_LEVEL_TRIVIAL, "[%d][S][rank:%d/%d] hostname:%s, rootip:%s\n", getpid(), mpi_rank, mpi_rank_og, minfo->hostname, pn);

		setenv("ICP_ROOT_IP", pn, 1);

#ifdef ICP_DMG_MPIIO
		CPIO_MPIIO_init(&(minfo->info), &newcom);
#endif
		procmode = MICP_PM_CLIENT;
		/* synchronization */
		SMICP_init_client(minfo);
		DEBUGF(DEBUG_LEVEL_TRIVIAL, "[%d][S][rank:%d/%d] Finish sync_ready\n", getpid(), mpi_rank, mpi_rank_og);


	}

	return procmode;
}

void MICP_enable(MICP_info_t *minfo, char* ckptname, int nckptdata){
	//SMICP_init_client(minfo, ckptname, nckptdata);
	int mpi_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
	ICP_client_enable(&(minfo->info), ckptname, mpi_rank, nckptdata);
}

void MICP_disable(MICP_info_t *minfo){
	ICP_client_disable(&(minfo->info));
}

int MICP_checkpoint_candidate(MICP_info_t *minfo){
	return ICP_poll_event(&(minfo->info));
}

void MICP_registration_data(MICP_info_t *minfo, void *start, int count, int sizeoftype){
	ICP_registration_data(&(minfo->info), start, count, sizeoftype);
}

void MICP_ready(MICP_info_t *minfo){
	DEBUGF(DEBUG_LEVEL_INFO, "[%d] CLIENT READY\n", getpid());
	ICP_client_ready(&(minfo->info));
	ICP_timestamp_init(&(minfo->info));
}

void MICP_finalize(MICP_info_t *minfo, char* flagfile){
	FILE *fp;
	int mpi_rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

	ICP_client_fini(&(minfo->info), mpi_rank);
	if(flagfile == NULL){
		flagfile = DEF_MICP_FLAGFILE;
	}
	if(mpi_rank == 0){
		fp = fopen(flagfile, "w");
		fprintf(fp, "Application was correctly finished. please delete this file before re-exec.\n");
		fclose(fp);
	}
#ifdef ICP_DMG_MPIIO
		CPIO_MPIIO_fini(&(minfo->info));
#endif

	spawn_fini();
}

