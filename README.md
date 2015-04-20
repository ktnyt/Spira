# SpiraFRP version 1
Yet another C++ library for functional reactive style programming.

C++11 is required for compiling.

Example usage
-------------
Include the header to use SpiraFRP in your project.
No linking required (for now).

```c++
#include "spira.hpp"
```

Streams are "constructed" via constructors.

```c++
spira::stream<int> stream0;
spira::stream<int> stream1(stream0); // Mirror stream0
```

Side-effects may be performed by "bind"ing to the stream.

```c++
std::function<void(int)> some_side_effect([](int value){std::cout << value << std::endl;});
stream1.bind(some_side_effect); // Bind to stream1
```

Bound functions will be called when values are "push"ed.

```c++
stream0.push(0);
stream0.push(1);
```

There are many constructors to perform various FRP like tasks.

```c++
/* Merge Constructor */
template<typename T>
stream<T>::stream(stream<T>& stream1, stream<T>& stream2, DUPLICATES d_flag=DUPLICATES::TAKE);

/* List Merge Constructor */
stream(std::list<stream<T>* > streams, DUPLICATES d_flag=DUPLICATES::TAKE);

/* Filter Constructor */
template<typename T>
stream<T>::stream(stream<T>& stream0, const std::function<bool(T)> filter, DUPLICATES d_flag=DUPLICATES::TAKE);

/* While Constructor */
template<typename T>
stream<T>::stream(stream<T>& stream0, stream<bool>& stream1, TAKE_WHILE t_flag=TAKE_WHILE::TRUE, DUPLICATES d_flag=DUPLICATES::TAKE);

/* Map Constructor */
template<typename T>
template<typename U>
stream<T>::stream(stream<U>& stream0, const std::function<T(U)> map, DUPLICATES d_flag=DUPLICATES::TAKE);

/* Scan Constructor */
template<typename T>
stream<T>::stream(stream<T>& stream0, T seed, const std::function<T(T,T)> scan, DUPLICATES d_flag=DUPLICATES::TAKE);

/* Combine Constructor */
template<typename T>
template<typename T1, typename T2>
stream<std::pair<T1, T2> >::stream(stream<T1>& stream1, stream<T2>& stream2, SAMPLED_BY s_flag=SAMPLED_BY::BOTH, DUPLICATES d_flag=DUPLICATES::TAKE);
```

Future Work
-----------
- Switch `std::make_unique` to `new std::unique_ptr` in C++11/C++0x
- Implement a pointer wrapper for `spira::stream`
- Create `stream` and `property` like BaconJS?
