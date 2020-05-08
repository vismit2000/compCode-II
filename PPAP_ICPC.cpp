// https://www.codechef.com/problems/PENS

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

int n, k;
int pos[1 << 20];
char s[1 << 20];
char p[25];
#define lowbit(x) ((x)&(-(x)))      // Returns the rightmost 1 in binary representation of x

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    boost;
    int t;
    cin >> t;
    while(t--)
    {
        memset(pos, 0, sizeof pos);
        cin >> n >> k;
        cin >> s;

        for (int i = 0; i < n; ++i)
            s[i] -= 'a';

        for (int i = 0; i < k; ++i) 
        {
            cin >> p;
            int l = strlen(p);
            int mask = 0;
            for (int j = 0; j < l; ++j)
                mask |= 1 << (p[j] - 'a');
            pos[mask] = i + 1;
        }

        for (int z = (1 << 20); z > 0; z--) 
        {
            if (pos[z]) 
            {
                int c = z;
                while (c) 
                {
                    pos[z ^ lowbit(c)] = pos[z];
                    c ^= lowbit(c);
                }
            }
        }

        int lst = 0;
        int msk = 0;

        for (int i = 0; i < n; ++i) 
        {
            msk |= 1 << s[i];
            if (!pos[msk]) 
            {
                int z = pos[msk ^ (1 << s[i])];
                for (int j = lst; j != i; ++j)
                    cout << z << ' ';
                lst = i;
                msk = 1 << s[i];
            }
        }

        for (int i = lst; i < n; ++i)
            cout << pos[msk] << ' ';
        cout << endl;
    }
    return 0;
}
