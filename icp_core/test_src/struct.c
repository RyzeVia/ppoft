#include <stdio.h>
#include <stdlib.h>

#define MOD_STRUCT \
	double e; \
	double f;

typedef struct A_info_ {
	int a;
	int b;;
	int c;
	MOD_STRUCT;
} A_info;

int main(int argc, char** argv){

	A_info a;
	a.b = 2;
	a.c = 2;
	a.a = 1;

	printf("%d, %d, %d\n", a.a, a.b, a.c);

	return EXIT_SUCCESS;

}

