//----------------------------------------------------------
// CS260 Assignment 3 Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may not be republished without approval.
//----------------------------------------------------------

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <fstream>
using namespace std;

//Assignment 3, Part 1&2 Knum: K01203846

//Turn loops off for the duration of this file.
//You are to use recursion for any repetition.
//Make sure to do any other includes before these defines.
#define for DONOTUSETHIS
#define while DONOTUSETHIS
#define goto DONOTUSETHIS

/**
 * @brief List node for AddressLinkedList
 */
template <class T>
struct StackNode
{
    T data;
    StackNode* next;

    StackNode();
    StackNode(const T& value);
};


/**
 * @brief Stack based on a linked list
 */
template <class T>
class Stack
{
private:
    StackNode<T>* top;

public:
    /**
     * @brief Construct empty stack
     */
    Stack();

    /**
     * @brief Copy constructor
     *
     * Implement if you need it, otherwise not required
     * Declared to prevent default shallow copy
     */
    Stack(const Stack<T>& other);

    /**
     * @brief Assignment Operator
     *
     * Implement if you need it, otherwise not required
     * Declared to prevent default shallow copy
     */
    Stack<T>& operator=(const Stack<T>& other);

    /**
     * @brief Destructor
     */
    ~Stack();

    /**
     * @brief recursively copy from other stack
     */
    void recursiveCopy(StackNode<T>*otherNode);

    /**
     * @brief remove all the nodes recursively for Destructor
     */
    void recursiveDelete(StackNode<T> *other);

    /**
     * @brief Check if stack is empty
     * @return true if nothing in stack, false otherwise
     */
    bool isEmpty() const;

    /**
     * @brief Add item to stack
     * @param value Item to push a copy of onto the stack
     */
    void push(const T& item);

    /**
     * @brief Remove and return top item from stack
     * @return Item that was at the top of the stack
     * Can throw exception/blow up with assertion if currently empty
     */
    T pop();

    /**
     * @brief Return a copy of the top item on the stack (without removing it)
     * @return Item that is at the top of the stack
     */
    T peek() const;


    /**
     * @brief Output the stack in order to cout
     */
    void print() const;

    /**
     * @brief Output the stack in reverse order to cout
     */
    void reversePrint() const;

    /**
     * @brief Recursive print for print()
     */
    void recursivePrint(StackNode<T> *other) const;

    /**
     * @brief Recursive print for reversePrint()
     */
    void recursivePrintReverse(StackNode<T> *other) const;


};


//--------------------------------------------------------------------
// StackNode implementations
//--------------------------------------------------------------------

template <class T>
StackNode<T>::StackNode() {
    next = nullptr;
    data = T(); //data will be default initialized
}

template <class T>
StackNode<T>::StackNode(const T& value)
    : data(value)
{
    next = nullptr;
}

//--------------------------------------------------------------------
// Stack Implementations
//--------------------------------------------------------------------

template <class T>
Stack<T>::Stack()
{
    top = nullptr;
}

template <class T>
Stack<T>::Stack(const Stack<T>& other)
{
    top = nullptr;
    recursiveCopy(other.top);
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if(this != &other)
    {
        recursiveDelete(top);
        top = nullptr;
        recursiveCopy(other.top);
    }
    return *this;
}

template <class T>
void Stack<T>:: recursiveCopy(StackNode<T>*otherNode)
{
    if (otherNode == nullptr)
        return;
    recursiveCopy(otherNode->next);
    push(otherNode->data);
}

template <class T>
Stack<T>::~Stack()
{
    recursiveDelete(top);
    cout << "Removed all stack elements from " << this << endl;
    top = nullptr;
}

template <class T>
void Stack<T>::recursiveDelete(StackNode<T> *other)
{
    if (other == nullptr)
        return;
    recursiveDelete(other->next);
    delete other;
}

template <class T>
bool Stack<T>::isEmpty() const
{
    if (top == nullptr)
        return true;
    else
        return false;
}

template <class T>
void Stack<T>::push(const T& item)
{
    StackNode<T>* newNode = new StackNode <T>(item);
    if (!newNode)
    {
        cout << "Stack overflow." << endl;
        return;
    }
    newNode->next = top;
    top = newNode;
}

template <class T>
T Stack<T>::pop()
{
    T temp = T();
    if(top == nullptr)
        cout << "Cannot pop from an empty stack." << endl;
    else
    {
        StackNode<T>* removeNode = nullptr;
        removeNode = top;
        temp = top->data;
        top = top->next;
        delete removeNode;
    }
    return temp;
}

template <class T>
T Stack<T>::peek() const
{
    T temp = T();
    if(top == nullptr)
    {
        cout << ("Cannot peek from an empty stack.");
        return temp;
    }

    return (top->data);
}

template <class T>
void Stack<T>::print() const
{
    recursivePrint(top);
}

template <class T>
void Stack<T>::recursivePrint(StackNode<T> *other) const
{
    if (other != nullptr)
    {
        cout << other->data;
        recursivePrint(other->next);
    }
    else
        return;
}

template <class T>
void Stack<T>::reversePrint() const
{
    recursivePrintReverse(top);
}

template <class T>
void Stack<T>::recursivePrintReverse(StackNode<T> *other) const
{
    if (other->next == nullptr)
    {
        cout << other->data;
        return;
    }

    recursivePrintReverse(other->next);
    if (other != nullptr)
        cout << other->data;
}

//--------------------------------------------------------------------
// Helper functions
//--------------------------------------------------------------------

void stackTesting()
{
   Stack<int> s1;
   cout << "Address from Stack 1: " << &s1 << endl << endl;

   cout << "Intentionally popping an empty stack" << endl;
   s1.pop(); // intentionally popping an empty stack;
   cout << endl;

   s1.push(10);
   s1.push(20);
   s1.push(30);
   s1.pop();

   cout << "Print Stack 1 (Top-Bottom & Bottom-Top)" << endl;
   s1.print();
   s1.reversePrint();
   cout << endl;

   //test copy & assignment operator
   Stack<int> s2(s1);
   cout << "Address from Stack 2: " << &s2 << endl;
   cout << "Testing copy operator" << endl;
   s2.print();
   s2.reversePrint();
   cout << endl;

   Stack<int> s3;
   cout << "Address from Stack 3: " << &s3 << endl;
   cout << "Testing assignment operator" << endl;
   s3 = s1;
   s3.print();
   s3.reversePrint();
   cout << endl;
}

//--------------------------------------------------------------------
// All your code before here
//--------------------------------------------------------------------
//Turn loops back on.
//Otherwise whatever file includes this will not be able to use them.
#undef for
#undef while
#undef goto

#endif // STACK_H
