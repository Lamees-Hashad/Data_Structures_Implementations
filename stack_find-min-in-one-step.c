#include<stdio.h>
#include<stdlib.h>

// 6. I suggest to add a variable min to the structure of the stack, this variable holds the minimum value of the elements
// behind it (including it's own element), this way the minimum value of the stack is always accessible from the stack's
//head even if we pop elements from the stack later.

typedef struct stack
{
    int data;
    int min;
    struct stack *next;
    struct stack *prev;
};

struct stack * push(struct stack *s, int x)
{
    struct stack *temp;
    temp = (struct stack*)malloc(sizeof(struct stack));
    temp->data = x;
    temp->next = NULL;
    temp->prev = NULL;
    if(s == NULL){
        temp->min = x;
        s = temp;
        return s;
    }
    if(s->min > x){
        temp->min = x;
    }
    else{
        temp->min = s->min;
    }
    temp->next = s;
    s->prev = temp;
    s = temp;
    return s;
}

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

void print (struct stack *s){

    printf("\n");
    if(s == NULL){
        printf("stack is empty");
        return;
    }

    int p;
    struct stack * temp = NULL;
    do{
        p = pop(&s);
        temp = push(temp, p);
        printf("%d->", p);
    }
    while(s != NULL);
    printf("NULL");

    do{
        p = pop(&temp);
        s = push(s, p);
    }
    while(temp != NULL);
}


int minimum(struct stack * s){

    int m = s->min;
    return m;

}

void printmin (struct stack *s){

    printf("\n");
    if(s == NULL){
        printf("stack is empty");
        return;
    }

    int p;
    struct stack * temp = NULL;
    do{
        printf("%d->", s->min);
        p = pop(&s);
        temp = push(temp, p);
    }
    while(s != NULL);
    printf("NULL");

    do{
        p = pop(&temp);
        s = push(s, p);
    }
    while(temp != NULL);
}

int main()
{
    struct stack * s1 = NULL;
    struct stack * s2 = NULL;
    int n, i, data;
    printf("enter number of stack1 elements: ");
    scanf("%d", &n);
    for(i=1; i<=n; i++){
        printf("%d: ", i);
        scanf("%d", &data);
        s1 = push(s1, data);
    }

    printf("enter number of stack2 elements: ");
    scanf("%d", &n);
    for(i=1; i<=n; i++){
        printf("%d: ", i);
        scanf("%d", &data);
        s2 = push(s2, data);
    }

    printf("\n\nstack1 is as follows: ");
    print(s1);

    printf("\n\nstack2 is as follows: ");
    print(s2);

    int min1 = minimum(s1);
    printf("\nmin of stak1: %d", min1);
    int min2 = minimum(s2);
    printf("\nmin of stak2: %d", min2);


    printf("\n\nstack1 minimum values is as follows: ");
    printmin(s1);

    printf("\n\nstack2 minimum values is as follows: ");
    printmin(s2);


    return 0;
}
