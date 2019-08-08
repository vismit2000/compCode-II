// https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/

/*
Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.
*/

typedef tuple <int, int, int> TII;

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) 
    {
        int n = matrix.size();
        int m = matrix[0].size();
        priority_queue < TII, vector <TII>, greater <TII> > pq;
        pq.push({matrix[0][0], 0, 0});
        int cnt = 0;
        TII temp;
        
        while(!pq.empty())
        {
            cnt++;
            temp = pq.top();
            pq.pop();
            int val = get<0>(temp);
            int i = get<1>(temp);
            int j = get<2>(temp);
                        
            if(k == cnt)
                return val;
            if(i < n-1 && matrix[i+1][j] != -1)
            {
                pq.push({matrix[i+1][j], i+1, j});
                matrix[i+1][j] = -1;
            }
            if(j < m-1 && matrix[i][j+1] != -1)
            {
                pq.push({matrix[i][j+1], i, j+1});
                matrix[i][j+1] = -1;
            }
        }
        return 0;
    }
};
