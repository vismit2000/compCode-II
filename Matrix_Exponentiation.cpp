// https://www.codechef.com/problems/CSUMD

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 1000000007

vector < vector < ll > > multiply(vector < vector < ll > > &A,vector < vector < ll > > &B, ll mod){
    int k = A.size();
    vector < vector < ll > > ans(k, vector < ll > (k, 0ll));
    for(int l = 0; l < k; l++)
        for(int m = 0; m < k; m++)
            for(int n = 0; n < k; n++)
                ans[l][m] = (ans[l][m] + A[l][n]*B[n][m]) % mod;
    return ans;
}
vector < vector < ll > > power(vector < vector < ll > > &mat, ll n, ll mod){
    if(n == 0) return {{1ll,0ll},{0ll,1ll}};
    if(n % 2 == 0){
        vector < vector < ll > > temp = power(mat, n/2, mod);
        return multiply(temp, temp, mod);
    }
    vector < vector < ll > > temp = power(mat, n-1, mod);
    return multiply(temp, mat, mod);
 
}
int main() {
    int t; cin>>t;
    while(t--){
        ll n; cin >> n;
        vector < vector < ll > > mat = {{2ll,2ll},{1ll,0ll}};
        if(n == 1){
            cout << 1 << endl;
            continue;
        }
        if(n == 2){
            cout << 3 << endl;
            continue;
        }
        vector < vector < ll > > a = power(mat, n-2, MOD);
        ll ans = (a[0][0]*3ll + a[0][1]*1ll) % MOD;
        cout << ans << endl;
    }
}
