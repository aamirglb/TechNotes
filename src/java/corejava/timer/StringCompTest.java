package timer;

import java.util.*;

public class StringCompTest {
    public static void main(String[] args) {
        String[] names = {
            "Aamir",
            "Mohammad",
            "Ali",
            "Sultan"
        };

        System.out.println("Before sort: ");
        for(var n : names) {
            System.out.println(n);
        }

        var comp = new LengthComparator();
        // Arrays.sort(names, comp);
        // Arrays.sort(names, (String f, String s) -> f.length() - s.length());
        Arrays.sort(names, (f, s) -> f.length() - s.length());

        System.out.println("\nAfter sort: ");
        for(var n : names) {
            System.out.println(n);
        }
   } 
}

class LengthComparator implements Comparator<String>
{
    public int compare(String first, String second)
    {
        return first.length() - second.length();
    }
}
