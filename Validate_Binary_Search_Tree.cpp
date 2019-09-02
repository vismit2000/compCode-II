//https://leetcode.com/problems/validate-binary-search-tree/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#define INF 0x3f3f3f3f3f3f3f3f

class Solution {
public:
    
    bool check(TreeNode *root, long min, long max)
    {
        if(root == NULL)
            return true;
        if(root->val >= max || root->val <= min)
            return false;
        return (check(root->left, min, root->val) && check(root->right, root->val, max));
    }
    
    bool isValidBST(TreeNode* root) 
    {
        return check(root, -INF, INF);
    }
};
