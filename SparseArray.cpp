#include <iostream>
#include <iomanip>
#include <string>
using namespace std;    

class List
{
    private: 
        int index;
        int value;
        List *nextindex;
    public: 
        List(int index)
        {
            this->index = index;
            nextindex = NULL;
            value = NULL;
        }
        List()
        {
            index = -1;
            value = NULL;
            nextindex = NULL;
        }
        void store(int index, int value)
        {
            List *current = this;
            List *previous = NULL;
            List *node = new List(index);
            node->value = value;
            while (current != NULL && current->index < index)
            {
                previous = current;
                current = current->nextindex;
            }
            if (current == NULL)
            {
                previous->nextindex = node;
            } 
            else
            {
                if (current->index == index)
                {
                    cout<<"DUPLICATE INDEX"<<endl;
                    return;
                }
                previous->nextindex = node;
                node->nextindex = current;
            }
            return;
        }

        int fetch(int index)
        {
            List *current = this;
            int value = NULL;
            while (current != NULL && current->index != index)
            {
                current = current->nextindex;
            }
            if (current != NULL)
            {
                value = current->value;
            } 
            else
            {
                value = NULL;
            }
            return value;
        }

        int elementCount()
        {
            int elementCount = 0;
            List *current = this->nextindex;
            for ( ; (current != NULL); current = current->nextindex)
            {
                elementCount++;
            }
            return elementCount;
        }
};

class SparseArray
{
    private:
        List *start;
        int index;
    public:
        SparseArray(int index)
        {
            start = new List();
            this->index = index;
        }
        void store(int index, int value)
        {
            if (index >= 0 && index < this->index)
            {
                if (value != NULL)
                    start->store(index, value);
            } 
            else
            {
                cout<<"INDEX OUT OF BOUNDS"<<endl;
            }
        }
        int fetch(int index)
        {
            if (index >= 0 && index < this->index)
                return start->fetch(index);
            else 
            {
                cout<<"INDEX OUT OF BOUNDS"<<endl;
                return NULL;
            }
        }
        int elementCount()
        {
            return start->elementCount();
        }
};

int main()
{
    int iarray[5];
    iarray[0] = 1;
    iarray[1] = NULL;
    iarray[2] = 2;
    iarray[3] = NULL;
    iarray[4] = NULL;
    SparseArray sparseArray(5);
    for (int i = 0; i < 5; i++)
    {
        sparseArray.store(i, iarray[i]);
    }
    cout<<"NORMAL ARRAY"<<endl;
    for (int i = 0 ; i < 5; i++)
    {
        if (iarray[i] == NULL)
            cout<<"NULL"<<"\t";
        else
            cout<<iarray[i] <<"\t";
    }

    cout<<"\nSPARSE ARRAY"<<endl;
    for (int i = 0; i < 5; i++)
    {
        if (sparseArray.fetch(i) != NULL)
            cout<<sparseArray.fetch(i) <<"\t";
    }
    cout<<"The Size of Sparse Array is "<<sparseArray.elementCount()<<endl;
}
