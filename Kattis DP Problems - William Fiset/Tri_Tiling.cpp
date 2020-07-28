/*
Problem Link: https://open.kattis.com/problems/tritiling
Solution Video: https://www.youtube.com/watch?v=yn2jnmlepY8
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

int main()
{
    boost;
    while(1){
        int n;
        cin >> n;
        if(n == -1)
            break;
        
        vector < vector < int > > dp(n+1, vector < int > (8, 0));

        dp[0][7] = 1;

        for (int i = 1; i <= n; i++) {
   
            dp[i][0] += dp[i - 1][7];

            dp[i][1] += dp[i - 1][6];

            // State 2 doesn't contribute to the number of tilings
            // dp[i][2] += dp[i-1][5];

            dp[i][3] += dp[i - 1][7];
            dp[i][3] += dp[i - 1][4];

            dp[i][4] += dp[i - 1][3];

            // State 5 doesn't contribute to the number of tilings
            // dp[i][5] += dp[i-1][2];

            dp[i][6] += dp[i - 1][7];
            dp[i][6] += dp[i - 1][1];

            dp[i][7] += dp[i - 1][3];
            dp[i][7] += dp[i - 1][6];
            dp[i][7] += dp[i - 1][0];
        }   
        cout << dp[n][7] << endl;
    }
    return 0;
}