# C++ Pointers and Memory - Ben Saks (CppCon 2020)

Notes from Ben Saks' CppCon 2020 talk: "Back to Basics: Pointers and Memory"

Video: [Back to Basics: Pointers and Memory - Ben Saks - CppCon 2020](https://www.youtube.com/watch?v=rqVWj0aVSxg)

## Introduction

C++ inherited language support for pointers and arrays from C. In modern C++, we usually try to avoid "raw" C-style pointers and arrays in favor of:

- Smart pointers such as `unique_ptr` and `shared_ptr`
- Container classes such as `vector` and `list`

These modern alternatives offer several advantages:

- Richer, more powerful interfaces
- More clearly express programmer's intent
- Automatic resource management through destructors

However, understanding how pointers work remains essential for:
- Interfacing with C libraries
- Working with hardware
- Understanding the underlying mechanisms of smart pointers and containers

## Pointers and Addresses

A pointer object holds the address of another object:

- A pointer type includes the type of object to which it points
- For any object `x`, the expression `&x` returns the address of `x`
- If `x` has type `T`, then `&x` has type "pointer to `T`" (written as `T*`)
- You can modify a pointer's value (with some exceptions)
- A pointer with a "null" value doesn't point to anything

### Null Pointers

You can set a pointer to "null" using `NULL`, `0`, or `nullptr`:

```cpp
int* p = nullptr;  // Preferred in modern C++
int* q = NULL;     // C-style null pointer constant
int* r = 0;        // Also works, but less clear
```

`nullptr` is preferred because:
- `NULL` is a constant from C that's either defined as `0` or `0L`
- `nullptr` has a unique type that can convert to any pointer type but not to an integer type
- Passing `NULL` to overloaded functions could produce unexpected results
- C++11 added the `nullptr` keyword to help avoid surprises

## Pointer Dereferencing

You use the unary `*` operator to dereference a pointer:

```cpp
int x = 42;
int* p = &x;       // p points to x
*p = 100;          // Modifies the value of x through p
std::cout << x;    // Outputs 100
```

- If `p` is a pointer, then `*p` is the object to which it points
- Dereferencing a null pointer produces undefined behavior
- A pointer doesn't usually have the same lifetime as the object to which it points

## Arrays and Pointer Arithmetic

C++ arrays are similar to arrays in other languages:

```cpp
int numbers[5] = {1, 2, 3, 4, 5};
int first = numbers[0];  // Access using square bracket notation
```

You can also access array elements using pointers:

```cpp
int* p = numbers;        // Array "decays" to pointer to first element
int second = *(p + 1);   // Points to second element
```

Incrementing a pointer causes it to point to the next element, regardless of the size of each element:

```cpp
char* cp = new char[10];
cp++;       // Adds 1 byte to the pointer (assuming char is 1 byte)

int* ip = new int[10];
ip++;       // Adds 4 bytes to the pointer (assuming int is 4 bytes)
```

Pointer arithmetic rules:
- Adding an integer to a pointer yields another pointer
- Subtracting two pointers gives the distance between the elements
- Subtracting two pointers is valid only if they both point to elements of the same array
- You can safely point to the element "one beyond the end" of an array for checking if you've reached the end, but accessing that element produces undefined behavior

## Array Decay

Arrays and pointers have an interesting relationship:

```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* p = arr;  // This works because arrays "decay" into pointers
```

Array decay refers to the implicit conversion of an array to a pointer to its first element:

- Subscripting arrays with `[]` is really a pointer operation rather than an array operation
- The compiler treats `arr` as a "pointer to int" when used in most contexts
- The conversion is temporary and happens during expression evaluation
- You can assign an array to a pointer, but you can't assign a pointer (or anything else) to an entire array

How to tell if something is an array or a pointer:
- You can assign an array to a pointer, but you can't assign anything to an entire array
- `sizeof` and `alignof` produce different results for arrays and pointers

## Size and Alignment Considerations

`size_t` and `ptrdiff_t` are important types for memory operations:

- `size_t` is the result of the `sizeof` operator
  - It's always an unsigned integer type (never negative)
  - May be `long` or even `long long` on some platforms
  - Represents the size of objects in bytes

- `ptrdiff_t` is the result of subtracting two pointers
  - It's always a signed value
  - Should be no larger than necessary

Tips for working with these types:
- Don't mix `size_t` and `ptrdiff_t` in comparisons as it can lead to accidental signed-to-unsigned conversions
- When using `auto` with `size_t` and `ptrdiff_t`, keep an eye on which values are signed and unsigned
- C++20 provides a non-member `ssize()` function for getting the size of a container as a signed value

## Pointer Const Qualifiers

Understanding `const` and `volatile` with pointers:

```cpp
const int* p;      // Pointer to const int (can't modify the int)
int* const p;      // Const pointer to int (can't change where p points)
const int* const p; // Const pointer to const int (can't do either)
```

- `const` and `volatile` are CV-qualifiers
- Type conversions involving `volatile` are similar to those involving `const`
- A `const` expression is not a CV-qualifier and can't be used everywhere that you can use `const`

## Pointer Type Conversions

C++ is stricter about pointer conversions than C:

- Accidental pointer conversions were a common source of errors in early C programs
- C++ treats such conversions as errors
- You can silence compiler complaints using casts like `reinterpret_cast`, but this doesn't make the conversion safe

Inheritance-related conversions:
- A pointer to a derived class can safely convert to a pointer to a base class
- The opposite (base to derived) doesn't work without an explicit cast

## Void Pointers

The `void*` type serves as a generic data pointer type:

```cpp
void* generic_ptr;  // Can point to any data object
```

Functions like `malloc` and `free` from the C standard library use `void*`:

```cpp
int* p = (int*)malloc(sizeof(int) * 10);  // C-style cast
int* q = static_cast<int*>(malloc(sizeof(int) * 10));  // C++ style
```

C++ attempts to reduce potential issues by:
- Allowing conversions to `void*`
- Disallowing conversions from `void*` without a cast
- Requiring a cast where C doesn't

Limitations of `void*`:
- You can't increment or decrement a `void*` because the compiler doesn't know the size
- You can't dereference `void*` because it's an incomplete type
- Converting from `void*` to a typed pointer is not safe

## References

References provide an alternative to pointers for associating names with objects:

```cpp
int x = 42;
int& r = x;  // r refers to x
r = 100;     // Changes the value of x to 100
```

Key characteristics of references:
- A reference is essentially a pointer that's automatically dereferenced each time it's used
- Once you create a reference, you can't change it to refer to something else
- Since you can't change what a reference refers to, you must give it a value when you define it
- There is no reference equivalent to a null pointer
- A pointer with a null value might point to something else in the future, but a reference refers to the same object for its entire lifetime

### Why Use References?

References are valuable for several reasons:

- They can provide friendlier function interfaces where overloaded operators look and feel like built-in operators
- They're especially useful in C++ because overloaded operators can't accept operands of enumeration types (they're viewed as user-defined objects)

```cpp
// With references, the ++ operator returns the incremented object by reference
T& operator++() {
    // increment
    return *this;
}

// Without references, the postfix ++ doesn't return void; it returns the pre-incremented object by value
T operator++(int) {
    T temp = *this;
    ++(*this);
    return temp;
}
```

Guidelines for choosing between pointers and references:
- Pointers are better for iteration and implementing data structures
- References are better for creating function interfaces

## Summary

- C++ inherited pointers from C but added references and smart pointers for safer memory management
- Understanding raw pointers remains essential for interfacing with C libraries and hardware
- Key concepts include pointer dereferencing, null pointers, array decay, and pointer arithmetic
- References provide an alternative to pointers with different constraints and use cases
- Proper understanding of type conversions, const qualifiers, and void pointers helps avoid common pitfalls