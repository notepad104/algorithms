#include <iostream>
#include <string>
#include <cstdlib>
#include <unordered_set>
using namespace std;
int main()
{
    unordered_set<string> myset = {"Mercury","Venus","Earth",
                                    "Mars","Jupiter","Saturn","Uranus"};
    unordered_set<string>::const_iterator got;
    unordered_set<string>::iterator it;
    int choice, item;
    string s;
    while (1)
    {
        cout<<"\n---------------------"<<endl;
        cout<<"Unordered Set Implementation in Stl"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element"<<endl;
        cout<<"2.Delete Element"<<endl;
        cout<<"3.Find Element"<<endl;
        cout<<"4.Count Elements"<<endl;
        cout<<"5.Size of the Unordered Set"<<endl;
        cout<<"6.Count number of Buckets"<<endl;
        cout<<"7.Buckets"<<endl;
        cout<<"8.Display Unordered Set"<<endl;
        cout<<"9.Exit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter string to be inserted: ";
            cin>>s;
            myset.insert(s);
            break;
        case 2:
            cout<<"Enter string to be deleted: ";
            cin>>s;
            myset.erase(s);
            break;
        case 3:
            cout<<"Enter key string to find ";
            cin>>s;
            got = myset.find (s);
            if (got == myset.end())
                cout<<"Element found in myset"<<endl;
            else
                cout<<"Element not found in myset"<<endl;
            break;
        case 4:
            cout<<"Enter string to be counted: ";
            cin>>s;
            cout<<"There are "<<myset.count(s)<<" elements with '"<<s<<"'\n";
            break;
        case 5:
            cout<<"Size of the Unordered Set: "<<myset.size()<<endl;
            break;
        case 6:
            cout<<"myset has "<< myset.bucket_count()<<" buckets.\n";
            break;
        case 7:
            for (const string& x: myset)
            {
                cout<< x <<" is in bucket #" << myset.bucket(x) << endl;
            break;
            }
        case 8:
            cout<<"Elements of the Unordered Set:  ";
            for (it = myset.begin(); it != myset.end(); ++it)
                cout << " " << *it;
            cout<<endl;
            break;
		case 9:
            exit(1);
	        break;
        default:
            cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}
