/*
 * C++ Program to Implement Pagoda
 */
#include <iostream>
#include <cstdlib>
#define MAX_ELEMS 25
using namespace std;
/*
 * Node Declaration
 */
struct node
{
 	int k;
 	node *left;
 	node *right;
};
typedef node *tree;

/*
 * Merging two trees
 */
tree merge(tree a,tree b )
{
	tree bota, botb, r, temp;
	if (a == NULL) 
	    return b;
	else if (b == NULL) 
	    return a;
	else	
	{
	    bota = a->right;
	    a->right = NULL;
	    botb = b->left;	
	    b->left = NULL;
	    r = NULL;
		while (bota != NULL && botb != NULL)
		{
			if (bota->k < botb->k) 
			{
				temp = bota->right;
				if (r == NULL)	
				    bota->right = bota;
				else	
				{
					bota->right = r->right;
					r->right = bota;
				}
				r = bota;
				bota = temp;
			}
			else	
			{
				temp = botb->left;
				if (r == NULL)	
				    botb->left = botb;
				else	
				{
					botb->left = r->left;
					r->left = botb;
				}
				r = botb;
				botb = temp;
			}
		}
		if (botb == NULL) 
		{
		    a->right = r->right;
			r->right = bota;
			return a;
		}
		else
		{
		    b->left = r->left;
			r->left = botb;
			return b;
		}
	}
}
/*
 * Insert element into pagoda
 */
tree insert(tree node, tree pq)
{
	node->left = node;
	node->right = node;
	return merge( pq, node);
}

/*
 * Delete element from pagoda
 */
tree del(tree pq)
{
	tree le, ri;
	if (pq == NULL)
	{
		cout<<"Deletion out of range"<<endl;
		return NULL;
	}
	else	
	{	
	    if (pq->left == pq) 
	        le = NULL;
		else 
		{
	        le = pq->left;
		    while (le->left != pq) 
		        le = le->left;
			le->left = pq->left;
		}
		if (pq->right == pq) 
		    ri = NULL;
		else 
		{
		    ri = pq->right;
		    while (ri->right != pq) 
			    ri = ri->right;
			ri->right = pq->right;
		}
		return merge(le, ri);
	}
}

/*
 * Main Contains Menu
 */
int main()
{
	node **root = new node* [MAX_ELEMS + 1];
	int value, i = 0;
    int choice;
    while(1)
    {
		cout<<"\n----------------------"<<endl;
		cout<<"Operations on Pagoda"<<endl;
		cout<<"\n----------------------"<<endl;
		cout<<"1.Insert element at Last"<<endl;
	    cout<<"2.Display Pagoda"<<endl;
	    cout<<"3.Delete Last element"<<endl;
	    cout<<"4.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
        {
        	cout<<"Enter element "<<i + 1<<": ";
        	cin>>value;
        	node *temp = new node;
        	temp->k = value;
            root[i] = insert(temp, root[i]);
            i++;
            break;
		}
        case 2:
        {
            cout<<"Displaying elements of pagoda: "<<endl;
            int j = 0;
            while(root[j] != NULL)
            {    
		        cout<<"Element "<<j + 1<<": "<<root[j]->k<<endl;
		        j++;
			}
            break;
		}
        case 3:
            root[i - 1] = del(root[i - 1]);
            i--;
            break;
        case 4:
            exit(1);
        default:
           cout<<"Wrong Choice"<<endl;
       }
    }
    return 0;
}
