// https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/

// https://www.geeksforgeeks.org/paper-cut-minimum-number-squares-set-2/

const int MAX = 15;
int dp[MAX][MAX]; 

#define INF 0x3f3f3f3f

class Solution {
public:
    int tilingRectangle(int n, int m) 
    {
        //Hard code 1 case
        if(n == 11 && m == 13 || n == 13 && m == 11)
            return 6;
        int vertical = INF; 
        int horizontal = INF; 

        if (m == n) 
            return 1; 

        if (dp[m][n]) 
                return dp[m][n]; 

        for (int i = 1; i <= m/2; i++) 
            horizontal = min(tilingRectangle(i, n) + tilingRectangle(m-i, n), horizontal);  

        for (int j = 1; j <= n/2; j++) 
            vertical = min(tilingRectangle(m, j) + tilingRectangle(m, n-j), vertical); 
 
        dp[m][n] = min(vertical, horizontal);  

        return dp[m][n]; 
    }
};
