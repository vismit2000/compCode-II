/* Problem:
How many different ways can you get a sum of 12, ignoring the order of the tiles?
There are 9 tiles numbered from 1 to 9.

Approach:
Let w(n,S) stand for the number of ways in which we can make the sum n using the elements of S.

Obviously, w(0,∅) = 1 and w(n,∅) = 0 for any higher values of n.

Then for each number v not already present in S,
  w(n, S ∪ {v}) = w(n,S) + w(n − v, S).
*/

#include<bits/stdc++.h>

const int NVAL = 9;
const int GOAL = 12;

int values[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

int main() 
{
    int ways[GOAL+1];
    for (int i = 1; i <= GOAL; i++) 
        ways[i] = 0;
    
    ways[0] = 1;

    for (int v = 0; v < NVAL; v++) 
        for (int i = GOAL; i >= values[v]; i--)
            ways[i] += ways[i - values[v]];

    printf("There are %d ways to make %d.\n", ways[GOAL], GOAL);
}
