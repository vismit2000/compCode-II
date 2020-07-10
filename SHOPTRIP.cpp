// https://www.codechef.com/problems/SHOPTRIP

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

int N, K, VISITED_ALL;
double dp[(1 << 12)][50]; // dp[i][j]: Set of ingredients i till the jth shop

vector < pair < int, int > > coords;
vector < int > ingredients;

double distance(pair < int, int > p1, pair < int, int > p2){
    int dx = p1.first - p2.first;
    int dy = p1.second - p2.second;
    return sqrt(dx*dx + dy*dy);
}

double shopTrip(int mask, int lastShop){
    if(mask == VISITED_ALL)
        return distance(coords[lastShop], coords[0]);
    
    if(dp[mask][lastShop] != 0)
        return dp[mask][lastShop];

    double ans = INF;

    for(int i = 1; i <= N; i++)
        if((mask | ingredients[i]) != mask)
            ans = min(ans, distance(coords[i], coords[lastShop]) + shopTrip(mask | ingredients[i], i));
    
    return dp[mask][lastShop] = ans;
}

int main()
{
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
    
    boost;
    int t;
    cin >> t;
    while(t--)
    {
        cin >> N >> K;

        VISITED_ALL = (1 << K) - 1;

        coords.clear();
        ingredients.clear();

        coords.push_back({0, 0});
        ingredients.push_back(0);

        for(int i = 1; i <= N; i++){
            int x, y;
            cin >> x >> y;
            coords.push_back({x, y});
        }

        int all_available = 0;

        for(int i = 1; i <= N; i++){
            int tempmask = 0;
            string s;  
            cin >> s;
            reverse(s.begin(), s.end());
            for(int j = 0; j < s.length(); j++)
                tempmask |= (1 << j)*(s[j]-'0');
            
            all_available |= tempmask;
            ingredients.push_back(tempmask);
        }

        memset(dp, 0, sizeof(dp));

        if(all_available != VISITED_ALL){
            cout << -1 << endl;
            continue;
        }
        cout << fixed << setprecision(10) << shopTrip(0, 0) << endl;
    }
    return 0;
}
