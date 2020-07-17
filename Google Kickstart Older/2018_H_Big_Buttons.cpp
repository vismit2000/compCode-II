#include <bits/stdc++.h>
using namespace std;

int main() 
{
	int t;
	cin>>t;
	for(int q = 1; q <= t; q++)
	{
	    cout<<"Case #"<<q<<": ";
	    int n, p, len, result, temp, j;
	    string str;
	    cin>>n>>p;
	    set<string> s;
	    vector<int> v;
	    set<string>::iterator it;
	    vector<int>::iterator itr;
	    for(int i = 0; i < p; i++)
	    {
	        cin>>str;
	        s.insert(str);
	    }
	    for(it = s.begin(); it != s.end(); it++)
	    {
	        str = *it;
	        len = str.length();
	        for(j = len-1; j > 0; j--)
	        {
	            if(s.count(str.substr(0,j)))
	                break;
	        }
	        if(j == 0)
	            v.push_back(n-len);
	    }
	    result = pow(2,n);
	    for(itr = v.begin(); itr != v.end(); itr++)
	    {
	        result -= pow(2, *itr);
	    }
	    cout<<result<<endl;
	}
	return 0;
}
