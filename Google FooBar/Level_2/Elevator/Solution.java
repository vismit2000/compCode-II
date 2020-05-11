import java.util.Comparator;
import java.util.Arrays;

class Player{
    int major;
    int minor;
    int revision;
    String str;
    
    Player(int major, int minor, int revision, String str){
        this.major = major;
        this.minor = minor;
        this.revision = revision;
        this.str = str;
    }
}

class Checker implements Comparator <Player>
{
    public int compare(Player a, Player b)
    {
        if(a.major == b.major)
        {
            if(a.minor == b.minor)
                return a.revision - b.revision;
            return a.minor - b.minor;
        }
        return a.major - b.major;
    }
}

public class Solution {
    public static String[] solution(String[] l) {
        // Your code here
        int n = l.length;

        Player[] player = new Player[n];
        Checker checker = new Checker();

        for(int i = 0; i < n; i++)
        {
            if(l[i].contains("."))
            {
                String[] firstSplit = l[i].split("\\.", 2);

                if(firstSplit[1].contains("."))
                {
                    String[] secondSplit = firstSplit[1].split("\\.", 2);
                    player[i] = new Player(Integer.parseInt(firstSplit[0]), Integer.parseInt(secondSplit[0]), Integer.parseInt(secondSplit[1]), l[i]);
                }
                else
                    player[i] = new Player(Integer.parseInt(firstSplit[0]), Integer.parseInt(firstSplit[1]), -1, l[i]);
            }
            else
                player[i] = new Player(Integer.parseInt(l[i]), -1, -1, l[i]);
        }
        
        Arrays.sort(player, checker);

        String[] ans = new String[n];

        for(int i = 0; i < n; i++)
            ans[i] = player[i].str;
        
        return ans;
    }
}