#include <stdio.h>
#include <stdlib.h>

struct tree { int x; struct tree *left, *right; };

void print_tree(struct tree *t){
    if(t){
        print_tree(t->left);
        printf("%d ", t->x);
        print_tree(t->right);
        free(t);
    }
}

int is_subset(int size, struct tree *t1, struct tree *t2){
    if(t2&&t1){
        return((t1->x==t2->x)&&(is_subset(size-1, t1->left, t2->left))&&(is_subset(size-1, t1->right, t2->right)));
    }
    else if(t1){
        free(t1);
        return 0;
    }
    else if(t2){
        free(t2);
        return 1;
    }

    else if(size<0)
        return 1;
    else return 1;
}
