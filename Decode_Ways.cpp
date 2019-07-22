// https://leetcode.com/problems/decode-ways/

// Bottom-up DP

class Solution {
public:
    
    bool isValid(string &s, int ones, int tens)
    {
        if(tens != -1 && s[tens] == '0')
            return false;
        int num = s[ones] - '0';
        if(tens != -1)
            num += 10 * (s[tens] - '0');
        
        return ((num >= 1) && (num <= 26));
    }
    
    int numDecodings(string s) 
    {
        int n = s.length();
        vector <int> dp(n+1, 0);
        
        dp[0] = 1;
        dp[1] = (s[0] == '0') ? 0 : 1;
        
        for(int index = 2; index <= n; index++)
        {
            if(isValid(s, index-1, -1))
                dp[index] += dp[index-1];
            if(isValid(s, index-1, index-2))
                dp[index] += dp[index-2];            
        }
        
        return dp[n];
    }
};

//Top-down DP

class Solution {
public:
    
    bool isValid(string &s, int ones, int tens)
    {
        if(tens != -1 && s[tens] == '0')
            return false;
        int num = s[ones] - '0';
        if(tens != -1)
            num += 10 * (s[tens] - '0');
        
        return ((num >= 1) && (num <= 26));
    }
    
    int decodeWays(string &s, int index, vector <int> &dp)
    {
        if(index == 0)
            return 1;
        
        if(dp[index] != -1)
            return dp[index];
        
        int ways = 0;
        
        if(index-1 >= 0 && isValid(s, index-1, -1))
            ways += decodeWays(s, index-1, dp);
        if(index-2 >= 0 && isValid(s, index-1, index-2))
            ways += decodeWays(s, index-2, dp);
        
        return dp[index] = ways;
    }
    
    int numDecodings(string s) 
    {
        vector <int> dp(s.length()+1, -1);
        
        return decodeWays(s, s.length(), dp);
    }
};
