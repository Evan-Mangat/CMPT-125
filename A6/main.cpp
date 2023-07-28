#include <iostream>
#include "AVLTree.h"

using namespace std;

int main()
{
    
    // Test 1
    //----------------------------------------
    cout << "Starting Test 1\n-----------------------------" << endl;
    
    AVL First;
    int seven[7] = {3,6,10,17,28,47,59};
    for(int j = 0; j < 7; j++)
    {
        First.put(seven[j]);
    }
    First.print();
    cout << "\nNow Erasing Entry with Key 17\n\n";
    First.erase(17);
    First.print();
    
    
    cout << "\nNow Finding Entry with Key 28\n";
    cout << "Entry found with key: " << First.find(28)->data << endl;
    
    
    
    cout << "\nNow Finding Entry with Key 35 (shouldn't exist)\n";
    if(First.find(35)->data == -1)
    {
        cout << "Error: Reference to data of Node end. Therefore no Entry with given key exists in this Tree.\n" << endl;
    }
    else
    {
        cout << "This message should not display. If it does then it is not working right\n";
    }
    
    
    
    
    // Test 2
    //-----------------------------------------------------------------------
    
    cout << "Starting Test 2\n-----------------------------" << endl;
    cout << "Original Tree:\n" << endl;
    int random[15] = {5,7,8,12,1,4,3,9,15,19,20,25,35,28,50}; 
    AVL obj;


    for(int i=0;i<15;i++)
    {
        obj.put(random[i]);
    }

    obj.print();
    cout<<endl<<endl;
    
    cout << "Going to erase following Nodes: 5, 9, 12, 19, 25\n" << endl;
    
    obj.erase(12);
    obj.erase(9);
    obj.erase(5);
    obj.erase(25);
    obj.erase(19);
    
    cout << "New Tree:\n" << endl;
    
    obj.print();

    return 0;
}
