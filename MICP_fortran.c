/*
 * MICP_fortran.c
 *
 *  Created on: 2013/05/09
 *      Author: RyzeVia
 */

#include "libmicp.h"
#define FMICP_MAX_FILENAME_SIZE 384

/* for Intel compiler */
//#define EXTN extern
#define EXTN
EXTN void fmicp_init_(int* err);
EXTN void fmicp_init__(int* err);
EXTN void fmicp_enable_(char* ckptname, int* len, int *nckptdata);
EXTN void fmicp_enable__(char* ckptname, int* len, int *nckptdata);
EXTN void fmicp_ready_();
EXTN void fmicp_ready__();
EXTN void fmicp_disable_();
EXTN void fmicp_disable__();
EXTN void fmicp_checkpoint_candidate_(int* err);
EXTN void fmicp_checkpoint_candidate__(int* err);
EXTN void fmicp_finalize_(char* flagfile, int* len);
EXTN void fmicp_finalize__(char* flagfile, int* len);
EXTN void fmicp_registration_data_(void* start, int* count, void* second);
EXTN void fmicp_registration_data__(void* start, int* count, void* second);
EXTN void fmicp_registration_data_scaler_(void* start, void* typearray1st, void* typearray2nd);
EXTN void fmicp_registration_data_scaler__(void* start, void* typearray1st, void* typearray2nd);
EXTN void fmicp_registration_data_sizeof_(void* start, int* count, int* size);
EXTN void fmicp_registration_data_sizeof__(void* start, int* count, int* size);

/*
int MICP_init(MICP_info_t *minfo);
void MICP_enable(MICP_info_t *minfo, char* ckptname, int nckptdata);
void MICP_disable(MICP_info_t *minfo);
int MICP_checkpoint_candidate(MICP_info_t *minfo);
void MICP_finalize(MICP_info_t *minfo, char* flagfile);
void MICP_registration_data(MICP_info_t *minfo, void *start, void *stop);
void MICP_ready(MICP_info_t *minfo);
*/
static MICP_info_t minfo;


#pragma weak fmicp_init_ = fmicp_init
#pragma weak fmicp_init__ = fmicp_init
void fmicp_init(int* err){
	*err = MICP_init(&minfo);
}

#pragma weak fmicp_enable_ = fmicp_enable
#pragma weak fmicp_enable__ = fmicp_enable
void fmicp_enable(char* ckptname, int* len, int *nckptdata){
	char buf[FMICP_MAX_FILENAME_SIZE];
	memset(buf, 0, FMICP_MAX_FILENAME_SIZE);
	strncpy(buf, ckptname, *len);
//	fprintf(stderr, "%s(%d)\n", buf, *len);

	MICP_enable(&minfo, buf, *nckptdata);
}

#pragma weak fmicp_ready_ = fmicp_ready
#pragma weak fmicp_ready__ = fmicp_ready
void fmicp_ready(){
	MICP_ready(&minfo);
}

#pragma weak fmicp_disable_ = fmicp_disable
#pragma weak fmicp_disable__ = fmicp_disable
void fmicp_disable(){
	MICP_disable(&minfo);
}

#pragma weak fmicp_checkpoint_candidate_ = fmicp_checkpoint_candidate
#pragma weak fmicp_checkpoint_candidate__ = fmicp_checkpoint_candidate
void fmicp_checkpoint_candidate(int* err){
	*err = MICP_checkpoint_candidate(&minfo);
}

#pragma weak fmicp_finalize_ = fmicp_finalize
#pragma weak fmicp_finalize__ = fmicp_finalize
void fmicp_finalize(char* flagfile, int* len){
	char buf[FMICP_MAX_FILENAME_SIZE];
	memset(buf, 0, FMICP_MAX_FILENAME_SIZE);
	strncpy(buf, flagfile, *len);
	MICP_finalize(&minfo, buf);
}

#pragma weak fmicp_registration_data_ = fmicp_registration_data
#pragma weak fmicp_registration_data__ = fmicp_registration_data
void fmicp_registration_data(void* start, int* count, void* second){
	MICP_registration_data(&minfo, start, *count, (char*)second - (char*)start);
}

#pragma weak fmicp_registration_data_scaler_ = fmicp_registration_data_scaler
#pragma weak fmicp_registration_data_scaler__ = fmicp_registration_data_scaler
void fmicp_registration_data_scaler(void* start, void* typearray1st, void* typearray2nd){
	MICP_registration_data(&minfo, start, 1, (char*)typearray2nd - (char*)typearray1st);
}
#pragma weak fmicp_registration_data_sizeof_ = fmicp_registration_data_sizeof
#pragma weak fmicp_registration_data_sizeof__ = fmicp_registration_data_sizeof
void fmicp_registration_data_sizeof(void* start, int* count, int* size){
	MICP_registration_data(&minfo, start, *count, *size);
}
