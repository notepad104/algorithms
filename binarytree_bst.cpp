/*
 * C++ Program to Check if a Binary Tree is a BST 
 */
#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;
 
/* Node Declaration */
struct node
{
    int data;
    node* left;
    node* right;
};
 
int isBSTUtil(node* node, int min, int max);
 
/* Returns true if the given tree is a binary search tree */
int isBST(node* node)
{
    return(isBSTUtil(node, INT_MIN, INT_MAX));
}
 
/* Returns true if the given tree is a BST and its
   values are >= min and <= max. */
int isBSTUtil(struct node* node, int min, int max)
{
    if (node==NULL)
        return 1;
    if (node->data < min || node->data > max)
        return 0;
    return isBSTUtil(node->left, min, node->data - 1) &&  
            isBSTUtil(node->right, node->data + 1, max);
}
 
/* allocates a new node with the data and NULL left and right pointers. */
node* newNode(int data)
{
    node* nod = new node;
    nod->data = data;
    nod->left = NULL;
    nod->right = NULL;
    return nod;
}
 
/* main*/
int main()
{
    node *root = newNode(4);
    root->left = newNode(2);
    root->right = newNode(5);
    root->left->left = newNode(1);
    root->left->right = newNode(3);
    if (isBST(root))
        cout<<"The Given Binary Tree is a BST"<<endl;
    else
        cout<<"The Given Binary Tree is not a BST"<<endl;
    return 0;
}  
