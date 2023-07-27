#ifndef Stack_h 
#define Stack_h

#include <iostream>
#include <string>

using namespace std;


class EmptyStackException 
{
    
private:
    string errMsg;

public:
    EmptyStackException(const string& err)
    {
        errMsg = err;
    }
    string getError()
    {
        return errMsg;
    }
};



template <typename T>

class Stack 
{

private:
    T* Stack_array; // The array that will change type based on constructor argument Stack<T> (will fill in T with a type.)
    int cap; // Our capacity
    int size_marker = -1; // Our size

public:

    Stack(int Desired_capacity = 4); // Default constructor, cap set to 4 if no argument is given.
    
    ~Stack() // Obligatory Destructor
    {
        
    }
    
    T& pop()
    {
        if(size_marker == -1) 
        {
            throw EmptyStackException("caught EmptyStackException\n"); // Will only go if the Stack attempting to be popped is empty.
        }
        else
        {
            T& popped_element = Stack_array[size_marker];
            size_marker--; // Reduced size but not capacity, next push will then overwrite the element that was popped.
            return popped_element;
        }
    }
    
    void push(const T& element)
    {
        if(size_marker+1 == cap) // If we reached the current capacity.
        {
            
            T* temp_stack_array = new T[cap];
            
            for(int copying = 0; copying < size(); copying++) // Copies Stack contents into a temporary storage
            {
                temp_stack_array[copying] = Stack_array[copying];
            }
            
            delete[] Stack_array; // Delete the maxed out Stack
            
            cap = cap * 2;
            
            Stack_array = new T[cap]; // Make a new Stack array that has twice the capacity as the old one.
            
            for(int pasting = 0; pasting < size_marker+1; pasting++) // Paste over the old contents
            {
                Stack_array[pasting] = temp_stack_array[pasting];
            }
            
            delete[] temp_stack_array; // Get rid of the temporary storage
        }
        
        Stack_array[size_marker+1] = element;
        
        size_marker++;
    }
    
    bool empty()
    {
        if(size_marker < 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
        
    }
    
    int size()
    {
        return size_marker+1;
    }
    
    int capacity()
    {
        return cap;
    }
    
    
    
    
};

template <typename T>
Stack<T>::Stack(int Desired_capacity) // Outside of class body constructor
{
    cap = Desired_capacity; // Changes default capcity to whatever is put as an argument.
    Stack_array = new T[cap]; // Make a Stack array as big as the constructor's capacity and type.
}

#endif