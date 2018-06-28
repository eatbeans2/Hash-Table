/* TestHash.cpp
 *   Test the Hash table code.
 */

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

#include "hash.h"


int main()
{  
      //  Put a few values in the table...
  ifstream dict;
  dict.open("dict4.txt");

  char str[255];

  while(dict.getline(str, 255)){
    (void)Insert(str, "");
  }
  
  dict.close();

   PrintHashTable();

   CountBuckets();

   LookupCheck("adroitness");
   LookupCheck("manhood");
   LookupCheck("oxan");
   LookupCheck("Tano");
   LookupCheck("yokefellow");
   LookupCheck("unblamable");
   LookupCheck("doolie");
   LookupCheck("hydrastine");
   LookupCheck("idiograph");
   LookupCheck("sermonist");


   return EXIT_SUCCESS;
}
 


 
