#include <iostream>
#include <string>
#include <math.h>
#include <bits/stdc++.h>
#include<bits/stdc++.h>
#include<vector>
#include<map>
#include<iomanip>
​
using namespace std;
​
typedef long long int ll;
typedef unsigned long long int ull;
​
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);
#define m_p make_pair
#define mod 1000000007
#define pi 3.14159265358979323846
#define mp make_pair
#define ff first
#define ss second
#define sol(i,a,b) for(ll i=a;i<b;i++)
#define rsol(i,a,b) for(ll i=a;i>b;i--)
#define rep(i,n) sol(i,0,n)
#define sp cout<<endl
#define pb push_back
#define mx 200010
#define mxl 2000100100
#define ll long long int
#define vi vector<ll>
/* Factorise an array of numbers
rep(i,n)
{
    cin >> num;
    arr.push_back(num);
    factors[i].clear();
    for(int j=2;j*j<=num;j++)
        while(num%j==0)
        {
            factors[i][j]++;
            num/=j;
        }
    if(num!=1)
        factors[i][num]++;
}
*/
/*  SUM OF SUBSETS
rep(mask,1<<n)
    SOS[i] = value[mask];
rep(i,n)
    rep(mask,1<<n)
        if(mask & (1<<i))
            SOS[mask] += SOS[mask^(1<<i)];
*/
ll maximum(ll a,ll b){
	return (a>b)?a:b;
}
ll minimum(ll a,ll b){
	return (a<b)?a:b;
}
ll sigmaN(ll i)
{
	return (i*(i+1))/2;
}
long long fast_pow(long long x, long long y)
{
    if (y == 1)
        return x%mod;
    if (y == 0)
        return 1;
    long long res = fast_pow(x, y/2);
    if (y%2)
        return (((res*res)%mod)*x)%mod;
    return res*res%mod;
}
ll modInverse(ll a) 
{
    return fast_pow(a,mod-2);
} 
int main()
{
    boost;
}
