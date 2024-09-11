#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    long long value;
    struct Node *next;
} Node;

Node* push(Node *head, long long data) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->value = data;
    temp->next = NULL;

    if (!head) {
        return temp;
    }
    head->next = temp;
    head = temp;
    return head;
}

void Merge(Node *head1, Node *head2, Node** target) {
    Node *tmp_target = NULL;
    while (head1 && head2) {
        if(head1->value - head2->value <= 0) {
            tmp_target = push(tmp_target, head1->value);
            head1 = head1->next;
        }
        else{
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

void MergeSort(Node **head, int N) {
    Node *left = *head, *right = NULL, *tmp = *head;
    if (N <= 1) return;
    int mid = N / 2 -1;
    for (int i = 0; i < mid; ++i) {
        tmp = tmp->next;
    }
    right = tmp->next;
    tmp->next = NULL;
    ++mid;
    MergeSort(&left, mid);
    MergeSort(&right, N-mid);
    *head = NULL;
    Merge(left, right, head);
}

Node* getNth(Node* head, int f) {
    int counter = 0;
    while (counter < f && head) {
        head = head->next;
        counter++;
    }
    return head;
}

long long deleteNth(Node **head, int f) {
    Node *prev = getNth(*head, f-1);
    Node *elm  = prev->next;
    long long val=elm->value;

    prev->next = elm->next;
    free(elm);
    return val;
}

void output(Node *head){
    Node *tmp=NULL;
    while(head){
        printf("%lld ", head->value);
        head = head->next;
    }
    while(head){
        tmp=head;
        free(head);
        head = tmp->next;
    }
    free(tmp);
    return;
}

int main(void){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Node *head = NULL;
    Node *tmp_head = NULL;
    long long x = 0;
    int n=0;
    while (scanf("%lld", &x) == 1) {
        tmp_head = push(tmp_head, x);
        if (!head) head = tmp_head;
        ++n;
    }

    MergeSort(&head, n);
    output(head);
    return 0;
}
