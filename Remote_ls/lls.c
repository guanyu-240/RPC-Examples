#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rls.h"

int main (int argc, char **argv){
	char dir[DIR_SIZE];
	strcpy(dir, argv[1]);
	read_dir(dir);
	printf("%s\n", dir);
	return 0;
}
