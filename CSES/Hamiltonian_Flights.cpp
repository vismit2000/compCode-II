// CSES Hamiltonian Flights: https://cses.fi/problemset/task/1690

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

map < pair < ll, ll >, ll > dp;

ll tsp(ll mask, ll pos, ll n, vector < vector < ll > > &v){
    if(mask == (1 << n) - 1) return pos == n-1 ? 1: 0;
    if(dp.count({mask, pos})) return dp[{mask, pos}];
    ll ans = 0;
    for(auto i: v[pos]){
        if((mask & (1 << i)) == 0)
            ans = (ans + tsp(mask | (1 << i), i, n, v)) % MOD;
    }
    return dp[{mask, pos}] = ans;
}


int main() {
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif

    ll n, m; cin >> n >> m;
    vector < vector < ll > > v(n);
    ll a, b;
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        v[a - 1].push_back(b - 1);
    }
    cout << tsp(1, 0, n, v) << endl;
}
