#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <list>
#include <queue>
#include <climits>
#include <vector>
#include <cstdlib>
using namespace std;
int *color, *parent, *dist;
struct node
{
    int num;
    node *next;
    node *last;
}*adj;
// creates a list of n edges
// number of nodes are k are maximum number given to a node is k
node *adjacency_list(int k, int n)
{
    adj = new node [k];
    for (int i = 0; i < k; i++)
    {
        adj[i].next = NULL;
        adj[i].last = &adj[i];
    }
    while (n--)
    {
        int x, y;
        cin>>x>>y;
        node *p;
        p = &adj[x];
        p = p->last;
        p->next = new node;
        p = p->next;
        p->num = y;
        p->next = NULL;
        adj[x].last = p;
    }
}
// white=0,gray=1,black=2
void bfs(int s)
{
    color = new int [V];
    parent = new int [V];
    dist = new int [V];
    queue <int> q;
    for (int i = 0; i < V; i++)
    {
        color[i] = 0;
        dist[i] = 1000000;
        parent[i] = 0;
    }
    color[s] = 1;
    dist[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

    }
}
int main()
{
    return 0;
}
