int Solution::ladderLength(string start, string end, vector<string> &dictV) 
{
    unordered_set<string> dict(dictV.begin(), dictV.end());
    int ladder = 1;
    queue < string > q;
    q.push(start);
    
    bool status = false;
    
    while(!q.empty())
    {
        int n = q.size();
        
        for(int i = 0; i < n; i++)
        {
            string word = q.front();
            q.pop();
            
            if(word == end)
            {
                status = true;
                return ladder;
            }
            
            dict.erase(word);
            
            for(int j = 0; j < word.size(); j++)
            {
                char c = word[j];
                for(int k = 0; k < 26; k++)
                {
                    word[j] = 'a' + k;
                    if(dict.find(word) != dict.end())
                        q.push(word);
                }
                word[j] = c;
            }
        }
        ladder++;
    }
    return status ? ladder : 0;
}
