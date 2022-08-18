//----------------------------------------------------------
// CS260 Assignment Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may not be republished without approval.
//----------------------------------------------------------

#include "IndexMap.h"
#include <iostream>
#include <iomanip>

//handle resizing the hash table into a new array with twice as many buckets
void IndexMap::grow()
{
    IndexRecord* oldPtr = buckets;
    int oldNumBuckets = numBuckets;
    numBuckets = 2 * numBuckets;
    buckets = new IndexRecord[numBuckets];
    keyCount = 0;
    for (int i = 0; i < oldNumBuckets; i++)
    {
        if(oldPtr[i].word != EMPTY_CELL && oldPtr[i].word != PREVIOUS_USED_CELL)
        {
            for(int j = 0; j < oldPtr[i].locations.size(); j++)
                add(oldPtr[i].word, oldPtr[i].locations[j].pageNum, oldPtr[i].locations[j].wordNum);
        }
    }
    delete [] oldPtr;
}

//hash function to return the position of the bucket
unsigned int IndexMap::getLocationFor(const std::string& key) const
{
    std::hash<string> hasher;
    unsigned int hashValue = static_cast<unsigned int>(hasher(key));

    //return that mapped onto table
    return hashValue % numBuckets;
}

//Construct HashMap with given number of buckets
IndexMap::IndexMap(int startingBuckets)
{
    keyCount = 0;
    numBuckets = startingBuckets;
    buckets = new IndexRecord[numBuckets];
}

//Destructor
IndexMap::~IndexMap()
{
    delete [] buckets;
}

//copy constructor
IndexMap::IndexMap(const IndexMap &other)
{
    keyCount = 0;
    numBuckets = other.numBuckets;
    buckets = new IndexRecord[numBuckets];
    for (int i = 0; i < numBuckets; i++)
    {
        for(int j = 0; j < other.buckets[i].locations.size(); j++)
            add(other.buckets[i].word, other.buckets[i].locations[j].pageNum, other.buckets[i].locations[j].wordNum);
    }
}

//assignment operator
IndexMap& IndexMap::operator=(const IndexMap& other)
{
    IndexRecord* temp = this->buckets;
    this->numBuckets = other.numBuckets;
    this->buckets = new IndexRecord[this->numBuckets];
    this->keyCount = 0;
    for (int i = 0; i < this->numBuckets; i++)
    {
        for(int j = 0; j < other.buckets[i].locations.size(); j++)
            add(other.buckets[i].word, other.buckets[i].locations[j].pageNum, other.buckets[i].locations[j].wordNum);
    }
    delete [] temp;
    return *this;
}

//Returns true of indicated key is in the map
bool IndexMap::contains(const std::string& key) const
{
    if(key == EMPTY_CELL || key == PREVIOUS_USED_CELL)
        throw invalid_argument("Invalid key");

    int bucketNumber = getLocationFor(key);

    while(buckets[bucketNumber].word != EMPTY_CELL && buckets[bucketNumber].word != PREVIOUS_USED_CELL)
    {
        if(buckets[bucketNumber].word == key)
            return true;
        else
        {
            if(bucketNumber == numBuckets - 1)
                bucketNumber = 0;
            else
                bucketNumber++;
        }
    }
    return false;
}

void IndexMap::add(const std::string& key, int pageNumber, int wordNumber)
{
    if(key == EMPTY_CELL || key == PREVIOUS_USED_CELL)
        throw invalid_argument("Invalid key");

    int bucketNumber = getLocationFor(key);

    if (contains(key))
        buckets[bucketNumber].addLocation(IndexLocation(pageNumber, wordNumber));
    else
    {
        if (keyCount > MAX_LOAD * numBuckets)
            grow();

        while(buckets[bucketNumber].word != EMPTY_CELL && buckets[bucketNumber].word != PREVIOUS_USED_CELL)
        {
            if(bucketNumber == numBuckets - 1)
                bucketNumber = 0;
            else
                bucketNumber++;
        }
        buckets[bucketNumber].word = key;
        buckets[bucketNumber].addLocation(IndexLocation(pageNumber, wordNumber));
        keyCount++;
    }
}

//get number of keys contained in the map
int IndexMap::numKeys() const
{
    return keyCount;
}

//print out the contents of the hash table
void IndexMap::print() const
{
    cout << "Index: " << setw(17) << "Contents: " << endl;
    for (int i = 0; i < numBuckets; i++)
        cout << setw(6) << i << setw(15) << buckets[i] << endl;
}

//get the IndexRecord associated with a particular word
IndexRecord IndexMap::get(const std::string& word) const
{
    IndexRecord temp;

    int bucketNumber = getLocationFor(word);
    while(buckets[bucketNumber].word != EMPTY_CELL && buckets[bucketNumber].word != PREVIOUS_USED_CELL)
    {
        if(buckets[bucketNumber].word == word)
            return buckets[bucketNumber];
        else
        {
            if(bucketNumber == numBuckets - 1)
                bucketNumber = 0;
            else
                bucketNumber++;
        }
    }
    return temp;
}

//find all locations where one word is directly followed on the same page by a second
//  print them to cout
void IndexMap::findWordPairs(const std::string& key1, const std::string& key2) const
{
    IndexRecord word1 = get(key1);
    IndexRecord word2 = get(key2);

    cout << key1 + " " + key2 + " : ";
    for (int i = 0; i < word1.locations.size(); i++)
    {
        if (word2.hasLocation(IndexLocation(word1.locations[i].pageNum, word1.locations[i].wordNum+1)))
            cout << word1.locations[i].pageNum << "-" << word1.locations[i].wordNum << " ";
    }
}

//returns the first word on the indicated page
std::string IndexMap::firstWordOnPage(int pageNumber) const
{
    int counter = 0;
    bool found = false;
    string answer = "";
    while(counter < numBuckets && !found)
    {
        if(buckets[counter].word != EMPTY_CELL)
        {
            IndexRecord temp = get(buckets[counter].word);
            if(temp.hasLocation(IndexLocation(pageNumber,1)))
            {
                found = true;
                answer = buckets[counter].word;
            }
            else
                counter++;
        }
        else
            counter++;
    }
    return answer;
}
