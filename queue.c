#include<stdio.h>
#include<stdlib.h>

typedef struct qnode
{
    int data;
    struct qnode *next;
    struct qnode *prev;
};

typedef struct queue
{
    int count;
    struct qnode *front;
    struct qnode *rear;
};

// used to reverse the queue
typedef struct stack
{
    int data;
    struct stack *next;
    struct stack *prev;
};

struct queue * enqueue(struct queue *q, int x)
{
    struct qnode *temp;
    temp = (struct qnode*)malloc(sizeof(struct qnode));
    temp->data = x;
    temp->next = NULL;
    temp->prev = NULL;
    if(q == NULL){
        q = (struct queue*)malloc(sizeof(struct queue));
        q->front = q->rear = temp;
        q->count = 1;
        return q;
    }
    if(q->front == NULL){
        q->front = q->rear = temp;
        q->count = 1;
        return q;
    }
    temp->prev = q->rear;
    q->rear->next = temp;
    q->rear = temp;
    q->count++;
    return q;
}

int dequeue(struct queue **q){

    if(*q == NULL || (*q)->front == NULL){
        printf("queue is empty");
        return NULL;
    }
    int p;
    struct qnode * temp;
    temp = (*q)->front;
    p = temp->data;
    if(temp->next == NULL){
        (*q)->front = (*q)->rear = NULL;
        (*q)->count = 0;
        free(temp);
        return p;
    }
    (*q)->front = (*q)->front->next;
    (*q)->front->prev = NULL;
    (*q)->count++;
    free(temp);
    return p;
}

void print (struct queue *q){

    printf("\n");
    if(q == NULL || q->front == NULL){
        printf("queue is empty");
        return;
    }

    int p;
    struct queue * temp = NULL;
    while(q->front != NULL){
        p = dequeue(&q);
        temp = enqueue(temp, p);
        printf("%d->", p);
    }
    printf("NULL");

    while(temp->front != NULL){
        p = dequeue(&temp);
        q = enqueue(q, p);
    }
}

// 1.Swap first and last element in a queue.
void swapFirstAndLast (struct queue *q){

    printf("\n");
    if(q == NULL || q->front == NULL){
        printf("queue is empty");
        return;
    }

    int r;
    int f = dequeue(&q);
    struct queue * temp = NULL;
    while(q->front != NULL){
        r = dequeue(&q);
        temp = enqueue(temp, r);
    }

    q = enqueue(q, r);
    while(temp->front->next != NULL){
        r = dequeue(&temp);
        q = enqueue(q, r);
    }
    q = enqueue(q, f);
}


// 2.Delete the ith element from a queue.
void delete_i (struct queue *q, int n){

    if(q == NULL || q->front == NULL){
        printf("queue is empty");
        return;
    }

    if(n > q->count){
        printf("out of range");
        return;
    }

    int p;
    int i = 0;
    struct queue * temp = NULL;
    while(q->front != NULL){
        p = dequeue(&q);
        i++;
        if(i == n){
            continue;
        }
        temp = enqueue(temp, p);
    }

    while(temp->front != NULL){
        p = dequeue(&temp);
        q = enqueue(q, p);
    }
}

// 3.Delete all elements in a queue of value below average of all the elements.
void deletBelowAverage (struct queue *q){

    if(q == NULL || q->front == NULL){
        printf("queue is empty");
        return;
    }

    int p;
    float sum = 0;
    float avg = 0;
    int c = q->count;
    struct queue * temp = NULL;
    while(q->front != NULL){
        p = dequeue(&q);
        sum += p;
        temp = enqueue(temp, p);
    }

    avg = sum/c;

    while(temp->front != NULL){
        p = dequeue(&temp);
        if(p < avg){
            continue;
        }
        q = enqueue(q, p);
    }
}

// 4.Extract even values from a queue to another queue.
struct queue * extractEven (struct queue *q){

    if(q == NULL || q->front == NULL){
        printf("queue is empty");
        return;
    }

    int p;
    struct queue * temp = NULL;
    struct queue * even = NULL;
    while(q->front != NULL){
        p = dequeue(&q);
        if(p%2){
            temp = enqueue(temp, p);
        }
        else{
            even = enqueue(even, p);
        }
    }

    while(temp->front != NULL){
        p = dequeue(&temp);
        q = enqueue(q, p);
    }

    return even;
}

// 5.Reverse a queue in place >>> using stacks

// push in stack
struct stack * push(struct stack *s, int x)
{
    struct stack *temp;
    temp = (struct stack*)malloc(sizeof(struct stack));
    temp ->data = x;
    temp ->next = NULL;
    temp->prev = NULL;
    if(s == NULL){
        s = temp;
        return s;
    }
    temp->next = s;
    s->prev = temp;
    s = temp;
    return s;
}

// pop out from stack
int pop(struct stack **s){

    if(*s == NULL){
        return NULL;
    }
    int p;
    struct stack * temp;
    temp = *s;
    p = temp->data;
    if(temp->next == NULL){
        *s = NULL;
        free(temp);
        return p;
    }
    *s=temp->next;
    temp->next->prev = NULL;
    temp->next = NULL;
    free(temp);
    return p;
}

// reverse
void reverseQueue (struct queue *q){

    if(q == NULL || q->front == NULL){
        printf("queue is empty");
        return;
    }

    int p;
    struct stack * temp = NULL;
    while(q->front != NULL){
        p = dequeue(&q);
        temp = push(temp, p);
    }

    while(temp != NULL){
        p = pop(&temp);
        q = enqueue(q, p);
    }
}

int main()
{
    struct queue * q1 = NULL;
    int n, i, data;
    printf("enter number of queue1 elements: ");
    scanf("%d", &n);
    for(i=1; i<=n; i++){
        printf("%d: ", i);
        scanf("%d", &data);
        q1 = enqueue(q1, data);
    }

    printf("\n\nqueue1 is as follows: ");
    print(q1);

    swapFirstAndLast(q1);
    printf("\n\nqueue1 after swap is as follows: ");
    print(q1);

    printf("\n\nenter index of an element to delete: ");
    scanf("%d", &data);
    delete_i(q1, data);
    printf("\n\nqueue1 after delete is as follows: ");
    print(q1);

    deletBelowAverage(q1);
    printf("\n\nqueue1 after deleting below average elements is as follows: ");
    print(q1);

    struct queue * q2 = NULL;
    q2 = extractEven(q1);
    printf("\n\nqueue1 after extracting even elements is as follows: ");
    print(q1);
    printf("\n\neven elements queue is as follows: ");
    print(q2);

    reverseQueue(q1);
    printf("\n\nqueue1 after reverse is as follows: ");
    print(q1);

    return 0;
}
