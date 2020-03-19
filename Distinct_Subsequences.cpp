// https://leetcode.com/problems/distinct-subsequences/

/*
PROBLEM: Given a string S and a string T, count the number of distinct subsequences of S which equals T.
A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the 
characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE"
while "AEC" is not).

EXPLANATION:
- We will build an array mem where mem[i+1][j+1] means that S[0..j] contains T[0..i] that many times as distinct subsequences. 
Therefore the result will be mem[T.length()][S.length()].

- We can build this array rows-by-rows:
- The first row must be filled with 1. That's because the empty string is a subsequence of any string but only 1 time. 
So mem[0][j] = 1 for every j. 
- The first column of every rows except the first must be 0. This is because an empty string cannot contain a non-empty string 
as a substring -- the very first item of the array: mem[0][0] = 1, because an empty string contains the empty string 1 time.

- From here we can easily fill the whole grid: for each (x, y), we check if S[x] == T[y] we add the previous item and the 
previous item in the previous row, otherwise we copy the previous item in the same row. The reason is simple:

-- if the current character in S doesn't equal to current character T, then we have the same number of distinct subsequences 
as we had without the new character.
-- if the current character in S equal to the current character T, then the distinct number of subsequences: the number we had 
before plus the distinct number of subsequences we had with less longer T and less longer S.
/*

class Solution {
public:
    int numDistinct(string s, string t) 
    {
        long dp[t.length() + 1][s.length() + 1];
        // dp[i][j] means that S[0..j] contains T[0..i] that many times as distinct subsequences
        
        for(int j = 0; j <= s.length(); j++)
            dp[0][j] = 1;
        
        for(int i = 1; i <= t.length(); i++)
            dp[i][0] = 0;
        
        for(int i = 1; i <= t.length(); i++)
        {
            for(int j = 1; j <= s.length(); j++)
            {
                dp[i][j] = dp[i][j-1];
                if(t[i-1] == s[j-1])
                    dp[i][j] += dp[i-1][j-1];
            }
        }
        return dp[t.length()][s.length()];
    }
};
