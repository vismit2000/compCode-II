// Problem : https://www.codechef.com/LTIME69B/problems/ROLLBAR
// Tutorial : http://olympiad.cs.uct.ac.za/old/saco2007/day1_2007_solutions.pdf - Problem 5

//My solution - TLE : Don't know why ?? :(

#include<bits/stdc++.h>
using namespace std;

// State :  0 -> U,  1 -> N,  2 -> W

int N, M;
bool visited[1005][1005][3];

bool isValid(int x, int y, int state, vector < string > v)
{
    if(x < 0 || x >= N || y < 0 || y >= M)
        return false;
    if(v[x][y] == '0')
        return false;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--)
    {
        int x, y;
        cin >> N >> M >> x >> y;
        x--, y--;
        vector < string > v(N);
        for(int i = 0; i < N; i++)
            cin >> v[i];

        vector < vector < int > > matrix(N, vector < int> (M, -1));

        queue < tuple < int, int, int, int > > q;       //tuple(x, y, state, dist)
        tuple < int, int, int, int > placeholder;
        int pos_x, pos_y, state, dist;
        q.push(make_tuple(x, y, 0, 0));

        memset(visited, false, sizeof(visited));

        visited[x][y][0] = true;

        while(!q.empty())
        {
            placeholder = q.front();
            q.pop();
            pos_x = get<0>(placeholder);
            pos_y = get<1>(placeholder);
            state = get<2>(placeholder);
            dist  = get<3>(placeholder);

            if(state == 0)
                matrix[pos_x][pos_y] = dist;
            
            if(state == 0)
            {
                // Neighbouring states : (x-2,y, N), (x+1, y, N), (x, y+1, E), (x, y-2, E)

                if(isValid(pos_x-2, pos_y, 1, v) && isValid(pos_x-1, pos_y, 1, v) && !visited[pos_x-2][pos_y][1])
                {
                    visited[pos_x-2][pos_y][1] = true;
                    q.push(make_tuple(pos_x-2, pos_y, 1, dist + 1));
                }
                if(isValid(pos_x+1, pos_y, 1, v) && isValid(pos_x+2, pos_y, 1, v) && !visited[pos_x+1][pos_y][1])
                {
                    visited[pos_x+1][pos_y][1] = true;
                    q.push(make_tuple(pos_x+1, pos_y, 1, dist + 1));
                }
                if(isValid(pos_x, pos_y+1, 2, v) && isValid(pos_x, pos_y+2, 2, v) && !visited[pos_x][pos_y+1][2])
                {
                    visited[pos_x][pos_y+1][2] = true;
                    q.push(make_tuple(pos_x, pos_y+1, 2, dist + 1));
                }
                if(isValid(pos_x, pos_y-2, 2, v) && isValid(pos_x, pos_y-1, 2, v) && !visited[pos_x][pos_y-2][2])
                {
                    visited[pos_x][pos_y-2][2] = true;
                    q.push(make_tuple(pos_x, pos_y-2, 2, dist + 1));
                }
            }

            else if(state == 1)
            {
                // Neighbouring states : (x,y+1, N), (x, y-1, N), (x-1, y, U), (x+2, y, U)

                if(isValid(pos_x, pos_y+1, 1, v) && isValid(pos_x+1, pos_y+1, 1, v) && !visited[pos_x][pos_y+1][1])
                {
                    visited[pos_x][pos_y+1][1] = true;
                    q.push(make_tuple(pos_x, pos_y+1, 1, dist + 1));
                }
                if(isValid(pos_x, pos_y-1, 1, v) && isValid(pos_x+1, pos_y-1, 1, v) && !visited[pos_x][pos_y-1][1])
                {
                    visited[pos_x][pos_y-1][1] = true;
                    q.push(make_tuple(pos_x, pos_y-1, 1, dist + 1));
                }
                if(isValid(pos_x-1, pos_y, 0, v) && !visited[pos_x-1][pos_y][0])
                {
                    visited[pos_x-1][pos_y][0] = true;
                    q.push(make_tuple(pos_x-1, pos_y, 0, dist + 1));
                }
                if(isValid(pos_x+2, pos_y, 0, v) && !visited[pos_x+2][pos_y][0])
                {
                    visited[pos_x+2][pos_y][0] = true;
                    q.push(make_tuple(pos_x+2, pos_y, 0, dist + 1));
                }
            }

            else if(state == 2)
            {
                // Neighbouring states : (x-1,y, E), (x+1, y, E), (x, y-1, U), (x, y+2, U)

                if(isValid(pos_x-1, pos_y, 2, v) && isValid(pos_x-1, pos_y+1, 2, v) && !visited[pos_x-1][pos_y][2])
                {
                    visited[pos_x-1][pos_y][2] = true;
                    q.push(make_tuple(pos_x-1, pos_y, 2, dist + 1));
                }
                if(isValid(pos_x+1, pos_y, 2, v) && isValid(pos_x+1, pos_y+1, 2, v) && !visited[pos_x+1][pos_y][2])
                {
                    visited[pos_x+1][pos_y][2] = true;
                    q.push(make_tuple(pos_x+1, pos_y, 2, dist + 1));
                }
                if(isValid(pos_x, pos_y-1, 0, v) && !visited[pos_x][pos_y-1][0])
                {
                    visited[pos_x][pos_y-1][0] = true;
                    q.push(make_tuple(pos_x, pos_y-1, 0, dist + 1));
                }
                if(isValid(pos_x, pos_y+2, 0, v) && !visited[pos_x][pos_y+2][0])
                {
                    visited[pos_x][pos_y+2][0] = true;
                    q.push(make_tuple(pos_x, pos_y+2, 0, dist + 1));
                }
            }                        
        }

        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < M; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}


// Accepted solution

#include <bits/stdc++.h>
 
using namespace std;
 
const int MX = (1009);
 
int T , n , m;
string valid[MX];
int sx , sy;
int bfs[MX][MX][3];
 
queue < pair < pair < int , int > , int > >  Q;
 
 
bool check(int x , int y){
    if(x < 1 || x > n || y < 1 || y > m) return 0;
    if(valid[x][y] == '0') return 0;
    return 1;
}
 
void add(int nx , int ny , int nstate , int ncost){
    if(bfs[nx][ny][nstate] != -1) return;
    bfs[nx][ny][nstate] = ncost;
    Q.push({{nx , ny},nstate});
}
 
void relax(int x , int y , int state){
    int C = bfs[x][y][state];
 
    if(state == 0){
 
        if(check(x , y - 1) && check(x , y - 2)) add(x , y - 2 , 1 , C + 1);
        if(check(x , y + 1) && check(x , y + 2)) add(x , y + 1 , 1 , C + 1);
 
        if(check(x - 1 , y) && check(x - 2 , y)) add(x - 2 , y , 2 , C + 1);
        if(check(x + 1 , y) && check(x + 2 , y)) add(x + 1 , y , 2 , C + 1);
    }
 
    if(state == 1){
 
        if(check(x - 1 , y) && check(x - 1 , y + 1)) add(x - 1 , y , 1 , C + 1);
        if(check(x + 1 , y) && check(x + 1 , y + 1)) add(x + 1 , y , 1 , C + 1);
 
        if(check(x , y + 2)) add(x , y + 2 , 0 , C + 1);
        if(check(x , y - 1)) add(x , y - 1 , 0 , C + 1);
 
    }
 
    if(state == 2){
 
 
        if(check(x , y - 1) && check(x + 1 , y - 1)) add(x , y - 1 , 2 , C + 1);
        if(check(x , y + 1) && check(x + 1 , y + 1)) add(x , y + 1 , 2 , C + 1);
 
 
        if(check(x + 2 , y)) add(x + 2 , y , 0 , C + 1);
        if(check(x - 1 , y)) add(x - 1 , y , 0 , C + 1);
 
    }
 
 
}
int main(){
 
  //  freopen("in.in","r",stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
 
    cin>>T;
 
    while(T--){
 
        memset(bfs , -1 , sizeof(bfs));
 
        cin>>n>>m>>sx>>sy;
 
        for(int j = 1 ; j <= n ; j++){ cin>>valid[j]; valid[j] = "#" + valid[j]; };
 
 
        bfs[sx][sy][0] = 0;
        Q.push({{sx , sy} , 0});
 
        while(!Q.empty()){
 
            int x = Q.front().first.first , y = Q.front().first.second , state = Q.front().second; Q.pop();
 
            relax(x , y , state);
 
        }
 
        for(int j = 1 ; j <= n ; j++){
            for(int i = 1 ; i <= m ; i++){
                cout<<bfs[j][i][0]<<' ';
            }
            cout<<endl;
        }
 
 
    }
 
 
 
 
}
