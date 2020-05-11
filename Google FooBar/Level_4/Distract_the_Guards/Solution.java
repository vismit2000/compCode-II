import java.util.Arrays;

public class Solution {
    public static int gcd(int a, int b) 
    { 
        if(b == 0)
            return a;
        return gcd(b, a % b);
    }

    public static boolean loops(int a, int b) {
        int x = (a + b) / gcd(a, b);
        return ((x != 0) && ((x & (x - 1)) == 0));
    }

    public static boolean matching(boolean[][] graph, int n, int u, boolean[] seen, int[] match) {
        for(int v = 0; v < n; v++)
        {
            if(graph[u][v] && !seen[v])
            {
                seen[v] = true;
                if(match[v] < 0 || matching(graph, n, match[v], seen, match))
                {
                    match[v] = u;
                    return true;
                }
            }
        }
        return false;
    }

    public static int maxMatching(boolean[][] graph, int n) {
        int[] match = new int[n];
        Arrays.fill(match, -1);
        
        int flow = 0;

        for(int u = 0; u < n; u++)
        {
            boolean[] seen = new boolean[n];
            Arrays.fill(seen, false);

            if(matching(graph, n, u, seen, match))
                flow++;
        }
        return flow;
    }

    public static int solution(int[] banana_list) {
        int n = banana_list.length;

        boolean[][] graph = new boolean[n][n];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                graph[i][j] = false;

        for(int i = 0; i < n; i++)
        {
            for(int j = i; j < n; j++)
            {
                graph[i][j] = !loops(banana_list[i], banana_list[j]);
                graph[j][i] = graph[i][j];
            }
        }

        int flow = maxMatching(graph, n);
        int ans = n - 2 * (flow / 2);

        return ans;
    }
}