#include<bits/stdc++.h> 
using namespace std; 
#define ll long long
typedef pair < ll, ll > iPair; 

map < iPair, ll > mp;

class Graph 
{ 
    ll V, E; 
    vector< pair < ll, iPair > > edges; 
  
public: 
    Graph(ll V, ll E) 
    { 
        this->V = V; 
        this->E = E; 
    } 
    void addEdge(ll u, ll v, ll w) 
    { 
        edges.push_back({w, {u, v}}); 
    } 
  // Function to find MST using Kruskal's MST algorithm 
    ll kruskalMST(); 
}; 
  
class DisjointSets         // To represent Disjoint Sets 
{ 
    ll *parent, *rnk; 
    ll n; 
  
 public: 
    DisjointSets(ll n) 
    { 
        this->n = n; 
        parent = new ll[n+1]; 
        rnk = new ll[n+1]; 
 
        for (ll i = 0; i <= n; i++) 
        { 
            rnk[i] = 0; 
            parent[i] = i; 
        } 
    } 
  
    // Find the parent of a node 'u' 
    // Path Compression 
    ll findParent(ll u) 
    { 
        if (u != parent[u]) 
            parent[u] = findParent(parent[u]); 
        return parent[u]; 
    } 
  
    void merge(ll x, ll y)   // Union by rank 
    { 
        x = findParent(x), y = findParent(y); 
  
        /* Make tree with smaller height 
           a subtree of the other tree  */
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else // If rnk[x] <= rnk[y] 
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
}; 
  
ll Graph::kruskalMST() 
{ 
    ll mst_wt = 0; // Initialize result 
    sort(edges.begin(), edges.end()); 
    DisjointSets ds(V); 
  
    vector< pair < ll, iPair > > ::iterator it; 
    for (it = edges.begin(); it != edges.end(); it++) 
    { 
        ll u = it->second.first; 
        ll v = it->second.second; 
  
        ll set_u = ds.findParent(u); 
        ll set_v = ds.findParent(v); 
  
        // Check if the selected edge is creating a cycle or not (Cycle is created if u and v belong to same set) 
        if (set_u != set_v) 
        { 
            mst_wt += it->first; 
            ds.merge(set_u, set_v); 
        } 
    } 
    return mst_wt; 
} 
  
int main() 
{ 
    int t;
    cin>>t;

    for(int q = 1; q <= t; q++)
    {
        cout<<"Case #"<<q<<": ";

        mp.clear();

        ll V, E, black; 
        cin >> V >> black;

        E = (V * (V-1)) / 2;
        
        Graph g(V, E); 

        ll a, b;

        for(ll i = 0; i < black; i++)
        {
            cin >> a >> b;
            a--, b--;
            if(a > b)
                swap(a, b);
            g.addEdge(a, b, 1);
            mp[{a, b}] = 1;
        }

        for(ll i = 0; i < V-1; i++)
        {
            for(ll j = i+1; j < V; j++)
            {
                if(!mp.count({i, j}))
                    g.addEdge(i, j, 2);
            }
        }
     
        ll mst_wt = g.kruskalMST(); 
        cout << mst_wt << endl; 
    }
    return 0; 
}
