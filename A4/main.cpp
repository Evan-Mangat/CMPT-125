#include <iostream>

#include "Heap.h"

using namespace std;


//________________________
void print(Entry A[], int n) 
{
    for (int i=0; i<n; ++i)
    {
        cout << A[i].toString() << " ";
        cout << "\n";
    }
    
}

//_________________________________
Entry* heapsort1(Entry arr[],int n)
{
   Heap h1(n);
   
   for(int i=0;i<n;i++)
   {
       h1.insert(arr[i]);
   }
   
   arr = h1.heapSort();
   
   Entry* sort_arr = new Entry[n];
   
   for(int i = 0; i < n; i++) // Load the heap sorted array into a new entries array to be returned
   {
      sort_arr[i] = arr[i];
   }
   
   return sort_arr;
}


//_________________________________
Entry* heapsort2(Entry arr[],int n)
{
   Heap h2(n);
   
   h2.make(arr, n);
   
   arr = h2.heapSort();
   
   Entry* sort_arr = new Entry[n];
   
   for(int i = 0; i < n; i++)
   {
      sort_arr[i] = arr[i];
   }
   
   return sort_arr;
}
//______________________


int main()
{
   srand(time(0));

   Entry* E1 = new Entry[15];
   
   Entry* E2 = new Entry[15];
   
   Entry* E3 = new Entry[31];
   
   Entry* E4 = new Entry[31];
   
   //---------------------------------------------------------------------- Array 1
   
   cout<<"Array 1 before sorting:\n";
   print(E1,15);
    
   cout << "------------------------------\n";
   
   E1 = heapsort1(E1, 15);

   cout<<"Array 1 after sorting:\n";
   print(E1, 15);
    
   cout<<endl;
   
   cout << "------------------------------\n";
   
   //---------------------------------------------------------------------- Array 2
   
   cout<<"Array 2 before sorting:\n";
   print(E2,15);
   
   cout << "------------------------------\n";
   
   E2 = heapsort2(E2, 15);
   
   cout<<"Array 2 after sorting:\n";
   print(E2, 15);
   
   cout << "------------------------------\n";

   //---------------------------------------------------------------------- Array 3
   
   cout<<"Array 3 before sorting:\n";
   print(E3,31);
    
   cout << "------------------------------\n";
   
   E3 = heapsort1(E3, 31);

   cout<<"Array 3 after sorting:\n";
   print(E3, 31);
    
   cout<<endl;
   
   cout << "------------------------------\n";
   
   //---------------------------------------------------------------------- Array 4
   
   cout<<"Array 4 before sorting:\n";
   print(E4,31);
   
   cout << "------------------------------\n";
   
   E4 = heapsort2(E4, 31);
   
   cout<<"Array 4 after sorting:\n";
   print(E4, 31);
   
   cout << "------------------------------\n";

   //----------------------------------------------------------------------
   
   cout << "End of array printing!";
   return 0;
}
