// https://code.google.com/codejam/contest/6214486/dashboard#s=p3

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;

    for(int z = 1; z <= t; z++)
    {
        cout << "Case #" << z << ": ";
        int n;
        cin >> n;

        char board[10][10];

        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
                board[i][j] = '#';
        }
        
        string s;
        int p, q; // To store position of bishop

        for(int i = 0; i < n; i++)
        {
            cin >> s;
            board[s[1]-'0'][8-(s[0]-'A')] = s[3];
        }

        int ans = 0;

        for(int i = 1; i <= 8; i++)
        {
            for(int j = 1; j <= 8; j++)
            {
                switch(board[i][j])
                {
                    case 'K' :  if(board[i][j+1] != '#')
                                    ans++;
                                if(board[i][j-1] != '#')
                                    ans++;
                                if(board[i+1][j] != '#')
                                    ans++;
                                if(board[i-1][j] != '#')
                                    ans++;
                                if(board[i-1][j-1] != '#')
                                    ans++;
                                if(board[i+1][j+1] != '#')
                                    ans++;
                                if(board[i-1][j+1] != '#')
                                    ans++;
                                if(board[i+1][j-1] != '#')
                                    ans++;
                                break;

                    case 'Q' :  p = i, q = j;
                                p++;
                                while(p < 10)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    p++;
                                }

                                p = i, q = j;
                                p--;
                                while(p > 0)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    p--;
                                }

                                p = i, q = j;
                                q++;
                                while(q < 10)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    q++;
                                }

                                p = i, q = j;
                                q--;
                                while(q > 0)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    q--;
                                }

                                //check all four diagonals
                                p = i, q = j;
                                p++, q++;
                                while(p < 10 && q < 10)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    p++, q++;
                                }

                                p = i, q = j;
                                p--, q--;
                                while(p > 0 && q > 0)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    p--, q--;
                                }

                                p = i, q = j;
                                p++, q--;
                                while(p < 10 && q > 0)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    p++, q--;
                                }

                                p = i, q = j;
                                p--, q++;
                                while(p > 0 && q < 10)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    p--, q++;
                                }

                                break;

                    case 'R' :  p = i, q = j;
                                p++;
                                while(p < 10)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    p++;
                                }

                                p = i, q = j;
                                p--;
                                while(p > 0)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    p--;
                                }

                                p = i, q = j;
                                q++;
                                while(q < 10)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    q++;
                                }

                                p = i, q = j;
                                q--;
                                while(q > 0)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    q--;
                                }

                                break;

                    case 'B' :  //check all four diagonals
                                p = i, q = j;
                                p++, q++;
                                while(p < 10 && q < 10)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    p++, q++;
                                }

                                p = i, q = j;
                                p--, q--;
                                while(p > 0 && q > 0)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    p--, q--;
                                }

                                p = i, q = j;
                                p++, q--;
                                while(p < 10 && q > 0)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    p++, q--;
                                }

                                p = i, q = j;
                                p--, q++;
                                while(p > 0 && q < 10)
                                {
                                    if(board[p][q] != '#')
                                    {
                                        ans++;
                                        break;
                                    }
                                    p--, q++;
                                }
                                
                                break;

                    case 'N' :  if((i+2 < 10) && (j+1 < 10) && board[i+2][j+1] != '#')
                                    ans++;
                                if((i+2 < 10) && (j-1 > 0) && board[i+2][j-1] != '#')
                                    ans++;
                                if((i-2 > 0) && (j+1 < 10) && board[i-2][j+1] != '#')
                                    ans++;
                                if((i-2 > 0) && (j-1 > 0) && board[i-2][j-1] != '#')
                                    ans++;
                                if((j+2 < 10) && (i+1 < 10) && board[i+1][j+2] != '#')
                                    ans++;
                                if((j+2 < 10) && (i-1 > 0) && board[i-1][j+2] != '#')
                                    ans++;
                                if((j-2 > 0) && (i+1 < 10) && board[i+1][j-2] != '#')
                                    ans++;
                                if((j-2 > 0) && (i-1 > 0) && board[i-1][j-2] != '#')
                                    ans++;
                                break;

                    case 'P' :  if(board[i-1][j-1] != '#')
                                    ans++;
                                if(board[i+1][j-1] != '#')
                                    ans++;
                                break;

                    default : continue;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
