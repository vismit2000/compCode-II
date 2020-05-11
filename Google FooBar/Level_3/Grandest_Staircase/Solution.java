public class Solution {
    private static int[][] dp;

    public static int staircase(int n, int k)
    {
        if( n > ((k*(k+1))/2))
            return 0;

        if(n < 0)
            return 0;            

        if(n == 0)
            return 1;
        if(dp[n][k] != -1)
            return dp[n][k];

        int ans = 0;
        for(int i = n-k; i <= n; i++)
            ans += staircase(i, n-1-i);

        return dp[n][k] = ans;
    }

    public static int solution(int n) {
        dp = new int[205][205];
        
        for(int i = 0; i < 205; i++)
            for(int j = 0; j < 205; j++)
                dp[i][j] = -1;
        
        int ans = 0;

        ans = staircase(n, n);
        
        return ans - 1;       
    }
}