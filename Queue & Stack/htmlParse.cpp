//----------------------------------------------------------
// CS260 Assignment 3 Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may not be republished without approval.
//----------------------------------------------------------

//Assignment 3, Part 1&2 Knum: K01203846

#include <iostream>
#include <fstream>

#include "Stack.h"

using namespace std;

int main()
{
   cout << "--------------- Part 1 ---------------" << endl;

   stackTesting();

   cout << "--------------- Part 2 ---------------" << endl;

   ifstream inFile("Document.html");
   if(!inFile.is_open())
   {
      cout << "Error opening file" << endl;
      return 1;
   }

   Stack <string> htmlStack;
   string temp;
   bool unmatched = false;

   //scan through the whole file; if any unmatched tag found, stop the loop
   while(!inFile.eof() && unmatched == false)
   {
       //get word by word;
       while(inFile >> temp && unmatched == false)
        {
           //case for finding the ending tag </xxx>
           if(temp.substr(0,2) == "</" && temp[temp.length()-1] == '>')

               //compare text with the tag from temp == top (e.g. </abc> <xxx>: check abc == xxx )
               if(htmlStack.peek().substr(1,htmlStack.peek().length()-2) == temp.substr(2,temp.length()-3))
                    htmlStack.pop();

               //unmatched tag found
               else
                {
                    cout << endl;
                    cout << "Unmatched tag spotted" << endl;
                    cout << "Current tag: " << temp << ", previous tag: " << htmlStack.peek() << endl;
                    unmatched = true;
                }
            else
            {
               //case for normal tag <xxx>
               if(temp[0] == '<' && temp[temp.length()-1] == '>')
                    htmlStack.push(temp);

               //case for simple text not enclosed by tag
               else
                {
                    htmlStack.reversePrint();
                    cout << " " << temp;
                    cout << endl;
                }
            }
        }
   }

   cout << endl;

   if(unmatched == false)
       cout << "Matched all html tags" << endl;
   else
       cout << "Stop matching html tag" << endl;

   cout << endl;

   cout << "--------------- End of Part 1 & 2 ---------------" << endl << endl;

   return 0;
}
