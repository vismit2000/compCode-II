/*
Problem Link: https://open.kattis.com/problems/scenes
Solution Video: https://www.youtube.com/watch?v=pPgBZqY_Xh0
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

ll N, W, H;

ll dp[101][10001];  // dp[W][N] represents the # mountanin scenes with the currrent column index as W (from column W to end) as N ribbons left

ll mountain_scenes(ll w, ll ribbon){
    if(ribbon < 0)
        return 0;
    if(w == W)
        return 1;
    if(dp[w][ribbon] != -1)
        return dp[w][ribbon];

    ll scenes = 0;
    // We can place 0 to H ribbon squares in the current column indexed by w
    for(ll height = 0; height <= H; height++)
        scenes += mountain_scenes(w + 1, ribbon - height);
    
    return dp[w][ribbon] = scenes % MOD;
}

int main()
{
    boost;
    cin >> N >> W >> H;
    memset(dp, -1, sizeof(dp));

    ll ribbon_squares = min(N, W*H);
    ll plains = (ribbon_squares / W) + 1;

    cout << (mountain_scenes(0, N) - plains + MOD) % MOD;

    return 0;
}