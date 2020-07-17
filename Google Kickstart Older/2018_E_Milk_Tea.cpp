#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

LL strDiff(string a, string b) {
	LL cnt = 0;
	for(int i = 0; i < a.length(); i++)
	{
	    if(a[i] != b[i])	
	        cnt++;
	}
	return cnt;
}

int main() 
{
	int t;
	cin>>t;
	for(int q = 1; q <= t; q++) 
	{
		cout << "Case #" << q << ": ";
		int n,m,p;
		cin>>n>>m>>p;
		string demands[n];
		set <string> forbidden;
		LL ones[p] = {0}, zeros[p] = {0};
		for(int i = 0; i < n; i++) 
		{
			cin >> demands[i];
			for(int j = 0; j < p; j++)
			{
				if(demands[i][j] == '1')	
				    ones[j]++;
				else	
				    zeros[j]++;
			}
		}
		for(int i = 0; i < m; i++)
		{
			string tmp; 
			cin >> tmp;
			forbidden.insert(tmp);
		}
	
		string opt(p, '#');
		for(int i = 0; i < p; i++)
		{
			if(ones[i] >= zeros[i])	
			    opt[i] = '1';
			else	
			    opt[i] = '0';
		}
		priority_queue< pair<LL, string>, vector< pair<LL, string> >, greater< pair<LL, string> > > pq;
		pq.push(make_pair(0, opt));
		map<string, bool> visited;
		while(!pq.empty()) 
		{
			string curr = pq.top().second;
			LL dist = pq.top().first;
			pq.pop();
			visited[curr] = true;
			if(forbidden.find(curr) == forbidden.end()) 
			{
				opt = curr;
				break;
			}
			for(int i = 0; i < p; i++)
			{
				if(curr[i] == '0') 
				{
					curr[i] = '1';
					if(!visited[curr])	
					    pq.push(make_pair(dist + zeros[i] - ones[i], curr));
					curr[i] = '0';
				}
				else if(curr[i] == '1') 
				{
					curr[i] = '0';
					if(!visited[curr])	
					    pq.push(make_pair(dist + ones[i] - zeros[i], curr));
					curr[i] = '1';
				}
			}
		}


		LL minComp = 0;
		for(int i = 0; i < n; i++)	
		    minComp += strDiff(demands[i], opt);
		cout << minComp << endl;
	}
}
