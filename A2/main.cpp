#include <iostream>
#include <string>
#include "ArrayUtils.h"
#include "Stack.h"
#include "Employee.h"

using namespace std;


//-------------------------------------------------------------------------------------

void testStackUnderflow()
{

    try
    {
        Stack<int> Numbers(2);
        Numbers.push(1);
        Numbers.pop();
        Numbers.pop(); // Throws the exception
        cout << "Did not catch exception\n"; // Shouldn't get here.
    }

    catch(EmptyStackException& es) // Catches it.
    {
        cout << es.getError();

    }

}

//-------------------------------------------------------------------------------------

void testStackGrowth() 
{
    Stack<double> Doubles(4);
    
    for(int pushed = 0; pushed < 5;  pushed++) // Pushing the initial 5 items
    {
        Doubles.push(pushed);
        cout << pushed << " ";
    }
    
    cout << "\nCapacity is: " << Doubles.capacity() << "\n"; // Check that capacity increased
    
    for(int more_pushed = 5; more_pushed < 9;  more_pushed++) // Pushing another 4
    {
        Doubles.push(more_pushed);
        cout << more_pushed << " ";
    }
    
    cout << "\nCapacity is: " << Doubles.capacity() << "\n"; // Check that it increased again
    
    for(int popping = 0; popping < 9; popping++) // Pop everything we added.
    {
        double popped_element = Doubles.pop();
        cout << popped_element << " ";
    }
    
    cout << "\n";
}

//-------------------------------------------------------------------------------------

void testReverseIntegers() // Tests if reverse works on an array of ints.
{
    int Integer_array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    
    for(int original_array_print = 0; original_array_print < 12; original_array_print++)
    {
        cout << Integer_array[original_array_print] << " "; // Printing the ordered ints.
    }
    
    cout << "\n";
    
    ArrayUtils<int>::reverse(Integer_array, 12); // reversing
    
    for(int reversed_array_print = 0; reversed_array_print < 12; reversed_array_print++)
    {
        cout << Integer_array[reversed_array_print] << " "; // printing the now reversed array.
    }
    
    cout << "\n";
}

//-------------------------------------------------------------------------------------

void testReverseStrings() // Same as above but using strings, no need to repeat the same comments twice.
{
    string String_array[12] = {"Ardvark","Bat","Cat","Dinosaur","Elephant","Flamingo","Giraffe","Hippo","Iguana","Jaguar","Koala","Lion"};
    
    for(int original_array_print = 0; original_array_print < 12; original_array_print++)
    {
        cout << String_array[original_array_print] << " ";
    }
    
    cout << "\n";
    
    ArrayUtils<string>::reverse(String_array, 12);
    
    for(int reversed_array_print = 0; reversed_array_print < 12; reversed_array_print++)
    {
        cout << String_array[reversed_array_print] << " ";
    }
    
    cout << "\n";
}

//-------------------------------------------------------------------------------------

void testReverseEmployees()
{
    Employee *employees[12];    // Making an array of pointers to Employee class objects
    
    employees[0] = new Employee("Josh", 21);
    employees[1] = new Employee("Rebecca", 137);
    employees[2] = new Employee("Matt", 60);
    employees[3] = new Employee("Daniel", 174);
    employees[4] = new Employee("Evan", 153);
    employees[5] = new Employee("Alex", 62);
    employees[6] = new Employee("Steve", 178);
    employees[7] = new Employee("Kim", 35);
    employees[8] = new Employee("Selene", 48);
    employees[9] = new Employee("Damien", 54);
    employees[10] = new Employee("Dwight", 13);
    employees[11] = new Employee("Jim", 6);
    
    string employee_strings[12] = {}; // The array of strings we will build and eventually reverse.
    
    for(int ordered_Employees = 0; ordered_Employees < 12; ordered_Employees++) // Printing the employees in order using toString() member function while also building an array of strings to reverse.
    {
        cout << employees[ordered_Employees]->toString() << ", ";
        
        employee_strings[ordered_Employees] = employees[ordered_Employees]->toString();
    }
    
    cout << "\n";
    
    
    
    ArrayUtils<string>::reverse(employee_strings, 12); // Reversing the array we built in the previous for loop
    
    for(int reverse_Employees = 0; reverse_Employees < 12; reverse_Employees++)
    {
        cout << employee_strings[reverse_Employees] << ", ";
    }
    
    cout << "\n";
    
    
    
}

//-------------------------------------------------------------------------------------

int main() // Just test function calls and some additional text output to make the tests visually clearer and more readable.
{
    cout << "------Now Testing StackUnderflow()------\n";
    testStackUnderflow();
    cout << "\n";
    cout << "------Now Testing StackGrowth()------\n";
    testStackGrowth();
    cout << "\n";
    cout << "------Now Testing ReverseIntegers()------\n";
    testReverseIntegers();
    cout << "\n";
    cout << "------Now Testing ReverseStrings()------\n";
    testReverseStrings();
    cout << "\n";
    cout << "------Now TestingReverseEmployees()------\n";
    testReverseEmployees();
    cout << "\n";
    cout << "------ Testing Complete! ------";
    
    return 0;
}
