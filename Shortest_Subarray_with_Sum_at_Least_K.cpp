class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) 
    {
        int n = A.size();
        vector < int > sum(n);
        
        sum[0] = A[0];
        for(int i = 1; i < n; i++)
            sum[i] = sum[i-1] + A[i];
        
        deque < pair < int, int > > q;
        q.push_back({0, -1});
        
        int ans = n+1;
        
        for(int i = 0 ; i < n; i++)
        {
            while(!q.empty() && sum[i] - q.front().first >= K)
            {
                ans = min(ans, i - q.front().second);
                q.pop_front();
            }
            while(!q.empty() && sum[i] <= q.back().first)
                q.pop_back();
            q.push_back({sum[i], i});
        }
        
        if(ans > n)
            return -1;
        return ans;
    }
};
