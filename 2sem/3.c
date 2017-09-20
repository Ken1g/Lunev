#define INCORRECT_INPUT         -100
#define NOT_A_NUMBER            -101
#define FORK_ERR                -102

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <malloc.h>

void* write_down(void* data)
{
	long n = (int) data;

	printf("%ld\n", n);
	
	return NULL;
}

int main(int argc, char** argv)
{
        long i, N;
        char* endptr;
	int number = 0;
        pid_t p;
	pthread_t* threads;

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
	threads = (pthread_t*) calloc(N, sizeof(pthread_t));	
	for (i = 0; i < N; i++)
        {
		pthread_create(&(threads[i]), NULL, write_down, i + 1);
        }
	for(i = 0; i < N; i++)
        {
                pthread_join(threads[i], NULL);
        }
	free(threads);

	return 0;
}
