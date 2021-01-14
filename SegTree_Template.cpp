#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

vector < ll > tree, lazy;

ll sum(ll a, ll b){
    return a + b;
}

void updateRangeLazy(ll index, ll s, ll e, ll rs, ll re, ll inc)
{
    if(lazy[index] != 0){
        tree[index] += lazy[index];
        if(s != e){
            lazy[2*index] += lazy[index];
            lazy[2*index+1] += lazy[index];
        }
        lazy[index] = 0;
    }
    
    if(re < s || rs > e)
        return;
    
    if(s >= rs && e <= re) {
        tree[index] += inc;
        if(s != e){
            lazy[2*index] += inc;
            lazy[2*index +1] += inc;
        }
        return;
    }
        
    ll mid = (s+e)/2;
    updateRangeLazy(2*index, s, mid, rs, re, inc);
    updateRangeLazy(2*index + 1, mid+1, e, rs, re, inc);
    tree[index] = sum(tree[2*index], tree[2*index + 1]);
    return;
}

ll queryRangeLazy(ll index, ll s, ll e, ll rs, ll re)
{
    if(lazy[index] != 0){
        tree[index] += lazy[index];
        if(s != e){
            lazy[2*index] += lazy[index];
            lazy[2*index + 1] += lazy[index];
        }
        lazy[index] = 0;
    }
    
    if(re < s || rs > e)
        return 0;
    if(s >= rs && e <= re)
        return tree[index];
    
    ll mid = (s+e)/2;
    ll left = queryRangeLazy(2*index, s, mid, rs, re);
    ll right = queryRangeLazy(2*index + 1, mid+1, e, rs, re);
    return sum(left, right);
}

void buildTree(vector < ll > &a, ll index, ll s, ll e)
{
    if(s == e){
        tree[index] = a[s];
        return;
    }
    if(s > e)
        return;

    ll mid = (s+e)/2;
    buildTree(a, 2*index, s, mid);
    buildTree(a, 2*index + 1, mid+1, e);

    tree[index] = sum(tree[2*index], tree[2*index+1]);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    boost;
    ll n, episodes, ans = 0;
    cin >> n;

    tree.assign(4*n + 3, 0);
    lazy.assign(4*n + 3, 0);
    vector < ll > a(n+1, 0);

    buildTree(a, 1, 1, n);

    for(ll i = 1; i <= n; i++){
        cin >> episodes;
        episodes = min(episodes, n);
        ans += queryRangeLazy(1, 1, n, i, i);
        updateRangeLazy(1, 1, n, i+1, episodes, 1);
    }
    cout << ans << endl;
    return 0;
}
