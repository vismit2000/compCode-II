// https://leetcode.com/problems/palindrome-partitioning-iii/

/*Problem:

You are given a string s containing lowercase letters and an integer k. You need to :

- First, change some characters of s to other lowercase English letters.
- Then divide s into k non-empty disjoint substrings such that each substring is palindrome.

Return the minimal number of characters that you need to change to divide the string.
*/

/*Approach:

We create 2 dp arrays

1. pal[i][j] = min changes to convert i....j to palindrome
2. dp[i][k] = min changes to convert to divide the string with k substrings and till ith index.

Let dp[i][j] = min. characters to change to divide s[0...i] into j non-empty disjoint substrings.

dp[i][j] = MIN ( dp[p][j-1]  +  pal[p+1][i] )      where (p-1 <= j < i)
         p-1 <= j < i

where pal[x][y] denotes min. character to change to make s[x..y] a palindrome.

*/

class Solution {
public:
    int pal[101][101];
    int dp[101][101];
    
    int dfs(string s, int i, int j) 
    {
        if(i >= j)
            return 0;
        int cnt = 0;
        
		if(pal[i][j] != -1)
			return pal[i][j];
        
        if(s[i] != s[j])
            cnt++;
        
        return pal[i][j] = dfs(s, i + 1, j - 1) + cnt;
    }
    
    int palindromePartition(string s, int k) 
    {
        int n = s.size(); 
        
        memset(pal, -1, sizeof(pal));
        memset(dp, 0, sizeof(dp));
        
        for(int i = 0; i < n; i++) 
        {
            pal[i][i] = 0;
            for(int j = i + 1; j < n; j++) 
            {
                if(pal[i][j] == -1)
                    pal[i][j] = dfs(s, i, j);
            }
        }
        
        for(int i = 0; i < n; i++)
            dp[i][0] = pal[0][i];
        
        for(int j = 1; j < k; j++)
        {
            for(int i = j; i < n; i++)
            {
                int opt = INT_MAX;
                
                for(int p = j-1; p < i; p++)
                {
                    opt = min(opt, dp[p][j-1] + pal[p+1][i]);
                }
                dp[i][j] = opt;
            }
        }
        
        return dp[n-1][k-1];
    }
};

// Similar Problem: https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/
