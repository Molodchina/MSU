#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <sys/msg.h>
#include <sys/types.h>



enum
{
    DEC_BASE = 0,
    CHMOD = 0666,
    MES_LEN = 2 * sizeof(char) + 2 * sizeof(long)
};

typedef struct Message
{
    long mtype;
    char data[MES_LEN];
} Message;

void
play (long proc, int msgid, int nproc, long maxval)
{
    Message message;
    int64_t tmp_mtype, val1, val2;
    while (1) {
        if (msgrcv(msgid, &message, sizeof(message)
                                    - sizeof(message.data), proc, 0) < 0) {
            exit(EXIT_SUCCESS);
        }

        sscanf(message.data, "%ld %ld", &val1, &val2);
        u_int64_t val3 = val1 + val2;

        printf("%ld %ld\n", proc - 1, val3);

        tmp_mtype = val3 % nproc + 1;
        if (val3 > maxval) {
            _exit(EXIT_FAILURE);
        }
        message.mtype = tmp_mtype;
        sprintf(message.data, "%ld %ld", val2, val3);
        msgsnd(msgid, &message, sizeof(message)
                                - sizeof(message.data), 0);
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

long
getvall (char *str)
{
    char *eptr = NULL;
    errno = 0;
    long long tmp = strtoll(str, &eptr, DEC_BASE);
    if (errno || *eptr || eptr == str
        || (long) tmp != tmp) {
        exit(EXIT_SUCCESS);
    }
    return ((long) tmp);
}

int
main (int argc, char *argv[])
{
    if (argc < 6) {
        fprintf(stderr, "Arguments err\n");
        exit(1);
    }

    key_t key = (key_t) getval(argv[1]);
    int nproc = getval(argv[2]);
    long value1 = getvall(argv[3]);
    long value2 = getvall(argv[4]);
    long maxval = getvall(argv[5]);

    int msgid = msgget(key, CHMOD | IPC_CREAT);
    Message message;

    for (int i = 1; i <= nproc; ++i) {
        int pid = fork();
        if (pid < 0) {
            msgctl(msgid, IPC_RMID, NULL);
            while (wait(NULL) > 0) {}
            _exit(EXIT_FAILURE);
        } else if (!pid) {
            play(i, msgid, nproc, maxval);
            _exit(EXIT_SUCCESS);
        }
    }

    sprintf(message.data, "%ld %ld", value1, value2);
    message.mtype = 1;
    msgsnd(msgid, &message, sizeof(message)
                            - sizeof(message.data), 0);

    wait(NULL);

    msgctl(msgid, IPC_RMID, NULL);

    while (wait(NULL) > 0) {}

    _exit(EXIT_SUCCESS);
}
