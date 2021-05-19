# Boost C++ Library

C++ GCC get all warnings: gcc -Q --help=warning   
## Boost.Signals2

* Boost.Signals2 library is an implementation of a _managed_ signals and slots system. Boost.Signals2 allows the user to specify the manner in which multiple return values are combined. 

```
// define a signal with no arguments and void return value
boost::signals2::signal<void ()> sig;

// connect a callback to signal
sig.connect(call_back);

// call all slots
sig();
```

* By default, slots are pushed onto the back of the slot list.

* The Boost.Signals2 library allows slots to be placed into groups that are ordered in some way. supply an extra parameter at the beginning of the connect call that specifies the group. Group values are, by default, ints, and are ordered by the integer < relation.

```
sig.connect(1, World());
sig.connect(0, Hello());
```

* pass argument to slot
```
  boost::signals2::signal<void (float, float)> sig;
```

* Just as slots can receive arguments, they can also return values. These values can then be returned back to the caller of the signal through a _combiner_.

* the default behavior of a signal that has a return type (float, the first template argument given to the boost::signals2::signal class template) is to call all slots and then return a boost::optional containing the result returned by the last slot called. 
