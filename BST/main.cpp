//----------------------------------------------------------
// CS260 Assignment Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may not be republished without approval.
//----------------------------------------------------------
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <ctime>

#include "MySet.h"

using namespace std;

//Assignment 4 BST K01203846

//Returns a vector containing all valid IP addresses starting with 192.168
vector<string> getLocalIPs() {
    vector<string> localIPs;
    localIPs.reserve(256 * 256);		//reserve space in advance to minimize grows

    char ip[] = "192.166.XXX.XXX";
    for(int i = 0; i < 256; i++) {
        for(int j = 0; j < 256; j++) {
            sprintf(ip, "192.168.%03d.%03d", i, j);
            localIPs.push_back(ip);
        }
    }

    return localIPs;
}

int main()
{
    cout << "--------------- Part 1 ---------------" << endl;
    int size = 0;
    string temp;
    MySet<string> setA;
    ifstream inFile("IPListA.txt");
    cout << "Enter the size of IP Addresses to be read: ";
    cin >> size;
     //counting the time for TRIALS times
    int const TRIALS = 1;
    clock_t startTime_p1 = clock();
    for (int i = 0; i < TRIALS; i++)
    {
        for (int i = 0; i < size; i++)
        {
            temp = "";
            getline(inFile, temp);
            setA.add(temp);
        }
    }
    clock_t endTime_p1 = clock();
    double seconds_p1 = static_cast<double>(endTime_p1 - startTime_p1)/ CLOCKS_PER_SEC;
    cout << "The average time (" << TRIALS << " trials) for this function is: " << seconds_p1/TRIALS << " seconds." << endl;
    cout << "The number of items (unique addresses) in setA: " << setA.size() << endl;
    cout << "Duplicated items: " << size - setA.size() << endl;
    cout << "The depth of setA: " << setA.depth() << endl;


    cout << "--------------- Part 2 ---------------" << endl;
    cout << "The smallest item in setA: " << setA.getSmallest() << endl;
    //counting the time for TRIALS times
    int const TRIALS_p2 = 1000000;
    clock_t startTime = clock();
    for (int i = 0; i < TRIALS_p2; i++)
        setA.getSmallest();
    clock_t endTime = clock();
    double seconds = static_cast<double>(endTime - startTime)/ CLOCKS_PER_SEC;
    cout << "The average time (" << TRIALS_p2 << " trials) for this function is: " << seconds/TRIALS << " seconds." << endl;

    cout << "--------------- Part 3 ---------------" << endl;
    MySet<string> setA2(setA);
    for (int i = 0; i < 1; i++)
        cout << setA2.removeLargest() << endl;
    cout << "The number of items (unique addresses) in setA2: " << setA2.size() << endl;

    cout << "--------------- Part 4 ---------------" << endl;
    MySet<string> setA3(setA);
    vector<string> localIPsHolder = getLocalIPs();
    for (int i = 0; i < localIPsHolder.size(); i++)
    {
        if(setA3.contains(localIPsHolder[i]))
            setA3.remove(localIPsHolder[i]);
    }
    cout << "The number of items (unique addresses) in setA3: " << setA3.size() << endl;
    cout << "Removed items (192.168.xxx.xxx): " << size - setA3.size() << endl;

    cout << "--------------- Part 5 ---------------" << endl;
    vector<string> IPsHolder;
    clock_t startTime_p5 = clock();
    IPsHolder = setA.getRange("100.000.000.000", "110.000.000.000");
    clock_t endTime_p5 = clock();
    double seconds_p5 = static_cast<double>(endTime_p5 - startTime_p5)/ CLOCKS_PER_SEC;
    cout << "The time (1 trial) for this function is: " << seconds_p5 << " seconds." << endl;
    cout << "The number of items in the vector: " << IPsHolder.size() << endl;
    cout << "The first 5 IPs from the vector: " << endl;
    for (int i = 0; i < 5; i++)
        cout << IPsHolder[i] << endl;

    cout << "--------------- Part 6 ---------------" << endl;
    MySet<string> setB;
    string tempB;
    ifstream inFile2("IPListB.txt");
    for (int i = 0; i < size; i++)
    {
        tempB = "";
        getline(inFile2, tempB);
        setB.add(tempB);
    }
    clock_t startTime_p6 = clock();
    MySet<string> setAIB(setA.intersectionWith(setB));
    clock_t endTime_p6 = clock();
    double seconds_p6 = static_cast<double>(endTime_p6 - startTime_p6)/ CLOCKS_PER_SEC;
    cout << "The time (1 trial) for this function is: " << seconds_p6 << " seconds." << endl;
    cout << "The number of items (unique addresses) in setAIB: " << setAIB.size() << endl;
    cout << "The smallest item in setAIB: " << setAIB.getSmallest() << endl;

    cout << "--------------- Part 7 ---------------" << endl;
    MySet<string> setAUB(setA.unionWith(setB));
    cout << "The number of items (unique addresses) in setAUB: " << setAUB.size() << endl;
    cout << "The smallest item in setAUB: " << setAUB.getSmallest() << endl;

    cout << "--------------- End ---------------" << endl;

    return 0;
}
