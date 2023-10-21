if(args.Length < 3)
{
    WriteLine("Specify two colors and cursor size, e.g.");
    WriteLine("dotnet run red yellow 50");
    return;
}

ForegroundColor = (ConsoleColor)Enum.Parse(enumType: typeof(ConsoleColor),
    value: args[0],
    ignoreCase: true);

BackgroundColor = (ConsoleColor)Enum.Parse(
    enumType: typeof(ConsoleColor),
    value: args[1],
    ignoreCase: true);

CursorSize = int.Parse(args[2]);

WriteLine($"Theare are {args.Length} arguments passed from command line.");
int i = 0;
foreach(var arg in args)
{
    ++i;
    WriteLine("{0} => {1}", i, arg);
}

WriteLine("Is it working??");