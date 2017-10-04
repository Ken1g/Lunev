#define INCORRECT_INPUT         -100
#define NOT_A_NUMBER            -101
#define FORK_ERR		-102

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char** argv)
{
        long i, N;
        char* endptr;
	pid_t p;

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
	for (i = 0; i < N; i++)
	{
		p = fork();
		if (p == 0)
		{
			printf("%ld\n", i + 1);
			break;
		}
		else if (p < 0)
		{
			printf("FORK_ERR");
			return FORK_ERR;
		}
	}

	return 0;
}
