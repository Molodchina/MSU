#include <stdio.h>
#include <stdlib.h>

struct list{
	int key;
	struct list *next;
	struct list *sublist_head;
};

int len=0, brt=0;

void clear(struct list *garland){
    struct list *tmp=garland;
    while(tmp){
        if(tmp->sublist_head)
            clear(tmp->sublist_head);
        tmp=tmp->next;
        free(garland);
    }
    free(tmp);
}

int check_len(struct list *garland){
    int len=0;
    while(garland){
        ++len;
        garland=garland->next;
    }
    return len;
}

int check_brt(struct list *garland){
    int brt=0;
    while(garland){
        brt+=garland->key;
        garland=garland->next;
    }
    return brt;
}

void push(struct list *garland){
    int tmp_brt=0, tmp_len;
    tmp_brt=check_brt(garland);
    tmp_len=check_len(garland);
    if(len<tmp_len){
        len=tmp_len;
        brt=tmp_brt;
    }
    else if(len==tmp_len)
        if(tmp_brt>brt) brt=tmp_brt;
}

void run_all(struct list *garland){
    while(garland){
        if(garland->sublist_head){
            push(garland->sublist_head);
            run_all(garland->sublist_head);
        }
        garland=garland->next;
    }
}

int examine(struct list *garland){
    push(garland);
    while(garland){
        if(garland->sublist_head){
            push(garland->sublist_head);
            run_all(garland->sublist_head);
        }
        garland=garland->next;
    }
    clear(garland);
    if(brt)
        return brt;
    else
        return -1;
}
