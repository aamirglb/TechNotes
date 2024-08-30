package lambda;

import java.util.*;

class CollatzConjTest {
    public static void main(String[] args) {
        for(int i = 3; i < 151; ++i) {
            CollatzConjecture(i);
        }
    }

    private static void CollatzConjecture(int input) {
        ArrayList<Integer> nums = new ArrayList<>();
        var n = input;
        while(n != 1) {
            nums.add(n);
            if( n % 2 == 0) {
                n = n / 2;
            } else {
                n = (n * 3) + 1;
            }
        }

        System.out.print(input + " => " + nums.size() + ": ");
        // for (int i : nums) {
        //     System.out.print(i + " ");
        // }
        System.out.println();
    }
}