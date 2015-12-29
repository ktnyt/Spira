[![Build Status](https://travis-ci.org/ktnyt/SpiraFRP.svg)](https://travis-ci.org/ktnyt/SpiraFRP)

# SpiraFRP version 2.1.0
Yet another C++ library for functional reactive style programming inspired by [Bacon.js](https://baconjs.github.io/).

Currently, C++11 is required for compiling.

Concept & Quick usage
---------------------
Include the header to use SpiraFRP in your project.  
Link your binary with `-lspira`.

```c++
#include "spira.hpp"
```

The two core concept of SpiraFRP are `source`s and `stream`s. A `source` is an object which only handles input side-effects and a `stream`, drawn from a source, handles functional style data manipulation and output side-effects.

```c++
spira::source<int> source0;
spira::stream<int> stream0 = source0.draw();
```

Side-effects are handled by "bind"ing to the `stream`.

```c++
std::function<void(int)> some_side_effect([](int value){std::cout << value << std::endl;});
stream0.bind(some_side_effect); // Bind to stream1
```

Bound functions will be called when values are "dump"ed to the `source`.

```c++
source0.dump(0);
source0.dump(42);
```

Data Manipulation
-----------------
The following is a table of available data manipulation operations on a `stream<T>` type, its arguments, and a simple explanation.

|Method |Argument                     |Function                               |
|:------|:----------------------------|:--------------------------------------|
|unique |None                         |Notifies only on value changes.        |
|mirror |None                         |Bypasses values from the parent.       |
|merge  |stream<T>&                   |Merges two streams into one.           |
|filter |std::function<bool(T)>       |Filters stream with given function.    |
|whilst |stream<bool>&                |Notifies while given stream is true.   |
|scan   |T seed, std::function<T(T,T)>|Accumulates values with given function.|
|map    |std::function<U(T)>          |Maps values with given function.       |
|combine|stream<U>&, SAMPLED_BY       |Combines two streams into a pair.      |

These methods can be chained as follows:

```c++
spira::stream<int> stream1 = stream0.mirror().unique();
```

Operators
---------
Most operators are overloaded and can be used on `stream`s as well as its template type.

Comparison Operators
- `==`
- `!=`
- `<`
- `<`
- `<=`
- `>=`

Arithmetic Operators
- `+`
- `-`
- `*`
- `/`
- `%`

Bitwise Operators
- `~`
- `&`
- `^`
- `|`
- `<<`
- `>>`

Logical Operators
- `!`
- `&&`
- `||`

```c++
spira::stream<int> stream2 = stream0 + stream1; // On streams
spira::stream<int> stream3 = stream2 + 42; // With constants
```


Future Work (by priority)
-------------------------
- Documentation
- `std::list` source generator
- boost support for pre-C++11 compilers
