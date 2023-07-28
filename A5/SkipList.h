#include <iostream>
#include <string>
#include <cstdlib>
#include <bits/stdc++.h>
#include "Entry.h"

using namespace std;


class QuadNode
{
    
private:

    Entry elem;
    
    QuadNode* prev;
    QuadNode* next;
    QuadNode* below;
    QuadNode* above;
    
    friend class SkipList;
};

//---------------------------------------------------------

class NoSuchElementException
{
    
private:
    string errMsg;

public:
    NoSuchElementException(const string& err)
    {
        errMsg = err;
    }
    string getError()
    {
        return errMsg;
    }
};


//---------------------------------------------------------

class SkipList
{

private:
   
   int currentSize;
   QuadNode* frontSentinel; // Pointer to the top-left node of the skip list.
   QuadNode* tailSentinel; // Pointer to top-right node of the skip list.
   QuadNode* position; // An iterator that will help with some functions below.
   Entry* end; // Special entry that is used 
   QuadNode* lowerFloorIterator;
   int height;
    
public:
    
    //-----------------------------------------------------------------------------------
    // Constructor
    //-----------------------------------------------------------------------------------
    SkipList()
    {
      QuadNode* defaultfrontSentinel = new QuadNode;
      defaultfrontSentinel->below = NULL;
      defaultfrontSentinel->prev = NULL;
      defaultfrontSentinel->above = NULL;
      defaultfrontSentinel->elem.setKey(INT_MIN);
      defaultfrontSentinel->elem.setData("-inf");
      
      
      QuadNode* defaultTailSentinel = new QuadNode;
      defaultTailSentinel->below = NULL;
      defaultTailSentinel->next = NULL;
      defaultTailSentinel->above = NULL;
      defaultTailSentinel->elem.setKey(INT_MAX);
      defaultTailSentinel->elem.setData("inf");
      
      defaultfrontSentinel->next = defaultTailSentinel;
      defaultTailSentinel->prev = defaultfrontSentinel;
      
      frontSentinel = defaultfrontSentinel;
      tailSentinel = defaultTailSentinel;
      
      Entry* ending = new Entry;
      end = ending;
      end->setData("END"); // Unique data string not producable by any regular entry due to capital letters.
      
      lowerFloorIterator = defaultfrontSentinel; // Set it to the start of the bottom row.
      
      currentSize = 0;
      height = 0;
      position = frontSentinel;
    }
    
    //-----------------------------------------------------------------------------------
    // Position setters.
    //-----------------------------------------------------------------------------------
    
    void resetPosition() //Resets Position to the top left of skiplist. Useful for printing.
    {
        position = frontSentinel;
    }
    
    void setPositionbase() // Sets position to the bottom left corner for insertion purposes
    {
        position = frontSentinel;
        while(position->below != NULL)
        {
            position = position->below;
        }
    }
    
    void setPositionFrontofRow()
    {
        while(position->prev != NULL)
        {
            position = position->prev; // Move position till it reaches the frontSentinel of the row
        }
    }
    
    //-----------------------------------------------------------------------------------
    // Destructor to prevent memory leaks.
    //-----------------------------------------------------------------------------------
    
    ~SkipList()
    {
        resetPosition();
        if(height % 2 == 0) // if height is an even number.
        {
            while(position->above != NULL)
            {
                while(position->next != NULL)
                {
                    QuadNode* CurrentNode = position;
                    position = position->next;
                    delete CurrentNode;
                }
                
                if(position->above != NULL)
                {
                    QuadNode* CurrentNode = position;
                    position = position->above;
                    delete CurrentNode;
                }
                
                while(position->prev != NULL)
                {
                    QuadNode* CurrentNode = position;
                    position = position->prev;
                    delete CurrentNode;
                }
                
                if(position->above != NULL)
                {
                    QuadNode* CurrentNode = position;
                    position = position->above;
                    delete CurrentNode;
                }
            }
        }  
        else // If its odd.
        {
            while(position->above != NULL)
            {
                while(position->next != NULL)
                {
                    QuadNode* CurrentNode = position;
                    position = position->next;
                    delete CurrentNode;
                }
                
                if(position->above != NULL)
                {
                    QuadNode* CurrentNode = position;
                    position = position->above;
                    delete CurrentNode;
                }
                
                while(position->prev != NULL)
                {
                    QuadNode* CurrentNode = position;
                    position = position->prev;
                    delete CurrentNode;
                }
                
                if(position->above != NULL)
                {
                    QuadNode* CurrentNode = position;
                    position = position->above;
                    delete CurrentNode;
                }
            }
            
            while(position->next != NULL)
            {
                QuadNode* CurrentNode = position;
                position = position->next;
                delete CurrentNode;
            }
                
            delete position;
            
        }   
        
    }
    //-----------------------------------------------------------------------------------
    // Coinflip and Level Creation/Deletion
    //-----------------------------------------------------------------------------------
    int coinflip()
    {
        int numberofHeads = 0;
        
        int coin = rand() % 2;
        
        
        if(coin == 0) // treat 0 as heads 1 as tails.
        {
            numberofHeads++;
            
            while(coin == 0)
            {
                coin = rand() % 2;
                if(coin == 0)
                {
                    numberofHeads++;
                }
            }
        }
        
        return numberofHeads;
        
    }
    
    //-----------------------------------------------------------------------------------
    
    void CreateNextLevel() // Moves frontSentinel and tailSentinel up a level and creating new nodes for them above the old ones thus making a new level.
    {
        QuadNode* newfrontSentinel = new QuadNode;
        QuadNode* newtailSentinel = new QuadNode;
        
        frontSentinel->above = newfrontSentinel; // Adjusting the new sentinals values
        newfrontSentinel->below = frontSentinel;
        newfrontSentinel->prev = NULL;
        newfrontSentinel->above = NULL;
        newfrontSentinel->elem = frontSentinel->elem;
        
        
        tailSentinel->above = newtailSentinel; // refer to above comment.
        newtailSentinel->below = tailSentinel;
        newtailSentinel->next = NULL;
        newtailSentinel->above = NULL;
        newtailSentinel->elem = tailSentinel->elem;
        
        newtailSentinel->prev = newfrontSentinel; // Linking them together
        newfrontSentinel->next = newtailSentinel;
        
        frontSentinel = newfrontSentinel; // Change the frontSentinel pointer to always be the one in the top-left of the skip list.
        tailSentinel = newtailSentinel; // Change the tailSentinel pointer to always be the one in the top-right of the skip list.
        
        
        height++; // Increase height to whetever the old height was plus the new level that was created.
        
        
    }
    
    //-----------------------------------------------------------------------------------
    void DeleteTopLevel()
    {
        QuadNode* CurrentHeadNode = frontSentinel;
        frontSentinel = frontSentinel->below;
        delete CurrentHeadNode; // Because they are being de-linked they won't be caught by the Destructor so must be deleted now.
        frontSentinel->above = NULL; // Make sure above now points to NULL as this is the new top left.
        
        QuadNode* CurrentTailNode = tailSentinel;
        tailSentinel = tailSentinel->below;
        delete CurrentTailNode;
        tailSentinel->above = NULL;
        
        resetPosition();
        height--;
    }
    
    //-----------------------------------------------------------------------------------
    // Find()
    //-----------------------------------------------------------------------------------
    
    Entry& find(int k)
    {
        resetPosition();
        while(1 == 1) // Only two ways out. Drops below lowest level and returns NULL or find the element.
        {
            int next_key = position->next->elem.getKey();
            
            if(k == next_key)
            {
                return position->next->elem; //found the element
            }
            
            else if(k > next_key)
            {
                position = position->next; // scan-forward
            }
            
            else if(k < next_key)
            {
                if(position->below == NULL)
                {
                    return *end;
                }
                
                else
                {
                    position = position->below;
                }
            }
        }
    }
    
    //-----------------------------------------------------------------------------------
    // Greater/Less Entry functions
    //-----------------------------------------------------------------------------------
    
    Entry& greaterEntry(int k)
    {
        find(k);
        
        if(find(k).getData() != "END")
        {
            position = position->next; // Move position onto the node with key k
            
            while(position->below != NULL)
            {
                position=position->below;
            }
            
            return position->next->elem;
        }
        
        else
        {
            return *end;
        }
        
    }
    
    Entry& lessEntry(int k) 
    {
        find(k);
        
        if(find(k).getData() != "END")
        {
            position = position->next; // Move position onto the node with key k
            
            while(position->below != NULL)
            {
                position=position->below;
            }
            
            return position->prev->elem;
        }
        
        else
        {
            return *end;
        }
    }
    
    //-----------------------------------------------------------------------------------
    // Put function
    //-----------------------------------------------------------------------------------
    
    void put(int k, string v)
    {
        
        if(find(k).getData() != "END") // if there is an entry in the SkipList with key k
        {
            setPositionbase(); // Start from the bottom list
            
            while(1 == 1) // will eventually end because if the code has made it here than there is an entry in skiplist with key k and it will be on the bottomlevel no matter what.
            {
                if(position->elem.getKey() == k)
                {
                
                    while(position->above != NULL) // keep going up
                    {
                    
                        position->elem.setData(v); // change the data to the string v
                        position = position->above;
                    }
                    
                    position->elem.setData(v); // while loop will end before the last node with key k can have its data changed. Change the last data to the string v
                    return;
                }
                
                else 
                {
                    position = position->next; // keep moving until find entry with "k" key in the bottom row
            
                }    
            }
        }
        

        else
        {
            
            // Step 1 Coin Toss
            int i = coinflip(); // Number of times it comes up heads.
            
            
            // Step 2 Adding lists so height > highest head count
            if(i >= height) // Adding New Lists until the top list is one above the coinflip head count.
            {
                for(int ceiling = height; ceiling <= i; ceiling++)
                {
                    CreateNextLevel();
                }
            }
            
            
            // Step 3 Finding largest key less than k in each list and inserting a new node for k up to Skip List level i.
            
            
            setPositionbase();  // Start at the bottom list.
            
            for(int elevator = 0; elevator <= i; elevator++)
            {
                QuadNode* add = new QuadNode;
                add->elem.setKey(k);
                add->elem.setData(v);
                
                while(position->next->elem.getKey() < k)
                {
                    position = position->next;
                }
                
                //Linking it in (As shown in lecture notes for Linked List) horizontally
                
                //---------------------------------------------------------
                add->prev = position; // make z's prev link point to v
                
                add->next = position->next; // Make z’s next link point to w = v->next
        
                position->next->prev = add; // Make w’s prev link point to z

                position->next = add; //Make v’s next link point to z
                //---------------------------------------------------------
                // Dealing with vertical connections
            
                if(elevator == 0) // If it is a node on the floor
                {
                    add->below = NULL;
                    currentSize++;
                }
                
                else // If added node is above bottom floor
                {
                    while(lowerFloorIterator->elem.getKey() != k) // Get lowerFloorIterator to the first instance of add on bottomlist
                    {
                        lowerFloorIterator = lowerFloorIterator->next;
                    }
                    
                    lowerFloorIterator->above = add; // link the add on the lower floor with the add on the new floor
                    add->below = lowerFloorIterator; // vice versa
                    
                }
                
                if(elevator == i) // If this is the highest level for this node
                {
                    add->above = NULL;
                }
                //---------------------------------------------------------
                // Final step moving up to a new level.
                
                
                lowerFloorIterator = add; // move lowerFloorIterator up a floor.
                setPositionFrontofRow(); // move Position back to the front of the current list row
                position = position->above; // move it up a level.
            }
            
        }
    }
    
    //-----------------------------------------------------------------------------------
    // Erase function
    //-----------------------------------------------------------------------------------
    
    void erase(int k, string v) 
    {
        if(find(k).getData() == "END")
        {
            throw NoSuchElementException("Error: Attempting to delete an element that does not exist.");
        }
        
        else
        {
            // Step 1: Find position of node set to be erased.
            resetPosition();
            find(k);
            position = position->next; // Move position onto the desired element to be deleted.
            
            
            // Step 2: Delinking the node.
            
            //Unlinking a node from a linked list (from lecture notes)
            //---------------------------------------------------------
            position->next->prev = position->prev;
            position->prev->next = position->next;
            //---------------------------------------------------------
            
            while(position->below != NULL)
            {
                QuadNode* CurrentNode = position;
                position = position->below;
                
                delete CurrentNode; // Remove the memory allocated with new by put() function. This is needed because these nodes are delinked completly and as such wouldn't be deleted by the Destructor.
                
                //Unlinking a node from a linked list (from lecture notes)
                //---------------------------------------------------------
                position->next->prev = position->prev;
                position->prev->next = position->next;
                //---------------------------------------------------------
                
            }
            
            QuadNode* CurrentNode = position; // Link a new pointer to the current Node.
            resetPosition(); // Set position back to top left.
            delete CurrentNode; // Delete the final node
            currentSize--;
            
            // Step 3: Checking if there is an exccess amount of empty list levels left. If there isn't nothing happpens.
            
            
            while(position->next->elem.getData() == "inf" && position->below->next->elem.getData() == "inf") // if the current row and row below it are both empty.
            {
                DeleteTopLevel();
            }
            
            
        }
    }
    
    //-----------------------------------------------------------------------------------
    // Size and empty
    //-----------------------------------------------------------------------------------
    int size()
    {
        return currentSize;
    }
    
    bool empty()
    {
        return(currentSize == 0);
    }
    
    
    //-----------------------------------------------------------------------------------
    // Print function
    //-----------------------------------------------------------------------------------
    
    void print()
    {
        setPositionbase();
        
        int arr[currentSize];
        
        for(int i = 0; i < currentSize; i++) // Copy all entries on bottom level into an array.
        {
            position = position->next;
            arr[i] = position->elem.getKey();
        }
        
        resetPosition();
        
        for(int reader = height; reader >= 0; reader--) // Overall loop.
        {
            cout << position->elem.getData();
            
            cout << "--";
            
            position = position->next;
            
            for(int row = 0; row < currentSize; row++)
            {
                
                if(position->elem.getKey() != arr[row]) // print this until the number lines up with bottom row.
                {
                    cout << "--";
                }
                
                else
                {
                    if(position->elem.getKey() < 10)
                    {
                        cout << "0" << position->elem.getKey();
                    }
                    
                    else
                    {
                        cout << position->elem.getKey();
                    }
                    
                    if(position->elem.getData() != "inf") // If not at the end of the row. And by extension the last key was matching.
                    {
                        position = position->next;
                    }
                }
                
                cout << "--"; // Do this regardless as a space between numbers.
            }
            
            
            cout << position->elem.getData();
            
            cout << "\n";
            
            setPositionFrontofRow();
            
            if(position->below != NULL)
            {
                position = position->below;
            }
            
            
        }
    }
    
};