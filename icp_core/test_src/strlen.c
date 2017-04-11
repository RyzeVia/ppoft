/*
 * strlen.c
 *
 *  Created on: 2013/04/22
 *      Author: RyzeVia
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){

	char *s = "hello world!\n";

	printf("%d: %s", strlen(s), s);
	printf("last words: [%s] \n", &(s[strlen(s) - 1]));
	return EXIT_SUCCESS;
}
