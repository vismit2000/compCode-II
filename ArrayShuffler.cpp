//Shuffle Integers
//Suppose you have an array of 2*n integers arranged as:
//
//  a1 a2 a3 ..... an b1 b3 b3 ..... bn
//  
//Rearrange the array without using extra space as:
//
//  a1 b1 a2 b2 a3 b3 ........... an bn
  
#include <bits/stdc++.h>
using namespace std;

void shuffleArrayRecursive(int left, int right, int arr[]) { 
	if (right - left == 1) 
		return; 
	int middle = (left + right) / 2;  
	int mmiddle= (left + middle) / 2; 
  int temp = middle + 1;

	for (int i = mmiddle + 1; i <= middle; i++) 
		swap(arr[i], arr[temp++]); 

	shuffleArrayRecursive(left, middle, arr); 
	shuffleArrayRecursive(middle + 1, right, arr); 
} 

void shuffler(int a[], int n){
	shuffleArrayRecursive(0, n-1, a);
}
