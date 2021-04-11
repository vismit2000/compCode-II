#include<bits/stdc++.h>
using namespace std;
 
struct P{
    long long x, y;
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
    int n, m;
    cin >> n >> m;
    vector<P> poly(n);
    for(int i = 0; i < n; i++) poly[i].read();
    for(int itr = 0; itr < m; itr++){
        int cnt = 0;
        bool flg = 0;
        P p;
        p.read();
        for(int i = 0; i < n; i++){
            if(segment_contains(poly[i], poly[(i + 1)%n], p)) flg = 1;
            if(min(poly[i].x, poly[(i + 1)%n].x) <= p.x && max(poly[i].x, poly[(i + 1)%n].x) > p.x){
                if(poly[i].x < poly[(i + 1)%n].x){
                    if(poly[i].triangle(p, poly[(i + 1)%n]) < 0) cnt++;
                }
                else if((poly[(i + 1)%n].triangle(p, poly[i])) < 0) cnt++;
            }
        }
        if(flg) cout << "BOUNDARY\n";
        else if(cnt % 2) cout << "INSIDE\n";
        else cout << "OUTSIDE\n";
    }
    return 0;
}
