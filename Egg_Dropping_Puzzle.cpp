// https://brilliant.org/wiki/egg-dropping/

#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

int solvepuzzle(int n,int k)        // n: No. of eggs left,     k: No. of floors left 
{
    int numdrops[n+1][k+1];
    int i,j,x;

    for(i = 0; i <= k; i++) 
        numdrops[0][i] = 0;
    for(i = 0; i <= k; i++) 
        numdrops[1][i] = i;
    for(j = 0; j <= n; j++) 
        numdrops[j][0] = 0;

    //This loop fills up the matrix
    for(i = 2; i <= n; i++)
    {
        for(j = 1; j <= k; j++)
        {
            int minimum = INF;

            //Evaluates 1+min{max(numeggs[i][j-x],numeggs[i-1][x-1])), for x:1,2,3...j-1,j}
            for(x = 1; x <= j; x++) 
                minimum = min(minimum,(1 + max(numdrops[i][j-x],numdrops[i-1][x-1]))); // find the critical floor in the worst case scenario, whilst using the best strategy

            //Defines the minimum value for numeggs[i][j]
            numdrops[i][j]=minimum;
        }
    }
    return numdrops[n][k];
}

int main()
{
    int e;  //Number of eggs
    int f;  //Number of floors

    cin >> e >> f;

    cout << solvepuzzle(e,f) << endl;

    return 0;
}
