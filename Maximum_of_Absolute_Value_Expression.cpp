// https://leetcode.com/contest/weekly-contest-146/problems/maximum-of-absolute-value-expression/

/*
Given two arrays of integers with equal lengths, return the maximum value of:

|arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|

where the maximum is taken over all 0 <= i, j < arr1.length.
*/

#define INF 0x3f3f3f3f

class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) 
    {
        int max1 = -INF, max2 = -INF, max3 = -INF, max4 = -INF;
        int min1 = INF, min2 = INF, min3 = INF, min4 = INF;
        
        for(int i = 0; i < arr1.size(); i++)
        {
            max1 = max(max1, arr1[i] + arr2[i] + i);
            max2 = max(max2, arr1[i] - arr2[i] + i);
            max3 = max(max3, arr1[i] + arr2[i] - i);
            max4 = max(max4, arr1[i] - arr2[i] - i);
            
            min1 = min(min1, arr1[i] + arr2[i] + i);
            min2 = min(min2, arr1[i] - arr2[i] + i);
            min3 = min(min3, arr1[i] + arr2[i] - i);
            min4 = min(min4, arr1[i] - arr2[i] - i);
        }
        
        int ans = 0;
        
        ans = max(ans, max1 - min1);
        ans = max(ans, max2 - min2);
        ans = max(ans, max3 - min3);
        ans = max(ans, max4 - min4);
        
        return ans;
    }
};
