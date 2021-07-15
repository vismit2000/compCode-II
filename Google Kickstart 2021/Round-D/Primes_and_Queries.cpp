// Segment tree (seg_tree) of vectors

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);
#define MAX_S 4

vector < vector < ll > > tree;

vector < ll > sum(vector < ll > &a, vector < ll > &b){
    vector < ll > ans;
    for(int i = 0; i < (int)a.size(); i++) ans.push_back(a[i] + b[i]);
    return ans;
}

void updateRange(ll index, ll s, ll e, ll rs, ll re, vector < ll > &inc) {
    if(re < s || rs > e)
        return;
    
    if(s >= rs && e <= re) {
        tree[index] = sum(tree[index], inc);
        return;
    }
        
    ll mid = (s + e) / 2;
    updateRange(2*index + 1, s, mid, rs, re, inc);
    updateRange(2*index + 2, mid + 1, e, rs, re, inc);
    tree[index] = sum(tree[2*index + 1], tree[2*index + 2]);
    return;
}

vector < ll > queryRange(ll index, ll s, ll e, ll rs, ll re) {
    if(re < s || rs > e)
        return vector < ll > (MAX_S, 0);

    if(s >= rs && e <= re)
        return tree[index];
    
    ll mid = (s + e) / 2;
    vector < ll > left = queryRange(2*index + 1, s, mid, rs, re);
    vector < ll > right = queryRange(2*index + 2, mid + 1, e, rs, re);
    return sum(left, right);
}

void buildTree(vector < vector < ll > > &a, ll index, ll s, ll e) {
    if(s == e){
        tree[index] = a[s];
        return;
    }
    if(s > e)
        return;

    ll mid = (s + e) / 2;
    buildTree(a, 2*index + 1, s, mid);
    buildTree(a, 2*index + 2, mid + 1, e);

    tree[index] = sum(tree[2*index + 1], tree[2*index + 2]);
}

ll caclVS(ll ele, ll S, ll P){
    ll val = pow(ele, S) - pow(ele % P, S);
    if(val == 0) return 0;
    ll ans = 0;
    while(val % P == 0){
        ans++;
        val /= P;
    }
    return ans;
}

void solve(){
    ll n, q, p; cin >> n >> q >> p;
    vector < vector < ll > > a(n);

    for(int i = 0; i < n; i++){
        int ele; cin >> ele;
        vector < ll > temp;
        for(int i = 0; i < MAX_S; i++) temp.push_back(caclVS(ele, i+1, p));
        a[i] = temp;
    }

    vector < ll > init(MAX_S, 0);

    tree.assign(4*n + 3, init);

    buildTree(a, 0, 0, n-1);

    while(q--){
        ll type; cin >> type;
        if(type == 1){
            ll pos, val; cin >> pos >> val;
            vector < ll > curValue = queryRange(0, 0, n-1, pos-1, pos-1);
            vector < ll > newValue, inc;
            for(int i = 0; i < MAX_S; i++) newValue.push_back(caclVS(val, i+1, p));
            for(int i = 0; i < MAX_S; i++) inc.push_back(newValue[i] - curValue[i]);
            updateRange(0, 0, n-1, pos-1, pos-1, inc);
        }
        else{
            ll S, L, R; cin >> S >> L >> R;
            vector < ll > ans = queryRange(0, 0, n-1, L-1, R-1);
            cout << ans[S-1] << " ";
        }
    }
    cout << endl;
}

int main() {   
    boost;
    ll t;
    cin >> t;
    for (int testcase = 1; testcase <= t; testcase++){
        cout << "Case #" << testcase << ": ";
        solve();
    }
}