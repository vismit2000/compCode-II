/* 
    Codeforces Painting Fence (Google): https://codeforces.com/problemset/problem/448/C
    Intelligent Divide and Conquer (DnC) - minimum brush strokes to pain fence
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

vector < ll > p;

ll paint(ll l, ll r, ll h){
    if (l > r) return 0;
    ll mn_index = l;
    for(int i = l; i <= r; i++){
        if(p[i] < p[mn_index]) mn_index = i;
    }
    return min(r - l + 1, p[mn_index] - h + paint(l, mn_index - 1, p[mn_index]) + paint(mn_index + 1, r, p[mn_index]));
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ll n; cin >> n;
    p.assign(n, 0);
    for(int i = 0; i < n; i++) cin >> p[i];
    cout << paint(0, n-1, 0) << endl;
}
