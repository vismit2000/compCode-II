// https://cses.fi/problemset/task/1695

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

ll n, m;
vector<vector<ll>> capacity;
vector<vector<ll>> adj;

void minCutDFS(int u, vector < ll > &nodes){
    for(auto v : adj[u]){
        if(nodes[v] == 0 && capacity[u][v] > 0){
            nodes[v] = 1;
            minCutDFS(v, nodes);
        }
    }
}

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
    vector<ll> parent(n);
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
    cin >> n >> m;
    adj.resize(n);
    capacity = vector<vector<ll>> (n, vector<ll>(n, 0));

    vector < pair < ll, ll > > edges;
    vector < ll > nodes(n, 0);

    while(m--){
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edges.push_back({a, b});
        capacity[a][b] = 1;
        capacity[b][a] = 1;
    }

    cout << maxflow(0, n-1) << endl;

    nodes[0] = 1;
    minCutDFS(0, nodes);

    for(auto edge : edges)
        if(nodes[edge.first] != nodes[edge.second])
            cout << edge.first + 1 << " " << edge.second + 1 << endl;
}
