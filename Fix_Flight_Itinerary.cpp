/*
PROBLEM: https://binarysearch.com/problems/Fix-Flight-Itinerary

EXPLANATION: We're asked to modify the itinerary to obey a certain rule while minimizing a cost function. Just from that description, 
it's very likely that it should be solved by dynamic programming, and indeed it will.

We will use a two-dimensional DP. The state will be dp[i][port], where i is an index and port is an airport. We'll define dp[i][port] to be the cheapest 
cost to modify the prefix of the itinerary ending at i such that the final airport is exactly port and the rule is followed (i.e. all adjacent edges are 
present in edges).

We can see that dp[0][port] is just the cost of changing itinerary[i] to port. Then, for subsequent indices, dp[i][port] can be computed by taking the least 
cost of dp[i-1][prev] for all edges (prev, port). To be precise: dp[i][port] = min(dp[i-1][prev]) + diff(itinerary[i], port), where diff(a, b) is the cost of 
changing the string a to b.
*/

int diff(const string& s1, const string& s2){
    int count=0;
    for(int i = 0; i < s1.length(); i++)
        if(s1[i] != s2[i])
            count++;
    return count;
}

int solve(vector<string>& itinerary, vector<vector<string>>& edges) {
    map < string, set <string> > graph;
    set < string > nodes;
    for(const auto& edge: edges){
       nodes.insert(edge[0]);
       nodes.insert(edge[1]);
       graph[edge[0]].insert(edge[1]);
    }

    map < string, long > dp;
    string item = itinerary[0];
    for(const auto& node: nodes){
        dp[node] = diff(item, node);
    }

    for(int i = 1; i < itinerary.size(); i++){
        string item = itinerary[i];
        map < string, long> idp;
        for(const auto& node: nodes)
            idp[node] = INT_MAX;
        //loop through graph
        for(const auto& [source,val] : graph)
            for(const auto& dest: val)
                idp[dest] = min( idp[dest], dp[source] + diff(item, dest) );

        dp = idp;
    }

    long minValue = INT_MAX;
    for(const auto& [key, val]: dp)
        minValue = min(minValue, val);

    return minValue;
}
