/* 
 * C++ Program to Implement Sorted Linked List into Balanced BST 
 */
#include<iostream>
#include<cstdlib>
using namespace std;
 
/* Link list node */
struct LNode
{
    int data;
    LNode* next;
};
 
/* A Binary Tree node */
struct TNode
{
    int data;
    TNode* left;
    TNode* right;
};


TNode* newNode(int data);
int countLNodes(LNode *head);
TNode* sortedListToBSTRecur(LNode **head_ref, int n);
 
 
/* counts the number of nodes in Linked List  */
TNode* sortedListToBST(LNode *head)
{
    int n = countLNodes(head);
    return sortedListToBSTRecur(&head, n);
}
 
/* constructs balanced BST and returns root of it. */
TNode* sortedListToBSTRecur(LNode **head_ref, int n)
{
    if (n <= 0)
        return NULL;
    TNode *left = sortedListToBSTRecur(head_ref, n/2);
    TNode *root = newNode((*head_ref)->data);
    root->left = left;
    *head_ref = (*head_ref)->next;
    root->right = sortedListToBSTRecur(head_ref, n-n/2-1);
    return root;
}
 
/* returns count of nodes in a given Linked List */
int countLNodes(LNode *head)
{
    int count = 0;
    LNode *temp = head;
    while(temp)
    {
        temp = temp->next;
        count++;
    }
    return count;
}
 
/* insert a node at the beginging of the linked list */
void push(LNode** head_ref, int new_data)
{
    LNode* new_node = new LNode;
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}
 
/* print nodes in a given linked list */
void printList(LNode *node)
{
    while(node!=NULL)
    {
        cout<<node->data<<"  ";
        node = node->next;
    }
}
 
/* allocates a new node with the data and NULL left and right pointers. */
 TNode* newNode(int data)
{
    TNode* node = new TNode;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
 
/* print preorder traversal of BST */
void preOrder(TNode* node)
{
    if (node == NULL)
        return;
    cout<<node->data<<"  ";
    preOrder(node->left);
    preOrder(node->right);
}
 
/* Main  */
int main()
{
    LNode* head = NULL;
    push(&head, 7);
    push(&head, 6);
    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
    cout<<"\n Given Linked List ";
    printList(head);
    TNode *root = sortedListToBST(head);
    cout<<"\n PreOrder Traversal of constructed BST ";
    preOrder(root);
    return 0;
}
