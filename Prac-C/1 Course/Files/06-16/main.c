#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in, *out;
int n;

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

Node* push(Node **head, int data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
    return *head;
}

void fromFile(Node **head){
    long long c;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%lld", &c);
    while(scanf("%lld", &c)!=-1){
        push(head, c);
        n++;
    }
    return;
}

Node* getNth(Node* head, int f) {
    int counter = 0;
    while (counter < f && head) {
        head = head->next;
        counter++;
    }
    return head;
}

int deleteNth(Node **head, int f) {
    if (f==0){
        return pop(head);
    }
    else{
        Node *prev = getNth(*head, f-1);
        Node *elm  = prev->next;
        int val=elm->value;

        prev->next = elm->next;
        free(elm);
        return val;
    }
}

void output(Node *head){
    for(int i=n-1; i>=0; i--)
        fprintf(out, "%d ", deleteNth(&head, i));
    fclose(in);
    fclose(out);
}

void merge(Node *head1, Node *head2, Node** target) {
    Node *tmp_target = NULL;
    while (head1 && head2) {
        if (head1->value <= head2->value) {
            tmp_target = push(tmp_target, head1->value);
            head1 = head1->next;
        } else {
            tmp_target = push(tmp_target, head2->value);
            head2 = head2->next;
        }
        if (!*target) *target = tmp_target;
    }
    while (head1) {
        tmp_target = push(tmp_target, head1->value);
        head1 = head1->next;
    }
    if (!*target) *target = tmp_target;
    while (head2) {
        tmp_target = push(tmp_target, head2->value);
        head2 = head2->next;
    }
    if (!*target) *target = tmp_target;
}

void mergeSort(Node **head, int len) {
    Node *left = *head, *right = NULL, *tmp = *head;
    int mid=len/2;

    if(len<=1) return;
    for (int i=0; i<mid-1; ++i)
        tmp = tmp->next;
    right = tmp->next;
    tmp->next = NULL;

    mergeSort(&left, mid);
    mergeSort(&right, len-mid);
    *head = NULL;
    merge(left, right, head);
}

int main(void){
    Node* head=NULL;
    fromFile(&head);
    mergeSort(&head, n);
    output(head);
}
