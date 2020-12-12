/*
PROBLEM: CF - https://codeforces.com/problemset/problem/1107/E, LC - https://leetcode.com/problems/remove-boxes/
EXPLANATION: Video - https://www.youtube.com/watch?v=NINZAQFW_AE&feature=youtu.be
             Text - https://leetcode.com/problems/remove-boxes/discuss/101310/Java-top-down-and-bottom-up-DP-solutions
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

ll dp[102][102][102];
ll RodCut[102];

void prepareRodCut(vector< ll >&a){
    memset(RodCut, 0, sizeof(RodCut));
    for(int len = 1; len <= a.size(); len++)
        for(int cut = 1; cut <= len; cut++)
            RodCut[len] = max(RodCut[len], a[cut - 1] + RodCut[len - cut]);
}

ll solve(vector<ll>& groups, int i, int j, int extra){
    if(i > j) return 0;
    if(dp[i][j][extra] != -1) return dp[i][j][extra];
 
    ll ans = RodCut[groups[i] + extra] + solve(groups, i+1, j, 0);
    for(int group = i + 2; group <= j; group += 2)
        ans = max(ans, solve(groups, i + 1, group - 1, 0) + solve(groups, group, j, extra + groups[i]));
 
    return dp[i][j][extra] = ans;
}

int main(){   
    boost;
    memset(dp, -1, sizeof(dp));
    ll n; cin >> n;
    string s; cin >> s;
    vector < ll > v(n), a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        v[i] = s[i] - '0';
    }

    vector <ll> groups;
    int consec = 0;
    for(int i = 0; i < v.size(); i++)
        if(i == 0)
            consec++;
        else{
            if(s[i] == s[i-1])
                consec++;
            else{
                groups.push_back(consec);
                consec = 1;
            }
        }
    groups.push_back(consec);
    
    prepareRodCut(a);
    
    int len_grp = groups.size();
    cout << solve(groups, 0, len_grp-1, 0) << endl;
    return 0;
}
