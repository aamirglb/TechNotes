// See https://aka.ms/new-console-template for more information
// #error version
using static System.Console;

System.Data.DataSet ds;
HttpClient client;

Animal?[] animals = new Animal?[]
{
    new Cat { Name = "Karen", Born = new(year:2022, month: 8, day:23),
        Legs = 4, IsDomestic = true },
    null,
    new Cat { Name = "Mufasa", Born = new(year:1994, month: 6, day: 12)},
    new Spider { Name = "spider", Born = DateTime.Today, IsPoisonous = true },
    new Spider { Name = "Captain Furry", Born = DateTime.Today }
};

foreach( Animal? animal in animals)
{
    string message;
    switch(animal)
    {
        case Cat fourLeggedCat when fourLeggedCat.Legs == 4:
            message = $"The cat named {fourLeggedCat.Name} has four legs.";
            break;
        case Cat wildCat when wildCat.IsDomestic == false:
            message = $"The non-domestic cat is named {wildCat.Name}.";
            break;
        case Cat cat:
            message = $"The cat is named {cat.Name}.";
            break;
        default:
            message = $"The animal named {animal.Name} is a {animal.GetType().Name}.";
            break;
        case Spider spider when spider.IsPoisonous:
            message = $"The {spider.Name} spider is poisonous.";
            break;
        case null:
            message = "The animal is null.";
            break;
    }
    WriteLine($"switch statement: {message}");
}
return;
WriteLine(Environment.CurrentDirectory);
WriteLine(Environment.OSVersion.VersionString);
WriteLine(Environment.UserName);
WriteLine(Environment.UserDomainName);

WriteLine("Temperature on {0:D} is {1}\u2103.", DateTime.Today, 24.5);

// print emoji
OutputEncoding = System.Text.Encoding.UTF8;
string emoji = char.ConvertFromUtf32(0x1F600);
WriteLine(emoji);

string xml = """
             <person age = "50">
                <first_name>Aamir</first_name>
             </person>
             """;
WriteLine(xml);


// raw interpolated string literals
var person = new {FirstName = "Aamir", Age = 38};
string json = $$"""
                {
                    "first_name": "{{person.FirstName}}",
                    "age": {{person.Age}},
                    "calculation", "{{{1+2}}}"
                }
                """;
WriteLine(json);

// float fraction = 0b00001100.1100;
// WriteLine(fraction);
WriteLine($"int = {sizeof(int)}, [{int.MinValue:N0} <==> {int.MaxValue:N0}]");
WriteLine($"double = {sizeof(double)}, [{double.MinValue:N0} <==> {double.MaxValue:N0}]");
WriteLine($"decimal = {sizeof(decimal)}, [{decimal.MinValue:N0} <==> {decimal.MaxValue:N0}]");

{
    WriteLine("Using doubles");
    double a = 0.1;
    double b = 0.2;
    if( a + b == 0.3)
    {
        WriteLine($"{a} + {b} = {0.3}");
    }
    else
    {
        WriteLine($"{a} + {b} != {0.3}");
    }

    WriteLine("Using decimal");
    decimal c = 0.1M;
    decimal d = 0.2M;
    if( c + d == 0.3M)
    {
        WriteLine($"{c} + {d} = {0.3}");
    }
    else
    {
        WriteLine($"{c} + {d} != {0.3}");
    }
}
dynamic myName = "Aamir";
WriteLine($"Length of {nameof(myName)} is {myName.Length}");
WriteLine($"default(int) = {default(int)}");
WriteLine($"default(bool) = {default(bool)}");
WriteLine($"default(DateTime) = {default(DateTime)}");
WriteLine($"default(string) = {default(string)}");


Write("Enter first name: ");
string firstName = ReadLine()!;

Write("Enter age: ");
string age = ReadLine()!;
WriteLine($"Hello {firstName}, age {age}.");

WriteLine();

Assembly? myApp = Assembly.GetEntryAssembly();

if(myApp == null) return;

foreach(AssemblyName name in myApp.GetReferencedAssemblies())
{
    Assembly a = Assembly.Load(name);
    int methodCount = 0;
    foreach(TypeInfo t in a.DefinedTypes)
    {
        methodCount += t.GetMethods().Count();
        // foreach(MethodInfo info in t.GetMethods())
        // {
        //     ++tmpCount;
        //     WriteLine("{0} => {1}", tmpCount, t.GetMethod(info));
        //     if(tmpCount > 10) break;
        // }
        // if(tmpCount < 10)
        // {
        //     ++tmpCount;
        //     WriteLine("{0} => {1}", tmpCount, t.GetMethod())
        // }
    }

    WriteLine("{0:N0} types with {1:N0} methods in {2} assembly.",
        arg0: a.DefinedTypes.Count(),
        arg1: methodCount,
        arg2: name.Name);
}
// byte[] bytes = new byte[256];
// for(int i = 0; i < 256; ++i)
// {
//     bytes[i] = (byte)i;
// }

// // File.WriteAllBytes("128bytes.txt", bytes);
// File.WriteAllBytes("256bytes.txt", bytes);
{
    object o = "3";
    int j = 4;
    if(o is int i)
    {
        WriteLine($"{i} x {j} = {i*j}");
    }
    else
    {
        WriteLine("o is not an int");
    }

    int number = Random.Shared.Next(1, 10);
    WriteLine($"My random number is {number}");

    switch(number)
    {
        case 1:
            WriteLine("One");
            break;
        case 2:
            WriteLine("Two");
            goto case 1;
        case 3:
        case 4:
            WriteLine("Three or four");
            goto case 1;
        case 5:
            goto A_label;
        default:
            WriteLine("Default");
            break;
    }

    WriteLine("After end of switch");
    A_label:
    WriteLine($"After A_label");
}


// STANAG 4509
