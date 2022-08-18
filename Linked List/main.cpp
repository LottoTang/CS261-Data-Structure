//----------------------------------------------------------
// CS260 Assignment 2 Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may not be republished without approval.
//----------------------------------------------------------
#include <iostream>
#include <ctime>
#include <fstream>

#include "Address.h"
#include "ArrayList.h"
#include "AddressArrayList.h"
#include "AddressLinkedList.h"

using namespace std;

//assignment2, Knum: K01203846 ltang3

//added library
#include<bits/stdc++.h>


int main()
{
    cout << "-------------------- Part 0 --------------------" << endl;

    int size = 0;
    cout << "Enter problem size: ";
    cin >> size;
    cout << endl;

    ArrayList<Address> aListA;
    ArrayList<Address> aListB;

    //open 2 external text files
    AddressFactory aFactory("25000AddressesA.txt");
    AddressFactory aFactory2("25000AddressesB.txt");

    for(int i = 0; i < size / 2; i++) {
        Address a = aFactory.getNext();
        aListA.insertEnd(a);
        Address a2 = aFactory2.getNext();
        aListB.insertEnd(a2);
    }
	
    cout << "-------------------- Part 1 --------------------" << endl;

    cout << "(Before) The number of items in aListA: " << aListA.listSize() << endl;
    cout << "(Before) The number of items in aListB: " << aListB.listSize() << endl << endl;

    aListA.combine(aListB);

    if (size >= 4)
    {
        cout << "Address with index " << size/2-2 << " to " << size/2+1 << " from aListA: " << endl;
        printListRange(aListA, size/2-2, size/2+1);
    }
    else
        cout << "The size is less than 4! Cannot display the last two from original listA and first two from original listB as requested!" << endl;

    cout << "(After) The number of items in aListA: " << aListA.listSize() << endl;
    cout << "(After) The number of items in aListB: " << aListB.listSize() << endl << endl;

    cout << "-------------------- Part 2 --------------------" << endl;

    ArrayList<Address> aListC;
    Address searchAddress;

    searchAddress.state = "OR";

    cout << "(Before) The number of items in aListA: " << aListA.listSize() << endl;
    cout << "(Before) The number of items in aListC: " << aListC.listSize() << endl << endl;

    aListC = aListA.extractAllMatches(searchAddress);

    cout << "(After) The number of items in aListA: " << aListA.listSize() << endl;
    cout << "(After) The number of items in aListC: " << aListC.listSize() << endl << endl;

    cout << "-------------------- Part 3 --------------------" << endl;

    //make 2 new AddressFactory objects
    AddressFactory aFactory_part3("25000AddressesA.txt");
    AddressFactory aFactory2_part3("25000AddressesB.txt");

    AddressLinkedList linkListA;
    AddressLinkedList linkListB;

    for(int i = 0; i < size / 2; i++)
    {
        Address a_part3 = aFactory_part3.getNext();
        linkListA.insertEnd(a_part3);
        Address a2_part3 = aFactory2_part3.getNext();
        linkListB.insertEnd(a2_part3);
    }

    if (linkListA.listSize() >= 5 && linkListB.listSize() >=5)
    {
        cout << "linkListA indexes 2-4:" << endl;
        linkListA.printRange(2,4);

        cout << endl;

        cout << "linkListB indexes 2-4:" << endl;
        linkListB.printRange(2,4);
    }
    else
        cout << "Cannot display items 3-5 as requested due to insufficient data." << endl;

    cout << "-------------------- Part 4 --------------------" << endl;

    AddressLinkedList linkListC(linkListA);
    AddressLinkedList linkListD(linkListB);

    cout << "(Before) The number of items in linkListC: " << linkListC.listSize() << endl;
    cout << "(Before) The number of items in linkListD: " << linkListD.listSize() << endl << endl;

    linkListC.combine(linkListD);

    if (size >= 4)
    {
        cout << "Address with index " << size/2-2 << " to " << size/2+1 << " from linkListC: " << endl;
        linkListC.printRange(size/2-2, size/2+1);
    }
    else
        cout << "The size is less than 4! Cannot display the last two from original linkListC and first two from original linkListD as requested!" << endl;

    cout << endl;

    cout << "(After) The number of items in linkListC: " << linkListC.listSize() << endl;
    cout << "(After) The number of items in linkListD: " << linkListD.listSize() << endl << endl;

    cout << "-------------------- Part 5 --------------------" << endl;

    AddressLinkedList linkListE;
    Address searchAddress_part5;

    searchAddress_part5.state = "OR";

    cout << "(Before) The number of items in linkListC: " << linkListC.listSize() << endl;
    cout << "(Before) The number of items in linkListE: " << linkListE.listSize() << endl << endl;

    linkListE = linkListC.extractAllMatches(searchAddress_part5);

    cout << "(After) The number of items in linkListC: " << linkListC.listSize() << endl;
    cout << "(After) The number of items in linkListE: " << linkListE.listSize() << endl << endl;

    if(linkListE.listSize() < 2)
        cout << "Cannot display the first two records of linkListE due to insufficient data." << endl;
    else
    {
        cout << "The first two records of linkList E:" << endl;
        linkListE.printRange(0, 1);
    }

    cout << "-------------------- Part 6 --------------------" << endl;

    cout << "(Before) The first five records from linkListA " << endl;
    linkListA.printRange(0,4);
    cout << endl;

    linkListA.interleave(linkListB);

    cout << "(After) The first five records from linkListA " << endl;
    linkListA.printRange(0,4);

    cout << "-------------------- End --------------------" << endl;

    return 0;
}
