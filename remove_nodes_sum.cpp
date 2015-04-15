#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std; 
// A Binary Tree Node
struct Node
{
    int data;
    Node *left, *right;
};
 
// create a new Binary Tree node with given data
Node* newNode(int data)
{
    Node* node = new Node;
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
 
// Inorder traversal.
void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout<<root->data<<"  ";
        inorder(root->right);
    }
}
 
/* truncates the binary tree. */
Node *pruneUtil(Node *root, int k, int *sum)
{
    if (root == NULL)  
        return NULL;
    int lsum = *sum + (root->data);
    int rsum = lsum;
    root->left = pruneUtil(root->left, k, &lsum);
    root->right = pruneUtil(root->right, k, &rsum);
    *sum = max(lsum, rsum);
    if (*sum < k)
    {
        free(root);
        root = NULL;
    }
    return root;
}
 
Node *prune(Node *root, int k)
{
    int sum = 0;
    return pruneUtil(root, k, &sum);
}
 
// Main
int main()
{
    int k = 45;
    Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->left->left->left = newNode(8);
    root->left->left->right = newNode(9);
    root->left->right->left = newNode(12);
    root->right->right->left = newNode(10);
    root->right->right->left->right = newNode(11);
    root->left->left->right->left = newNode(13);
    root->left->left->right->right = newNode(14);
    root->left->left->right->right->left = newNode(15);
    cout<<"Tree before truncation"<<endl;
    inorder(root);
    root = prune(root, k);
    cout<<"\nTree after truncation\n";
    inorder(root);
    return 0;
}
