.c.o:
	gcc -c -Wall -DRPC_SVC_FG $<

all: rpc_ft_client rpc_ft_server

rpc_ft_client: rpc_ft_client.o file_clnt.o file_xdr.o
	gcc -o rpc_ft_client rpc_ft_client.o file_clnt.o file_xdr.o

rpc_ft_server: rpc_ft_server.o file_svc.o file_xdr.o
	gcc -o rpc_ft_server rpc_ft_server.o file_svc.o file_xdr.o -lrpcsvc

file.h: file.x
	rpcgen -C file.x

clean:
	rm rpc_ft_client rpc_ft_server *.o file.h file_svc.c file_clnt.c file_xdr.c 

rpc_ft_client.c: file.h
rpc_ft_server.c: file.h
