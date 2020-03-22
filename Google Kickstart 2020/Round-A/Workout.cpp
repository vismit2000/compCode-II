// Approach: Binary Search

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
        ll n, k;
        cin >> n >> k;
        vector < ll > m(n);
        
        ll diff = -INF;

        for(int i = 0; i < n; i++)
        {
            cin >> m[i];
            if(i > 0)
                diff = max(diff, m[i] - m[i-1]);
        }

        ll lo = 1, hi = diff, mid, temp, ans = diff;

        while(lo <= hi)
        {
            mid = lo + (hi - lo)/2;
            temp = 0;
            for(int i = 1; i < n; i++)
                temp += (m[i] - m[i-1] - 1) / mid;
            
            if(temp <= k)
            {
                ans = mid;
                hi = mid - 1;
            }
            else
                lo = mid + 1;               
        }
        cout << ans << endl;
    }
    return 0;
}
