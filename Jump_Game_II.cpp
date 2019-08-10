// https://leetcode.com/problems/jump-game-ii/

// Approach: https://www.youtube.com/watch?v=hZkb_Dqu7YY

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Your goal is to reach the last index in the minimum number of jumps.
*/

class Solution {
public:
    int jump(vector<int>& nums) 
    {
        int n = nums.size();
        
        if(n <= 1)
            return 0;
     
        int ans = 1, end = nums[0], lim = nums[0];
        
        for(int i = 0; i < n; i++)
        {
            if(i > lim)
            {
                ans++;
                lim = end;
            }
            end = max(end, i + nums[i]);
        }
        return ans;
    }
};
