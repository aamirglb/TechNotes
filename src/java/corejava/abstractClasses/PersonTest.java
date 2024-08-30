// javac .\abstractClasses\PersonTest.java
// java abstractClasses.PersonTest

package abstractClasses;

import java.util.ArrayList;
import java.util.Scanner;
import java.lang.Character;

public class PersonTest 
{
    public static void main(String[] args)
    {
        // var people = new Person[2];
        ArrayList<Person> people = new ArrayList<>();

        System.out.println("List of current employees: ");
        people.add(new Employee("Aamir", 50_000, 1984, 1, 1));
        people.add(new Student("Ali", "Computer Science"));

        // people[0] = new Employee("Aamir", 50_000, 1984, 1, 1);
        // people[1] = new Student("Ali", "Computer Science");

        for(Person p : people)
        {
            System.out.println(p.getName() + ", " + p.getDescription());
        }

        char choice = 'q';
        Scanner sc = new Scanner(System.in);
        do
        {
            System.out.println("New Employee (E/e)");
            System.out.println("New Student (S/s)");
            System.out.println("Display All People (D/d)");
            System.out.println("Quit (Q/q)");
            System.out.print("Enter your choice: ");
            choice = sc.next().charAt(0); 
            sc.nextLine();
            choice = Character.toLowerCase(choice);
            // sc.close();
            switch( choice ) 
            {
                case 'e':
                    people.add( ReadEmployee(sc) );
                    break;

                case 's':
                    people.add( ReadStudent(sc));
                    break;

                case 'd':
                    ShowAll(people);
                    break;

                case 'q':
                    break;
                
            }
        } while( choice != 'q');
        sc.close();
    }

    private static void ShowAll(ArrayList<Person> ppl)
    {
        int count = 1;
        for(Person p : ppl)
        {
            System.out.println(count + ": " + p.getName() + ", " + p.getDescription());
            count += 1;
        }
    }

    private static Employee ReadEmployee(Scanner sc)
    {
        // Scanner sc = new Scanner(System.in);

        System.out.print("Enter Employee Name: ");
        var name = sc.nextLine(); 

        System.out.print("Enter Employee Salary: ");
        var salary = sc.nextInt();  sc.nextLine();

        System.out.print("Enter Hire Year: ");
        var year = sc.nextInt();  sc.nextLine();

        System.out.print("Enter Hire Month: ");
        var month = sc.nextInt();  sc.nextLine();

        System.out.print("Enter Hire Day: ");
        var day = sc.nextInt();  sc.nextLine();

        return new Employee(name, salary, year, month, day);
    }

    private static Student ReadStudent(Scanner sc)
    {
        System.out.print("Enter Student Name: ");
        var name = sc.nextLine();

        System.out.print("Enter Student Major: ");
        var major = sc.nextLine();

        return new Student(name, major);
    }
}