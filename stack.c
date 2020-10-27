#include<stdio.h>
#include<stdlib.h>

typedef struct stack
{
    int data;
    struct stack *next;
    struct stack *prev;
};

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


// 1. Get the maximum element in a stack.
int maximum (struct stack *s){

    if(s == NULL){
        printf("stack is empty");
        return NULL;
    }
    int m = 0;
    int p;
    struct stack * temp = NULL;
    do{
        p = pop(&s);
        if(m < p){
            m = p;
        }
        temp = push(temp, p);
    }
    while(s != NULL);

    do{
        p = pop(&temp);
        s = push(s, p);
    }
    while(temp != NULL);

    return m;
}

// 2. Get the average of the elements in a stack.
float average (struct stack *s){

    if(s == NULL){
        printf("stack is empty");
        return;
    }
    int p;
    int sum = 0;
    int count = 0;
    struct stack * temp = NULL;
    do{
        p = pop(&s);
        sum += p;
        count++;
        temp = push(temp, p);
    }
    while(s != NULL);

    do{
        p = pop(&temp);
        s = push(s, p);
    }
    while(temp != NULL);

    return sum/count;
}


// 3. Check if two stacks are equal.
int equal (struct stack *s1, struct stack *s2){

    int e = 0; // o not equal, 1 equal

    if(s1 == NULL || s2 == NULL){
        printf("\none of the stacks is empty!");
        return 0;
    }

    int p1, p2;
    int f = 0;
    struct stack * temp1 = NULL;
    struct stack * temp2 = NULL;
    do{
        p1 = pop(&s1);
        p2 = pop(&s2);
        temp1 = push(temp1, p1);
        temp2 = push(temp2, p2);
        if(p1 != p2){
            f = 1;
            break;
        }
    }
    while(s1 != NULL && s2 != NULL);

    if((s1 != NULL || s2 != NULL) || (f == 1)){
        //printf("\nnot equal");
        e = 0;
    }
    else{
        //printf("\nequal");
        e = 1;
    }

    do{
        p1 = pop(&temp1);
        p2 = pop(&temp2);
        s1 = push(s1, p1);
        s2 = push(s2, p2);
    }
    while(temp1 != NULL || temp2 != NULL);

    return e;
}


// 4. Check if two stacks are reverse to each other.
int areReverse (struct stack *s1, struct stack *s2){

    int r = 0; // 0 not reverse, 1 reverse

    if(s1 == NULL || s2 == NULL){
        printf("\none of the stacks is empty!");
        return r;
    }

    int p1;
    struct stack * temp1 = NULL;
    do{
        p1 = pop(&s1);
        temp1 = push(temp1, p1);
        }
    while(s1 != NULL);

    r = equal(temp1, s2);

    do{
        p1 = pop(&temp1);
        s1 = push(s1, p1);
    }
    while(temp1 != NULL);

    /*if(r = 0){
        printf("\nnot reverse to each other");
    }
    else{
        printf("\nare reverse to each other");
    }*/

    return r;
}


// 5. Check if the sum of the upper half of a stack is the same as the sum of the lower half.
void upperHalfEqualLowerHalf (struct stack *s){

    if(s == NULL){
        printf("stack is empty");
        return;
    }

    int p;
    int i = 1;
    int sum1 = 0;
    int sum2 = 0;
    int count = 0;
    struct stack * temp = NULL;
    do{
        p = pop(&s);
        temp = push(temp, p);
        count++;
    }
    while(s != NULL);

    do{
        p = pop(&temp);
        s = push(s, p);
        if(i <= count/2){
            sum1 += p;
        }
        else{
            sum2 += p;
        }
        i++;
    }
    while(temp != NULL);

    if(sum1 != sum2){
        printf("\nsum of upper half doesn't equal sum of lower half");
    }
    else{
        printf("\nsum of upper half equals sum of lower half");
    }
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

    int max = maximum(s1);
    printf("\n\nmaximum of stack1 is: %d", max);

    float avg = average(s1);
    printf("\n\naverage of stack1 is: %f", avg);

    printf("\n\nchecking if s1 and s2 are equal ...");
    int e = equal(s1, s2);
    if(e == 1){
        printf("\nequal");
    }
    else{
        printf("\nnot equal");
    }

    printf("\n\nchecking if s1 and s2 are reverse to each other ...");
    int r = areReverse(s1, s2);
    if(r == 1){
        printf("\nare reverse to each other");
    }
    else{
        printf("\nnot reverse to each other");
    }

    printf("\n\nchecking if the sum of the upper half of a s1 is the same as the sum of the lower half ...");
    upperHalfEqualLowerHalf(s1);

    printf("\n\nstack1 is as follows: ");
    print(s1);

    printf("\n\nstack2 is as follows: ");
    print(s2);

    return 0;
}
