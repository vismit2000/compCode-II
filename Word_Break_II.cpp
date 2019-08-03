//https://leetcode.com/problems/word-break-ii/

//(Not accepted - TLE)

class Solution {
public:
    
    unordered_map < string, int > mp;
    map < pair <int, int> , vector < string > > dp;    
    
    vector < string > Break(string s, int i, int j)
    {
        if(dp.count({i, j}))
            return dp[{i, j}];
        
        if(mp.count(s.substr(i, j-i+1)))
            dp[{i, j}].push_back(s.substr(i, j-i+1));
        
        string temp;
        
        for(int k = i; k < j; k++)
        {
            for(auto it1 : Break(s, i, k))
            {
                for(auto it2 : Break(s, k+1, j))
                {
                    temp = it1 + " " + it2;
                    if(find(dp[{i, j}].begin(), dp[{i, j}].end(), temp) == dp[{i, j}].end())
                        dp[{i, j}].push_back(temp);
                }
            }
        }
        
        return dp[{i, j}];
    }
    
    vector<string> wordBreak(string s, vector<string>& wordDict) 
    {
        for(auto str : wordDict)
            mp[str] = 1;
        
        return Break(s, 0, s.length() - 1);      
    }
};
