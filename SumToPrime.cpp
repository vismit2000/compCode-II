#include <bits/stdc++.h>
using namespace std;

int main() 
{
    long N = 1000005;
	unsigned long long int p[N] = {0};
	
	p[2] = 1;
	
	//Initialize: Mark all odds as prime
	for(long i = 3; i < N; i += 2)
	    p[i] = 1;
	    
    //Sieve
    for(long i = 3; i < N; i += 2)
    {
        if(p[i])
        {
            for(long j = i*i; j < N; j += 2*i)
                p[j] = 0;
        }
    }
    
    
    for(long i = 1; i < 1000004; i++)
    {
        if(p[i])
            p[i] = p[i-1] + i;
        else
            p[i] = p[i-1];
    }
    
    int t;
    cin >> t;
    
    while(t--)
    {
        int n;
        cin >> n;
        cout << p[n] << endl;
    }
    
	return 0;
}
