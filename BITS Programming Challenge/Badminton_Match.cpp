// https://www.hackerrank.com/contests/bppc18/challenges/badminton-match

/*
PROBLEM
There is a class of N students and you, being the captain of the sports team, want to organize a badminton tournament for your class. A game of badminton will be played between
two players.
No student can play more than 1 game in one day. Also every student has a preference order in which he wants to choose his opponents. Each student i has an order in which he 
wants to play a match with corresponding students.
More formally, each student i wants to play with students A[i][1], A[i][2], …. A[i][N-1] in the following order only.
Your task is to calculate the minimum number of days required to complete the tournament without breaking any student’s preference.
If it is impossible to complete the tournament keeping every student’s preference, print -1.
Note: that on a single day multiple games can also be conducted but no student should be playing more than one game a day.

Constraints
3 <= N <= 1000
1 <= A[i][j] <= N

APPROACH
We can remodel the problem as a graph in which the vertices are the matches played between 2 players (i.e: one vertex can represent a match play by player 1 and 2, another can
represent a match played between players 3 and 5, there are n(n-1)/2 such vertices). We candraw an edge from one vertex to another if we know that the match between two players
must be played before a match between two other players. We can find the edges by taking each pair A[i][j], A[i][j+1] as an edge between vertex (i, A[i][j]) directed towards 
(i, A[i][j+1]), indicating that the match between players i and A[i][j] must be played before the match between players i and A[i][j+1].

We can then do a topological sort whilst checking for the presence of cycles. If there is a cycle present, then its impossible as we cannot schedule the games in such a way as
to satisfy the ordering required. If there is no cycle, we can greedily select all the nodes with in-degree = 0 and remove them, while simultaneously updating the nodes to 
which they are directed towards and decreasing their in-degree by 1. The number of times we have to do this is our answer.

#include <bits/stdc++.h>
using namespace std;

const int M = 1e6;
set<int> adj[M];
int nd, indeg[M];
bool vis[M];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n;
	cin >> n;
	map<pair<int, int>, int > mp;
	int mat[n][n - 1];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			cin >> mat[i][j];
			mat[i][j]--;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 2; j++) {
			pair<int, int> p1 = {i, mat[i][j]}, p2 = {i, mat[i][j + 1]};
			if (p1.first > p1.second)
				swap(p1.first, p1.second);
			if (p2.first > p2.second)
				swap(p2.first, p2.second);
			if (mp.find(p1) == mp.end())
				mp[p1] = nd++;
			if (mp.find(p2) == mp.end())
				mp[p2] = nd++;
			if (adj[mp[p1]].find(mp[p2]) == adj[mp[p1]].end()) {
				adj[mp[p1]].insert(mp[p2]);
				indeg[mp[p2]]++;
			}
		}
	}
	queue<pair<int, int> > q;
	for (int i = 0; i < nd; i++) {
		if (indeg[i] == 0) {
			vis[i] = true;
			q.push({i, 1});
		}
	}
	int ans = -1;
	while (!q.empty()) {
		int v = q.front().first, d = q.front().second;
		q.pop();
		for (auto nbr : adj[v])
			indeg[nbr]--;
		ans = d;
		for (auto nbr : adj[v]) {
			if (!vis[nbr] && indeg[nbr] == 0) {
				vis[nbr] = true;
				q.push({nbr, d + 1});
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (!vis[i])
			ans = -1;
	}
	cout << ans;
	return 0;
}
