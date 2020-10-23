// Errichto solution

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
    for (int testcase = 1; testcase <= t; testcase++){
        cout << "Case #" << testcase << ": ";
        int n;
        cin >> n;
        vector < int > a(n);

        for(int i = 0; i < n; i++)
            cin >> a[i];

        double ans = 0;

        for(int x = 0; x < n-1; x++){
            for(int i = x; i >= 0; i--)
                ans += a[i] / (double)(x - i + 1);
            for(int i = x+1; i < n; i++)
                ans += a[i] / (double)(i - x);
        }
        cout << fixed << setprecision(10) << ans << endl;
    }
    return 0;
}
