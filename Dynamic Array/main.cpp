#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "Person.h"

//assignment1, Knum: K01203846 ltang3

int main()
{
    int size = 0, counter_1 = 0, counter_2 = 0, location_1 = -1, location_2 = -1;
    std::ifstream infile;
    infile.open("people.txt");
    if (infile.is_open())
    {
        //section 0
        std::cout << "------------------------Section 0-----------------------" << std::endl;
        std::cout << "Read successful" << std::endl;

        //section 1
        std::cout << "------------------------Section 1-----------------------" << std::endl;

        //get how many records to deal with
        size = getInt();

        //create 2 dynamic arrays
        Person *persons = createArray(size, infile);
        Person *personsSorted = new Person[size];

        //copy persons to personsSorted, and sort it
        std::copy(persons, persons + size, personsSorted);
        std::sort(personsSorted, personsSorted + size);

        //display the last name of the last item in the unsorted array
        std::cout << "Last person read was: " << (persons+size-1)->last << std::endl;
        std::cout << std::endl;

        //section 2
        std::cout << "------------------------Section 2-----------------------" << std::endl;
        //trial for 10000 times
        std::string NAME_1 = "Mertz";
        counter_1 = countLastName(NAME_1, persons, size);
        std::cout << std::endl;

        //section 3
        std::cout << "------------------------Section 3-----------------------" << std::endl;
        //the 1st index for the person with last name "Abbott" in sorted array
        std::string NAME_2 = "Abbott";
        location_1 = binaryFindFirstByLastName(NAME_2, personsSorted, size);
        if (location_1 != -1)
            std::cout << "The 1st index with last name " << NAME_2 << " in the sorted array : " << location_1 << std::endl;
        else
            std::cout << "Not found " << NAME_2 << " in the sorted array!" << std::endl;

        //the last index for the person with last name "Zulauf" in sorted array
        std::string NAME_3 = "Zulauf";
        location_2 = binaryFindLastByLastName(NAME_3, personsSorted, size);
        if (location_2 != -1)
            std::cout << "The last index with last name " << NAME_3 << " in the sorted array : " << location_2 << std::endl;
         else
            std::cout << "Not found " << NAME_3 << " in the sorted array!" << std::endl;
        std::cout << std::endl;

        //section 4
        std::cout << "------------------------Section 4-----------------------" << std::endl;
        //the number of people named "Mertz"
        std::string NAME_4 = "Mertz";
        counter_2 = countLastNameInSorted(NAME_4, personsSorted, size);
        std::cout << std::endl;

        //section 5
        std::cout << "------------------------Section 5-----------------------" << std::endl;
        //sort index 2-7 of the persons by zipcode
        partialZipSort(persons, 2, 7);
        int PARTIAL = 10;
        std::cout << "Print the data in persons array, sorted by zipCode for index 2 - 7." << std::endl;
        std::cout << std::setw(5) << "Index" << std::setw(15) << "Last Name" << std::setw(15) << "First Name" << std::setw(15) << "Zip Code" << std::endl;

        for (int i = 0; i < PARTIAL; i++)
            std::cout << std::setw(5) << i << std::setw(15) << (persons+i)->last << std::setw(15) << (persons+i)->first << std::setw(15) << (persons+i)->zipCode << std::endl;
        std::cout << std::endl;

        //section 6
        std::cout << "------------------------Section 6-----------------------" << std::endl;
        //mergesort to the entire persons array
        nameSort(persons, size);
        PARTIAL = 10;
        std::cout << "Print the data in persons array (first 10 records), sorted by mergesort (based on lastname, followed by firstname)" << std::endl;
        for (int i = 0; i < PARTIAL; i++)
            std::cout << std::setw(5) << i << std::setw(15) << (persons+i)->last << std::setw(15) << (persons+i)->first << std::setw(15) << (persons+i)->zipCode << std::endl;
        std::cout << std::endl;

        //free up the heap memory
        delete []persons;
        delete []personsSorted;
        infile.close();
    }
    else
        std::cout << "Unable to open file" << std::endl;

    return 0;
}
