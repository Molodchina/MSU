#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>



enum
{
    DEC_BASE = 0,
    CHMOD = 0666,
    SHM_LEN = 2 * sizeof(char) + 2 * sizeof(int)
};

int
place (int val, int nproc)
{
    long long tmp = (val % nproc);
    tmp *= (val % nproc);
    tmp %= nproc;
    tmp *= (val % nproc);
    tmp %= nproc;
    tmp *= (val % nproc);
    tmp %= nproc;
    return ((int) tmp);
}

void
play (int proc, int semid, char *shmaddr, int maxval, int nproc)
{
    int val, snd;
    char *str = calloc(SHM_LEN + 1, sizeof(*str));

    struct sembuf sops;
    sops.sem_flg = 0;

    while (1) {
        sops.sem_num = proc - 1;
        sops.sem_op = -1;

        if (semop(semid, &sops, 1) < 0) {
            free(str);
            _exit(EXIT_SUCCESS);
        }

        strcpy(str, shmaddr);
        sscanf(str, "%d %d", &val, &snd);

        printf("%d %d %d\n", proc, val++, snd);
        fflush(stdout);

        snd = place(val, nproc);
        if (val > maxval) {
            free(str);
            _exit(EXIT_FAILURE);
        }
        sprintf(str, "%d %d", val, proc);
        strcpy(shmaddr, str);

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
    if (argc < 4) {
        fprintf(stderr, "Arguments err\n");
        exit(1);
    }

    int nproc = getval(argv[1]);
    key_t key = (key_t) getval(argv[2]);
    int maxval = getval(argv[3]);

    struct sembuf sops;
    char *str = calloc(SHM_LEN + 1, sizeof(*str));

    int semid = semget((key_t) key, nproc, CHMOD | IPC_CREAT | IPC_EXCL);
    int shmid = shmget((key_t) key, SHM_LEN, CHMOD | IPC_CREAT | IPC_EXCL);
    char *shmaddr = shmat(shmid, NULL, 0);

    for (int i = 0; i < nproc; ++i) {
        semctl(semid, i, SETVAL, (int) 0);
    }

    for (int i = 1; i <= nproc; ++i) {
        int pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Proc creature err\n");
            exit(EXIT_FAILURE);
        } else if (!pid) {
            play(i, semid, shmaddr, maxval, nproc);
            _exit(EXIT_SUCCESS);
        }
    }

   sprintf(str, "%d %d", 0, 0);
    strcpy(shmaddr, str);

    sops.sem_num = 0;
    sops.sem_op = 1;
    semop(semid, &sops, 1);

    wait(NULL);

    semctl(semid, 0, IPC_RMID, 0);

    while (wait(NULL) > 0) {}

    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);

    _exit(EXIT_SUCCESS);
}
