// https://www.hackerrank.com/contests/bppc19/challenges/grid-and-good-square/problem

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f

int main() {  
    ll n, m;
    cin >> n >> m;
    char A[n][m];
    ll dp[n][m];
    
    memset(dp, INF, sizeof(dp));
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> A[i][j];
    
    dp[n-1][m-1] = (A[n-1][m-1] == '#') ? 1 : 0;
    
    for(int i = n-2; i >= 0; i--){
        dp[i][m-1] = dp[i+1][m-1];
        if(A[i][m-1] == '#' && A[i+1][m-1] != '#')
            dp[i][m-1] += 1;
    }
    
    for(int j = m-2; j >= 0; j--){
        dp[n-1][j] = dp[n-1][j+1];
        if(A[n-1][j] == '#' && A[n-1][j+1] != '#')
            dp[n-1][j] += 1;
    }
    
    for(int i = n-2; i >= 0; i--){
        for(int j = m-2; j >= 0; j--){
            if(A[i][j] == '.')
                dp[i][j] = min(dp[i+1][j], dp[i][j+1]);
            else
                dp[i][j] = min((dp[i+1][j] + (A[i+1][j] == '#' ? 0 : 1)), (dp[i][j+1] + (A[i][j+1] == '#' ? 0 : 1)));
        }
    }
    cout << dp[0][0] << endl;
    return 0;
}
