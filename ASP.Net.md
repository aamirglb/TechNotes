# ASP.NET Core

## ASP.NET Core in Action 2nd Edition

* In .NET, a _project_ is a unit of deployment, which will be compiled into a `.dll` file or an `executable`. Each separate app is a separate project. Multiple projects can be built and developed at once in a solution.

* Create a new Razor page application with .NET CLI

```cs
dotnet new sln -n WebApp1 -o WebApp1
dotnet new webapp -o WebApp1 --use-program-main
dotnet sln add WebApp1

dotnet run --project .\WebApp1\

dotnet add package <packagename>

dotnet add reference  # adds a project-to-project reference to your project file

dotnet run --launch-profile <Profile Name>
dotnet run --no-launch-profile  # ignore launchSetting.json file
dotnet run --no-launch-profile --environment Staging
```

* Most ASP.NET Core applications have dependencies on various external libraries,
which are managed through the NuGet package manager. These dependencies are
listed in the project, but the files of the libraries themselves aren’t included.

* ASP.NET Core projects list their dependencies in the project’s `.csproj` file.

[project_layout](./images/asp.net/project_layout.png)

*
> Pages: contains Razor pages files use to build the application
> Properties: contains launchSettings.json (controls how Visual Studio will run and debug the app)
> wwwroot: only folder allowed to be access by the browser (store CSS, JS, images, static HTML files)

* `appsettings.json` and `appsettings.Development.json` provides configuration settings that are used at runtime to control the behaviour of the application.

* `.csproj` defines the type of project being build (web app, console app, library), which platform the project targets (.NET Core 3.1, .NET 5.0 etc) and which NuGet packages the project depends on.

New project file includes changes like:
* No GUIDs
* Implicit file includes
* No paths to NuGet package .dll files

* NuGet is the library package manager for .NET, where libraries are packaged into
NuGet packages and published to https://nuget.org.

* All ASP.NET Core applications start in the same way as **.NET Console applications**, with a `Program.cs` file

* In ASP.NET Core applications, the Main entry point is used to build and run an `IHost` instance

* The `IHost` is the core of your ASP.NET Core application, containing the application configuration and the Kestrel server that listens for requests and sends responses.

* In .NET 7 ASP.NET Core applications the top-level statements build and run a WebApplication instance,

* Before C# 9, every .NET program had to include a static void Main function (it could also return int, Task, or Task<int>),

* In .NET 7 all the default templates use top-level statements
* The WebApplication and WebApplicationBuilder classes were introduced in .NET 6.

* Within the context of ASP.Net Core, **service** refers to any class that provides functionality to an application

* The single-responsibility principle (SRP) states that every class should be responsible for only a single piece of functionality

* SRP is one of the five main design principles promoted by Robert C. Martin in Agile Software Development, Principles, Patterns, and Practices

* In an ASP.NET Core application, this registration is performed by using the `Services` property of `WebApplicationBuilder`.

* `AddHttpLogging` isn't exposed directly on the `Services` property; it's an extension method that provides a convenient way to encapsulate all the code required to set up HTTP logging.

* The `Services` property is an `IServiceCollection`, which is a list of every known service that your application will need to use

* It’s important to consider the order of middleware when
adding it to the pipeline, as middleware can use only objects created
earlier in the pipeline

* WebApplication automatically adds more
middleware, including two of the most important and
substantial pieces of middleware in the pipeline: the _routing_
middleware and the _endpoint_ middleware.

* In ASP.NET Core, middleware is a C# class1 that can handle
an HTTP request or response.

The most important piece of middleware in most ASP.NET
Core applications is the _EndpointMiddleware_ class.

* https://learn.microsoft.com/en-us/aspnet/core/fundamentals/middleware/?view=aspnetcore-8.0#built-in-middleware


* https://www.rfc-editor.org/rfc/rfc9110#name-status-codes

Blazor in Action, by Chris Sainty (Manning, 2022).
Building Web APIs with ASP.NET Core, by Valerio De Sanctis (Manning, 2023).

https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview
https://developer.mozilla.org/en-US/docs/Web/HTTP/Status

```pwsh
# commands to create a minimal API application
dotnet new sln -n app1 -o app1
dotnet new web -o app1
dotnet sln add app1
```

* ASP.NET Core exposes the simple `static` helper types
`Results` and `TypedResults` in the namespace
`Microsoft.AspNetCore.Http`. You can use these helpers
to create a response with common status codes, optionally
including a JSON body.

* **Problem Details** is a web specification (https://www.rfc-editor.org/rfc/rfc7807.html) for providing machine-readable errors for
HTTP APIs. It defines the required and optional fields that should be in
the JSON body for errors.

* in .NET 6, ASP.NET Core introduced the `ConfigurationManager` class, implementing both of the two main configuration-related interfaces: `IConfigurationBuilder` and `IConfigurationRoot`

* You can use either the `DOTNET_ENVIRONMENT` or `ASPNETCORE_ENVIRONMENT` environment variable. The `ASPNETCORE_` value overrides the `DOTNET_` value if both are set.

* The
`ContentRootPath` property, for example, tells the
application in which directory it can find any configuration
files, such as appsettings.json.

* `LaunchSettings.json` defines profiles for running your application. You can use _profiles_ to run your application with different
environment variables.

* minimal API endpoint handlers, but there are other
types of handlers, such as MVC action methods and Razor
Pages

* Routing in ASP.NET Core is the process of selecting a
specific handler for an incoming HTTP request. In **minimal APIs**, the
handler is the _endpoint handler_ associated with a route. In **Razor Pages**,
the handler is a _page handler method_ defined in a Razor Page. In **MVC**,
the handler is an _action method in a controller_.

* ASP.NET Core can extract values
from the query string automatically in a process called _model binding_

Razer and Blazer

* ASP.NET Core 3.0 introduced a new routing system: **endpoint routing**.

* /products/123    -> app.MapGet("/products/{id}", (int id) => $"Received {id}");
* /products?id=456 -> app.MapGet("/products", (int id) => $"Received {id}");

* [FromRoute], [FromQuery], and [FromHeader] attributes force the
endpoint parameters to bind to specific parts of the request.

* StringValues is a helper type in the
Microsoft.Extensions.Primitives namespace that
represents zero, one, or many strings in an efficient way

https://cheatsheetseries.owasp.org/cheatsheets/Docker_Security_Cheat_Sheet.html
https://www.martinfowler.com/articles/injection.html

System.ComponentModel.DataAnnotations

* In ASP.NET context, a service refers to any
class or interface that the DI container creates when required























































































# C# 12 and .NET 8 

* On GitHub change `.com` to `.dev` in the link to convert the repository into a live code editor based on Visual Studio Code

* The **Polyglot Notebooks** extension for Visual Studio Code provides an easy and safe place to write
simple code snippets for experimenting and learning.

* C# Dev kit: https://devblogs.microsoft.com/visualstudio/announcing-csharp-dev-kit-for-visual-studio-code/.

* GitHub Codespaces is a fully configured development environment based on Visual Studio Code that
can be spun up in an environment hosted in the cloud and accessed through any web browser. https://github.com/features/codespaces

VSCode Extensions for C# development
C# Dev Kit [ms-dotnettools.csdevkit]
C# [ms-dotnettools.csharp]
IntelliCode for C# Dev Kit [ms-dotnettools.vscodeintellicode-csharp]
MSBuild project tools [tintoy.msbuild-project-tools]
ilspy-vscode [icsharpcode.ilspy-vscode]
REST Client [humao.rest-client]

* Visual studio code extensions at command prompt
```
code --list-extensions
code --install-extension <extension-id>
code --uninstall-extension <extension-id>
```

* https://code.visualstudio.com/shortcuts/keyboard-shortcuts-windows.pdf

* The .NET SDK includes the .NET runtime as well as the compilers and other tools needed to build .NET code and apps.

.NET SDK = .NET runtime + compiler + other tools

* .NET runtime versioning follows semantic versioning, that is, a major increment indicates breaking changes, minor increments indicate new features, and patch increments indicate bug fixes.

* Semantic Version
    major increment = breaking changes
    minor increment = new feature
    patch increment = bug fixes

```cs
dotnet --list-sdks
dotnet --list-runtimes
dotnet --info
```

* The C# compiler (named **Roslyn**) used by the dotnet CLI tool converts your C# source code into **intermediate language (IL)** code and stores the IL in an **assembly** (a DLL or EXE file).

* IL code statements are executed by .NET's virtual machine, known as **CoreCLR**.

* top-level program feature introduced in C# 9

* C# compiler generates two folders
    `obj`: one compiled _object_ file for each source code file
    `bin`: _binary_ executable for the application or class library

* `dotnet clean` - to clean the project
* This uses a feature introduced in .NET 5 called top-level programs, but it was not until .NET 6 that
Microsoft updated the project template for console apps to use top-level statements by default.

```
dotnet new console --use-program-main
```

* Implicitly imported namespaces: C# 10 and .NET 6.

* In Solution Explorer, expand the `obj` folder, expand the `Debug` folder, expand the `net8.0` folder, and open the file named `HelloCS.GlobalUsings.g.cs`.

* uses a feature introduced in C# 10 called **global namespace imports**, which imports some commonly used namespaces like System for use in all code files

```cs
// <autogenerated />
global using global::System;
global using global::System.Collections.Generic;
global using global::System.IO;
global using global::System.Linq;
global using global::System.Net.Http;
global using global::System.Threading;
global using global::System.Threading.Tasks;
```

```
string name = typeof(Program).Namespace ?? "None!";
```

* `??` is the null-coalescing operator. The first statement means, "If the namespace of Program is null, then return None!; otherwise, return the name."

```
dotnet new sln --name Chapter01       # or use -n instead of --name
dotnet new console --output HelloCS   # or use -o instead of --output
dotnet new console --framework net6.0  # or use -f instead of --framework to target different version
dotnet sln add HelloCS   # add the project to solution

dotnet help <command>

dotnet run --project Numbers
dotnet run --configuration Release


```

| Visual Studio 2022     | dotnet new      | JetBrains Rider
| ------------- | ------------- |------------------------|
| Console App | consle | |
| Class Library | classlib | |
| xUnit Test Project | xunit | |
| ASP.NET Core Empty | web | |
| Razor Class Library | razorclasslib | |
| ASP.NET Core Web App (Model-View-Controller) | mvc | |
| ASP.NET Core Web API | webapi | |
| ASP.NET Core Web API (native AOT) | webapiaot | |
| Blazor Web App | blazor | |

* https://learn.microsoft.com/en-us/docs

* add a `<LangVersion>` configuration element to the project file

```
<LangVersion>7.3</LangVersion>
<LangVersion>preview</LangVersion>
```

* You can define your own labeled regions around any statements you want and then most code editors will allow you to collapse and expand them in the same way as blocks

```cs
#region My new region
#endregion
```

https://learn.microsoft.com/en-us/dotnet/csharp/fundamentals/codingstyle/coding-conventions
https://learn.microsoft.com/en-us/dotnet/csharp/fundamentals/coding-style/coding-conventions

* C# 10 introduced a new keyword combination and .NET SDK 6 introduced a new project setting that works together to simplify importing common namespaces

* The `global using` keyword combination means you only need to import a namespace in one `.cs` file and it will be available throughout all `.cs` files instead of having to import the namespace at the top of every file that needs it.

**GlobalUsings.cs**

```
global using System;
global using System.Linq;
global using System.Collections.Generic;
```

* Any projects that target .NET 6 or later, and therefore use the C# 10 or later compiler, generate a `<ProjectName>.GlobalUsings.g.cs` file in the `obj\Debug\net8.0` folder to implicitly globally import some common namespaces

| SDK  | Implicitly imported namespaces |
|------|---------------------------------|
| Microsoft.NET.Sdk | System
                        System.Collections.Generic
                        System.IO
                        System.Linq
                        System.Net.Http
                        System.Threading
                        System.Threading.Tasks |

| Microsoft.NET.Sdk.Web | Same as Microsoft.NET.Sdk and: 
                            System.Net.Http.Json
                            Microsoft.AspNetCore.Builder
                            Microsoft.AspNetCore.Hosting
                            Microsoft.AspNetCore.Http
                            Microsoft.AspNetCore.Routing
                            Microsoft.Extensions.Configuration
                            Microsoft.Extensions.DependencyInjection
                            Microsoft.Extensions.Hosting
                            Microsoft.Extensions.Logging |
| Microsoft.NET.Sdk.Worker | Same as Microsoft.NET.Sdk and:
                                Microsoft.Extensions.Configuration
                                Microsoft.Extensions.DependencyInjection
                                Microsoft.Extensions.Hosting
                                Microsoft.Extensions.Logging |

* `.csproj`

```xml
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
    <OutputType>Exe</OutputType>
    <TargetFramework>net8.0</TargetFramework>
    <Nullable>enable</Nullable>
    <ImplicitUsings>enable</ImplicitUsings>
</PropertyGroup>
<ItemGroup>
    <Using Remove="System.Threading" />
    <Using Include="System.Numerics" />
    <Using Include="System.Console" Static="true" />
    <Using Include="System.Environment" Alias="Env" />
</ItemGroup>
</Project>
```

* Keywords such as `string` that look like types are **aliases**, which represent types provided by the platform on which C# runs.

* In practice, the platform for C# is .NET, which provides tens of thousands of types to C#, including System.Int32, which is the C# keyword alias int maps to

* `N0`: format a number (N) with zero (0) decimal places

* In C# 12, `nameof` can now access instance data from a static context

* @ symbol to use a verbatim literal string

```cs
string filePath = @"C:\televisions\sony\bravia.txt";
```

* Two of the improvements seen in C# 7 and later are the use of the underscore character _ as a digit separator and support for binary literals.

* C# has an operator named `sizeof()` that returns the number of bytes that a type uses in memory

* https://www.ima.umn.edu/~arnold/disasters/patriot.html

* The System.Half type was introduced in .NET 5. (2 bytes)
* The System.Int128 and System.UInt128 types were introduced in .NET 7. (16 bytes)

* To allow unsafe block in the code
```
<AllowUnsafeBlocks>True</AllowUnsafeBlocks>
```

* There is a special type named `object` that can store any type of data
* There is another special type named `dynamic` that can also store any type of data
* You can use the `var` keyword to declare local variables with C# 3 and later. The compiler will infer the type from the value that you assign after the assignment operator, =.

* With C# 9, Microsoft introduced another syntax for instantiating objects, known as **target-typed new**. When instantiating an object, you can specify the type first and then use new without repeating the type

```
XmlDocument xml1 = new(); // Target-typed new

class Person
{
    public DateTime BirthDate;
}

Person p = new();
p.BirthDate = new(1990, 3, 6);

List<Person> people = new()
{
    new() { FirstName = "Md" },
    new() { FirstName = "Aamir" },
    new() { FirstName = "Ali }
};
```

Page-94: Getting and setting the default values for types

* You can determine the default value of a type by using the `default()` operator and passing the type as a parameter. You can assign the default value of a type by using the `default` keyword.

* `null` is the default for all reference types

* C# 6 and later have a handy feature named **interpolated strings**. A string prefixed with $ can use curly braces around the name of a variable or expression to output the current value of that variable or expression at that position in the string

```
{ index [, alignment ] [: formatString] } // syntax for formatting
```

* Use `Console.ReadLine()` to read the input

* By default, with .NET 6 and later, nullability checks are enabled

```cs
string? firstName = Console.ReadLine(); // expecting a possible null value
string age = Console.ReadLine()!;       // null-forgiving operator, user should make sure ReadLine() doesn't return null
```

```cs
using static System.Console;  // statically import the class (not a namespace)
```

* Same can be done in `.csproj` 

```xml
<ItemGroup>
    <Using Include="System.Console" Static="true" />
</ItemGroup>
```

* In top-level programs, the `Program` class and its `Main` method are hidden, along with the declaration of the `args` array.

* Another way to handle differences in operating systems is to use the `OperatingSystem` class in the `System` namespace,

* a new feature introduced in C# 7.1 was support for async in Main

* a new feature introduced in C# 7.1 was support for async in Main

* **Null-coalescing operators (??)**

```cs
int maxLen = authorName?.Length ?? 30;
authorName ??= "Unknow";  // if authorName is null, it will be set as Unknow
```

* Technically, the sizeof operator requires an unsafe code block but the sizes of
value types with a C# alias, like int and double, are hardcoded as constants by the compiler
so they do not need an unsafe block.

* An infamous example is the #gotofail bug in Apple’s iPhone iOS operating system

* A feature introduced with C# 7 and later is **pattern matching**. The if statement can use the `is` keyword in combination with declaring a local variable to make your code safer

* In C# 8 or later, you can simplify switch statements using **switch expressions**

* The `System.Convert` type can convert to and from all the C# number types, as well as Booleans, strings, and date and time values

* **Banker's rounding**: It will round _away from zero_ if the decimal part is the midpoint .5 and the non-decimal part is _odd_, but it will round toward zero if the non-decimal part is _even_.

* The safest thing to do is to convert the binary object into a string of safe characters. Programmers call this **Base64** encoding.

* An exclamation mark `!` after an expression is called the **null-forgiving operator** and it disables the compiler warning. The null-forgiving operator has no effect at runtime.

* The `checked` statement tells .NET to throw an exception when an overflow happens instead of allowing it to happen silently

* Naming things is one of the hardest parts of computing

```cs
using System.Globalization; // To use CultureInfo.
```

* To use hot reload launch the application using `dotnet watch`

* principle that programmers should create unit tests before they write code, and this is called **Test-Driven Development (TDD)**

* Microsoft has a proprietary unit testing framework known as **MSTest**. free and open-source third-party framework **xUnit.net**

* A class library is a package of code that can be distributed and referenced by other .NET applications

* Class library assemblies group types together into easily deployable units (DLL files).

* If you use C# 10 or later, **file-scoped namespace** declaration

* If you do not explicitly apply the **public** keyword, then it will only be accessible within the _assembly that defined it_.

* implicit access modifier for a class is _internal_

* Introduced with .NET 7, the **file** access modifier applied to a type means that type can only be used within its code file.

* There are three specialized categories of field: 
    **Constant**: The data never changes  
    **Read-only**: The data cannot change after the class is instantiated, but the data can be calculated or loaded from an external source at the time of instantiation 
    **Event**

* Class Methods:
    **Constructor**: The statements execute when you use the `new` keyword to allocate memory to instantiate a class
    **Property**: The statements execute when you get or set data
    **Indexer**: The statements execute when you get or set data using "array" syntax [].
    **Operator**: The statements execute when you apply an operator like + and / to operands of your type


* `using Env = System.Environment;`

* .NET 6 introduced the `DateOnly` type. This would store only the date without a time value. `DateTime` stores the date and time, but it varies between local and UTC time.

* The best choice is `DateTimeOffset`, which stores the date, time, and hours offset from **Universal Coordinated Time (UTC)**, which is related to the time zone.

* There are four **member access modifier** keywords, and two combinations of access modifier keywords that you can apply to a class member

| Member Access Modifier | Description |
|------------------------|-------------|
| `private`   | The member is accessible inside the type only. This is the default. |
| `internal`  | The member is accessible inside the type and any type in the same assembly. |
| `protected` | The member is accessible inside the type and any type that inherits from the type. |
| `public`    | The member is accessible everywhere. |
| `internal protected` | The member is accessible inside the type, any type in the same assembly, and any type that inherits from the type. Equivalent to a fictional access modifier named internal_or_protected. |
| `private protected` | The member is accessible inside the type and any type that inherits from the
type and is in the same assembly. Equivalent to a fictional access modifier named internal_and_protected. This combination is only available with C# 7.2 or later. |

* An `enum` type is a very efficient way of storing one or more choices because, internally, it uses integer values in combination with a lookup table of string descriptions

* `List<T>`: is generics that was introduced in 2005 with C# 2

* The old `System.Collection` types are **statically typed** to contain weakly typed `System.Object` items. The newer `System.Collection.Generic` types are statically typed to contain strongly typed <T> instances.

* Constant fields are accessible via the type not by instance variables.

* Every reference to the read-only field is a live reference, so any future changes will be correctly reflected by the calling code

* C# 11 introduced the `required` modifier. If you use it on a field or property, the compiler will ensure that you set the field or property to a value when you instantiate it (require .NET 7 or later)

* .NET only added support for **tuples** with .NET 4 in 2010, using the `System.Tuple` type

* The ability to alias a tuple was introduced in C# 12 so that you can name the type and use that as the type name when declaring variables and parameters.

```cs
using UnnamedParameters = (string, int); // Aliasing a tuple type.
// Aliasing a tuple type with parameter names.
using Fruit = (string Name, int Number);
```

* `Tuples` are not the only type that can be deconstructed. Any type can have special methods, named
`Deconstruct`, that break down an object into parts.

* A **property** is simply a method (or a pair of methods) that acts and looks like a field when you want to get or set a value

* **Indexers** allow the calling code to use the array syntax to access a _property_.

* https://learn.microsoft.com/en-us/dotnet/csharp/fundamentals/functional/patternmatching

* One of the most important behaviors of record types is their equality. Two records with the same property values are considered equal.

* Introduced with C# 12, you can define one constructor as part of the class definition. This is called the **primary constructor**.

```cs
// Auto generate the class constructor
public class Headset(string manufacturer, string productName);
```

* Avoid types in the `System.Collections` namespace. Use types in the `System.Collections.Generics` and related namespaces instead

* `System.Collections.Generic.Dictionary<TKey, TValue>` can be used to store multiple values

* Events are often described as _actions that happen to an object_. Events are built on **delegates**.

* think of a delegate as being a **type-safe method pointer**. In other words, a _delegate_ contains the memory address of a method 
that must match the same signature as the delegate, enabling it to be called safely with the correct parameter types

* Delegates have built-in support for asynchronous operations that run on a different thread, which can provide improved responsiveness

* The most important example is that delegates allow us to implement events to send messages between different objects that do not need to know about each other.

* Microsoft has two predefined delegates for use as events. They both have two parameters: `object? sender`, `EventArgs e` or `TEventArgs e`

* ## Common Interfaces

| Interface | Method(s) | Description |
|-----------|-----------|-------------|
| `IComparable` | `CompareTo(other)` | This defines a comparison method that a type implements to order or sort its instances. |
| `IComparer`   | `Compare(first, second)` | This defines a comparison method that a secondary type implements to order or sort instances of a primary type. |
| `IDisposable` | `Dispose()` | This defines a disposal method to release unmanaged resources more efficiently than waiting for a finalizer. |
| `IFormattable` | `ToString(format, culture)` | This defines a culture-aware method to format the value of an object into a string representation. |
| `IFormatter` | `Serialize(stream, object)`. `Deserialize(stream)` | This defines methods to convert an object to and from a stream of bytes for storage or transfer. |
| `IFormatProvider` | `GetFormat(type)` | This defines a method to format inputs based on a language and region. |

* If a type implements one of the `IComparable` interfaces, then arrays and collections containing instances of that type can be sorted

* A language feature introduced in C# 8 is **default implementations** for an interface

* **Boxing** in C# is when a value type is moved to heap memory and wrapped inside a System.Object instance. **Unboxing** is when that value is moved back onto the stack. 

```cs
int n = 3;
object o = n; // Boxing happens implicitly.
n = (int)o; // Unboxing only happens explicitly.
```

* https://learn.microsoft.com/en-us/dotnet/csharp/programming-guide/types/boxing-and-unboxing

* use a `record class` because one of its benefits is that it implements this equality behavior for you.

* C# 10 introduced the ability to use the `record` keyword with `struct` types as well as `class` types

* A `struct` does not implement the `==` and `!=` operators, but they are automatically implemented with a `record struct`

* Each type can have a single **finalizer** that will be called by the .NET runtime when the resources need to be released

* but in C# 8 and later, reference types can be configured to warn you about `null` values by setting a file- or project-level option, enabling this useful new feature

```cs
string  firstName; // Allows null but gives warning when potentially null.
string? lastName;  // Allows null and does not give warning if null.

// To disable the feature at the file level
#nullable disable
#nullable enable

<NoWarn>CS8600;CS8602</NoWarn>

#pragma warning disable CS8602
WriteLine(firstName.Length);
WriteLine(lastName.Length);
#pragma warning restore CS8602
```

* ### null related operator

```cs
public string? Building;
public string Street = string.Empty;

Building = null,  // OK
Street = null,    // WARNING: CS8625 Cannot convert null literal to non-nullable reference type.

Street = null!, // null-forgiving operator: disable CS8625 warning

WriteLine(address.Building.Length); // CS8602 Dereference of a possibly null reference.
WriteLine(address.Street.Length);

if (address.Street is not null)
{
    WriteLine(address.Street.Length);
}

if (!(thisCouldBeNull is null))  // C# 7 ! with is null

if (thisCouldBeNull is not null)  // C# 9, is not null 

string authorName = null;
int? authorNameLength;

// null conditional operator (?.), instead of throwing exception, null is assigned
authorNameLength = authorName?.Length;

// null-coalescing operator (??), use alternate value if authorName is null
authorNameLength = authorName?.Length ?? 25;
```

* C# 10 introduced a convenience method to throw an exception if an argument is `null`

```cs
public void Hire(Person manager, Person employee)
{
    ArgumentNullException.ThrowIfNull(manager);
    ArgumentNullException.ThrowIfNull(employee);
}

// C# 11 preview - this feature was not accepted
public void Hire(Person manager!!, Person employee!!)
```

```cs
class Person {
    public void Show() { Console.Write("Person"); }
}

class Employee : public Person {
    // hide inherited member function warning
    public new void Show() { Console.Write("Employee"); }
}
```

* You can only **override** it if the base class chooses to allow overriding, by applying the `virtual` keyword to any methods that should allow overriding.

* The `base` keyword allows a subclass to access members of its superclass, that is, the **base class** that it inherits or derives from.

* You can prevent another developer from inheriting from your class by applying the `sealed` keyword to its definition.

* you can use the `as` keyword to cast a type. Instead of throwing an exception, the `as` keyword returns `null` if the type cannot be cast.

* Can we still add new methods to strings? Yes, if we use a language feature named **extension methods**, which was introduced with C# 3.0

* With C# 8, _interfaces_ can now include default implementations, making them more like abstract classes



| Keyword   | .NET type |
|-----------|-----------|
| `string`  | `System.String` |
| `char`    | `System.Char` |
| `sbyte`   | `System.SByte` |
| `byte`    | `System.Byte` |
| `short`   | `System.Int16` |
| `ushort`  | `System.UInt16` |
| `int`     | `System.Int32` |
| `uint`    | `System.UInt32` |
| `long`    | `System.Int64` |
| `ulong`   | `System.UInt64` |
| `nint`    | `System.IntPtr` |
| `nuint`   | `System.UIntPtr` |
| `float`   | `System.Single` |
| `double`  | `System.Double` |
| `decimal` | `System.Decimal` |
| `bool`    | `System.bool` |
| `object`  | `System.Object` |
| `dynamic` | `System.Dynamic.DynamicObject` |

* C# 9 introduced the `nint` and `nuint` keyword aliases for **native-sized integers**, meaning that the storage size for the integer value is platform-specific

page-430




* Initial Microsoft's WebAssembly supporting product was called Blazor (client side version) and was released as part of ASP.NET. Blazor can be used for doing non-visual operations and also to modify the HTML tree in C#.

* Microsoft says WinUI 3 is best used when apps are graphical, media, and consumer focused, and WPF is best used when leveraging the larger ecosystem of third-party controls and libraries.