// Problem: https://www.codechef.com/problems/J7

/*
Problem Statement:
Johnny needs to make a rectangular box for his physics class project. He has bought P cm of wire and S cm2 of special paper. 
He would like to use all the wire (for the 12 edges) and paper (for the 6 sides) to make the box.

What is the largest volume of the box that Johnny can make?
*/

/*
Solution Approach:
The volume V = lbh
Now using P = 4(l+b+h) and S = 2(lb+bh+hl)

Convert the above formula of V in terms of only h so that we can differentiate it and then get the value of h for which the 
volume will be maximum or minimum.

The volume will come out to be equal to (S/2-h(P/4-h))*h.

Differentiate the above to get two values of h. One will be for maximum value and other will be for minimum value. 
*/

#include <bits/stdc++.h>
using namespace std;

double p, s;

double calc(double h)
{
    return (h*h*h + (s/2)*h - (p/4)*h*h);
}

int main() 
{
    int t;
    cin>>t;
    while(t--)
    {
        cin >> p >> s;
        double val1 = (p + sqrt(p*p - 24*s))/12;
        double val2 = (p - sqrt(p*p - 24*s))/12;
        
        val1 = calc(val1);
        val2 = calc(val2);
        
        double c = max(val1, val2);
        
        printf("%.2lf\n", c);
    }
    return 0;
}
