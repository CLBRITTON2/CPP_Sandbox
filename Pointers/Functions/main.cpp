#include <iostream>
// Avoiding multiple header and source files for the time being
// These are just basic functions so I'll define them here

void DoubleAValue(int *intPointer){
    // Dereference the value at intPointer and multiply it by 2
    *intPointer *= 2;
}

int MultiplyTwoValues(int *firstIntPointer, int *secondIntPointer){
    // Dereference the values at firstIntPointer and secondIntPointer - multiply them - return the result (the value not a pointer to a result)
    return (*firstIntPointer) * (*secondIntPointer);
}

void SwapTwoValues(double *firstDoublePointer, double *secondDoublePointer){
    // Create a place holder to store the initial value of *firstDoublePointer
    // If we set the value of *firstDoublePointer to point to *secondDoublePointer without a place holder we can't point secondDoublePointer back to first
    // We'd be pointing the second double pointer back to itself
    double placeHolder = *firstDoublePointer;
    *firstDoublePointer = *secondDoublePointer;
    *secondDoublePointer = placeHolder;
}

int* AddTwoValues(int *firstIntPointer, int *secondIntPointer){
    // Allocate memory on the heap
    int *resultPointer = new int;
    // Dereference first and second int pointer along with the result pointer - add the values - store them in newly allocated memory
    *resultPointer = *firstIntPointer + *secondIntPointer;
    // Return the pointer
    // NOTE: The caller is now responsible for deleting this memory
    // If the caller doesn't deal with this - a memory leak is born
    return resultPointer;
}

int main() {
    // Initialize a null pointer to avoid garbage data
    int *intPointer = nullptr;
    int numberToDouble = 25;
    std::cout << "The value of number is: " << numberToDouble << std::endl;
    std::cout << "intPointer is currently pointing to: " << intPointer << std::endl;
    // Point intPointer to numberToDouble's memory address
    intPointer = &numberToDouble;
    std::cout << "The address of number is: " << &numberToDouble << " and intPointer is now pointing to address: " << intPointer << std::endl;
    // Pass the pointer to DoubleAValue function
    DoubleAValue(intPointer);
    // Print the dereferenced pointer value
    std::cout << "The value at address intPointer after passing it to DoubleAValue is: " << *intPointer << std::endl;
    std::cout << std::endl;


    int firstNumberToMultiply = 10;
    std::cout << "The value of number 1 is: " << firstNumberToMultiply << " with memory address: " << &firstNumberToMultiply << std::endl;
    int secondNumberToMultiply = 20;
    std::cout << "The value of number 2 is: " << secondNumberToMultiply << " with memory address: " << &secondNumberToMultiply << std::endl;
    int *pointerToNumberOne = &firstNumberToMultiply;
    int *pointerToNumberTwo = &secondNumberToMultiply;
    std::cout << "*pointerToNumberOne is pointing at memory address: " << pointerToNumberOne << std::endl;
    std::cout << "*pointerToNumberTwo is pointing at memory address: " << pointerToNumberTwo << std::endl;
    int result = MultiplyTwoValues(pointerToNumberOne, pointerToNumberTwo);
    std::cout << "Passing these 2 pointers to MultiplyTwoValues function results: " << result << std::endl;
    std::cout << std::endl;


    double firstNumberToSwap = 5.5;
    std::cout << "The value of number 1 is: " << firstNumberToSwap << " with memory address: " << &firstNumberToSwap << std::endl;
    double secondNumberToSwap = 100.100;
    std::cout << "The value of number 2 is: " << secondNumberToSwap << " with memory address: " << &secondNumberToSwap << std::endl;
    double *pointerToFirstNumber = &firstNumberToSwap;
    double *pointerToSecondNumber = &secondNumberToSwap;
    std::cout << "First pointer is pointing to memory address: " << pointerToFirstNumber << std::endl;
    std::cout << "Second pointer is pointing to memory address: " << pointerToSecondNumber << std::endl;
    std::cout << "PRE SWAP: dereferncing first pointer gives: " << *pointerToFirstNumber << " and dereferncing seccond pointer gives: " << *pointerToSecondNumber << std::endl;
    SwapTwoValues(pointerToFirstNumber, pointerToSecondNumber);
    std::cout << "POST SWAP: dereferncing first pointer gives: " << *pointerToFirstNumber << " and dereferncing seccond pointer gives: " << *pointerToSecondNumber << std::endl;
    std::cout << std::endl;

    int firstNumberToAdd = 100;
    std::cout << "The value of number 1 is: " << firstNumberToAdd << " with memory address: " << &firstNumberToAdd << std::endl;
    int secondNumberToAdd = 200;
    std::cout << "The value of number 2 is: " << secondNumberToAdd << " with memory address: " << &secondNumberToAdd << std::endl;
    int *pointerToFirstNumberToAdd = &firstNumberToAdd;
    int *pointerToSecondNumberToAdd = &secondNumberToAdd;
    std::cout << "First pointer is pointing to memory address: " << pointerToFirstNumberToAdd << std::endl;
    std::cout << "Second pointer is pointing to memory address: " << pointerToSecondNumberToAdd << std::endl;
    int *additionResultPointer = AddTwoValues(pointerToFirstNumberToAdd, pointerToSecondNumberToAdd);
    std::cout << "The result pointer is at memory address: " << additionResultPointer << " and dereferencing this pointer gives: " << *additionResultPointer << std::endl;
    // Failing to do this results in a memory leak
    delete additionResultPointer;

    return 0;
}