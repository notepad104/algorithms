/*
 * C++ Program to Check whether Graph is a Bipartite using BFS
 */
#include <iostream>
#include <queue>
#define V 4
using namespace std;

/* 
 * Returns true if graph G[V][V] is Bipartite
 */
bool isBipartite(int G[][V], int src)
{
    int colorArr[V];
    for (int i = 0; i < V; ++i)
        colorArr[i] = -1;
    colorArr[src] = 1;
    queue <int> q;
    q.push(src);
	while (!q.empty())
    {
        int u = q.front();
        q.pop();
	    for (int v = 0; v < V; ++v)
        {
            if (G[u][v] && colorArr[v] == -1)
            {
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
	        else if (G[u][v] && colorArr[v] == colorArr[u])
                return false;
        }
    }
    return true;
}

/* 
 * Main Contains Menu 
 */
int main()
{
    int G[][V] = {{0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    if (isBipartite(G, 0)) 
        cout << "The Graph is Bipartite"<<endl;
    else
        cout << "The Graph is Not Bipartite"<<endl;
    return 0;
}
