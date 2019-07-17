// Python code

/*
def square(x):
    return int(x) * int(x)

def happy(number):
    return sum(map(square, list(str(number))))

def is_happy(n):
    return (n == 1 or n > 4 and is_happy(happy(n)))

n = int(input())

print(is_happy(n))
*/

//If we treat every number as a node and replacement by square sum digit as a link, then this problem is same as finding a loop in a linklist.
//We will keep two number slow and fast both initialize from given number, slow is replaced one step at a time and fast is replaced two steps at a time. If they meet at 1, then the given number is Happy Number otherwise not.

#include <bits/stdc++.h> 
using namespace std; 
  
// Utility method to return sum of square of 
// digit of n 
int numSquareSum(int n) 
{ 
    int squareSum = 0; 
    while (n) 
    { 
        squareSum += (n % 10) * (n % 10); 
        n /= 10; 
    } 
    return squareSum; 
} 
  
//    method return true if n is Happy number 
bool isHappynumber(int n) 
{ 
    int slow, fast; 
  
    //    initialize slow and fast by n 
    slow = fast = n; 
    do
    { 
        //    move slow number by one iteration 
        slow = numSquareSum(slow); 
  
        //    move fast number by two iteration 
        fast = numSquareSum(numSquareSum(fast)); 
  
    } 
    while (slow != fast); 
  
    //    if both number meet at 1, then return true 
    return (slow == 1); 
} 
  
//    Driver code to test above methods 
int main() 
{ 
    int n = 13; 
    if (isHappynumber(n)) 
        cout << n << " is a Happy number\n"; 
    else
        cout << n << " is not a Happy number\n"; 
} 

//Source : GfG
