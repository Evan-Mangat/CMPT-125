#include <iostream>
#include <string>

using namespace std;

class EmptyListException 
{
    
private:
    string errMsg;

public:
    EmptyListException(const string& err)
    {
        errMsg = err;
    }
    string getError()
    {
        return errMsg;
    }
};


class InvalidIteratorException 
{
    
private:
    string errMsg;

public:
    InvalidIteratorException(const string& err)
    {
        errMsg = err;
    }
    string getError()
    {
        return errMsg;
    }
};

//------------------------------------------------------------------------------------------------------------------------------

template <typename T>

class ArrayList
{

private:
    T* ArrList;
    int cap = 4;
    int size_marker = 0;
    int front_marker = 0;
    int rear_marker = 0;
    
public:

    ArrayList(int Desired_capacity = 4);
    
    ~ArrayList()
    {
        
    };
    
    //------------------------------------------------------------------------------------------------------------------------------
    
    class Iterator
    {
    private:
    
        int position;
        ArrayList Arr_list_referenced;
    
    public:
    
        Iterator(int pos, ArrayList Arr_list_orig)
        {
            position = pos;
            Arr_list_referenced = Arr_list_orig;
        }
        
        ~Iterator()
        {
            
        };
        
        int current_position()
        {
            return position;
        }
        
        T& operator*()
        {
            int *pos;
            pos = &position;
            T Current_Array = Arr_list_referenced.current_Arrlist();
            return Current_Array[pos];
        }
        
        Iterator operator++()
        {
            if(position == Arr_list_referenced.size())
            {
                position = (position + 1) % Arr_list_referenced.capacity();
            }
            else
            {
            position++;
            }
        }
        
        Iterator operator--()
        {
            position--;
        }
        
        bool operator==(Iterator& i)
        {
           return(position == i.current_position());
        }
        
        bool operator!=(Iterator& i)
        {
           return(position == i.current_position());
        }
        
        
    
    };
    
    
    Iterator begin(ArrayList Arr_list)
    {
        return Iterator(front_marker, Arr_list);
    }
    
    Iterator end(ArrayList Arr_list)
    {
        return Iterator(rear_marker, Arr_list);
    }
        
    
    //------------------------------------------------------------------------------------------------------------------------------
    
    
    
    T& operator[](int i)
    {
        return ArrList[(front_marker + i) % cap];
    }
    
    T& front()
    {
      return ArrList[front_marker];
    }
    
    T& back()
    {
      return ArrList[rear_marker];
    }
    
    void expand()
    {
        T* temp_array_list = new T[cap];
            
        for(int copying = 0; copying < size(); copying++) // Copies List contents into a temporary storage
        {
            temp_array_list[copying] = ArrList[copying];
        }
            
        delete[] ArrList; // Delete the maxed out List
            
        cap = cap * 2;
            
        ArrList = new T[cap]; // Make a new List array that has twice the capacity as the old one.
            
        for(int pasting = 0; pasting < size_marker+1; pasting++) // Paste over the old contents
        {
            ArrList[pasting] = temp_array_list[pasting];
        }
            
        delete[] temp_array_list; // Get rid of the temporary storage
    }
    
    //------------------------------------------------------------------------------------------------------------------------------ Inserts
    void insertFront(const T& e)
    {
        if(size_marker == cap)
        {
            expand();
        }
        
        if(size_marker == 0)
        {
            ArrList[front_marker] = e;
            size_marker++;
        }
        
        else
        {
        front_marker = (front_marker - 1) % cap;
        ArrList[front_marker] = e;
        size_marker++;
        }
        
    }
    
    void insertBack(const T& e)
    {
        if(size_marker == cap)
        {
            expand();
        }
        
        if(size_marker == 0)
        {
            rear_marker = (rear_marker) % cap;
            ArrList[rear_marker] = e;
            size_marker++;
        }
        
        else
        {
        rear_marker = (rear_marker+1) % cap;
        ArrList[rear_marker] = e;
        size_marker++;
        }
        
    }
    
    
    void insert(Iterator p, const T& e)
    {
        if(p.current_position() < 0 || p.current_position() > size_marker) 
        {
            throw InvalidIteratorException("caught InvalidIteratorException\n"); // Will only go if the List attempting to be popped is empty.
        }
        
        if(size_marker == cap)
        {
            expand();
        }
        
        T& temporary_insert_forward_array = new T[size_marker+1 - p.current_position()];
        
        int copy_arr_size = 0;
        
        for(int i = p.current_position(); p <= size_marker; i++)
        {
            temporary_insert_forward_array[copy_arr_size] = ArrList[i];
            copy_arr_size++;
        }
        
        p++;
        
        ArrList[p.current_position() - 1] = e;
        
        for(int paste = 0; paste < copy_arr_size; paste++)
        {
            ArrList[paste + p.current_position()] == temporary_insert_forward_array[paste];
        }
        
        delete[] temporary_insert_forward_array;
        
        size_marker++;
        rear_marker++;
        
    }
    
    void removeFront()
    {
        if(size_marker == 0) 
        {
            throw EmptyListException("caught EmptyListException\n"); // Will only go if the List attempting to be popped is empty.
        }
        else
        {
            front_marker = (front_marker + 1) % cap;
            size_marker--;
        }
    }
    
    
    void removeBack()
    {
        if(size_marker == 0) 
        {
            throw EmptyListException("caught EmptyListException\n"); // Will only go if the List attempting to be popped is empty.
        }
        else
        {
            rear_marker = (rear_marker-1) % cap;
            size_marker--;
        }
    }
    
    void remove(Iterator p)
    {
        if(size_marker == 0) 
        {
            throw EmptyListException("caught EmptyListException\n"); // Will only go if the List attempting to be popped is empty.
        }
        
        
        if(p.current_position() < 0 || p.current_position() > size_marker) 
        {
            throw InvalidIteratorException("caught EmptyListException\n"); // Will only go if the List attempting to be popped is empty.
        }
        
        
        if(p.current_position() == front_marker)
        {
            removeFront();
            return;
        }
        
        if(p.current_position() == rear_marker)
        {
            removeBack();
            return;
        }
        
        // Start copying if it makes it here.
        
        
        T* temporary_insert_forward_array = new T[size_marker];
        
        
        for(int i = 0; i < size_marker; i++) //copy everything in the array
        {
            if(i != p.current_position())
            {
            temporary_insert_forward_array[i] = ArrList[i];
            }
        }
        
        delete[] ArrList;
        
        ArrList = new T[cap];
        
        
        
        for(int paste = 0; paste < size_marker; paste++)
        {
            ArrList[paste] == temporary_insert_forward_array[paste];
        }
        
        delete[] temporary_insert_forward_array;
        
        rear_marker--; //move end back one because we deleted one in between
        size_marker--; // Reduce size by 1
        
        
    }
    
    int size()
    {
        return size_marker;
    }
    
    bool empty()
    {
        return(size == 0);
        
    }
    
    int capacity()
    {
        return cap;
    }
    
    T& current_Arrlist()
    {
        return *ArrList;
    }
    
    
};

template <typename T>

ArrayList<T>::ArrayList(int Desired_capacity)
{
    cap = Desired_capacity;
    ArrList = new T[cap];
}