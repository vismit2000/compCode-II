import java.util.Queue;
import java.util.LinkedList;

public class Solution {
    public static final int INF = 1000000;

    public static int[][] bfs(int[][] grid, int n, int m, int start_x, int start_y)
    {
        int[][] dp = new int[n][m];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                dp[i][j] = INF;

        int[][] visited = new int[n][m];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                visited[i][j] = 0;

        int[] dir_x = {-1, 0, 1, 0};
        int[] dir_y = {0, 1, 0, -1};

        Queue < Integer > X = new LinkedList < Integer > ();
        Queue < Integer > Y = new LinkedList < Integer > ();
        Queue < Integer > D = new LinkedList < Integer > ();

        X.offer(start_x);
        Y.offer(start_y);
        D.offer(1);

        while(X.peek() != null)
        {
            int x = X.poll();
            int y = Y.poll();
            int d = D.poll();

            dp[x][y] = d;
            visited[x][y] = 1;

            for(int i = 0; i < 4; i++)
            {
                int new_x = x + dir_x[i];
                int new_y = y + dir_y[i];
                int new_d = d + 1;

                if(new_x >= 0 && new_x < n && new_y >= 0 && new_y < m && grid[new_x][new_y] == 0 && visited[new_x][new_y] == 0)
                {
                    visited[new_x][new_y] = 1;
                    X.offer(new_x);
                    Y.offer(new_y);
                    D.offer(new_d);
                }
            }
        }
        return dp;
    }

    public static int solution(int[][] map) {
        int n = map.length;
        int m = map[0].length;

        int[][] bfs_start = bfs(map, n, m, 0, 0);
        int[][] bfs_end = bfs(map, n, m, n-1, m-1);

        int ans = INF;

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                int start_ans = INF, end_ans = INF;

                if(i > 0)
                {
                    start_ans = Math.min(start_ans, bfs_start[i-1][j]);
                    end_ans = Math.min(end_ans, bfs_end[i-1][j]);
                }
                if(i < n-1)
                {
                    start_ans = Math.min(start_ans, bfs_start[i+1][j]);
                    end_ans = Math.min(end_ans, bfs_end[i+1][j]);
                }
                if(j > 0)
                {
                    start_ans = Math.min(start_ans, bfs_start[i][j-1]);
                    end_ans = Math.min(end_ans, bfs_end[i][j-1]);
                }
                if(j < m-1)
                {
                    start_ans = Math.min(start_ans, bfs_start[i][j+1]);
                    end_ans = Math.min(end_ans, bfs_end[i][j+1]);
                }

                ans = Math.min(ans, start_ans + end_ans + 1);
            }
        }
        return ans;
    }
}