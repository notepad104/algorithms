#include <iostream>
#include <forward_list>
#include <string>
#include <cstdlib>
using namespace std;
int main()
{
    forward_list<int> fl, fl1 = {5, 6, 3, 2, 7};
    forward_list<int>::iterator it;
    int choice, item;
    while (1)
    {
        cout<<"\n---------------------"<<endl;
        cout<<"Forward_List Implementation in Stl"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element at the Front"<<endl;
        cout<<"2.Delete Element at the Front"<<endl;
        cout<<"3.Front Element of Forward List"<<endl;
        cout<<"4.Resize Forward List"<<endl;
        cout<<"5.Remove Elements with Specific Values"<<endl;
        cout<<"6.Remove Duplicate Values"<<endl;
        cout<<"7.Reverse the order of elements"<<endl;
        cout<<"8.Sort Forward List"<<endl;
        cout<<"9.Merge Sorted Lists"<<endl;
        cout<<"10.Display Forward List"<<endl;
        cout<<"11.Exit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter value to be inserted at the front: ";
            cin>>item;
            fl.push_front(item);
            break;
        case 2:
		    item = fl.front();
		    fl.pop_front();
		    cout<<"Element "<<item<<" deleted"<<endl;
            break;
        case 3:
		    cout<<"Front Element of the Forward List: ";
		    cout<<fl.front()<<endl;
            break;
        case 4:
            cout<<"Enter new size of Forward List: ";
            cin>>item;
            if (item <= fl.max_size())
                fl.resize(item);
            else
                fl.resize(item, 0);
            break;
        case 5:
            cout<<"Enter element to be deleted: ";
            cin>>item;
            fl.remove(item);
            break;
        case 6:
            fl.unique();
            cout<<"Duplicate Items Deleted"<<endl;
            break;
        case 7:
            fl.reverse();
            cout<<"Forward List reversed"<<endl;
            break;
        case 8:
            fl.sort();
            cout<<"Forward List Sorted"<<endl;
            break;
        case 9:
            fl1.sort();
            fl.sort();
            fl.merge(fl1);
            cout<<"Forward List Merged after sorting"<<endl;
            break;
        case 10:
            cout<<"Elements of Forward List:  ";
            for (it = fl.begin(); it != fl.end(); it++)
                cout<<*it<<"  ";
            cout<<endl;
            break;
		case 11:
            exit(1);
	        break;
        default:
            cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}
