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
