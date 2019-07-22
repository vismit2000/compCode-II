// https://leetcode.com/problems/decode-ways-ii/

#define MOD 1000000007

class Solution {
public:
    int numDecodings(string s) 
    {
        int n = s.length();
        vector <long> dp(n+1, 0);
        
        dp[0] = 1;
        if(s[0] == '0')
            dp[1] = 0;
        else if(s[0] == '*')
            dp[1] = 9;
        else
            dp[1] = 1;
        
        for(int index = 2; index <= n; index++)
        {
            if(s[index-1] == '*')
                dp[index] = (dp[index]%MOD + (9 * dp[index-1])%MOD) % MOD;
            else if(s[index-1] != '0')
                dp[index] = (dp[index]%MOD + dp[index-1]) % MOD;
            
            if((s[index-1] >= '0' && s[index-1] <= '6') && (s[index-2] == '2'))
                dp[index] = (dp[index]%MOD + dp[index-2]) % MOD;
            if((s[index-1] >= '0' && s[index-1] <= '9') && (s[index-2] == '1'))
                dp[index] = (dp[index]%MOD + dp[index-2]) % MOD;
            else if((s[index-1] >= '0' && s[index-1] <= '6') && (s[index-2] == '*'))
                dp[index] = (dp[index]%MOD + (2 * dp[index-2])%MOD) % MOD;   
            else if((s[index-1] >= '7' && s[index-1] <= '9') && (s[index-2] == '*'))
                dp[index] = (dp[index]%MOD + (dp[index-2])%MOD) % MOD;
            else if(s[index-1] == '*' && s[index-2] == '2')
                dp[index] = (dp[index]%MOD + (6 * dp[index-2])%MOD) % MOD;
            else if(s[index-1] == '*' && s[index-2] == '1')
                dp[index] = (dp[index]%MOD + (9 * dp[index-2])%MOD) % MOD;
            else if(s[index-1] == '*' && s[index-2] == '*')
                dp[index] = (dp[index]%MOD + (15 * dp[index-2])%MOD) % MOD;
            
            dp[index] %= MOD;
        }
        
        return dp[n];
    }
};
