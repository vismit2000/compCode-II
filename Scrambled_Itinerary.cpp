// https://code.google.com/codejam/contest/6214486/dashboard#s=p2

#include <bits/stdc++.h>
using namespace std;

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int t;
	cin >> t;
	
	for(int q = 1; q <= t; q++)
	{
	    cout << "Case #" << q << ": ";
	    
	    int n;
	    cin >> n;
	    
	    map < string, string > mp;
	    
	    vector < string > src(n), dest(n);
	    
	    for(int i = 0; i < n; i++)
	    {
	        cin >> src[i];
	        cin >> dest[i];
	        
	        mp[src[i]] = dest[i];
	    }
	    
	    //Find start point;
	    string startPoint;
	    
	    map < string, int > cnt;
	    
	    for(int i = 0; i < n; i++)
	        cnt[src[i]]++;
	       
	    for(int i = 0; i < n; i++)
	    {
	        if(cnt[dest[i]] == 1)
	            cnt[dest[i]]++;
	    }
	    
	    for(auto i : cnt)
	    {
	        if(i.second == 1)
	            startPoint = i.first;
	    }
	    
	    string s = startPoint, d = mp[startPoint];
	    
	    while(n)
	    {
	        cout << s << "-" << d << " ";
	        s = d;
	        d = mp[s];
	        n--;
	    }
	    cout << endl;
	}
	return 0;
}
