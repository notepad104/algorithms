#include <iostream>
#include <string>
using namespace std;
 
int main()
{
    int *array, size;
    cout<<"Enter size of array: ";
    cin>>size;
    array = new int [size];
    for (int i = 0; i < size; i++)
    {
        cout<<"Enter an integer to be inserted: ";
        cin>>array[i];
    }
    for(int i = 0; i < size; i++)
    {
        cout<<array[i]<<"  ";
    }
    cout<<endl;
    delete []array;
    return 0;
}
