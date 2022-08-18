//----------------------------------------------------------
// CS260 Assignment Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may not be republished without approval.
//----------------------------------------------------------
#ifndef MYSET_H
#define MYSET_H

#include <iostream>
#include <vector>

//Assignment 4 BST K01203846

using namespace std;

//Node node for Set
template <class T>
struct SetNode
{
    T data;
    SetNode<T>* left;
    SetNode<T>* right;

    SetNode(const T& value);

    //overloaded operators
    bool operator==(const SetNode<T>& other);
    bool operator<(const SetNode<T>& other);
    bool operator>(const SetNode<T>& other);
};


//Set based on a BST
template <class T>
class MySet
{
private:
    SetNode<T>* root;

public:
    //Construct empty set
    MySet();

    //Copy constructor
    MySet(const MySet<T>& other);

    //Assignment operator - implement if needed
    MySet<T>& operator=(const MySet<T>& other);

    //Destructor
    ~MySet();

    //get number of items contained
    int size() const;

    //get depth of underlying tree
    int depth() const;

    //Add item to set
    //  Do not add duplicates of existing items - ignore any duplicate add
    void add(const T& item);

    //Check if item is in the set
    bool contains(const T& item) const;

    //Remove given item from the set if it exists
    void remove(const T& item);

    //returns the smallest item from the set (does not remove it)
    T getSmallest() const;

    //Helper function for getSmallest()
    T smallestValueFrom(SetNode<T>* curNode) const;

    //removes the largest item from the set and returns it
    T removeLargest();

    //Generates a new set containing all the items that are in either
    //  this set or another set
    //  intersections of {A, B, C, D} and {B, D, F} would be {A, B, C, D, F}
    //  Both original sets are left unmodified
    MySet<T> unionWith(const MySet<T>& other) const;

    //Generates a new set containing all the items that are in both
    //  this set and another set
    //  intersections of {A, B, C, D} and {B, D, F} would be {B, D}
    //  Both original sets are left unmodified
    MySet<T> intersectionWith(const MySet<T>& other) const;

    //Returns a vector of items in the set that are >= start and < end
    std::vector<T> getRange(const T& startValue, const T& endValue) const;

    //Recursively copy all the SetNode from other set
    SetNode<T> *recursiveCopy(const SetNode<T> *curNode);

    //Recursively delete all the SetNode
    void recursiveDelete(SetNode<T> *curNode);

    //Recursively count the number of all SetNode
    int recursiveCount(SetNode<T> *curNode) const;

    //Recursively count the depth of the tree
    int recursiveDepth(SetNode<T> *curNode) const;

    //Recursively delete the desired item within the tree
    SetNode<T>* removeHelper(SetNode<T>* curNode, const T& item);

    //returns the largest item from the set (does not remove it)
    T getLargest() const;

    //helper function for getRange()
    std::vector<T> recursivePrintRange(SetNode<T>*curNode, const T& startValue, const T& endvalue, vector<T> &IPsHolder) const;

    //helper function for add()
    SetNode<T>* recursiveAdd(SetNode<T>*curNode, const T& item);

    //helper function for unionWith()
    SetNode<T>* bstFromVector(int const begin, int const end, vector<T> const sortedData) const;
};


//--------------------------------------------------------------------
// SetNode implementations
//--------------------------------------------------------------------

template <class T>
SetNode<T>::SetNode(const T& value)
    : data(value)
{
    left = nullptr;
    right = nullptr;
}

//overloaded operators implementation
template <class T>
bool SetNode<T>::operator==(const SetNode<T>& other)
{
    return this->data == other.data;
}

template <class T>
bool SetNode<T>::operator<(const SetNode<T>& other)
{
    return this->data < other.data;
}

template <class T>
bool SetNode<T>::operator>(const SetNode<T>& other)
{
    return this->data > other.data;
}

//--------------------------------------------------------------------
// Set Implementations
//--------------------------------------------------------------------

template <class T>
MySet<T>::MySet()
{
    root = nullptr;
}

//copy constructor
template <class T>
MySet<T>::MySet(const MySet<T>& other)
{
    root = recursiveCopy(other.root);
}

//destructor
template <class T>
MySet<T>::~MySet()
{
    recursiveDelete(root);
}

template <class T>
void MySet<T>::recursiveDelete(SetNode<T> *curNode)
{
    if(curNode == nullptr)
        return;
    //delete left-sided subtree
    recursiveDelete(curNode->left);
    //delete right-sided subtree
    recursiveDelete(curNode->right);
    delete curNode;
}

template <class T>
SetNode<T> *MySet<T>::recursiveCopy(const SetNode<T> *curNode)
{
    SetNode<T> *newNode;
    if(curNode == nullptr)
        return nullptr;
    else
        //create a newNode for curNode->data
        newNode = new SetNode<T>(curNode->data);
    //recursiveCopy for left and right subtree
    newNode->left = recursiveCopy(curNode->left);
    newNode->right = recursiveCopy(curNode->right);
    return newNode;
}

template <class T>
int MySet<T>::size() const
{
    return recursiveCount(root);
}

template <class T>
int MySet<T>::recursiveCount(SetNode<T> *curNode) const
{
    if (curNode == nullptr)
        return 0;
    //count number of nodes in left, right subtree and root
    return recursiveCount(curNode->left) + recursiveCount(curNode->right) + 1;
}

template <class T>
int MySet<T>::depth() const
{
    return recursiveDepth(root);
}

template <class T>
int MySet<T>::recursiveDepth(SetNode<T> *curNode) const
{
    if (curNode == nullptr)
        return -1;
    else
    {
        int leftDepth;
        int rightDepth;
        //calculate the depth for left and right subtree
        leftDepth = recursiveDepth(curNode->left);
        rightDepth = recursiveDepth(curNode->right);
        //if left subtree's depth is larger than right subtree, return left's Depth + 1(as parent node)
        if (leftDepth > rightDepth)
            return leftDepth + 1;
        else
            return rightDepth + 1;
        //return the largest among the left and right subtree's depth
        return std::max(leftDepth, rightDepth);
    }
}

template <class T>
bool MySet<T>::contains(const T& item) const
{
    SetNode<T>*curNode = root;
    while (curNode != nullptr)
    {
        if (item == curNode->data)
            return true;
        else
            //search for left/right subtree
            if (item < curNode->data)
                curNode = curNode->left;
            else
                curNode = curNode->right;
    }
    return false;
}

template <class T>
void MySet<T>::remove(const T& item)
{
    root = removeHelper(root, item);
}

template <class T>
SetNode<T>* MySet<T>::removeHelper(SetNode<T>* curNode, const T& item)
{
    if(curNode == nullptr)
        return nullptr;
    else if(item < curNode->data)
        curNode->left = removeHelper(curNode->left, item);
    else if (item > curNode->data)
            curNode->right = removeHelper(curNode->right, item);

    // case if found the item
    else
    {
        //case for no right child
        if (curNode->right == nullptr)
        {
            SetNode<T>*temp = curNode->left;
            delete curNode;
            return temp;
        }
        //case for no left child
        else if (curNode->left == nullptr)
        {
            SetNode<T>*temp = curNode->right;
            delete curNode;
            return temp;
        }
        //have both left/right child
        else
        {
            curNode->data = smallestValueFrom(curNode->right);
            curNode->right = removeHelper(curNode->right, curNode->data);
        }
    }
    return curNode;
}

template <class T>
T MySet<T>::getSmallest() const
{
    return smallestValueFrom(root);
}

template <class T>
T MySet<T>::smallestValueFrom(SetNode<T>* curNode) const
{
    /*search for left subtree only, if no left subtree, return root)*/
    if(curNode->left == nullptr)
        return curNode->data;
    else
        return smallestValueFrom(curNode->left);
}

template <class T>
void MySet<T>::add(const T& item)
{
    root = recursiveAdd(root, item);
}

template <class T>
SetNode<T>* MySet<T>::recursiveAdd(SetNode<T>*curNode, const T& item)
{
    //exclude any duplicate items
    if(!contains(item))
    {
        if(curNode == nullptr)
            return new SetNode<T>(item);
        if (item < curNode->data)
            curNode->left = recursiveAdd(curNode->left, item);
        else
            curNode->right = recursiveAdd(curNode->right, item);
        return curNode;
    }
    else
        //if found duplicated item, just return curNode (the linkage should be unchanged)
        return curNode;
}

template <class T>
T MySet<T>::removeLargest()
{
    T largest = getLargest();
    remove(largest);
    return largest;
}

//iterative version
template <class T>
T MySet<T>::getLargest() const
{
    if(root->right == nullptr)
        return root->data;
    else
    {
        SetNode<T>*temp = root;
        while (temp->right != nullptr)
            temp = temp->right;
        return temp->data;
    }
}

template <class T>
vector<T> MySet<T>::getRange(const T& startValue, const T& endValue) const
{
    vector<T> IPsHolder;
    return recursivePrintRange(root, startValue, endValue, IPsHolder);
}

template <class T>
vector<T> MySet<T>::recursivePrintRange(SetNode<T>*curNode, const T& startValue, const T& endValue, vector<T> &IPsHolder) const
{

    //if the other set is an empty set, just return the empty vector
    if (curNode == nullptr)
        return IPsHolder;

    //go to the position where startValue < curNode->data
    if(startValue < curNode->data)
        recursivePrintRange(curNode->left, startValue, endValue, IPsHolder);

    // once found the position (should be equal to or larger than startValue)
    // stop when curNode->data > endValue
    // each recursive call will push the curNode->data to vector
    if (startValue <= curNode->data && curNode->data <= endValue)
        IPsHolder.push_back(curNode->data);

    //case for right subtree
    recursivePrintRange(curNode->right, startValue, endValue, IPsHolder);

    return IPsHolder;
}

template <class T>
MySet<T> MySet<T>::intersectionWith(const MySet<T>& other) const
{
    // transfer the BST into vector
    vector<T> thisData = getRange(getSmallest(), getLargest());
    vector<T> otherData = other.getRange(other.getSmallest(), other.getLargest());
    vector<T> sortedData;

    MySet<T> setAIB;

    // case if the largest item from 1st vector is smaller than the smallest item in 2nd vector
    // indicating no intersection
    if(this->getLargest() < other.getSmallest() ||
       other.getLargest() < this->getSmallest())
       return setAIB;

    int thisCounter = 0, otherCounter = 0;

    //stop when either vector has visited all the data
    while(thisCounter < thisData.size() && otherCounter < otherData.size())
    {
        //case for matching the data (intersection)
        if(thisData[thisCounter] == otherData[otherCounter])
        {
            sortedData.push_back(thisData[thisCounter]);
            //setAIB.add(thisData[thisCounter]);
            thisCounter++;
            otherCounter++;
        }
        else
        {
            //1st vector data is smaller than 2nd vector data; forward 1st vector
            if(thisData[thisCounter] < otherData[otherCounter])
                thisCounter++;
            else
                otherCounter++;
        }
    }
    setAIB.root = bstFromVector(0, sortedData.size()-1, sortedData);
    return setAIB;
}

template <class T>
MySet<T> MySet<T>::unionWith(const MySet<T>& other) const
{
    MySet<T> setAUB;
    if (other.root == nullptr)
        return *this;
    vector<T> thisData = getRange(getSmallest(), getLargest());
    vector<T> otherData = other.getRange(other.getSmallest(), other.getLargest());
    vector<T> sortedData;

    int thisCounter = 0, otherCounter = 0;
    //stop when either vector has visited all the data
    while(thisCounter < thisData.size() && otherCounter < otherData.size())
    {
        //prepare a sorted vector
        if(thisData[thisCounter] < otherData[otherCounter])
        {
            sortedData.push_back(thisData[thisCounter]);
            thisCounter++;
        }
        else
        {
            if(thisData[thisCounter] > otherData[otherCounter])
            {
                sortedData.push_back(otherData[otherCounter]);
                otherCounter++;
            }
            else
            {
                //case for matching the same item; for this case, the vector will only push once to formulate union effect
                sortedData.push_back(thisData[thisCounter]);
                thisCounter++;
                otherCounter++;
            }
        }
    }

    //push back the remaining data from otherData
    if (thisCounter == thisData.size())
    {
        while(otherCounter < otherData.size())
        {
            sortedData.push_back(otherData[otherCounter]);
            otherCounter++;
        }
    }

    //push back the remaining data from thisData
    if (otherCounter == otherData.size())
    {
        while(thisCounter < thisData.size())
        {
            sortedData.push_back(thisData[thisCounter]);
            thisCounter++;
        }
    }

    setAUB.root = bstFromVector(0, sortedData.size()-1, sortedData);
    return setAUB;
}

template <class T>
//build bst from sorted data
SetNode<T>* MySet<T>::bstFromVector(int const begin, int const end, vector<T> const sortedData) const
{
    if(begin > end)
        return nullptr;

    int middle = (begin + end)/2;
    //the 1st call will be the root;
    SetNode<T>* newNode = new SetNode<T>(sortedData[middle]);

    //construct the bst through recursive call of bstFromVector
    //1st call will create the left & right child for the root, and continue to expand the tree until (begin > end)
    newNode->left = bstFromVector(begin, middle-1, sortedData);
    newNode->right = bstFromVector(middle+1, end, sortedData);

    //return the newNode(should be the root of the bst)
    return newNode;
}

#endif // MYSET_H
