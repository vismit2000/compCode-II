// Problem : https://www.spoj.com/problems/IOIPALIN/
// Approach : https://codeforces.com/blog/entry/53962

/*
Let dp[l][r] be the minimum number of insertions to make s[l...r] a palindrome.

If s[l] = s[r], then obviously dp[l][r] = dp[l + 1][r - 1].

Otherwise, you must either add s[r] to the beginning or s[l] to the end so dp[l][r] = 1 + min(dp[l + 1][r], dp[l][r - 1]).
*/

#include <bits/stdc++.h>
using namespace std;

int findMinInsertions(string &s, int i, int j, map < pair<int, int>, int > &dp)
{
    if(i >= j)
        return 0;
    if(dp.count({i,j}))
        return dp[{i, j}];
    
    if(s[i] == s[j])
        return dp[{i,j}] = findMinInsertions(s, i+1, j-1, dp);
    else
        return dp[{i,j}] = 1 + min(findMinInsertions(s, i+1, j, dp), findMinInsertions(s, i, j-1, dp));
}

int main()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    map < pair <int, int>, int > dp;

    cout << findMinInsertions(s, 0, n-1, dp); 

    return 0;
}
