#include <bits/stdc++.h>
using namespace std;

int findAns(vector<int> &v)
{
    int len = v.size();
    int murals = (1+v.size())/2;
    int mx = 0, sum = 0;
    for(int j = 0; j < murals; j++)
    {
        sum += v[j];
    }
    mx = sum;
    for(int i = 1; i <= len-murals; i++)
    {
        sum = sum - v[i-1] + v[i+murals-1];
        if(sum > mx)
            mx = sum;
    }
    return mx;
}

int main() 
{
	int t;
	cin>>t;
	for(int q = 1; q <= t; q++)
	{
	    cout<<"Case #"<<q<<": ";
	    int n, temp;
	    string str;
	    cin>>n>>str;
	    vector<int> v;
	    for(int i = 0; i < str.length(); i++)
	    {
	        temp = str[i] - '0';
	        v.push_back(temp);
	    }
	    cout<<findAns(v)<<endl;
	}
	return 0;
}
