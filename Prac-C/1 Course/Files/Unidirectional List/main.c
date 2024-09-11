#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in, *out;
int len;

typedef struct Node{
    int value;
    struct Node *next;
} Node;

int pop(Node **head) {
    Node* prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->value;
    (*head) = (*head)->next;
    free(prev);
    return val;
}

Node* getNth(Node* head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    return head;
}

int deleteNth(Node **head, int n) {
    if (n==0){
        return pop(head);
    }
    else{
        Node *prev = getNth(*head, n-1);
        Node *elm  = prev->next;
        int val=elm->value;

        prev->next = elm->next;
        free(elm);
        return val;
    }
}

/*
void insert(Node *head, unsigned n, int val) {
    unsigned i = 0;
    Node *tmp = NULL;
    while (i < n && head->next) {
        head = head->next;
        i++;
    }
    tmp = (Node*) malloc(sizeof(Node));
    tmp->value = val;
    if (head->next) {
        tmp->next = head->next;
    } else {
        tmp->next = NULL;
    }
    head->next = tmp;
}

Node* getLastButOne(Node* head) {
    if (head == NULL) {
        exit(-2);
    }
    if (head->next == NULL) {
        return NULL;
    }
    while (head->next->next) {
        head = head->next;
    }
    return head;
}

void deleteNth(Node **head, int n){
    if (n==0){
        return pop(head);
    }
    else{
        Node *prev = getNth(*head, n-1);
        Node *elm  = prev->next;
        prev->next = elm->next;
        free(elm);
    }
}

Node* getLast(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

void pushBack(Node *head, int value) {
    Node *last = getLast(head);
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = value;
    tmp->next = NULL;
    last->next = tmp;
}*/

void push(Node **head, int data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

void deleteList(Node **head) {
    Node* prev = NULL;
    while ((*head)->next) {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev);
    }
    free(*head);
}

void fromFile(Node **head){
    int c;
    in=fopen("input.txt", "r");
    out=fopen("output.txt", "w");
    fscanf(in, "%d", &c);
    while(c!=-1){
        push(head, c);
        len++;
        fscanf(in, "%d", &c);
    }
    return;
}

void printLinkedList(Node *head){
    /*while(head){
        fprintf(out, "%d ", head->value);
        head = head->next;
    }*/
    for(int i=len-1; i>=0; i--)
        fprintf(out, "%d ", deleteNth(&head, i));
    fclose(in);
    fclose(out);
}

int main(void){
    Node* head=NULL;
    Node* temp=NULL;
    int c, val;
    fromFile(&head);
    fscanf(in, "%d", &c);
    while(c!=-1){
        temp=head;
        int i=0;
        while(temp){
            val=temp->value;
            temp=temp->next;
            if(val==c){
                val=deleteNth(&head, i);
                len--;
                i--;
            }
            i++;
        }
        fscanf(in, "%d", &c);
    }
    printLinkedList(head);
}
