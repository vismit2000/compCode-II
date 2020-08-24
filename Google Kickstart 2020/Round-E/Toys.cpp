/*EXPLANATION:
- Suppose you have toys at indices i1, i2,... in, which are all the toys the kid could cry at. 
- Assume for now that indices are sorted.
- The kid will cry if sum of all Ei where i is not the current toy is less than R(current toy).
- If I don't remove any toys then the kid will start at index 1, go through the entire list of toys and end at i1.
- If I remove the toy at i1, the kid will lose out the enjoyment gained from that toy but he will gain the enjoyment from all the toys in i1+1,...i2. This is the tradeoff 
you need to consider while removing some toy.
- However, if I remove the toy at i1, some other toys will start to make the kid cry because without the time spent on the toy at i1, their R value will become too big.
- Going back to the previous case. If I remove i2, then the total time spent will actually decrease, because the kid will still top at i1. So it always makes sense to 
remove the first toy when indices are sorted.
- After this happens, if some toy before i1 becomes unusable, it has to be removed before i2
- So you need to always choose the first unplayable toy by index. This can be done using a priority queue or a set. Before removing each toy, you calculate how much 
enjoyment the kid will have with that toy. You calculate this in log time using a Fenwick tree
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

void update(vector< ll > &BIT, ll idx, ll val){
    while(idx < BIT.size()){
        BIT[idx] += val;
        idx += idx & -idx;
    }
}

ll query(vector< ll > &BIT, ll idx){
    ll prefSum = 0;
    while(idx > 0){
        prefSum += BIT[idx];
        idx -= idx & -idx;
    }
    return prefSum;
}

int main()
{
    boost;
    int t, tc = 0;
    cin >> t;
    while(t--){
        tc++;
        cout << "Case #" << tc << ": ";

        ll n, sum = 0, minRemoved = 0;
		cin >> n;
		vector< ll > E(n),R(n), BIT(n+1,0);
		priority_queue < pair < ll, ll >, vector < pair < ll, ll > >, greater < pair < ll , ll > > > minHeap;
		priority_queue < pair < ll, ll > > maxHeap;

		for(int i = 0; i < n; i++){
			cin >> E[i] >> R[i];
			sum += E[i];
			maxHeap.push({E[i] + R[i], i});
			update(BIT, i+1, E[i]);
		}

		while(!maxHeap.empty() && maxHeap.top().first > sum){
			minHeap.push({maxHeap.top().second, maxHeap.top().first});
			maxHeap.pop();
		}

        // Currently, minHeap contains all the "bad" toys from the first pass
		sum = 0;
		while(!minHeap.empty()){
			pair < ll, ll > p = minHeap.top();
			ll t = query(BIT, n), te;
			if(sum < (te = query(BIT, p.first) + t)){
				sum = te;
				minRemoved = n - minHeap.size() - maxHeap.size();
			}
			minHeap.pop();
			update(BIT, p.first + 1, -E[p.first]);
			t -= E[p.first];
			while(!maxHeap.empty () && maxHeap.top().first > t){
				minHeap.push({maxHeap.top().second, maxHeap.top().first});
				maxHeap.pop();
			}
		}
		if(!maxHeap.empty())
			cout << n - maxHeap.size() << ' ' << "INDEFINITELY" << endl;
		else
			cout << minRemoved << ' ' << sum << endl;
    }
    return 0;
}
