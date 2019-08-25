//Google Kickstart Round-E 2019

/*
Alice and Bob are playing a new virtual reality team game - Street Checkers. The game is set on a very long street divided into tiles which are numbered from 0 to 109(inclusive of both). At the start of the game, Alice and Bob are standing on tile number 0 and are given a random number X in range [L, R] (both ends are inclusive). Alice only jumps to odd numbered tiles, while Bob only jumps to even numbered tiles. If the number on the tile divides X, then the player landing on it has to color it with their favorite color. The game is over after tile X has been colored.

A game is considered interesting by both the players if the absolute difference between the number of tiles painted by each is not greater than 2. Help Alice and Bob find how many numbers in the interval [L, R] could make for an interesting game.

Input
The first line of the input gives the number of test cases, T. T lines follow each containing two integers L and R, the start and end of the interval used to generate the random number X.

Output
For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the count of numbers in interval [L, R] which results in an interesting game for Alice and Bob.

Limits
Time limit: 40 seconds per test set.
Memory limit: 1GB.
1 ≤ T ≤ 100.
0 ≤ R - L ≤ 105.

Test set 1 (Visible)
1 ≤ L ≤ R ≤ 106.

Test set 2 (Hidden)
1 ≤ L ≤ R ≤ 109.

Sample

Input 
 	
Output 
 
2
5 10
102 102

  
Case #1: 5
Case #2: 1

  
For the first sample case, let us look at all the possible number in range [5, 10]:
5 - Alice would paint 2 tiles : {1, 5}, and Bob would not paint any tile. The game would be interesting since the absolute difference is 2.
6 - Alice would paint 2 tiles : {1, 3}, and Bob would paint 2 tiles : {2, 6}. The game would be interesting since the absolute difference is 0.
7 - Alice would paint 2 tiles : {1, 7}, and Bob would not paint any tile. The game would be interesting since the absolute difference is 2.
8 - Alice would paint 1 tile : {1}, and Bob would paint 3 tiles : {2, 4, 8}. The game would be interesting since the absolute difference is 2.
9 - Alice would paint 2 tiles : {1, 3, 9}, and Bob would not paint any tile. The game would not be interesting since the absolute difference is greater than 2.
10 - Alice would paint 2 tiles : {1, 5}, and Bob would paint 2 tiles : {2, 10}. The game would be interesting since the absolute difference is 0.
Thus, the answer for this test case is 5.

In the second sample case, we have only one number 102. Alice would paint 4 tiles : {1, 3, 17, 51} while Bob would paint 4 tiles : {2, 6, 34, 102}. The game would be interesting since the absolute difference is 0.
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int p[1000001];

vector<int> primeSieve()
{
    memset(p, 0, sizeof(p));
    int n = 1000001;
    p[0] = p[1] = 0;
    p[2] = 1;

    for(int i = 3; i <= n; i += 2)
        p[i] = 1;

    for(ll i = 3; i <= n; i += 2)
    {    
        if(p[i])
        {
            for(ll j = i*i; j <= n; j += 2*i)
            {
                p[j] = 0;
            }
        }
    }

    vector<int> primes;
    primes.push_back(2);
    
    for(int i = 3; i < n; i += 2)
    {
        if(p[i] == 1)
        {
            primes.push_back(i);
        }
    }
    return primes;
}

//This function returns a vector of prime factors with their count
vector< pair < int, int > > factorize(int m,vector <int> &primes)
{
    vector< pair < int, int > > factors;

    int i = 0, cnt;
    int p = primes[0];

    while(p*p <= m)
    {
        if(m%p == 0)
        {
            cnt = 0;
            while(m % p == 0)
            {
                cnt++;
                m = m/p;
            }
            factors.push_back({p, cnt});
        }
        i++;
        p = primes[i];
    }

    //One Last Check for a prime
    if(m!=1){
        factors.push_back({m, 1});
    }
    return factors;
}

int main() 
{
    int t;
    cin>>t;

    vector<int> primes = primeSieve();

    for(int q = 1; q <= t; q++)
    {
        cout<<"Case #"<<q<<": ";
        int L, R;
        cin >> L >> R;

        int ans = 0;

        for(int i = L; i <= R; i++)
        {
            vector< pair < int, int > > factors = factorize(i, primes);
            int cnt_odd = 0, cnt_even = 0;

            if(i % 2 != 0)
            {
                cnt_even = 0;
                cnt_odd = 1;
                for(auto group : factors)
                    cnt_odd *= (1 + group.second);
            }
            else
            {
                cnt_even = 1;
                for(auto group : factors)
                    cnt_even *= (1 + group.second);

                cnt_odd = cnt_even/(1 + factors[0].second);

                cnt_even -= cnt_odd;
            }

            if(abs(cnt_even - cnt_odd) <= 2)
                ans++;            
        }

        cout << ans << endl;
    }
    return 0;
}
