#include <bits/stdc++.h>
using namespace std;

long sum, cnt;

class Node
{
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d)
        {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution
{
public:
    Node *insert(Node *root, int data)
    {
        if(root == NULL)
            return new Node(data);
        
        Node *cur;
            
        if(data <= root->data)
        {
            cur = insert(root->left, data);
            root->left = cur;
        }
        else
        {
            cur = insert(root->right, data);
            root->right = cur;
        }
        return root;
    }
     
    Node *search(Node *root, int data)
    {
        if(root == NULL || data == root->data)
            return root;
        if(data < root->data)
            return search(root->left, data);
        return search(root->right, data);
    }
    
    void inorder(Node *root)
    {
        if(root == NULL)
            return;
        if(root->left == NULL && root->right == NULL)
        {
            if(cnt % 2 == 0)
                sum += root->data;
            cnt++;
        }
        inorder(root->left);
        inorder(root->right);
    }
};

int main() 
{
	int t;
	cin >> t;
	while(t--)
	{
	    int n;
	    cin >> n;
	    int data;
	    Solution myTree;
	    Node *root = NULL;
	    
	    for(int i = 0; i < n; i++)
	    {
	        cin >> data;
	        root = myTree.insert(root, data);
	    }
	    
	    sum = 0;
	    cnt = 0;
	    
	    myTree.inorder(root);
	    
	    cout << sum << endl;
	    
	}
	return 0;
}
