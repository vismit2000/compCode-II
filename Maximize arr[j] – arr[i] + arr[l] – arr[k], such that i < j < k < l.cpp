// https://www.geeksforgeeks.org/maximize-arrj-arri-arrl-arrk-such-that-i-j-k-l/

/*
Maximize arr[j] – arr[i] + arr[l] – arr[k], such that i < j < k < l. 
Find the maximum value of arr[j] – arr[i] + arr[l] – arr[k], such that i < j < k < l

We will use Dynamic Programming to solve this problem. For this we create four 1-Dimensional DP tables.

Let us say there are four DP tables as – table1[], table2[], table3[], table4[]

Then to find the maximum value of arr[l] – arr[k] + arr[j] – arr[i], such that i < j < k < l

table1[] should store the maximum value of arr[l]
table2[] should store the maximum value of arr[l] – arr[k]
table3[] should store the maximum value of arr[l] – arr[k] + arr[j]
table4[] should store the maximum value of arr[l] – arr[k] + arr[j] – arr[i]

Then the maximum value would be present in index 0 of table4 which will be our required answer.
*/

/* A C++ Program to find maximum value of 
arr[l] - arr[k] + arr[j] - arr[i] and i < j < k < l, 
given that the array has atleast 4 elements */

#include <bits/stdc++.h> 
using namespace std; 

// To reprsent minus infinite 
#define MIN -100000000 

// A Dynamic Programing based function to find maximum 
// value of arr[l] - arr[k] + arr[j] - arr[i] is maximum 
// and i < j < k < l 
int findMaxValue(int arr[], int n) 
{ 
	// If the array has less than 4 elements 
	if (n < 4) 
	{ 
		printf("The array should have atlest 4 elements\n"); 
		return MIN; 
	} 

	// We create 4 DP tables 
	int table1[n + 1], table2[n], table3[n - 1], table4[n - 2]; 

	// Initialize all the tables to MIN 
	for (int i=0; i<=n; i++) 
		table1[i] = table2[i] = table3[i] = table4[i] = MIN; 

	// table1[] stores the maximum value of arr[l] 
	for (int i = n - 1; i >= 0; i--) 
		table1[i] = max(table1[i + 1], arr[i]); 

	// table2[] stores the maximum value of arr[l] - arr[k] 
	for (int i = n - 2; i >= 0; i--) 
		table2[i] = max(table2[i + 1], table1[i + 1] - arr[i]); 

	// table3[] stores the maximum value of arr[l] - arr[k] 
	// + arr[j] 
	for (int i = n - 3; i >= 0; i--) 
		table3[i] = max(table3[i + 1], table2[i + 1] + arr[i]); 

	// table4[] stores the maximum value of arr[l] - arr[k] 
	// + arr[j] - arr[i] 
	for (int i = n - 4; i >= 0; i--) 
		table4[i] = max(table4[i + 1], table3[i + 1] - arr[i]); 

	/*for (int i = 0; i < n + 1; i++) 
		cout << table1[i] << " " ; 
	cout << endl; 

	for (int i = 0; i < n; i++) 
		cout << table2[i] << " " ; 
	cout << endl; 

	for (int i = 0; i < n - 1; i++) 
		cout << table3[i] << " " ; 
	cout << endl; 

	for (int i = 0; i < n - 2; i++) 
		cout << table4[i] << " " ; 
	cout << endl; 
	*/

	// maximum value would be present in table4[0] 
	return table4[0]; 
} 

// Driver Program to test above functions 
int main() 
{ 
	int arr[] = { 4, 8, 9, 2, 20 }; 
	int n = sizeof(arr) / sizeof(arr[0]); 

	printf("%d\n", findMaxValue(arr, n)); 

	return 0; 
} 

*/
This problem is simple yet powerful. The problem can be generalized to any expression under the given conditions.
Find the maximum value of arr[j] – 2*arr[i] + 3*arr[l] – 7*arr[k], such that i < j < k < l
*/
