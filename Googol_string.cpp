// https://code.google.com/codejam/contest/4284486/dashboard
// Tutorial : https://unacademy.com/lesson/problem-04-googol-string/4RWCJORL

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int googol(ll len, ll pos)
{
    if((len == 1) || (pos == 1))
        return 0;
    ll mid = len/2;

    if(pos <= mid)
        return googol(mid, pos);
    if(pos == mid+1)
        return 0;
    else 
        return 1-googol(mid, len+1-pos);
}

int main()
{
    int t;
    cin >> t;
    for(int q = 1; q <= t; q++)
    {
        cout << "Case #" << q << ": ";
        ll k, len;
        cin >> k;

        while(len <= k)
            len = 2*len + 1;
        
        cout << googol(len, k) << endl;
    }
    return 0;
}
