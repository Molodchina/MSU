#include <stdio.h>
#include <stdlib.h>

struct tree { int x; struct tree *left, *right; };

void print_tree(struct tree *t){
    if(t){
        print_tree(t->left);
        printf("%d ", t->x);
        print_tree(t->right);
    }
}

int is_subset(int size, struct tree *t1, struct tree *t2){
    struct tree *tmp1=t1, *tmp2=t2;
    int size2=1, s_tmp=1;
    if(t1->x!=t2->x) return 0;
}

int main(void){
    struct tree t1_3 = {3, 0, 0};
    struct tree t1_2 = {2, 0, &t1_3};
    struct tree t1 = {1, 0, &t1_2};

    struct tree t2_5= {5, 0, 0};
    struct tree t2_4 = {4, 0, &t2_5};
    struct tree t2_3 = {3, 0, &t2_4};
    struct tree t2_2 = {2, 0, &t2_3};
    struct tree t2 = {1, 0, &t2_2};

    print_tree(&t1);
    print_tree(&t2);
    return 0;
}
