#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> iPair;

int main() 
{
	int t;
	cin>>t;
	for(int q = 1; q <= t; q++)
	{
	    cout<<"Case #"<<q<<": ";
	    int n, m, E, sr, sc, tr, tc, node, src, dest, addNode;
	    cin>>n>>m>>E>>sr>>sc>>tr>>tc;
	    int prod = m*n;
	    int arr[n][m];
	    vector<iPair> adj[prod];
	    for(int i = 0; i < n; i++)
	    {
	        for(int j = 0; j < m; j++)
	        {
	            cin>>arr[i][j];
	            arr[i][j] = (-1)*arr[i][j];
	        }
	    }
	    for(int i = 0; i < n; i++)
	    {
	        for(int j = 0; j < m; j++)
	        {
	            node = i*m + j;
	            
	            addNode = i*m + j + 1;
	            if(j != m-1 && arr[i][j+1] != 100000 && arr[i][j] != 100000)
	                adj[node].push_back({arr[i][j+1], addNode});
	                
	            addNode = i*m + j - 1;
	            if(j != 0 && arr[i][j-1] != 100000 && arr[i][j] != 100000)
	                adj[node].push_back({arr[i][j-1], addNode});
	             
	             addNode = (i+1)*m + j;
	            if(i != n-1 && arr[i+1][j] != 100000 && arr[i][j] != 100000)
	                adj[node].push_back({arr[i+1][j], addNode});
	             
	             addNode = (i-1)*m + j;
	            if(i != 0 && arr[i-1][j] != 100000 && arr[i][j] != 100000)
	                adj[node].push_back({arr[i-1][j], addNode});
	             
	        }
        }
	    src = m*(sr-1) + (sc-1);
	    dest = m*(tr-1) + (tc-1);
	    priority_queue < iPair, vector <iPair>, greater<iPair> > pq;
	    vector <int> dist(prod, INT_MAX);
	    pq.push(make_pair(0,src));
	    dist[src] = 0;
	    
	    while(!pq.empty())
	    {
	        int u = pq.top().second;
	        pq.pop();
	        vector <iPair>:: iterator it;
	        for(it = adj[u].begin(); it != adj[u].end(); it++)
	        {
	            int v = it->second;
	            int weight = it->first;
	            if(dist[v] > (dist[u] + weight))
	            {
	                dist[v] = (dist[u] + weight);
	                pq.push(make_pair(dist[v], v));
	            }
	        }
	    }
	    E = E - dist[dest];
	    if(E < 0)
	        cout<<"-1"<<endl;
	    else 
	       cout<<E<<endl;
	}
	return 0;
}
