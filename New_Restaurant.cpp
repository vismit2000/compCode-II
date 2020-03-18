// https://www.codechef.com/NOV11/problems/NEWREST
// http://discuss.codechef.com/problems/NEWREST

/*
PROBLEM: Chef Dengklek will open a new restaurant in the city. The restaurant will be open for N days. He can cook M 
different types of dish. He would like to cook a single dish every day, such that for the entire N days, he only cook at 
most K distinct types of dishes.
In how many ways can he do that?

EXPLANATION
This problem is to be solved using dynamic programming approach plus some combinatorics.

First, define dp[i][j] as the number of ways to cook exactly j different types of dish for i days. As the base case, it is 
obvious that dp[0][0] = 1, dp[0][x] = 0 for x > 0.

Suppose we know the value of dp[i][j] for some pair (i, j). Now, consider the (i+1)th day. There are two options for us:

Cook a dish which has been cooked before. There are j types of such dishes. 
We can update dp[i+1][j]:  dp[i+1][j] += j * dp[i][j]

Cook a new type of dish. Note that we don’t care which type of dish it is; we only care that its type is different from all 
j types. We can update dp[i+1][j+1]:  dp[i+1][j+1] += dp[i][j]

After that, we’ll take the actual types of dish into account. There are M available types of dish. There are P(M, j) ways to 
choose j types from M types (the order is important). So, the number of ways to cook exactly j different types of dish for i 
days is P(M, j) * dp[i][j] = (M! / (M-j)!) * dp[i][j] = M! * (M-j)!-1 * dp[i][j]. Of course, all calculations are performed 
modulo MOD = 1000000007.

We can precompute all values of k! for all 1 ≤ k ≤ M. The value of k!-1 (mod MOD) can be calculated using Euler’s Theorem: 
k!-1 = k!MOD-2 (mod MOD). Also, the DP values can be computed only once for all T test cases.

Since the original problem asks for the number of ways to cook at most K different types of dish in N days, the final answer
is: sum {M! * (M-j)!-1 * dp[N][j]} for all 1 ≤ j ≤ min(M, K).

The complexity of this solution is O(N(M+K) + M log MOD + T(M+K)).
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll MOD = 1000000007;
const int MAX = 1000005;
int N, M, K;

long long fact[MAX], ifact[MAX];
long long dp[1005][1005];	// define dp[i][j] as the number of ways to cook exactly j different types of dish for i days

ll fastModExp(ll a, ll b, ll m) 
{
	ll res = 1;
	while (b > 0) 
	{
		if (b & 1) 
			res = (res * a) % m;
		a = (a * a) % m;
		b >>= 1;
	}
	return res;
}

void preProcess()
{
	dp[0][0] = 1;
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			// cook a dish which has been cooked before.
			dp[i+1][j] += dp[i][j] * j % MOD;
			if (dp[i+1][j] >= MOD)
				dp[i+1][j] -= MOD;
			
			// cook a new type of dish.
			dp[i+1][j+1] += dp[i][j];
			if (dp[i+1][j+1] >= MOD)
				dp[i+1][j+1] -= MOD;
		}
	}
	
	fact[0] = 1, ifact[0] = 1;
	for (int i = 1; i <= 1000000; i++)
	{
		fact[i] = (i * fact[i-1]) % MOD;
		ifact[i] = fastModExp(fact[i], MOD - 2, MOD);
	}
}

int main()
{
	preProcess();
	int t;
	cin >> t;
	while(t--)
	{
		cin >> N >> M >> K;
		
		ll res = 0;
		for (int j = 1; j <= K && j <= M; j++)
		{
			ll cur = 1;
			cur = (cur * dp[N][j]) % MOD;
			cur = (cur * fact[M]) % MOD;
			cur = (cur * ifact[M-j]) % MOD;
			
			res += cur;
			if (res >= MOD)
				res -= MOD;
		}
		cout << res << endl;
	}
}
