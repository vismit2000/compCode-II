// https://leetcode.com/problems/super-ugly-number/

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) 
    {
        int k = primes.size();
        if(n <= 0)
            return 0;
        if(n == 1)
            return 1;
        
        vector <int> pointers(k, 0), v(n);
        v[0] = 1;
        
        for(int i = 1; i < n; i++)
        {
            v[i] = INT_MAX;
            for(int j = 0; j < k; j++)
                v[i] = min(v[i], v[pointers[j]] * primes[j]);
            
            for(int j = 0; j < k; j++)
            {
                if(v[i] == v[pointers[j]] * primes[j])
                    pointers[j]++;
            }
        }
        
        return v[n-1];
    }
};
