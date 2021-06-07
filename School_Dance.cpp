// https://cses.fi/problemset/task/1696

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

ll n, m, k;
vector<vector<ll>> capacity;
vector<vector<ll>> adj;

ll bfs(ll s, ll t, vector<ll>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<ll, ll>> q;
    q.push({s, INF});

    while (!q.empty()) {
        ll cur = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for (ll next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                ll new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

ll maxflow(ll s, ll t) {
    ll flow = 0;
    vector<ll> parent(n+m+2);
    ll new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        ll cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    boost;
    cin >> n >> m >> k;
    adj.resize(n + m + 2);
    capacity = vector<vector<ll>> (n + m + 2, vector<ll>(n + m + 2, 0));

    for(int i = 1; i <= n; i++){
        adj[0].push_back(i);
        adj[i].push_back(0);
        capacity[0][i] = 1;
    }
    for(int i = n+1; i <= n+m; i++){
        adj[i].push_back(n+m+1);
        adj[n+m+1].push_back(i);
        capacity[i][n+m+1] = 1;
    }

    while(k--){
        ll a, b; cin >> a >> b;
        adj[a].push_back(n + b);
        adj[n + b].push_back(a);
        capacity[a][n + b] = 1;
    }

    cout << maxflow(0, n+m+1) << endl;

    for(int i = 1; i <= n; i++)
        for(int j = n+1; j <= n+m; j++)
            if(capacity[j][i] == 1)
                cout << i << " " << j-n << endl;
}
