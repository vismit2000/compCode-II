// https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/

class Solution {
public:
    // sort by end point, if end points are same - then by start point
    static bool compare(const pair <int, int> & p1, const pair <int, int> & p2)
    {
        if(p1.second == p2.second)
            return p1.first < p2.first;
        return p1.second > p2.second;
    }
    
    int minTaps(int n, vector<int>& ranges) 
    {
        int start, end, pos, ans = 0;
        vector < pair <int, int> > v;
        
        // convert the problem into minimum intervals covering whole range
        //How? - Each tap's range is an interval (i - range[i], i+ range[i])
        for(int i = 0; i <= n; i++)
        {
            start = max(0, i - ranges[i]);
            end = min(n, i + ranges[i]);
            v.push_back({start, end});
        }
        
        // sort by end point, if end points are same - then by start point
        sort(v.begin(), v.end(), compare);
                
        // The problem is somewhat similar to activity selection problem but REMEMBER here we have to
        // find minimum intervals to cover whole range
        
        
        // flag denotes the rightmost end-point upto which the range is covered
        int flag = n;
        
        for(int i = 0; i <= n; )
        {
            int f = 0;
            
            /*
            Why this variable f here?
            To prevent index i from being double incremented in case the code goes into while loop  even once
            */
            
            pos = flag;
            while((i <= n) && (v[i].second >= flag))
            {
                pos = min(pos, v[i].first);
                i++;
                f = 1;
            }    
            
            //pos is used for updating our flag
            
            flag = pos;

            ans++;     
            
            // If we have reached the beginning, i.e. Covered the whole range
            if(flag == 0)
                break;
            if(!f) i++;
        }
        
        // Not yet reached beginning, it means it is impossible to cover the range
        if(flag)
            return -1;
        return ans;
    }
};
