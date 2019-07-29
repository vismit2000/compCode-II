// Knapsack Problem(Bounded)

#include<iostream>
using namespace std;

int knapsack(int wts[],int prices[],int N,int W){
    ///Base Case
    if(N==0||W==0){
        return 0;
    }
    ///Rec Case
    int inc= 0,exc=0;
    if(wts[N-1]<=W){
        inc = prices[N-1] + knapsack(wts,prices,N-1,W- wts[N-1]);
    }
    exc = knapsack(wts,prices,N-1,W);
    return max(inc,exc);
}

//-------------------Normal DP Code--------------------------//

int knapsackDP(int wt[],int price[],int N,int W){
        int dp[100][100] = {0};

        for(int n=0;n<=N;n++){
            for(int w=0;w<=W;w++){

                if(n==0||w==0){
                    dp[n][w] = 0;
                }
                else{
                    int inc=0,exc = 0;
                    if(wt[n-1]<=w){

                        inc = price[n-1] + dp[n-1][w-wt[n-1]];
                    }
                        exc = dp[n-1][w];

                    dp[n][w] = max(inc,exc);
                }
            }
        }
        return dp[N][W];
}

//-------------------End of Normal DP Code--------------------------//



//-------------------Space optimized DP Code--------------------------//

/*
If we observe carefully, we can see that the dp solution with states (i,j)
will depend on state (i-1, j) or (i-1, j-wt[i-1]). In either case the solution
for state (i,j) will lie in the i-1th row of the memoization table. So at
every iteration of the index, we can copy the values of current row and
use only this row for building the solution in next iteration and no
other row will be used. Hence, at any iteration we will be using only a
single row to build the solution for current row. Hence, we can reduce
the space complexity to just O(W).
*/

int knapsackDPSpaceOptimized(int wt[],int price[],int N,int W)
{
        int dp[2][W+1] = {0};
        
        for(int n = 0; n <= N; n++)
        {
            for(int w = 0; w <= W; w++)
            {

                if(n == 0 || w == 0){
                    dp[1][w] = 0;
                }
                else
                {
                    int inc = 0,exc = 0;
                    if(wt[n-1] <= w)
                        inc = price[n-1] + dp[0][w - wt[n-1]];
                    exc = dp[0][w];

                    dp[1][w] = max(inc,exc);
                }
            }
            
            for(int j = 0; j <= W; j++)
                dp[0][j] = dp[1][j];
        }
        return dp[1][W];
}

//-------------------Space optimized DP Code ends--------------------------//

int main(){

    int wts[] = {2, 7, 3, 4};
    int prices[ ] = {5,20,20,10};

    int N = 4;
    int W = 11;
    cout<<knapsack(wts,prices,N,W)<<endl;
    cout<<knapsackDP(wts,prices,N,W)<<endl;
    cout<<knapsackDPSpaceOptimized(wts,prices,N,W)<<endl;
    return 0;
}
