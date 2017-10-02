#define 	CREATE_FIFO_ERROR 		-100
#define		CANT_OPEN_FIFO_FOR_WR		-101
#define 	CANT_OPEN_FILE			-102
#define 	INCORRECT_NUMBER_OF_ARGUMENTS	-103

#define BLOCK_SIZE 2 // 16 kb

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>

int main(int argc, char** argv)
{
	int ffd, fld;
	int res;
	size_t size;
	char* mystr = (char*) calloc(BLOCK_SIZE, sizeof(char));
	char name[] = "a.fifo";
	struct stat sb;

	umask(0);
	unlink("2");
	if (argc != 2)
	{
		printf("INCORRECT_NUMBER_OF_ARGUMENTS");
		return INCORRECT_NUMBER_OF_ARGUMENTS;
	}
	if ((mknod(name, S_IFIFO | 0666, 0) < 0) && (errno != EEXIST))
	{
                printf("CREATE_FIFO_ERROR");
		return CREATE_FIFO_ERROR;
	}
	errno = 0;
/*
	link(name, "a1.fifo");
	if (errno == EEXIST)
		return 0;
*/
	if ((fld = open(argv[1], O_RDONLY)) < 0) 
	{
		printf("CANT_OPEN_FILE");
		return CANT_OPEN_FILE;
	}
	if ((ffd = open(name, O_WRONLY | O_NONBLOCK)) < 0)
	{
		printf("CANT_OPEN_FIFO_FOR_WR");
		printf("%d", errno);
//		printf("%d", ENXIO);
		return CANT_OPEN_FIFO_FOR_WR;
	}
	while (size = read(fld, mystr, BLOCK_SIZE))
		size = write(ffd, mystr, size);
	close(ffd);
	close(fld);
	free(mystr);
//	unlink("a1.fifo");
	unlink("a.fifo");

	return 0;
}
