/*
 *  C++ Program to Implement Weight Balanced Tree
 */
#include <iostream>
#include <cstdlib>
#define MAX_VALUE 65536
using namespace std;
/* Class WBTNode */
class WBTNode
{
    public:
        WBTNode *left;
        WBTNode *right;
        int weight, element;     

        /* Constructor */
         WBTNode(int theElement, int wt, WBTNode *lt, WBTNode *rt)
         {
             element = theElement;
             left = lt;
             right = rt;
             weight = wt;
         }
        /* Constructor */    
        WBTNode(int theElement, int wt)
        {
            WBTNode(theElement, wt, NULL, NULL);
        }
             
};
WBTNode *nullNode;
/* Class WeightBalancedTree */
class WeightBalancedTree
{
    private: 
        WBTNode *root;
    public:     
         /* Constructor */
        WeightBalancedTree()
        {
            root = nullNode;
        }

        /* Function to check if tree is empty */
        bool isEmpty()
        {
            return root == nullNode;
        }

        /* Make the tree logically empty */
        void makeEmpty()
        {
            root = nullNode;
        }

        /* Functions to insert data */
        void insert(int x, int wt)
        {
            root = insert(x, wt, root);
        }
        WBTNode *insert(int x, int wt, WBTNode *t)
        {
            if (t == nullNode)
                t = new WBTNode(x, wt, nullNode, nullNode);
            else if (x < t->element)
            {
                t->left = insert (x, wt, t->left);
                if (t->left->weight < t->weight)
                    t = rotateWithLeftChild (t);
            }
            else if (x > t->element)
            {
                t->right = insert (x, wt, t->right);
                if (t->right->weight < t->weight)
                    t = rotateWithRightChild (t);
            }
            return t;
        }

        /* Functions to delete data */
        void remove(int x)
        {
            if (isEmpty())
                cout<<"Tree Empty"<<endl;
            else if (search(x) == false)
                cout<<x <<" is not present"<<endl;
            else
            {             
                root = remove (x, root);
                cout<<x <<" deleted from the tree"<<endl;
            }
        }     

        WBTNode *remove(int x, WBTNode *t)
        {
            if (t != nullNode)
            {
                if (x < t->element)
                    t->left = remove (x, t->left);
                else if (x > t->element)
                    t->right = remove (x, t->right);
                else
                {
                    if (t->left->weight == 0)
                        t->left->weight = MAX_VALUE;
                    if (t->right->weight == 0)
                        t->right->weight = MAX_VALUE;
                    if (t->left->weight < t->right->weight)
                    {
                        t = rotateWithLeftChild(t);
                    }
                    else
                    {
                        t = rotateWithRightChild(t);
                    }
                    if (t != nullNode)     
                        t = remove( x, t );
                    else
                        t->left = nullNode;    
                }
            }
            return t;
        }     

        /* Rotate tree node with left child  */     
        WBTNode *rotateWithLeftChild (WBTNode *k2)
        {
            WBTNode *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            return k1;
        }
        
        /* Rotate tree node with right child */
        WBTNode *rotateWithRightChild (WBTNode *k1)
        {
            WBTNode *k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            return k2;
        }

        /* Functions to count number of nodes */
        int countNodes()
        {
            return countNodes(root);
        }

        int countNodes(WBTNode *r)
        {
            if (r == nullNode)
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

        bool search(WBTNode *r, int val)
        {
            bool found = false;
            while ((r != nullNode) && !found)
            {
                int rval = r->element;
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

        void inorder(WBTNode *r)
        {
            if (r != nullNode)
            {
                inorder(r->left);
                cout<<r->element<<"   ";
                inorder(r->right);
            }
        }

        /* Function for preorder traversal */
        void preorder()
        {
            preorder(root);
        }
        void preorder(WBTNode *r)
        {
            if (r != nullNode)
            {
                cout<<r->element<<"   ";
                preorder(r->left);             
                preorder(r->right);
            }
        }

        /* Function for postorder traversal */
        void postorder()
        {
            postorder(root);
        }

        void postorder(WBTNode *r)
        {
            if (r != nullNode)
            {
                postorder(r->left);             
                postorder(r->right);
                cout<<r->element<<"   ";
            }
        }         
};
     

/* Main Contains Menu */

int main()
{
    nullNode = new WBTNode(0, MAX_VALUE);
    nullNode->left = nullNode->right = nullNode;
    WeightBalancedTree wbt; 
    cout<<"Weight Balanced Tree Test\n";          
    int choice, val, wt;
    char ch;
    /*  Perform tree operations  */
    do    
    {
        cout<<"\nWeight Balanced Tree Operations\n";
        cout<<"1. Insert "<<endl;
        cout<<"2. Delete"<<endl;
        cout<<"3. Search"<<endl;
        cout<<"4. Count nodes"<<endl;
        cout<<"5. Check empty"<<endl;
        cout<<"6. Clear"<<endl;
        cout<<"Enter Your Choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1 : 
            cout<<"Enter integer element to insert: "; 
            cin>>val;
            cout<<"Enter weight of the element in int: ";
            cin>>wt;
            wbt.insert(val, wt);                     
            break;                          
        case 2 : 
            cout<<"Enter integer element to delete: ";
            cin>>val;
            wbt.remove(val);
            break;                         
        case 3 : 
            cout<<"Enter integer element to search: ";
            cin>>val;
            if (wbt.search(val) == true)
                cout<<"Element "<<val<<" found in the tree"<<endl;
            else
                cout<<"Element "<<val<<" not found in the tree"<<endl;
            break;                                         
        case 4 : 
            cout<<"Nodes = "<< wbt.countNodes();
            break;     
        case 5 : 
            if (wbt.isEmpty() == true)
                cout<<"Tree is empty"<<endl;
            else
                cout<<"Tree is non-empty"<<endl;
            break;
        case 6 : 
            cout<<"\nTree Cleared";
            wbt.makeEmpty();
            break;            
        default : 
            cout<<"Wrong Entry \n ";
            break;   
        }
        /*  Display tree  */ 
        cout<<"\nPost order : ";
        wbt.postorder();
        cout<<"\nPre order : ";
        wbt.preorder();    
        cout<<"\nIn order : "; 
        wbt.inorder();
        cout<<"\nDo you want to continue (Type y or n) \n";
        cin>>ch;                        
    } 
    while (ch == 'Y'|| ch == 'y');               
    return 0;
}
