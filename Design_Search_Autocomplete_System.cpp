// https://leetcode.com/problems/design-search-autocomplete-system/

#define hashmap unordered_map<char, node*>

struct compare{
    bool operator() (pair < string, int > &p1, pair < string, int > &p2){
        if(p1.second == p2.second)
            return p1.first > p2.first;
        return p1.second < p2.second;
    }
};

class node{
public:
    char data;
    string str;
    hashmap h;
    int freq;
    bool isTerminal;
    
    node(char d){
        data = d;
        str = "";
        isTerminal = false;
        freq = 0;
    }
};

class Trie{
public:
    node *root;
    Trie(){
        root = new node('\0');
    }
    
    void addWord(string word, int cnt){
        node *temp = root;
        
        for(int i = 0; i < word.length(); i++){
            char ch = word[i];
            
            if(temp->h.count(ch))
                temp = temp->h[ch];
            else{
                node *child = new node(ch);
                child->str = temp->str + ch;
                temp->h[ch] = child;
                temp = child;
            }
        }
        temp->isTerminal = true;
        temp->freq += cnt;
    }
};

class AutocompleteSystem {
public:
    string curr;
    Trie *t;
    priority_queue < pair < string, int >, vector < pair < string, int > >, compare > pq;
    
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        t = new Trie();
        curr = "";
        for(int i = 0; i < sentences.size(); i++)
            t->addWord(sentences[i], times[i]);
    }
    
    void dfs(node* temp){
        if (temp->isTerminal) 
            pq.push({temp->str, temp->freq});
        
        for (auto ele: temp->h){
            dfs(ele.second);
        }
    }
    
    vector<string> input(char c) {
        pq = priority_queue < pair < string, int >, vector < pair < string, int > >, compare >();
        vector < string > ans;
         
        if(c == '#'){
            t->addWord(curr, 1);
            curr = "";
            return ans;
        }
        
        curr += c;
        
        node *temp = t->root;

        for(int i = 0; i < curr.length(); i++){
            char ch = curr[i];
            
            if(temp->h.count(ch))
                temp = temp->h[ch];
            else
                return ans;
        }
        
        dfs(temp);
        
        while (!pq.empty() && ans.size() < 3){
            ans.push_back(pq.top().first);
            pq.pop();
        }
        
        return ans;
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */
