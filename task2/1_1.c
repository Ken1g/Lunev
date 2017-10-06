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

typedef struct mybuf
{
	long mtype;
} mybuf;

int main(int argc, char** argv)
{
        long i, j, N, msqid;
        char *endptr;
	char fnm[] = "1.c";
	mybuf buf;
	struct msqid_ds rmbuf;
	pid_t p;	
	key_t k;
	     
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
//////////////// The main part of the task //////////////////
	k = ftok(fnm, 1);
	if ((msqid = msgget(k, 0666 | IPC_CREAT)) < 0)
	{
		printf("CANT_GET_MSQID");
		return CANT_GET_MSQID;
	}	
	for (i = 0; i < N; i++)
	{
		p = fork();
		if (p == 0)
		{		
			if (i == 0)
			{
				for (j = 0; j < (N - 1); j++)
				{
					buf.mtype = N + 1;
					msgsnd(msqid, (mybuf*) &buf, 0, 0);
					buf.mtype = j + 1;
                                        msgsnd(msqid, (mybuf*) &buf, 0, 0);
				}
				buf.mtype = N;
				msgsnd(msqid, (mybuf*) &buf, 0, 0);

			}
			msgrcv(msqid, (mybuf*) &buf, 0, i + 1, 0);
			errno = 0;
			msgrcv(msqid, (mybuf*) &buf, 0, N + 1, IPC_NOWAIT);
			if (errno == ENOMSG)
			{
				buf.mtype = 1;
				msgsnd(msqid, (mybuf*) &buf, 0, 0);
			}
			msgrcv(msqid, (mybuf*) &buf, 0, i + 1, 0);
			printf("%ld\n", i + 1);
			buf.mtype = i + 2;
			if (i != N - 1)
				msgsnd(msqid, (mybuf*) &buf, 0, 0);
			else
			{
				msgctl(msqid, IPC_RMID, &rmbuf);
				return 0;
			}
			break;
			
		}
		else if (p < 0)
		{
			printf("FORK_ERR");
			msgctl(msqid, IPC_RMID, &rmbuf);
			return FORK_ERR;
		}
	}
}
