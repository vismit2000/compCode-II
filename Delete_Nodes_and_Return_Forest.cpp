//https://leetcode.com/contest/weekly-contest-144/problems/delete-nodes-and-return-forest/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> res;
    
    set<int> dp;
    
    void postOrder(TreeNode* &root)
    {
        if(root == NULL)
            return;
        
        postOrder(root->left);
        postOrder(root->right);
        
        // if root->val is found in the set of nodes to be deleted
        if(dp.find(root->val)!=dp.end())
        {
            if(root->left)  res.push_back(root->left);
            if(root->right) res.push_back(root->right);
            root = NULL;
        }
    }
    
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) 
    {
        for(int i=0;i<to_delete.size();i++)
            dp.insert(to_delete[i]);
        
        postOrder(root);
        if(root)
            res.push_back(root);
        return res;   
    }
};
