This problem can easily solved by binary-search by defining the predicate: "Given N, how many numbers upto N are divisible by A or B or C"

The predicate can be evaluated by inclusion-exclusion principle:

	No. of numbers upto N divisible by A = N/A;
	No. of numbers upto N divisible by B = N/B;
	No. of numbers upto N divisible by C = N/C;
	
	No. of numbers upto N divisible by both A and B = N / lcm(A, B);
	No. of numbers upto N divisible by both B and C = N / lcm(B, C);
	No. of numbers upto N divisible by both A and C = N / lcm(A, C);
	
	No. of numbers upto N divisible by all A, B and C = N / lcm(A, B, C);
	
Furthermore LCM(A, B) can be computed as LCM(A, B) = (A*B) / GCD(A, B)

For problem solving technique using binary search predicate, refer to following awesome article:
	https://www.topcoder.com/community/competitive-programming/tutorials/binary-search

```
typedef long long ll;
class Solution {
public:
    int nthUglyNumber(int n, int a, int b, int c) 
    {
        ll N = (ll)n, A = ll(a), B = ll(b), C = ll(c);
        ll lo = 1, hi = 2000000000, mid, ans;
        
        while(lo <= hi)
        {
            mid = (lo+hi)/2;
            ll cnt = 0;
            cnt += mid/A;
            cnt += mid/B;
            cnt += mid/C;
            cnt -= (mid*__gcd(A, B))/(A*B);
            cnt -= (mid*__gcd(C, B))/(B*C);
            cnt -= (mid*__gcd(A, C))/(A*C);
            cnt += (mid*__gcd(A, B)*__gcd(C, ((A*B)/__gcd(A, B))))/(A*B*C);
            
            if(cnt == N)
            {
                ans = mid;
                hi = hi-1;
            }
            if(cnt < N)
                lo = mid+1;
            else
                hi = mid-1;
        }
        return ans;
    }
};
```
