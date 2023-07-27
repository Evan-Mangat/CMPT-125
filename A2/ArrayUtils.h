#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

template <typename T>

class ArrayUtils
{

public:

    ArrayUtils();
    
    ~ArrayUtils();
    
    static T& reverse(T Original_array[], int size)
    {
        Stack<T> new_stack(size);
        
        for(int c = 0; c < size; c++) // Copies array elements to a new stack
        {
            new_stack.push(Original_array[c]);
        }
        
        for(int p = 0; p < size; p++)
        {
            Original_array[p] = new_stack.pop(); // Overwrites array elements with the popped elements of the Stack effectivly reversing the array.
        }
        
        return *Original_array;
        
        
    }
    
    
};