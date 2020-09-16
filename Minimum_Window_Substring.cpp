//https://leetcode.com/problems/minimum-window-substring/

// Very good explanation : https://medium.com/outco/how-to-solve-sliding-window-problems-28d67601a66

#define INF 0x3f3f3f3f

class Solution {
public:
    string minWindow(string s, string t) 
    {
        int n = s.length(), missing, ansLength = INF;
        string ans;
        
        map < char, int > cnt, mp;
        
        for(char ch : t)
            mp[ch]++;
        
        missing = mp.size();
        
        int slow = 0;
        
        for(int fast = 0; fast < n; fast++)
        {
            if(mp.count(s[fast]))
            {
                cnt[s[fast]]++;
                if(cnt[s[fast]] == mp[s[fast]])
                    missing--;
            }
            
            while(missing == 0)
            {
                if(fast-slow+1 < ansLength)
                {
                    ansLength = fast-slow+1;
                    ans = s.substr(slow, ansLength);
                }

                if(mp.count(s[slow]))
                {
                    cnt[s[slow]]--;
                    if(cnt[s[slow]] < mp[s[slow]])
                        missing++;
                }           
                slow++;
            }
        }
        if(ansLength == INF)
            return "";
        return ans;
    }
};
