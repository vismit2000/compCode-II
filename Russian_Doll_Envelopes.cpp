// https://leetcode.com/problems/russian-doll-envelopes/

/*The problem boils down to a two dimensional version of the longest increasing subsequence problem (LIS).*/

bool compare(vector <int> &v1, vector <int> &v2)
{
    if(v1[0] == v2[0])
        return v1[1] < v2[1];
    return v1[0] < v2[0];
}

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) 
    {
        int n = envelopes.size();
        if(n == 0)
            return 0;
        
        int *A = new int[n];
        
        sort(envelopes.begin(), envelopes.end(), compare);    

        A[0] = 1;

        for(int i = 1; i < n; i++)
        {
            int w = 0, h = 0, mx = 0;
            for(int j = 0; j < i; j++)
            {
                if(envelopes[j][0]<envelopes[i][0] && envelopes[j][1]<envelopes[i][1] && A[j]>mx )
                    mx = A[j];
                A[i] = 1 + mx;
            }
        }

        int ans = 0;
        for(int i = 0; i < n; i++)
            ans = max(ans, A[i]);

        return ans;
    }
};
