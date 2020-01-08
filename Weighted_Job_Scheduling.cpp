// https://leetcode.com/problems/maximum-profit-in-job-scheduling/

class Solution {
public:
    /* A Binary Search based function to find the latest job (before current job) that doesn't conflict with current job.  "index" is index of the current job.  This function returns -1 if all jobs before index conflict with it. The array jobs[] is sorted in increasing order of finish time.
    */
    int binarySearch(vector < vector < int > > jobs, int index) 
    { 
        int lo = 0, hi = index - 1; 

        while (lo <= hi) 
        { 
            int mid = lo + (hi - lo)/2; 
            if (jobs[mid][0] <= jobs[index][1]) 
            { 
                if (jobs[mid + 1][0] <= jobs[index][1]) 
                    lo = mid + 1; 
                else
                    return mid; 
            } 
            else
                hi = mid - 1; 
        } 
        return -1; 
    } 
    
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) 
    {
        int n = startTime.size();
        
        vector < vector < int > > jobs;
        
        for (int i = 0; i < n; i++) 
            jobs.push_back({endTime[i], startTime[i], profit[i]});
        
        sort(jobs.begin(), jobs.end());
        
        vector <int> dp(n);
        
        dp[0] = jobs[0][2];
        
        for(int i = 1; i < n; i++)
        {
            int include = jobs[i][2];
            int exclude = dp[i-1];
            
            int l = binarySearch(jobs, i);
            
            if(l != -1)
                include += dp[l];
            
            dp[i] = max(include, exclude);
        }
        
        return dp[n-1];
    }
};
