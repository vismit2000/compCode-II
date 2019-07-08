//https://medium.com/@harekrishnamahto18/range-sum-and-update-in-arrays-competitive-programming-82ae5039a16f

#include <iostream.h>
using namespace std;

//Updates the BIT[X] +=val
void update(int x,int val,int *b,int n)
{
    b[x] += (val);
    x += (x&-x);
    while(x <= n)
    {
        b[x] += val;
        x += (x&-x);
    }
}
//returns sum[j] - sum[i-1]
int getsum(int i,int j,int *b,int n)
{ 
    i = i-1;
    int sum1 = b[i];
    i -= (i&-i);
    while(i > 0)
    {
        sum1 += b[i];
        i -= (i&-i);
    }

    int sum2=b[j];
    j -= (j&-j);
    while(j > 0)
    {
        sum2 += b[j];
        j -= (j&-j);
    }
    return sum2-sum1;
}

int main()
{ 
    int n;
    cin >> n;
    int *a = new int[n+1];
    a[0] = 0;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    
    int *b = new int[n+1];
    for(int i = 0;i <= n; i++)
        b[i] = 0;
    for(int i = 1; i <= n;i++)
        update(i, a[i], b, n);

    int q;
    cout<<”no of queries:”;
    cin>>q;
    for(int i = 0; i < q; i++)
    {
        int l,r;
        cin >> l >> r;
        cout << getsum(l,r,b,n)<<endl;
    }

    int u;
    cout<<”no of updates:”;
    cin>>u;
    for(int i = 0; i < u; i++)
    {
        int idx,value;
        cout << ”Enter index and val”;
        cin >> idx >> value;
        update(idx,(value-b[idx]),b,n);
    }
    for(int i = 1; i <= n; i++)
        cout << b[i] << endl;   
}
