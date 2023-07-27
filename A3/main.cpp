#include <iostream>
#include <string>
#include "ArrayList.h"

using namespace std;


void testArrayListUnderflow()
{
    // 1st try block
    
    try
    {
        ArrayList<int> Numbers(4);
        Numbers.insertFront(1);
        Numbers.removeFront();
        Numbers.removeFront(); // Throws the exception
        cout << "Did not catch exception\n"; // Shouldn't get here.
    }

    catch(EmptyListException& es) // Catches it.
    {
        cout << es.getError();

    }
    
    //2nd try block
    
    try
    {
        ArrayList<int> Numbers(4);
        Numbers.insertBack(1);
        Numbers.removeBack();
        Numbers.removeBack(); // Throws the exception
        cout << "Did not catch exception\n"; // Shouldn't get here.
    }

    catch(EmptyListException& es) // Catches it.
    {
        cout << es.getError();

    }
    
    //3rd try block
    
    try
    {
        ArrayList<int> Numbers(4);
        
        
        ArrayList<int>::Iterator beginning = Numbers.begin(Numbers);
        
        Numbers.insertBack(1);
        Numbers.remove(beginning);
        Numbers.remove(beginning); // Throws the exception
        cout << "Did not catch exception\n"; // Shouldn't get here.
    }

    catch(EmptyListException& es) // Catches it.
    {
        cout << es.getError();

    }
}
//---------------------------------------------------------------------------------------------------------------------------
void testIntegerIterator()
{
    ArrayList<int> L(4);
    
    L.insertBack(1);
    L.insertBack(2);
    L.insertBack(3);
    L.insertBack(4);
    L.insertBack(5);
    L.insertBack(6);
    
    
    
    ArrayList<int>::Iterator ending = L.end(L);
    
    for(ArrayList<int>::Iterator iter = L.begin(L); iter.current_position() != ending.current_position(); ++iter) 
    {
        cout << *iter << " ";
    }
    cout << endl;
    
    L.removeFront();
    L.removeFront();
    L.removeFront();
    L.insertBack(1);
    L.insertBack(2);
    L.insertBack(3);
    
    for(ArrayList<int>::Iterator iter = L.begin(L); iter.current_position() != ending.current_position(); ++iter) 
    {
        cout << *iter << " ";
    }
    cout << endl;
    
}

//---------------------------------------------------------------------------------------------------------------------------
int main()
{
    cout << "Now testing ArrayListUnderflow()\n-------------------------------------\n";
    testArrayListUnderflow();
    cout << "Now testing IntegerIterator()\n-------------------------------------\n";
    testIntegerIterator();
    cout << "All tests complete!\n";
    return 0;
}
