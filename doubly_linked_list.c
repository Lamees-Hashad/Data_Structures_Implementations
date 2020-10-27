#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *prev;
	struct Node *next;
};

struct Node *initialize_DLL(int x){

    struct Node* newlist = (struct Node*)malloc(sizeof(struct Node));
    newlist->data = x;
    newlist->prev = NULL;
    newlist->next = NULL;

    return newlist;
}

struct Node *insert_at_head_DLL(struct Node *head, int x){

    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data=x;
    temp->prev=NULL;
    temp->next=head;
    head->prev = temp;
    head = temp;

    return head;

}


int count_DLL (struct Node *head){
   if (head == NULL){
        return 0;
   }
   struct Node *temp = head;
   int c = 0;
   while (temp != NULL){
        c++;
        temp = temp->next;
   }
   return c;
}


struct Node *insert_at_pos_DLL(struct Node *head, int x, int pos){

    //make sure position is valid
    int c = count_DLL(head);
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

    // if position is at the end of list
    if(c == pos-1){

        p->next = temp;
        temp->prev = p;
        return head;
    }

    temp->prev = p;
    temp->next = p->next;
    p->next->prev = temp;
    p->next = temp;


    return head;

}


struct Node *delet_pos_DLL(struct Node *head, int pos){

    //make sure position is valid
    int c = count_DLL(head);
    if(pos > c){
        printf("\nposition is out of range");
        return head;
    }

    struct Node *temp = head;

    // if position at start of list
    if(pos == 1){
        head = head->next;
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

    if(pos == c){
        temp->prev->next = NULL;
        temp->prev = NULL;
        free(temp);
        return head;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    temp->prev = NULL;
    temp->next = NULL;
    free(temp);

    return head;
}

void display_DLL(struct Node *head){

    struct Node *p = head;

    printf("\n\ndouble linked list is as follows: ");
    while(p != NULL){
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL");
}

void display_pos_DLL(struct Node *head, int m){

    struct Node *p = head;

    printf("\n\nelement m of list is: ");
    int i = 1;
    while(i<=m){
        if(i == m){
            printf("%d", p->data);
        }
        p = p->next;
        i++;
    }
}

struct Node *swap_first_last_DLL(struct Node *head){

    struct Node *first, *last, *temp;
    first = head;
    temp = first->next;
    last = head;

    while(last->next != NULL){
        last = last->next;
    }

    first->prev = last->prev;
    last->prev->next = first;
    first->next = NULL;
    last->prev = NULL;
    last->next = temp;
    temp->prev = last;
    head = last;

    return head;
}

// swap node m and node n
struct Node* swap_node_DLL(struct Node* head, int n, int m){

    struct Node *p1, *p2, *n1, *n2, *temp;
    int c = count_DLL(head);
    if(n>c || m>c || n==m){
        printf("\n\ncan't swap");
        return head;
    }

    int maxpos;
    if(m>n){
        maxpos = m;
    }
    else{
        maxpos = n;
    }

    temp = head;
    n1 = NULL;
    p1 = NULL;
    n2 = NULL;
    p2 = NULL;

    int i=1;

    while(i<=maxpos){

        if(i==n-1){
          p1 = temp;
        }

        if(i==n){
          n1 = temp;
        }

        if(i==m-1){
          p2 = temp;
        }

        if(i==m){
          n2 = temp;
        }

        temp=temp->next;
        i++;
    }

    if(p1 != NULL){
        p1->next = n2;
    }
    else{
        head = n2;
    }

    if(p2 != NULL){
        p2->next = n1;
    }
    else{
        head = n1;
    }

    //if one of the positions is last node
    if(n1->next == NULL){
        n1->prev = p2;
        n1->next = n2->next;
        n2->next->prev = n1;
        n2->prev = p1;
        n2->next = NULL;
        return head;
    }
    if(n2->next == NULL){
        temp = n1->next;
        n1->prev = p2;
        n1->next = NULL;
        n2->prev = p1;
        n2->next = temp;
        temp->prev = n2;
        return head;
    }

    temp = n1->next;
    n1->prev = p2;
    n1->next = n2->next;
    n2->next->prev = n1;
    n2->prev = p1;
    n2->next = temp;
    temp->prev = n2;

    return head;

}


// reverse a linked list
struct Node* reverse_DLL(struct Node* head){

    int c = count_DLL(head);
    int i=1, j=c;

    while(i <= c/2){
        head = swap_node_DLL(head, i, j);
        i++;
        j--;
    }

    return head;
}

// dispose
void dispose(struct Node *head){

    struct Node *p, *temp;
    p = head->next;

    while(p != NULL){
        temp = p->next;
        p->prev = NULL;
        p->next = NULL;
        free(p);
        p = temp;
    }

    head->next = NULL;
    free(head);
}



int main()
{
    int num_nodes, data, x, y;
    struct Node *list;
    printf("please enter number of nodes: ");
    scanf("%d", &num_nodes);
    printf("please enter data of first node: ");
    scanf("%d", &data);
    list = initialize_DLL(data);
    int i;
    for(i = 1; i<num_nodes; i++){
        printf("enter data for node %d: ", i+1);
        scanf("%d", &data);
        list = insert_at_pos_DLL(list, data, i+1);
    }

    display_DLL(list);
    printf("\n\nenter data to insert at beginning of the list: ");
    scanf("%d", &data);
    list = insert_at_head_DLL(list, data);
    display_DLL(list);

    printf("\n\nenter number of an element to display: ");
    scanf("%d", &x);
    display_pos_DLL(list, x);
    display_DLL(list);

    printf("\n\nenter node to be deleted: ");
    scanf("%d", &x);
    list = delet_pos_DLL(list, x);
    display_DLL(list);

    printf("\n\nswap first and last node");
    list = swap_first_last_DLL(list);
    display_DLL(list);

    printf("\n\nenter two positions to swap: ");
    scanf("%d%d", &x, &y);
    list = swap_node_DLL(list, x, y);
    display_DLL(list);

    printf("\n\nreverse list in place");
    list = reverse_DLL(list);
    display_DLL(list);

    dispose(list);
    display_DLL(list);

    return 0;
}
