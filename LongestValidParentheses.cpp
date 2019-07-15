/*
  Question Link :
  https://www.interviewbit.com/problems/longest-valid-parentheses/
  https://leetcode.com/problems/longest-valid-parentheses/

  Awesome Tutorial:
  https://leetcode.com/articles/longest-valid-parentheses/
*/

//Using stack

int Solution::longestValidParentheses(string A) 
{
    int ans = 0;
    stack <int> s;
    s.push(-1);
    
    for(int i = 0; i < A.length(); i++)
    {
        if(A[i] == '(')
            s.push(i);
        else
        {
            s.pop();
            if(!s.empty())
                ans = max(ans, i - s.top());
            else
                s.push(i);
        }
    }
    return ans;
}


//Using DP

class Solution {
public:
    int longestValidParentheses(string s) 
    {
        int n = s.length();
        int ans = 0;
        int dp[n+1];
        memset(dp, 0, sizeof(dp));
        
        for(int i = 2; i <= n; i++)
        {
            if(s[i-1] == ')')
            {
                if(s[i-2] == '(')
                    dp[i] = 2 + dp[i-2];
                else
                {
                    if(i-dp[i-1] - 2 >= 0 && s[i-dp[i-1] - 2] == '(')
                        dp[i] = 2 + dp[i-1] + dp[i-dp[i-1] - 2];
                }
                ans = max(ans, dp[i]);
            }
        }
        return ans;
    }
};

//Awesome approach : Without extra space

public class Solution {
    public int longestValidParentheses(String s) {
        int left = 0, right = 0, maxlength = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                maxlength = Math.max(maxlength, 2 * right);
            } else if (right >= left) {
                left = right = 0;
            }
        }
        left = right = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s.charAt(i) == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                maxlength = Math.max(maxlength, 2 * left);
            } else if (left >= right) {
                left = right = 0;
            }
        }
        return maxlength;
    }
}
