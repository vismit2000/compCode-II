// https://leetcode.com/problems/maximal-square/

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) 
    {
        int rows, cols;
        rows = matrix.size();
        if(rows == 0)
            return 0;
        cols = matrix[0].size();
        
        vector < vector < int > > dp(rows+1, vector < int > (cols+1, 0));
        
        int maxLen = 0;
        
        for(int i = 1; i <= rows; i++)
        {
            for(int j = 1; j <= cols; j++)
            {
                if(matrix[i-1][j-1] == '1')
                {
                    dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
                    maxLen = max(maxLen, dp[i][j]);
                }
            }
        }
        return maxLen * maxLen;
    }
};
