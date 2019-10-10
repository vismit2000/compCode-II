//https://leetcode.com/problems/count-vowels-permutation/

/*
Given an integer n, your task is to count how many strings of length n can be formed under the following rules:

Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
Each vowel 'a' may only be followed by an 'e'.
Each vowel 'e' may only be followed by an 'a' or an 'i'.
Each vowel 'i' may not be followed by another 'i'.
Each vowel 'o' may only be followed by an 'i' or a 'u'.
Each vowel 'u' may only be followed by an 'a'.
Since the answer may be too large, return it modulo 10^9 + 7.
*/

class Solution {
public:
    bool ok(int a, int b) 
    {   // aeiou
        if (a == 0)
            return b == 1;
        else if (a == 1)
            return b == 0 || b == 2;
        else if (a == 2)
            return b != 2;
        else if (a == 3)
            return b == 2 || b == 4;
        else if (a == 4)
            return b == 0;
        else
            assert(false);
    }

    static const int N_MAX = 2e5 + 5;
    static const int MOD = 1e9 + 7;

    int dp[N_MAX][5];

    int countVowelPermutation(int n) 
    {
        for (int c = 0; c < 5; c++)
            dp[1][c] = 1;

        for (int i = 1; i < n; i++)
            for (int a = 0; a < 5; a++)
                for (int b = 0; b < 5; b++)
                    if (ok(a, b))
                        dp[i + 1][b] = (dp[i + 1][b] + dp[i][a]) % MOD;

        int sum = 0;

        for (int c = 0; c < 5; c++)
            sum = (sum + dp[n][c]) % MOD;

        return sum;
    }
};
