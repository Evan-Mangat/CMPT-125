#include <iostream>
#include "Entry.h"
#include "SkipList.h"

using namespace std;

int main()
{
    srand(time(0));
   
    
    SkipList List;
    
    
    // Test 1: Making 8 entries and deleting one of them then printing it again.
    //-------------------------------------------------------------
    cout << "-------------------------------------------------------------" << "\n" << "Starting First Test!" << "\n" << "-------------------------------------------------------------" << "\n";
    
    cout << "Entries being added:\n";
    
    for(int i = 0; i < 7; i++)
    {
        Entry element;
        cout << element.toString() << "\n";
        List.put(element.getKey(), element.getData());
    }
    
    
    Entry tbd;
    tbd.setKey(28);
    tbd.setData("del");
    
    cout << "Adding Entry with key 28 and data 'del'" << "\n";
    
    List.put(tbd.getKey(), tbd.getData());
    
    int size_a = List.size();
    
    cout << "Current Size:" << size_a << "\n" << "\n";
    
    List.print();
    
    cout << "\n";
    
    List.erase(tbd.getKey(), tbd.getData());
    
    
    
    int size_b = List.size();
    
    cout << "New Size: " << size_b << "\n" << "\n";
    
    List.print();
    
    //-------------------------------------------------------------
    // End of Test 1.
    
    // Test 2: find of an element in the list and a find of an element not in the list.
    //-------------------------------------------------------------
    cout << "-------------------------------------------------------------" << "\n" << "Starting Second Test!" << "\n" << "-------------------------------------------------------------" << "\n";
    
    Entry tbf;
    tbf.setKey(39);
    tbf.setData("fnd");
    
    cout << "Adding Entry with key 39 and data 'fnd'" << "\n";
    
    List.put(tbf.getKey(), tbf.getData());
    
    cout << "Searching for this new Entry:\n";
    
    cout << List.find(tbf.getKey()).toString() << "\n";
    
    cout << "Now attempting to search for previously deleted element:\n";
    
    try
    {
    
        if(List.find(28).getData() == "END") // If the special end entry with unique data string "END" is recieved
        {
            throw NoSuchElementException("Error: No such element with given key exists in this SkipList.");
        }
    
    }
    
    catch(NoSuchElementException& ex)
    {
        cout << ex.getError();
    }
    
    cout << "\n\nCurrent state of List:\n_____________________________\n\n";
    
    List.print();
    
    cout << "\n";
    
    
    
    //-------------------------------------------------------------
    // End of Test 2.
    
    // Test 3: greaterEntry() and lessEntry()
    //-------------------------------------------------------------
    cout << "-------------------------------------------------------------" << "\n" << "Starting Third Test!" << "\n" << "-------------------------------------------------------------" << "\n";
    cout << "Searching for Greater Entry and Lesser Entry of 39" << "\n";
    cout << "Greater Entry: " << List.greaterEntry(39).toString() << "\n";
    cout << "Lesser Entry: " << List.lessEntry(39).toString() << "\n";
    
    
    
    //-------------------------------------------------------------
    // End of Test 3.
    
    // Test 4: Fourty Generated Entries.
    //-------------------------------------------------------------
    cout << "-------------------------------------------------------------" << "\n" << "Starting Fourth Test!" << "\n" << "-------------------------------------------------------------" << "\n";

    cout << "Listing all 40 Entries being added into a new SkipList:" << "\n" << "------------------------------------------" << "\n";
    
    SkipList FourtyList;

    for(int i = 0; i < 40; i++)
    {
        Entry element;
        cout << element.toString() << "\n";
        FourtyList.put(element.getKey(), element.getData());
    }

    cout << "Now Printing SkipList:" << "\n" << "___________________________" << "\n" << "\n";

    FourtyList.print();

    //--------------------------------

    cout << "\n" << "Testing Complete!";

    return 0;
}
