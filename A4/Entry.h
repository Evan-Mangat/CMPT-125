#ifndef Entry_h 
#define Entry_h



#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;


class Entry
{

private:

int key;
string data;

    
public:

    Entry()
    {
        random();
    }
    
    ~Entry()
    {
        
    }
    
    void random()
    {
        key = rand() % 100;
        string lower_case_letters[26] = {"a","b","c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"}; // Contains all lower case letters
        for(int i = 0; i < 3; i++) // Choose 3 lower case letters for data string
        {
            int added_letter = rand() % 26; 
            data = data + lower_case_letters[added_letter];
        }
    }
    
    int getKey()
    {
        return key;
    }
    
    string getData()
    {
        return data;
    }
    
    string toString()
    {
        stringstream S_key;
        S_key << key;
    
        string string_key;
        S_key >> string_key;
        
        return string_key + ", " + data; // Combines key and data into a single string.
    }
    

};

#endif