/*
 * ICP_datamanage.c
 *
 *  Created on: 2012/11/14
 *      Author: RyzeVia
 */

/* FIXME(Ryze 2012/11/20): ICP_datamanage.c
 *  All functions on this file assume
 * cp values do not change on application execution (simply,... static!).
 * Then most of functions have code about "One-Time-Called-Limitation".
 */

#include "libicp.h"

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
	FILE *fp;
	char ckptname[MAX_ICP_CKPTNAME];
	int rv;
	char *cpprint;
	int cppf;

	ICP_PRE_PROC(__FUNCTION__);
	ICP_ASSERT_PMODE(info, ICP_PM_CLIENT);

	ICP_pftp_make_filename(info, ckptname, 1);


	if ((fp = fopen(ckptname, "w")) == NULL ) {
		ERROR_LOC("Cannot create FILE.");
		exit(EXIT_FAILURE);
	}

	do {
		rv = fwrite(&(info->iter_current), sizeof(int), 1, fp);
	} while (rv != 1);

	for (i = 0; i < info->nregistered; i++) {
		ICP_value_t *cpv = &((info->cpvalue)[i]);
		do {
			rv = fwrite(cpv->start, cpv->size, 1, fp);
		} while (rv != 1);
	}

	sleep(info->cpwait);

	cpprint = CFR_getvalue("ICP_TEST_CHK_CPDONE", NULL);
	if(cpprint != NULL){
		fprintf(stderr, "CP WAS DONE.\n");
	}


	fclose(fp);

	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;

}

int ICP_read_data(ICP_info_t *info) {
	int i;
	FILE *fp;
	char ckptname[MAX_ICP_CKPTNAME];
	int rv;

	ICP_PRE_PROC(__FUNCTION__);
	ICP_ASSERT_PMODE(info, ICP_PM_CLIENT);

	ICP_pftp_make_filename(info, ckptname, 1);

	if ((fp = fopen(ckptname, "r")) == NULL ) {
		ERROR_LOC("Cannot read file.");
		exit(EXIT_FAILURE);
	}

	do {
		rv = fread(&(info->iter_current), sizeof(int), 1, fp);
	} while (rv != 1);

	for (i = 0; i < info->nregistered; i++) {
		ICP_value_t *cpv = &((info->cpvalue)[i]);
		do {
			rv = fread(cpv->start, cpv->size, 1, fp);
		} while (rv != 1);
	}

	fclose(fp);

	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;

}

