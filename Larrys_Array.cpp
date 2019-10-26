//Problem: https://www.hackerrank.com/challenges/larrys-array/problem

// 15 tile invariant: https://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html

// Editorial: https://www.hackerrank.com/challenges/larrys-array/editorial

#include <bits/stdc++.h>
using namespace std;

string larrysArray(vector<int> A) 
{
    int n = A.size();

    int cnt = 0;

    for(int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(A[i] > A[j])
                cnt++;
        }
    }
    if(cnt % 2 == 0)
        return "YES";
    return "NO";

}

int main()
{
    int t;
    cin >> t;

    while(t--)
    {
        int n;
        cin >> n;

        vector <int> A(n);

        for(int i = 0; i < n; i++)
            cin >> A[i];
            
        cout << larrysArray(A) << endl;
    }
    return 0;
}
