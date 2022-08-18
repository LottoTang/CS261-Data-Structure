//----------------------------------------------------------
// CS260 Assignment 1 Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may not be republished without approval.
//----------------------------------------------------------
#include "Person.h"
#include <iostream>
#include <fstream>
#include <ctime>

//assignment1, Knum: K01203846 ltang3

using namespace std;

bool operator==(const Person& p1, const Person& p2){
	if(p1.kNum == p2.kNum)
		return true;
	else
		return false;
}

bool operator<(const Person& p1, const Person& p2) {
	if(p1.last < p2.last ||
	   p1.last == p2.last && p1.first < p2.first)
		return true;
	else
		return false;
}

void partialZipSort(Person* array, int start, int end) {
	//TODO
	//selection sort based
	int location;

	//from start to end sort
	for (int i = start; i < end; i++)
    {
        location = i;
        for (int j = i + 1; j < end; j++)
        {
            //sort based on zipCode
            if ((array+j)->zipCode < (array+location)->zipCode)
                location = j;
        }

        std::swap(*(array+i), *(array+location));

    }
}

/** \void nameSort(Person* array, int size)
 *  create Person *temp
 *  Helper function for mergeSortInternal
 */

void nameSort(Person* array, int size) {
    //TODO
    clock_t startTime = clock();

    //start of the block function
    int const TRIALS = 1;
    for (int i = 0; i < TRIALS; i++)
    {
        Person *temp = new Person[size];
        //call mergeSortInternal
        mergeSortInternal(array, 0, size-1, temp);
        delete []temp;
    }
    //end of the block function

    clock_t endTime = clock();

    double seconds = static_cast<double>(endTime - startTime)/ CLOCKS_PER_SEC;

    //show the average time required
    cout << "The average time (" << TRIALS << " trials) for this function is: " << seconds/TRIALS << " seconds." << endl;
}


int countLastName(const std::string& lastName, const Person* array, int size) {
	//TODO
	clock_t startTime = clock();

	//start of the block function

    int const TRIALS = 1;
	int counter;

	//loop for larger runs to get measurable time
	for (int i = 0; i < TRIALS; i++)
    {
        counter = 0;

        for (int j = 0; j < size; j++)
        {
            if ((array+j)->last == lastName)
                counter++;
        }
    }

    cout << "The number of people in the persons array with the name '" << lastName << "' is: " << counter << endl;

    //end of the block function

    clock_t endTime = clock();

    double seconds = static_cast<double>(endTime - startTime)/ CLOCKS_PER_SEC;

    //show the average time required
    cout << "The average time (" << TRIALS << " trials) for this function is: " << seconds/TRIALS << " seconds." << endl;

	return counter;

}

int binaryFindFirstByLastName(const std::string& value, const Person* array, int size) {
	//TODO
	int low = 0;
	int high = size - 1;
	int location = -1;

	//binary search
	while (low <= high)
    {
        int mid = (low + high)/2;

        if ((array+mid)->last == value)
        {
            location = mid;
            //update high as mid-1 if found, continue searching between low to high
            high = mid - 1;
        }
        else
            if ((array+mid)->last < value)
                low = mid + 1;
            else
                high = mid - 1;
    }

	//return the 1st index of the value in the array
	return location;
}


int binaryFindLastByLastName(const std::string& value, const Person* array, int size) {
	//TODO
	int low = 0;
	int high = size - 1;
	int location = -1;

	//binary search
	while (low <= high)
    {
        int mid = (low + high)/2;

        if ((array+mid)->last == value)
        {
            location = mid;
            //update low as mid+1 if found, continue searching between mid to high
            low = mid + 1;
        }
        else
            if ((array+mid)->last < value)
                low = mid + 1;
            else
                high = mid - 1;
    }
    //return the last index of the value in the array
	return location;
}


int countLastNameInSorted(std::string lastName, const Person* array, int size) {
	//TODO
    clock_t startTime = clock();

	//start of the block function

    int const TRIALS = 1;
	int counter;

	//loop for larger runs to get measurable time
	for (int i = 0; i < TRIALS; i++)
    {
        counter = -1;
        int location_1 = binaryFindFirstByLastName(lastName, array, size);
        int location_2 = binaryFindLastByLastName(lastName, array, size);
        counter = location_2 - location_1;
        //if found any record with that name
        if (counter != -1)
            counter = location_2 - location_1 + 1;
        //case for location_2 - location_1 = -1: not found
        else
            counter = 0;
    }

    cout << "The number of people in the personsSorted array with the name '" << lastName << "' is: " << counter << endl;

    //end of the block function
    clock_t endTime = clock();
    double seconds = static_cast<double>(endTime - startTime)/ CLOCKS_PER_SEC;

    //show the average time required
    cout << "The average time (" << TRIALS << " trials) for this function is: " << seconds/TRIALS << " seconds." << endl;
    return counter;
}

/** \int getInt()
 *  validate int type input in range [1-100000]
 *  return size
 */

int getInt() {
    int size = 0;
    int const MIN_RECORD = 1;
    int const MAX_RECORD = 100000;
    bool valid;

    //data validation
    do
    {
        valid = true;
        cout << "How many records to be read and worked with?: [1-100000]: ";
        cin >> size;
        if (cin.fail() || size < MIN_RECORD || size > MAX_RECORD) {
            if (cin.fail())
                cout << "Please enter an integer!" << endl;
            else
                cout << "Please enter within range!" << endl;

            cin.clear();
            cin.ignore(10000, '\n');
            valid = false;
        }
    } while (!valid);

    //return valid integer input
    return size;
}

/** \Person *createArray(int size, ifstream &infile)
 *  create the dynamic array for persons
 *  assign the infile's content to persons accordingly
 *  return array (as a pointer)
 */

Person *createArray(int size, ifstream &infile) {
    //create dynamic array
    Person *array = new Person[size];
    char const COMMA = ',';

    //assign content from infile to array accordingly
    for (int i = 0; i < size; i++)
    {
        getline(infile, (array+i)->kNum, COMMA);
        getline(infile, (array+i)->last, COMMA);
        getline(infile, (array+i)->first, COMMA);
        infile >> (array+i)->zipCode;
    }

    return array;
}

/** \void mergeFunc(Person *array, int low, int mid, int high, Person *temp)
 *  merge the array (separated into half) back into one
 *  mergesort based on lastname, followed by firstname
 *  if both lastname, firstname are the same, this case is not handled as not required by assignment
 */

void mergeFunc(Person *array, int low, int mid, int high, Person *temp) {

    int i = low;
    int j = mid + 1;
    int k = 0;

    //while still have comparable items between the separated array
    while (i <= mid && j <= high)
    {
        //comparing lastname
        if ((array+i)->last < (array+j)->last)
        {
            *(temp+k) = *(array+i);
            k++;
            i++;
        }
        else
        {
            if ((array+i)->last > (array+j)->last)
            {
                *(temp+k) = *(array+j);
                k++;
                j++;
            }
            else
            {
                //starting from here (lastname are equal), check firstname
                if ((array+i)->first < (array+j)->first)
                {
                    *(temp+k) = *(array+i);
                    k++;
                    i++;
                }
                else
                {
                    *(temp+k) = *(array+j);
                    k++;
                    j++;
                }
            }
        }
    }

    //the other half of the array (j-part) is empty
    while (i <= mid)
    {
        *(temp+k) = *(array+i);
        k++;
        i++;
    }

    //the other half of the array (i-part) is empty
    while (j <= high)
    {
        *(temp+k) = *(array+j);
        k++;
        j++;
    }

    //assign the temp array back to array
    //consider the case as 0 is not always be the low
    for (i = low; i <= high; i++)
        *(array+i) = *(temp+i-low);
}

/** \void mergeSortInternal (Person *array, int low, int high, Person *temp)
 *  set up base case for the merge sort (only 0/1 items left for each separated array)
 *  recursively call itself to divide the array into 0/1 items left
 *  once divided, call mergeFunc to merge back the 2 arrays
 */

void mergeSortInternal (Person *array, int low, int high, Person *temp) {

    //base case
    if (low >= high)
        return;

    int mid = (low + high)/2;

    //1st division: the left part of the array, divide the array recursively
    mergeSortInternal(array, low, mid, temp);

    //1st division: the right part of the array, divide the array recursively
    mergeSortInternal(array, mid+1, high, temp);

    mergeFunc(array, low, mid, high, temp);
}

