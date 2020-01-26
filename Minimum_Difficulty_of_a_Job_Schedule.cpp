// https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/

class Solution {
public:
    int minDifficulty(vector<int>& jobs, int d) {
        
        /*
            Minimum Sum Partition Problem:
        
            dp[i][j]: The minimum cost to finish the first j jobs in the first i days.
            
            dp[i][j] =  MIN { dp[i - 1][k] + MAX(difficulty[k + 1][j]) }
                      i-1<=k<j 
        */
        
        int n = jobs.size();
        if (d > n)
            return -1;
        
        vector < vector < int > > cost (n, vector < int > (n, 0));
        
        for (int i = 0 ; i < n ; ++i) 
            cost[i][i] = jobs[i];

        for (int l = 2 ; l <= n ; ++l) 
        {
            for (int i = 0, j = i + l - 1 ; i <= n - l ; ++i, ++j) 
            {
                cost[i][j] = max(cost[i][j - 1], jobs[j]);
            }
        }
        
        vector < vector < int > > dp (d, vector < int > (n, 0));
        
        for (int i = 0 ; i < n ; ++i)
            dp[0][i] = cost[0][i];
        
        for (int i = 1 ; i < d ; ++i) 
        {
            for (int j = i ; j < n ; ++j) 
            {
                int opt = INT_MAX;
                
                for (int k = i - 1 ; k < j ; ++k) 
                {
                    int sum = dp[i - 1][k] + cost[k + 1][j];
                    opt = min(opt, sum);
                }
                
                dp[i][j] = opt;
            }
        }
        
        return dp[d - 1][n - 1];
    }
};
