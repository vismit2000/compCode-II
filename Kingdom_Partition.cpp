// https://hack.codingblocks.com/app/contests/1338/983/problem

/*PROBLEM
Louise is the king of Warland . Warland is a special kingdom somewhere beyond seven seas . It consist of N provinces and N-1 
roads connecting these provinces . Roads are such that every two provinces are connected directly or indirectly through a 
road. The provinces are numbered as 1,2,3 ……. N. Louise has two sons Keneth and Benjamin,both his sons possess the potential 
to become the heir of the throne .Louise was in dilemma so he asked his ministers to solve this problem .One of the ministers 
came up with an idea, he suggested to distribute some of the provinces to Keneth and some to Benjamin. Louise wants to stop 
his sons from fighting ,so he will not allot them neighboring provinces (Neighboring provinces are those directly connected 
by roads). Louise will keep one province for himself.
He will allot them provinces in such a way that his province lies in the path on every two provinces X and Y such that X 
belongs to Keneth and Y belongs to Benjamin .

Let “a” be the number of provinces given to Keneth and “b” be the number of provinces given to Benjamin .Then sum of a and b 
should be N-1 as the king will have 1 province and a>0 & b>0. Tell number of unique pairs (a,b) in which the King can 
partition his Kingdom .

Input Format
First line of the input contains a single integer representing the number of provinces N in the kingdom. Each of the next N-1 
lines contains two integers A and B ,representing that province A and province B are connected via a direct road.

Constraints
3<=N<=5000
1<=A,B<=N

Output Format
Print number of unique pairs (a,b) ,representing provinces of Keneth and Benjamin .(a,b) and (b,a) are considered two unique 
pairs .

Sample Input
6 
1 2
1 3
2 4
4 6
3 5
Sample Output
4
Explanation
Max value of a + b is 5. All possible ways to distribute are : {6} belong to Keneth and {2,1,3,5} belong to Benjamin which 
gives (1,4) {6,4} belong to Keneth and {1,3,5} belong to Benjamin which gives (2,3) {6,4,2} belong to Keneth and {3,5} belong 
to Benjamin which gives (3,2) {6,4,2,1} belong to Keneth and {5} belong to Benjamin which gives (1,4)

Suppose if we distribute like { 6,4,3} for Keneth and {2,5} for Benjamin . We can see that 3 and 5 are neighbors in our 
kingdom hence this type of allotment will not work due to conflict between Keneth and Benjamin. Similarly 2 and 4 are 
neighbors hence this will also not work .
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define boost ios_base ::sync_with_stdio(0); cin.tie(0);

int n;                      // global declation of n so as to access easily
vector < int > tree[5005];  // for storing tree in the form of adjacency list
set < int > ans; 

void subsetsum(vector < int > &child_size, vector < int > &subsets)
{
   // finding all possible subsets from child_sizes to partion it into two parts
    int x = child_size.size();

    vector < vector < int > > dp(x+1, vector < int > (n+1, 0));

    dp[0][0] = 1;
    for(int i = 1; i <= x; i++){
        for(int j = 0; j < n; j++){
            dp[i][j] = dp[i-1][j]; // leave ith element 
            if(j >= child_size[i-1])  // take the ith element if j>child_size[i-1]
             dp[i][j] = dp[i][j] || dp[i-1][j-child_size[i-1]];
        }
    }
    // removing the cases where each subtree is picked in one partion  
    // Also removing case where no subtree is picked  
    // Storing all possible subset sums in subsets vector

    for(int i = 1; i <= n-2; i++){
        if(dp[x][i] == 1){
        subsets.push_back(i);
      }
    }
}

int dfs(int node, int parent){
    vector < int > child_size;
    vector < int > subsets;
    int is_leaf_node = 1;

    for(auto i : tree[node]){
        if(i != parent){            // skip if i is parent of node 
            int x = dfs(i, node);
            is_leaf_node = 0;
            child_size.push_back(x);
        }
    }

    int sizesum = 0;
    for(auto i : child_size){
        sizesum += i;
    }

    if(is_leaf_node)    // if node is a leaf node
        return 1; 
    child_size.push_back(n-1-sizesum); // inserting size of remaining tree as a subtree
    subsetsum(child_size, subsets);
    for(int i = 0; i < subsets.size(); i++){
        ans.insert(subsets[i]);
    }
    return sizesum + 1;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    boost;
    cin >> n;

    for(int i = 0; i < n-1; i++)
    {
        int x, y;
        cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    dfs(1,0);  // traversing tree using depth first search

    cout << ans.size() << endl;
}

