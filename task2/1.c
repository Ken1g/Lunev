#define INCORRECT_INPUT         -100
#define NOT_A_NUMBER            -101
#define FORK_ERR		-102
#define CANT_GET_MSQID		-103

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

typedef struct mybuf
{
	long mtype;
} mybuf;

int main(int argc, char** argv)
{
	long i, j, N, msqid;
	int status;
        char *endptr;
	mybuf buf;
	pid_t p;
	struct msqid_ds rmbuf;	
	char buff[BUFSIZ];

//////////////// Reading Command line data ////////////////
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
//////////////// The main part of the task /////////////////
	setvbuf(stdout, buff,  _IONBF, 0);
	if ((msqid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT)) < 0)
	{
		printf("CANT_GET_MSQID\n");
		return CANT_GET_MSQID;
	}
	for (i = 0; i < N; i++)
	{
		p = fork();
		if (p == 0)
		{
			if (i == (N - 1))
			{
				buf.mtype = 1;
                        	msgsnd(msqid, (mybuf*) &buf, 0, 0);
			}
			errno = 0;
			msgrcv(msqid, (mybuf*) &buf, 0, i + 1, 0);
			if ((errno == EIDRM) || (errno == EINVAL))
				exit(FORK_ERR);
			printf("%ld\n", i + 1);
			if (i != (N - 1))
			{
				buf.mtype = i + 2;
				msgsnd(msqid, (mybuf*) &buf, 0, 0);
			}
			else
				msgctl(msqid, IPC_RMID, &rmbuf);
			exit(0);
		}
		else if (p < 0)
		{
			printf("FORK_ERR\n");
			msgctl(msqid, IPC_RMID, &rmbuf);
			exit(FORK_ERR);
		}
	}
	for (i = 0; i < N; i++)
		wait(&status);
		
	return 0;	
}
