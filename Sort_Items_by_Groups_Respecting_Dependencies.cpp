/*
Problem: https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/
Approach: https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/discuss/402945/C%2B%2B-with-picture-generic-topological-sort
*/

class Solution {
public:
    bool dfs(int v, vector < vector < int > > &adj, vector<int> &color, vector<int> &ans){
        color[v] = 1;
        for (int u : adj[v]) {
            if (color[u] == 0){
                if(dfs(u, adj, color, ans))
                    return true;
            }
            else if(color[u] == 1)
                return true;
        }
        ans.push_back(v);
        color[v] = 2;
        return false;
    }
    
    bool topological_sort(int n, vector < vector < int > > &adj, vector<int> &color, vector<int> &ans){
        color.assign(n, 0);
        for (int i = n-1; i >= 0; i--) {
            if (!color[i]){
                bool res = dfs(i, adj, color, ans);
                if(res == true)
                    return true;
            }
        }
        reverse(ans.begin(), ans.end());
        return false;
    }
    
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        vector < vector < int > > adj(n + 2*m);
        for (int i = 0; i < n; i++) {
            if (group[i] != -1) {
                adj[n + group[i]].push_back(i);
                adj[i].push_back(n + m + group[i]);
            }
            for (auto j : beforeItems[i]) {
                if (group[i] != -1 && group[i] == group[j]) 
                    adj[j].push_back(i);
                else {
                    auto ig = group[i] == -1 ? i : n + group[i];
                    auto jg = group[j] == -1 ? j : n + m + group[j];
                    adj[jg].push_back(ig);
                }
            }
        }
        
        vector < int > color, ans, result;
        
        bool isCyclic = topological_sort(n + 2*m, adj, color, ans);
        
        if(isCyclic)
            return vector < int > {};
        
        for(int ele : ans)
            if(ele < n)
                result.push_back(ele);
        
        return result;
    }
};
