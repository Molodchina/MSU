#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


typedef struct Node
{
    struct stat stb;
    char *s;
} Node;

int
comp(const void *s1, const void *s2)
{
    Node *e1 = (Node *)s1;
    Node *e2 = (Node *)s2;
    return strcmp(e1->s, e2->s);
}

int
main(int argc, char *argv[])
{
    if (argc < 1) {
        fprintf(stderr, "paths amount err\n");
        exit(1);
    }

    char fl_alrdy_written = 0;
    Node *paths = calloc(argc, sizeof(Node));
    size_t s_paths = 0;

    for (int i = 1; i < argc; ++i) {
        fl_alrdy_written = 0;
        struct stat stb;
        if (stat(argv[i], &stb) >= 0) {
            for (int j = 0; j < s_paths; ++j) {
                if (paths[j].stb.st_ino == stb.st_ino) {
                    if (strcmp(paths[j].s, argv[i]) < 0) {
                        paths[j].stb = stb;
                        fl_alrdy_written = 1;
                        break;
                    }
                    fl_alrdy_written = 1;
                    break;
                }
            }
            if (fl_alrdy_written != 1) {
                paths[s_paths].stb = stb;
                paths[s_paths].s = argv[i];
                ++s_paths;
            }
        }
    }

    qsort(paths, s_paths, sizeof(Node), comp);
    for (int i = 0; i < s_paths; ++i) {
        printf("%s\n", paths[i].s);
    }
    return 0;
}