// https://leetcode.com/problems/course-schedule/

class Solution {
public:
    
    vector < vector < int> > adj;
    vector <int> parent, color;
    int cycle_start, n;
    
    bool dfs(int v)
    {
        color[v] = 1;
        for(int u : adj[v])
        {
            if(color[u] == 0)
            {
                parent[u] = v;
                if(dfs(u))
                    return true;
            }
            else if(color[u] == 1)
            {
                cycle_start = u;
                return true;
            }
        }
        color[v] = 2;
        return false;
    }
    
    bool isCyclic()
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
            return false;
        return true;
    }
    
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
    {
        n = numCourses;
        adj.resize(n);
        
        for(auto v : prerequisites)
            adj[v[1]].push_back(v[0]);
        
        return !isCyclic();
    }
};
