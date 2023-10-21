using static System.Console;

int[] sequentialNumbers = new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int[] oneTwoNumbers = new int[] {1, 2};
int[] oneTwoTenNumbers = new int[] {1, 2, 10};
int[] oneTwoThreeTenNumbers = new int[] {1, 2, 3, 10};
int[] primeNumbers = new int[]{2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int[] fibonacciNumbers = new int[] {0, 1, 1, 2, 3, 5, 8, 12, 21, 34, 55, 89};
int[] emptyNumbers = new int[] {};
int[] threeNumbers = new int[]{9, 7, 5};
int[] sixNumbers = new int[]{9, 7, 5, 4, 2, 10};

WriteLine($"{nameof(sequentialNumbers)}: {CheckSwitch(sequentialNumbers)}");
WriteLine($"{nameof(oneTwoNumbers)}: {CheckSwitch(oneTwoNumbers)}");
WriteLine($"{nameof(oneTwoTenNumbers)}: {CheckSwitch(oneTwoTenNumbers)}");
WriteLine($"{nameof(oneTwoThreeTenNumbers)}: {CheckSwitch(oneTwoThreeTenNumbers)}");
WriteLine($"{nameof(primeNumbers)}: {CheckSwitch(primeNumbers)}");
WriteLine($"{nameof(fibonacciNumbers)}: {CheckSwitch(fibonacciNumbers)}");
WriteLine($"{nameof(emptyNumbers)}: {CheckSwitch(emptyNumbers)}");
WriteLine($"{nameof(threeNumbers)}: {CheckSwitch(threeNumbers)}");
WriteLine($"{nameof(sixNumbers)}: {CheckSwitch(sixNumbers)}");

static string CheckSwitch(int[] values) => values switch
{
    [] => "Empty array",
    [1, 2, _, 10] => "Contains 1, 2, any single number, 10.",
    [1, 2, .., 10] => "Contains 1, 2, any range including empty, 10.",
    [1, 2] => "Contains 1 then 2.",
    [int item1, int item2, int item3] => $"Contains {item1} then {item2} then {item3}.",
    [0, _] => "Starts with 0, then one other number.",
    [0, ..] => "Starts with 0, then any range of numbers.",
    [2, .. int[] others] => $"Starts with 2, then {others.Length} more numbers.",
    [..] => "Any items in any order."
};