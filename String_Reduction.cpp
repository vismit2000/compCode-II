// Problem: https://www.hackerrank.com/challenges/string-reduction/problem
/*
Given a string consisting of a, b and c's, we can perform the following operation: Take any two adjacent distinct characters 
and replace it with the third character. For example, if 'a' and 'c' are adjacent, they can be replaced with 'b'. What is the
smallest string which can result by applying this operation repeatedly?
*/

// Awesome approach: https://stackoverflow.com/a/8715230

#include <bits/stdc++.h>
using namespace std;

int stringReduction(string s) 
{
    int cntA = 0, cntB = 0, cntC = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == 'a')
            cntA++;
        else if(s[i] == 'b')
            cntB++;
        else if(s[i] == 'c')
            cntC++;
    }

    if(cntA == 0 && cntB == 0)
        return cntC;
    if(cntA == 0 && cntC == 0)
        return cntB;
    if(cntB == 0 && cntC == 0)
        return cntA;

    cntA %= 2;
    cntB %= 2;
    cntC %= 2;

    if(cntA == 0 && cntB == 0 && cntC == 0 || cntA == 1 && cntB == 1 && cntC == 1)
        return 2;
    
    return 1;
}

int main()
{
    int t;
    cin >> t;

    while(t--)
    {
        string s;
        cin >> s;
        cout << stringReduction(s) << endl;
    }
    return 0;
}
