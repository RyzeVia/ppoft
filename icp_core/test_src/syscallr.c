#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
	int a;

	a = SXPTI_FTB_exist_programs(argv[1]);

	printf("%s: %d\n", argv[1], a);
	




	return EXIT_SUCCESS;
}

int SXPTI_FTB_exist_programs(char* pname){
	char buf[256];
	sprintf(buf, "pgrep -x %s > /dev/null 2>&1", pname);
	return !(system(buf));
}
