// https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050edd/00000000001a274e

#include <bits/stdc++.h>
using namespace std;

#define ll lonf long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

int main()
{
    boost;
    int t;
    cin >> t;
    for(int q = 1; q <= t; q++)
    {
        cout<<"Case #"<<q<<": ";
        int n, cite, prev;
        cin >> n;
        int ans[n+1] = {0};
        int sum[n+1] = {0};
        int freq[100002] = {0};

        for(int i = 1; i <= n; i++)
        {
            cin >> cite;
            prev = ans[i-1];
            ans[i] = prev;
            if(cite <= prev)
                sum[prev]++;
            freq[cite]++;

            if((i - sum[prev]) >= (prev+1))
            {
                ans[i] = ans[i-1] + 1;      
                sum[ans[i]] = sum[prev]+freq[ans[i]]; 
            }       
        }

        for(int i = 1; i <= n; i++)
            cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}
