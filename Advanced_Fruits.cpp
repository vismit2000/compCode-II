//https://www.spoj.com/problems/ADFRUITS/

/*
Approach :
  First we will find the LCS of the two strings.
  We will insert the non-LCS characters in the LCS found above in their original order.
*/

#include <bits/stdc++.h>
using namespace std;

int main() 
{
    string str1, str2;
    while(cin >> str1)
    {
        cin >> str2;
        int m = str1.length(), n = str2.length();

        int LCS[m+1][n+1];

        for(int i = 0; i <= m; i++)
        {
            for(int j = 0; j <= n; j++)
            {
                if(i == 0 || j == 0)
                    LCS[i][j] = 0;
                else if(str1[i-1] == str2[j-1])
                    LCS[i][j] = 1 + LCS[i-1][j-1];
                else  
                    LCS[i][j] = max(LCS[i-1][j], LCS[i][j-1]);
            }
        }

        int i = m, j = n;

        string result = "";

        while(i > 0 && j > 0)
        {
            if(str1[i-1] == str2[j-1])
            {
                result += str1[i-1];
                i--;
                j--;
            }
            else if(LCS[i-1][j] > LCS[i][j-1])
            {
                result += str1[i-1];
                i--;
            }
            else
            {
                result += str2[j-1];
                j--;
            }
        }
        while(i > 0)
        {
            result += str1[i-1];
            i--;
        }
        while(j > 0)
        {
            result += str2[j-1];
            j--;
        }
        reverse(result.begin(), result.end());
        cout << result << endl;
    }
    return 0;
}
