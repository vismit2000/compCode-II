// https://leetcode.com/problems/as-far-from-land-as-possible/

//Explanation: https://leetcode.com/problems/as-far-from-land-as-possible/discuss/360963/C%2B%2B-with-picture-DFS

/*
Given an N x N grid containing only values 0 and 1, where 0 represents water and 1 represents land, find a water cell such that its distance to the nearest land cell is maximized and return the distance.

The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.

If no land or water exists in the grid, return -1.
*/

class Solution {
public:
    
    int dist(int x1, int y1, int x2, int y2)
    {
        return abs(x1-x2) + abs(y1-y2);
    }
    
    void dfs(vector < vector <int> > &grid, int i, int j, int dist, bool land = false)
    {
        int n = grid.size(), m = grid[0].size();
        
        if(!land)
        {
            if(i < 0 || i >= n || j < 0 || j >= m || (grid[i][j] != 0 && grid[i][j] <= dist))
                return;

            grid[i][j] = dist;
        }
        
        dfs(grid, i-1, j, dist+1);
        dfs(grid, i+1, j, dist+1);
        dfs(grid, i, j-1, dist+1);
        dfs(grid, i, j+1, dist+1);
    }
    
    int maxDistance(vector<vector<int>>& grid) 
    {
        int n = grid.size();
        if(n == 0)
            return -1;
        int m = grid[0].size();
        if(m == 0)
            return -1;
                
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(grid[i][j] == 1)
                    dfs(grid, i, j, 1, true);
            }
        }
        
        int best = -1;
        
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
                if(grid[i][j] > 1)
                    best = max(best, grid[i][j] - 1);    
        }
        return best;
    }
};
