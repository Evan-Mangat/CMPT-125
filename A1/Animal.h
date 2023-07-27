#include <iostream>
#include <string>

using namespace std;

class Animal 
{
    
private:

    int age;
    
public:

  Animal(int num)
  {
    age = num; 
  }
  
  virtual ~Animal()
  {
      
  }
  
  virtual string const noise()
  {
    return "grunt";
  }
  
  int const repeats()
  {
    return 3;
  }
  
  int ageInMonths()
  {
    return age;
  }
  
  void print()
  {
    cout << ageInMonths() << " ";
    
    for(int i = 0; i < repeats(); i++)
    {
        cout << noise() << " ";
    }
    
    cout << "\n";
  }
    
};

