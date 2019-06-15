//http://codeforces.com/contest/166/problem/E 

#include<bits/stdc++.h>
using namespace std;

#define ll long
#define MOD 1000000007

const int N = 1e7 + 2;

ll path(ll left, ll c, ll dp[][2])
{
    if(left == 0)
    {
        if(c == 1)
            return 1;
        else
            return 0;
    }
    if(dp[left][c] != -1)
        return dp[left][c];

    if(c == 1)
        dp[left][c] = (3LL * (path(left-1, 0, dp) % MOD)) % MOD;
    else
        dp[left][c] = ((2LL * (path(left-1, 0, dp) % MOD)) % MOD + (path(left-1, 1, dp) % MOD)) % MOD;
    
    return dp[left][c];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin>>n;
    
    ll dp[N][2];

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < 2; j++)
            dp[i][j] = -1;
    }

    cout << path(n, 1, dp);

    return 0;
}
