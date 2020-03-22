// Approach: Brute Force (That's why only small testcase passed, not the large one)

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
        ll n, k, p;
        cin >> n >> k >> p;
        vector < vector < ll > > plates(n, vector < ll > (k+1, 0));

        for(int i = 0; i < n; i++)
        {
            for(int j = 1; j <= k; j++)
            {
                cin >> plates[i][j];    
                plates[i][j] += plates[i][j-1];
            }
        }

        if(n == 1)
        {
            cout << plates[0][p] << endl;
        }
        else if(n == 2)
        {
            int j;
            ll ans = 0;

            for(int i = 0; i <= k; i++)
            {
                j = p-i;
                if(j > k || j < 0)
                    continue;
                ans = max(ans, plates[0][i] + plates[1][j]);
            }
            cout << ans << endl;
        }
        else if(n == 3)
        {
            int u;
            ll ans = 0;

            for(int i = 0; i <= k; i++)
            {
                for(int j = 0; j <= k; j++)
                {
                    u = p - i - j;
                    if(u > k || u < 0)
                        continue;
                    ans = max(ans, plates[0][i] + plates[1][j] + plates[2][u]);
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}