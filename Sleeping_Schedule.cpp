// https://codeforces.com/contest/1324/problem/E
// https://www.youtube.com/watch?v=L0tMJtj3XyQ

#include<bits/stdc++.h>
using namespace std;

int dp[2001][2001];
int a[2001];

int good_sleep(int x, int l, int r) 
{
	if(l <= x && x <= r)
        return 1;
    return 0;
}
 
int main()
{
	int n, h, l, r; 
    cin >> n >> h >> l >> r;

    for (int i = 1; i <= n; ++i)
		cin >> a[i];
    
    // dp[i][j] denotes the max. good sleeping times if Vova sleeps exactly i times and wakes up at jth hour

	dp[0][0] = 0;
 
	for (int i = 1; i < h; ++i)
		dp[0][i] = -1;
 
	for (int i = 0; i < n; i++)
	{
		//i denotes number of sleeps
		//calculate answer for [i+1];
 
		for (int hr = 0; hr < h; hr++)
			dp[i + 1][hr] = -1;
 
		for (int hr = 0; hr < h; hr++)
		{
			if (dp[i][hr] == -1)
				continue;
 
			int h1 = (hr + a[i + 1] - 1 + h) % h;
			int h2 = (hr + a[i + 1]) % h;
 
			dp[i + 1][h1] = max(dp[i + 1][h1], dp[i][hr] + good_sleep (h1, l, r));
			dp[i + 1][h2] = max(dp[i + 1][h2], dp[i][hr] + good_sleep (h2, l, r));
		}
	}
 
	//After n sleeps
	int ans = 0;
 
	for (int i = 0; i < h; ++i)
		if (dp[n][i] != -1)
			ans = max(ans, dp[n][i]);
 
	cout << ans << '\n';
	return 0;
}
