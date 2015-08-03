#include <rpc/rpc.h>
#include "rls.h"

int main(){
	extern bool_t xdr_dir();
	extern char * read_dir();
	registerrpc(DIRPROG, DIRVERS, READDIR, read_dir, 
			(xdrproc_t)xdr_dir, (xdrproc_t)xdr_dir);
	svc_run();
	return 0;
}
