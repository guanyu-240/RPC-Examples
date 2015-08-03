#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "rls.h"

void read_dir(char *host, char *dir)
{
	extern bool_t xdr_dir();
	enum clnt_stat clnt_stat;
	clnt_stat = callrpc(host, DIRPROG, DIRVERS, READDIR,
					(xdrproc_t)xdr_dir, dir, (xdrproc_t)xdr_dir, dir);
	if (clnt_stat != 0){
		clnt_perrno (clnt_stat);
	}
}

int main(int argc, char *argv[])
{
	if (argc!=3) {
		fprintf(stderr,"Usage: %s hostname dir\n",argv[0]);
		exit(0);
	}
	char dir[DIR_SIZE];
	strcpy(dir, argv[2]);
	read_dir(argv[1], dir);
	printf("%s\n", dir);
	exit(0);
}
