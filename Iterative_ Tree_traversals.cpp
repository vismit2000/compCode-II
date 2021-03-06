09/08/2019

#Iterative InOrder, PreOrder and PostOrder Traversals

struct node
{
    int val;
    node *left, *right;
    node(int x) 
    {
        val = x;
        left = right = NULL;
    }
};

##InOrder

unordered_map<node*, int> cnt;

 void traversal_trick(node *root) 
{
    stack<node*> S;
    
    S.push(root);
    while(!S.empty())
    {
        node* cur = S.top();
        if(cur == NULL) 
        { 
        	S.pop(); 
        	continue; 
        }
        if (cnt[cur] == 0) 
        	S.push(cur->left);
        else if (cnt[cur] == 1) 
        	cout << cur->val << " " ;
        else if (cnt[cur] == 2) 
        	S.push(cur->right);
        else 
        	S.pop();
        cnt[cur]++; 
    }
}

##PreOrder

unordered_map<node*, int> cnt;

void traversal_trick(node *root) 
{
    stack<node*> S;
    
    S.push(root);
    while(!S.empty())
    {
        node* cur = S.top();
        if(cur == NULL) 
        { 
        	S.pop(); 
        	continue; 
        }
        if (cnt[cur] == 0) 
        	cout << cur->val << " " ;
        else if (cnt[cur] == 1) 
        	S.push(cur->left);
        else if (cnt[cur] == 2) 
        	S.push(cur->right);
        else 
        	S.pop();
        cnt[cur]++;
    }
}

##PostOrder

unordered_map<node*, int> cnt;

void traversal_trick(node *root) 
{
    stack<node*> S;
    
    S.push(root);
    while(!S.empty())
    {
        node* cur = S.top();
        if(cur == NULL) 
        { 
        	S.pop(); 
        	continue; 
        }
        if (cnt[cur] == 0) 
        	S.push(cur->left);
        else if (cnt[cur] == 1) 
        	S.push(cur->right);
        else if (cnt[cur] == 2) 
        	cout << cur->val << " " ;
        else 
        	S.pop();
        cnt[cur]++;
    }
}
