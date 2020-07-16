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
        vector < int > v(n), cont(n);

        int ans = 0;

        for(int i = 0; i < n; i++){
            cin >> v[i];

            if(i == 0)
                cont[i] = 0;
            else{
                if(v[i] > v[i-1])
                    cont[i] = 1;
                else if(v[i] < v[i-1])
                    cont[i] = -1;
                else
                    cont[i] = 0;
            }
            if(i >= 4){
                if(cont[i] == 1 && cont[i-1] == 1 && cont[i-2] == 1 && cont[i-3] == 1){
                    cont[i] = -1;
                    ans++;
                }
                if(cont[i] == -1 && cont[i-1] == -1 && cont[i-2] == -1 && cont[i-3] == -1){
                    cont[i] = 1;
                    ans++;
                }
            }
        }

        // for(int i = 0; i < n; i++)
        //     cout << cont[i] << endl;

        cout << ans << endl;

    }
    return 0;
}