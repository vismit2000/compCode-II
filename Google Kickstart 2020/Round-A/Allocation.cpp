// Approach: Greedy

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

int main()
{
    boost;
    int t;
    cin >> t;
    for(int q = 1; q <= t; q++)
    {
        cout << "Case #" << q << ": ";
        ll n, b;
        cin >> n >> b;
        vector < ll > a(n);

        for(int i = 0; i < n; i++)
            cin >> a[i];
        
        sort(a.begin(), a.end());

        ll ans = 0, sum = 0;

        for(int i = 0; i < n; i++)
        {
            sum += a[i];
            if(sum <= b)
                ans++;
            else
                break;
        }
        cout << ans << endl;        
    }
    return 0;
}