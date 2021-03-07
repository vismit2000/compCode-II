// https://leetcode.com/problems/sum-of-distances-in-tree/

class Solution {
    int n;
    vector < vector < int > > tree;
    vector < int > dp1, dp2, numNodesSubtree;
public:
    void populateNumNodesSubtree(int node, int parent = -1){
        numNodesSubtree[node] = 1;
        for(auto child : tree[node]){
            if(child != parent){
                populateNumNodesSubtree(child, node);
                numNodesSubtree[node] += numNodesSubtree[child];
            }
        }
    }
    
    void dfs1(int node, int parent = -1){
        dp1[node] = numNodesSubtree[node] - 1;
        for(auto child : tree[node]){
            if(child != parent){
                dfs1(child, node);
                dp1[node] += dp1[child];
            }
        }
    }
    
    void dfs2(int node, int parent = -1){
        dp2[node] = dp1[node];
        if(parent != -1)
            dp2[node] += (dp2[parent] - (dp1[node] + numNodesSubtree[node])) + (n - numNodesSubtree[node]);
        
        for(auto child : tree[node]){
            if(child != parent)
                dfs2(child, node);
        }
    }
    
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        n = N;
        tree = vector < vector < int > > (N);
        dp1.assign(N, 0);
        dp2.assign(N, 0);
        numNodesSubtree.assign(N, 0);
        
        for(auto edge : edges){
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }
        populateNumNodesSubtree(0);
        dfs1(0);
        dfs2(0);
        
        return dp2;
    }
};
