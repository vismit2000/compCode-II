// https://www.codechef.com/problems/CIRMERGE
// https://discuss.codechef.com/t/cirmerge-editorial/29723

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f

ll a[405], dp[405][405], sum[405][405];
int n;

ll minPenalty(int i, int j)
{
    if(dp[i][j] != -1)
        return dp[i][j];

    if(i == j)
        return dp[i][j] = 0;

    if((i+1) % n == j)
        return dp[i][j] = a[i] + a[j];

    ll ret = INF;

    for(int k = i; k != j; k = (k+1)%n)
        ret = min(ret, minPenalty(i,k) + minPenalty((k+1)%n, j) + sum[i][j]);

    return dp[i][j] = ret;
}

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n;
        memset(a, -1, sizeof(a));
        memset(dp, -1, sizeof(dp));

        for(int i = 0; i < n; i++)
            cin >> a[i];

        ll ans = INF;

        //pre-compute sum from arr[i...j] - (both inclusive)
        for(int i = 0; i < n; i++)
        {
            sum[i][i] = a[i];
            for(int j = (i+1)%n; j != i; j = (j+1)%n)
                sum[i][j] = sum[i][(j+n-1)%n] + a[j];
        }

        for(int i = 0; i < n; i++)
            ans = min(ans, minPenalty(i, (i+n-1) % n));

        cout << ans << endl;
    }
    return 0;
}
