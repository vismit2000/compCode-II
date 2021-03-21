#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

int countL(int a, int b){
    return max(0, min(a/2 - 1, b - 1));
}

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

        ll R, C;
        cin >> R >> C;

        vector < vector < ll > > grid(R, vector < ll > (C, 0));
        vector < vector < ll > > up(R, vector < ll > (C, 0));
        vector < vector < ll > > down(R, vector < ll > (C, 0));
        vector < vector < ll > > left(R, vector < ll > (C, 0));
        vector < vector < ll > > right(R, vector < ll > (C, 0));

        for(int i = 0; i < R; i++)
            for(int j = 0; j < C; j++)
                cin >> grid[i][j];

        up = grid;
        down = grid;
        left = grid;
        right = grid;

        for(int i = 1; i < R; i++){
            for(int j = 0; j < C; j++){
                if(grid[i][j] == 0)
                    up[i][j] = 0;
                else
                    up[i][j] = grid[i][j] + up[i-1][j];
            }
        }

        for(int i = R-2; i >= 0; i--){
            for(int j = 0; j < C; j++){
                if(grid[i][j] == 0)
                    down[i][j] = 0;
                else
                    down[i][j] = grid[i][j] + down[i+1][j];
            }
        }

        for(int j = 1; j < C; j++){
            for(int i = 0; i < R; i++){
                if(grid[i][j] == 0)
                    left[i][j] = 0;
                else
                    left[i][j] = grid[i][j] + left[i][j-1];
            }
        }

        for(int j = C-2; j >= 0; j--){
            for(int i = 0; i < R; i++){
                if(grid[i][j] == 0)
                    right[i][j] = 0;
                else
                    right[i][j] = grid[i][j] + right[i][j+1];
            }
        }

        ll ans = 0;
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                ans += countL(up[i][j], left[i][j]);
                ans += countL(left[i][j], up[i][j]);
                ans += countL(up[i][j], right[i][j]);
                ans += countL(right[i][j], up[i][j]);
                ans += countL(down[i][j], left[i][j]);
                ans += countL(left[i][j], down[i][j]);
                ans += countL(down[i][j], right[i][j]);
                ans += countL(right[i][j], down[i][j]);
            }
        }
        cout << ans << endl;      
    }
    return 0;
}