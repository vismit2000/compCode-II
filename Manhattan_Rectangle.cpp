// https://www.codechef.com/FEB19B/problems/MANRECT

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        long xl, xu, yl, yu, R1, R2, R3, R4, R5, R6, R7;

        //first
        cout << "Q 0 0" << endl;
        cin >> R1; 

        //R1 = xl + yl;

        //second
        cout << "Q 1000000000 0" << endl;
        cin >> R2;

        //R2 = 1000000000 - xu + yl;

        long midx = (1000000000 + R1 - R2)/2;

        //third
        cout << "Q " << midx << " 0" << endl;
        cin >> R3;

        yl = R3;
        xl = R1 - yl;
        xu = 1000000000 + yl - R2;

        //fourth
        cout << "Q 0 1000000000" << endl;
        cin >> R4;

        //R4 = 1000000000 - yu + xl

        yu = 1000000000 + xl - R4;

        cout << "A "<< xl << " " << yl << " " << xu << " " << yu << endl;

        int flag;
        cin >> flag;
        if(flag < 0)
            break;
    }
    return 0;
}
