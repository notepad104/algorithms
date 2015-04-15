/*
 *  C++ Program to Implement D-ary-Heap
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
/*
 *   D-ary Heap Class
 */
class DaryHeap
{
    private:
        int d;
        int currentSize;
        int size;
        int *array;
    public:
    /** Constructor **/
        DaryHeap(int capacity, int numKids)
        {
            currentSize = 0;
            d = numKids;
            size = capacity + 1;
            array = new int[capacity + 1];
            for(int i = 0 ;i < capacity + 1; i++)
                array[i] = -1;
        }

        /** Constructor , filling up heap with a given array **/
        DaryHeap(int* array, int numKids)
        {
            int i = 0;
            while (array[i] != -1)
                i++;
            currentSize = i;
            this->array = array;
            this->d = numKids;
            buildHeap();
        }

        /** Function to check if heap is empty **/
        bool isEmpty()
        {
            return currentSize == 0;
        }

        /** Check if heap is full **/
        bool isFull()
        {
            return currentSize == size;
        }

        /** Clear heap **/
        void makeEmpty( )
        {
            currentSize = 0;
        }

        /** Function to  get index parent of i **/
        int parent(int i)
        {
            return (i - 1)/d;
        }

        /** Function to get index of k th child of i **/
        int kthChild(int i, int k)\
        {
            return d * i + k;
        }

        /** Function to inset element **/
        void insert(int x)
        {
            if (isFull())
            {
                cout<<"Array Out of Bounds"<<endl;
                return;
            }

            // Percolate up
            int hole = currentSize;
            currentSize++;
            array[hole] = x;
            percolateUp(hole);
        }

        /** Function to find least element **/
        int findMin()
        {
            if (isEmpty())
            {
                cout<<"Array Underflow"<<endl;
                return 0;
            }
            return array[0];
        }
        /** Function to delete element at an index **/
        int Delete(int hole)
        {
            if (isEmpty())
            {
                cout<<"Array Underflow"<<endl;
                return 0;
            }
            int keyItem = array[hole];
            array[hole] = array[currentSize - 1];
            currentSize--;
            percolateDown( hole );
            return keyItem;
        }

        /** Function to build heap **/
        void buildHeap()
        {
            for (int i = currentSize - 1 ; i >= 0; i--)
                percolateDown(i);
        }

        /** Function percolateDown **/

        void percolateDown(int hole)
        {
            int child;
            int tmp = array[hole];
            for ( ; kthChild(hole, 1) < currentSize; hole = child)
            {
                child = smallestChild( hole );
                if (array[child] < tmp)
                    array[hole] = array[child];
                else
                    break;
            }
            array[hole] = tmp;
        }

        /** Function to get smallest child from all valid indices **/
        int smallestChild(int hole)
        {
            int bestChildYet = kthChild(hole, 1);
            int k = 2;
            int candidateChild = kthChild(hole, k);
            while ((k <= d) && (candidateChild < currentSize))
            {
                if (array[candidateChild] < array[bestChildYet])
                    bestChildYet = candidateChild;
                k++;
                candidateChild = kthChild(hole, k);
            }
            return bestChildYet;
        }

        /** Function percolateUp  **/
        void percolateUp(int hole)
        {
            int tmp = array[hole];
            for (; hole > 0 && tmp < array[parent(hole)]; hole = parent(hole))
                array[hole] = array[ parent(hole) ];
            array[hole] = tmp;
        }

        /** Function to print heap **/
        void printHeap()
        {
            cout<<"\nHeap = ";
            for (int i = 0; i < currentSize; i++)
                cout<<array[i]<<"   ";
            cout<<endl;
        }
};

int main()
{
    cout<<"Dary Heap Test\n\n";
    cout<<"Enter size and D of Dary Heap: ";
    int size, num, choice, val;
    cin>>size>>num;
    /** Make object of DaryHeapHeap **/
    DaryHeap th(size, num);
    char ch;
    /**  Perform Dary Heap operations  **/
    do
    {
        cout<<"\nDary Heap Operations\n";
        cout<<"1. Insert "<<endl;
        cout<<"2. Delete"<<endl;
        cout<<"3. Check full"<<endl;
        cout<<"4. Check empty"<<endl;
        cout<<"5. Clear"<<endl;
        bool chk;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"Enter integer element to insert: ";
            cin>>val;
            th.insert(val);
            break;
        case 2:
            cout<<"Enter delete position: ";
            cin>>val;
            th.Delete(val - 1);
            break;
        case 3:
            if(th.isFull())
                cout<<"The Heap is Full"<<endl;
            else
                cout<<"The Heap is not Full"<<endl;
            break;
        case 4 :
            if(th.isEmpty())
                cout<<"The Heap is Empty"<<endl;
            else
                cout<<"The Heap is not Empty"<<endl;
            break;
        case 5 :
            th.makeEmpty();
            cout<<"Heap Cleared\n";
            break;
        default :
            cout<<"Wrong Entry \n ";
            break;
        }

        /** Display heap **/
        th.printHeap();
        cout<<"\nDo you want to continue (Type y or n) \n";
        cin>>ch;
    }
    while (ch == 'Y'|| ch == 'y');
    return 0;
}

