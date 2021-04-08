class TreeAncestor {
    int height;
    vector < vector < int > > up;
public:
    TreeAncestor(int n, vector<int>& parent) {
        height = (int)ceil(log2(n));
        up = vector < vector < int > > (n, vector < int > (height + 1, -1));
        
        for(int v = 0; v < n; v++)
            up[v][0] = parent[v];
        
        for(int i = 1; i <= height; i++)
            for(int v = 0; v < n; v++){
                if (up[v][i-1] != -1)
                    up[v][i] = up[up[v][i-1]][i-1];
                if (up[v][i] == -1) continue;
            }
    }
    
    int getKthAncestor(int node, int k) {
        for (int i = 0; i <= height; i++){
            if (k & (1 << i)){
                node = up[node][i];
                if (node == -1) break;
            }
        }
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */
