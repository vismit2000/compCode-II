// https://leetcode.com/contest/weekly-contest-145/problems/lowest-common-ancestor-of-deepest-leaves/

// Problem : Given a rooted binary tree, return the lowest common ancestor of its deepest leaves.

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
    TreeNode* dfs(TreeNode* A, int h, int height) {
    if(!A)
        return A;
    if(h == height)
        return A;
    TreeNode* l = dfs(A -> left, h + 1, height);
    TreeNode* r = dfs(A -> right, h + 1, height);
    if(l && r)
        return A;
    if(l)
        return l;     
    return r;
}
    
    int findH(TreeNode* root) {
        if(!root)
            return -1;
        return 1 + max(findH(root -> left), findH(root -> right));
    }
    
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        int height = findH(root);
        return dfs(root, 0, height);
    }
};
