#ifndef Heap_h 
#define Heap_h




#include <iostream>
#include <string>
#include <cstdlib>
#include "Entry.h"

using namespace std;

class Heap {
private:
   Entry *arr;
   int capacity;
   int currentSize;

   void swap(Entry *x,Entry *y) // Simple function that swaps the contents of the two variables the function is given
   {
       Entry temp = *x;
       *x = *y;
       *y = temp;
   }
   
   int leftChild(int index) // In an array for a binary tree, the left child's index is 2* the parents index + 1
   {
       return 2*index+1;
   }
   
   int rightChild(int index) // Same as above but +2
   {
       return 2*index+2;
   }
   
   int parent(int index)
   {
        if(index<=0) // If the index is the root or for some reason out of bounds.
        {
            return -1;
        }
        
        return (index-1)/2; // parent is always the childs index - 1 divided by 2 in an array
   }
   
   int getMax3(int current_index,int left,int right) // Basic comparision function between 3 elements.
   {
        if(arr[current_index].getKey()>=arr[left].getKey() && arr[current_index].getKey()>=arr[right].getKey())
        {
            return current_index;
        }
        else if(arr[left].getKey()>arr[current_index].getKey() && arr[left].getKey()>arr[right].getKey())
        {
            return left;
        }
        else
        {
            return right;
        }
    }
    
   int getMax2(int i,int j) // Compares two elements to determine which is larger.
   {
        if(arr[i].getKey()>=arr[j].getKey())
        {
            return i;
        }
        else
        {
            return j;
        }
   }
   
   int getMin(int i, int j) // Determines which is smaller
   {
       if(arr[i].getKey()<arr[j].getKey())
       {
           return i;
       }
       else
       {
           return j;
       }
   }
   
   void increaseSize() // Doubles the size of the array used for the heap.
   {
        Entry *newArr = new Entry[capacity*2];
        for(int i=0; i < capacity; i++)
        {
            newArr[i] = arr[i];
        }
        Entry *temp = arr;
        delete []temp;
        arr = newArr;
        capacity = capacity*2;
       
   }

//--------------------------------------------------------------------------------------------------

public:


   Heap() //default constructor
   {
      capacity=10;//default size
      arr=new Entry[capacity];
      currentSize=0; 
   }
   
   Heap(int totalSize) //parameterized constructor
   {
       capacity = totalSize; // capacity set by parameter
       arr = new Entry[totalSize];
       currentSize=0;
   }
   
   ~Heap()
   {
       delete []arr;
   }
   
   Entry removeMax() // Removes largest element in heap.
   {
        Entry temp = arr[0];
        currentSize--;
        heapifyDown(0);
        return temp;
   }
   
   void insert(Entry e)
   {
        if(size() == capacity) // If the array is maxed out
        {
            increaseSize(); // Double the array in size
        }
       
        arr[currentSize] = e; // Insert new Entry at the end of the array
        currentSize++; // Increase size
        heapifyUp(currentSize-1); // call heapify up to sort array the new entry in the tree.
   }
   
   int size()
   {
       return currentSize;// Return size of the array
   }
   
   bool empty()
   {
       return(currentSize == 0); // Is the size 0?
   }
   
   void make(Entry entries[],int n) // Overide the array with the given array
   {
       for(int i = 0; i < n; i++) // Write over elements of arr with the given array
       {
            arr[i] = entries[i];
       }
       
       currentSize=n; // Reduce size to the size of the given array
       
       for(int i = n-1; i >= 0; i--) // Start at the end of the array for bottom->up creation of heap
       {
            heapifyDown(i); // Starts from the bottom (first loop shouldn't move anything) and countionusly calls heapify down which will swap elements 
       }                    // (starts from child than next loop goes parent->child then grandparent->parent->child, etc for more info look at heapifydown comments.) until a maxheap is formed from the given array.
   }
   
   void decreaseSizeByOne()
   {
       currentSize--; // Lowers size variable
   }
   
   void heapifyUp(int index)
   {
       
        if(index >= currentSize || index<=0) // If given index is out of range for the array
        {
            return;
        }
        
        while(index>0) // While index is not the root of the tree.
        {
            int p = parent(index); // Get the parent of the indexed node
            int i = getMin(index,p); // Obtain which of the two is smaller
            if(i == index) // If the given index node is smaller than its parent than do nothing (Maxheap has largest at the top)
            {
                return;
            }
            swap(&arr[index],&arr[p]); // Since the parent is smaller than the child node swap them.
            index = p; // The index variable moves up the tree so it may keep comparing itself to the next parents.
        }
   
   }
   
   void heapifyDown(int index)
   {
       if(empty())
       {
            return;
       }
       
       if(index<0)
       {
        return;
       }
       while(index<currentSize)
       {
            int l = leftChild(index); // Obtains the left child of the index node
            int r = rightChild(index); // Obtains the right child of the index node
            int i; // Placeholder int that will store the max of the compared nodes.
            
            if(l < currentSize && r < currentSize) // If the node has a right and left child.
            {
                i = getMax3(index,l,r); // compare all 3 to see which is the LARGEST (maxheap)
            }
            else if(l < currentSize) // Else if the node only has a left child.
            {
                i = getMax2(index,l); // Compare the 2 nodes to see which is the largest
            }
            else
            {
                return; // If the node reffered to by index has no children.
            }
            if(i == index) // If index is larger than both its children
            {
                return; // do nothing
            }
            swap(&arr[index],&arr[i]); // Swap current index node with the child that was the largest or in the case of getMax2 only if the child was larger than it in the array.
            index = i; // After swapping the elements so the largest is now the parent, moves down the tree and treats whetever is now at the index of the child as the new parent.
       }
   }
   
   Entry *heapSort()
   {
       for (int i = currentSize-1; i > 0; i--) // Formats heap array so that the returned array in the function goes smallest->largest (as instructed in the assignment) when a maxheap normally goes largest->smallest in its tree.
       {
            swap(&arr[0], &arr[i]);
            decreaseSizeByOne();
            heapifyDown(0);
       }
       return arr;
   }
   
};

#endif