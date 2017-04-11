/*
 * ICP_failurerate_db.c
 *
 *  Created on: 2013/01/18
 *      Author: RyzeVia
 *
 *	*Database manipulate method definition
 *   This file use text db with Liner search
 *
 */

#include "libicp.h"

int ICP_frdb_search(char* dbname, char* hostname, double * dbfr) {
	char line[MAX_ICP_FRDB_LINE];
	char dbhn[MAX_ICP_HOSTNAME];
	int done = 0;
	FILE *fp;

	ICP_PRE_PROC(__FUNCTION__);

	*dbfr = 0;
	if ((fp = fopen(dbname, "r")) == NULL ) {
		ERRORF("DB file (%s) is not found.\n", dbname);
		return ICP_FALSE;
	}


	while (fgets(line, MAX_ICP_FRDB_LINE, fp) != NULL) {
		// permit no \n line just before EOF
		if (line[strlen(line) - 1] != '\n') {
			ERRORF("DB file (%s) has too long line: %s\n", dbname, line);
			return ICP_FALSE;
		}
		// skip line which has # on the first
		if (line[0] == '#') {
			continue;
		}

		// search
		if (sscanf(line, "%s %lf", dbhn, dbfr) != 2) {
			ERRORF("DB file (%s) has wrong format line: %s\n", dbname, line);
			return ICP_FALSE;
		}

		if (strncmp(hostname, dbhn, MAX_ICP_HOSTNAME) == 0) {
			done = 1;
			break;
		}
	}
	if (done == 0) {
		*dbfr = 0.;
	}


	ICP_POST_PROC(__FUNCTION__);
	return ICP_TRUE;
}

void SICP_file_lock(FILE* fp, int cmd){
    struct flock fl;

    int fd = fileno(fp);
    fl.l_type   = cmd;
    fl.l_whence = SEEK_SET;
    fl.l_start  = 0;
    fl.l_len    = 0;
    fl.l_pid    = getpid();

sicp_file_lock_relock:
    if (fcntl(fd, F_SETLKW, &fl) == -1) {
    	if(errno == EINTR){
    		goto sicp_file_lock_relock;
    	}
    	perror("fcntl");
        ERROR_EXIT();
    }
}

void ICP_file_readlock(FILE* fp){
//	fprintf(stdout, "rlock\n");

	SICP_file_lock(fp, F_RDLCK);

//	fprintf(stdout, "rlock out\n");
}

void ICP_file_writelock(FILE* fp){
//	fprintf(stdout, "wlock\n");
	SICP_file_lock(fp, F_WRLCK);
//	fprintf(stdout, "wlock out\n");
}

void ICP_file_unlock(FILE* fp){
//	fprintf(stdout, "unlock\n");
	SICP_file_lock(fp, F_UNLCK);
//	fprintf(stdout, "unlock out\n");
}


int SICP_frdb_search_joinedname_byfp(FILE* fp, char* hostname){
	int done = 0;
	char line[MAX_ICP_HOSTNAME];



//	while ((done != 1) || (feof(fp) == 0)) {
	while(fgets(line, MAX_ICP_FRDB_LINE, fp) != NULL){
/*
		if (fgets(line, MAX_ICP_FRDB_LINE, fp) == NULL ) {
			continue;
//			ERRORF("DB file (%s) got error on reading.\n", dbname);
//			ERROR_EXIT();
		}
		*/
		// permit no \n line just before EOF
		if (line[strlen(line) - 1] != '\n') {
			ERRORF("DB file has too long line: %s\n", line);
			ERROR_EXIT();
		}
		// skip line which has # on the first
		if (line[0] == '#') {
			continue;
		}

		if (strncmp(hostname, line, strlen(hostname)) == 0) {
			done = 1;
			break;
		}
	}

//	fprintf(stdout, "# out\n");

	return done;
}

void SICP_frdb_make_flagfilename(char* dbname, char* output){
	sprintf(output, "%s.fl", dbname);
}

void ICP_frdb_delete_flagfile(char* frdbname){
	char output[MAX_ICP_FILENAME];


	SICP_frdb_make_flagfilename(frdbname, output);
	unlink(output);
	DEBUGF(DEBUG_LEVEL_INFO, "[%d]:delete %s\n", getpid(), output);
}

int ICP_frdb_push_joinedname(char* dbname, char* hostname){
	FILE *fp;
	int done = 0;
	char fn[MAX_ICP_FILENAME];

	SICP_frdb_make_flagfilename(dbname, fn);

//	fprintf(stdout, "make/write[%d]: %s\n", errno, fn);
	if ((fp = fopen(fn, "a+")) == NULL ) {
		ERRORF("DB file (%s) is not found.\n", fn);
		ERROR_EXIT();
	}
	ICP_file_writelock(fp);

	if(SICP_frdb_search_joinedname_byfp(fp, hostname) != 1){
		done = 1;
	//	printf("write %s\n", hostname);
		fprintf(fp, "%s\n", hostname);
	}


	ICP_file_unlock(fp);

	fclose(fp);

	return done;
}

int ICP_frdb_search_joinedname(char* dbname, char* hostname){
	FILE *fp;
	int done = 0;
	char fn[MAX_ICP_FILENAME];

	SICP_frdb_make_flagfilename(dbname, fn);
	if ((fp = fopen(fn, "r")) != NULL ) {
		ICP_file_readlock(fp);
		done = SICP_frdb_search_joinedname_byfp(fp, hostname);
		ICP_file_unlock(fp);
		fclose(fp);
	}

	return done;
}


