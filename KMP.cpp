//just a comment
#include <bits/stdc++.h>
using namespace std;

#define MAX 100005
int reset[MAX];

void KMPpreprocess(string pat) 
{
	int i = 0, j = -1;
	reset[0] = -1;
	while(i < pat.size()) 
    {
		// Check for resetting
		while(j >= 0 and pat[i]!=pat[j]) 
			j = reset[j];
		i++;
		j++;
		reset[i] = j;
	}
}

void KMPsearch(string str, string pat) 
{
	KMPpreprocess(pat);
	int i = 0, j = 0;
	while(i < str.size()) 
    {
		while(j >= 0 and str[i] != pat[j])
			j = reset[j];
		i++;
		j++;
		if(j == pat.size()) 
        {
			cout<<"Pattern is found at "<<i-j<<endl;
			j = reset[j];
		}
	}
}

int main()
{
	for(int i = 0; i < MAX; i++) {
		reset[i] = -1;
	}
	string str, pat;
	cin>>str>>pat;
	KMPsearch(str, pat);
	return 0;
}
