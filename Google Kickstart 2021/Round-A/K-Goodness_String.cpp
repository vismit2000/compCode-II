#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

int main(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    boost;
    int t;
    cin >> t;
    for (int testcase = 1; testcase <= t; testcase++){
        cout << "Case #" << testcase << ": ";

        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;

        int goodness = 0;
        for(int i = 0; i < n/2; i++)
            if(s[i] != s[n-1-i])
                goodness++;
        
        cout << abs(k - goodness) << endl;
    }
    return 0;
}