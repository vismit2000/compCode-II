#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

void solve(){
    double ans;
    ll n;
    cin >> n;
    if(n <= 1000000){
        ans = 0.0;
        for(int i = 1; i <= n; i++) ans += 1.0/i;
    }
    else
        ans = log(n) + 0.57721566490153286060651209008240243104215933593992;
    cout << ans << endl;
}

int main() {   
    boost;
    cout << fixed << setprecision(20);
    ll t;
    cin >> t;
    for (int testcase = 1; testcase <= t; testcase++){
        cout << "Case #" << testcase << ": ";
        solve();
    }
}
