#define MAX 1000000000

class SegmentNode{
public:
    int l, r;
    bool state;
    SegmentNode *left, *right;
    SegmentNode(int l, int r, bool state){
        this->l = l;
        this->r = r;
        this->state = state;
        left = NULL;
        right = NULL;
    }
};

class RangeModule {
    SegmentNode *root;
public:
    RangeModule() {
        root = new SegmentNode(0, MAX, false);
    }
    
    void updateRange(SegmentNode *node, int l, int r, bool state){
        if(l > node->r || r < node->l)
            return;
        if(l <= node->l && r >= node->r){
            node->state = state;
            node->left = NULL;
            node->right = NULL;
            return;
        }
        
        int mid = node->l + (node->r - node->l)/2;
        
        if(node->left == NULL){
            node->left = new SegmentNode(node->l, mid, node->state);
            node->right = new SegmentNode(mid + 1, node->r, node->state);
        }
        
        updateRange(node->left, l, r, state);
        updateRange(node->right, l, r, state);
        
        node->state = node->left->state && node->right->state;
    }
    
    bool query(SegmentNode *node, int l, int r){
        if(l > node->r || r < node->l)
            return true;
        if((l <= node->l && r >= node->r) || node->left == NULL)
            return node->state;
        
        return query(node->left, l, r) && query(node->right, l, r);
    }
    
    void addRange(int left, int right) {
        updateRange(root, left, right - 1, true);
    }
    
    bool queryRange(int left, int right) {
        return query(root, left, right - 1);
    }
    
    void removeRange(int left, int right) {
        updateRange(root, left, right - 1, false);
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
