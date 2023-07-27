#include <iostream>
#include <string>
#include "Animal.h"


using namespace std;

// Using Allman bracket style
//-----------------------------------------------------------

class Dog: public Animal
{
    
public:

  Dog(int num) : Animal(num)
  { 
      
  }
  
  
  string const noise()
  {
      return "bark";
  }
  
  int const repeats()
  {
      return 5;
  }
  
  
    
};

//-----------------------------------------------------------

class Sheep: public Animal
{
    

public:

  Sheep(int num) : Animal(num)
  {
   
  }
  
  
  string const noise()
  {
      return "baaa";
  }
  
  int const repeats()
  {
      return 4;
  }
 
  
    
};

//-----------------------------------------------------------

class Seal: public Animal
{

public:

  Seal(int num) : Animal(num)
  {
     
  }
  
  
  string const noise()
  {
      return "arf";
  }
  
  int const repeats()
  {
      return 3;
  }
  
    
};

//-----------------------------------------------------------
class Elephant: public Animal
{
    
public:

  Elephant(int num) : Animal(num)
  {
   
  }
  
  
  string const noise()
  {
      return "pavoot";
  }
  
  int const repeats()
  {
      return 2;
  }
  
  
    
};

//-----------------------------------------------------------

int main()
{
    Animal general(6);
    Dog doggo(13);
    Sheep mareep(8);
    Seal polar(3);
    Elephant dumbo(36);
    
    general.print();
    doggo.print();
    mareep.print();
    polar.print();
    dumbo.print();
    cout << "\n";
    
    Animal *animals[10];
    
    animals[0] = new Dog(12);
    animals[1] = new Animal(2);
    animals[2] = new Sheep(3);
    animals[3] = new Seal(4);
    animals[4] = new Elephant(15);
    animals[5] = new Dog(9);
    animals[6] = new Sheep(3);
    animals[7] = new Animal(1);
    animals[8] = new Seal(10);
    animals[9] = new Seal(6);
    
    for(int i = 0; i < 10; i++)
    {
     animals[i]->print(); // Do to using pointers using -> instead of .
    }
    
    for(int j = 0; j < 10; j++)
    {
        delete animals[j]; // deleting everything allocated with new.
    }
    
    return 0;
}
