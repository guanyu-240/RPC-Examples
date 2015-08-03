#define VERSION_NUMBER 1

#define DIR_SIZE 8196 

struct dirpath{
	char name[DIR_SIZE];
};


program RLS_PROG{
	version RLS_VERSION{
		dirpath READ_DIR(dirpath) = 1;
	} = VERSION_NUMBER;
} = 555555555;
