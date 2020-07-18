#include <bits/stdc++.h>
using namespace std;

void printmatrix(float A[][4]);
void RowReduce(float A[][4]);

int main()
{
    float A[3][4] = {{5, -6, -7,   7},
                     {3, -2,  5, -17},
                     {2,  4, -3,  29}}; //answer should be {2, 4, -3}

    printmatrix(A);
    RowReduce(A);
}

void printmatrix(float A[][4]) // Outputs the matrix
{
    int p=3;
    int q=4;

    for (int i=0; i<p; i++) 
    {
        for (int j=0; j<q; j++) 
        {
            cout << setw(7) << setprecision(4) << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void RowReduce(float A[][4])
{
    const int nrows = 3; // number of rows
    const int ncols = 4; // number of columns

    int lead = 0; 

    while (lead < nrows) 
    {
        float d, m;
        for (int r = 0; r < nrows; r++) 
        { // for each row calculate divisor and multiplier 
            d = A[lead][lead];
            m = A[r][lead] / A[lead][lead];

            for (int c = 0; c < ncols; c++) 
            { // for each column ...
                if (r == lead)
                    A[r][c] /= d;               // make pivot = 1
                else
                    A[r][c] -= A[lead][c] * m;  // make other = 0
            }
        }

        lead++;
        printmatrix(A);
    }
}
