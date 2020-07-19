/*
There is a magic tree with N nodes in it. On each node ,there is an integer written on it. Select exactly two non intersecting subtrees of this tree such that 
the sum of values on all nodes of both the subtrees is maximum.

You cannot select only one subtree . You must select two subtrees or none at all .
(Two subtrees are non intersecting if they do not have any node in common.)

Note: The nodes can have negative values .If total sum is negative , Popeye will not get any coins .

Input Format:
First line of the input contains single integer representing the number of nodes N in the tree . Second line contains N integers a1,a2,a3…..an representing the 
value on each node . Next N-1 lines contains two integers A and B ,representing that node A and node B are connected.
*/

#include<bits/stdc++.h>
using namespace std;

const int N = 100005;
vector<int> values(N), subtree_sum(N), max_subtree(N);
vector<vector<int>> graph(N), directed_tree(N);

int dfs1(int a, int parent){
    int t = 0;
    for(auto curnode : graph[a]){
        if(curnode != parent){
            directed_tree[a].push_back(curnode);
            t += dfs1(curnode, a);
        }
    }
    //sum of values on nodes in subtree a
    return subtree_sum[a] = t + values[a];
}

int dfs2(int a, int parent){
    int t = subtree_sum[a];
    for(auto curnode : graph[a]){
        if(curnode != parent)
            t = max(t, dfs2(curnode, a));
    }
    
    return max_subtree[a] = t;
} 

int main(){
    int n;
    cin>>n;
    
    for(int i = 1; i <= n; i++) cin >> values[i];
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    //dfs to find subtree sum at each node and to get directed tree from parent to child
    dfs1(1,0);   
    
    //dfs to find maximum sum subtree in a particular subtree
    dfs2(1,0);
    
    int ans=0;
    for(auto a : directed_tree){
        vector < int > all_values;
        for(auto b : a)
            all_values.push_back(max_subtree[b]);

        sort(all_values.rbegin(), all_values.rend());
        
        if(all_values.size() > 1)
            ans=max(ans,all_values[0]+all_values[1]);         
    }

    cout << ans << endl;
}
