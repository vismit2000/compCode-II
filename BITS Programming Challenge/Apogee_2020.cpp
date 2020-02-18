/*
There are 'n' students in the 2nd year batch in BITS. There are also 'm' branch assocs. Let the branch assocs be numbered 
from 1 to 'm'. Each student 'i' in BITS has a potential p(i), and is a member of his/her branch's assoc, given by index number
c(i). (A student, initially, is part of exactly one branch assoc)
In APOGEE 2020, a series of inter-college coding competitions is organized for 2nd year undergrad students. There is one 
coding competition each day, for a duration of 'd' days.

Every day, in the morning, exactly one 2nd year of BITS leaves their branch assoc, after which they cannot join any branch 
assoc ever again. Also, every day, in the afternoon, the college professors select one student from each branch assoc to form 
a team of students who take part in that day's coding competition (In case a branch assoc has no members, nobody is chosen 
from that branch asoc).

The strength of a team is given by the function f (of the potentials of its members) as given below:

f(multiset of potentials) = smallest non-negative integer that is not present in the multiset of potentials. If the multiset 
is empty, f gives 0.

Help the professors figure out the maximum possible strength of the BITSian team for each day!

Input Format

The first line contains two integers n and m , the number of students and the number of assocs in college.
The second line contains n integers p1,p2,…,pn , where pi is the potential of the i-th student.
The third line contains n integers c1,c2,…,cn, which means that i-th student is initially a member of the assoc with index ci.
The fourth line contains an integer d , number of days for which the college prof wants to know the maximum possible strength 
of the team.
Each of the next d lines contains an integer ki , which means that ki-th student lefts their assocs on the i-th day. It is 
guaranteed, that the ki-th student has not left their assocs earlier.

Constraints

1≤m≤n≤5000
0≤pi<5000
1≤ci≤m
1≤d≤n
1≤ki≤n

Output Format
For each of the d days, print the maximum possible strength of the BITSian team on that day.

Sample Input 0

5 3
0 1 2 2 0
1 2 2 3 2
5
3
2
4
5
1
Sample Output 0
3
1
1
1
0

Explanation 0
Consider the first example:
On the first day, student 3 leaves their club. Now, the remaining students are 1, 2, 4 and 5. We can select students 1, 2 and
4 to get maximum possible strength, which is 3. Note, that we can't select students 1, 2 and 5, as students 2 and 5 belong to
the same club. Also, we can't select students 1, 3 and 4, since student 3 has left their club.
On the second day, student 2 leaves their club. Now, the remaining students are 1, 4 and 5. We can select students 1, 4 and 5
to get maximum possible strength, which is 1.

On the third day, the remaining students are 1 and 5. We can select students 1 and 5 to get maximum possible strength, which 
is 1.

On the fourth day, the remaining student is 1. We can select student 1 to get maximum possible strength, which is 1.

On the fifth day, no club has students and so the maximum possible strength is 0.
*/

#include<bits/stdc++.h>
using namespace std;

const int N = 5005;

int t, n, m, d, p[N], c[N], k[N], vis[N], match[N], r[N],ans[N];
vector<int> a[N];

bool dfs(int x)
{
    if(vis[x]) return false;
    vis[x] = 1;
    for(int i : a[x])
    {
        if(match[i] == -1 || dfs(match[i]))
        {
            match[i] = x;
            return true;
        }
    }
    return false;
}

int main()
{
    cin >> n >> m;
    
    memset(match, -1, sizeof(match));
    
    for(int i = 1; i <= n; i++) cin >> p[i];
    for(int i = 1; i <= n; i++) cin >> c[i];
    
    cin >> d;
    for(int i = 1; i <= d; i++) 
    {
        cin >> k[i];
        r[k[i]] = 1;
    }
    for(int i = 1; i <= n; i++)
    {
        if(!r[i]) 
            a[p[i]].push_back(c[i]);
    }
    
    for(int i = d; i >= 1; i--)
    {
        ans[i] = ans[i+1];
        memset(vis, 0, sizeof(vis));
        while(dfs(ans[i])) 
        {
            memset(vis, 0, sizeof(vis));
            ans[i]++;
        }
        a[p[k[i]]].push_back(c[k[i]]);
    }
    for(int i = 1; i <= d; i++) 
        cout << ans[i] << endl;
    return 0;
}
