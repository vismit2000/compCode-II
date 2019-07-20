// https://leetcode.com/problems/all-possible-full-binary-trees/

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
    unordered_map < int , vector <TreeNode*> > hash;
    
    vector<TreeNode*> allPossibleFBT(int N) 
    {
        if(hash.count(N) != 0)
            return hash[N];
        
        vector < TreeNode * > res;
        
        if(N < 1)
            return res;
        
        TreeNode *temp = new TreeNode(0);
        
        if(N == 1)
            res.push_back(temp);
        
        for(int i = 1; i < N; i += 2)
        {
            vector < TreeNode *> left = allPossibleFBT(i);
            vector < TreeNode *> right = allPossibleFBT(N-1-i);
            
            for(auto tl : left)
            {
                for(auto tr : right)
                {
                    TreeNode *tree = new TreeNode(0);
                    tree->left = tl;
                    tree->right = tr;
                    res.push_back(tree);
                }
            }
        }
        hash[N] = res;
        return res;
    }
};
