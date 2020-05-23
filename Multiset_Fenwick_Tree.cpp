// https://codeforces.com/contest/1354/problem/D

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

struct FenwickTree{
    int N;
    vector < int > tree;

    void init(int n) {
        N = n;
        tree.assign(n+1, 0);
    }

    void update(int idx, int val){
        while(idx <= N){
            tree[idx] += val;
            idx += idx & -idx;
        }
    }

    void updateMax(int idx, int val){
        while(idx <= N){
            tree[idx] = max(tree[idx], val);
            idx += idx & -idx;
        }
    }

    int pref(int idx){
        int ans = 0;
        while(idx > 0){
            ans += tree[idx];
            idx -= idx & -idx;
        }
        return ans;
    }

    int rsum(int l, int r){
        return pref(r) - pref(l-1);
    }

    int prefMax(int idx){
        int ans = -INF;
        while(idx > 0){
            ans = max(ans, tree[idx]);
            idx -= idx & -idx;
        }
        return ans;
    }
};

int main()
{
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
    
    boost;
    int n, q;
    cin >> n >> q;

    FenwickTree bit;
    bit.init(n);

    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        bit.update(x, 1);
    }

    while(q--){
        int k;
        cin >> k;

        if(k > 0)
            bit.update(k, 1);
        else
        {
            k = -k;      
            int lo = 1, hi = n, mid, ans;

            while(lo <= hi)
            {
                mid = lo + (hi-lo)/2;

                if(bit.pref(mid) >= k)
                {
                    ans = mid;
                    hi = mid - 1;
                }
                else
                    lo = mid + 1;
            }
            bit.update(ans, -1);
        }
    }

    int ans = 0;

    for(int i = 1; i <= n; i++)
        if(bit.pref(i)){
            ans = i;
            break;
        }
    
    cout << ans << endl;

    return 0;
}
