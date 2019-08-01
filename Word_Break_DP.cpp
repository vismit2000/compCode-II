// https://leetcode.com/problems/word-break/submissions/

/*
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, 
determine if s can be segmented into a space-separated sequence of one or more dictionary words.
*/

class Solution {
public:
    
    unordered_map < string, int > mp;
    int dp[1005][1005];
    
    bool Break(string s, int i, int j)
    {
        if(mp.count(s.substr(i, j-i+1)))
        {
            dp[i][j] = 1;
            return true;
        }
            
        if(dp[i][j] != -1)
        {
            if(dp[i][j] == 0)
                return false;
            else if(dp[i][j] == 1)
                return true;
        }
        
        bool result = false;
                
        for(int k = i; k < j; k++)
        {            
            if(Break(s, i, k) && Break(s, k+1, j))
            {
                result = true;
                break;
            }
        }
        if(result == true)
            dp[i][j] = 1;
        else dp[i][j] = 0;
        
        return result;
    }
    
    bool wordBreak(string s, vector<string>& wordDict) 
    {
        for(auto str : wordDict)
            mp[str] = 1;
        
        memset(dp, -1, sizeof(dp));
        
        return Break(s, 0, s.length() - 1);
    }
};
