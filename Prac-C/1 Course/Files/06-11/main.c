#include <stdio.h>
#include <stdlib.h>

FILE *in, *out;

typedef struct node_t {
    int value;
    struct node_t *prev, *next;
}node_t;

void output(node_t *heap, node_t **link, node_t *list){
    while(list){
        fprintf(out, "%d ", list->value);
        list = list->next;
    }
    free(heap);
    free(link);
    return;
}

int main(void){
    node_t *heap, **link, *list, *temp, *tail, *cx, *cy;
    int n=0, m=0, x=0, y=0;

    in=fopen("input.txt", "r");
    out=fopen("output.txt", "w");

    fscanf(in, "%d %d", &n, &m);

    heap = malloc(sizeof(node_t) * (n+5));
    link = malloc(sizeof(node_t *) * (n+5));

    tail = NULL;
    list = NULL;

    for(int i=1; i<n+1; i++) {
        temp=heap+n+5-i;
        temp->value = i;
        temp->next = NULL;
        temp->prev = tail;

        if (i==1)
            list = temp;
        else
            tail->next = temp;

        link[i] = temp;
        tail = temp;
    }

    while(m>0){
        fscanf(in, "%d %d", &x, &y);
        cx = link[x];
        if (cx != list){
            cy = link[y];
            if (cx->prev!=NULL) {cx->prev->next = cy->next;}
            if (cy->next!=NULL) {cy->next->prev = cx->prev;}
            cx->prev = NULL;
            cy->next = list;
            list->prev = cy;
            list = cx;
        }
        m--;
    }

    output(heap, link, list);

    fclose(in);
    fclose(out);
    return 0;
}
