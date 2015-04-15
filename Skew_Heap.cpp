#include <iostream>
#include <cstdlib>
using namespace std;

class Skew_Heap
{
    public:
        int key;
        Skew_Heap *right;
        Skew_Heap *left;
        Skew_Heap *parent;
        Skew_Heap()
        {
            key = 0;
            right = NULL;
            left = NULL;
            parent = NULL;
        }
        Skew_Heap *merge(Skew_Heap *h1, Skew_Heap *h2)
        {
            Skew_Heap *temp;
            if (h1 == NULL)
                return h2;
            else if (h2 == NULL)
                return h1;
            else
            {
                if (h1->key < h2->key)
                {
                    temp = h1;
                    h1 = h2;
                    h2 = temp;
                }
                temp = h1->left;
                h1->left = h1->right;
                h1->right = temp;
                h1->left = merge(h2, h1->left);
            }
            return h1;
        }

        Skew_Heap *construct(Skew_Heap *root)
        {
            Skew_Heap *temp;
            int input, val;
            while (1)
            {
                cout<<"Enter the value of the node(0 to exit): ";
                cin >> val;
                if (val == 0)
                    break;
                temp = new Skew_Heap;
                temp->key = val;
                root = merge(root, temp);
            }
            return root;
        }

        Skew_Heap *insert(Skew_Heap *root)
        {
            int val;
            Skew_Heap *temp;
            cout<<"Enter the value of the node: ";
            cin >> val;
            temp = new Skew_Heap;
            temp->key = val;
            root = merge(root, temp);
            return root;
        }

        Skew_Heap *delete_max(Skew_Heap *root)
        {
            if (root == NULL)
            {
                cout << "The heap is empty"<<endl;
                return NULL;
            }
            Skew_Heap *temp1, *temp2;
            temp1 = root->left;
            temp2 = root->right;
            temp1 = merge(temp1, temp2);
            cout << "Maximum Deleted "<<endl;
            return temp1;
        }

        void preorder(Skew_Heap *root)
        {
            if (root == NULL)
                return;
            else
            {
                cout << root->key <<"  ";
                preorder(root->left);
                preorder(root->right);
            }
            return;
        }
        void inorder(Skew_Heap *root)
        {
            if (root == NULL)
                return;
            else
            {
                inorder(root->left);
                cout << root->key <<"  ";
                inorder(root->right);
            }
            return;
        }

        void postorder(Skew_Heap *root)
        {
            if (root == NULL)
                return;
            else
            {
                postorder(root->left);
                postorder(root->right);
                cout << root->key <<"   ";
            }
            return;
        }

        void print_heap(Skew_Heap *root)
        {
            cout << "Preorder traversal of the heap is " << endl;
            preorder(root);
            cout << endl;
            cout << "Inorder traversal of the heap is " << endl;
            inorder(root);
            cout << endl;
            cout << "Postorder traversal of the heap is " << endl;
            postorder(root);
            cout << endl;
        }
};


int main()
{
    Skew_Heap *head1, *temp1, *temp2, obj;
    int input;
    head1 = NULL;
    temp1 = NULL;
    temp2 = NULL;
    while(1)
    {
        cout << endl<< "-----------Operations on Skew Heap---------"<<endl;
        cout << "1.Insert a Skew_Heap into the existing heap"<<endl;
        cout << "2.Delete_max Skew_Heap of the existing heap"<<endl;
        cout << "3.Merge two heaps"<<endl;
        cout << "4.Print the heap"<<endl;
        cout << "5.Print the maximum element of the heap"<<endl;
        cout << "6.Merge the present heap with another heap"<<endl;
        cout << "7.Exit"<<endl;
        cout << "Enter your Choice: ";
        cin >> input;
        switch(input)
        {
        case 1:
            head1 = obj.insert(head1);
            break;
        case 2:
            head1 = obj.delete_max(head1);
            break;
        case 3:
            cout << "Enter the first heap: "<<endl;
            temp1 = obj.construct(temp1);
            cout << "Enter the second heap: "<<endl;
            temp2 = obj.construct(temp2);
            temp1 = obj.merge(temp1, temp2);
            cout << "The heap obtained after merging is: "<<endl;
            obj.print_heap(temp1);
            break;
        case 4:
            obj.print_heap(head1);
            break;
        case 5:
            cout << "The maximum element existing in the heap is: ";
            cout << head1->key << endl;
            break;
        case 6:
            cout << "Enter the second heap"<<endl;
            temp1 = obj.construct(temp1);
            temp1 = obj.merge(temp1, head1);
            cout << "The heap obtained after merging is: "<<endl;
            obj.print_heap(temp1);
            break;
        case 7:
            exit(1);
        default:
            cout<<"Enter Correct Choice"<<endl;
            break;
        }
    }
    return 0;
}
