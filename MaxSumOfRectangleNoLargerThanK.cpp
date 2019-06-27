//https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/

#define INF 0x3f3f3f3f
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) 
    {
        int n = matrix.size(), m= matrix[0].size(), best = -INF, temp;
        
        int sum[n+1][m+1];
        
        for(int i = 0; i <= n; i++)
            sum[i][0] = 0;
        for(int i = 0; i <= m; i++)
            sum[0][i] = 0;
        
        sum[1][1] = matrix[0][0];
        
        for(int i = 2; i <= n; i++)
            sum[i][1] = matrix[i-1][0] + sum[i-1][1];
            
        
        for(int i = 2; i <= m; i++)
            sum[1][i] = matrix[0][i-1] + sum[1][i-1];
                  
        for(int i = 2; i <= n; i++)
        {
            for(int j = 2; j <= m; j++)
            {
                sum[i][j] = sum[i][j-1] + sum[i-1][j] + matrix[i-1][j-1] - sum[i-1][j-1];
            }
        }
        
        for(int i = 1; i <= n; i++)
        {
            for(int j = i; j <= n; j++)
            {
                for(int p = 1; p <= m; p++)
                {
                    for(int q = p; q <= m; q++)
                    {
                        temp = sum[j][q] + sum[i-1][p-1] - sum[j][p-1] - sum[i-1][q];
                        if(temp <= k)
                            best = max(best, temp);
                        if(best == k)
                            return k;
                    }
                }
            }
        }
        return best;
    }
};