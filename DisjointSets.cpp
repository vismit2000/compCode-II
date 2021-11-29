class DisjointSets{ 
    int *parent, *rnk; 
    int n; 
 public: 
    DisjointSets(int n) { 
        this->n = n; 
        parent = new int[n+1]; 
        rnk = new int[n+1]; 
 
        for (int i = 0; i <= n; i++) { 
            rnk[i] = 0; 
            parent[i] = i; 
        } 
    } 
  
    // Find the parent of a node 'u' - Path Compression 
    int findParent(int u){ 
        if (u != parent[u]) 
            parent[u] = findParent(parent[u]); 
        return parent[u]; 
    } 
    
    // Union by rank
    void merge(int x, int y){ 
        x = findParent(x), y = findParent(y); 
  
        // Make tree with smaller height a subtree of the other tree
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else // If rnk[x] <= rnk[y] 
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
}; 


// Better:

class DisjointSets {
    unordered_map < int, int > parent, rnk;
public:
    DisjointSets(int n) { 
        for (int i = 0; i < n; i++) rnk[i] = 0, parent[i] = i; 
    } 
    
    int findParent(int u){ 
        if (!parent.count(u)) parent[u] = u;
        if (u != parent[u]) parent[u] = findParent(parent[u]); 
        return parent[u]; 
    } 
    
    void merge(int x, int y){ 
        x = findParent(x), y = findParent(y); 
  
        // Make tree with smaller height a subtree of the other tree
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else // If rnk[x] <= rnk[y] 
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    }
};
