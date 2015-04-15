#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
struct TrieNode
{
    bool isfinal;
    char *data;
    int childs;
    TrieNode *nxt[256];
};

struct Trie
{
    TrieNode *root;
}*pTrie;

class HashTrie
{
    public:
        char *crt_data;
        int crt_data_len;
        char *crt_search_data;
        void trie_init_node(TrieNode *node);
        Trie *trie_new();
        void trie_delete(Trie *trie);
        void trie_node_free(TrieNode *node);
        void trie_del_data(Trie *trie, char *str);
        int trie_add_nodes(TrieNode *node, char *str, int pos);
        int trie_add(Trie *trie, char *str, char *data, int data_len);
        void del_data(TrieNode *node, char *str, int pos);
        int trie_search_node(TrieNode *node, char *str, int pos);
        void trie_search(Trie *trie, char *str);
};

void HashTrie::trie_init_node(TrieNode *node)
{
    for (int i = 0; i < 256; i++)
    {
        node->nxt[i] = 0;
    }
    node->childs = 0;
    node->isfinal = 0;
    node->data = 0;
}

Trie *HashTrie::trie_new()
{
    Trie *trie = new Trie;
    trie->root = new TrieNode;
    trie_init_node(trie->root);
    return trie;
}

void HashTrie::trie_node_free(TrieNode *node)
{
    for (int i = 0; i < 256; i++)
    {
        if (node->nxt[i])
            trie_node_free(node->nxt[i]);
    }
    free(node->data);
    free(node);
}

void HashTrie::trie_delete(Trie *trie)
{
    trie_node_free(trie->root);
    free(trie);
}

int HashTrie::trie_add_nodes(TrieNode *node, char *str, int pos)
{
    char ch = str[pos];
    if (ch)
    {
        cout<<node->nxt[ch]<<endl;
        if (node->nxt[ch] == 0)
        {
            node->nxt[ch] = new TrieNode;
            if (node->nxt[ch] == NULL)
                return 0;
            trie_init_node(node->nxt[ch]);
            node->childs++;
        }
        return trie_add_nodes(node->nxt[ch], str, pos + 1);
    }
    else
    {
        if (node->isfinal)
            free(node->data);
        node->isfinal = 1;
        if (crt_data && crt_data_len)
        {
            node->data = new char [crt_data_len];
            if (node->data == 0)
                return 0;
            node->data = crt_data;
        }
        else
        {
            node->data = NULL;
        }
        
        return 1;
    }
}

int HashTrie::trie_add(Trie *trie, char *str, char *data, int data_len)
{
    crt_data = data;
    crt_data_len = data_len;
    return trie_add_nodes(trie->root, str, 0);
}

void HashTrie::del_data(TrieNode *node, char *str, int pos)
{
    char ch = str[pos];
    if (ch)
    {
        if (node->nxt[ch])
        {
            del_data(node->nxt[ch], str, pos + 1);
            if (node->nxt[ch]->isfinal == 0 && node->nxt[ch]->childs == 0)
            {
                free(node->nxt[ch]);
                node->nxt[ch] = 0;
                node->childs--;
            }
        }
    }
    else
    {
        if (node->isfinal)
        {
            node->isfinal = 0;
            free(node->data);
            node->data = 0;
        }
    }
}
void HashTrie::trie_del_data(Trie *trie, char *str)
{
  del_data(trie->root, str, 0);
}

int HashTrie::trie_search_node(TrieNode *node, char *str, int pos)
{
    char ch = str[pos];
    if (ch)
    {
        
        if (node->nxt[ch])
            return trie_search_node(node->nxt[ch], str, pos + 1);
        else
            return 0;
    }
    else
    {
        if (node->isfinal)
        {
            crt_search_data = node->data;
            cout<<"Element found at string "<<str<<": ";
            cout<<crt_search_data<<endl;
            return 1;
        }
        else
            return 0;
    }
}

void HashTrie::trie_search(Trie *trie, char *str)
{
    crt_search_data = 0;
    if (trie_search_node(trie->root, str, 0))
    {
        return;
    }
    else
        cout<<"Element not found in the trie"<<endl;
}

int main()
{
    char data[100],str[100];
    HashTrie ht;
    Trie *root = ht.trie_new();
    int len;
    int choice;
    while(1)
    {
		cout<<"\n----------------------"<<endl;
		cout<<"Operations on Hash Trie"<<endl;
		cout<<"\n----------------------"<<endl;
		cout<<"1.Insert element into the Trie"<<endl;
	    cout<<"2.Search element from the Trie"<<endl;
	    cout<<"3.Delete element"<<endl;
	    cout<<"4.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
        	cout<<"Enter data string to be inserted: ";
        	scanf("%s",data);
        	len = strlen(data);
        	cout<<"Enter key string at which data is inserted: ";
        	scanf("%s",str);
            ht.trie_add(root, str, data, len);
            break;
        case 2:
            cout<<"Enter key string at which data is searched: ";
        	scanf("%s",str);
        	ht.trie_search(root, str);
            break;
        case 3:
            cout<<"Enter key string at which data to be deleted: ";
        	scanf("%s",str);
            ht.trie_del_data(root, str);
            break;
        case 4:
            exit(1);
        default:
           cout<<"\nEnter correct option\n";
           break;
       }
    }
}
