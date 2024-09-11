#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <sys/msg.h>



enum
{
    DEC_BASE = 10,
    CHMOD = 0666,
    MES_LEN = 32
};

typedef struct Message
{
    long long mtype;
    char data[MES_LEN];
} Message;

void
play (long long proc, int msgid, long long nproc, long long maxval)
{
    Message message;
    long long tmp_mtype, val1, val2;
    while (1) {
        if (msgrcv(msgid, &message, MES_LEN, proc, 0) < 0) {
            exit(EXIT_SUCCESS);
        }

        sscanf(message.data, "%lld%lld", &val1, &val2);

        unsigned long long val3 = val1 + val2;

        printf("%lld %llu\n", proc - 1, val3);
        fflush(stdout);

        if (val3 > maxval) {
            _exit(EXIT_FAILURE);
        }

        tmp_mtype = (long) val3 % nproc + 1;
        message.mtype = tmp_mtype;
        sprintf(message.data, "%lld %lld", val2, val3);
        msgsnd(msgid, &message, sizeof(message)
                - sizeof(message.mtype), 0);
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

long long
getvalll (char *str)
{
    char *eptr = NULL;
    errno = 0;
    unsigned long long tmp = strtoull(str, &eptr, DEC_BASE);
    if (errno || *eptr || eptr == str
            || (long long) tmp != tmp) {
        exit(EXIT_FAILURE);
    }
    return ((long long) tmp);
}

int
main (int argc, char *argv[])
{
    if (argc < 6) {
        fprintf(stderr, "Arguments err\n");
        exit(1);
    }

    key_t key = (key_t) getval(argv[1]);
    long long nproc = getvalll(argv[2]);
    long long value1 = getvalll(argv[3]);
    long long value2 = getvalll(argv[4]);
    int64_t maxval = getvalll(argv[5]);

    int msgid = msgget(key, CHMOD | IPC_CREAT);
    Message message;

    for (int64_t i = 1; i <= nproc; ++i) {
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

    sprintf(message.data, "%lld %lld", value1, value2);
    message.mtype = 1;
    msgsnd(msgid, &message, sizeof(message)
            - sizeof(message.mtype), 0);

    wait(NULL);

    msgctl(msgid, IPC_RMID, NULL);

    while (wait(NULL) > 0) {}

    _exit(EXIT_SUCCESS);
}
