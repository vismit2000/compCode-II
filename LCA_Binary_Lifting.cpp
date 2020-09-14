#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);
#define NODES 100005

vector < vector < int > > tree;
vector < vector < int > > up;
vector < int > lvl;

void dfs(int src, int par, int level = 0){
    lvl[src] = level;
    for(int child : tree[src])
        if(child != par)
            dfs(child, src, level + 1);
}

void binaryLifting(int src, int par){
    up[src][0] = par;
    for(int i = 1; i < 20; i++){
        if(up[src][i-1] != -1)
            up[src][i] = up[up[src][i-1]][i-1];
        else
            up[src][i] = -1;
    }

    for(int child : tree[src])
        if(child != par)
            binaryLifting(child, src);
}

int liftNode(int node, int jumpRequired){
    for(int i = 19; i >= 0; i--){
        if(jumpRequired == 0 || node == -1)
            break;
        if(jumpRequired >= (1 << i)){
            node = up[node][i];
            jumpRequired -= (1 << i);
        }
    }
    return node;
}

int LCA(int u, int v){
    if(lvl[u] < lvl[v])
        swap(u, v);
    u = liftNode(u, lvl[u] - lvl[v]);

    if(u == v)
        return u;
    
    for(int i = 19; i >= 0; i--){
        if(up[u][i] != up[v][i]){
            u = up[u][i];
            v = up[v][i];
        }
    }
    return liftNode(u, 1);
}

int distanceNodes(int a, int b){
    int lca = LCA(a, b);
    return lvl[a] + lvl[b] - 2*lvl[lca];
}

int kthNode(int a, int b, int k){
    int res;
    int lca = LCA(a, b);
    if(lvl[a] - lvl[lca] >= k)
        res = liftNode(a, k);
    else
        res = liftNode(b, distanceNodes(a, b) - k);
    return res;
}

vector < int > pathLCA(int N, vector < vector < int > > &edges, vector < vector < int > > &queries){
    tree.resize(N+1);
    up.resize(N+1, vector < int > (20));
    lvl.resize(N+1);

    for(auto edge : edges){
        tree[edge[0]].push_back(edge[1]);
        tree[edge[1]].push_back(edge[0]);
    }

    dfs(1, 0);
    binaryLifting(1, 0);

    vector < int > ans;

    for(auto query : queries){
        int a = query[1], b = query[2];
        if(query[0] == 1)
            ans.push_back(distanceNodes(a, b));
        else
            ans.push_back(kthNode(a, b, query[3] - 1));
    }

    return ans;
}

int main()
{
    boost;
    int N, Q, u, v, w, x;
    cin >> N >> Q;
    vector < vector < int > > edges;
    for(int i = 0; i < N-1; i++){
        cin >> u >> v;
        edges.push_back({u, v});
    }

    vector < vector < int > > queries;
    for(int i = 0; i < Q; i++){
        cin >> u >> v >> w >> x;
        queries.push_back({u, v, w, x});
    }

    vector < int > result = pathLCA(N, edges, queries);

    for(auto res : result)
        cout << res << endl;

    return 0;
}
