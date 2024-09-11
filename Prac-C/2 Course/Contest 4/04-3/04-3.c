#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

typedef struct Node
{
    int32_t key;
    int32_t l_node;
    int32_t r_node;
} Node;

Node
*read_node(int fdl, Node *head, int node_idx)
{
    if (head == NULL || node_idx == 0) {
        return NULL;
    }
    if (lseek(fdl, (off_t) (node_idx * sizeof(*head)),
            SEEK_SET) == -1) {
        return NULL;
    }
    if (read(fdl, head, sizeof(*head)) != sizeof(*head)) {
        return NULL;
    }
    return head;
}

void
make_node(int fdl, Node *head)
{
    if (head) {
        Node *l_node = calloc(1, sizeof(*l_node));
        Node *r_node = calloc(1, sizeof(*r_node));

        l_node = read_node(fdl, l_node, head->l_node);
        r_node = read_node(fdl, r_node, head->r_node);

        make_node(fdl, r_node);
        printf("%d ", head->key);
        make_node(fdl, l_node);

        free(l_node);
        free(r_node);
    }
}

int
main(int argc, char *argv[]) {
    int fdl = open(argv[1], O_RDWR);
    if (fdl == -1) {
        fprintf(stderr, "file open err\n");
        exit(1);
    }

    Node *head = calloc(1, sizeof(*head));
    if (read(fdl, head, sizeof(*head)) != sizeof(*head)) {
        exit(0);
    }
    make_node(fdl, head);
    putchar('\n');
    free(head);

    if (close(fdl) == -1) {
        fprintf(stderr, "file close err\n");
        exit(1);
    }
    return 0;
}