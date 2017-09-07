#define INCORRECT_INPUT 	-100
#define NOT_A_NUMBER 		-101

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char** argv)
{
	long i, N;
	char* endptr;

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
		printf("%ld ", i + 1);

	return 0;
}
