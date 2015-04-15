<div style="text-align:justify">
This C++ Program demonstrates operations on Hash Tables Chaining with Doubly Linked Lists.
Here is source code of the C++ Program to demonstrate Hash Tables Chaining with Doubly Linked Lists. The C++ program is successfully compiled and run on a Linux system. The program output is also shown below. 
</div>
<pre lang="cpp" line="1" cssfile="hk1_style">
/*
 * C++ Program to Implement Hash Tables Chaining 
 * with Doubly Linked Lists
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
const int TABLE_SIZE = 25;
using namespace std;
/*
 * Node Declaration
 */
struct HashNode
{
    int data, key;
    HashNode *next;
    HashNode *prev;
};
/*
 * Class Declaration
 */
class HashMap
{
    public:
        HashNode **htable, **top;
        HashMap()
        {
            htable = new HashNode*[TABLE_SIZE];
            top = new HashNode*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
            {
            	htable[i] = NULL;
            	top[i] = NULL;
            }
        }
	~HashMap()
	{
            delete [] htable;
	}
		
	/*
         * Hash Function
	 */
	int HashFunc(int key)
	{
            return key % TABLE_SIZE;
        }
        
        /*
	 * Insert Element at a key
	 */
        void insert(int key, int value)
        {
            int hash_val = HashFunc(key);
            HashNode *entry = htable[hash_val];
            if (entry == NULL)
            {
	        entry = new HashNode;
                entry->data = value;
        	entry->key = key;
        	entry->next = NULL;
        	entry->prev = NULL;
        	htable[hash_val] = entry;
        	top[hash_val] = entry;
            }
            else
            {
	        while (entry != NULL)
	            entry = entry->next;
		entry = new HashNode;
        	entry->data = value;
                entry->key = key;
        	entry->next = NULL;
        	entry->prev = top[hash_val];
        	top[hash_val]->next = entry;
       		top[hash_val] = entry;
            }
        }
        
        /*
         * Remove Element at a key
	 */
	void remove(int key)
	{
	    int hash_val = HashFunc(key);
	    HashNode *entry = htable[hash_val];
	    if (entry->key != key || entry == NULL)
	    {
	        cout<<"No Element found at key: "<<key<<endl;
	        return;
	    }
	    while (entry != NULL)
	    {
                if (entry->next == NULL)
	        {
                    if (entry->prev == NULL)
		    {
		        htable[hash_val] = NULL;
		        top[hash_val] = NULL;
		        delete entry;
		        break;
		    }
		    else
		    {
		        top[hash_val] = entry->prev;
		        top[hash_val]->next = NULL;
			delete entry;
		        entry = top[hash_val];
		    }
                }
		entry = entry->next;
	    }
	}
	/*
	 * Search Element at a key
	 */
	void get(int key)
	{
	    int hash_val = HashFunc(key);
	    bool flag = false;
	    HashNode* entry = htable[hash_val];
	    if (entry != NULL)
	    {
	        while (entry != NULL)
	        {
	            if (entry->key == key)
				{
	                flag = true;
				}
		    if(flag)
		    {
		        cout<<"Element found at key "<<key<<": ";
				cout<<entry->data<<endl;
		    }
		    entry = entry->next;
                }
	    }
	    if(!flag)
	        cout<<"No Element found at key "<<key<<endl;
        }
};

/*
 * Main Contains Menu
*/
int main()
{
    HashMap hash;
    int key, value;
    int choice;
    while (1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Hash Table"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Insert element into the table"<<endl;
        cout<<"2.Search element from the key"<<endl;
        cout<<"3.Delete element at a key"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter element to be inserted: ";
            cin>>value;
            cout<<"Enter key at which element to be inserted: ";
            cin>>key;
            hash.insert(key, value);
            break;
        case 2:
            cout<<"Enter key of the element to be searched: ";
            cin>>key;
            hash.get(key);
            break;
        case 3:
            cout<<"Enter key of the element to be deleted: ";
            cin>>key;
            hash.remove(key);
            break;
        case 4:
            exit(1);
        default:
           cout<<"\nEnter correct option\n";
       }
    }
    return 0;
}

</pre>
<br/>
<pre lang="bash" cssfile="hk1_style">
$ g++ hash_doubly.cpp
$ a.out
----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 1
Enter element to be inserted: 12
Enter key at which element to be inserted: 1

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 1
Enter element to be inserted: 24
Enter key at which element to be inserted: 1

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 1
Enter element to be inserted: 36
Enter key at which element to be inserted: 1

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 1
Enter element to be inserted: 48
Enter key at which element to be inserted: 2

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 1
Enter element to be inserted: 60
Enter key at which element to be inserted: 2

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 1
Enter element to be inserted: 72
Enter key at which element to be inserted: 2

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 2
Enter key of the element to be searched: 3
No Element found at key 3

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 3
Enter key of the element to be deleted: 2

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 2
Enter key of the element to be searched: 2
Element found at key 2: 48
Element found at key 2: 60

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 3
Enter key of the element to be deleted: 1

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 2
Enter key of the element to be searched: 1
Element found at key 1: 12
Element found at key 1: 24

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 3
Enter key of the element to be deleted: 1

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 2
Enter key of the element to be searched: 1
Element found at key 1: 12

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 1
Enter element to be inserted: 100
Enter key at which element to be inserted: 1

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 2
Enter key of the element to be searched: 1
Element found at key 1: 12
Element found at key 1: 100

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 3
Enter key of the element to be deleted: 4
No Element found at key: 4

----------------------
Operations on Hash Table

----------------------
1.Insert element into the table
2.Search element from the key
3.Delete element at a key
4.Exit
Enter your choice: 4


------------------
(program exited with code: 1)
Press return to continue

</pre>

<strong>Sanfoundry Global Education & Learning Series – 1000 C++ Programs.</strong>
<div style="text-align:justify">
If you wish to look at all C++ Programming examples, go to <a href="http://www.sanfoundry.com/">C++ Programs</a>.
</div>
<strong>If you liked this C++ Program, kindly share, recommend or like below!</strong>
