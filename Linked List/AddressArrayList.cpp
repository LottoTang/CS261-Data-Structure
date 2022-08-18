//----------------------------------------------------------
// CS260 Assignment 2 Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may not be republished without approval.
//----------------------------------------------------------

#include "AddressArrayList.h"

//added libraries
#include <iostream>
#include <algorithm>

//assignment2, Knum: K01203846 ltang3

using namespace std;

void printListRange(const ArrayList<Address>& list, int startIndex, int endIndex) {
    if(endIndex == -1)
        endIndex = list.listSize() - 1;
    for(int i = startIndex; i <= endIndex; i++) {
        cout << list.retrieveAt(i);
    }
}

template <>
void ArrayList<Address>::combine(ArrayList<Address>& otherList) {
    //FIXME

    //insert otherList at the end of this list
    for(int i = 0; i < otherList.listSize(); i++) //O(n)
    {
        this->insertEnd(otherList.list[i]); //O(1)
    }
    //clear the otherList
    ArrayList temp(otherList.listSize()); //O(n)
    otherList = temp; //O(1)
    otherList.clear(); //O(1)
}

template <>
ArrayList<Address> ArrayList<Address>::extractAllMatches(const Address& itemToMatch) {
    //FIXME - returns empty list
    ArrayList<Address> toExtractList;
    ArrayList<Address> tempList;

    for (int i = 0; i < this->listSize(); i++) //O(n)
    {
        if((this->list+i)->state == itemToMatch.state) //O(1)
            toExtractList.insertEnd(*(this->list+i)); //O(1)
        else
            tempList.insertEnd(*(this->list+i)); //O(1)
    }

    *this = tempList; //O(n)

    return ArrayList<Address> (toExtractList); // O(1)
}
