class DisjointSets {
    int n;
    vector < int > parent, rank;
public:
    DisjointSets(int n) {
        this->n = n;
        rank.resize(n), parent.resize(n);
        for (int i = 0; i < n; i++) rank[i] = 0, parent[i] = i; 
    } 
    
    int findParent(int u){
        if (u == parent[u]) return u;
        return parent[u] = findParent(parent[u]);
    } 
    
    void merge(int x, int y){ 
        int rootX = findParent(x), rootY = findParent(y);
        
        if (rootX != rootY) { // Make tree with smaller height a subtree of the other tree
            if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
            else if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
            else parent[rootY] = rootX, rank[rootX] += 1;
        }
    }
    
    bool connected(int x, int y) {
        return findParent(x) == findParent(y);
    }
    
    int numComponents(){
        int conn = 0;
        for(int i = 0; i < n; i++) if(parent[i] == i) conn++;
        return conn;
    }
};
