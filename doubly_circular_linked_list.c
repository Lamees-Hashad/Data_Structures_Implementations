#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *prev;
	struct Node *next;
};

struct Node *initialize_CDLL(int x){

    struct Node* newlist = (struct Node*)malloc(sizeof(struct Node));
    newlist->data = x;
    newlist->prev = newlist;
    newlist->next = newlist;

    return newlist;
}

struct Node *insert_at_head_CDLL(struct Node *head, int x){

    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data=x;
    temp->next=head;
    temp->prev=head->prev;
    head->prev->next = temp;
    head->prev = temp;
    head = temp;

    return head;

}


int count_CDLL (struct Node *head){
   if (head == NULL){
        return 0;
   }
   struct Node *temp = head;
   int c = 0;
   do{
        c++;
        temp = temp->next;
   }
   while (temp != head);

   return c;
}


struct Node *insert_at_pos_CDLL(struct Node *head, int x, int pos){

    //make sure position is valid
    int c = count_CDLL(head);
    if(pos > c+1){
        printf("\nposition is out of range");
        return head;
    }

    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    struct Node *p = head;
    temp->data=x;
    temp->prev=NULL;
    temp->next=NULL;

    // if position at start of list
    if(pos == 1){
        temp->next=head;
        temp->prev=head->prev;
        head->prev->next = temp;
        head->prev = temp;
        head = temp;

        return head;
    }

    int i=1;

    //find the node previous to the position;
    while(i<pos-1){

        p=p->next;
        i++;
    }

    temp->prev = p;
    temp->next = p->next;
    p->next->prev = temp;
    p->next = temp;


    return head;

}


struct Node *delet_pos_CDLL(struct Node *head, int pos){

    //make sure position is valid
    int c = count_CDLL(head);
    if(pos > c){
        printf("\nposition is out of range");
        return head;
    }

    struct Node *temp = head;

    // if position at start of list
    if(pos == 1){
        head = head->next;
        head->prev = temp->prev;
        temp->prev->next = head;
        temp->prev = NULL;
        temp->next = NULL;
        free(temp);

        return head;
    }

    int i=1;

    // find node to be deleted
    while(i<pos){

        temp=temp->next;
        i++;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    temp->prev = NULL;
    temp->next = NULL;
    free(temp);

    return head;
}

void display_CDLL(struct Node *head){

    struct Node *p = head;

    printf("\n\ndouble linked list is as follows: ");
    do{
       printf("%d->", p->data);
        p = p->next;
    }
    while(p != head);

    printf("NULL");
}


// 4. check if CDLL is sorted
void check_sort_CDLL(struct Node *head){

    struct Node *p = head;
    printf("\n\nchecking if list is sorted ...");

    while(p != head->prev){
        if(p->data > p->next->data){
            printf("list is not sorted");
            return;
        }
        p = p->next;
    }

    printf("list is sorted");
}

float avg_CDLL(struct Node *head){

    struct Node *p = head;
    float s = 0;
    int c = count_CDLL(head);

    int i = 1;
    while(i <= c){
        s=s + p->data;
        p = p->next;
        i++;
    }

    return s/c;
}

// 5.
void elements_above_avg_CDLL(struct Node *head){

    struct Node *p = head;
    float a = avg_CDLL(head);

    printf("\n\nelements above average: ");
    do{
        if(p->data > a){
        printf("%d, ", p->data);
        }
        p = p->next;
    }
    while(p != head);
}

int isprime(int x){

    int prime = 0;
    int i;
    for(i=2; i<=x/2; i++){
        if(x%i == 0){
            return prime;
        }
    }
    prime = 1;
    return prime;
}


void prime_elements_CDLL(struct Node *head){

    struct Node *p = head;

    printf("\n\nprime elements are: ");
    do{
        if(isprime(p->data)){
        printf("%d, ", p->data);
        }
        p = p->next;
    }
    while(p != head);
}


void check_ifmirrored_CDLL(struct Node *head){

    struct Node *p, *t;
    p = head;
    t = head->prev;
    int c = count_CDLL(head);

    int i=1;
    while(i<=c/2){
        if(p->data != t->data){
            printf("\n\nlist is not mirrored");
            return;
        }
        p = p->next;
        t = t->prev;
        i++;
    }
    printf("\n\nlist is mirrored");
}


int main()
{
    int num_nodes, data, x;
    struct Node *list;
    printf("please enter number of nodes: ");
    scanf("%d", &num_nodes);
    printf("please enter data of first node: ");
    scanf("%d", &data);
    list = initialize_CDLL(data);
    int i;
    for(i = 1; i<num_nodes; i++){
        printf("enter data for node %d: ", i+1);
        scanf("%d", &data);
        list = insert_at_pos_CDLL(list, data, i+1);
    }

    display_CDLL(list);
    printf("\nenter data to insert at beginning of the list: ");
    scanf("%d", &data);
    list = insert_at_head_CDLL(list, data);
    display_CDLL(list);

    printf("\n\nenter node to be deleted: ");
    scanf("%d", &x);
    list = delet_pos_CDLL(list, x);
    display_CDLL(list);

    printf("\n\ncheck if sorted");
    check_sort_CDLL(list);
    display_CDLL(list);

    printf("\n\naverage of nodes is ...");
    float a = avg_CDLL(list);
    printf(" %f", a);

    elements_above_avg_CDLL(list);

    prime_elements_CDLL(list);

    check_ifmirrored_CDLL(list);


    return 0;
}

