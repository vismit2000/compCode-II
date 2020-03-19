// https://www.spoj.com/problems/HOLI/

/*
EXPLANATION:
This problem can be solved if its viewed from the edges point of view, rather than nodes point of view. 
We can easily observe that to obtain the maximum distance travelled by all the visitors, each edge should
be travelled by maximum possible number of visitors. So the idea is since the maximum visitors which can
travel the edge is minimum of the total number of nodes to the left and right of the edge, hence we 
compute it using DFS. If number of visitors one side of the edge is a, then the number of visitors on 
the other side of the edge automatically becomes n-a.
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 100005;
 
vector < pair < ll, ll > > adj[N];
bool visited[N];
ll cnt[N];
ll n, res;
 
// res will contain the total travel distance (travelled one-sidedly) by the visitors, that's why, at the end we are 
// multiplying by 2, as people from both sides are crossing a particular edge.

void dfs(ll u)
{
    visited[u] = true;
    for (int i = 0; i < adj[u].size(); i++)
    {
        ll v = adj[u][i].first;
        ll wt = adj[u][i].second;
        
        if (visited[v])     //i.e. v is the parent of u
            continue;

        dfs(v);
        res += min(cnt[v], n - cnt[v]) * 2ll * wt;
        
        // cnt[v] contains the total number of nodes present in the tree subrooted at node 'v'
        cnt[u] += cnt[v];
    }
}
 
void solve(int test)
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        adj[i].clear();
        visited[i] = false;
        cnt[i] = 1;
    }
    for (int i = 0; i < n-1; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        x--, y--;
        adj[x].push_back({y, z});
        adj[y].push_back({x, z});
    }
    res = 0;
    dfs(0);
    cout << "Case #" << test << ": " << res << endl;
}
 
int main()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
        solve(i);
    return 0;
}
