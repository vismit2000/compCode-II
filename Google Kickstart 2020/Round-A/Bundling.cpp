// Approach: Trie

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);
#define hashmap unordered_map<char, node*>

class node
{
public:
    char data;
    hashmap h;
    bool isTerminal;
    ll no_of_times;

    node(char d)
    {
        data = d;
        isTerminal = false;
        no_of_times = 1;
    }
};

class Trie
{
public:
    node* root;
    Trie()
    {
        root = new node('\0');
    }
    //Insertion
    void addWord(string word)
    {
        node* temp = root;
        for(int i = 0; i < word.length(); i++)
        {
            char ch = word[i];

            if(temp->h.count(ch) == 0)
            {
                node* child = new node(ch);
                temp->h[ch] = child;
                temp = child;
            }
            else
            {
                temp = temp->h[ch];
                (temp->no_of_times)++;
            }
        }
        temp->isTerminal = true;
    }
    //Lookup
    bool search(string word)
    {
        node* temp = root;
        for(int i = 0; i < word.length(); i++)
        {
            char ch = word[i];

            if(temp->h.count(ch))
                temp = temp->h[ch];
            else
                return false;
        }
        return temp->isTerminal;
    }
};

int main()
{
    boost;
    int t;
    cin >> t;
    for(int q = 1; q <= t; q++)
    {
        cout << "Case #" << q << ": ";
        ll N, K;
        cin >> N >> K;
        string s;

        Trie t;

        for(int i = 0; i < N; i++)
        {
            cin >> s;
            t.addWord(s);
        }

        ll ans = 0, temp;

        node *nod;

        queue < node *> que;
        que.push(t.root);

        while(!que.empty())
        {
            nod = que.front();
            que.pop();

            for(auto it : nod->h)
            {
                temp = ((it.second)->no_of_times) / K;
                ans += temp;

                if(temp > 0)
                    que.push(it.second);
            }
        }
        cout << ans << endl;
    }
    return 0;
}