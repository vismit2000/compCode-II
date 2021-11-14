// Round H 2021 - Kick Start 2021: https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435914/00000000008d9970

/* CONCEPTS USED:
- LCA for general or n-ary trees (Sparse Matrix DP approach)
- Fast Modular Exponentiation + Modular Inverse
- Reducing a decimal to fraction in lowest irreducible form
- Conditional probability over graph
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define LARGE 1000000.0
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

#define MAXN 1005
#define level 18

vector < ll > tree[MAXN];
ll depth[MAXN];
ll parent[MAXN][level];

vector < double > prob, occ, not_occ;

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    else if (b == 0) return a;

    if (a < b) return gcd(a, b % a);
    else return gcd(b, a % b);
}

pair < ll, ll > reduce(double input){
    double integral = floor(input);
    double frac = input - integral;

    ll precision = 1000000000; // This is the accuracy.

    ll gcd_ = gcd((ll)round(frac * precision), precision);

    ll denominator = precision / gcd_;
    ll numerator = round(frac * precision) / gcd_;

    pair < ll, ll > retVal = make_pair(integral*denominator + numerator, denominator);
    return retVal;
}

ll fastModExp(ll a, ll b, ll m){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = (res*a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

// pre-compute the depth for each node and their first parent(2^0th parent)
void dfs(ll cur, ll prev) {
    depth[cur] = depth[prev] + 1;
    parent[cur][0] = prev;
    for (int i = 0; i < tree[cur].size(); i++)
        if (tree[cur][i] != prev)
            dfs(tree[cur][i], cur);
}
 
// Dynamic Programming Sparse Matrix Approach populating 2^i parent for each node
void precomputeSparseMatrix(ll n) {
    for (int i = 1; i < level; i++)
        for (int node = 1; node <= n; node++)
            if (parent[node][i-1] != -1)
                parent[node][i] = parent[parent[node][i-1]][i-1];
}
 
// Returning the LCA of u and v
ll lca(ll u, ll v) {
    if (depth[v] < depth[u]) swap(u, v);
    ll diff = depth[v] - depth[u];
 
    for (int i = 0; i < level; i++)
        if ((diff >> i) & 1)
            v = parent[v][i];
 
    // now depth[u] == depth[v]
    if (u == v) return u;
 
    for (int i = level-1; i >= 0; i--)
        if (parent[u][i] != parent[v][i]){
            u = parent[u][i];
            v = parent[v][i];
        }
 
    return parent[u][0];
}

void addEdge(ll u,ll v) {
    tree[u].push_back(v);
    tree[v].push_back(u);
}

double findCondProb(ll u, ll LCA, bool lca_occurs){
    if(u == LCA) return lca_occurs ? 1 : 0;
    double parentCond = findCondProb(parent[u][0], LCA, lca_occurs);
    return parentCond * occ[u] + (1 - parentCond) * not_occ[u];
}

void solve(){
    ll n, q, k; cin >> n >> q >> k;
    prob.assign(n+1, 0);
    occ.assign(n+1, 0);
    not_occ.assign(n+1, 0);

    prob[1] = k / LARGE;
    for(ll i = 2; i <= n; i++){
        ll par; cin >> par >> occ[i] >> not_occ[i];
        addEdge(i, par);
        occ[i] /= LARGE;
        not_occ[i] /= LARGE;
        prob[i] = prob[par] * occ[i] + (1 - prob[par]) * not_occ[i];
    }

    memset(parent, -1, sizeof(parent));
    depth[0] = 0;
    dfs(1, 0); // running dfs and precalculating depth of each node
    precomputeSparseMatrix(n + 1); // Precomputing the 2^i th ancestor for evey node

    while(q--){
        ll u, v; cin >> u >> v;
        ll LCA = lca(u, v);
        double prob_combined = prob[LCA] * findCondProb(u, LCA, true) * findCondProb(v, LCA, true)
                        + (1 - prob[LCA]) * findCondProb(u, LCA, false) * findCondProb(v, LCA, false);
        // cout << prob_combined << " ";
        pair < ll, ll > frac = reduce(prob_combined);
        ll num = frac.first, den = frac.second;
        ll den_inv = fastModExp(den, MOD-2, MOD);
        ll ans = ((num % MOD) * (den_inv % MOD)) % MOD;
        cout << ans << " ";
    }
    cout << endl;
}

int main() {   
    boost;
    // cout << fixed << setprecision(20);
    ll t;
    cin >> t;
    for (int testcase = 1; testcase <= t; testcase++){
        cout << "Case #" << testcase << ": ";
        solve();
    }
}
