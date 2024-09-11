#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int len=0, len2=0;

typedef struct Node{
    int value;
    struct Node *next;
} Node;

typedef struct Node2{
    int value;
    struct Node2 *next;
} Node2;

Node* getNth2(Node2* head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    return head;
}

int deleteNth2(Node2 **head, int n) {
    Node2 *prev = getNth2(*head, n-1);
    Node2 *elm  = prev->next;
    int val=elm->value;

    prev->next = elm->next;
    free(elm);
    return val;
}

void push(Node **head, int data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

void push2(Node2 **head, int data) {
    Node2 *tmp = (Node2*) malloc(sizeof(Node2));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

void fromFile(Node **head){
    int c;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &c);
    while(c!=-1){
        push2(head, c);
        len++;
        scanf("%d", &c);
    }
    return;
}

void fromFile2(Node2 **head){
    int c;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &c);
    while(c!=-1){
        push2(head, c);
        len++;
        scanf("%d", &c);
    }
    return;
}

void output(Node2 *head){
    for(int i=len-1; i>=0; i--)
        printf("%d ", deleteNth2(&head, i));
}

int main(void){
    Node* head=NULL;
    Node2* head2=NULL;
    Node2* tmp=NULL;
    int val, val2;
    fromFile(&head);
    fromFile2(&head2);
    while(head){
        val=head->value;
        head=head->next;
        int i=0;
        tmp=head2;
        while(tmp){
            val2=tmp->value;
            tmp=tmp->next;
            if(val==val2){
                val2=deleteNth2(&head2, i);
                len--;
                i--;
            }
            i++;
        }
    }
    output(head);
}
