#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

vector<int> dogs[1001];
int dp[1001][1001][2];


int solve(int i, int x, bool last_fix){
    if(x <= 0)return 0;
    if(i == 1001)return INF;
 
    if(dp[i][x][last_fix] != -1)
        return dp[i][x][last_fix];
 
    int ans = solve(i + 1, x, last_fix);    // Not including shirt i

    for(int j = 0; j < dogs[i].size(); j++)
    {
        if(!last_fix)
            ans = min(ans, dogs[i][j] + solve(i+1, x-(j+1), 1));
        ans = min(ans, 2*dogs[i][j] + solve(i+1, x-(j+1), last_fix));
    }
 
    return dp[i][x][last_fix] = ans;
}

int main()
{
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
    
    boost;
    int t;
    cin >> t;

    for(int tc = 1; tc <= t; tc++){
        cout << "Case #" << tc << ": ";

        int n, k;
        cin >> n >> k;
        vector < int > pos(n), colors(n);
        memset(dp, -1, sizeof(dp));

        for(int i = 0; i <= 1000; i++)
            dogs[i].clear();

        for(int i = 0; i < n; i++)
            cin >> pos[i];
        for(int i = 0; i < n; i++)
            cin >> colors[i];
 
        for(int i = 0; i < n; i++)
            dogs[colors[i]].push_back(pos[i]);
 
        for(int i = 0; i <= 1000; i++)
            sort(dogs[i].begin(), dogs[i].end());
 
        cout << solve(1, k, 0) << endl;
    }
    
    return 0;
}
