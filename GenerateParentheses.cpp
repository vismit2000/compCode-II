//https://leetcode.com/problems/generate-parentheses/

void genPar(string s, vector <string> &ret, int open, int closed, int n)
{
    if(closed == n)
    {
        ret.push_back(s);
        return;
    }
    if(open < n)
    {
        s += "(";
        genPar(s, ret, open+1, closed, n);
        s.pop_back();
    }
    if(closed < n && open > closed)
    {
        s += ")";
        genPar(s, ret, open, closed+1, n);
        s.pop_back();
    }
}

class Solution {
public:
    vector<string> generateParenthesis(int n) 
    {
        vector < string > ret;
        
        string s  = "";
        s += "(";
        int open = 1, closed = 0;
        
        genPar(s, ret, open, closed, n);
        
        return ret;
    }
};
