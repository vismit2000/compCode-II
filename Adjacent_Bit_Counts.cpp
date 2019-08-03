// https://www.spoj.com/problems/GNYR09F/
// Adjacent Bit Counts

#include <bits/stdc++.h>
using namespace std;

int dp[105][105][2];

int adjBitCount(int n, int k, int first)
{
    if(n == 0)
        return 0;
    if(n == 1)
    {
        if(k == 0)
            return 1;
        else
            return 0;
    }
    if(dp[n][k][first] != -1)
        return dp[n][k][first];

    if(first == 1)
        return dp[n][k][first] = adjBitCount(n-1, k-1, 1) + adjBitCount(n-1, k, 0);
    else
        return dp[n][k][first] = adjBitCount(n-1, k, 1) + adjBitCount(n-1, k, 0);
}

int main() 
{
    memset(dp, -1, sizeof(dp));
    int t;
    cin >> t;
    while(t--)
    {
        int num, n, k;
        cin >> num >> n >> k;

        cout << num << " " << adjBitCount(n, k, 0) + adjBitCount(n, k, 1) << endl;
    }
    return 0;
}
