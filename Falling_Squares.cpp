#define MAX 1000000000

class SegmentNode{
public:
    int l, r;
    int height;
    SegmentNode *left, *right;
    SegmentNode(int l, int r, int height){
        this->l = l;
        this->r = r;
        this->height = height;
        left = NULL;
        right = NULL;
    }
};

class Solution {
public:
    void updateRange(SegmentNode *node, int l, int r, int height){
        if(l > node->r || r < node->l)
            return;
        if(l <= node->l && r >= node->r){
            node->height = height;
            node->left = NULL;
            node->right = NULL;
            return;
        }
        
        int mid = node->l + (node->r - node->l)/2;
        
        if(node->left == NULL){
            node->left = new SegmentNode(node->l, mid, node->height);
            node->right = new SegmentNode(mid + 1, node->r, node->height);
        }
        
        updateRange(node->left, l, r, height);
        updateRange(node->right, l, r, height);
        
        node->height = max(node->left->height, node->right->height);
    }
    
    int query(SegmentNode *node, int l, int r){
        if(l > node->r || r < node->l)
            return 0;
        if((l <= node->l && r >= node->r) || node->left == NULL)
            return node->height;
        
        return max(query(node->left, l, r), query(node->right, l, r));
    }

    vector<int> fallingSquares(vector<vector<int>>& positions) {
        SegmentNode *root = new SegmentNode(0, MAX, 0);
        vector < int > ans;
        int result = 0;
        for(auto position : positions){
            int currHeight = query(root, position[0], position[0] + position[1] - 1);
            updateRange(root, position[0], position[0] + position[1] - 1, currHeight + position[1]);
            result = max(result, currHeight + position[1]);
            ans.push_back(result);
        }
        return ans;
    }
};
