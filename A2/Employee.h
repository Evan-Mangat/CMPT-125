#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Employee
{
private: // Make sure variables are immutable

    string name;
    int ID;
    
public:

  Employee(string Employee_name, int ID_number)
  {
    name = Employee_name;
    ID = ID_number;
  }
  
  string toString() const //getter for ID and Name. Used to help print in testing.
  {
    stringstream S_ID;
    S_ID << ID;
    
    string String_ID;
    S_ID >> String_ID;
    
    return name + " " + String_ID;
  }
  
};