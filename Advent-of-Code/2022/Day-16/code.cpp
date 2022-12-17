// https://adventofcode.com/2022/day/16
// Approach: 3-D DP with bitmasking (like TSP)

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);


vector < string > nodes;
vector < vector < int > > dependencies;
vector < int > flow;
map < tuple < int, int, ll, bool >, ll > dp;


ll maxReward(int tim, int state, ll visited, bool extra){
    if(tim == 0){
        return extra ? maxReward(26, 59, visited, false) : 0LL;
    }
    auto key = make_tuple(tim, state, visited, extra);
    if(dp.count(key) == 1) return dp[key];

    ll ans = 0;

    bool no_state = ((visited & (1LL << state)) == 0);

    if(no_state && (flow[state] > 0)){
        ll newVisited = visited | (1LL << state);
        assert (newVisited > visited);
        ans = max(ans, flow[state] * (tim-1) + maxReward(tim - 1, state, newVisited, extra));
    }

    for(auto dep: dependencies[state]){
        ans = max(ans, maxReward(tim - 1, dep, visited, extra));
    }
    return dp[key] = ans;
}


int main() {
#ifndef ONLINE_JUDGE
    freopen("input1.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n; cin >> n;
    string line;
    nodes.resize(n);
    vector < vector < string > > deps(n);
    dependencies.resize(n);
    map < string, int > mp;
    flow.resize(n);

    for(int i = 0; i < n; i++){
        cin >> nodes[i] >> flow[i] >> line;
        mp[nodes[i]] = i;
        for(int j = 0; j < line.length(); j += 3){
            deps[i].push_back(line.substr(j, 2));
        }
    }
    for(int i = 0; i < n; i++){
        for(auto dep: deps[i]){
            dependencies[i].push_back(mp[dep]);
        }
    }

    cout << maxReward(30, 59, 0LL, false) << endl;
    cout << maxReward(26, 59, 0LL, true) << endl;
}