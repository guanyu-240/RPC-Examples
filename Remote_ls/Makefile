.c.o:
	gcc -g -c -Wall -DRPC_SVC_FG $<

all: client server

client: rls_client.o rls_clnt.o rls_xdr.o
	gcc -g -o client rls_client.o rls_clnt.o rls_xdr.o

server: rls_server.o rls_svc.o rls_xdr.o
	gcc -g -o server rls_server.o rls_svc.o rls_xdr.o -lrpcsvc

rls.h: rls.x
	rpcgen -C rls.x
