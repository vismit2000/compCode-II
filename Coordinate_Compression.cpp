#define ll long long
#define MOD 1000000007
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        set < int > X, Y;
        
        for(auto rectangle : rectangles){
            X.insert(rectangle[0]); X.insert(rectangle[2]);
            Y.insert(rectangle[1]); Y.insert(rectangle[3]);
        }
        vector < int > imapx (X.begin(), X.end());
        vector < int > imapy (Y.begin(), Y.end()); 
        
        map < int, int > mapx, mapy;
        for(int i = 0; i < imapx.size(); i++) mapx[imapx[i]] = i;
        for(int i = 0; i < imapy.size(); i++) mapy[imapy[i]] = i;
        
        vector < vector < bool > > grid (imapx.size(), vector < bool > (imapy.size(), false));
        for(auto rectangle : rectangles)
            for(int i = mapx[rectangle[0]]; i < mapx[rectangle[2]]; i++)
                for(int j = mapy[rectangle[1]]; j < mapy[rectangle[3]]; j++)
                    grid[i][j] = true;
        ll ans = 0;
        for(int i = 0; i < imapx.size(); i++)
            for(int j = 0; j < imapy.size(); j++)
                if(grid[i][j])
                    ans += (ll)(imapx[i+1] - imapx[i]) * (imapy[j+1] - imapy[j]);
        ans %= MOD;
        return (int) ans;
    }
};
