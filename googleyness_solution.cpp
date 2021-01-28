#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

// DFA based implementation - There would be 4 states, 0 is the start state
ll googleyness(ll N, ll K){
    ll dp[N+1][K+1][4];
    memset(dp, 0, sizeof(dp));

    for(int state = 0; state < 4; state++)
        dp[0][0][state] = 1;

    for(int i = 1; i <= N; i++) {
        for(int k = 0; k <= K; k++){
            dp[i][k][0] = (dp[i-1][k][1] + 25 * dp[i-1][k][0]) % MOD;
            dp[i][k][1] = (dp[i-1][k][1] + dp[i-1][k][2] + 24 * dp[i-1][k][0]) % MOD;
            dp[i][k][2] = (dp[i-1][k][1] + dp[i-1][k][3] + 24 * dp[i-1][k][0]) % MOD;
            dp[i][k][3] = (25 * dp[i-1][k][0]) % MOD;
            if(k != 0)
                dp[i][k][3] = (dp[i][k][3] + dp[i-1][k-1][1]) % MOD;
        }
    }
    // for(int i = 1; i <= N; i++) {
    //     for(int k = 1; k <= K; k++){
    //         cout << dp[i][k][0] << " " << dp[i][k][1] << " " << dp[i][k][2] << " " << dp[i][k][3] << endl ;
    //     }
    // }
    return dp[N][K][0];
}

int main()
{   
    boost;
    ll N, K;
    cin >> N >> K;
    cout << googleyness(N, K) << endl;
    return 0;
}