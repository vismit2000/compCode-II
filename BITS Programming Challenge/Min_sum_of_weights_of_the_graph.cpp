// https://www.hackerrank.com/contests/bppc10/challenges/find-the-graph

#include<bits/stdc++.h>

#define ll long long
using namespace std;


int main() {  
    ll n;
    cin>>n;
   
    vector<vector<ll>> graph(n, vector<ll>(n));
    ll total = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            cin>>graph[i][j];
            total += graph[i][j];
        }
    }
   
    for (ll u = 0; u < n; u++) {
        // if (u == k) continue;
        for (ll v = 0; v < n; v++) {
            // if (v == k || u == v) continue;
            if (u == v) continue;
            for (int k = 0; k < n; k++) {
                if (k == u || k == v) continue;
                int indirect = graph[u][k] + graph[k][v];
                if (graph[u][v] > indirect) {
                    cout<<-1<<endl;
                    return 0;
                }
                else if (graph[u][v] == indirect) {
                    total -= indirect;
                    break;
                }
            }
        }
    }  
    cout<<(total>>1)<<endl;
    return 0;
}
