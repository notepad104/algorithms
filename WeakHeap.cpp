/*
 * C++ Program to Implement Weak Heap
 */
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#define GETFLAG(r, x) ((r[(x) >> 3] >> ((x) & 7)) & 1)
#define TOGGLEFLAG(r, x) (r[(x) >> 3] ^= 1 << ((x) & 7))
using namespace std;
/*
 * Class Declaration
 */
class WeakHeap
{
    private:
        vector <int> wheap;
    public:
        WeakHeap()
        {}
        int Size();
        void Insert(int element);
        void DisplaySorted();
        void WeakHeapMerge(unsigned char *r, int i, int j);
        void WeakHeapSort();
};
/*
 * Heap Size
 */
int WeakHeap::Size()
{
    return wheap.size();
}
/*
 * Insert Element into a Heap
 */
void WeakHeap::Insert(int element)
{
    wheap.push_back(element);
    WeakHeapSort();
}

/*
 * Merge Weak Heap
 */
void WeakHeap::WeakHeapMerge(unsigned char *r, int i, int j)
{
    if (wheap[i] < wheap[j])
    {
        TOGGLEFLAG(r, j);
        swap(wheap[i], wheap[j]);
    }
}
/*
 * Weak Heap Sort
 */
void WeakHeap::WeakHeapSort()
{
    int n = Size();
    if (n > 1)
    {
        int i, j, x, y, Gparent;
        int s = (n + 7) / 8;
        unsigned char * r = new unsigned char [s];
        for (i = 0; i < n / 8; ++i)
            r[i] = 0;
        for (i = n - 1; i > 0; --i)
        {
            j = i;
            while ((j & 1) == GETFLAG(r, j >> 1))
                j >>= 1;
            Gparent = j >> 1;
            WeakHeapMerge(r, Gparent, i);
        }
        for (i = n - 1; i >= 2; --i)
        {
            swap(wheap[0], wheap[i]);
            x = 1;
            while ((y = 2 * x + GETFLAG(r, x)) < i)
                x = y;
            while (x > 0)
            {
                WeakHeapMerge(r, 0, x);
                x >>= 1;
            }
        }
        swap(wheap[0], wheap[1]);
        delete[] r;
    }
}
/*
 * Display Sorted Heap
 */
void WeakHeap::DisplaySorted()
{
    vector <int>::iterator pos = wheap.begin();
    cout<<"Heap -->  ";
    while (pos != wheap.end())
    {
        cout<<*pos<<" ";
        pos++;
    }
    cout<<endl;
}
/*
 * Main Contains Menu
 */
int main()
{
    WeakHeap wh;
    while (1)
    {
        cout<<"------------------"<<endl;
        cout<<"Operations on Weak Heap"<<endl;
        cout<<"------------------"<<endl;
        cout<<"1.Insert Element"<<endl;
        cout<<"2.Display Weak Heap Sorted Array"<<endl;
        cout<<"3.Exit"<<endl;
        int choice, element;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter the element to be inserted: ";
            cin>>element;
            wh.Insert(element);
            break;
        case 2:
            cout<<"Array Sorted by Weak Heap:  ";
            wh.DisplaySorted();
            break;
        case 3:
            exit(1);
        default:
            cout<<"Enter Correct Choice"<<endl;
        }
    }
    return 0;
}

/*
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 1
Enter the element to be inserted: 5
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 1
Enter the element to be inserted: 4
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 2
Array Sorted by Weak Heap:  Heap -->  4 5
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 1
Enter the element to be inserted: 7
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 1
Enter the element to be inserted: 20
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 1
Enter the element to be inserted: 4
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 1
Enter the element to be inserted: 3
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 1
Enter the element to be inserted: 7
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 2
Array Sorted by Weak Heap:  Heap -->  3 4 4 5 7 7 20
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 1
Enter the element to be inserted: 11
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 2
Array Sorted by Weak Heap:  Heap -->  3 4 4 5 7 7 11 20
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 21
Enter Correct Choice
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 1
Enter the element to be inserted: 1
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice: 2
Array Sorted by Weak Heap:  Heap -->  1 3 4 4 5 7 7 11 20
------------------
Operations on Weak Heap
------------------
1.Insert Element
2.Display Weak Heap Sorted Array
3.Exit
Enter your choice:


 */
