// https://leetcode.com/problems/gray-code/

class Solution {
public:
    
    int binaryToGray(int num)
    {
        return num ^ (num >> 1);
    }

    vector<int> grayCode(int n) 
    {
        vector<int> res;
        for (auto i = 0; i < (1 << n); i++)
            res.push_back(binaryToGray(i));
        return res;
    }
};
