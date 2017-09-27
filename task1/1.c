#define 	CREATE_FIFO_ERROR 	-100
#define		CANT_OPEN_FIFO_FOR_WR	-101
#define 	CANT_OPEN_FILE		-102

#define		OK 	0
#define 	ERROR	-1

#define BLOCK_SIZE 16000 // 16 kb

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>

int fifo_create(char* ffnm)
{
	if ((mknod(ffnm, S_IFIFO | 0666, 0) < 0) && (errno != EEXIST))
        	return ERROR;
	return OK;
}

int main(int argc, char** argv)
{
	int ffd, fld;
	int res;
	size_t size;
	char* mystr = (char*) calloc(BLOCK_SIZE, sizeof(char));
	char name[] = "a.fifo";

	umask(0);
	if (res = fifo_create(name))
	{
		printf("CREATE_FIFO_ERROR");
		return CREATE_FIFO_ERROR;
	}
	if ((fld = open(argv[1], O_RDONLY)) < 0) 
	{
		printf("CANT_OPEN_FILE");
		return CANT_OPEN_FILE;
	}
	if ((ffd = open(name, O_WRONLY)) < 0)
	{
		printf("CANT_OPEN_FIFO_FOR_WR");
		return CANT_OPEN_FIFO_FOR_WR;
	}
	while (size = read(fld, mystr, BLOCK_SIZE))
		size = write(ffd, mystr, BLOCK_SIZE); 
	close(ffd);
	close(fld);
	free(mystr);

	return 0;
}
