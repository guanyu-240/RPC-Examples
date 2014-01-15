#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file.h"

extern __thread int errno;

FILE *fp;
CLIENT *clnt;

void init_fp(char *f_name) {
    fp = fopen(f_name, "wb");
    if (fp == NULL) {
        printf("Initialize file pointer error!\n");
        exit(1);
    }
}

void init_clnt(char *host) {
    clnt = clnt_create(host, FT, FTVERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        fclose(fp);
        exit(1);
    }
}

/*
 * Call the remote procedure and get the file
 */
int get_file_rpc(char *host, char *f_name) {
    init_fp(f_name);
    init_clnt(host);

    size_t offset = 0;
    size_t written = 0;
    get_file_ret *ret;
    request req;
    memset(req.f_name, 0, MAX_FNAME_LEN);
    memcpy(req.f_name, f_name, (strlen(f_name) <=  MAX_FNAME_LEN ? strlen(f_name): MAX_FNAME_LEN));
    while (1) {
        req.offset = offset;
        ret = get_file_1(&req, clnt);

        // connection error
        if (ret == NULL) {
            clnt_perror(clnt, host);
            fclose(fp);
            exit(1);
        }

        // file name does not exist
        if (ret->errno != 0) {
            errno = ret->errno;
            perror(f_name);
            fclose(fp);
            exit(1);
        }

        // successfully got a file chunk
        if (ret->get_file_ret_u.f_chunk.offset == offset) {
            printf("Write a chunk\n");
            written = fwrite(ret->get_file_ret_u.f_chunk.data, 1,
                        ret->get_file_ret_u.f_chunk.bytes, fp);
            if (written < 0) {
                perror("Error in writing\n");
                exit(1);
            }
            offset += ret->get_file_ret_u.f_chunk.bytes;
        }
        if (ret->get_file_ret_u.f_chunk.end) break;
    }

    fclose(fp);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: ./rpc_ft_client <host> <file>\n");
        exit(1);
    }
    printf("%s : %lu\n", argv[2], strlen(argv[2]));
    get_file_rpc(argv[1], argv[2]);
    return 0;
}

