/*
 * C++ Program to Check whether Graph is a Bipartite using DFS
 */
#include <iostream>
#include <cstdio>
#include <stack>
#include <list>
using namespace std;
/*
 * Class Declaration
 */
class Graph
{
    public:
        int V;
        list<int> *adj;
        Graph(int V);
        void addEdge(int v, int w);
};
/*
 * Constructor
 */
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
/*
 * Adding Edge to Graph
 */
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}
/*
 * Class Bipartite Declaration
 */
class Bipartite
{
    private:
        bool isBipartite;
        bool *color;
        bool *marked;
        int *edgeTo;
        stack<int> cycle;
    public:
        Bipartite(Graph G)
        {
            isBipartite = true;
            color = new bool [G.V];
            marked = new bool [G.V];
            edgeTo = new int [G.V];
            for (int v = 0; v < G.V; v++)
            {
                if (!marked[v])
                {
                    color[v] = false;
                    dfs(G, v);
                }
            }
        }
        /*
         * DFS
         */
        void dfs(Graph G, int v)
        {
            marked[v] = true;
            list<int>::iterator w;
            for (w = G.adj[v].begin(); w != G.adj[v].end(); w++)
            {
                if (!cycle.empty())
                    return;
                if (!marked[*w])
                {
                    edgeTo[*w] = v;
                    color[*w] = !color[v];
                    dfs(G, *w);
                }
                else if (color[*w] == color[v])
                {
                    isBipartite = false;
                    cycle.push(*w);
                    for (int x = v; x != *w; x = edgeTo[x])
                    {
                        cycle.push(x);
                    }
                    cycle.push(*w);
                }
            }
        }
        /* 
         * Returns true if graph is Bipartite
         */
        bool isBi()
        {
            return isBipartite;
        }
};

/*
 * Main Contains Menu
 */
int main()
{
    Graph g1(4);
    g1.addEdge(0, 1);
    g1.addEdge(0, 3);
    g1.addEdge(1, 0);
    g1.addEdge(1, 2);
    g1.addEdge(2, 1);
    g1.addEdge(2, 3);
    g1.addEdge(3, 2);
    g1.addEdge(3, 0);
    Bipartite b(g1);
    if (b.isBi())
        cout<<"The graph is Bipartite"<<endl;
    else
        cout<<"The graph is not Bipartite"<<endl;
}
