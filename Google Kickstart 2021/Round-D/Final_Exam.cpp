/*
    - Searching in sorted intevals
    - Uses idea of LRU cache - List iterator in map
*/
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);
typedef pair < ll , ll > pii;

void operate(ll lo, ll hi, ll ans, list < pii > &recent, map < ll, list < pii > ::iterator > &pos){
    auto erase_itr = pos[lo];
    pos.erase(lo);
    if(lo != ans){
        auto iserted_itr = recent.insert(erase_itr, make_pair(lo, ans - 1));
        pos[lo] = iserted_itr;
    }
    if(hi != ans){
        auto iserted_itr = recent.insert(erase_itr, make_pair(ans + 1, hi));
        pos[ans + 1] = iserted_itr;
    }        
    recent.erase(erase_itr);
}

ll bSearch(ll skill, list < pii > &recent, map < ll, list < pii > ::iterator > &pos){
    ll idx = 0, ans;
    // edge case
    if(skill < pos.begin()->first){
        idx = pos.begin()->first;
        ll end_idx = pos[idx]->second;
        ans = idx;
        pos.erase(recent.front().first);
        recent.pop_front();
        if(idx != end_idx){
            recent.push_front(make_pair(idx + 1, end_idx));
            pos[idx+1] = recent.begin();
        }        
        return ans;
    }

    auto it = pos.lower_bound(skill);
    if(it == pos.end() || it->first > skill) it--;

    ll lo = it->first;
    ll hi = pos[lo]->second;

    ans = -1;

    if(skill >= lo && skill <= hi){
        ans = skill;
        operate(lo, hi, ans, recent, pos);
    }
    else{
        ll op1 = hi, op2 = INF;
        auto op2_itr = pos.upper_bound(skill);
        if(op2_itr != pos.end()) op2 = op2_itr->first;

        if(skill - op1 <= op2 - skill){
            ans = op1;
            operate(lo, hi, ans, recent, pos);
        }
        else{
            ans = op2;
            operate(op2, pos[op2]->second, ans, recent, pos);
        }
    }
    return ans;
}

void solve(){
    list < pii > recent;
    vector < pii > v;
    map < ll, list < pii > ::iterator > pos;
    ll n, m, a, b, s; cin >> n >> m;
    
    for(int i = 0; i < n; i++){
        cin >> a >> b;
        v.push_back(make_pair(a, b));
    }
    sort(v.begin(), v.end());

    for(auto p : v){
        recent.push_back(p);
        auto it = recent.end();
        it--;
        pos[p.first] = it;
    }

    for(int i = 0; i < m; i++){
        cin >> s;
        ll ans = bSearch(s, recent, pos);
        cout << ans;
        if(i != m-1) cout << " ";
        else cout << endl;
    }
}

int main() {   
    boost;
    ll t;
    cin >> t;
    for (int testcase = 1; testcase <= t; testcase++){
        cout << "Case #" << testcase << ": ";
        solve();
    }
}