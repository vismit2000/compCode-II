https://www.algoexpert.io/questions/Max%20Profit%20With%20K%20Transactions

You are given an array of integers representing the prices of a single stock on various days (each index in the array represents a different day). You are also
given an integer k, which represents the number of transactions you are allowed to make. One transaction consists of buying the stock on a given day and
selling it on another, later day. Write a function that returns the maximum prot that you can make buying and selling the stock, given k transactions. Note
that you can only hold 1 share of the stock at a time; in other words, you cannot buy more than 1 share of the stock on any given day, and you cannot buy a
share of the stock if you are still holding another share.
Sample input: [5, 11, 3, 50, 60, 90], 2
Sample output: 93

#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f

int maxProfitWithKTransactions(vector<int> prices, int k) 
{
		if(prices.size() == 0)
				return 0;
		
		vector < vector < int > > profits(k+1, vector < int > (prices.size(), 0));
	
		for(int i = 1; i <= k; i++)
		{
				int mx = -INF;
				for(int j = 1; j < prices.size(); j++)
				{
						mx = max(mx, profits[i-1][j-1] - prices[j-1]);
						profits[i][j] = max(profits[i][j-1], mx + prices[j]);
				}
		}
		return profits[k][prices.size()-1];
}
