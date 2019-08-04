// https://www.hackerrank.com/challenges/count-triplets-1/problem
/*
You are given an array and you need to find number of tripets of indices (i, j, k) such that the elements at those indices
are in geometric progression for a given common ratio r and i < j < k.
*/

long countTriplets(vector<long> arr, long k) 
{
    map < long, long > left, right;    
    long cnt = 0;

    for(auto it : arr)
        right[it]++;

    for(int i = 0; i < arr.size(); i++)
    {
        right[arr[i]]--;
        if(arr[i] % k == 0)
            cnt += left[arr[i]/k]*right[arr[i]*k];
        left[arr[i]]++;
    }
    return cnt;
}
