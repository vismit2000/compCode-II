/*
Problem: https://codeforces.com/problemset/problem/16/E
Solution: https://www.youtube.com/watch?v=d7kvyp6dfz8
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

int n;
double p[20][20];
double dp[(1 << 19)];

int count_set_bits(int x){
    int cnt = 0;
    while(x){
        x = x & (x-1);
        cnt++;
    }
    return cnt;
}

double pMove(int prevBitMask, int j){
    int k = count_set_bits(prevBitMask);
    int den = (k * (k-1))/2;
    double num = 0;

    for(int fish = 0; fish < n; fish++){
        if(prevBitMask & (1 << fish))
            num += p[fish][j];
    }
    return num/(1.0 * den);
}

double solve(int bitMask){
    int alive = count_set_bits(bitMask);

    if(alive == n)
        return 1.0;

    if(dp[bitMask] > -0.5)
        return dp[bitMask];

    double ans = 0.0;

    for(int fish = 0; fish < n; fish++){
        if(!(bitMask & (1 << fish))){
            int prevBitMask = bitMask | (1 << fish);
            ans += solve(prevBitMask) * pMove(prevBitMask, fish);
        }
    }
    return dp[bitMask] = ans;
}

int main()
{
    boost;
    cin >> n;

    memset(dp, -1, sizeof(dp));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> p[i][j];

    for(int i = 0; i < n; i++)
        cout << fixed << setprecision(10) << solve(1 << i) << " ";

    return 0;
}
