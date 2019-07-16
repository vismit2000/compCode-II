// Problem : https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/

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
    
    vector <int> ret;
    
    void findNodes(TreeNode *root, int distance, map < TreeNode *, int > path)
    {
        queue < pair < TreeNode *, int > > q;
        q.push({root, 0});
        
        while(!q.empty())
        {
            TreeNode *top = q.front().first;
            int topDist = q.front().second;
            q.pop();
            
            if(topDist == distance)
                ret.push_back(top->val);
            if(topDist > distance)
                break;
            if(top->left && path[top->left] != 1)
                q.push({top->left, topDist+1});
            if(top->right && path[top->right] != 1)
                q.push({top->right, topDist+1});
        }
    }
    
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) 
    {
        map < TreeNode *, TreeNode * > parent;
        map < TreeNode *, int > dist;
        map < TreeNode*, int > path;
        
        queue < TreeNode* > q;
        q.push(root);
        parent[root] == NULL;
        dist[root] = 0;
        
        while(!q.empty())
        {
            TreeNode *top = q.front();
            q.pop();
            
            if(top == target)
                break;
            
            if(top->left)
            {
                parent[top->left] = top;
                dist[top->left] = dist[top]+1;
                q.push(top->left);
            }
            if(top->right)
            {
                parent[top->right] = top;
                dist[top->right] = dist[top]+1;
                q.push(top->right);
            }
        }
        
        TreeNode *p = target;
        while(p != NULL)
        {
            path[p] = 1;
            p = parent[p];
        }
        
        while(1)
        {
            findNodes(target, K, path);
            target = parent[target];
            K--;
            if(K < 0 || target == NULL)
                break;
        }
    
        return ret;
    }
};
