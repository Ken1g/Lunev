#define         CREATE_FIFO_ERROR       -100
#define         CANT_OPEN_FIFO_FOR_RD   -101
#define 	CANT_OPEN_FILE		-102

#define BLOCK_SIZE 2

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>

int main(int argc, char** argv)
{
        int ffd, fld, res;
        size_t size;
        char* mystr = (char*) calloc(BLOCK_SIZE, sizeof(char));
        char name[] = "a.fifo";
	char outnm[] = "2";

        umask(0);
       	if ((mknod(name, S_IFIFO | 0666, 0) < 0) && (errno != EEXIST))
	{
		printf("CREATE_FIFO_ERROR");
		return CREATE_FIFO_ERROR;	
	}
	errno = 0;
/*
	link(name, "a2.fifo");
        if (errno == EEXIST)
                return 0;
*/
        if ((ffd = open(name, O_RDONLY)) < 0)
        {
                printf("CANT_OPEN_FIFO_FOR_RD");
                return CANT_OPEN_FIFO_FOR_RD;
        }
	if ((fld = open(outnm, O_WRONLY | O_CREAT | O_APPEND, 0666)) < 0)
        {
                printf("CANT_OPEN_FILE");
                return CANT_OPEN_FILE;
        }
	while (size = read(ffd, mystr, BLOCK_SIZE))
		size = write(fld, mystr, size);
        close(ffd);
	close(fld);
	free(mystr);
	unlink("a2.fifo");

        return 0;
}

