// https://www.hackerrank.com/challenges/manasa-loves-maths/problem

#include <bits/stdc++.h>
using namespace std;

bool ok(int i, int j, int k, string s)
{
    if(((s[i] - '0')*100 + (s[j] - '0')*10 + (s[k] - '0')) % 8 == 0)
        return true;
    return false;
}

string solve(string s) 
{
    int len = s.length();

    if(len == 1)
    {
        if((s[0]-'0') % 8 == 0)
            return "YES";
        else
            return "NO";
    }
    else if(len == 2)
    {
        if(((s[1]-'0')*10+(s[0]-'0')) % 8 == 0 || ((s[0]-'0')*10 + (s[1]- '0')) % 8 == 0)
            return "YES";
        else
            return "NO";
    }
    else
    {
        for(int i = 0; i < len-2; i++)
        {
            for(int j = i+1; j < len-1; j++)
            {
                for(int k = j+1; k < len; k++)
                {
                    if(ok(i, j, k, s) || ok(i, k, j, s) || ok(j, i, k, s) || ok(j, k, i, s) || ok(k, i, j, s) || ok(k, j, i, s))
                        return "YES";
                }
            }
        }
        return "NO";
    }
}

int main()
{
    int t;
    cin >> t;

    while(t--)
    {
        string s;
        cin >> s;
        cout << solve(s) << endl;
    }
    return 0;
}
