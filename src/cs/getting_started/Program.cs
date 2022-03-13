// See https://aka.ms/new-console-template for more information
using System;
using Animals;
using System.Text;

Console.WriteLine("Hello, World!");

UnitConverter feetToInch = new UnitConverter(12);
Console.WriteLine(feetToInch.Convert(30));

// Panda example
Panda p1 = new Panda("panda-1");
Panda p2 = new Panda("panda-2");

Console.WriteLine(p1.Name);
Console.WriteLine(p2.Name);
Console.WriteLine(Panda.Population);

// Point
Point pt1;
pt1.X = 2;
pt1.Y = 4;

Point pt2 = pt1;
pt2.X = 1;

Console.WriteLine(pt1.X);
Console.WriteLine(pt2.X);

int a = int.MinValue;
Console.WriteLine(a);
a--;
Console.WriteLine(a);

// Checked operator
// int aa = 1000000;
// int b = 1000000;

// // int c = checked(aa * b);
// int c;
// checked
// {
//     c = a * b;
// }

// float and decimal
{
    float x = 0.1f;
    Console.WriteLine(x+x+x+x+x+x+x+x+x+x);

    decimal m = 1M/6M;
    double d = 1.0/6.0;
    Console.WriteLine(m);
    Console.WriteLine(d);
}

Console.WriteLine('\u00A9');
Console.WriteLine('\u03A9');
Console.WriteLine('\u00B0');

string a2 = @"\\server\fileshare\helloworld.cs";
Console.WriteLine(a2);

// Indices
{
    char[] vowels = new char[]{'a', 'e', 'i', 'o', 'u'};
    Console.WriteLine($"Last Char: {vowels[^1]}");
    Console.WriteLine($"Second Last Char: {vowels[^2]}");
}

Console.WriteLine(default (decimal));

// Method parameters
{
    StringBuilder sb = new StringBuilder();
    sb.Append("Hello ");
    Foo(sb);
    Console.WriteLine(sb.ToString());

    // string fn, ln;
    // Split("Aamir Ali", out fn, out ln);
    Split("Aamir Ali", out string fn, out string ln);
    Console.WriteLine($"{fn}, {ln}");
}

int total = Sum(1, 2, 3, 4, 5);
Console.WriteLine($"Total: {total}");

int Sum(params int[] a)
{
    int sum = 0;
    for(int i=0; i<a.Length; ++i) sum += a[i];
    return sum;
}

static void Split(string name, out string fn, out string ln)
{
    int i = name.LastIndexOf(' ');
    fn = name.Substring(0, i);
    ln = name.Substring(i+1);
}
static void Foo(StringBuilder fooSb)
{
    fooSb.Append("test");
    fooSb = null;
}
public class UnitConverter
{
    int ratio;

    public UnitConverter(int unitRatio)
    {
        ratio = unitRatio;
    }

    public int Convert(int unit)
    {
        return unit * ratio;
    }
}

namespace Animals {
public class Panda
{
    public string Name;
    public static int Population;

    public Panda(string n)
    {
        Name = n;
        Population += 1;
    }
}
}

public struct Point
{
    public int X, Y;
}