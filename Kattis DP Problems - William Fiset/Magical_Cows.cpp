/*
Problem Link: https://open.kattis.com/problems/magicalcows
Solution Video: https://www.youtube.com/watch?v=_tur2nPkIKo
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

#define MAX_DAYS 50

int main()
{
    boost;
    ll C, N, M, cows;
    cin >> C >> N >> M;

    vector < vector < ll > > dp(MAX_DAYS + 1, vector < ll > (C+1, 0));
    vector < ll > total(MAX_DAYS + 1, 0);

    total[0] = N;

    for(int i = 1; i <= N; i++){
        cin >> cows;
        dp[0][cows]++;
    }

    for(int day = 1; day <= MAX_DAYS; day++){
        for(int j = 1; j <= C; j++){
            ll newCows = 2*j;
            if(newCows <= C){
                dp[day][newCows] += dp[day-1][j];
            }
            else{
                dp[day][(newCows+1)/2] += dp[day-1][j];
                dp[day][newCows/2] += dp[day-1][j];
            }
        }

        for(int j = 1; j <= C; j++)
            total[day] += dp[day][j];
    }

    while(M--){
        ll d;
        cin >> d;
        cout << total[d] << endl;
    }



    return 0;
}