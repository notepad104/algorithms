#include <iostream>
#include <list>
#include <cstdlib>
using namespace std;
int main()
{
    int choice, item;
    list<int> lt;
    list<int>::iterator it;
    while (1)
    {
        cout<<"\n---------------------"<<endl;
        cout<<"Sorting Containers Implementation in Stl"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element into the List"<<endl;
        cout<<"2.Display Sorted Elements"<<endl;
        cout<<"3.Exit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter the element to be inserted: ";
            cin>>item;
            lt.push_back(item);
            break;
        case 2:
            lt.sort();
            cout<<"Elements of Sorted List: ";
             for (it = lt.begin(); it != lt.end(); ++it)
                cout <<"  "<< *it;
            cout << endl;
            break;
        case 3:
            exit(1);
            break;
        default:
            cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}
