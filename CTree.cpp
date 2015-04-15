/*
 * C++ Program To Implement Cartesian Tree
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
/*
 * Node Declaration
 */
struct node
{
    int data;
    struct node* left;
    struct node* right;
};
/*
 * Class Declaration
 */
class CTree
{
	public:
		node *newNode (int);
		int mini(int [], int, int);
		node *buildTree (int [], int, int);
		void printInorder (node* node);
		void display(node *, int);
		CTree()
		{}
};

/*
 * Main Contains Menu
 */
int main()
{
	CTree ct;
	int i, n;
	cout<<"Enter number of elements to be inserted: ";
	cin>>n;
	int a[n];
	for(i = 0;i < n;i++)
	{
	    cout<<"Enter Element "<<i + 1<<" : ";
	    cin>>a[i];
	}
	node *root = ct.buildTree(a, 0, n - 1);
    cout<<"Cartesian tree Structure: "<<endl;
    ct.display(root,1);
    cout<<endl;
    cout<<"\n Inorder traversal of the constructed tree \n"<<endl;
    ct.printInorder(root);
    cout<<endl;
    return 0;
}

/*
 * Creating New Node
 */
node *CTree::newNode (int data)
{
    node* temp = new node;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

/*
 * Finding index of minimum element
 */
int CTree::mini(int arr[], int strt, int end)
{
    int i, min = arr[strt], minind = strt;
    for(i = strt + 1; i <= end; i++)
    {
        if(arr[i] < min)
        {
            min = arr[i];
            minind = i;
        }
    }
    return minind;
}

/*
 * Function for Building Tree
 */
node *CTree::buildTree (int inorder[], int start, int end)
{
    if (start > end)
        return NULL;
    int i = mini(inorder, start, end);
    node *root = newNode(inorder[i]);
    if (start == end)
        return root;
    root->left  = buildTree(inorder, start, i - 1);
    root->right = buildTree(inorder, i + 1, end);
    return root;
}

/*
 * InOrder Traversal
 */
void CTree::printInorder (struct node* node)
{
    if (node == NULL)
        return;
    printInorder (node->left);
    cout<<node->data<<" ";
    printInorder (node->right);
}

/*
 * Display Tree
 */
void CTree::display(node *ptr, int level)
{
    int i;
    if(ptr == NULL)
		return;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		cout<<endl;
	    for (i = 0;i < level;i++)
			    cout<<"       ";
		cout<<ptr->data;
		display(ptr->left, level + 1);
	}
}


//11   8 4 9 3 5 0 11 2 6 7 12
