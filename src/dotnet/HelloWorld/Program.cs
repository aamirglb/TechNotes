// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");
Console.WriteLine("What is your name?");
var name = Console.ReadLine();
var currentDate = DateTime.Now;
Console.Write($"{Environment.NewLine}Hello, {name}, on {currentDate:d} at {currentDate:t}!");
Console.WriteLine($"{Environment.NewLine}Press any key to exit...");
Console.ReadKey(true);
