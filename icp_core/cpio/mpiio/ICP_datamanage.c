/*
 * ICP_datamanage_mpiio.c
 *
 *  Created on: 2013/09/18
 *      Author: RyzeVia
 */
/* FIXME(Ryze 2012/11/20): ICP_datamanage.c
 *  All functions on this file assume
 * cp values do not change on application execution (simply,... static!).
 * Then most of functions have code about "One-Time-Called-Limitation".
 */

#include "libicp.h"
#include "mpi.h"


static int metasize = 0;
int ICP_data_init(ICP_info_t *info, int ndata) {
	ICP_PRE_PROC(__FUNCTION__);
	ICP_ASSERT_PMODE(info, ICP_PM_CLIENT);

	if (info->nvalue != ICP_UNDEF_UINT) {
		ERROR_LOC("Cannot re-execute this function");
		exit(EXIT_FAILURE);
	}

	info->nvalue = ndata;
	info->nregistered = 0;
	MALLOC(ICP_value_t*, info->cpvalue, sizeof(ICP_value_t)*ndata);

	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;
}

int ICP_data_fini(ICP_info_t *info){
	ICP_PRE_PROC(__FUNCTION__);
	ICP_ASSERT_PMODE(info, ICP_PM_CLIENT);
	free(info->cpvalue);
	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;

}

int ICP_data_ready(ICP_info_t *info){
/*
	int i;
	for (i = 0; i < info->nregistered; i++) {
		ICP_value_t *cpv = &((info->cpvalue)[i]);
		info->cpsize += cpv->size;
	}
*/
	int nprocs;
	MPI_Comm comm = *((MPI_Comm*)(info->comm));
	MPI_Comm_size(comm, &nprocs);
	metasize = sizeof(int)*nprocs;
	info->cpsize += sizeof(info->iter_current);
	return ICP_TRUE;
}

/* FIXME(Ryze 2012/11/20): ICP_registration_data
 * This function cannot un-register value.
 * For supporting it, I must change the ICP_value_t for
 * light-weight, efficient data management.
 */
/* TODO(Ryze 2012/11/20): ICP_registration_data
 * On many case, cp data registration is called one time
 * for one value. Does I need to include passing second calling for same value ?
 */
int ICP_registration_data(ICP_info_t *info, void* start, int count, int size_of_type){
	ICP_value_t *cpv;

	ICP_PRE_PROC(__FUNCTION__);
	ICP_ASSERT_PMODE(info, ICP_PM_CLIENT);

	if (info->nregistered == info->nvalue) {
		ERROR_LOC("the registration over the allocated value");
		exit(EXIT_FAILURE);
	}

	cpv = &((info->cpvalue)[info->nregistered]);
	cpv->size = size_of_type * count;
	cpv->start = (char*)start;
	(info->nregistered)++;
	info->cpsize += cpv->size;

	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;

}




/* (Ryze 2013/05/14): Following function was obsoleted, because this function
 * cannot got last of the data. For compatibility of previous application,
 * the function still remain. BUT DON'T USE THIS!
 */

int ICP_registration_data_ob(ICP_info_t *info, void* start, void* end) {
	ICP_value_t *cpv;


	ICP_PRE_PROC(__FUNCTION__);
	ICP_ASSERT_PMODE(info, ICP_PM_CLIENT);

	if (info->nregistered == info->nvalue) {
		ERROR_LOC("the registration over the allocated value");
		exit(EXIT_FAILURE);
	}

	cpv = &((info->cpvalue)[info->nregistered]);
	cpv->size = (char*)end - (char*)start;
	cpv->start = (char*)start;
	(info->nregistered)++;

	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;
}





/* FIXME(Ryze 2012/11/22): ICP_write_data/ICP_read_data
 * These functions can support same byte-order data between writing and reading.
 * For interoperability, They must implement to use some "Standard Format" like netCDF(?).
 */

int ICP_write_data(ICP_info_t *info) {
	int i;
	char ckptname[MAX_ICP_CKPTNAME];
	char *cpprint;
	MPI_File fh;
	int offset = metasize;
	int rank;
	MPI_Status state;
	MPI_Comm comm = *((MPI_Comm*)(info->comm));

	ICP_PRE_PROC(__FUNCTION__);
	ICP_ASSERT_PMODE(info, ICP_PM_CLIENT);

	ICP_pftp_make_filename(info, ckptname, 0);
	// NEXT: //

	MPI_Comm_rank(comm, &rank);
	offset = rank*(info->cpsize);
	MPI_File_open(comm, ckptname, MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);

	/* meta infomation */
	MPI_File_write_at(fh, sizeof(int)*rank, &rank, sizeof(int), MPI_BYTE, &state);

	/* checkpoint */
	MPI_File_write_at(fh, offset, &(info->iter_current), sizeof(int), MPI_BYTE, &state);
	offset += sizeof(int);
	for (i = 0; i < info->nregistered; i++) {
		ICP_value_t *cpv = &((info->cpvalue)[i]);
		MPI_File_write_at(fh, offset, cpv->start, cpv->size, MPI_BYTE, &state);
		offset += cpv->size;
	}

	sleep(info->cpwait);

	cpprint = CFR_getvalue("ICP_TEST_CHK_CPDONE", NULL);
	if(cpprint != NULL){
		fprintf(stderr, "CP WAS DONE.\n");
	}

	MPI_File_close(&fh);
	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;

}

int ICP_read_data(ICP_info_t *info) {
	int i;
	char ckptname[MAX_ICP_CKPTNAME];
	MPI_File fh;
	int offset = metasize;
	int rank;
	MPI_Status state;
	MPI_Comm comm = *((MPI_Comm*)(info->comm));

	ICP_PRE_PROC(__FUNCTION__);
	ICP_ASSERT_PMODE(info, ICP_PM_CLIENT);

	ICP_pftp_make_filename(info, ckptname, 0);


	MPI_Comm_rank(comm, &rank);
	offset = rank*(info->cpsize);
	MPI_File_open(comm, ckptname, MPI_MODE_CREATE|MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);

	MPI_File_read_at(fh, offset, &(info->iter_current), sizeof(int), MPI_BYTE, &state);
	offset += sizeof(int);
	for (i = 0; i < info->nregistered; i++) {
		ICP_value_t *cpv = &((info->cpvalue)[i]);
		MPI_File_read_at(fh, offset, cpv->start, cpv->size, MPI_BYTE, &state);
		offset += cpv->size;
	}

	MPI_File_close(&fh);

	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;

}

void CPIO_MPIIO_init(void *info, void *comm){
	static int inited = 0;
	if (inited == 1){
		return;
	}

	((ICP_info_t *)info)->comm = malloc (sizeof(MPI_Comm));
	memcpy(((ICP_info_t *)info)->comm, comm, sizeof(MPI_Comm));
	inited = 1;
}

void CPIO_MPIIO_fini(void *info){
	free (((ICP_info_t *)info)->comm);
}


