//https://leetcode.com/problems/knight-probability-in-chessboard/

class Solution {
public:
    double dp[30][30][105];
    
    int dirX[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dirY[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    
    double knightProbability(int N, int K, int r, int c) 
    {
        memset(dp, 0, sizeof(dp));
        dp[r][c][0] = 1;
        
        int dx, dy;
        
        for(int move = 1; move <= K; move++)
        {
            for(int i = 0; i < N; i++)
            {
                for(int j = 0; j < N; j++)
                {
                    for(int p = 0; p < 8; p++)
                    {
                        dx = i + dirX[p];
                        dy = j + dirY[p];
                        
                        if(dx >= 0 && dx < N && dy >= 0 && dy < N)
                            dp[i][j][move] += (0.125)*dp[dx][dy][move-1];
                    }
                }
            }
        }
        
        double ans = 0;    
        
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
                ans += dp[i][j][K];
        }
        return ans;
    }
};
