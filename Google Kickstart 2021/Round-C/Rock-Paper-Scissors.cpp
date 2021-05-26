/*
Problem Link: https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435c44/00000000007ec28e

Credits: Errichto - https://www.youtube.com/watch?v=TagGSh6QALs
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

void solve(){
    ll W, E; cin >> W >> E;
    pair < double, int > dp[62][62][62];

    for(int a = 0; a <= 60; ++a)
		for(int b = 0; a + b <= 60; ++b)
			dp[a][b][60-a-b] = {0, -1};

    // a > b > c > a (a beats b, b beats c, c beats a)
    for(int a = 60; a >= 0; --a) {
		for(int b = 60 - a; b >= 0; --b) {
			for(int c = 60 - a - b; c >= 0; --c) {
				dp[a][b][c] = {-1, -1};
	
				double p_a = 1. / 3;
				double p_b = 1. / 3;
				double p_c = 1. / 3;
				if(a + b + c != 0) {
					p_a = (double) b / (a + b + c);
					p_b = (double) c / (a + b + c);
					p_c = (double) a / (a + b + c);
				}
				// move a
				double tmp = dp[a+1][b][c].first + p_a * E + p_b * W;
				dp[a][b][c] = max(dp[a][b][c], make_pair(tmp, 0));
				// move b
				tmp = dp[a][b+1][c].first + p_b * E + p_c * W;
				dp[a][b][c] = max(dp[a][b][c], make_pair(tmp, 1));
				// move c
				tmp = dp[a][b][c+1].first + p_c * E + p_a * W;
				dp[a][b][c] = max(dp[a][b][c], make_pair(tmp, 2));
			}
		}
	}
    string s = "RSP";
	int a = 0, b = 0, c = 0;
	while(a + b + c < 60) {
		int m = dp[a][b][c].second;
		if(m == 0) a++;
		else if(m == 1) b++;
		else c++;
        cout << s[m];
	}
	cout << endl;
}

int main(){
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
    
    boost;
    ll t, x;
    string s = "RSP", ans = "";
    for(int i = 0; i < 20; i++) ans += s;
    cin >> t >> x;
    for (int testcase = 1; testcase <= t; testcase++){
        cout << "Case #" << testcase << ": ";
        solve();
    }
}
