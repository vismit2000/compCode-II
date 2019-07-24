// https://leetcode.com/contest/weekly-contest-146/problems/minimum-cost-tree-from-leaf-values/

/*
Given an array arr of positive integers, consider all binary trees such that:

Each node has either 0 or 2 children;
The values of arr correspond to the values of each leaf in an in-order traversal of the tree.  (Recall that a node is a leaf if and only if it has 0 children.)
The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree respectively.
Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node.  It is guaranteed this sum fits into a 32-bit integer.
*/

const int N_MAX = 105;
const long long LL_INF = (long long) 2e18 + 5;

class Solution {
public:
    int n;
    vector<int> leaves;
    long long dp[N_MAX][N_MAX];

    long long solve(int start, int end) {
        if (end - start <= 1)
            return 0;

        long long &answer = dp[start][end];

        if (answer >= 0)
            return answer;

        answer = LL_INF;

        for (int i = start + 1; i < end; i++) {
            int left = 0, right = 0;

            for (int j = start; j < i; j++)
                left = max(left, leaves[j]);

            for (int j = i; j < end; j++)
                right = max(right, leaves[j]);

            answer = min(answer, left * right + solve(start, i) + solve(i, end));
        }

        return answer;
    }

    int mctFromLeafValues(vector<int>& arr) {
        leaves = arr;
        n = leaves.size();
        memset(dp, -1, sizeof(dp));
        return solve(0, n);
    }
};
