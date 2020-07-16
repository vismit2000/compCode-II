#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

void calculateSparse(vector < vector < int > > &table, int height, int u, int v) { 
    table[v][0] = u; 
    for (int i = 1; i <= height; i++){ 
        table[v][i] = table[table[v][i - 1]][i - 1]; 
        if (table[v][i] == -1) 
            break; 
    } 
} 

int kthancestor(vector < vector < int > > &table, int height, int V, int k){ 
    for (int i = 0; i <= height; i++) { 
        if (k & (1 << i)) { 
            V = table[V][i]; 
            if (V == -1) 
                break; 
        } 
    } 
    return V; 
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
    for (int testcase = 1; testcase <= t; testcase++){
        cout << "Case #" << testcase << ": ";
        int n, A, B;
        cin >> n >> A >> B;

        vector < int > v(n+1);

        double total = 0.0 + (double)n;

        int height = (int)ceil(log2(n)); 
        vector < vector < int > > table = vector < vector < int > > (n+1, vector < int > (height+1, -1));

        vector < int > child[n+1];

        for(int i = 1; i <= n-1; i++){
            cin >> v[i];
            calculateSparse(table, height, v[i], i+1);
            child[v[i]].push_back(i+1);
        }
        
        vector < int > a(n+1, 1), b(n+1, 1);

        queue < int > q;
        q.push(1);

        vector < int > arr;

        while(!q.empty()){
            int top = q.front();
            q.pop();

            arr.push_back(top);

            for(auto ele : child[top])
                q.push(ele);
        }

        reverse(arr.begin(), arr.end());

        for(auto ele : arr){
            int parent = kthancestor(table, height, ele, A);
            if(parent != -1)
                a[parent] += a[ele];
        }

        for(auto ele : arr){
            int parent = kthancestor(table, height, ele, B);
            if(parent != -1)
                b[parent] += b[ele];
        }

        // for(int i = 1; i <= n; i++){
        //     int parent = kthancestor(table, height, i, B);
        //     while(parent != -1){
        //         b[parent]++;
        //         parent = kthancestor(table, height, parent, B);
        //     }
        // }

        double ans = 0;

        for(int i = 1; i <= n; i++){
            double First = ((double)a[i]/total);
            double Second = ((double)b[i]/total);
            ans += First + Second - First*Second;
        }
        
        cout << fixed << setprecision(7) << ans << endl;

    }
    return 0;
}