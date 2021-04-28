// Program to print all prime factors of a number
#include <bits/stdc++.h>
using namespace std;

int N = 1000000;
vector < int > p;

//PRIME SIEVE & OPTIMISATIONS
vector<int> primeSieve(int n){   
    p.assign(N, 0);
    p[2] = 1;

    // Mark all odd numbers as Prime (Initialisation)
    for(int i = 3; i <= n; i += 2)
        p[i] = 1;

    //Sieve Login to mark non prime numbers as 0
    //1. Optimsation : Iterate only over odd Numbers
    for(int i = 3; i <= n; i += 2){    
        if(p[i]){
            //Mark all the multiples of that number as not prime.
            //2. Optimisation Take a jump of 2i starting from i*i
            for(int j = i*i; j <= n; j += 2*i)
                p[j] = 0;
        }
    }
    vector < int > primes;
    primes.push_back(2);
    
    for(int i = 3; i <= n; i += 2)
        if(p[i] == 1)
            primes.push_back(i);

    return primes;
}

//This function returns a vector of prime factors
vector<int> factorize(long m, vector<int> &primes){
    vector<int> factors;
    int i = 0, p = primes[0];

    while(p*p <= m){
        if(m%p==0){
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
    vector< int > primes = primeSieve(10000);
    long num; cin >> num;

    vector < int > factors = factorize(num, primes);
   
    for(auto f : factors)
        cout << f << " " << endl;
}
