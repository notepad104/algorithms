/*
 * C++ Program To Implement Binary Tree
 */
#include <iostream>
#include <cstdlib>
using namespace std;
/*
 * Node Declaration
 */
struct node
{
    int info;
    struct node * right;
    struct node * left;
}*root;
/*
 * Class Declaration
 */
class BinaryTree
{
	public:
		void insert(node *, node *);
		void preorder(node *);
		void inorder(node *);
		void postorder(node *);
		void display(node *, int);
		BinaryTree()
		{
		    root = NULL;
		}
};

void BinaryTree::insert(node *tree, node *newnode)
{
    if (root == NULL)
    {
        root = new node;
        root->info = newnode->info;
        root->left = NULL;
        root->right = NULL;
        cout<<"Root Node is Added"<<endl;
        return;
	}
	if (tree->info == newnode->info)
	{
		cout<<"Element already in the tree"<<endl;
		return;
	}
	if (tree->info > newnode->info)
	{
		if (tree->left != NULL)
		{
		    insert(tree->left, newnode);
		}
		else
		{
			tree->left = newnode;
            (tree->left)->left = NULL;
            (tree->left)->right = NULL;
            cout<<"Node Added To Left"<<endl;
            return;
		}
	}
	else
	{
	    if(tree->right != NULL)
	    {
            insert(tree->right, newnode);
		}
        else
        {
            tree->right = newnode;
            (tree->right)->left = NULL;
            (tree->right)->right = NULL;
            cout<<"Node Added To Right"<<endl;
            return;
        }
	}
}

void BinaryTree::preorder(node * tree)
{
    if (tree)
    {
        cout<<tree->info<<" ";
        preorder(tree->left);
        preorder(tree->right);
    }

}

void BinaryTree::inorder(node * tree)
{
    if (tree)
    {
        inorder(tree->left);
        cout<<tree->info<<" ";
        inorder(tree->right);
    }
}

void BinaryTree::postorder(node * tree)
{
    if (tree)
    {
        postorder(tree->left);
        postorder(tree->right);
        cout<<tree->info<<" ";
    }
}

/*
 * Display Tree Structure
 */
void BinaryTree::display(node *tree, int level)
{
	int i;
	if (tree != NULL)
	{
		display(tree->right, level+1);
		cout<<endl;
		if (tree == root)
			cout<<"Root->:  ";
		else
		{
		    for (i = 0;i < level;i++)
			    cout<<"       ";
		}
		cout<<tree->info;
		display(tree->left, level+1);
	}
}
int main()
{
	int choice, num;
	node *temp;
    BinaryTree bt;
	while (1)
	{
        cout<<"-----------------"<<endl;
		cout<<"Operations on Binary Tree"<<endl;
		cout<<"-----------------"<<endl;
		cout<<"1.Insert Element "<<endl;
		cout<<"2.Inorder Traversal"<<endl;
		cout<<"3.Preorder Traversal"<<endl;
		cout<<"4.Postorder Traversal"<<endl;
		cout<<"5.Display Binary Tree"<<endl;
		cout<<"6.Quit"<<endl;
		cout<<"Enter your choice : ";
		cin>>choice;
		switch(choice)
		{
		case 1:
		    temp = new node;
		    cout<<"Enter the number to be inserted : ";
			cin>>temp->info;
			bt.insert(root, temp);
			break;
	    case 2:
		 	cout<<"Inorder Traversal:"<<endl;
			bt.inorder(root);
			cout<<endl;
			break;
		case 3:
            cout<<"Preorder Traversal:"<<endl;
			bt.preorder(root);
            cout<<endl;
			break;
		case 4:
			cout<<"Postorder Traversal:"<<endl;
 			bt.postorder(root);
			cout<<endl;
			break;
		case 5:
		    bt.display(root, 1);
		    cout<<endl;
		    break;
		case 6:
			exit(1);
		default:
			cout<<"Wrong choice"<<endl;
		}
	}
    return 0;
}
