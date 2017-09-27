#define         CREATE_FIFO_ERROR       -100
#define         CANT_OPEN_FIFO_FOR_RD   -101
#define 	CANT_OPEN_FILE		-102

#define         OK      0
#define         ERROR   -1

#define BLOCK_SIZE 16000

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
        int ffd, fld, res;
        size_t size;
        char* mystr = (char*) calloc(BLOCK_SIZE, sizeof(char));
        char name[] = "a.fifo";

        umask(0);
       	if (res = fifo_create(name))
        {
                printf("CREATE_FIFO_ERROR");
                return CREATE_FIFO_ERROR;
        }
        if ((ffd = open(name, O_RDONLY)) < 0)
        {
                printf("CANT_OPEN_FIFO_FOR_RD");
                return CANT_OPEN_FIFO_FOR_RD;
        }
	if ((fld = open(argv[1], O_WRONLY | O_CREAT, 0666)) < 0)
        {
                printf("CANT_OPEN_FILE");
                return CANT_OPEN_FILE;
        }
	while (size = read(ffd, mystr, BLOCK_SIZE))
		size = write(fld, mystr, BLOCK_SIZE);
        close(ffd);
	close(fld);
	free(mystr);

        return 0;
}

