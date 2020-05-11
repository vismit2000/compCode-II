public class Solution {
    public static int calc_xor(int a) 
    {
        switch(a % 4)
        {
            case 0: return a;
            case 1: return 1;
            case 2: return a + 1;
            case 3: return 0;
        }
        return 0;
    }

    public static int getXor(int a, int b) 
    {
        return calc_xor(b) ^ calc_xor(a-1);
    }
    
    public static int solution(int start, int length) {
        int ans = 0;
        int s = start, l = length;
        while(l > 0)
        {
            ans ^= getXor(s, s + l -1);
            s += length;
            l--;
        }
        return ans;
    }
}