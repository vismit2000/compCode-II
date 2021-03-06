//http://codeforces.com/contest/676/problem/C 

#include<bits/stdc++.h>
using namespace std;

int binSrch(int n, int k, string s)
{
    int hi = n, lo = 1, mid, ans = 1;

    while(lo <= hi)
    {
        mid = lo + (hi-lo)/2;

        bool flag = false;
        int cnt_a = 0, cnt_b = 0;

        for(int i = 0; i < mid; i++)
        {
            if(s[i] == 'a')
                cnt_a++;
            else
                cnt_b++;
        }
        if(cnt_a <= k || cnt_b <= k)
            flag = true;

        for(int i = mid; i < n; i++)
        {
            if(s[i-mid] == 'a')
                cnt_a--;
            else
                cnt_b--;
            if(s[i] == 'a')
                cnt_a++;
            else
                cnt_b++;
            if(cnt_a <= k || cnt_b <= k)
                flag = true;
        }
        if(flag)
        {
            ans = mid;
            lo = mid+1;
        }
        else
            hi = mid-1;
    }
    return ans;
}

int main()
{
    int n, k;
    string s;
    cin >> n >> k >> s;
    
    cout << binSrch(n, k, s);

    return 0;
}
