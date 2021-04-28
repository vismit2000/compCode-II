// Program to print all prime factors of a number
#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
vector < bool > p;

vector <int> primeSieve(){   
    p.assign(N, true);

    for(int i = 2; i*i < N; i++)  
        if(p[i])
            for(int j = 2*i; j < N; j += i) p[j] = false;
    
    vector < int > primes;
    primes.push_back(2);
    
    for(int i = 3; i < N; i += 2)
        if(p[i] == 1)
            primes.push_back(i);

    return primes;
}

//This function returns a vector of prime factors
vector<int> factorize(long m, vector<int> &primes){
    vector<int> factors;
    int i = 0, p = primes[0];

    while(p*p <= m){
        if(m % p == 0){
            factors.push_back(p);
            while(m % p == 0)
                m = m/p;
        }
        i++;
        p = primes[i];
    }
    //One Last Check for a prime
    if(m != 1) factors.push_back(m);

    return factors;
}

int main(){
    vector< int > primes = primeSieve();
    long num; cin >> num;

    vector < int > factors = factorize(num, primes);
   
    for(auto f : factors)
        cout << f << " " << endl;
}
