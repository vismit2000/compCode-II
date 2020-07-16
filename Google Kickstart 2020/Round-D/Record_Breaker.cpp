#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

int main()
{
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
    
    boost;
    int t;
    cin >> t;
    for (int testcase = 1; testcase <= t; testcase++){
        cout << "Case #" << testcase << ": ";
        int n;
        cin >> n;
        vector < int > v(n), rightPref(n, -INF);

        for(int i = 0; i < n; i++)
            cin >> v[i];

        rightPref[0] = v[0];

        for(int i = 1; i < n; i++)
            rightPref[i] = max(v[i], rightPref[i-1]);

        int ans = 0;

        if(n == 1){
            cout << 1 << endl;
            continue;
        }

        for(int i = 0; i < n; i++){
            if(i == 0){
                if(v[i+1] < v[i])
                    ans++;
            }
            else if(i == n-1){
                if(rightPref[i-1] < v[i]){
                    ans++;
                }
            }
            else if(rightPref[i-1] < v[i] && v[i+1] < v[i])
                ans++;
        }

        cout << ans << endl;

    }
    return 0;
}