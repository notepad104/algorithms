/*
 * C++ Program to Implement Suffix Tree
 */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#define MAX_LENGTH 1000
#define HASH_TABLE_SIZE 2179
using namespace std;
   
/** Class Node **/
class Node     
{    
    public: 
        int suffix_node;    
        static int Count;
        /** Constructor **/
        Node() 
        { 
            suffix_node = -1; 
        }    
};
int Node::Count = 1;
char *T = new char[MAX_LENGTH];
/** Class Suffix Tree **/
class SuffixTree
{
    public:  
        int N;       
        /** Class Suffix **/
        class Suffix 
        {
                public: 
                    int origin_node;
                    int first_char_index;
                    int last_char_index;
                    /** Constructor **/
                    Suffix(int node, int start, int stop)
                    {
                        origin_node = node;
                        first_char_index = start;
                        last_char_index = stop;
                    }
                        
                    /** Function Implicit  **/
                    bool Implicit()
                    {
                        return first_char_index > last_char_index; 
                    }
                        
                    /** Function Explicit  **/
                    bool Explicit()
                    { 
                        return first_char_index > last_char_index; 
                    }
                        
                    /** Function Canonize() **/
                    void Canonize()
                    {
                        if (!Explicit()) 
                        {
                            Edge *edge = Find(origin_node, T[first_char_index]);
                            int edge_span = edge->last_char_index - edge->first_char_index;
                            while (edge_span <= (last_char_index - first_char_index)) 
                            {
                                first_char_index = first_char_index + edge_span + 1;
                                origin_node = edge->end_node;
                                if (first_char_index <= last_char_index) 
                                {
                                    edge = Find(edge->end_node, T[first_char_index]);
                                    edge_span = edge->last_char_index - edge->first_char_index;
                                }
                            }
                        }
                    }
        };   
         /** Class Edge **/       
        class Edge 
        {
            public: 
                int first_char_index;
                int last_char_index;
                int end_node;
                int start_node;
                /** Constructor **/
                Edge()
                {
                    start_node = -1;
                }
                
                /** Constructor **/
                Edge(int init_first, int init_last, int parent_node)
                {
                    first_char_index = init_first;
                    last_char_index = init_last;
                    start_node = parent_node;
                    end_node = Node::Count++;
                }

                /** function Insert () **/
                void Insert()
                {
                    int i = Hash(start_node, T[first_char_index]);
                    while (Edges[i]->start_node != -1)
                        i = ++i % HASH_TABLE_SIZE;
                    Edges[i] = this;
                }
                  
                /** function SplitEdge () **/
                int SplitEdge(Suffix *s)
                {
                    Remove();
                    Edge *new_edge =  new Edge(first_char_index, 
                            first_char_index + s->last_char_index - s->first_char_index, 
                            s->origin_node);
                    new_edge->Insert();
                    Nodes[new_edge->end_node]->suffix_node = s->origin_node;
                    first_char_index += s->last_char_index - s->first_char_index + 1;
                    start_node = new_edge->end_node;
                    Insert();
                    return new_edge->end_node;
                }
        
                /** function Remove () **/
                void Remove()
                {
                    int i = Hash(start_node, T[first_char_index]);
                    while (Edges[i]->start_node != start_node ||
                           Edges[i]->first_char_index != first_char_index)
                        i = ++i % HASH_TABLE_SIZE;
                    for ( ; ; ) 
                    {
                        Edges[i]->start_node = -1;
                        int j = i;
                        for ( ; ; ) 
                        {
                            i = ++i % HASH_TABLE_SIZE;
                            if (Edges[i]->start_node == -1)
                                return;
                            int r = Hash(Edges[i]->start_node, T[Edges[i]->first_char_index]);
                            if (i >= r && r > j)
                                continue;
                            if (r > j && j > i)
                                continue;
                            if (j > i && i >= r)
                                continue;
                            break;
                        }
                        Edges[j] = Edges[i];
                    }
                }        
        };
        Edge *Edges ;    
        Node *Nodes ;
        Suffix *active;
        /** Constructor */
        SuffixTree()
        {
            Edges = new Edge[HASH_TABLE_SIZE];
            for (int i = 0; i < HASH_TABLE_SIZE; i++)
                Edges[i] = new Edge();
            Nodes = new Node[MAX_LENGTH * 2];
            for (int i = 0; i < MAX_LENGTH * 2 ; i++)
                Nodes[i] = new Node();
            active = new Suffix(0, 0, -1);   
        }

        /** Function Find() - function to find an edge **/
        Edge *Find( int node, int c )
        {
            int i = Hash(node, c);
            for ( ; ; ) 
            {
                if (Edges[i]->start_node == node)
                    if (c == T[Edges[i]->first_char_index])
                        return Edges[i];
                    if (Edges[i]->start_node == -1)
                        return Edges[i];
                    i = ++i % HASH_TABLE_SIZE;
            }
        }

        /** Function Hash() - edges are inserted into the hash table 
        using this hashing function **/

        int Hash(int node, int c)
        {
            return (( node << 8 ) + c ) % HASH_TABLE_SIZE;
        }

        /** Function AddPrefix() - called repetitively, 
        once for each of the prefixes of the input string **/

        void AddPrefix(Suffix *active, int last_char_index)
        {
            int parent_node;
            int last_parent_node = -1;
            for ( ; ; ) 
            {
                Edge *edge;
                parent_node = active->origin_node;
                if (active->Explicit()) 
                {
                    edge = Find(active->origin_node, T[last_char_index]);
                    if (edge->start_node != -1)
                        break;
                } 
                else 
                { 
                    edge = Find(active->origin_node, T[active->first_char_index]);
                    int span = active->last_char_index - active->first_char_index;
                    if (T[edge->first_char_index + span + 1] == T[last_char_index])
                        break;
                    parent_node = edge->SplitEdge(active);
                }
                Edge *new_edge = new Edge(last_char_index, N, parent_node);
                new_edge->Insert();
                if (last_parent_node > 0)
                    Nodes[last_parent_node]->suffix_node = parent_node;
                last_parent_node = parent_node;
                if (active->origin_node == 0)
                    active->first_char_index++;
                else
                    active->origin_node = Nodes[active->origin_node]->suffix_node;
                active->Canonize();
            }
            if (last_parent_node > 0)
                Nodes[last_parent_node]->suffix_node = parent_node;
            active->last_char_index++;  
            active->Canonize();
        }

        /** Function to print all contents and details of suffix tree **/
        void dump_edges(int current_n)
        {
            cout<<" Start  End  Suf  First Last  String"<<endl;
            for (int j = 0 ; j < HASH_TABLE_SIZE ; j++) 
            {
                Edge *s = Edges[j];
                if (s->start_node == -1)
                    continue;
                printf("%5d %5d %3d %5d %6d   ",s->start_node, s->end_node, 
                                            Nodes[s->end_node]->suffix_node, 
                                    s->first_char_index, s->last_char_index);
                int top;
                if (current_n > s->last_char_index)
                    top = s->last_char_index;
                else
                    top = current_n;
                for (int l = s->first_char_index ; l <= top; l++)
                    cout<<T[l];
                cout<<endl;
            }
        } 
};

/** Main Function **/
int main()
{
    cout<<"Suffix Tree Test\n";
    cout<<"Enter string\n";     
    /** Construct Suffix Tree **/       
    SuffixTree *st;
    scanf("%s",st->T);
    st->N = strlen(st->T) - 1;  
    for (int i = 0 ; i <= st->N ; i++)
        st->AddPrefix(st->active, i);
    st->dump_edges(st->N);    
    return 0;
}
