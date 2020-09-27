// http://discuss.codingblocks.com/t/i-think-their-is-some-fault-with-the-base-case/108124

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 1000000007

ll n;
ll dp[100006][5][5];

ll func(ll i, ll f, ll s) {
	if (i == 2)
		return 1;

	if (dp[i][f][s] != -1)
		return dp[i][f][s];

	if (f == 0) {
		if (s == 0)
			dp[i][f][s] = (func(i - 1, 0, 0) + func(i - 1, 0, 1) + func(i - 1, 0, 2)) % MOD;
		else if (s == 1)
			dp[i][f][s] = (func(i - 1, 1, 0) + func(i - 1, 1, 2)) % MOD;
		else 
			dp[i][f][s] = (func(i - 1, 2, 0) + func(i - 1, 2, 1)) % MOD;
	} 
    else if (f == 1) {
		if (s == 0)
			dp[i][f][s] = (func(i - 1, 0, 0) + func(i - 1, 0, 1) + func(i - 1, 0, 2)) % MOD;
		else if (s == 1)
			dp[i][f][s] = 0;
		else
			dp[i][f][s] = (func(i - 1, 2, 0) + func(i - 1, 2, 1)) % MOD;
	} 
    else if (f == 2) {
		if (s == 0)
			dp[i][f][s] = (func(i - 1, 0, 0) + func(i - 1, 0, 1)) % MOD;
		else if (s == 1)
			dp[i][f][s] = func(i - 1, 1, 0);
		else
			dp[i][f][s] = 0;
	}
	return dp[i][f][s];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	memset(dp, -1, sizeof(dp));

	if (n == 1)
		cout << "3" << endl;
	else if (n == 2)
		cout << "7" << endl;
	else
		cout << (func(n, 0, 0) + func(n, 0, 1) + func(n, 0, 2) + func(n, 1, 0) + func(n, 1, 2) + func(n, 2, 0) + func(n, 2, 1)) % MOD << endl;
	return 0;
}
