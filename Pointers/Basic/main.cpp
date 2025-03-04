#include <iostream>

// TLDR: A pointer is simply a variable that stores the memory address of another variable or function
// A pointer has: a memory location where it's bound to
//                a type
//                a value (which is an address)
// Every pointer is one of the following: a pointer to an object or function
//                                        a pointer past the end of and object
//                                        the null pointer value for that type
//                                        an invalid pointer value
// A pointer that points to an object represents the address of the first byte in memory occupied by the object
// To use a pointer you must know the type that it points to     
// Pointer declration format is - variable type *pointer name and can be read from right to left
// Ex: int *intPointer - *intPointer is a pointer to an int
// When a pointer is declared, it has garbage values until the pointer is initialized aka it is pointing "anywhere" 
// All pointers should be initialized before use

int main() {
    // Since we don't initalize intPointer to point to nothing.. Printing the value at memory address intPointer produces unexpected output
    int *intPointer;
    std::cout << "The value of uninitialized intPointer is: " << intPointer << std::endl; 
    std::cout << "The memory address of uninitialized intPointer is: " << &intPointer << std::endl;
    std::cout << std::endl;

    // The address doesnt change here but the value does - expected output
    intPointer = nullptr;
    std::cout << "The value of initialized intPointer is: " << intPointer << std::endl; 
    std::cout << "The memory address of initialized intPointer is: " << &intPointer << std::endl;

    // Note: all pointers in a program have the same size.. But they may be pointing to objects or functions of different size
    std::cout << "The size of initialized intPointer is: " << sizeof intPointer << std::endl;
    std::cout << std::endl;

    // Give intPointer a number to point to and print it
    int number = 634634;
    std::cout << "Value of number is: " << number << std::endl;
    std::cout << "The memory address of number is: " << &number << std::endl;

    // intPointer is now pointing to the memory address of number and has the ability to access the value of number from it's memory address
    intPointer = &number;
    std::cout << "Value of intPointer after pointing to number is: " << intPointer << std::endl;

    // In order to access the data we're pointing to we have to dereference the pointer using the dereference operator *
    std::cout << "When we derefernce intPointer using *intPointer we get: " << *intPointer << std::endl;
    std::cout << std::endl;
    
    // These same concepts can be applied to pointers of different types
    std::string string = "This is a string";
    std::string *stringPointer = nullptr;
    std::cout << "The value of string is: " << string << std::endl;
    std::cout << "The memory address of string is: " << &string << std::endl;
    std::cout << "The value of initialized stringPointer is: " << stringPointer << std::endl; 
    std::cout << "The memory address of null stringPointer is: " << &stringPointer << std::endl;
    stringPointer = &string;
    std::cout << "The memory address of string pointer after pointing to string is: " << stringPointer << std::endl;
    std::cout << "When we derefernce stringPointer using *stringPointer we get: " << *stringPointer << std::endl;

    string = "We've changed the value of string";
    std::cout << "When we change the value of string and dereference *stringPointer we get: " << *stringPointer << std::endl;
    std::cout << "But the memory addess of stringPointer is still: " << stringPointer << std::endl;

    return 0;
}