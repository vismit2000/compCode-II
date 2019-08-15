/*Problem:
You are given a grid with n rows and m columns. Each of the numbers from 1 to x is present twice in the grid, 
at the coordinates (ai,bi) and (ci,di).
You have to calculate if it is possible to draw curves that join the two pairs of coordinates for each of the numbers, 
in such a way that none of the curves overlap, or leave the boundaries of the grid.
*/

/*Solution Approach:
We call a number 'critical', if both occurrences of this number is on the border of the grid. Suppose that there are two 
critical numbers a and b, and they appear in the border in the order a, b, a, b. In this case, it is clear that we can’t 
connect both numbers without overlapping, thus the answer is 'No'. Otherwise, we can connect all numbers in the following 
order:

First, we connect non-critical numbers one by one.
Then, we connect critical numbers one by one. This way, we never get stuck.

How can we check if there exists such a pair (a, b) of critical numbers? Start from any point on the border and check all 
critical points on the border one by one in clockwise order (ignore non-critical numbers on the border). Initially we have 
an empty stack, and whenever we find an critical number x on the border, do the following:

If the top element of the stack is also x, pop it.
Otherwise, push x into the stack.

If the stack becomes empty after we check all points, the answer is 'Yes'. Otherwise the answer is 'No'. 
This algorithm works in O(NlogN).
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, m, x, a, b;
        cin >> n >> m >> x;
        priority_queue < pair < int,int > > pq;
        vector<int> A(x, 2);
        for (int i = 0; i < 2*x; i++) 
        {
            // inserting in a priority queue in such a way that
            // they are popped in anti-clockwise order
            cin >> a >> b;
            if (a == 0)
                pq.push({b, i / 2});
            else if (b == m)
                pq.push({m + a, i / 2});
            else if (a == n)
                pq.push({m + n + m - b, i / 2});
            else if (b == 0)
                pq.push({m + n + m + n - a, i / 2});
            else
                A[i/2]--;
        }
        
        stack<int> S;
        while (!pq.empty())
        {
            // checking if any of the curves overlap
            a = pq.top().second;
            pq.pop();
            if (A[a] != 2) continue;
            if (S.empty()) S.push(a);
            else if (S.top() == a) S.pop();
            else S.push(a);
        }
        if (S.empty()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
