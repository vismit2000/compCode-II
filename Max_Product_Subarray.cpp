// https://leetcode.com/problems/maximum-product-subarray/

class Solution {
public:
    int maxProduct(vector<int>& A) 
    {
        int n = A.size();

        int positive[n], negative[n];

        int best = A[0];
        positive[0] = A[0], negative[0] = A[0];

        for(int i = 1; i < n; i++)
        {
            if(A[i] > 0)
            {
                positive[i] = max(positive[i-1]*A[i], A[i]);
                negative[i] = min(negative[i-1]*A[i], A[i]);
            }
            else
            {
                positive[i] = max(negative[i-1]*A[i], A[i]);
                negative[i] = min(positive[i-1]*A[i], A[i]);
            }
            best = max(best, positive[i]);
        }
        return best;
    }
};
