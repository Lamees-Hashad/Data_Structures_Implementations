#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	int data;
	struct node* left;
	struct node* right;
};


void BSTinorderPrint(struct node *root) {
  if (root != NULL) {
    BSTinorderPrint(root->left);
    printf("%d -> ", root->data);
    BSTinorderPrint(root->right);
  }
}


// 1.Insert an element in a BST.
struct node * BSTinsert(struct node *root, int x){

    if(root == NULL){

        struct node* temp = (struct node*)malloc(sizeof(struct node));
        temp->data = x;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    else if(x <= root->data){
        root->left = BSTinsert(root->left, x);
    }
    else{
        root->right = BSTinsert(root->right, x);
    }
    return root;
}

// 2.Count the number of nodes in a BST.
int BSTcount(struct node *root){

    if(root == NULL){
        return 0;
    }
    else{
        return 1 + BSTcount(root->left) + BSTcount(root->right);
    }
}

// 3. Get the sum of all elements in a BST.
int BSTsum(struct node *root){

    if(root == NULL){
        return 0;
    }
    else{
        return root->data + BSTsum(root->left) + BSTsum(root->right);
    }
}

// 4. Get the smallest element in a BST.
int BSTmin(struct node *root){

    if(root == NULL){
        printf("tree is empty");
        return;
    }
    else if(root->left == NULL){
        return root->data;
    }
    else{
        return BSTmin(root->left);
    }
}

// 5. Make a copy of a BST.
struct node * BSTcopy(struct node *root){

    if(root == NULL){
        return NULL;
    }
    struct node* temp = NULL;
    temp = BSTinsert(temp, root->data);

    temp->left = BSTcopy(root->left);
    temp->right = BSTcopy(root->right);

    return temp;
}

// 6. Check if two trees are identical.
bool BSTidentical(struct node *root1, struct node *root2){

    if (root1 == NULL && root2 == NULL){
        return true;
    }
    else if(root1 != NULL && root2 == NULL){
        return false;
    }
    else if(root1 == NULL && root2 != NULL){
        return false;
    }
    else{
        if(root1->data == root2->data && BSTidentical(root1->left, root2->left)
                                      && BSTidentical(root1->right, root2->right)){
            return true;
        }
        else{
            return false;
        }
    }
}

// 7. Reverse a tree into its mirror.
void BSTreverse(struct node *root){

    if(root == NULL){
        return;
    }

    BSTreverse(root->left);
    BSTreverse(root->right);

    struct node *temp = root->left;
    root->left = root->right;
    root->right = temp;
}

// 8. Delete an element from a BST.
struct node *BSTdelete(struct node *root, int x){

    if(root == NULL){
        printf("not found");
        return root;
    }
    else if(x == root->data){
        if(root->left == NULL && root->right == NULL){
            root = NULL;
            free(root);
        }
        else if(root->left == NULL && root->right != NULL){
            root->data = root->right->data;
            root->right = NULL;
            free(root->right);
        }
        else if(root->left != NULL && root->right == NULL){
            root->data = root->left->data;
            root->left = NULL;
            free(root->left);
        }
        else{
            int temp = BSTmin(root->right);
            root->data = temp;
            root->right = BSTdelete(root->right, temp);
        }
        return root;
    }
    else if(x < root->data){
        root->left = BSTdelete(root->left, x);
    }
    else{
        root->right = BSTdelete(root->right, x);
    }

    return root;
}

// 9. Get the depth of a node.
int BSTnodeDepth(struct node *root, int x){

    int d = 1;
    if(root == NULL){
        printf("not found");
        return 0;
    }
    else if(x == root->data){
        return d;
    }
    else if(x < root->data){
        d = BSTnodeDepth(root->left, x) + 1;
    }
    else{
        d = BSTnodeDepth(root->right, x) + 1;
    }
}

// 10. Check if two trees are mirrors.
bool BSTmirrors(struct node *root1, struct node *root2){

    if (root1 == NULL && root2 == NULL){
        return true;
    }
    else if(root1 != NULL && root2 == NULL){
        return false;
    }
    else if(root1 == NULL && root2 != NULL){
        return false;
    }
    else{
        if(root1->data == root2->data && BSTmirrors(root1->left, root2->right)
                                      && BSTmirrors(root1->right, root2->left)){
            return true;
        }
        else{
            return false;
        }
    }
}


int main()
{
    struct node* tree1 = NULL;
    int n, i, data;
    printf("enter number of tree1 nodes: ");
    scanf("%d", &n);
    for(i=1; i<=n; i++){
        printf("%d: ", i);
        scanf("%d", &data);
        tree1 = BSTinsert(tree1, data);
    }

    printf("\n\ntree1 inorder: ");
    BSTinorderPrint(tree1);

    int count = BSTcount(tree1);
    printf("\n\nnumber of nodes in tree1 = %d", count);

    int sum = BSTsum(tree1);
    printf("\n\nthe sum of tree1 nodes = %d", sum);

    int min = BSTmin(tree1);
    printf("\n\nthe min value in tree1 = %d", min);

    printf("\n\ncopying tree1 in tree2 ...");
    struct node* tree2 = NULL;
    tree2 = BSTcopy(tree1);

    printf("\n\ntree2 inorder: ");
    BSTinorderPrint(tree2);

    bool check = BSTidentical(tree1, tree2);
    printf("\n\nare tree1 and tree2 identical? ");
    printf(check? "true" : "false");

    printf("\n\nreversing tree1 in it's mirror ...");
    BSTreverse(tree1);
    printf("\n");
    BSTinorderPrint(tree1);

    check = BSTidentical(tree1, tree2);
    printf("\nafter reverse ... are tree1 and tree2 identical? ");
    printf(check? "true" : "false");

    bool check2 = BSTmirrors(tree1, tree2);
    printf("\nafter reverse ... are tree1 and tree2 mirrors? ");
    printf(check2? "true" : "false");

    printf("\n\nenter value of a node to delete from tree2: ");
    scanf("%d", &data);
    tree2 = BSTdelete(tree2, data);

    printf("\n\nafter deletion ... tree2 inorder: ");
    BSTinorderPrint(tree2);

    printf("\n\nenter node to find the depth of in tree2: ");
    scanf("%d", &data);
    int depth = BSTnodeDepth(tree2, data);
    printf("depth of %d is: %d", data, depth);

    return 0;
}
