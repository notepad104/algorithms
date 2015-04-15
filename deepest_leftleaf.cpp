/* 
 * C++ program to Find Deepest Left Leaf in a Binary Tree
 */
#include <cstdio>
#include <iostream>
using namespace std;

/* 
 * Node Declaration
 */ 
struct Node
{
    int val;
    Node *left, *right;
};
 
Node *newNode(int data)
{
    Node *temp = new Node;
    temp->val = data;
    temp->left = temp->right =  NULL;
    return temp;
}
 
// find deepest leaf node.
void deepestLeftLeafUtil(Node *root, int lvl, int *maxlvl, bool isLeft, Node **resPtr)
{
    if (root == NULL)
        return;
    if (isLeft && !root->left && !root->right && lvl > *maxlvl)
    {
        *resPtr = root;
        *maxlvl = lvl;
        return;
    }
 
    deepestLeftLeafUtil(root->left, lvl + 1, maxlvl, true, resPtr);
    deepestLeftLeafUtil(root->right, lvl + 1, maxlvl, false, resPtr);
}
 
// implement deepestLeftLeafUtil.
Node* deepestLeftLeaf(Node *root)
{
    int maxlevel = 0;
    Node *result = NULL;
    deepestLeftLeafUtil(root, 0, &maxlevel, false, &result);
    return result;
}
 
// Main
int main()
{
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->right->left = newNode(5);
    root->right->right = newNode(6);
    root->right->left->right = newNode(7);
    root->right->right->right = newNode(8);
    root->right->left->right->left = newNode(9);
    root->right->right->right->right = newNode(10);
 
    Node *result = deepestLeftLeaf(root);
    if (result)
        cout << "The deepest left child is " << result->val;
    else
        cout << "There is no left leaf in the given tree";
 
    return 0;
}
