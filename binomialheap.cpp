/*
 * C++ Program to Implement Binomial Heap
 */

#include <iostream>
#include <cstdlib>
using namespace std;

/* Class BinomialHeapNode */
class BinomialHeapNode
{
    public:
        int key, degree;
        BinomialHeapNode *parent;
        BinomialHeapNode *sibling;
        BinomialHeapNode *child;
        /* Constructor */
        BinomialHeapNode(int k)
        {
            key = k;
            degree = 0;
            parent = NULL;
            sibling = NULL;
            child = NULL;
        }

        /* Function reverse */
        BinomialHeapNode *reverse(BinomialHeapNode *sibl)
        {
            BinomialHeapNode *ret;
            if (sibling != NULL)
                ret = sibling->reverse(this);
            else
                ret = this;
                sibling = sibl;
                return ret;
        }

        /* Function to find min node */
        BinomialHeapNode *findMinNode()
        {
            BinomialHeapNode *x = this, *y = this;
            int min = x->key;
            while (x != NULL)
            {
                if (x->key < min)
                {
                    y = x;
                    min = x->key;
                }
                x = x->sibling;
            }
            return y;
        }

        /* Function to find node with key value */
        BinomialHeapNode *findANodeWithKey(int value)
        {
            BinomialHeapNode *temp = this, *node = NULL;
            while (temp != NULL)
            {
                if (temp->key == value)
                {
                    node = temp;
                    break;
                }
                if (temp->child == NULL)
                    temp = temp->sibling;
                else
                {
                    node = temp->child->findANodeWithKey(value);
                    if (node == NULL)
                        temp = temp->sibling;
                    else
                        break;
                }
            }
            return node;
        }

        /* Function to get size */
        int getSize()
        {
            if (child == NULL)
            {
                if (sibling == NULL)
                    return 1;
                else
                    return 1 + sibling->getSize();
            }
            else
            {
                if (sibling == NULL)
                    return 1 + child->getSize();
                else
                    return 1 + child->getSize() + sibling->getSize();
            }
        }
};


/* class BinomialHeap */
class BinomialHeap
{
    private:
        BinomialHeapNode *Nodes;
        int size;
    public:
        /* Constructor */
        BinomialHeap()
        {
            Nodes = NULL;
            size = 0;
        }

        /* Check if heap is empty */
        bool isEmpty()
        {
            return Nodes == NULL;
        }

        /* Function to get size */
        int getSize()
        {
            return size;
        }

        /* clear heap */
        void makeEmpty()
        {
            Nodes = NULL;
            size = 0;
        }

        /* Function to insert */
        void insert(int value)
        {
            if (value > 0)
            {
                BinomialHeapNode *temp = new BinomialHeapNode(value);
                if (Nodes == NULL)
                {
                    Nodes = temp;
                    size = 1;
                }
                else
                {
                    unionNodes(temp);
                    size++;
                }
            }
        }

        /* Function to unite two binomial heaps */
        void merge(BinomialHeapNode *binHeap)
        {
            BinomialHeapNode *temp1 = Nodes, *temp2 = binHeap;
            while ((temp1 != NULL) && (temp2 != NULL))
            {
                if (temp1->degree == temp2->degree)
                {
                    BinomialHeapNode *tmp = temp2;
                    temp2 = temp2->sibling;
                    tmp->sibling = temp1->sibling;
                    temp1->sibling = tmp;
                    temp1 = tmp->sibling;
                }
                else
                {
                    if (temp1->degree < temp2->degree)
                    {
                        if ((temp1->sibling == NULL) ||
                            (temp1->sibling->degree > temp2->degree))
                        {
                            BinomialHeapNode *tmp = temp2;
                            temp2 = temp2->sibling;
                            tmp->sibling = temp1->sibling;
                            temp1->sibling = tmp;
                            temp1 = tmp->sibling;
                        }
                        else
                        {
                            temp1 = temp1->sibling;
                        }
                    }
                    else
                    {
                        BinomialHeapNode *tmp = temp1;
                        temp1 = temp2;
                        temp2 = temp2->sibling;
                        temp1->sibling = tmp;
                        if (tmp == Nodes)
                        {
                            Nodes = temp1;
                        }
                    }
                }
            }
            if (temp1 == NULL)
            {
                temp1 = Nodes;
                while (temp1->sibling != NULL)
                {
                    temp1 = temp1->sibling;
                }
                temp1->sibling = temp2;
            }
        }

        /* Function for union of nodes */
        void unionNodes(BinomialHeapNode *binHeap)
        {
            merge(binHeap);
            BinomialHeapNode *prevTemp = NULL, *temp = Nodes;
            BinomialHeapNode *nextTemp = Nodes->sibling;
            while (nextTemp != NULL)
            {
                if ((temp->degree != nextTemp->degree) ||
                    ((nextTemp->sibling != NULL) &&
                     (nextTemp->sibling->degree == temp->degree)))

                {
                    prevTemp = temp;
                    temp = nextTemp;
                }
                else
                {
                    if (temp->key <= nextTemp->key)
                    {
                        temp->sibling = nextTemp->sibling;
                        nextTemp->parent = temp;
                        nextTemp->sibling = temp->child;
                        temp->child = nextTemp;
                        temp->degree++;
                    }
                    else
                    {
                        if (prevTemp == NULL)
                        {
                            Nodes = nextTemp;
                        }
                        else
                        {
                            prevTemp->sibling = nextTemp;
                        }
                        temp->parent = nextTemp;
                        temp->sibling = nextTemp->child;
                        nextTemp->child = temp;
                        nextTemp->degree++;
                        temp = nextTemp;
                    }
                }
                nextTemp = temp->sibling;
            }
        }

        /* Function to return minimum key */

        int findMinimum()
        {
            return Nodes->findMinNode()->key;
        }

        /* Function to delete a particular element */
        void Delete(int value)
        {
            if ((Nodes != NULL) && (Nodes->findANodeWithKey(value) != NULL))
            {
                decreaseKeyValue(value, findMinimum() - 1);
                extractMin();
            }
        }

        /* Function to decrease key with a given value */
        void decreaseKeyValue(int old_value, int new_value)
        {
            BinomialHeapNode *temp = Nodes->findANodeWithKey(old_value);
            if (temp == NULL)
                return;
            temp->key = new_value;
            BinomialHeapNode *tempParent = temp->parent;
            while ((tempParent != NULL) && (temp->key < tempParent->key))
            {
                int z = temp->key;
                temp->key = tempParent->key;
                tempParent->key = z;
                temp = tempParent;
                tempParent = tempParent->parent;
            }
        }

        /* Function to extract the node with the minimum key */
        int extractMin()
        {
            if (Nodes == NULL)
                return -1;
            BinomialHeapNode *temp = Nodes, *prevTemp = NULL;
            BinomialHeapNode *minNode = Nodes->findMinNode();
            while (temp->key != minNode->key)
            {
                prevTemp = temp;
                temp = temp->sibling;
            }
            if (prevTemp == NULL)
            {
                Nodes = temp->sibling;
            }
            else
            {
                prevTemp->sibling = temp->sibling;
            }
            temp = temp->child;
            BinomialHeapNode *fakeNode = temp;
            while (temp != NULL)
            {
                temp->parent = NULL;
                temp = temp->sibling;
            }
            if ((Nodes == NULL) && (fakeNode == NULL))
            {
                size = 0;
            }
            else
            {
                if ((Nodes == NULL) && (fakeNode != NULL))
                {
                    Nodes = fakeNode->reverse(NULL);
                    size = Nodes->getSize();
                }
                else
                {
                    if ((Nodes != NULL) && (fakeNode == NULL))
                    {
                        size = Nodes->getSize();
                    }
                    else
                    {
                        unionNodes(fakeNode->reverse(NULL));
                        size = Nodes->getSize();
                    }
                }
            }
            return minNode->key;
        }

        /* Function to display heap */
        void displayHeap()
        {
            cout<<"\nHeap : ";
            displayHeap(Nodes);
            cout<<endl;
        }

        void displayHeap(BinomialHeapNode *r)
        {
            if (r != NULL)
            {
                displayHeap(r->child);
                cout<<r->key<<"  ";
                displayHeap(r->sibling);
            }
        }
};

int main()
{
    cout<<"Binomial Heap\n\n";
    BinomialHeap bh;
    char ch;
    int val;
        /*  Perform BinomialHeap operations  */
    do
    {
        cout<<"1. Insert "<<endl;
        cout<<"2. Delete "<<endl;
        cout<<"3. Size"<<endl;
        cout<<"4. Check empty"<<endl;
        cout<<"5. Clear"<<endl;
        int choice;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1 :
            cout<<"Enter integer element to insert: ";
            cin>>val;
            bh.insert(val);
            break;
        case 2 :
            cout<<"Enter element to delete: ";
            cin>>val;
            bh.Delete(val);
            break;
        case 3 :
            cout<<"Size = "<<bh.getSize()<<endl;
            break;
        case 4 :
            cout<<"Empty status = ";
            if (bh.isEmpty())
                cout<<"Heap is empty"<<endl;
            else
                cout<<"Heap is non - empty"<<endl;
            break;
        case 5 :
            bh.makeEmpty();
            cout<<"Heap Cleared\n";
            break;
        default :
            cout<<"Wrong Entry \n ";
            break;
        }

        /* Display heap */
        bh.displayHeap();
        cout<<"\nDo you want to continue (Type y or n) \n";
        cin>>ch;
    }
    while (ch == 'Y'|| ch == 'y');
    return 0;
}
