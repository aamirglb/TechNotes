Beautiful C++

30 core guidelines
1. Write in ISO Standard C++
2. Where there is a choice, prefer default arguments over overloading
3. Don't define a default constructor that only initializes data members; use in-class member initalizers instead
4. Avoid trivial getters and setters
5. Declare one name (only) per declaration

* ISO Standard C++ has a very small library compared to languages like C# and Java.

* Stability over decades is a feature.

* API design is a valuable skill. Naming is hard.

* Overload resolution is a tricky beast to master. Nearly two percent of the C++20 standard is devoted to defining how overload resolution works

* There are three types of implicit conversion sequence:
    * standard conversion sequence 
        * exact match, promotion and conversion. These three ranks are C concepts and are unavoidable if compatibility with C is to be maintained.
    * user-defined conversion sequence
        * nonexplicit constructor, nonexplicit conversion operator
    * ellipsis conversion sequence

* You should make an interface easy to use correctly and hard to use incorrectly.

* 
