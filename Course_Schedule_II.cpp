// https://leetcode.com/problems/course-schedule-ii/

/*
There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.
*/

class Solution {
public:
    
    vector < vector < int> > adj;
    vector <int> ans, visited, color;
    bool isCyclic;
    
    void dfs(int v)
    {
        color[v] = 1;
        visited[v] = 1;
        for(auto u : adj[v])
        {
            if(color[u] == 1)
                isCyclic = true;
            if(!visited[u])
                dfs(u);
        }
        color[v] = 2;
        ans.push_back(v);
    }
    
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) 
    {
        adj.resize(numCourses);
        
        for(auto v : prerequisites)
            adj[v[0]].push_back(v[1]);
        
        visited.assign(numCourses, 0);
        color.assign(numCourses, 0);
        ans.clear();
        
        isCyclic = false;
        
        for(int i = 0; i < numCourses; i++)
        {
            if(!visited[i])
                dfs(i);
        }
        
        vector <int> emp;
        
        if(isCyclic)
            return emp;
        
        // reverse(ans.begin(), ans.end());
        
        return ans;
    }
};
