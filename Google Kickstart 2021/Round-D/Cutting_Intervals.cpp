#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

void solve(){
    ll n, c, l, r;
    cin >> n >> c;
    vector < ll > v(10005, 0);
    for(int i = 0; i < n; i++){
        cin >> l >> r;
        if(r-l > 1){
            v[l + 1]++;
            v[r]--;
        }
    }
    for(int i = 1; i <= 10004; i++) v[i] += v[i-1];
    sort(v.rbegin(), v.rend());

    ll len = min((ll)v.size(), c);

    ll ans = n;
    for(int i = 0; i < len; i++)
        ans += v[i];
    cout << ans << endl;
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