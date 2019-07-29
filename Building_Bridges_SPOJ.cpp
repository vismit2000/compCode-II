//https://www.spoj.com/problems/BRIDGE/

/*
In this problem we will use the concept of LIS. Two bridges will not cut
each other if both their end points are either in non-increasing or non-
decreasing order. To find the solution we will first pair the endpoints
i.e. ith point in 1st sequence is paired with ith point in 2nd sequence.
Then sort the points w.r.t 1st point in the pair and apply LIS on second
point of the pair.
*/

#include <bits/stdc++.h>
using namespace std;

vector < pair <int, int> > points;

int maxBridges(int n)
{
    //for a single point, there is always a bridge
    if(n == 1)
        return 1;
    
    //Sort the points according to the first sequence
    sort(points.begin(), points.end());

    int res = 0;
    int LIS[n];

    for(int i = 0; i < n; i++)
        LIS[i] = 1;
    
    for(int i = 1; i < n; i++)
        for(int j = 0; j < i; j++)
            if(points[i].second >= points[j].second && LIS[i] < LIS[j]+1)
                LIS[i] = LIS[j] + 1;
    
    for(int i = 0; i < n; i++)
        res = max(res, LIS[i]);
    return res;
}

int main() 
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        points.resize(n);
        
        for(int i = 0; i < n; i++)
            cin >> points[i].first;
        for(int i = 0; i < n; i++)
            cin >> points[i].second;

        cout << maxBridges(n) << endl;

        points.clear();
    }
    return 0;
}
