//https://leetcode.com/problems/minimum-falling-path-sum/

#define INF 0x3f3f3f3f
int dp[105][105];

int MIN(int a, int b, int c)
{
    return min(a, min(b, c));
}

int minFallingPath(vector<vector<int>>& A, int i, int j, int n, int m)
{
    if(i == n)
        return 0;
    
    if(j < 0 || j >= m)
        return INF;

    if(dp[i][j] != -1)
        return dp[i][j];
    
    int ret = A[i][j];
    
    ret += MIN(minFallingPath(A, i+1, j-1, n, m), minFallingPath(A, i+1, j, n, m), minFallingPath(A, i+1, j+1, n, m));
    
    return dp[i][j] = ret;
}

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& A) 
    {
        int n = A.size(), m = A[0].size();
        
        for(int i = 0; i < 105; i++)
        {
            for(int j = 0; j < 105; j++)
                dp[i][j] = -1;
        }
        
        int ans = INF;
        
        for(int i = 0; i < m; i++)
            ans = min(ans, minFallingPath(A, 0, i, n, m));
        
        return ans;
    }
};
