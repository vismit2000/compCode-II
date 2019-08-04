// https://leetcode.com/problems/smallest-sufficient-team/

/*
PROBLEM:

In a project, you have a list of required skills req_skills, and a list of people.  The i-th person people[i] contains a list of skills that person has.

Consider a sufficient team: a set of people such that for every required skill in req_skills, there is at least one person in the team who has that skill.  We can represent these teams by the index of each person: for example, team = [0, 1, 3] represents the people with skills people[0], people[1], and people[3].

Return any sufficient team of the smallest possible size, represented by the index of each person.

You may return the answer in any order.  It is guaranteed an answer exists.
/*
APPROACH:

Enumerate given skills. Their index will act as index of bit when we do bitmasking. Also create a set to store diff combination of skills (bitwise).

for each people :
2.1 calculate bitmask of all its skill
for each prev bitmask in our set:
2.1.1 calculate combo of prev and curr skill
2.1.2 if combo doesn't exist already , add it with this people id
2.1.3 if combo bitmask exists but with a larger group of people, replace it with current people and group of people with prev bitmask

return group of people with bitmask (1<<(skills.size())) -1.
*/

class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) 
    {
        int n = req_skills.size(), m = people.size();
        
        unordered_map < string, int > needed;
        
        for(int i = 0; i < n; i++)
            needed[req_skills[i]] = i;
        
		unordered_map<int,vector<int>> dp;  
        dp.reserve(1 << n);   
        dp[0]={};
        
        for(int i = 0;i < m; i++)
        {
            int skill = 0;
            for(auto j : people[i])
                skill |= (1 << needed[j]);
            
            for(auto it = dp.begin(); it != dp.end(); it++)
            {
                int comb = it->first | skill;
                if(dp.find(comb)==dp.end() || dp[comb].size()>1+dp[it->first].size())
                {
                    dp[comb]=it->second;
                    dp[comb].push_back(i);
                }       
            }
        }
        return dp[(1<<n) -1];
    }
};


//Similar solution - BETTER

class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) 
    {
        int n = req_skills.size(), m = people.size();
        unordered_map<string, int> needed;
        for(int i = 0; i < n; ++i) 
            needed[req_skills[i]] = i;
            
        vector<vector<int>> dp(1 << n);

        for(int i = 0; i < m; ++i) 
        {
            int skill = 0;
            for(auto j : people[i])
                skill |= (1 << needed[j]);
            
            dp[skill]=vector<int>{i};  //OR
            
            //dp[skill].clear();
            //dp[skill].push_back(i);
            
            for(int j = 0; j < (1 << n); ++j) 
            {
                if(!dp[j].size()) continue;
                int new_skill = j | skill;
                if (!dp[new_skill].size() || dp[new_skill].size() > dp[j].size() + 1) {
                    dp[new_skill] = dp[j];
                    dp[new_skill].push_back(i);
                }
            }
        }
        return dp.back(); //OR dp[(1<<n) - 1]
    }
};
