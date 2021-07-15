#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

void solve(){
    ll a, b, c, d, e, f, g, h, i, ans = 0;
    cin >> a >> b >> c >> d >> f >> g >> h >> i;

    if((2*b) == (a + c)) ans++;
    if((2*h) == (g + i)) ans++;
    if((2*d) == (a + g)) ans++;
    if((2*f) == (c + i)) ans++;

    map < ll, ll > mp;
    mp[a + i]++;
    mp[c + g]++;
    mp[b + h]++;
    mp[d + f]++;

    ll best = 0;
    for(auto it : mp)
        if(it.first % 2 == 0)
            best = max(best, it.second);

    cout << ans + best << endl;
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