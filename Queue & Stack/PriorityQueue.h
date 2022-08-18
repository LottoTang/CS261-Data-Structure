//----------------------------------------------------------
// CS260 Assignment 3 Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may not be republished without approval.
//----------------------------------------------------------

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

//Assignment 3 PQ K01203846

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;


template<typename T>
class PriorityQueue
{
private:
    T* data;        //array containing the heap
    int capacity;   //maximum size
    int queueSize;   //current logical size

    //Double the size of the underlying array
    void grow();

public:
    //Get a copy of the top item
    T getMax();

    //Rmove the top item and return it
    T removeMax();

    //Add the given value to the heap
    void add(const T& value);

    //Construct a max heap with initial space for 32 items
    PriorityQueue();

    //Destroy the max heap and release memory
    ~PriorityQueue();

    //You do not need to implement copy ctor and assignment operator
    // Declared to prevent accidental use of defaults
    PriorityQueue(const PriorityQueue& other);
    PriorityQueue& operator=(const PriorityQueue& other);

    //added functions
    int largestChildIndex(int current) const;

    bool full() const;

    bool empty() const;

    void displayQueue() const;

    int showQueueSize() const;

    int showQueueCapacity() const;

};


//--------------------------------------------------------------------
// PriorityQueue implementations
//--------------------------------------------------------------------

template <class T>
void PriorityQueue<T>::grow()
{
    T *temp = new T[capacity*2];
    for(int i = 0; i < capacity; i++)
        temp[i] = data[i];
    capacity = capacity * 2;
    delete[] data;
    data = temp;
}


template <class T>
PriorityQueue<T>::PriorityQueue()
{
    queueSize = 0;
    capacity = 32;
    data = new T[capacity];
}

template <class T>
PriorityQueue<T>::~PriorityQueue()
{
    delete [] data;
    cout << "Removed all items in the Priority Queue" << endl;
}

template <class T>
T PriorityQueue<T>::getMax()
{
    return data[0];
}

template <class T>
int PriorityQueue<T>::largestChildIndex(int current) const
{
    int leftChild = current*2+1;
    int rightChild = current*2+2;

    if (leftChild > queueSize || rightChild > queueSize)
        return -1;
    if(leftChild < queueSize && rightChild >= queueSize)
        return leftChild;
    if(data[leftChild] > data[rightChild])
        return leftChild;
    else
        return rightChild;
}

template <class T>
void PriorityQueue<T>::add(const T& value)
{
    if(queueSize == capacity)
        grow();

    ///TODO - add to bottom of heap
    data[queueSize] = value;
    /// then swap our way up until current location is root
    int newIndex = queueSize;
    int parentIndex = (newIndex-1)/2;
    /// and increase logical size of heap
    while(value > data[parentIndex]  && parentIndex >= 0)
    {
        std::swap(data[newIndex], data[parentIndex]);
        newIndex = parentIndex;
        parentIndex = (newIndex-1)/2;
    }
    queueSize++;
}

template <class T>
T PriorityQueue<T>::removeMax()
{
    T origMax = T();
    if(queueSize == 0)
    {
        cout << "Cannot remove top from the empty Priority Queue" << endl;
        return origMax;
    }
    else
    {

        ///TODO
        /// Swap first and last elements and reduce size
        origMax = data[0];
        std::swap(data[0], data[queueSize-1]);
        queueSize--;
        /// Until the promoted value is in valid location, swap it with largest child
        int current = 0;
        int largestChild = largestChildIndex(current);
        while (largestChild != -1)
        {
            if (data[current] < data[largestChild])
            {
                std::swap(data[current], data[largestChild]);
                current = largestChild;
                largestChild = largestChildIndex(current);
            }
            else
                largestChild = -1;
        }
        /// Return old first element
        return origMax;
    }
}

template <class T>
bool PriorityQueue<T>::full() const
{
    if(queueSize == capacity)
        return true;
    else
        return false;
}

template <class T>
bool PriorityQueue<T>::empty() const
{
    if (queueSize == 0)
        return true;
    else
        return false;
}

template <class T>
void PriorityQueue<T>::displayQueue() const
{
    for (int i = 0; i < queueSize; i++)
        cout << data[i] << " ";
}

template <class T>
int PriorityQueue<T>:: showQueueSize() const
{
    return queueSize;
}

template <class T>
int PriorityQueue<T>:: showQueueCapacity() const
{
    return capacity;
}

//--------------------------------------------------------------------
// Helper functions implementations
//--------------------------------------------------------------------

void testingPQ()
{
    PriorityQueue<int> intPQ;
    //intentionally test for removing an empty PQ
    intPQ.removeMax();

    //auto fill up the PQ
    int pqCapacity = 32;
    srand(static_cast<unsigned>(time(nullptr)));
    cout << "Testing empty() function: " << (intPQ.empty() ? "True" : "False") << endl;
    for (int i = 0; i < pqCapacity; i++)
    {
        //auto generate number in between 1 - 100
        int value = rand() % 100 + 1;
        intPQ.add(value);
    }

    cout << "Testing full() function: " << (intPQ.full() ? "True" : "False") << endl;

    cout << "Testing grow() function" << endl;
    intPQ.add(8);

    cout << "Showing the updated PQ capacity: " << intPQ.showQueueCapacity() << endl;

    cout << "Display all queue elements" << endl;
    intPQ.displayQueue();

    cout << endl;
    cout << "Testing removeMax() function" << endl;
    cout << intPQ.removeMax() << endl;

    cout << "Testing getMax() function after removeMax()" << endl;
    cout << intPQ.getMax() << endl;

    cout << "Showing the updated PQ queue size: " << intPQ.showQueueSize() << endl;

    cout << "------------------------------------------------------------------" << endl;
    PriorityQueue<string> stringPQ;
    //intentionally test for removing an empty PQ
    intPQ.removeMax();

    //auto fill up the PQ
    int stringCapacity = 32;
    string temp = "";
    srand(static_cast<unsigned>(time(nullptr)));
    cout << "Testing empty() function: " << (stringPQ.empty() ? "True" : "False") << endl;
    for (int i = 0; i < stringCapacity; i++)
    {
        //auto generate number in between 65-90
        temp = "";
        for (int j = 0; j < 2; j++)
        {
            int value = 65 + (rand() % 26) ;
            temp = temp + char(value);
        }

        stringPQ.add(temp);
    }

    cout << "Testing full() function: " << (stringPQ.full() ? "True" : "False") << endl;

    cout << "Testing grow() function" << endl;
    stringPQ.add("ZZ");

    cout << "Showing the updated PQ capacity: " << stringPQ.showQueueCapacity() << endl;

    cout << "Display all queue elements" << endl;
    stringPQ.displayQueue();

    cout << endl;
    cout << "Testing removeMax() function" << endl;
    cout << stringPQ.removeMax() << endl;

    cout << "Testing getMax() function after removeMax()" << endl;
    cout << stringPQ.getMax() << endl;

    cout << "Showing the updated PQ queue size: " << stringPQ.showQueueSize() << endl;

}


#endif // PRIORITYQUEUE_H
