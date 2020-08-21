// https://codeforces.com/problemset/problem/1324/F

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

vector < vector < int > > tree;
vector < int > a, dp1, dp2;

void dfs1(int node, int parent = -1){
    dp1[node] = a[node];
    for(auto child : tree[node]){
        if(child != parent){
            dfs1(child, node);
            dp1[node] += max(dp1[child], 0);
        }
    }
}

void dfs2(int node, int parent = -1){
    dp2[node] = dp1[node];
    if(parent != -1){
        int val = dp2[parent] - max(dp1[node], 0);
        dp2[node] += max(val, 0);
    }
    for(auto child : tree[node]){
        if(child != parent)
            dfs2(child, node);
    }
}

int main()
{
    boost;
    int n, u, v;
    cin >> n;
    
    tree = vector < vector < int > > (n);
    a.assign(n, 0);
    dp1.assign(n, 0);
    dp2.assign(n, 0);

    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] == 0) a[i] = -1;
    }

    for(int i = 0; i < n-1; i++){
        cin >> u >> v;
        u--, v--;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs1(0);
    dfs2(0);

    for(int i = 0; i < n; i++)
        cout << dp2[i] << " ";
        
    return 0;
}
