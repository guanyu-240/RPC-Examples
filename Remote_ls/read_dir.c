#include <stdio.h>
#include <sys/types.h>
#include <sys/dir.h>
#include "rls.h"

void *read_dir(char *dir){
	DIR *dir_ptr;
	struct direct *d;
	printf("beginning ");
	dir_ptr = opendir(dir);
	if (dir_ptr == NULL){
		return NULL;
	}
	dir[0] = (int)NULL;
	while ((d = readdir(dir_ptr))){
		sprintf(dir, "%s%s\n", dir, d->d_name);
	}
	printf("returning ");
	closedir(dir_ptr);
	return (void *)(dir);
}
