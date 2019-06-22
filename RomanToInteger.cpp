//https://www.interviewbit.com/problems/roman-to-integer/

#include <bits/stdc++.h>
using namespace std;

map <char, int > mp;

int RomanTOArabic(string s)
{
    int n = s.length();

    mp['I'] = 1;
    mp['V'] = 5;
    mp['X'] = 10;
    mp['L'] = 50;
    mp['C'] = 100;
    mp['D'] = 500;
    mp['M'] = 1000;

    int ret = 0;

    if(n == 1)
        return mp[s[0]];

    int i = 0, cnt = 0;
    char ch = s[0];

    while(i < n)
    {
        while(ch == s[i])
        {
            cnt++;
            i++;
        }
        if(cnt > 1)
        {
            ret += cnt*mp[ch];
            ch = s[i];
            cnt = 0;
            continue;
        }
        cnt = 0;
        if(i-1 < n && mp[s[i]] > mp[ch])
            ret -= mp[ch];
        else
            ret += mp[ch];
        ch = s[i];
    }
    return ret;
}

int main() 
{
    string s;
    cin >> s;
    cout << RomanTOArabic(s);
    return 0;
}


//Editorial

class Solution {
public:
    int romanToInt(string s) {
        int num = 0;
        int size = s.size();

        for (int i = 0; i < size; i++) {
            // Does lesser value precede higher value ? 
            if (i < (size - 1) && romanCharToInt(s[i]) < romanCharToInt(s[i + 1])) {
                num -= romanCharToInt(s[i]);
            } else {
                num += romanCharToInt(s[i]);
            }
        }
        return num;
    }

    int romanCharToInt(char c) {
        switch (c) {
            case 'I':   return 1;
            case 'V':   return 5;
            case 'X':   return 10;
            case 'L':   return 50;
            case 'C':   return 100;
            case 'D':   return 500;
            case 'M':   return 1000;
            default:    return 0;
        }
    }
};
