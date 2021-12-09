/*
PROBLEM: https://adventofcode.com/2021/day/7
APPROACH: https://cp-algorithms.com/num_methods/ternary_search.html
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f

ll summation(ll n){
    return (n*(n+1))/2;
}

ll predicate(vector < ll > &v, ll pos){
    ll res = 0;
    for(auto ele : v) res += summation(abs(ele - pos));
    return res;
}

int main(){
    ll n; cin >> n;
    vector < ll > v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    ll l = v[0], r = v[n-1];
    while(r - l >= 3){
        ll m1 = l + (r - l) / 3;
        ll m2 = r - (r - l) / 3;
        ll f1 = predicate(v, m1);      //evaluates the function at m1
        ll f2 = predicate(v, m2);      //evaluates the function at m2
        if (f1 > f2) l = m1;
        else r = m2;
    }
    ll ans = INF;
    for(ll i = l; i <= r; i++) ans = min(ans, predicate(v, i));
    cout << ans << endl;
}
