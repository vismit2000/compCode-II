#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

int dirX[4] = {1, 0, -1, 0};
int dirY[4] = {0, -1, 0, 1};

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

        ll R, C;
        cin >> R >> C;

        vector < vector < ll > > grid(R, vector < ll > (C, 0));
        vector < vector < ll > > visited(R, vector < ll > (C, 0));
        priority_queue < vector < ll > > pq;  

        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                cin >> grid[i][j];
                pq.push({grid[i][j], i, j});
            }
        }

        ll ans = 0;  

        while(!pq.empty()){
            vector < ll > top = pq.top();
            pq.pop();

            ll height = top[0], x = top[1], y = top[2];

            if(visited[x][y])
                continue;

            visited[x][y] = 1;

            ans += height - grid[x][y];
            
            for(int i = 0; i < 4; i++){
                ll dx = x + dirX[i];
                ll dy = y + dirY[i];

                if(dx < 0 || dx >= R || dy < 0 || dy >= C || visited[dx][dy])
                    continue;                        
                pq.push({height - 1, dx, dy});
            }
        }
        cout << ans << endl;
    }
    return 0;
}