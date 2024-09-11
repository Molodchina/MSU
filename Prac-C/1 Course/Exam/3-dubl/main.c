#include <stdio.h>
#include <stdlib.h>

struct list{
	int key;
	struct list *next;
	struct list *sublist_head;
};

int len=0, brt=0;

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
    return brt;
}

void crt_list(struct list *garland){
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int len=0, j=0, fl=0, dp=0;
    char x;
    char **m=malloc(sizeof(char*));
    m[len]=malloc(sizeof(char));
    x=getchar();
    while(1){
        printf("----\n");
        if(x==EOF){
            m[len][j]='\0';
            j=0;
            ++len;
            m=realloc(m, sizeof(char*)*(len+1));
            break;
        }
        else if (x=='\n'){
            m[len][j]='\0';
            j=0;
            ++len;
            printf("----\n");
            m=realloc(m, sizeof(char*)*(len+1));
        }
        m[len][j]=x;
        printf("%c\n", x);
        ++j;
        m[len]=realloc(m[len], sizeof(char)*(j+1));
        x=getchar();
    }
    for(int i=0; i<len; i++){
        int sz=0;
        x=m[i][sz];
        while(x!='\0'){
            printf("%c", x);
            ++sz;
            x=m[i][sz];
        }
    }

    /*
    struct list **mas=malloc(sizeof(struct list*));
    int high=0;
    for(int i=0; i<len; i++){
        struct list *tmp=malloc(sizeof(struct list));
        int temp=0;
        while(x!='\0'){
            x=m[i][temp];
            if(atoi(x)){
                if(m[i][temp-1]=='→'){
                    tmp[j].key=atoi(x);
                    tmp[j].next=NULL;
                    tmp[j-1].next=&tmp[j];
                    tmp[j].sublist_head=NULL;
                    ++j;
                    tmp=realloc(tmp,sizeof(struct list)*(j+1));
                }
                else if((i==0)&&(temp==0)){
                    j=0;
                    tmp[j].key=atoi(x);
                    tmp[j].next=NULL;
                    tmp[j].sublist_head=NULL;
                    ++j;
                    tmp=realloc(tmp,sizeof(struct list)*(j+1));
                }
                else if((i>0)&&(m[i-1][temp]=='↓')){
                    mas[high]=tmp;
                    ++high;
                    mas=realloc(mas,sizeof(struct list*)*(high+1));
                    mas[high-1][dp].sublist_head=&tmp;
                    ++dp;
                    j=0;
                    tmp[j].key=atoi(x);
                    tmp[j].next=NULL;
                    tmp[j].sublist_head=NULL;
                    ++j;
                    tmp=realloc(tmp,sizeof(struct list)*(j+1));
                }
                else if(atoi(m[i][temp-1])){
                    if((i==0)||((i>0)&&(m[i-1][temp]!='↓'))) fl=-1;
                }
            }
        }
        if(j!=0){
            mas[high]=tmp;
            ++high;
            mas=realloc(mas,sizeof(struct list*)*(high+1));
        }
        free(tmp);
    }
    for(int i=0; i<high; i++){
        struct list *temp=&mas[i][0];
        while(temp){
            printf("%d\n", temp->key);
            temp=temp->next;
        }
    }
    garland=&mas;
    */
}

int main(void){
    struct list *example=NULL;
    crt_list(example);
    printf("%d", examine(example));
    return 0;
}
