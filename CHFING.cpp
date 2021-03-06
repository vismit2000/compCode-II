//https://www.codechef.com/JUNE19B/problems/CHFING 

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MOD 1000000007

ll findModuloExp(ll a, ll b, ll p)
{
    ll res = 1;
    while(b > 0)
    {
        if (b & 1) 
            res = (res*a) % p; 
        b = b>>1; // b = b/2 
        a = (a*a) % p;   
    } 
    return res;
}

int main()
{
    int t ;
    cin >> t;
    while(t--)
    {
        ll n, k;
        cin >> n >> k;
        ll sum = (k-1) % MOD;

        if(n >= k)
        {
            cout<< sum <<endl;
            continue ;
        }
        ll a, d, terms;
        a = (k - n) % MOD;
        d = -(n-1);
        terms = -((k-1)/d);

        //sum of AP : (n/2)*(2a + (n-1)d)
       
        ll temp1,temp2 ;

        temp1 = (2*a) % MOD ;
        temp1 += (d * (terms-1)) % MOD ;
        temp1 = (temp1 + MOD) % MOD ;

        temp2 = ((terms%MOD) * findModuloExp(2, MOD-2, MOD)) % MOD ;
        temp2 = (temp2 * temp1) % MOD ;
        
        sum = (sum + temp2) % MOD;
        cout << sum <<endl;     
    }
    return 0;
}
