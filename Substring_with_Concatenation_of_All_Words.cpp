// https://leetcode.com/problems/substring-with-concatenation-of-all-words/

/*
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of 
substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.
*/

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) 
    {
        vector <int> v;
        int strLength = s.length(), wordsLength = words.size();       

        if(strLength == 0 || wordsLength == 0)
            return v;

        int wordSize = words[0].length();
        int search = wordsLength * wordSize;

        int rem;
        string temp;

        map < string, int > mp;

        for(int i = 0; i < strLength - search + 1; i++)
        {
            mp.clear();
            for(auto str : words)
                mp[str]++;

            rem = wordsLength;

            for(int j = i; true; j += wordSize)
            {
                temp = s.substr(j, wordSize);
                if(mp[temp] != 0)
                {
                    mp[temp]--;
                    rem--;
                    if(rem == 0)
                        break;
                }
                else
                    break;
            }

            if(rem == 0)
                v.push_back(i);
        }
        return v;
    }
};
