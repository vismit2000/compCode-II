// https://leetcode.com/problems/burst-balloons/
// https://www.interviewbit.com/problems/burst-balloons/

// ** Solution approach : https://journeywithdp.blogspot.com/2019/07/burst-balloons-google-interview-question.html

int dp[105][105];

int collectCoins(int L, int R, vector <int> &val)
{
    if(L > R)
        return 0;
    if(dp[L][R] != -1)
        return dp[L][R];
    
    int ans = 0;
    
    for(int k = L; k <= R; k++)
        ans = max(ans, collectCoins(L, k-1, val) + collectCoins(k+1, R, val) + val[k] * (L == 0 ? 1 : val[L-1]) * (R == val.size()-1 ? 1 : val[R+1]));
    
    return dp[L][R] = ans;
}

int Solution::solve(vector<int> &nums) 
{
    int n = nums.size();
    
    for(int i = 0; i < 105; i++)
    {
        for(int j = 0; j < 105; j++)
            dp[i][j] = -1;
    }
        
    return collectCoins(0, n-1, nums);
}
