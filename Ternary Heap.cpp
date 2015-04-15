#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
int const N = 16;
using namespace std;

class Ternary_Heap
{
    private:
        int heap_capacity;
        int initial_capacity;
        int *array;
        int heap_size;
        void double_capacity()
        {
            int *tmp_array = new int[2 * capacity()];

            for (int i = 0; i < size(); ++i )
            {
                tmp_array[i] = array[i];
            }

            delete [] array;
            array = tmp_array;
            heap_capacity *= 2;
        }
        void halve_capacity()
        {
            int *tmp_array = new int[capacity() / 2];

            for (int i = 0; i < size(); ++i)
            {
                tmp_array[i] = array[i];
            }

            delete [] array;
            array = tmp_array;
            heap_capacity /= 2;
        }
    public:
        Ternary_Heap(int);
        ~Ternary_Heap();
        Ternary_Heap(Ternary_Heap &);
        Ternary_Heap &operator=(Ternary_Heap &heap);
        friend ostream &operator <<(ostream &, Ternary_Heap &);
        bool empty()
        {
            return heap_size == 0;
        }
        int size()
        {
            return heap_size;
        }
        int capacity()
        {
            return heap_capacity;
        }
        int count(int &obj)
        {
            int c = 0;
            for (int i = 0; i < size(); i++)
            {
             if (array[i] == obj)
                ++c;
            }
            return c;
        }
        int top()
        {
            if (empty())
                return NULL;
            return array[0];
        }

        void push(int &obj)
        {
            if (size() == capacity())
                double_capacity();
            int i = heap_size;
            ++heap_size;
            while (i != 0 && array[(i - 1) / 3] > obj)
            {
                array[i] = array[(i - 1) / 3];
                i = (i - 1) / 3;
            }
            array[i] = obj;
        }
        void pop()
        {
            if (empty())
                return;
            --heap_size;
            int last = array[size()];
            int posn = 0;
            int posn30 = 0;
            int posn33 = 3;
            while (posn33 < size())
            {
                int posn31  = posn30 + 1;
                int posn32 = posn30 + 2;
                int min = last;
                int loc = posn;
                if (array[posn33] < min)
                {
                    min = array[posn33];
                    loc = posn33;
                }
                if (array[posn32] < min)
                {
                    min = array[posn32];
                    loc = posn32;
                }
                if (array[posn31] < min)
                {
                    min = array[posn31];
                    loc = posn31;
                }
                array[posn] = min;
                if (posn == loc)
                {
                    if ( 4 * size() == capacity())
                    {
                        if (capacity() > initial_capacity)
                        {
                            halve_capacity();
                        }
                    }
                    return;
                }
                    posn = loc;
                    posn30 = 3 * loc;
                    posn33 = posn30 + 3;
                }
                int min = last;
                int loc = posn;
                int posn31 = posn30 + 1;
                int posn32 = posn30 + 2;

                switch (posn33 - size())
                {
                case 0:
                    if (array[posn32] < min)
                    {
                        min = array[posn32];
                        loc = posn32;
                    }
                case 1:
                    if (array[posn31] < min)
                    {
                        min = array[posn31];
                        loc = posn31;
                    }
                }

                array[posn] = min;
                if (posn != loc)
                {
                    array[loc] = last;
                }
            }
        void clear()
        {
            heap_size = 0;
            if (heap_capacity != initial_capacity)
            {
                heap_capacity = initial_capacity;
                delete [] array;
                array = new int[heap_capacity];
            }
        }
};
Ternary_Heap::Ternary_Heap(int n)
{
    heap_capacity = max(1, n);
    initial_capacity = heap_capacity;
    array = new int [heap_capacity];
    heap_size = 0;
}

Ternary_Heap::~Ternary_Heap()
{
    delete [] array;
}

Ternary_Heap::Ternary_Heap(Ternary_Heap &heap)
{
    heap_capacity = heap.heap_capacity;
    initial_capacity = heap.initial_capacity;
    array = new int [heap_capacity];
    heap_size = heap.heap_size;
    for (int i = 0; i < heap_size; i++)
    {
        array[i] = heap.array[i];
    }
}

Ternary_Heap &Ternary_Heap::operator=(Ternary_Heap &heap)
{
    if (this == &heap)
        return *this;
    if (heap_capacity != heap.heap_capacity)
    {
        delete [] array;
        heap_capacity = heap.heap_capacity;
        array = new int [heap_capacity];
    }
    initial_capacity = heap.initial_capacity;
    heap_size = heap.heap_size;
    for (int i = 0; i < size(); i++)
    {
        array[i] = heap.array[i];
    }
    return *this;
}

ostream &operator << (ostream &out, Ternary_Heap &heap)
{
    out << "Size:             " << heap.size() << endl;
    out << "Capacity:         " << heap.capacity() << endl;
    out << "Initial capacity: " << heap.initial_capacity << endl;
    for (int i = 0; i < heap.size(); ++i)
    {
        out << heap.array[i] << " ";
    }
    out << endl;
    return out;
}
int main()
{
    Ternary_Heap heap(8);
    for (int i = 0; i < N; ++i)
    {
        int x = (5 + 7 * i) % N;
		heap.push(x);
		cout << heap << endl;
	}

	for (int i = 0; i < N; ++i)
    {
		cout << "Current top: " << heap.top() << endl;
		heap.pop();
		cout << heap << endl;
	}
	cout << heap << endl;
    return 0;
}
