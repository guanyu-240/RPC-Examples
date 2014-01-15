#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include "file.h"

extern __thread int errno;
get_file_ret* get_file_1_svc(request *req, struct svc_req *rqstp) {
	FILE *fp = fopen(req->f_name, "rb");
	static get_file_ret ret;
	size_t bytes = 0;
	
	if (fp == NULL) {
		printf("Open file failed.\n");
		ret.errno = errno;
		return &ret;
	}

	fseek(fp, req->offset, SEEK_SET);
	bytes = fread(ret.get_file_ret_u.f_chunk.data, 1, MAX_CHUNK_SIZE, fp);
	ret.get_file_ret_u.f_chunk.bytes = bytes;
	ret.get_file_ret_u.f_chunk.offset = req->offset;
	ret.get_file_ret_u.f_chunk.end = feof(fp);
	fclose(fp);
	return &ret;
}
