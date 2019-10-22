// Problem: https://www.hackerrank.com/challenges/interval-selection/problem

// Approach: Greedy Technique - https://www.hackerrank.com/challenges/interval-selection/editorial

#include <bits/stdc++.h>
using namespace std;

// Sort the intervals based on their ending boundaries
bool compare(const pair <int, int> & p1, const pair <int, int> & p2)
{
    return (p1.second < p2.second);
}

int main ()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t, a, b, ans, n;
    int last, limit;

    cin >> t;

    while(t--)
    {
        ans = 1;
        last = limit = 0;
        cin >> n;

        vector < pair <int, int> > arr;

        for (int i = 0; i < n ; i++) {

            cin >> a >> b;
            arr.push_back({a, b});
        }

        sort(arr.begin(), arr.end(), compare);

        //After sorting, interval[0] will always be taken, so start loop variable from 1 (Note: ans is initialized to 1 already)

        for (int i = 1; i < n; i++) {

            if(arr[i].first > arr[last].second) 
            {
                last = i;
                ans++;
            }
            else if (arr[i].first > limit) 
            {
                limit = arr[last].second;
                last = i;
                ans++;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
