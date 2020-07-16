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
        
        int N, Q;
        cin >> N >> Q;

        vector < vector < int > > v(N+2, vector < int > (4, INF));

        int diff;

        for(int i = 1; i <= N-1; i++){
            cin >> diff;
            v[i][1] = diff;
            v[i+1][0] = diff;
            v[i][2] = i-1;
            v[i][3] = i+1;
        }

        v[1][2] = 0;
        v[0][3] = 1;
        v[N][3] = N+1;
        v[N][2] = N-1;
        v[N+1][2] = N;

        while(Q--){
            int S, K;
            cin >> S >> K;
            int curr = S;

            vector < vector < int > > temp = v;

            for(int i = 1; i < K; i++){
                if(temp[curr][0] < temp[curr][1]){
                    int next = temp[curr][3];
                    int prev = temp[curr][2];

                    temp[prev][3] = next;
                    temp[next][2] = prev;

                    temp[prev][1] = temp[next][0];

                    curr = prev;
                }
                else{
                    int next = temp[curr][3];
                    int prev = temp[curr][2];

                    temp[prev][3] = next;
                    temp[next][2] = prev;

                    temp[next][0] = temp[prev][1];

                    curr = next;
                }
            }
            cout << curr << " ";
        }
        cout << endl;
    }
    return 0;
}