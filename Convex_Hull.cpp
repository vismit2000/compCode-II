// https://cses.fi/problemset/task/2195

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

 
struct P{
    ll x, y;
    void read(){
        cin >> x >> y;
    }
    P operator - (const P &b) const{
        return P{x - b.x, y - b.y};
    }
    void operator -= (const P &b){
        x -= b.x;
        y -= b.y;
    }
    P operator + (const P &b) const{
        return P{x + b.x, y + b.y};
    }
    void operator += (const P &b){
        x += b.x; y += b.y;
    }
    long long operator * (const P &b) const{
        return x*b.y - y*b.x;
    }
    long long triangle(const P &b, const P &c) const{
        return (b - *this)*(c - *this);
    }
    bool operator <(const P&b) const {
        return make_pair(x, y) < make_pair(b.x, b.y);
    }
};
 
bool intersection(P p1, P p2, P p3, P p4){
    if((p2 - p1)*(p4 - p3) == 0){
        if(p1.triangle(p2, p3) != 0) return 0;
        for(int i = 0; i < 2; i++){
            if(max(p1.x, p2.x) < min(p3.x, p4.x) || max(p1.y, p2.y) < min(p3.y, p4.y)) return 0;
            swap(p1, p3); swap(p2, p4);
        }
    }
    else{
        for(int i = 0; i < 2; i++){
            long long sgn1 = (p3 - p1)*(p2 - p1), sgn2 = (p4 - p1)*(p2 - p1);
            if((sgn1 < 0 && sgn2 < 0) || (sgn1 > 0 && sgn2 > 0)) return 0;
            swap(p1, p3); swap(p2, p4);
        }
    }
    return 1;
}
 
bool segment_contains(P p1, P p2, P p){
    if(p.triangle(p1, p2)) return 0;
    if(max(p1.x, p2.x) < p.x || min(p1.x, p2.x) > p.x) return 0;
    if(max(p1.y, p2.y) < p.y || min(p1.y, p2.y) > p.y) return 0;
    return 1;
}
 
int main(){
    int n; cin >> n;
    vector < P > points(n);
    for(int i = 0; i < n; i++) points[i].read();
    sort(points.begin(), points.end()); // sort from left to right

    vector < P > hull;
    for(int rep = 0; rep < 2; rep++){
        const int S = hull.size();
        for(P C : points){
            while(hull.size() - S >= 2){
                P A = hull.end()[-2];
                P B = hull.end()[-1];
                if(A.triangle(B, C) <= 0) break; // B on the left of C or collinear
                hull.pop_back(); // remove B
            }
            hull.push_back(C);
        }
        hull.pop_back(); // remove rightmost point
        reverse(points.begin(), points.end());
    }
    cout << hull.size() << endl;
    for(P p : hull) cout << p.x << " " << p.y << endl;
}
