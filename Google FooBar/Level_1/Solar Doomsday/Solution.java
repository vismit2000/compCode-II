import java.util.Collections;
import java.util.ArrayList;

public class Solution {
    public static int[] solution(int area) {
        // Your code here
        ArrayList <Integer> squares = new ArrayList< Integer >();
        ArrayList <Integer> ans = new ArrayList< Integer >();
        
        for(int i = 1; i <= 1000; i++)
            squares.add(i*i);
        
        int left = area, index;
        
        while(left > 0)
        {
            index = Collections.binarySearch(squares, left);
            if(index < 0)
                index = -1*(index + 1) - 1;
            ans.add(squares.get(index));
            left -= squares.get(index);
        }
        
        int n = ans.size();
        
        int[] final_ans = new int[n];
        
        for(int i = 0; i < n; i++)
            final_ans[i] = ans.get(i);
        
        return final_ans;
    }

    public static void main(String args[]) {
        int[] ans = solution(12);
        // System.out.println(ans);
        for(int i = 0; i < ans.length; i++)
            System.out.println(ans[i]);
    }
}