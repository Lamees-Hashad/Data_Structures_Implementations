#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* next;
};


// a.count number of elements
int count(struct Node *head){
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


// b.make a copy of a linked list
struct Node* Copy(struct Node* head)
{
	struct Node* p = head;
	struct Node* newlist = NULL;
	struct Node* tail = NULL;

	while (p != NULL)
	{
		//first node
		if (newlist == NULL)
		{
			newlist = (struct Node*)malloc(sizeof(struct Node));
			newlist->data = p->data;
			newlist->next = NULL;
			tail = newlist;
		}
		// rest of nodes
		else
		{
			tail->next = (struct Node*)malloc(sizeof(struct Node));
			tail = tail->next;
			tail->data = p->data;
			tail->next = NULL;
		}
		p = p->next;
	}

	return newlist;
}

// c.maximum
int max(struct Node* head){

    struct Node* p = head;

    int m = 0;
    while (p != NULL){

        if (p->data > m){
            m = p->data;
        }
        p = p->next;
    }

    return m;
}


// c.minimum
int min(struct Node* head){

    struct Node* p = head;

    int m = p->data;
    while (p != NULL){

        if (p->data < m){
            m = p->data;
        }
        p = p->next;
    }

    return m;
}


// c.average
float avg(struct Node* head){

    struct Node* p = head;

    float s = 0;
    int c = count(head);
    while (p != NULL){
        s=s+p->data;
        p = p->next;
    }

    return s/c;
}


// d. display kth element
void displayk(struct Node* head, int k){

   struct Node* p = head;

   while(k!=1){
    k--;
    p=p->next;
   }

   printf("\n%d", p->data);
}


// e. copy array of n values to a linked list
struct Node* Copyn(int a[], int n)
{

	struct Node* newlist = NULL;
	struct Node* tail = NULL;
    int i;
	for (i = 0; i<n; i++)
	{
		// first node
		if (newlist == NULL)
		{
			newlist = (struct Node*)malloc(sizeof(struct Node));
			newlist->data = a[i];
			newlist->next = NULL;
			tail = newlist;
		}
		// rest of nodes
		else
		{
			tail->next = (struct Node*)malloc(sizeof(struct Node));
			tail = tail->next;
			tail->data = a[i];
			tail->next = NULL;
		}
	}

	return newlist;
}


// f. sorted linked list
void sort(struct Node* head, int n){

    struct Node *temp;
    int k, i, t;
    for(k=1; k<=n-1; k++){
        temp = head;
        for(i=0; i<=n-k-1; i++){
            if(temp->data > temp->next->data){
                t = temp->data;
                temp->data = temp->next->data;
                temp->next->data = t;
            }
            temp=temp->next;
        }
    }
}


// g. swap two adjacent nodes
struct Node* swap_adj_nodes(struct Node* head, int n){

    struct Node *p1, *n1, *n2, *temp;
    int c = count(head);
    if(n>=c){
        printf("\n\ncan't swap");
        return head;
    }

    temp = head;
    n1 = NULL;
    p1 = NULL;
    n2 = NULL;

    int i=1;

    while(i<=c){

        if(i==n-1){
          p1 = temp;
        }

        if(i==n){
          n1 = temp;
        }

        if(i==n+1){
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

    n1->next = n2->next;
    n2->next = n1;

    return head;

}


// h. swap node m and node n
struct Node* swap_node(struct Node* head, int n, int m){

    struct Node *p1, *p2, *n1, *n2, *temp;
    int c = count(head);
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

    temp = n1->next;
    n1->next = n2->next;
    n2->next = temp;

    return head;

}


// i. reverse a linked list
struct Node* reverse(struct Node* head){

    int c = count(head);
    int i=1, j=c;

    while(i <= c/2){
        head = swap_node(head, i, j);
        i++;
        j--;
    }

    return head;
}


// j. concatenate two linked list
struct Node* concatenate(struct Node* head1, struct Node* head2){

    struct Node *tail1, *temp;

    temp = head1;
    while(temp != NULL){
        if(temp->next == NULL){
            tail1 = temp;
        }
        temp = temp->next;
    }

    tail1->next = head2;

    return head1;
}


// k. combine two oreded linked lists
struct Node* combine(struct Node* head1, struct Node* head2){

    struct Node *temp;

    struct Node *newlist = Copy(head1);
    temp = Copy(head2);
    newlist = concatenate(newlist, temp);
    int n = count(newlist);
    sort(newlist, n);

    return newlist;
}


// l. union of two linked lists
struct Node* unioned(struct Node* head1, struct Node* head2)
{
    struct Node* p = head1;
	struct Node* newlist = NULL;
	struct Node* tail = NULL;
	struct Node* temp;

	while (p != NULL)
	{
		// first node
		if (newlist == NULL)
		{
			newlist = (struct Node*)malloc(sizeof(struct Node));
			newlist->data = p->data;
			newlist->next = NULL;
			tail = newlist;
		}
		// rest of nodes
		else
		{
			tail->next = (struct Node*)malloc(sizeof(struct Node));
			tail = tail->next;
			tail->data = p->data;
			tail->next = NULL;
		}
		p = p->next;
	}

	p = head2;
	while(p!= NULL){

        temp = newlist;
        int d = 0;
        while(temp != NULL){
            if(temp->data == p->data){
                d = 1;
                break;
            }
            temp = temp->next;
        }

        if(d == 1){
            p = p->next;
            continue;
        }
        tail->next = (struct Node*)malloc(sizeof(struct Node));
        tail = tail->next;
		tail->data = p->data;
		tail->next = NULL;
		p = p->next;

	}

	return newlist;
}


// m. move node m forward n positions
struct Node* move_forward(struct Node *head, int m, int n){

    int i=1;
    while(i<=n){
        head = swap_adj_nodes(head, m+i-1);
        i++;
    }

    return head;

}

// n. destroy a linked list
void destroy(struct Node *head){

    struct Node *temp, *p;
    p = head->next;
    while(p != NULL){
        temp = p->next;
        p->next = NULL;
        free(p);
        p = temp;
    }
    head->next = NULL;
    free(head);
}

void display(struct Node *head){

    struct Node *temp = head;
    while(temp != NULL){
        printf("%d->", temp->data);
        temp = temp->next;
    }
    printf("NULL");
}


int main()
{

	int ary1[]={10, 15, 4, 20};
    int ary2[]={8, 4, 2, 10};
    int s1 = sizeof(ary1)/sizeof(ary1[0]);
    int s2 = sizeof(ary2)/sizeof(ary2[0]);
    struct Node* list1 = Copyn(ary1, s1);
    struct Node* list2 = Copyn(ary2, s2);

    printf("\n\nlist1 is: ");
    display(list1);
    printf("\n\nlist2 is: ");
    display(list2);


	struct Node* dup = Copy(list1);

	printf("\n\ncopy of list1: ");
	display(dup);

    int m = max(list1);

    int s = min(list1);

    float a = avg(list1);

    printf("\n\nmaximum: %d\nminimum: %d\naverage: %f", m, s, a);

    int k;
    printf("\n\nenter number of an element to dispaly ");
    scanf("%d", &k);
    printf("\nkth element: ");
    displayk(list1, k);


    int c = count(list1);
    printf("\n\nnumber of node in list1: %d", c);
    sort(list1, c);

    printf("\n\nlist1 sorted: ");
    display(list1);

    int x,y;
    printf("\n\nenter two positions to swap: ");
    scanf("%d", &x);
    scanf("%d", &y);
    list1 = swap_node(list1, x, y);

    printf("\nlist1 after swapping: ");
    display(list1);

    printf("\n\nenter a position to swap it with the one after it: ");
    scanf("%d", &x);
    list1 = swap_adj_nodes(list1, x);

    printf("\nlist1 after swapping: ");
    display(list1);

    struct Node* ulist = unioned(list1, list2);
    printf("\n\nunion of list1 and list2: ");
    display(ulist);

    list1 = reverse(list1);
    printf("\n\nlist1 reversed: ");
    display(list1);

    struct Node* clist = combine(list1, list2);
    printf("\n\nlist1 and list 2 combined and ordered: ");
    display(clist);

    struct Node* conclist = concatenate(list1, list2);
    printf("\n\nlist2 concatenated to list1: ");
    display(list1);

    printf("\n\nenter number of node and number of positons to move it forward: ");
    scanf("%d%d", &x, &y);
    move_forward(list1, x, y);
    printf("\nlist1: ");
    display(list1);

    printf("\n\ndestroy list1: ");
    destroy(list1);
    display(list1);



	return 0;
}


