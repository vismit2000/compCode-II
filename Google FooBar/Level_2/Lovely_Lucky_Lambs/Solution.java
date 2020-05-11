public class Solution {
    public static int log2(int x)
    {
        return (int) (Math.log(x) / Math.log(2));
    }

    public static int solution(int total_lambs) {
        
        int min_hc = 0, max_hc = 0;

        min_hc = log2(total_lambs + 1);

        int sum_fib = 1, i = 1;

        int[] Fib = new int[60];
        Fib[0] = 1;
        Fib[1] = 1;

        while(sum_fib <= total_lambs)
        {
            max_hc++;
            if(i >= 2)
                Fib[i] = Fib[i-1] + Fib[i-2];
            sum_fib += Fib[i];
            i++;
        }
        
        return max_hc - min_hc;
    }
}