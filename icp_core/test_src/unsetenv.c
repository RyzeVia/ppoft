#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv){
	char* res, *res2, *res3;
	setenv("A", "B", 1);

	res = getenv("A");

	printf("%s\n", res);

	unsetenv("A");

	setenv("B", "C", 1);

	res2 = getenv("B");

	printf("%s, %s\n", res, res2);

	res3 = getenv("A");

	printf("%s, %s, %s\n", res, res2, res3);

	return 1;



}

