const MAX_CHUNK_SIZE = 4096;
const MAX_FNAME_LEN = 1024;

typedef int boolean;

typedef opaque filename[MAX_FNAME_LEN];

struct request{
	filename f_name;
	u_long offset;
};

typedef struct request request;

typedef opaque chunk[MAX_CHUNK_SIZE];

struct filechunk {
	chunk data;
	u_long offset;
	u_long bytes;
	boolean end;
};

typedef struct filechunk filechunk;

union get_file_ret switch (int errno) {
	case 0:
		filechunk f_chunk;
	default:
		void;
};

program FT{
	version FTVERS {
		get_file_ret get_file(request *) = 1;
	} = 1;
} = 0x20000011;
