// Problem : https://leetcode.com/problems/minimum-size-subarray-sum/
// Approach : Two-pointer

#define INF 0x3f3f3f3f

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) 
    {
        int l = 0, r = 0, n = nums.size();
        int ret = INF;
        
        int sum = 0;
        
        while(l != n)
        {
            if(sum >= s)
                ret = min(ret, r-l);
            if(r == n)
            {
                sum -= nums[l];
                l++;
                continue;
            }
            if(sum < s)
            {
                sum += nums[r];
                r++;   
                continue;
            }
            else
            {
                sum -= nums[l];
                l++;
                continue;
            }
        }
        if(ret == INF)
            return 0;
        return ret;
    }
};

// A better solution - Editorial

int minSubArrayLen(int s, vector<int>& nums)
{
    int n = nums.size();
    int ans = INT_MAX;
    int left = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
        while (sum >= s) {
            ans = min(ans, i + 1 - left);
            sum -= nums[left++];
        }
    }
    return (ans != INT_MAX) ? ans : 0;
}
