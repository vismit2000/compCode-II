//https://leetcode.com/problems/largest-rectangle-in-histogram/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) 
    {
        int n = heights.size();
        vector <int> prefix(n), suffix(n);
        
        stack < int > s;
        
        for(int i = 0; i < n; i++)
        {
            if(s.empty())
            {
                prefix[i] = 0;
                s.push(i);
            }
            else if(heights[i] > heights[s.top()])
            {
                prefix[i] = s.top() + 1;
                s.push(i);
            }
            else
            {
                while(!s.empty() && heights[i] <= heights[s.top()])
                    s.pop();
                if(s.empty())
                    prefix[i] = 0;
                else
                    prefix[i] = s.top()  + 1;
                s.push(i);
            }
        }
        
        while(!s.empty())
            s.pop();
        
        for(int i = n-1; i >= 0; i--)
        {
            if(s.empty())
            {
                suffix[i] = n-1;
                s.push(i);
            }
            else if(heights[i] > heights[s.top()])
            {
                suffix[i] = s.top() - 1;
                s.push(i);
            }
            else
            {
                while(!s.empty() && heights[i] <= heights[s.top()])
                    s.pop();
                if(s.empty())
                    suffix[i] = n-1;
                else
                    suffix[i] = s.top() - 1;
                s.push(i);
            }
        }
        
        int largest = 0;
        
        for(int i = 0; i < n; i++)
            largest = max(largest, (suffix[i]-prefix[i]+1)*heights[i]);
        return largest;
    }
};
