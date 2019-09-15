// https://leetcode.com/problems/k-concatenation-maximum-sum/
/*
Given an integer array arr and an integer k, modify the array by repeating it k times.

For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].

Return the maximum sub-array sum in the modified array. Note that the length of the sub-array can be 0 and its sum in that case is 0.

As the answer can be very large, return the answer modulo 10^9 + 7.
*/

const int MOD = 1e9 + 7;

class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        int n = arr.size();
        long long best = 0;
        long long full_sum = accumulate(arr.begin(), arr.end(), 0LL);
        long long sum = 0;

        for (int i = 0; i < n; i++) {
            sum += arr[i];

            if (sum < 0)
                sum = 0;
            else if (sum > best)
                best = sum;
        }

        long long max_prefix = 0, max_suffix = 0;
        sum = 0;

        for (int i = 0; i < n; i++) {
            sum += arr[i];
            max_prefix = max(max_prefix, sum);
        }

        sum = 0;

        for (int i = n - 1; i >= 0; i--) {
            sum += arr[i];
            max_suffix = max(max_suffix, sum);
        }

        if (k > 1) {
            best = max(best, max_suffix + max_prefix);
            best = max(best, max_suffix + max_prefix + (k - 2) * full_sum);
        }

        return best % MOD;
    }
};
