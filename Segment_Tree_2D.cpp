/*
PROBLEM (Leetcode): Range Sum Query 2D - Mutable, (Lintcode): https://www.lintcode.com/problem/817/
EXPLANATION: https://iq.opengenus.org/2d-segment-tree/
*/

class NumMatrix {
    int n, m;
    vector < vector < int > > tree;
public:
    int sum(int a, int b){
        return a + b;
    }

    void update(vector<int> &segTree, int index, int s, int e, int rs, int re, int inc) {
        if(re < s || rs > e)
            return;

        if(s >= rs && e <= re) {
            segTree[index] += inc;
            return;
        }

        int mid = (s + e) / 2;
        update(segTree, 2*index + 1, s, mid, rs, re, inc);
        update(segTree, 2*index + 2, mid + 1, e, rs, re, inc);
        segTree[index] = sum(segTree[2*index + 1], segTree[2*index + 2]);
        return;
    }

    int query(vector<int> &segTree, int index, int s, int e, int rs, int re) {
        if(re < s || rs > e)
            return 0;

        if(s >= rs && e <= re)
            return segTree[index];

        int mid = (s + e) / 2;
        int left = query(segTree, 2*index + 1, s, mid, rs, re);
        int right = query(segTree, 2*index + 2, mid + 1, e, rs, re);
        return sum(left, right);
    }

    void buildTree(vector < int > &segTree, vector < int > &a, int index, int s, int e) {
        if(s == e){
            segTree[index] = a[s];
            return;
        }
        if(s > e)
            return;

        int mid = (s + e) / 2;
        buildTree(segTree, a, 2*index + 1, s, mid);
        buildTree(segTree, a, 2*index + 2, mid + 1, e);

        segTree[index] = sum(segTree[2*index + 1], segTree[2*index + 2]);
    }

    void update2D(int index, int s, int e, int x1, int y1, int x2, int y2, int inc) {
        if(x2 < s || x1 > e)
            return;

        if(s >= x1 && e <= x2) {
            update(tree[index], 0, 0, m-1, y1, y2, inc);
            return;
        }

        int mid = (s + e) / 2;
        update2D(2*index + 1, s, mid, x1, y1, x2, y2, inc);
        update2D(2*index + 2, mid + 1, e, x1, y1, x2, y2, inc);
        // merge left and right children
        for(int i = 0; i < tree[index].size(); ++i)
            tree[index][i] = sum(tree[2*index + 1][i], tree[2*index + 2][i]);
    }

    int query2D(int index, int s, int e, int x1, int y1, int x2, int y2) {
        if(x2 < s || x1 > e)
            return 0;

        if(s >= x1 && e <= x2)
            return query(tree[index], 0, 0, m-1, y1, y2);

        int mid = (s + e) / 2;
        int left = query2D(2*index + 1, s, mid, x1, y1, x2, y2);
        int right = query2D(2*index + 2, mid + 1, e, x1, y1, x2, y2);
        return sum(left, right);
    }

    void buildTree2D(vector < vector < int > > &mat, int index, int s, int e) {
        if(s == e){
            buildTree(tree[index], mat[s], 0, 0, m-1);
            return;
        }
        if(s > e)
            return;

        int mid = (s + e) / 2;
        buildTree2D(mat, 2*index + 1, s, mid);
        buildTree2D(mat, 2*index + 2, mid + 1, e);

        // merge left and right children
        for(int i = 0; i < tree[index].size(); ++i)
            tree[index][i] = sum(tree[2*index + 1][i], tree[2*index + 2][i]);
    }

    NumMatrix(vector<vector<int>> matrix) {
        n = matrix.size(), m = matrix[0].size();

        tree.assign(4*n + 3, vector < int > (4*m + 3, 0));
        buildTree2D(matrix, 0, 0, n-1);
    }
    
    void update(int row, int col, int val) {
        int oldVal = query2D(0, 0, n-1, row, col, row, col);
        update2D(0, 0, n-1, row, col, row, col, val - oldVal);
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return query2D(0, 0, n-1, row1, col1, row2, col2);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */
