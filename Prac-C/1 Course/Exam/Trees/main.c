#include <stdio.h>
#include <stdlib.h>

struct list{
    int data;
    struct list *next;
};

struct list *pair(struct list *head, int n){
    struct list *tmp=head;
    while(n>0){
        tmp=tmp->next;
        --n;
    }
    return tmp;
}

struct list *swap(struct list *head){
    struct list *tmp=head;
    struct list *tmp1=head;
    struct list *tmp2=NULL;
    int len=0;
    while(tmp){
        ++len;
        tmp=tmp->next;
    }
    //printf("%d\n", len);
    for(int i=0; i<len/2; i++){
        tmp1=head;
        tmp2=head->next;
        int j=i-1;
        while(j>0){
            tmp1=tmp1->next;
            --j;
        }
        j=len-i-2;
        while(j>0){
            tmp2=tmp2->next;
            --j;
        }
        tmp=tmp2->next;
        tmp2.next=tmp1;
        tmp1->next.next=tmp;
    }
}

int main(void){
    struct list l[]={{7611, &l[1]}, {-1729, NULL}};
    struct list *head=swap(l);
    return 0;
}
