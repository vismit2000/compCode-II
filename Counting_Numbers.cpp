/*
PROBLEM: https://cses.fi/problemset/task/2220/
APPROACH: https://www.youtube.com/watch?v=lD_irvBkeOk&feature=youtu.be
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

ll dp[21][11][2][2];

ll solve(string number, int n, int x, int leading_zeros, bool tight){
    if(n == 0)
        return 1;
    if(x != -1 && dp[n][x][leading_zeros][tight] != -1)
        return dp[n][x][leading_zeros][tight];
    
    int lb = 0;
    int ub = tight ? (number[number.length() - n] - '0') : 9;

    ll ans = 0;
    for(int dig = lb; dig <= ub; dig++){
        if(dig == x && !leading_zeros)
            continue;
        ans += solve(number, n-1, dig, leading_zeros & (dig == 0), tight & (dig == ub));
    }
    return dp[n][x][leading_zeros][tight] = ans;
}

int main() { 
    boost;
    ll a, b;
    cin >> a >> b;
    string A = to_string(a-1), B = to_string(b);

    memset(dp, -1, sizeof(dp));
    ll ans1 = solve(B, B.length(), -1, 1, 1);

    memset(dp, -1, sizeof(dp));
    ll ans2 = solve(A, A.length(), -1, 1, 1);

    cout << ans1 - ans2 << endl;
    return 0;
}
