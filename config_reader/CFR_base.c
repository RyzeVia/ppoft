/*
 * CFR_base.c
 *
 *  Created on: 2013/01/30
 *      Author: RyzeVia
 */

#define GLOBAL_DEFINITION
#include "libcfr.h"

char* CFR_getvalue(char* token, char* defvalue){
	char *rv;
	if((rv = getenv(token)) == NULL){
		rv = defvalue;
	}

	return rv;
}

int CFR_deletevalue(char* token){
	int rv;

	rv = unsetenv(token);

	return rv;
}

int CFR_setenv_from_file(char* filename, const char* formatter){
	char key[MAX_CFR_KEYSIZE];
	char value[MAX_CFR_VALUESIZE];
	char line[MAX_CFR_LINESIZE];
	FILE *fp;

	if((fp = fopen(filename, "r")) == NULL){
		ERRORF("Configure file (%s) is not found.\n", filename);
		return CFR_FALSE;
	}

	while(feof(fp) == 0){
		if(fgets(line, MAX_CFR_LINESIZE, fp) == NULL){
			continue;
			//ERRORF("Configure file (%s) got error on reading.\n", filename);
			//ERROR_EXIT();
		}
		// permit no \n line just before EOF
		if((feof(fp) != 0) && (line[strlen(line)-1] != '\n')) {
			ERRORF("Configure file (%s) has too long line (limit all:%d(key:%d+value:%d)): %s\n",
					filename, MAX_CFR_LINESIZE, MAX_CFR_KEYSIZE, MAX_CFR_VALUESIZE,
					line);
			ERROR_EXIT();
		}
		// skip line which has # on the first
		if(line[0] == '#'){
			continue;
		}

		// search
		switch (sscanf(line, formatter, key, value)){

		case 1:
			unsetenv(key);
			break;
		case 2:
			if(setenv(key, value, 1) < 0){
				if(errno == EINVAL){
					ERRORF("Configure file(%s) has '=' on key or value.\n", filename);
					ERRORF("Passing line: %s\n", line);
				}
				else if(errno == ENOMEM){
					ERRORF("Cannot allocate memory.\n");
					ERROR_EXIT();
				}
			}
			break;
		default:
			ERRORF("There are some unexpected thing.\n");
			ERROR_EXIT();
			break;
		}

	}

	return CFR_TRUE;

}

