//https://leetcode.com/problems/non-overlapping-intervals/
/*
Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals 
non-overlapping.
*/

/*
this as a variation of classic Greedy problem of Activity-Selection. First I determine the maximum number of non-overlapping 
activities. When I subtract the number with size of the input, I get the number of activities I need to remove.
*/

bool compare(vector <int> &v1, vector < int > &v2)
{
    return v1[1] < v2[1];
}

class Solution {
public:
    
    int eraseOverlapIntervals(vector<vector<int>>& intervals) 
    {
        if(intervals.empty())
            return 0;
        int n = intervals.size();
        
        sort(intervals.begin(), intervals.end(), compare);
        
        int ans = 1;
        
        int finish = intervals[0][1];
        
        for(int i = 1; i < n; i++)
        {
            if(intervals[i][0] >= finish)
            {
                ans++;
                finish = intervals[i][1];
            }
        }
        return n-ans;
    }
};
