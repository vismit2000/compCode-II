// PROBLEM: https://leetcode.com/problems/wildcard-matching/
// EXPLANATION: https://www.youtube.com/watch?v=3ZDZ-N0EPV0

class Solution {
public:
    bool isMatch(string s, string p) 
    {
        string t = "";
        if(p.length() > 0)
            t += p[0];
        
        for(int i = 1; i < p.length(); i++)
        {
            if(p[i] == '*' && p[i-1] == '*')
                continue;
            else
                t += p[i];
        }
        
        p = t;
        
        int n = s.length(), m = p.length();
        
        bool dp[n+1][m+1];
        memset(dp, false, sizeof(dp));
        
        dp[0][0] = true;
        
        if(p[0] == '*')
            dp[0][1] = true;
        
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                if(s[i-1] == p[j-1] || p[j-1] == '?')
                    dp[i][j] = dp[i-1][j-1];
                else if(p[j-1] == '*')
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
        }
        return dp[n][m];
    }
};
