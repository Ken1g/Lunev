#define ERROR -100

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv, char** envp)
{
	execvp(argv[1], &argv[2]);
			
	return 0;
}
	
