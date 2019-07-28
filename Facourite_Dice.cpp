// https://www.spoj.com/problems/FAVDICE/

#include <bits/stdc++.h>
using namespace std;

int main() 
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		double res = 0.0;
		
		for(double i = 1; i <= n; i++)
			res += (1/i);
		res *= n;
		printf("%.2f\n", res);
	}
	return 0;
}
