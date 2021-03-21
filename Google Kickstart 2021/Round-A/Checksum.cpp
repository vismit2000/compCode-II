// Wrong (Not accepted)

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

int main(){
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
    
    boost;
    int t;
    cin >> t;
    for (int testcase = 1; testcase <= t; testcase++){
        cout << "Case #" << testcase << ": ";
        
        ll N, ans = 0;
        cin >> N;
        vector < vector < ll > > A(N, vector < ll > (N, 0));
        vector < vector < ll > > B(N, vector < ll > (N, 0));
        vector < ll > R(N), C(N), v;

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                cin >> A[i][j];

        
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                cin >> B[i][j];
                v.push_back(B[i][j]);
            }
        }

        for(int i = 0; i < N; i++)
            cin >> R[i];

        for(int i = 0; i < N; i++)
            cin >> C[i];

        sort(v.begin(), v.end());

        for(int i = 0; i < (N-1)*(N-1); i++)
            ans += v[i];
        
        cout << ans << endl;        
    }
    return 0;
}