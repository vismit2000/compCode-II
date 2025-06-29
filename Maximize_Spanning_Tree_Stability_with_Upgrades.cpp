# https://leetcode.com/problems/maximize-spanning-tree-stability-with-upgrades/

#include<bits/stdc++.h> 
using namespace std; 
using Edge = tuple<int, int, int, int>;

class DisjointSet {
    vector<int> parent, rank;

public:
    DisjointSet(int n) : parent(n + 1), rank(n + 1, 0) {
        for (int i = 0; i <= n; ++i) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]); // Path Compression
        return parent[u];
    }
    void merge(int x, int y)   // Union by rank 
    { 
        x = find(x), y = find(y); 
  
        /* Make tree with smaller height 
           a subtree of the other tree  */
        if (rank[x] > rank[y]) 
            parent[y] = x; 
        else // If rank[x] <= rank[y] 
            parent[x] = y; 
        if (rank[x] == rank[y]) 
            rank[y]++; 
    } 
}; 

class Graph 
{ 
    int V, E; 
    vector < Edge > edges; 
  
public: 
    Graph(int V, int E) { 
        this->V = V; 
        this->E = E; 
    } 
    void addEdge(int u, int v, int w, int must) { 
        edges.push_back({w, u, v, must}); 
    } 
    bool kruskalMST(int k, int min_wt); 
}; 
  

  
bool Graph::kruskalMST(int k, int min_wt) {  
    sort(edges.rbegin(), edges.rend()); 
    DisjointSet ds(V); 
    int total_edges = 0;
  
    for (auto &[w, u, v, must] : edges) { 
        if(must == 0) continue;
        if (w < min_wt) return false;
  
        int set_u = ds.find(u); 
        int set_v = ds.find(v);

        if (set_u == set_v) return false;
  
        if (set_u != set_v) { 
            total_edges += 1;
            ds.merge(set_u, set_v); 
        } 
    }
    for (auto &[w, u, v, must] : edges) {
        if(must == 1) continue;
        int set_u = ds.find(u); 
        int set_v = ds.find(v); 
    
        if (set_u != set_v) 
        {
            if (w < min_wt){
                if(k == 0) return false;
                k -= 1;
                if (w*2 < min_wt) return false;
            }
            total_edges += 1;
            ds.merge(set_u, set_v); 
        } 
    } 
    return total_edges == V-1; 
}
class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        int lo = 1, hi = 0, mid, ans = -1;
        for(auto edge: edges)
            hi = max(hi, edge[2] * 2);
            
        while(lo <= hi){
            mid = lo + (hi-lo) / 2;

            Graph g(n, edges.size());
            for(auto edge: edges)
                g.addEdge(edge[0], edge[1], edge[2], edge[3]);
       
            if(g.kruskalMST(k, mid)){
                ans = mid;
                lo = mid + 1;
            }
            else
                hi = mid - 1;
        }
        return ans;
    }
};
