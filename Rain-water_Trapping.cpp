// https://leetcode.com/problems/trapping-rain-water/

class Solution {
public:
    int trap(vector<int>& height) 
    {
        int n = height.size(), mx;
        
        if(n == 0)
            return 0;
        
        int prefix[n], suffix[n];
        
        prefix[0] = 0;
        mx = 0;
        
        for(int i = 1; i < n; i++)
            prefix[i] = max(prefix[i-1], height[i-1]);
        
        suffix[n-1] = 0;
        mx = 0;
        
        for(int i = n-2; i >= 0; i--)
            suffix[i] = max(suffix[i+1], height[i+1]);
       
        int ans = 0;
        
        for(int i = 0; i < n; i++)
        {
            if(min(prefix[i], suffix[i]) > height[i])
                ans += min(prefix[i], suffix[i]) - height[i];
        }
        return ans;
    }
};

//Better Approach : Using 2 pointers
//https://leetcode.com/problems/trapping-rain-water/solution/
