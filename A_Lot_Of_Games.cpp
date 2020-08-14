/*
PROBLEM: https://codeforces.com/problemset/problem/456/d
EDITORIAL: https://codeforces.com/blog/entry/13336
TUTORIAL: https://www.quora.com/q/threadsiiithyderabad/Tutorial-on-Trie-and-example-problems
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);
#define hashmap unordered_map<char, node*>

class node{
public:
    char data;
    hashmap h;
    bool isTerminal;
    bool win;
    bool lose;
    
    node(char d){
        data = d;
        isTerminal = false;
        win = false;
        lose = false;
    }
};

class Trie{
    node *root;
public:
    Trie(){
        root = new node('\0');
    }
    
    void addWord(string word){
        node *temp = root;
        
        for(int i = 0; i < word.length(); i++){
            char ch = word[i];
            
            if(temp->h.count(ch))
                temp = temp->h[ch];
            else{
                node *child = new node(ch);
                temp->h[ch] = child;
                temp = child;
            }
        }
        temp->isTerminal = true;
        temp->lose = true;
    }

    void calculateStates(node *n){
        for(auto it : n->h){
            node *child = it.second;
            calculateStates(child);

            n->win |= !child->win;
            n->lose |= !child->lose;
        }
    }

    string query(int k){
        calculateStates(root);
        // if it is not possible to win by moving first
        if(!root->win)
            return "Second";

        // player moving first can force a win now
        // if the first player can force a loss as well, he will change the state of game in his favour
        if(root->lose)
            return "First";
        else{
            if(k % 2 == 1)
                return "First";
            else
                return "Second";
        }       
    }
};

int main()
{
    boost;
    int n, k;
    cin >> n >> k;

    Trie *t = new Trie();
    string str;

    for(int i = 0; i < n; i++){
        cin >> str;
        t->addWord(str);
    }

    cout << t->query(k) << endl;

    return 0;
}
