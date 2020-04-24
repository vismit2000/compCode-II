// https://leetcode.com/problems/minimum-height-trees/

// Explanation: https://leetcode.com/problems/minimum-height-trees/discuss/76055/Share-some-thoughts

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) 
    {
        if(n == 1)
            return vector <int> {0};
        
        vector < vector < int > > v(n);
        
        for(auto edge : edges)
        {
            v[edge[0]].push_back(edge[1]);
            v[edge[1]].push_back(edge[0]);
        }
        
        vector < int > leaves;
        
        for(int i = 0; i < n; i++)
            if(v[i].size() == 1)
                leaves.push_back(i);
        
        while(n > 2)
        {
            n -= leaves.size();
            vector < int > newLeaves;
            
            for(int i : leaves)
            {
                int j = v[i][0]; // Remember i has only one neighbour - That's why it is a leaf
                v[j].erase(std::remove(v[j].begin(), v[j].end(), i), v[j].end());
                if(v[j].size() == 1)
                    newLeaves.push_back(j);
            }
            leaves = newLeaves;
        }
        return leaves;
    }
};
