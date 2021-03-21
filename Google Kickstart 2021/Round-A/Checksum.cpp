#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

typedef pair < ll, ll > iPair;

class Graph { 
    ll V; 
    vector< pair < ll, iPair > > edges; 
  
public: 
    Graph(ll V) { 
        this->V = V;  
    } 
    void addEdge(ll u, ll v, ll w) { 
        edges.push_back({w, {u, v}}); 
    } 
  // Function to find MST using Kruskal's MST algorithm 
    ll kruskalMST(); 
}; 
  
class DisjointSets {      // To represent Disjoint Sets  
    ll *parent, *rnk; 
    ll n; 
  
 public: 
    DisjointSets(ll n) { 
        this->n = n; 
        parent = new ll[n+1]; 
        rnk = new ll[n+1]; 
 
        for (ll i = 0; i <= n; i++) { 
            rnk[i] = 0; 
            parent[i] = i; 
        } 
    } 
  
    // Find the parent of a node 'u' - Path Compression 
    ll findParent(ll u) { 
        if (u != parent[u]) 
            parent[u] = findParent(parent[u]); 
        return parent[u]; 
    } 
  
    void merge(ll x, ll y) {  // Union by rank 
        x = findParent(x), y = findParent(y); 
  
        /* Make tree with smaller height a subtree of the other tree */
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else // If rnk[x] <= rnk[y] 
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
}; 
  
ll Graph::kruskalMST() { 
    ll mst_wt = 0; // Initialize result 
    // Max Spanning Tree - This time
    sort(edges.rbegin(), edges.rend()); 
    DisjointSets ds(V); 
  
    vector< pair < ll, iPair > > ::iterator it; 
    for (it = edges.begin(); it != edges.end(); it++) { 
        ll u = it->second.first; 
        ll v = it->second.second; 
  
        ll set_u = ds.findParent(u); 
        ll set_v = ds.findParent(v); 
  
        // Check if the selected edge is creating a cycle or not (Cycle is created if u and v belong to same set) 
        if (set_u != set_v) { 
            mst_wt += it->first; 
            ds.merge(set_u, set_v); 
        } 
    } 
    return mst_wt; 
} 

int main(){
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
    
    boost;
    int t;
    cin >> t;
    for (int testcase = 1; testcase <= t; testcase++){
        cout << "Case #" << testcase << ": ";
        
        ll N, ans = 0;
        cin >> N;
        vector < vector < ll > > A(N, vector < ll > (N, 0)), B(N, vector < ll > (N, 0));
        vector < ll > R(N), C(N);

        for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) cin >> A[i][j];     
        for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) cin >> B[i][j];
        for(int i = 0; i < N; i++) cin >> R[i];
        for(int i = 0; i < N; i++) cin >> C[i];

        Graph g(2*N);

        ll total = 0;

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++){
                if(A[i][j] == -1)
                    g.addEdge(i, j + N, B[i][j]);
                total += B[i][j];
            }

        ll mst_wt = g.kruskalMST(); 
        
        cout << total - mst_wt << endl;        
    }
    return 0;
}
