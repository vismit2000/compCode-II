// https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/

#define ll long long
#define MOD 1000000007

class Node{
public:
    ll val;
    ll cntLeft, cntRight;
    Node *left, *right;
    
    Node(ll value){
        val = value;
        cntLeft = cntRight = 0;
        left = right = NULL;
    }
};

class BST{
public:
    Node *root;
    
    void insert(ll value){
        Node *node = new Node(value);
        if(root == NULL){
            root = node;
            return;
        }
        
        Node *prev = NULL;
        Node *temp = root;
        
        while(temp){
            prev = temp;
            if(value <= temp->val){
                temp->cntLeft++;
                temp = temp->left;
            }
            else{
                temp->cntRight++;
                temp = temp->right;
            }
        }
        
        if(value <= prev->val)
            prev->left = node;
        else
            prev->right = node;
    }
};

class Solution {
    ll fact[1001], invFact[1001];
public:
    ll fastModExp(ll a, ll b, ll m){
        ll res = 1;
        while(b > 0){
            if(b & 1) res = (res*a) % m;
            a = (a * a) % m;
            b >>= 1;
        }
        return res;
    }
    
    ll numReorders(Node *node){
        if(node == NULL)
            return 1;
        
        ll leftAns = numReorders(node->left);
        ll rightAns = numReorders(node->right);
        
        ll result = (leftAns * rightAns) % MOD;
        result = (result * fact[node->cntLeft + node->cntRight]) % MOD;
        result = (result * invFact[node->cntLeft]) % MOD;
        result = (result * invFact[node->cntRight]) % MOD;
        
        // cout << node->val << " " << result << endl;
        return result;        
    }
    
    int numOfWays(vector<int>& nums) {
        fact[0] = invFact[0] = 1;
        for(int i = 1; i <= 1000; i++){
            fact[i] = (i * fact[i-1]) % MOD;
            invFact[i] = fastModExp(fact[i], MOD-2, MOD);
        }
        
        BST *bst = new BST();
        for(int num : nums)
            bst->insert(num);
        
        ll ans = numReorders(bst->root) - 1;
        return ans;
    }
};
