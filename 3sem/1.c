#define INCORRECT_INPUT         -100
#define NOT_A_NUMBER            -101
#define FORK_ERR                -102

#define MAX_LENGTH 10

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <malloc.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
        long i, N;
        char* endptr;
	char* fullstr;
	pid_t p;
	int pipefd[2];

        if (argc != 2)
        {
                printf("INCORRECT_INPUT\n");
                return INCORRECT_INPUT;
        }
        errno = 0;
        N = strtol(argv[1], &endptr, 0);
        if ((errno == ERANGE && (N == LONG_MAX || N == LONG_MIN)) || (errno != 0 && N == 0))
        {
                printf("INCORRECT_INPUT\n");
                return INCORRECT_INPUT;
        }
        if (*endptr)
        {
                printf("NOT_A_NUMBER\n");
                return NOT_A_NUMBER;
        }

	res = pipe(pipefd);
	p = fork();
	if (p == 0)
	{
		FILE* input = fopen("input.txt", "r");
		fullstr = fgets(fullstr, MAX_LENGTH, input);
	}
	else if (p < 0)
	{
		printf("FORK_ERR");
		return FORK_ERR;
	}
	else
	{

	}
	

	
	
	





        return 0;
}

