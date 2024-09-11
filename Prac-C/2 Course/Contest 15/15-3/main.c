#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>


enum
{
    DEC_BASE = 0,
    CHMOD = 0666
};

void
play (int proc, int semid, int nproc)
{
    long val;
    int snd;

    struct sembuf sops;
    sops.sem_flg = 0;

    while (1) {
        sops.sem_num = proc;
        sops.sem_op = -1;

        if (semop(semid, &sops, 1) < 0) {
            _exit(EXIT_SUCCESS);
        }

        if (scanf("%ld", &val) <= 0) {
            _exit(EXIT_FAILURE);
        }

        printf("%d %ld\n", proc, val);
        fflush(stdout);

        long tmp = (long) nproc;
        snd = (int) (val % tmp);
        if (snd < 0) {
            snd += nproc;
        }

        sops.sem_num = snd;
        sops.sem_op = 1;
        semop(semid, &sops, 1);
    }
}

int
getval (char *str)
{
    char *eptr = NULL;
    errno = 0;
    long tmp = strtol(str, &eptr, DEC_BASE);
    if (errno || *eptr || eptr == str
            || (int) tmp != tmp) {
        exit(EXIT_SUCCESS);
    }
    return ((int) tmp);
}

int
main (int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Arguments err\n");
        exit(1);
    }

    int nproc = getval(argv[1]);
    key_t key = 1010;
    setbuf(stdin, NULL);

    struct sembuf sops;
    int semid = semget((key_t) key, nproc, CHMOD | IPC_CREAT);

    for (int i = 0; i < nproc; ++i) {
        semctl(semid, i, SETVAL, (int) 0);
    }

    for (int i = 0; i < nproc; ++i) {
        int pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Proc creature err\n");
            exit(EXIT_FAILURE);
        } else if (!pid) {
            play(i, semid, nproc);
            _exit(EXIT_SUCCESS);
        }
    }

    sops.sem_num = 0;
    sops.sem_op = 1;
    semop(semid, &sops, 1);

    wait(NULL);

    semctl(semid, 0, IPC_RMID, 0);

    while (wait(NULL) > 0) {}

    _exit(EXIT_SUCCESS);
}