// https://leetcode.com/contest/weekly-contest-145/problems/longest-well-performing-interval/

/*
We are given hours, a list of the number of hours worked per day for a given employee.

A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.

A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.

Return the length of the longest well-performing interval.
*/

class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();

        for (int i = 0; i < n; i++)
            hours[i] = hours[i] > 8 ? +1 : -1;

        vector<int> sums(n + 1, 0);

        for (int i = 0; i < n; i++)
            sums[i + 1] = sums[i] + hours[i];

        int best = 0;

        for (int i = 0; i < n; i++)
            for (int j = n; j > i && j - i > best; j--)
                if (sums[i] < sums[j])
                    best = j - i;

        return best;
    }
};

// O(N) Without Hashmap. Generalized Problem & Solution: Find Longest Subarray With Sum >= K
/*
Problem:

input: arrary arr in which elements are arbitrary integers.
output: length of a longest subarray arr[i, j) with sum(arr[i], ... , arr[j-1]) >= K.

Solution:

Compute prefix sum of arr as prefixSum so that prefixSum[j] - prefixSum[i] = sum(arr[i], ... arr[j-1])
Iterate through prefixSum from begin to end and build a strictly monotone decreasing stack smdStack. (smdStack.top() is the smallest)
Iterate through prefixSum from end to begin. For each prefixSum[i], while smdStack.top() is less than prefixSum[i] by at least K, pop smdStackand try to update result by subarray [index of top,i). Until top element is not less than it by K.
Return result.
Time complexity: O(n)

step1, compute prefixSum O(n)
step2, build strictly monotone decreasing stack O(n)
step3, iterate prefixSum O(n). pop top elements in smdStack O(n)

Explanation:

For simplicity, call (i, j) a valid pair if the inequation prefixSum[j] - prefixSum[i] >= K holds. Our goal is to optimize j-i over all valid pair (i, j).

Firstly, fix j and minimize i. Consider any i1 and i2 that i1 < i2 < j and prefixSum[i1] <= prefixSum[i2]. It is obvious that (i2, j) can't be a candidate of optimal subarray because (i1, j) is more promising to be valid and longer than (i2, j). This discovery tells us that candidates can form a strictly monotone descresing stack.
Secondly, fix i and maximize j. Consider any j1 and j2 that i < j1 < j2 and prefixSum[j2] - prefix[i] >= K. We can find that (i, j1) can't be a candidate of optimal subarrary because (i, j2) is better. This discovery tells us that we should iterate j from end to begin and if we find a valid (i, j), we don't need to keep i in smdStack any longer.
*/

class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int len = hours.size();
        vector<int> prefixSum(len+1, 0);
        for (int i = 1; i <= len; ++i) {
            prefixSum[i] = prefixSum[i-1] + (hours[i-1] > 8 ? 1 : -1);
        }
        stack<int> smdStack;
        for (int i = 0; i <= len; ++i) {
            if (smdStack.empty() || prefixSum[smdStack.top()] > prefixSum[i]) {
				// Trick, store index than value.
                smdStack.push(i);
            }
        }
        int res = 0;
        for (int j = len; j >= 0; --j) {
            while (!smdStack.empty() && prefixSum[smdStack.top()] < prefixSum[j]) {
                res = max(res, j - smdStack.top());
                smdStack.pop();
            }
        }
        return res;
    }
};
