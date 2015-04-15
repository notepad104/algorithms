/**
 * C++ Program to Check whether Undirected Graph is Connected using DFS
 */
#include <iostream>
#include <list>
#include <stack>
using namespace std;
/**
 * Class Declaration
 */
class Graph
{
    private:
        int V;
        list<int> *adj;
        void DFSUtil(int v, bool visited[]);
    public:
        Graph(int V)
        {
            this->V = V;
            adj = new list<int>[V];
        }
        ~Graph()
        {
            delete [] adj;
        }
        void addEdge(int v, int w);
        bool isConnected();
        Graph getTranspose();
};

/**
 *  A recursive function to print DFS starting from v
 */
void Graph::DFSUtil(int v, bool visited[])
{
    visited[v] = true;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

/**
 * Function that returns reverse (or transpose) of this graph
 */
Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}
/**
 * Add Edge to connect v and w
 */
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

/**
 * Check if Graph is Connected
 */
bool Graph::isConnected()
{
    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    DFSUtil(0, visited);
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
             return false;
    Graph gr = getTranspose();
    for(int i = 0; i < V; i++)
        visited[i] = false;
    gr.DFSUtil(0, visited);
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
             return false;
    return true;
}
/**
 * Main Contains Menu
 */
int main()
{
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(3, 0);
    g1.addEdge(2, 4);
    g1.addEdge(4, 2);
    if (g1.isConnected())
        cout<<"The Graph is Connected"<<endl;
    else
        cout<<"The Graph is not Connected"<<endl;

    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    if (g2.isConnected())
        cout<<"The Graph is Connected"<<endl;
    else
        cout<<"The Graph is not Connected"<<endl;

    return 0;
}
