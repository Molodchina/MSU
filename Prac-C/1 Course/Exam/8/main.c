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
    else if(t1)
        return 0;
    else if(t2)
        return 1;
    else if(size<0)
        return 1;
    else return 1;
}

int main(void){
    struct tree t1_4 = {6, 0, 0};
    struct tree t1_3 = {3, 0, &t1_4};
    struct tree t1_2 = {2, 0, &t1_3};
    struct tree t1 = {1, 0, &t1_2};

    struct tree t2_5= {5, 0, 0};
    struct tree t2_4 = {4, 0, &t2_5};
    struct tree t2_3 = {3, 0, &t2_4};
    struct tree t2_2 = {2, 0, &t2_3};
    struct tree t2 = {1, 0, &t2_2};

    print_tree(&t1);
    printf("\n");
    print_tree(&t2);
    printf("\n");
    if(is_subset(3, &t1, &t2))
        printf("YES");
    else
        printf("No");
    printf("\n");
    return 0;
}
