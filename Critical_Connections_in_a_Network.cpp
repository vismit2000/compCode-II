// https://leetcode.com/problems/critical-connections-in-a-network
/*
A brilliant post explaining the concept of articulation points and bridges: 
https://www.hackerearth.com/practice/notes/nj/
*/

#define INF 0x3f3f3f3f
class Solution {
public:
    
    vector < vector <int> > adj, bridges;
    vector <bool> visited; 
    
    vector <int> disc, low;
    
    void dfs(int u, int parent)
    {
        static int tim = 1;
        disc[u] = low[u] = tim++;
        int child = 0;
        visited[u] = true;
        
        for(auto ele: adj[u])
        {
            if(!visited[ele])
            {
                child++;
                dfs(ele, u);
                low[u] = min(low[u], low[ele]);
                if(low[ele] > disc[u])
                {
                    vector <int> temp;
                    temp.push_back(u);
                    temp.push_back(ele);
                    bridges.push_back(temp);
                }
            }
            else if (ele != parent)
            {
                low[u] = min(low[u], disc[ele]);
            }
        }
    }
    
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) 
    {
        adj.resize(n);
        
        for(int i = 0; i < connections.size(); i++)
        {
            adj[connections[i][0]].push_back(connections[i][1]);
            adj[connections[i][1]].push_back(connections[i][0]);
        }
                
        visited.resize(n, false);
        disc.resize(n, INF);
        low.resize(n, INF);
        
        for(int i = 0; i < n; i++)
        {
            if(!visited[i])
                dfs(i, -1);
        }
                
        return bridges;
    }
};


/*
Another Solution - Using Topological Sorting
Note that all critical connections should not be on any loop, so we can just use topological sorting to find them.
*/

class Solution {
public:
    queue<int> Q;
    vector<int> G[100005];
    int ind[100005];
    
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        memset(ind, 0, sizeof(ind));
        
        for(int i=0; i<connections.size(); ++i) {
            int a = connections[i][0];
            int b = connections[i][1];
            G[a].push_back(b);
            G[b].push_back(a);
            ind[a]++; ind[b]++;
        }
        
        for(int i=0; i<n; ++i) if(ind[i]==0 || ind[i]==1) Q.push(i);
        
        vector<vector<int>> ans;
        
        while(!Q.empty()) {
            int v = Q.front(); Q.pop();
            for(int i=0; i<G[v].size(); ++i) {
                int u = G[v][i];
                ans.push_back(vector{v, u});
                
                auto iter = find(G[u].begin(), G[u].end(), v);
                G[u].erase(iter);
          
                ind[u]--;
                if(ind[u]==0 || ind[u]==1) Q.push(u);
            }
        }
        return ans;
    }
};
