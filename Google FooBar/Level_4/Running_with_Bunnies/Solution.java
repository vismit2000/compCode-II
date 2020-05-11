import java.util.ArrayList;

public class Solution {
    public static int result;
    public static int[][] bestStates;
    public static final int INF = 1000000000;
    public static final int cMaxBunnies = 5;

    public static int count_set_bits(int n)
    {
        int ans = 0;
        while(n > 0)
        {
            n = n & (n-1);
            ans++;
        }
        return ans;
    }

    public static void Recurse(int[][] mtx, int bRescued, int loc, int time_limit)
    {
        if (loc == mtx.length - 1)
        {
            int rescued = count_set_bits(bRescued);
            if(time_limit >= 0) 
            {
                if(rescued > count_set_bits(result))
                    result = bRescued;
                else if(rescued == count_set_bits(result))
                    result = Math.min(result, bRescued);
            }
        }
        else if (loc > 0)
            bRescued |= (1 << (loc-1));

        int curVal = bestStates[bRescued][loc];

        if ((curVal == INF) || (curVal < time_limit))
        {
            bestStates[bRescued][loc] = time_limit;
            for (int i = 0; i < mtx[loc].length; i++)
                Recurse(mtx, bRescued, i, time_limit - mtx[loc][i]);
        }
    }

    public static int[] solution(int[][] times, int times_limit) {
        // Your code here
        bestStates = new int[50][10];
        for(int i = 0; i < 50; i++)
            for(int j = 0; j < 10; j++)
                bestStates[i][j] = INF;
        
        int n = times.length;

        int[] escape_all = new int[n-2];
        for(int i = 0; i < n-2; i++)
            escape_all[i] = i;

        result = 0;

        int[][] d = new int[n][n];

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                d[i][j] = times[i][j];

        // Floyd Warshall
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    d[i][j] = Math.min(d[i][j], d[i][k] + d[k][j]); 
                }
            }
        }

        // case of negative cycle
        for(int i = 0; i < n; i++)
            if(d[i][i] < 0)
                return escape_all;

        Recurse(times, 0, 0, times_limit);

        ArrayList <Integer> ans = new ArrayList< Integer >();

        for(int i = 0; i < cMaxBunnies; i++)
            if((result & (1 << i)) != 0)
                ans.add(i);

        int len = ans.size();
        int[] res = new int[len];
        for(int i = 0; i < len; i++)
            res[i] = ans.get(i);
        
        return res;
    }
}
