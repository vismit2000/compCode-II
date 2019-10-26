//Problem: https://codeforces.com/problemset/problem/682/D

//Approach: https://www.youtube.com/watch?v=Uz0WD9yRzFE

//Some test case failing 

#include <bits/stdc++.h>
using namespace std;

int dp[1001][1001][10][2];

int solve(string s, string t, int idx_s, int idx_t, int remaining, int cont)
{
    if((cont == 0 && remaining == 0) || (cont == 1 && remaining < 0)  || idx_s == s.length() || idx_t == t.length())
        return 0;
    if(dp[idx_s][idx_t][remaining][cont] != -1)
        return dp[idx_s][idx_t][remaining][cont];

    int ans;

    if(cont == 1)
    {
        ans = max(solve(s, t, idx_s + 1, idx_t, remaining, 0), solve(s, t, idx_s, idx_t + 1, remaining, 0));
        if(s[idx_s] == t[idx_t])
            ans = max(ans, 1 + solve(s, t, idx_s + 1, idx_t + 1, remaining, 1));
    }
    else
    {
        ans = max(solve(s, t, idx_s + 1, idx_t, remaining, 0), solve(s, t, idx_s, idx_t + 1, remaining, 0));
        if(s[idx_s] == t[idx_t])
            ans = max(ans, 1 + solve(s, t, idx_s + 1, idx_t + 1, remaining - 1, 1));
    }

    return dp[idx_s][idx_t][remaining][cont] = ans;
}

int main() 
{
    int n, m, k;
    cin >> n >> m >> k;
    string s, t;
    cin >> s >> t;
    memset(dp, -1, sizeof(dp));
    cout << solve(s, t, 0, 0, k, 0) << endl;
    return 0;
}

//Botom-Up DP Solution (Accepted)

#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
char a[1500];
char b[1500];
int dp[1005][1005][12][2];
int main()
{
    int n,m,kk;
    while(~scanf("%d%d%d",&n,&m,&kk))
    {
        memset(dp,0,sizeof(dp));
        scanf("%s",a+1);
        scanf("%s",b+1);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                for(int k=1;k<=kk;k++)
                {
                    if(a[i]==b[j])
                    {
                        dp[i][j][k][1]=max(dp[i-1][j-1][k-1][0]+1,dp[i][j][k][1]);
                        dp[i][j][k][1]=max(dp[i-1][j-1][k][1]+1,dp[i][j][k][1]);
                    }
                    dp[i][j][k][0]=max(dp[i][j][k][1],dp[i][j][k][0]);
                    dp[i][j][k][0]=max(dp[i][j-1][k][0],dp[i][j][k][0]);
                    dp[i][j][k][0]=max(dp[i-1][j-1][k][0],dp[i][j][k][0]);
                    dp[i][j][k][0]=max(dp[i-1][j][k][0],dp[i][j][k][0]);
                }
            }
        }
        printf("%d\n",max(dp[n][m][kk][0],dp[n][m][kk][1]));
    }
}
