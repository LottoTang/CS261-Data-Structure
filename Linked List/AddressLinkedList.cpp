//----------------------------------------------------------
// CS260 Assignment 2 Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may not be republished without approval.
//----------------------------------------------------------

#include "AddressLinkedList.h"

//added codes
#include <iostream>
using namespace std;

//assignment2, Knum: K01203846 ltang3

AddressListNode::AddressListNode() {
    next = nullptr;
    //data will be default initialized
}

AddressListNode::AddressListNode(const Address& value)
    : data(value)
{
    next = nullptr;
}

//added codes for AddressLinkedList

//default constructor
AddressLinkedList::AddressLinkedList()
{
    head = nullptr;
    tail = nullptr;
    length = 0;
}

//copy constructor
AddressLinkedList::AddressLinkedList(const AddressLinkedList& other)
{
    this->length = 0;
    this->head = nullptr;
    this->tail = nullptr;

    if (other.head == nullptr)
        return;

    AddressListNode* temp = other.head;

    while (temp != nullptr)
    {
        AddressListNode *newNode = new AddressListNode(temp->data);
        this->length++;

        if (this->head == nullptr)
        {
            this->head = newNode;
            this->tail = newNode;
            newNode->next = nullptr;
        }
        else
        {
            this->tail->next = newNode;
            this->tail = newNode;
        }

        temp = temp->next;
    }
}

//assignment operator
AddressLinkedList &AddressLinkedList ::operator=(const AddressLinkedList& other)
{
    if (this != &other)
    {
        this->clear();

        AddressListNode *temp = other.head;
        while(temp)
        {
            this->insertEnd(temp->data);
            temp = temp->next;
        }
    }
    return *this;
}

//destructor
AddressLinkedList:: ~AddressLinkedList()
{
    this->clear();
}

//get the length(number of values) in the list
int AddressLinkedList:: listSize() const
 {
     return this->length;
 }

//print the contents within the list
void AddressLinkedList:: print() const
{
   AddressListNode *current = this->head;
    while(current != nullptr)
    {
        cout << current->data;
        current = current->next;
    }
}

//print the contents within the list at specific range
void AddressLinkedList::printRange(int startIndex, int endIndex) const
{
    if ((startIndex < 0 || startIndex > this->length) || (endIndex < startIndex || endIndex > this->length))
        throw out_of_range("Bad index spotted");

    AddressListNode *current = this->head;
    int counter = 0;
    while(counter < startIndex)
    {
        current = current->next;
        counter++;
    }
    while (counter <= endIndex)
    {
        cout << current->data;
        current = current->next;
        counter++;
    }
}

//insert at the head of the linked list
void AddressLinkedList::insertStart(const Address& value)
{
    AddressListNode *newNode = new AddressListNode(value);
    if (this->length == 0)
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        newNode->next = this->head->next;
        this->head = newNode;
    }
    this->length++;
}

//insert at the end of the linked list
void AddressLinkedList::insertEnd(const Address& value)
{
    AddressListNode *newNode = new AddressListNode(value);
    if (this->length == 0)
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->length++;
}

//remove first item of the list, and return Address that was removed
Address AddressLinkedList::removeFirst()
{
    if (this->length == 0)
        throw out_of_range("Cannot remove from an empty list.");
    AddressListNode *removeNode = this->head;
    AddressListNode *temp = removeNode;
    if (this->length == 1)
    {
        this->head = nullptr;
        this->tail = nullptr;
    }
    else
    {
        this->head = removeNode->next;
    }
    delete removeNode;
    this->length--;

    return temp->data;
}

//get the Address at specific index
Address AddressLinkedList:: retrieveAt(int index) const
{
    if (this->length == 0)
        throw out_of_range("Cannot remove from an empty list");
    int counter = 0;
    AddressListNode *current = this->head;
    while (counter != index)
    {
        current = current->next;
        counter++;
    }
    return current->data;
}

//combine 2 lists into 1 (retaining the order), the list being combined will end up emptied
void AddressLinkedList::combine(AddressLinkedList& other)
{
    //just return as no need to combine
    if (other.length == 0)
        return;

    //add the data from other to the end of this->list
    AddressListNode* current = other.head;
    while (current)
    {
        this->insertEnd(current->data);
        current = current->next;
    }
    //clear the other list
    other.clear();
}


/*  extract the matched data from the original list to new list
/   remove the matched data from the original list
/   return the new list */

AddressLinkedList AddressLinkedList::extractAllMatches(const Address& itemToMatch)
{

    AddressLinkedList toExtractList;
    if (this->length == 0)
    {
        cout << "Cannot extract from an empty list." << endl;
        return toExtractList;
    }

    AddressListNode *current = this->head;
    AddressListNode *prev = nullptr;

    while(current->next != nullptr)
    {
        if(current->data.state == itemToMatch.state)
        {

            if(current == this->head)
            {
                toExtractList.insertStart(current->data);
                this->removeFirst();
            }
            else
            {
                //if the last item from the list == itemToMatch.state, need update the tail of original list
                if(current == this->tail)
                {
                    toExtractList.insertEnd(current->data);
                    this->tail = prev;
                    delete current;
                    this->length--;
                }
                else
                {
                    toExtractList.insertEnd(current->data);
                    prev->next = current->next;
                    delete current;
                    current = prev;
                    this->length--;
                }
            }
        }
        prev = current;
        current = current->next;
    }
    return toExtractList;
}



/* interleaves the other list into this one
    return other List to combine - should end up emptied */

void AddressLinkedList::interleave(AddressLinkedList& other)
{
    if(this->length == 0)
    {
        *this = other;
        other.clear();
    }
    else
    {
        AddressListNode *nodeFromB = other.head;
        AddressListNode *nodeFromA = this->head;
        while (nodeFromB != nullptr)
        {
            AddressListNode *newNode = new AddressListNode(nodeFromB->data);
            newNode->next = nodeFromA->next;
            nodeFromA->next = newNode;
            this->length++;

            //check if listA still has other data
            if(newNode->next != nullptr)
            {
                nodeFromA = newNode->next;
                nodeFromB = nodeFromB->next;
            }
            else
            {
                //check if listA does not have other data
                if (newNode->next == nullptr)
                {
                    nodeFromA = newNode;
                    nodeFromB = nodeFromB->next;
                    this->tail = newNode;
                }
            }
        }
        other.clear();
    }
}

//clear function - delete all the nodes within the list and reset the length to 0
void AddressLinkedList::clear()
{
    while(this->head != nullptr)
    {
        AddressListNode* temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}
