/*
You are given an n-bit integer (initially 0). There are Q queries. Each query is of following type:
 0 L R: Set all the bits from Lth bit to Rth bit to zero.
 1 L R: Set all the bits from Lth bit to Rth bit to one.
 2 L R: Find the integer formed by the bits in range [L, R]. 

Answer all the queries of type 2. Indexing is 0-based. See the sample test case for clarity.

Input Format
First line contains two integers, nand q. Next Q lines contains Q queries.

Constraints
1<=n,q<=200000 0<=L,R<n

Output Format
For each query of type 2, print the integer(in decimal) formed by it modulo 10^9+7.

Sample Input
3 6
1 0 1
2 0 2
0 1 1
2 1 1
1 2 2
2 0 2

Sample Output
6
0
5

Explanation
Initially the integer in binary is "000". After first query, it becomes, 110(=6). Answer to next query comes out to be 6, i.e. "110" in decimal. After 3rd 
query, it becomes "100". Answer to 4th query is 0, i.e. decimal of "0". After 5th query, it becomes, "101" and thus answer to the last query comes out to be
5, i.e. "101" in decimal
*/

#include <bits/stdc++.h>
using namespace std;

#define boost ios_base ::sync_with_stdio(0); cin.tie(0);
#define N 200005
#define ll long long
#define MOD 1000000007

ll tree[N<<2 + 1], lazy[N<<2 + 1]; // 4*N + 1

ll pow(ll a, ll p, ll m = MOD){
    ll res = 1; 
    while( p > 0){
        if(p & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        p >>= 1;
    }
    return res;
}

void lazy_update(int node, int s, int e){
    if(lazy[node] != -1){
        tree[node] = (pow(2, e - s + 1, MOD) - 1) * lazy[node];
        if(s != e){
            lazy[node*2 + 1] = lazy[node];
            lazy[node*2 + 2] = lazy[node];
        }
        lazy[node] = -1;
    }
}

void update(int node, int s, int e, int l, int r, int x){
    lazy_update(node, s, e); //updating pending lazy updates.
    if(s > r || e < l)
        return;
    if(s >= l && e <= r){
        tree[node]=(pow(2, e - s + 1, MOD) - 1) * x;
        if(s != e){
            lazy[node*2 + 1] = x;
            lazy[node*2 + 2] = x;
        }
        return;
    }
    int mid = (s + e)>>1;
    update(node*2 + 1, s, mid, l, r, x);
    update(node*2 + 2, mid + 1, e, l, r, x);
    tree[node] = (tree[node*2 + 1] * pow(2, e - mid , MOD) % MOD + tree[node*2 + 2]) % MOD;  //merging children to form parent
}

ll query(int node,int s,int e,int l,int r){
    lazy_update(node, s, e); //updating peding lazy updates.
    if(s > r || e < l)
        return 0;
    if(s >= l && e <= r)
        return tree[node];

    int mid = (s + e)>>1;
    int p1 = query(node*2 + 1, s, mid, l, r);
    int p2 = query(node*2 + 2, mid + 1, e, l, r);
    if(r <= mid)
        return p1;
    return (p1 * pow(2, min(e, r) - mid, MOD) % MOD + p2) % MOD;
}

int main(){
    boost;
    int n, q;
    cin >> n >> q;
    while(q--){
        int x, l, r;
        cin >> x >> l >> r;
        if(x < 2)
            update(0, 0, n-1, l, r, x);
        else
            cout << query(0, 0, n-1, l, r) << endl;
    }
    return 0;
}
