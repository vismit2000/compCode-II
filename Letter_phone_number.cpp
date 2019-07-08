//https://leetcode.com/problems/letter-combinations-of-a-phone-number/

class Solution {
public:
    
    void backtrack(string comb, string next, vector < string > &ret, map<int, string> &mp)
    {
        if(next.length() == 0)
        {
            ret.push_back(comb);
            return;
        }
        char digit = next[0];
        string letters = mp[digit - '0'];
        
        for(int i = 0; i < letters.length(); i++)
        {
            string letter = letters.substr(i, 1);
            backtrack(comb + letter, next.substr(1), ret, mp);
        }
    }
    
    vector<string> letterCombinations(string digits) 
    {
        map < int, string > mp;
        mp[2] = "abc";
        mp[3] = "def";
        mp[4] = "ghi";
        mp[5] = "jkl";
        mp[6] = "mno";
        mp[7] = "pqrs";
        mp[8] = "tuv";
        mp[9] = "wxyz";
        
        vector < string > ret;
        
        if(digits.length())
            backtrack("", digits, ret, mp);
               
        return ret;
    }
};
