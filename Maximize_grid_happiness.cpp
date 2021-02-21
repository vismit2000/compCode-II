/*
PROBLEM: https://leetcode.com/problems/maximize-grid-happiness/
APPROACH: https://leetcode.com/problems/maximize-grid-happiness/discuss/936256/Java-Detailed-Explanation-5D-DP-Ternary-(Base-3)-State-Compression
*/

class Solution {
    int m, n;
    int dp[6][6][7][7][243];
public:
    // Ternary get ith bit value (0, 1 or 2)
    int get(int prevN, int i) {
        prevN /= pow(3, i);
        return prevN % 3;
    }

    // Ternary set new-coming bit to value
    int set(int currRow, int value) {
        return (currRow * 3 + value) % 243;
    }

    // Ternary bit meaning -> empty: 0, intro: 1, extro: 2
    int solve(int x, int y, int iCount, int eCount, int prevN) {
        // advance pointer
        if (y == n)
            y = 0, x++;

        if (iCount == 0 && eCount == 0) return 0;

        if (x == m) return 0;

        if (dp[x][y][iCount][eCount][prevN] != -1) return dp[x][y][iCount][eCount][prevN];

        // leave the cell empty
        int res = solve(x, y + 1, iCount, eCount, set(prevN, 0));

        int up = get(prevN, n - 1);  // get up bit -> which is at (n - 1)th
        int left = get(prevN, 0);  // get left bit -> which is at (0)th

        if (iCount > 0) {  // put intro guy at current cell
            int addOn = 120;

            if (x - 1 >= 0 && up != 0) {
                addOn -= 30;
                if (up == 1) addOn -= 30;
                else addOn += 20;
            }
            if (y - 1 >= 0 && left != 0) {
                addOn -= 30;
                if (left == 1) addOn -= 30;
                else addOn += 20;
            }     
            res = max(res, solve(x, y + 1, iCount - 1, eCount, set(prevN, 1)) + addOn);
        }

        if (eCount > 0) {  // put extro guy at current cell
            int addOn = 40;

            if (x - 1 >= 0 && up != 0) {
                addOn += 20;
                if (up == 1) addOn -= 30;
                else addOn += 20;
            }
            if (y - 1 >= 0 && left != 0) {
                addOn += 20;
                if (left == 1) addOn -= 30;
                else addOn += 20;
            }
            res = max(res, solve(x, y + 1, iCount, eCount - 1, set(prevN, 2)) + addOn);
        }
        return dp[x][y][iCount][eCount][prevN] = res;
    }
    
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
        this->m = m, this->n = n;
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, introvertsCount, extrovertsCount, 0);
    }
};
