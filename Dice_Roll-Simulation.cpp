// https://leetcode.com/problems/dice-roll-simulation/
// Explanation: https://leetcode.com/problems/dice-roll-simulation/discuss/403756/Java-Share-my-DP-solution

#define MOD 1000000007
#define ll long long

class Solution {
public:
    int dieSimulator(int n, vector<int>& rollMax) 
    {
        // DP[i][j] means how many choice for total i dices and the last number is j.
        ll dp[n][7];
        // save the sum of dp[i][1~6] at dp[i][7] for easier calculation
        
        for(int i = 0; i < 6; i++)
            dp[0][i] = 1;
        dp[0][6] = 6;
        
        for(int i = 1; i < n; i++)
        {
            ll sum = 0;
            for(int j = 0; j < 6; j++)
            {
                dp[i][j] = dp[i-1][6];
                
                if(i - rollMax[j] < 0)
                    sum = (sum + dp[i][j]) % MOD;
                else
                {
                    if(i - rollMax[j] - 1 >= 0) 
                        dp[i][j] = (dp[i][j] - (dp[i-rollMax[j]-1][6] - dp[i-rollMax[j]-1][j]) + MOD) %MOD;
                    else 
                        dp[i][j] = (dp[i][j] - 1) % MOD;
                    
                    sum = (sum + dp[i][j]) % MOD;
                }
            }
            dp[i][6] = sum;
        }
        return (int)dp[n-1][6];
    }
};
