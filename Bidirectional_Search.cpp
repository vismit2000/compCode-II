// https://leetcode.com/problems/open-the-lock/

class Solution {
public:
    vector < string > nbrStrs(string key) {
        vector < string > res;
        for (int i = 0 ; i < 4; i++) {
            string tmp = key;
            tmp[i] = (key[i] - '0' + 1) % 10 + '0';
            res.push_back(tmp);
            tmp[i] = (key[i] - '0' - 1 + 10) % 10 + '0';
            res.push_back(tmp);
        }
        return res;
    }
    
    int openLock(vector < string > &deadends, string target) {
        unordered_set<string> dds(deadends.begin(), deadends.end());
        unordered_set<string> q1, q2, pass, visited;
        
        string init = "0000";
        if (dds.count(init) || dds.count(target)) return -1;
        if(target == init) return 0;
        
        visited.insert("0000");
        q1.insert("0000"), q2.insert(target);
        int res = 0;
        
        while (!q1.empty() && !q2.empty()) {
            if (q1.size() > q2.size()) swap(q1, q2);
            pass.clear();
            for (auto ss : q1) {
                vector<string> nbrs = nbrStrs(ss);
                for (auto s : nbrs) {
                    if (q2.count(s)) return res + 1;
                    if (visited.count(s) || dds.count(s)) continue;
                    pass.insert(s);
                    visited.insert(s);
                }
            }
            swap(q1, pass);
            res++;
        }
        return -1;
    }
};
