// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees 
of every node never differ by more than 1.
*/

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
    
    TreeNode* ArrayToBST(vector < int > &v, int s, int e)
    {
        if(s > e)
            return NULL;
        
        int mid = (s+e)/2;
        
        TreeNode *root = new TreeNode(v[mid]);
        root->left = ArrayToBST(v, s, mid-1);
        root->right = ArrayToBST(v, mid+1, e);
        return root;
    }
    
    TreeNode* sortedArrayToBST(vector<int>& nums) 
    {
        return ArrayToBST(nums, 0, nums.size()-1);   
    }
};
