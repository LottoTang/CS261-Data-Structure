#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>

#include "IndexRecord.h"
#include "IndexMap.h"

using namespace std;

int main()
{
    cout << "----------------Section 3----------------" << endl << endl;;
    ifstream inFile ("GreatExpectations.txt");
    string temp = "";
    int bookPage = 1;
    int wordNum = 1;
    IndexMap bookContent;

    //start building index of the contents of book
    clock_t startTime = clock();
    //read word to temp
    while (inFile >> temp)
    {
        if (temp != "----------------------------------------")
        {
            //all transform to lowercase
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            //add to IndexMap
            bookContent.add(temp, bookPage, wordNum);
            wordNum++;
        }
        else
        {
            //advance page number; reset wordNum to 1
            bookPage++;
            wordNum = 1;
        }
    }
    clock_t endTime = clock();
    double seconds = static_cast<double>(endTime - startTime)/ CLOCKS_PER_SEC;
    cout << "The time (1 trial) for this function is: " << seconds << " seconds." << endl << endl;
    cout << "Number of keys stored in the index (distinct words): " << bookContent.numKeys() << "." << endl << endl;
    IndexRecord fathers = bookContent.get("fathers");
    cout << fathers << endl << endl;

    cout << "----------------Section 4----------------" << endl << endl;
    bookContent.findWordPairs("great", "expectations");
    cout << endl << endl;

    cout << "----------------Section 5----------------" << endl << endl;
    cout << "The first word on page 100 is : " << bookContent.firstWordOnPage(100) << endl << endl;

    cout << "----------------End----------------" << endl;
    return 0;
}
