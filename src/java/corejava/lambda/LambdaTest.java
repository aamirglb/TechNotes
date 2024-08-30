package lambda;

import java.util.*;
import java.util.function.IntConsumer;

import javax.swing.*;
import javax.swing.Timer;

public class LambdaTest {
    public static void main(String[] args) {
        var planets = new String[] { "Mercury", "Venus", "Earth", 
        "Mars", "Jupiter", "Saturn", "Uranus", "Neptune" };

        System.out.println(Arrays.toString(planets));
        System.out.println("Sorted in dictionary order: ");
        Arrays.sort(planets);
        System.out.println(Arrays.toString(planets));
        System.out.println("Sorted by length: ");
        Arrays.sort(planets, (f, s) -> f.length() - s.length());
        System.out.println(Arrays.toString(planets));

        var timer = new Timer(2000, event -> 
        System.out.println("The timer is " + new Date()));
        timer.start();

        JOptionPane.showMessageDialog(null, "Quit Program?", "Exit Dialog", 0);

        repeat(10, i -> System.out.println("Countdown: " + (9 - i)));
    }


    public static void repeat(int n, IntConsumer action)
    {
        for(int i = 0; i < n; ++i) action.accept(i);
    }
}
