#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
 
int main()
{
    int array[100001] = {0}, value;
    char ch = 'y';
    while (ch == 'Y' || ch == 'y')
    {
        cout<<"Enter an integer to be inserted: ";
        cin>>value;
        array[value] = value;
        cout<<"Do you want to insert more ( Y or N): ";
        cin>>ch;
    }
    for(int i = 0; i < 100001; i++)
    {
        if (array[i] != 0)
            cout<<array[i]<<"  ";
    }
    cout<<endl;
    return 0;
}
