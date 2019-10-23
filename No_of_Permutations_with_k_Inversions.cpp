// Problem: https://www.spoj.com/problems/PERMUT1/

// Approach: https://stackoverflow.com/a/25747326

#include <bits/stdc++.h>
using namespace std;

int dp[100][100];

int inversions(int n, int k)
{
    if(dp[n][k] != -1)
        return dp[n][k];
    if(n == 0)
        return 0;
    if(k == 0)
        return 1;
    
    int val = 0;

    for(int i = 0; i < n && i <= k; i++)
        val += inversions(n-1, k-i);

    return dp[n][k] = val;
}

int main() 
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, k;
        cin >> n >> k;
        memset(dp, -1, sizeof(dp));
        cout << inversions(n, k) << endl;
    }
    return 0;
}
