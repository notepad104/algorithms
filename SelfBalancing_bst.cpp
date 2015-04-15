/*
 *  C++ Program to Implement Self Balancing Binary Search Tree
 */
#include <iostream>
#include <cstdlib>
using namespace std;

/* Class SBBSTNode */

class SBBSTNode
{
    public:
        int height, data;
        SBBSTNode *left, *right;
         /* Constructor */
         SBBSTNode()
         {
             left = NULL;
             right = NULL;
             data = 0;
             height = 0;
         }

         /* Constructor */
         SBBSTNode(int n)
         {
             left = NULL;
             right = NULL;
             data = n;
             height = 0;
         }
};

/*
 * Class SelfBalancingBinarySearchTree
 */

class SelfBalancingBinarySearchTree
{
    private:
        SBBSTNode *root;
    public:
         /* Constructor */
         SelfBalancingBinarySearchTree()
         {
             root = NULL;
         }

         /* Function to check if tree is empty */
         bool isEmpty()
         {
             return root == NULL;
         }

         /* Make the tree logically empty */
         void makeEmpty()
         {
             root = NULL;
         }

         /* Function to insert data */
         void insert(int data)
         {
             root = insert(data, root);
         }

         /* Function to get height of node */
         int height(SBBSTNode *t)
         {
             return t == NULL ? -1 : t->height;
         }

         /* Function to max of left/right node */
         int max(int lhs, int rhs)
         {
             return lhs > rhs ? lhs : rhs;
         }

         /* Function to insert data recursively */
         SBBSTNode *insert(int x, SBBSTNode *t)
         {
             if (t == NULL)
                 t = new SBBSTNode(x);
             else if (x < t->data)
             {
                 t->left = insert(x, t->left);
                 if (height(t->left) - height(t->right) == 2)
                     if (x < t->left->data)
                         t = rotateWithLeftChild(t);
                     else
                         t = doubleWithLeftChild(t);
             }
             else if (x > t->data)
             {
                 t->right = insert(x, t->right);
                 if (height(t->right) - height(t->left) == 2)
                     if (x > t->right->data)
                         t = rotateWithRightChild(t);
                     else
                         t = doubleWithRightChild(t);
             }
             t->height = max(height(t->left), height(t->right)) + 1;
             return t;
         }

         /* Rotate binary tree node with left child */
         SBBSTNode *rotateWithLeftChild(SBBSTNode* k2)
         {
             SBBSTNode *k1 = k2->left;
             k2->left = k1->right;
             k1->right = k2;
             k2->height = max(height(k2->left), height(k2->right)) + 1;
             k1->height = max(height(k1->left), k2->height) + 1;
             return k1;
         }

         /* Rotate binary tree node with right child */
         SBBSTNode *rotateWithRightChild(SBBSTNode *k1)
         {
             SBBSTNode *k2 = k1->right;
             k1->right = k2->left;
             k2->left = k1;
             k1->height = max(height(k1->left), height(k1->right)) + 1;
             k2->height = max(height(k2->right), k1->height) + 1;
             return k2;
         }

         /*
          * Double rotate binary tree node: first left child
          * with its right child; then node k3 with new left child
          */
         SBBSTNode *doubleWithLeftChild(SBBSTNode *k3)
         {
             k3->left = rotateWithRightChild(k3->left);
             return rotateWithLeftChild(k3);
         }

         /*
          * Double rotate binary tree node: first right child
          * with its left child; then node k1 with new right child
          */
         SBBSTNode *doubleWithRightChild(SBBSTNode *k1)
         {
             k1->right = rotateWithLeftChild(k1->right);
             return rotateWithRightChild(k1);
         }

         /* Functions to count number of nodes */
         int countNodes()
         {
             return countNodes(root);
         }

         int countNodes(SBBSTNode *r)
         {
             if (r == NULL)
                 return 0;
             else
             {
                 int l = 1;
                 l += countNodes(r->left);
                 l += countNodes(r->right);
                 return l;
             }
         }

         /* Functions to search for an element */
         bool search(int val)
         {
             return search(root, val);
         }

         bool search(SBBSTNode *r, int val)
         {
             bool found = false;
             while ((r != NULL) && !found)
             {
                 int rval = r->data;
                 if (val < rval)
                     r = r->left;
                 else if (val > rval)
                     r = r->right;
                 else
                 {
                     found = true;
                     break;
                 }
                 found = search(r, val);
             }
             return found;
         }

         /* Function for inorder traversal */
         void inorder()
         {
             inorder(root);
         }

         void inorder(SBBSTNode *r)
         {
             if (r != NULL)
             {
                 inorder(r->left);
                 cout<<r->data<<"  ";
                 inorder(r->right);
             }
         }

         /* Function for preorder traversal */
         void preorder()
         {
             preorder(root);
         }
         void preorder(SBBSTNode *r)
         {
             if (r != NULL)
             {
                 cout<<r->data<<"  ";
                 preorder(r->left);
                 preorder(r->right);
             }
         }

         /* Function for postorder traversal */
         void postorder()
         {
             postorder(root);
         }
         void postorder(SBBSTNode *r)
         {
             if (r != NULL)
             {
                 postorder(r->left);
                 postorder(r->right);
                 cout<<r->data<<"  ";
             }
         }
};

int main()
{
    SelfBalancingBinarySearchTree sbbst;
    cout<<"SelfBalancingBinarySearchTree Test\n";
    int val;
    char ch;
    /*  Perform tree operations  */
    do
    {
        cout<<"\nSelfBalancingBinarySearchTree Operations\n";
        cout<<"1. Insert "<<endl;
        cout<<"2. Count nodes"<<endl;
        cout<<"3. Search"<<endl;
        cout<<"4. Check empty"<<endl;
        cout<<"5. Make empty"<<endl;
        int choice;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1 :
            cout<<"Enter integer element to insert: ";
            cin>>val;
            sbbst.insert(val);
            break;
        case 2 :
            cout<<"Nodes = " <<sbbst.countNodes()<<endl;
            break;
        case 3:
            cout<<"Enter integer element to search: ";
            cin>>val;
            if (sbbst.search(val))
                cout<<val<<" found in the tree"<<endl;
            else
                cout<<val<<" not found"<<endl;
            break;
        case 4 :
            cout<<"Empty status = ";
            if (sbbst.isEmpty())
                cout<<"Tree is empty"<<endl;
            else
                cout<<"Tree is non - empty"<<endl;
            break;
        case 5 :
            cout<<"\nTree cleared\n";
            sbbst.makeEmpty();
            break;
        default :
            cout<<"Wrong Entry \n ";
            break;
        }

        /*  Display tree*/
        cout<<"\nPost order : ";
        sbbst.postorder();
        cout<<"\nPre order : ";
        sbbst.preorder();
        cout<<"\nIn order : ";
        sbbst.inorder();
        cout<<"\nDo you want to continue (Type y or n) \n";
        cin>>ch;
    }
    while (ch == 'Y'|| ch == 'y');
    return 0;
}
