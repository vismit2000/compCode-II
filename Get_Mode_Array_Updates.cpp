/*
You are given an array of N positive integers, A1, A2 ,…, AN. 
Also, given a Q updates of form:

i j: Update Ai = j. 1 ≤ i ≤ N.
Perform all updates and after each such update report mode of the array. Therefore, return an array of Q elements, where ith element is mode of the array after ith update has been executed.

Notes

Mode is the most frequently occuring element on the array.
If multiple modes are possible, return the smallest one.
Update array input is via a Q*2 array, where each row represents a update.
For example,

A=[2, 2, 2, 3, 3]

Updates=    [ [1, 3] ]
            [ [5, 4] ]
            [ [2, 4] ]

A = [3, 2, 2, 3, 3] after 1st update.
3 is mode.

A = [3, 2, 2, 3, 4] after 2nd update.
2 and 3 both are mode. Return smaller i.e. 2.

A = [3, 4, 2, 3, 4] after 3rd update.
3 and 4 both are mode. Return smaller i.e. 3.

Return array [3, 2, 3].
Constraints 
1 ≤ N, Q ≤ 105 
1 ≤ j, Ai ≤ 109
*/

class compare
{
    public:
    bool operator()(pair<int,int> p1,pair<int,int> p2)
    {
        if(p1.first==p2.first)
        return p1.second>p2.second;
        return p1.first<p2.first;
    }
};
vector<int> Solution::getMode(vector<int> &a, vector<vector<int> > &b) {
    map<int,int> m;// map store the exact count of elements
    int n=a.size();
    for(int i=0;i<n;i++)
    {
        m[a[i]]++;
    }
    vector<int> ans;

// take a max heap which store element count and its value
    priority_queue<pair<int,int> ,vector<pair<int,int> >,compare >pq;
    for(int i=0;i<n;i++)
    {
        pq.push(make_pair(m[a[i]],a[i]));
    }
    int i=0,q=b.size();
    while(i<q)
    {
        int index=b[i][0]-1;
        int val=b[i][1];
        int val1=a[index];
        a[index]=val;
        if(val!=val1)
        {
            m[val1]--;
            m[val]++;
            pq.push(make_pair(m[val1],val1));
            pq.push(make_pair(m[val],val));
        }
        while(true)
        {
            pair<int,int> t=pq.top();
            int cnt=t.first;int vall=t.second;
            if(m[vall]==cnt)
            {

         // when top of heap has cnt same as in map then this the answer for the ith query
                ans.push_back(vall);
                break;
            }
            else
                pq.pop();
        }
        i++;
    }
    return ans;
}
