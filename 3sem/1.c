#define PIPE_CREATION_ERROR 	-100
#define CANT_FORK_CHILD		-101
#define CANT_OPEN_FILE		-102

#define BLOCK_SIZE 16000

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int pd[2], result, fd;
	size_t size;
	char* mystr = (char*) calloc(BLOCK_SIZE, sizeof(char));

	if (pipe(pd) < 0)
	{
		printf("PIPE_CREATION_ERROR");
		return PIPE_CREATION_ERROR;
	}
	result = fork();
	if (result < 0)
	{
		printf("CANT_FORK_CHILD");
		return CANT_FORK_CHILD;
	}
	else if (result == 0)
	{
		close(pd[0]);
		if ((fd = open("myfile", O_RDONLY)) < 0)
		{
			printf("CANT_OPEN_FILE");
			return CANT_OPEN_FILE;
		}
		size = read(fd, mystr, BLOCK_SIZE);		
		size = write(pd[1], mystr, BLOCK_SIZE);
		close(fd);
		close(pd[1]);
	}
	else
	{
		close(pd[1]);
		size = read(pd[0], mystr, BLOCK_SIZE);
		printf("%s", mystr);
		close(pd[0]);
	}
	free(mystr);
	
	return 0;
}
