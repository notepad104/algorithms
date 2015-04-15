/*
 * C++ Program to Implement Hash Tables Chaining with List Heads
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
using namespace std;
const int TABLE_SIZE = 5;
/*
 * Link List Class Declaration
 */
class LinkedHash
{
	public:
        int key, value;
        LinkedHash *next;
        LinkedHash(int key, int value)
        {
            this->key = key;
            this->value = value;
            this->next = NULL;
        }
};
/*
 * HashMap Class Declaration
 */
class HashMap
{
    private:
        LinkedHash **htable;
    public:
        HashMap()
        {
            htable = new LinkedHash*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
            {
                htable[i] = NULL;
            }
        }
        ~HashMap()
        {
            for (int i = 0; i < TABLE_SIZE; i++)
            {
                if (htable[i] != NULL)
                {
                    LinkedHash *prev = NULL;
                    LinkedHash *entry = htable[i];
                    while (entry != NULL)
                    {
                        prev = entry;
                        entry = entry->next;
                        delete prev;
                    }
                }
                delete[] htable;
            }
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
        void Insert(int key, int value)
        {
            int hash_val = HashFunc(key);
            if (htable[hash_val] == NULL)
                htable[hash_val] = new LinkedHash(key, value);
            else
            {
                LinkedHash *entry = htable[hash_val];
                while (entry->next != NULL)
                    entry = entry->next;
                    if (entry->key == key)
                        entry->value = value;
                    else
                        entry->next = new LinkedHash(key, value);
            }
        }
        /*
	     * Search Element at a key
         */
        int Find(int key)
        {
            int hash_val = HashFunc(key);
            if (htable[hash_val] == NULL)
                return -1;
            else
            {
                LinkedHash *entry = htable[hash_val];
                while (entry != NULL && entry->key != key)
                    entry = entry->next;
                if (entry == NULL)
                    return -1;
                else
                    return entry->value;
            }
        }
        /*
	     * Delete Element at a key
         */
        void Delete(int key)
        {
            int hash_val = HashFunc(key);
            if (htable[hash_val] != NULL)
            {
                LinkedHash *entry = htable[hash_val];
                LinkedHash *prev = NULL;
                while (entry->next != NULL && entry->key != key)
                {
                    prev = entry;
                    entry = entry->next;
                }
                if (entry->key == key)
                {
                    if (prev == NULL)
                    {
                        LinkedHash *next = entry->next;
                        delete entry;
                        htable[hash_val] = next;
                    }
                    else
                    {
                        LinkedHash *next = entry->next;
                        delete entry;
                        prev->next = next;
                    }
                }
            }
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
    while(1)
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
            hash.Insert(key, value);
            break;
        case 2:
            cout<<"Enter key of the element to be searched: ";
        	cin>>key;
        	if (hash.Find(key) == -1)
                cout<<"No element found at key "<<key<<endl;
            else
            {
                cout<<"Elements at key "<<key<<" : ";
                cout<<hash.Find(key)<<endl;
            }
            break;
        case 3:
            cout<<"Enter key of the element to be deleted: ";
            cin>>key;
            if (hash.Find(key) == -1)
                cout<<"Key "<<key<<" is empty, nothing to delete"<<endl;
            else
            {
                hash.Delete(key);
                cout<<"Entry Deleted"<<endl;
            }
            break;
        case 4:
            exit(1);
        default:
           cout<<"\nEnter correct option\n";
       }
    }
    return 0;
}

