// https://www.hackerrank.com/contests/bppc7/challenges/arpit-classes/problem

/*PROBLEM
Arpit wants to attend all classes next week.
There are N classes happening at locations numbered from 1 to N.
There are N-1 roads connecting class locations and each of them takes a known time to traverse.
Also he precalculated the distance of his hostel room from each class location.
He starts at class number 1 and will visit all classes and comes to his hostel room.
He wanted to find the minimum time it takes to complete the above schedule.

NOTE: Starting From 1 you can visit any class and the time he spends in each class is neglected and classes are happening 
continuously at their respective locations.

INPUT FORMAT
First, there will be a single integer N (the number of classes, 1 ≤ N ≤ 100,000).
Next, there will be N lines, each with an integer ci (starting with i = 0, 0 ≤ ci ≤ 1,000,000,000), the time it takes to get 
from class location i to hostel room.
Finally, the input will contain N-1 lines, each with three integers **a, b, c **(1 ≤ a, b ≤ N, a != b, 0 ≤ c ≤ 1,000).
Each of these lines describes a road between class locations a and b taking c minutes to traverse.
It is guaranteed that you will be able to reach all the class Locations.

CONSTRAINTS
0 ≤ ci ≤ 1,000,000,000
1 ≤ a, b ≤ N
a != b
0 ≤ c ≤ 1,000

OUTPUT FORMAT
Output the minimum time it will take to visit all classes and go hostel room.

NOTE: Home has to be visited at end only.You cannot go to hostel room in between classes .

SAMPLE INPUT 0
3
1
3
4
1 2 1
1 3 2

SAMPLE OUTPUT 0
7

EXPLANATION 0
It is better to follow the path given : 1->2->1->3->1->Room  [which gives minimum time of 7(1+1+2+2+1)].
*/


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <ll, ll > intpair; 

#define MAXN 100000
#define INF 0x3f3f3f3f

bool seen[MAXN];
ll distToNode[MAXN];

vector<intpair> adj[MAXN];

void bfs(int root)
{
    seen[root]=true;
    queue < intpair > myQ;
    myQ.push({root,0});

    while(!myQ.empty())
    {
        intpair curr = myQ.front();
        distToNode[curr.first] = curr.second;
        myQ.pop();
        for(auto it: adj[curr.first])
        {
            if(!seen[it.first])
            {
                seen[it.first] = true;
                myQ.push({it.first, it.second + curr.second});
            }
        }
    }
}

int main()
{
    ll n;
    cin >> n;

    ll hostel[n];
    for(int i = 0; i < n; i++)
        cin >> hostel[i];

    ll a, b, c;
    ll totSum = 0;

    for(int i = 0; i < n-1; i++)
    {
        cin >> a >> b >> c;
        a--;b--;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
        totSum += c;
    }

    for(int i = 0; i < n; i++)
    {
        seen[i] = false;
        distToNode[i] = 0;
    }

    bfs(0);

    ll ans = INF;
    for(int i = 0; i < n; i++)
        ans = min(ans, 2 * totSum - distToNode[i] + hostel[i]);
    
    cout << ans << endl;

    return 0;
}
