//Given a directed graph containing cycle. Find minimum distance of every node from cycle.

//Concepts used : Finding cycle in a directed graph, multi-source BFS using priority queue

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi; 

vector < vector <int> > adj;
vector <int> color, parent, cycle;
int cycle_start, cycle_end, n;

bool dfs(int v)
{
    color[v] = 1;
    for(int u : adj[v])
    {
        if(parent[v] != u && color[u] == 0)
        {
            parent[u] = v;
            if(dfs(u))
                return true;
        }
        else if(parent[v] != u && color[u] == 1)
        {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
    }
    color[v] == 2;
    return false;
}

void find_cycle()
{
    color.assign(n, 0);
    parent.assign(n, -1);
    cycle_start = -1;

    for(int v = 0; v < n; v++)
    {
        if(dfs(v))
            break;
    }

    if(cycle_start == -1)
        return;         // or cout << "Acyclic" << endl;

    else
    {
        for(int v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start);
    }
}

vector<int> findRemoteness(int g_nodes, vector<int> g_from, vector<int> g_to) 
{
    n = g_nodes;

    vector <int> remote(n);

    adj.resize(n);

    int edges = g_from.size();

    for(int i = 0; i < edges; i++)
    {
        adj[g_from[i]-1].push_back(g_to[i]-1);
        adj[g_to[i]-1].push_back(g_from[i]-1);
    }

    find_cycle();

    vector < bool > visited(n, false);

    priority_queue < pi, vector <pi>, greater<pi> > q;

    for(int i = 0; i < cycle.size(); i++)
    {
        q.push({0, cycle[i]});
        visited[cycle[i]] = true; // since multi-source BFS
    }

    while(!q.empty())
    {
        int ele = q.top().second;
        int rem = q.top().first;

        q.pop();

        visited[ele] = true;
        remote[ele] = rem;

        for(int u : adj[ele])
        {
            if(!visited[u])
                q.push({rem+1, u});
        }
    }
    return remote;
}
int main()
{
    int nodes, edges;
    cin >> nodes >> edges;

    vector<int> g_from(edges);
    vector<int> g_to(edges);

    for (int i = 0; i < edges; i++) 
        cin >> g_from[i] >> g_to[i];

    vector<int> result = findRemoteness(nodes, g_from, g_to);

    for (int i = 0; i < result.size(); i++)
        cout << result[i] << endl;

    return 0;
}

// Sample Input
// 6 (nodes) 6 (edges)
// 1 2
// 3 4
// 6 4
// 2 3
// 1 3
// 3 5 
// Sample Output
// 0
// 0
// 0
// 1
// 1
// 2

// 6 6
// 1 2
// 3 4
// 6 4
// 2 3
// 1 3
// 3 5 
