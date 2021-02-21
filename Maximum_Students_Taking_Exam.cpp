// PROBLEM: https://leetcode.com/problems/maximum-students-taking-exam/

class Solution {
    int m, n;
    int dp[9][9][512];
public:
    int get(int prevN, int i) {
        prevN /= pow(2, i);
        return prevN % 2;
    }

    int set(int currRow, int value) {
        return (currRow * 2 + value) % (1 << (n+1));
    }

    int solve(vector<vector<char>>& seats, int x, int y, int prevN) {
        // advance pointer
        if (y == n)
            y = 0, x++;

        if (x == m) return 0;

        if (dp[x][y][prevN] != -1) return dp[x][y][prevN];
        
        int inc = 1 + solve(seats, x, y + 1, set(prevN, 1));;
        int exc = solve(seats, x, y + 1, set(prevN, 0));


        int left = get(prevN, 0);
        int upper_right = get(prevN, n-2);
        int upper_left = get(prevN, n);
        
        if(seats[x][y] == '#')
            inc = 0; 
        else if(y == 0){
            if(upper_right == 1)
                inc = 0;
        }
        else if(y == n-1){
            if(left == 1 || upper_left == 1)
                inc = 0;
        }
        else{
            if(left == 1 || upper_left == 1 || upper_right == 1)
                inc = 0;
        }
        return dp[x][y][prevN] = max(inc, exc);
    }
    
    int maxStudents(vector<vector<char>>& seats) {
        m = seats.size(), n = seats[0].size();
        memset(dp, -1, sizeof(dp));
        return solve(seats, 0, 0, 0);
    }
};
