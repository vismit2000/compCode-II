//https://practice.geeksforgeeks.org/problems/magnet-array-problem/0
/*
Given n Magnets which are placed linearly, with each magnet to be considered as of point object. Each magnet suffers force 
from its left sided magnets such that they repel it to the right and vice versa. All forces are repulsive. The force being 
equal to the distance (1/d , d being the distance). Now given the positions of the magnets, the task to find all the points 
along the linear line where net force is ZERO. 

Note: Distance have to be calculated with precision of 0.0000000000001.

Input:
The first line of input contains an integer T denoting the no of test cases. Then T test cases follow. The second line of each 
test case contains an integer N. Then in the next line are N space separated values of the array M[], denoting the positions of
the magnet.

Output:
For each test case in a new line print the space separated points having net force zero till precised two decimal places.

Constraints:
1<=T<=100
1<=N<=100
1<=M[]<=1000

Example:
Input:
2
2
1 2
4
0 10 20 30
Output:
1.50
3.82 15.00 26.18
*/

#include <bits/stdc++.h>
using namespace std;

#define EPS 0.0000000000001

double binSrch(double lo, double hi, vector < double > &m)
{
    double mid;
    int n = m.size();
    
    while(lo <= hi)
    {
        mid = lo + (hi-lo)/2;
        
        double force = 0.0;
        
        for(int i = 0; i < n; i++)
            force += (1/(mid - m[i]));
            
        if(abs(force) < EPS)
            return mid;
            
        if(force > 0)
            lo = mid;
        else
            hi = mid;
    }
    return mid;
}

int main() 
{
	int t;
	cin >> t;
	while(t--)
	{
	    int n;
	    cin >> n;
	    vector < double > m(n);
	    for(int i = 0; i < n; i++)
	        cin >> m[i];
	        
	    for(int i = 0; i < n-1; i++)
	        cout << fixed << setprecision(2) << binSrch(m[i], m[i+1], m) << " ";
	    cout << endl;
	}
	return 0;
}
