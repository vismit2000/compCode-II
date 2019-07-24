// https://leetcode.com/contest/weekly-contest-146/problems/shortest-path-with-alternating-colors/

/*
Consider a directed graph, with nodes labelled 0, 1, ..., n-1.  In this graph, each edge is either red or blue, and there could be self-edges or parallel edges.

Each [i, j] in red_edges denotes a red directed edge from node i to node j.  Similarly, each [i, j] in blue_edges denotes a blue directed edge from node i to node j.

Return an array answer of length n, where each answer[X] is the length of the shortest path from node 0 to node X such that the edge colors alternate along the path (or -1 if such a path doesn't exist).
*/

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) 
    {
        vector < pair < int, int > > adjList[n];
        vector < int > distance(n, -1);
        
        bool visited[n][2];
        
        memset(visited, false, sizeof(visited));
        
        for(auto it : red_edges)
            adjList[it[0]].push_back({it[1], 0});
        
        for(auto it : blue_edges)
            adjList[it[0]].push_back({it[1], 1});
        
        distance[0] = 0;
        
        queue < tuple < int, int, int > > q;
        tuple < int, int, int > placeholder;
        int ele, color, dist;
        
        for(auto it : adjList[0])
            q.push({it.first, 1, it.second});
        
        while(!q.empty())
        {
            placeholder = q.front();
            q.pop();
            
            ele = get <0> (placeholder);
            dist = get <1> (placeholder);
            color = get <2> (placeholder);
            
            visited[ele][color] = true;
            
            if(distance[ele] == -1)
                distance[ele] = dist;
            else
                distance[ele] = min(distance[ele],dist);
            
            for(auto it : adjList[ele])
            {
                if(it.second == 1-color && visited[it.first][1-color] == false)
                    q.push(make_tuple(it.first, dist+1, 1-color));
            }
        }
        return distance;
    }
};
