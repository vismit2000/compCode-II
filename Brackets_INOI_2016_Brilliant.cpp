// https://brilliant.org/problems/inoi-2016-brackets/#!/solution-comments/

#include <iostream>
#include <algorithm>

int V[701], B[701], cache[701][701], N, k;

int coolSum(int start, int end){
    //std::cout << "coolSum Call" << start << " " << end << std::endl;
    if (cache[start][end] != -123456789)
       return cache[start][end];
    if (start >= end){
        cache[start][end] = 0;
        return cache[start][end];
    }
    if ((start == 0) || (end == 0)){
        cache[start][end] = 0;
        return cache[start][end];
    }
    if (B[end] <= k){
        cache[start][end] = coolSum(start,end-1);   //An open bracket at the end contributes nothing
        return cache[start][end];
    }

    int maxTemp = -999999999;
    if (B[end] > k){
        for (int iii=start; iii < end; iii++)
           if (B[iii]==B[end]-k)
              maxTemp = std::max(maxTemp, V[iii]+V[end]+coolSum(iii+1,end-1)+coolSum(start,iii-1));
        maxTemp = std::max(maxTemp,coolSum(start, end-1));
        cache[start][end] = maxTemp;
        return maxTemp;
    }
}

int main(){

    std::cin >> N >> k;
    for (int iii=1; iii<=N; iii++)
       std::cin >> V[iii];
    for (int iii=1; iii<=N; iii++)
       std::cin >> B[iii];

    for (int iii=0; iii< 701; iii++)
       for (int jjj=0; jjj < 701; jjj++)
          cache[iii][jjj] = -123456789;

    std::cout << coolSum(1,N);


    return 0;
}
