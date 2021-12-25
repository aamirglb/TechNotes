# C#

* **.NET Core** is open source, is available on Linux, and uses modern patterns.
    
* **C#** and **ASP.NET Core**: create web applications and services that run on Windows, Linux, and Mac. 

* **Windows Runtime**: create native Windows apps (Universal Windows Platform, UWP) using C# and XAML, as well as .NET Core.

* **Xamarin**, C# and XAML: create apps that run on Android and iOS devices. 
    
* ASP.NET Core works great in combination with JavaScript technologies like Angular and React/Redux. 
    
* C# started not only as an object-oriented general-purpose programming language but was a component-based programming     language that supported _properties_, _events_, _attributes_ (annotations), and building assemblies (binaries including metadata).
    
* C# was enhanced with **Generics**, **Language Integrated Query (LINQ)**, **lambda expressions**, **dynamic features**, and easier **asynchronous** programming. 
    
* C# is not an easy programming language because of the many features it offers, but it’s continuously evolving with features that are practical to use.
    
* C# is more than an object-oriented or component-based language; it also includes ideas of functional programming.
    
## C# 1.0 Features

* .NET Framework consisted of about 3,000 classes and the CLR. C# offered component-based programming enhancements such as delegates and events.

    * Classes
    * Structs
    * Interfaces
    * Events
    * Properties
    * Delegates
    * Expressions
    * Statements
    * Attributes
    * Literals
    
## C# 2.0 Features

* Released in 2005, along with Visual Studio 2005, Class count: 8,000 types. 

    * Generics
    * Partial types
    * Anonymous methods
    * Nullable types
    * Iterators
    * Covariance and contravariance

## C# 3.0 Features

* Released in late 2007, along with Visual Studio 2008, Class count: 12,000 types.

    * Auto-implemented properties
    * Anonymous types
    * Query expressions
    * Lambda expressions
    * Expression trees
    * Extension methods
    * Implicitly typed local variables
    * Partial methods
    * Object and collection initializers
    
## C# 4.0 Features

    * Dynamic binding
    * Named/optional arguments
    * Generic covariant and contravariant
    * Embedded interop types
    
## C# 5.0 Features

    * Asynchronous members
    * Caller info attributes
    
## C# 6 Features

    * static using, 
    * expression-bodied methods and properties, 
    * auto-implemented property initializers, 
    * readonly auto properties, 
    * the nameof operator, 
    * the null conditional operator, 
    * string interpolation, 
    * dictionary initializers, 
    * exception filters, and
    * await in catch. 
    
## C# 7 Features

    * Digit Separators,
    * Binary Literals,
    * Expression-Bodied Members,
    * Out Var
    * Non-Trailing Named Arguments,
    * Readonly Struct,
    * In Parameters
    * Private Protected,
    * Target-Typed Default
    * Local Functions,
    * Tuples,
    * Inferred Tuple Names,
    * Deconstructors,
    * Pattern Matching,
    * Throw Expressions,
    * Async Main,
    * Reference Semantics,
    
## .NET History
    
| .NET Framework | CLR | C#  | Visual Studio |
|----------------|-----|-----|---------------|
| 1.0            | 1.0 | 1.0 | 2002  | 
| 1.1            | 1.1 | 1.2 | 2003  |
| 2.0            | 2.0 | 2.0 | 2005  |
| 3.0            | 2.0 | 3.0 | 2005+ |
| 3.5            | 2.0 | 3.0 | 2008  |
| 4.0            | 4.0 | 4.0 | 2010  |
| 4.5            | 4.0 | 5.0 | 2012  |
| 4.5.1          | 4.0 | 5.0 | 2013  |
| 4.6            | 4.0 | 6   | 2015  |
| 4.7            | 4.0 | 7   | 2017  |  

    
* **Intermediate Language (IL)** code can be checked by using the tool **ildasm.exe** to open DLL or EXE files that contain .NET code.
    
* Other parts of the CLR are:
    * a garbage collector (GC)
    * a security mechanism
    * an extension for the debugger
    * a threading facility

* .NET 3.0: **Windows Presentation Foundation (WPF)** was probably the biggest part of the new Framework for creating Windows desktop applications. Windows Forms wrapped the native Windows controls and was based on pixels, whereas WPF was based on DirectX to draw every control on its own. The vector graphics in WPF allow seamless resizing of every form. 
    
* With WPF the user interface can be designed using an XML syntax: XML for Applications Markup Language (XAML).
    
* For communicating between applications different technologies where used like _ASP.NET Web Services_, _.NET Remoting_, _Message Queuing_ etc. With .NET 3.0, **Windows Communication Foundation (WCF)** combined all the options of the other APIs into the one API.
    
* .NET 5.0: A new version of platform-independent communication is offered by the ASP.NET Web API. Unlike WCF, which offers stateful and stateless services as well as many different network protocols, the ASP.NET Web API is a lot simpler and based on the **Representational State Transfer (REST)** software architecture style.
    
* .NET Core is smaller with modular NuGet packages, has a runtime that’s distributed with every application, is open source, and is available not only for the desktop version of Windows but also for many different Windows devices, as well as for Linux and OS X.
    
* More than 20,000 APIs have been added to .NET Core 2.0.
    
* Another feature that helps bring legacy applications to .NET Core is the Windows Compatibility Pack (Microsoft.Windows.Compatibility). This NuGet package defines APIs for WCF, registry access, cryptography, directory services, drawing, and more.
    
* The .NET Standard is a spec that defines which APIs should be available on any platform that supports the standard.

* .NET Core is designed in a modular approach. The framework splits up into a large list of NuGet packages.
    
* The .NET Standard is not an implementation; it’s a contract. This contract specifies what APIs need to be implemented. .NET Framework, .NET Core, and Xamarin implement this standard.
    
* A NuGet package is a zip file that contains the assembly (or multiple assemblies) as well as configuration information and PowerShell scripts. 
    
* The new CLR and the CoreCLR include the JIT compiler named RyuJIT. It support the Edit and Continue feature while debugging with Visual Studio.
    
* Creating a managed thread from C# is not necessarily a thread from the underlying operating system. Threads are virtualized and managed by the runtime.
    
* Starting with Windows 8, the Windows operating system offers another framework: the Windows Runtime. This runtime is used by the Windows Universal Platform (WUP) and was version 1 with Windows 8, version 2 with Windows 8.1, and version 3 with Windows 10.

* The assembly generated for .NET Core has a dependency to the `System.Console` assembly, whereas the .NET 4.6 assembly finds the Console class in the mscorlib assembly.
    
* One great productivity feature from the code editor is _code snippets_. Just by typing _cw_ and pressing Tab twice in the editor, the editor creates Console.WriteLine.
    
* **Microsoft Azure** offers Software as a Service (SaaS), Infrastructure as a Service (IaaS), Platform as a Service (PaaS), and Functions as a Service (FaaS).
    
## Core C#

* All C# code must be contained within a class.
    
* Constants are always implicitly static.
    
* Value type stores its value directly, whereas a reference type stores a reference to the value.

* Value types are stored in an area known as the stack, and reference types are stored in an area known as the managed heap.
    
* If you want to define your own type as a value type, you should declare it as a **struct**.
    
* C# has 15 predefined types, 13 value types, and 2 (string and object) reference types.
    
* In C#, all data types have been defined in a platform-independent manner to allow for the possible future porting of C# and .NET to other platforms.
    
* strings are immutable. Making changes to one of these strings creates an entirely new string object, leaving the other string unchanged.
    
* With C# 7, the switch statement has been enhanced with pattern matching. Using pattern matching, the ordering of the cases becomes important.
    
* Namespace Aliases

```c#
    using alias = NamespaceName;
    :: is namespace alias qualifier
```

* Aprart from keywords, C# also includes a number of commands that are known as **preprocessor directives**. These commands are never actually translated to any commands in your executable code, but they affect aspects of the compilation process.

* C# doesn’t actually have a separate preprocessor. The so-called preprocessor directives are actually handled by the compiler.
    
* Class members can be one of the following:

    * Fields
    * Constants
    * Methods
    * Properties: Properties are sets of functions that can be accessed from the client in a similar way to the public fields of the class.
    * Constructors
    * Indexers: Indexers allow object to be accessed the same way as arrays. 
    * Operators
    * Events: Events are class members that allow an object to notify a subscriber whenever something noteworthy happens, such as a field or property of the class changing, or some form of user interaction occurring.
    * Destructors or finalizers: It is impossible to predict precisely when a finalizer will be called.
    * Types: Classes can contain inner classes.

    
* Fields with the `readonly` modifier can be assigned values only from constructors.
    
* `property` is a method or a pair of methods dressed to look like a field.
    
* In C# 7, property accessors can be written as **expression-bodied members**.

```c#
    public string FirstName
    {
    get => _firstName;
    set => _firstName = value;
    }
```        

* Auto-implemented properties    

```c#
    public int Age { get; set; }
    public int Age { get; set; } = 42;
```    

* expression-bodied properties/methods don’t need curly brackets and return statements.
    
* Use `var` with the new keyword, for creating **anonymous types**.

```c#
    var captain = new
    {
        FirstName = "James",
        MiddleName = "T",
        LastName = "Kirk"
    };
```

* **Named Arguments**

```c#
    r.MoveAndResize(x: 30, y: 40, width: 20, height: 40);
```

* **Variable Number of Arguments**

```c#
    public void AnyNumberOfArguments(params int[] data);
```

* **coalescing operator**

```c#
    // If the left side of this operator is null, the right side of this operator is processed.
    x =  instance ?? (instance = new Singleton(42)); 
```

* Special syntax known as a **constructor initializer** for calling one constructor from other.

```c#
    public Car(string description, uint nWheels)
    public Car(string description): this(description, 4)
```   

* A C# constructor initializer may contain either one call to another constructor in the same class (using keyword **base**) or one call to a constructor in the immediate base class (using keyword **base**). It is not possible to put more than one call in the initializer.
    
* With a **struct**, you can specify how the fields are to be laid out in memory. 
    
* It is an error to define a default (parameterless) constructor for a struct.
    
* A struct is considered fully initialized either when the new operator has been called against it or when values have been individually assigned to all its fields.
    
* When using the **in** modifier with reference types, you can change the content of the variable, but not the variable itself.
    
* **Nullable Types**: Variables of reference types (classes) can be null while variables of value types (structs) cannot. This can be a problem with some scenarios, such as mapping C# types to database or XML types. A database or XML number can be null, whereas an int or double cannot be null.
    
* A **nullable type** is a value type that can be null. The only overhead a value type has compared to the underlying struct is a Boolean member that tells whether it is null.
    
* Use the **HasValue** and **Value** properties of nullable types.
    
* enum type can be used to assign multiple options to a variable and not just one of the enum constants. To do this, the values assigned to the constants must be different bits, and the Flags attribute needs to be set with the enum.
    
* The **partial** keyword allows the _class_, _struct_, _method_, or _interface_ to span multiple files.
    
* Attributes, XML comments, interfaces, generic-type parameter attributes, and members are combined when the partial types are compiled into the type.
    
* Partial classes can contain partial methods. This is extremely useful if generated code should invoke methods that might not exist at all. If there’s no implementation of partial method, the compiler removes the invocation of the method.

* A partial method needs to be of type void. Otherwise the compiler cannot remove the invocation in case no implementation exists.
    
* **Extension Methods**: adds additional functionality to classes. Extension methods are static methods that can look like part of a class without actually being in the source code for the class. This keyword defines the type that is extended.
    
* In case the type also defines an instance method with the same name, the extension method is never used. Any instance method already in the class takes precedence.
    
* Every class is actually derived from `System.Object` and struct is always derived from `System.ValueType`, which in turn derives from `System.Object`.
    
* For more sophisticated string representation, for example, one that takes into account your formatting preferences or the culture (the locale), then you should implement the **IFormattable** interface.
    
* System.Object class members

    * ToSting
    * GetHashCode
    * Equals
    * Finalize
    * GetType
    * MemberwiseClone
    
* `System.Type` also provides the entry point into .NET’s reflection technology.
    
* C# does not support multiple inheritance with classes, but it allows multiple inheritance with interfaces.
    
* By declaring a base class method as `virtual`, you allow the method to be overridden in any derived classes.
    
* It is also permitted to declare a property as `virtual`.
    
* In C#, functions are not `virtual` by default but (aside from constructors) can be explicitly declared as `virtual`. This follows the C++ methodology: For performance reasons, functions are not virtual unless indicated. In Java, by contrast, all functions are virtual.
    
* With polymorphism, the method that is invoked is defined dynamically and not during compile time. The compiler creates a virtual method table (vtable) that lists the methods that can be invoked during runtime, and it invokes the method based on the type at runtime.
    
* If a method with the same signature is declared in both base and derived classes but the methods are not declared with the modifiers virtual and override, respectively, then the derived class version is said to hide the base class version.
    
* `new public void Move(Position newPosition)`

* Instead of using the new keyword, you can also rename the method or override the method of the base class if it is declared virtual and serves the same purpose. However, in case other methods already invoke this method, a simple rename can lead to breaking other code.

* C# has a special syntax for calling base versions of a method from a derived class:

```c#
    base.<MethodName>
```

* C# allows both classes and methods to be declared as abstract. An abstract class cannot be instantiated, whereas an abstract method does not have an implementation and must be overridden in any nonabstract derived class. 
    
* An abstract method is automatically virtual. If any class contains any abstract methods, that class is also abstract and must be declared as such.
    
* Adding the `sealed` modifier to a class doesn’t allow you to create a subclass of it. Sealing a method means it’s not possible to override this method.
    
* With a sealed class, the compiler knows that derived classes are not possible, and thus the virtual table used for virtual methods can be reduced or eliminated, which can increase performance. The string class is sealed.
    
* Compiler supplies default zeroing out constructors for all the classes.
    
* **Modifiers** are keywords that can be applied to a type or a member. Modifiers can indicate the visibility of a method, such as public or private, or the nature of an item, such as whether a method is virtual or abstract.
    * public
    * protected
    * internal
    * private
    * protected internal
    * private protected (new with C\# 7.2)
    
* Type definitions can be internal or public, depending on whether you want the type to be visible outside its containing assembly. Types can not be protected, private, or protected internal because these visibility levels would be meaningless for a type contained in a namespace.
    
* Following other modifiers can be applied to members of Types.
    * new - hides an inherited member with the same signature.
    * static - does not operate on a specific instance of the class.
    * virtual - member can be overridden by a derived class.
    * abstract - A virtual member that defines signature but doesn’t provide an implementation.
    * override - overrides an inherited virtual or abstract member.
    * sealed - class cannot be inherited, properties and methods cannot be overridden.
    * extern - member is implemented externally, in a different language.
    
* **Interfaces**: By deriving from an interface, a class is declaring that it implements certain functions.
    
* **System.IDisposable**: IDisposable contains one method, `Dispose`, which is intended to be implemented by classes to clean up resources.
    
* An interface can contain only _declarations_ of methods, properties, indexers, and events.
    
* Interface members are always implicitly public, and they cannot be declared as virtual.
    
* Two important operators related to inheritance: the `is` and `as` operators.
    
* The `as` operator returns a reference to the object. However, it never throws an `InvalidCastException`. Instead, it returns null in case the object is not of the type asked for.
    
* The `is` operator returns true or false, depending on whether the condition is fulfilled and the object is of the specified type.
    
## Generics

* Generics are more than a part of the C# programming language; they are deeply integrated with the IL (Intermediate Language) code in the assemblies.
    
* There’s a big difference between C++ templates and .NET generics. With C++ templates, the source code of the template is required when a template is instantiated with a specific type. The C++ compiler generates separate binary code for each type that is an instance of a specific template. Unlike C++ templates, generics are not only a construct of the C# language but are defined with the Common Language Runtime (CLR). This makes it possible to instantiate generics with a specific type in Visual Basic even though the generic class was defined with C#.
    
*   * **System.Collections** - non-generic collections
    * **System.Collections.Generic** - generic collections
    
* The conversion from a value type to a reference type is known as **boxing**. A boxed value type can be converted to a value type by using **unboxing**.
    
* **Binary Code Reuse**: Generics enable better binary code reuse. A generic class can be defined once and can be instantiated with many different types. Unlike C++ templates, it is not necessary to access the source code.
    
* The `GetEnumerator` method makes use of the yield statement for creating an enumerator type.
    
* It is not possible to assign `null` to a generic type. In this case, the keyword `default` can be used.
    
* **Constraints**: If the generic class needs to invoke some methods from the generic type, you have to add constraints.
    
```c#
    public class DocumentManager<T> where T: IDocument
    // The above constraint implies that the type using the generic class must implement IDocument interface.
```
    
* Static members of generic classes are shared with only one instantiation of the class, and they require special attention.
    
* Prior to .NET 4, generic interfaces were `invariant`. .NET 4 added important changes for generic interfaces and generic delegates: `covariance` and `contra-variance`.
    
* Covariance and contra-variance are used for the conversion of types with arguments and return types.
    
* With .NET, parameter types are covariant. Return types of methods are contra-variant.
    
* Since C# 4, the language is extended to support covariance and contra-variance with generic interfaces and generic delegates.
    
* An example of a generic struct in the .NET Framework is `Nullable<T>`.
    
* C# provides the `checked` and `unchecked` operators. If you mark a block of code as `checked`, the CLR enforces overflow checking, throwing an `OverflowException` if an overflow occurs. `unchecked` is the default behavior.
    
* The `is` operator allows you to check whether an object is compatible with a specific type.
    
* C# 7 extends the `is` operator with pattern matching. You can check for constants, types, and var.

```c#
    if (i is 42)
    if (o is Person p)
```

* The `as` operator is used to perform explicit type conversions of reference types.
    
* The `as` operator allows you to perform a safe type conversion in a single step without the need to first test the type using the `is` operator and then perform the conversion.
    
* By default, unsafe code is not allowed. You need to specify the `AllowUnsafeBlocks` in the csproj project file.

```c#
    unsafe
    {
        Console.WriteLine(sizeof(Point));
    }
```

* The `typeof` operator returns a `System.Type` object representing a specified type. This is useful when you want to use reflection to find information about an object dynamically.
    
* The index operator doesn’t require an integer within the brackets. Index operators can be defined with any type.
    
* When you use the C# keyword `?` with the type declaration, `int?`, the compiler resolves this to use the generic type `Nullable<int>`.
    
* `BigInteger` is a struct that contains a number of any size. The namespace for `BigInteger` is `System.Numeric`.
    
* C# provides a `checked` operator that you can use to test whether an operation causes an arithmetic overflow.

```c#
    int i = checked((int)val);
```    
