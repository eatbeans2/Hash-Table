/* Hash.cpp
 *
 *  Hash table implementation from:
 *  Kernighan & Ritchie, The C Programming Language,
 *     Second Edition, Prentice-Hall, 1988.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "hash.h"


const int HASH_TABLE_SIZE = 100;
static NListPtr hashTable[HASH_TABLE_SIZE];

    //  Prototypes
static char *Strdup( const char * );  //  in cstring, but....



/*  Hash
 *  Generate hash value for string s
 */

unsigned Hash( char *s )
{
    unsigned hashVal;
    
    for( hashVal = 0 ; *s != '\0' ; s++ )
        hashVal = *s + 31 * hashVal;
        
    return  hashVal % HASH_TABLE_SIZE;
}


/*  Lookup
 *  Look for s in hashTable
 */

NListPtr Lookup( char *s )
{
    NListPtr np;
    for( np = hashTable[Hash(s)] ; np != NULL ; np = np->next )
    {
        if( strcmp(s, np->name) == 0 )
	  {
            return np;    //  found
	  }
    }
    return NULL;          //  not found
}

/*  Insert
 *  Put (name, defn) in hash table
 */
 
NListPtr Insert( char *name, char *defn )
{
    unsigned hashVal;
    NListPtr np;
    
    if( (np = Lookup(name)) == NULL )  // not found
    {
        np = (NListPtr) malloc(sizeof(*np));
        if( np == NULL || (np->name = Strdup(name)) == NULL )
            return NULL;
        hashVal = Hash(name);
        np->next = hashTable[hashVal];
        hashTable[hashVal] = np;
    }
    else
    {      //  remove previous definition
        free( (void *)np->defn );
    }
    
    if( (np->defn = Strdup(defn)) == NULL )
        return NULL;
    
    return np;
}


/*  PrintHashTable
 *  Print the hash table contents
 */

void PrintHashTable()
{
    NListPtr np;

    cout << "Hash table contents:" << endl;
    cout << "--------------------\n" << endl;

    for( int i = 0 ; i < HASH_TABLE_SIZE ; i++ )
    {
        np = hashTable[i];
        while( np != NULL )
        {
             cout << setw(3) << i << ":    ";
             cout << np->name << ", " << np->defn;
             cout << endl;
             np = np->next;
        }
    }
}


/*  Strdup
 *  Make a duplicate copy of s
 */

static char *Strdup( const char *s )
{
    char *p;
    
    p = (char *) malloc(strlen(s)+1);  /*  +1 for '\0'  */
    if( p != NULL )
        strcpy(p,s);

    return p;
}

void CountBuckets()
{

  NListPtr np;
  int max = 0;
  int min = 0;

  int zeroBuckets = 0;
  
  int isNew = 1;

   for( int i = 0 ; i < HASH_TABLE_SIZE ; i++ )
    {
      cout << "Bucket: " << i << " Contents: ";

      int size = 0;

      np = hashTable[i];
      while( np != NULL )
        {
	  size++;
	  np = np->next;
        }
      if(isNew==1)
	{
	  min = size;
	  isNew = 0;
	}
      if(size == 0)
	zeroBuckets++;
      if(size < min)
	min = size;
      if(size > max)
	max = size;
      cout << size << endl;
    }

   cout << "Max bucket size: " << max << endl;
   cout << "Min bucket size: " << min << endl;
   cout << "Empty buckets: " << zeroBuckets << endl;
}

void LookupCheck( char *s )
{
    NListPtr np;
    int probeCount = 0;
    for( np = hashTable[Hash(s)] ; np != NULL ; np = np->next )
    {
      probeCount++;
        if( strcmp(s, np->name) == 0 )
	  {
	    cout << "'" << s << "' "  << "Probes required: " << probeCount << endl;
            return;    //  found
	  }
    }
    cout << "Failed to find the word" << endl;
    return;          //  not found
}
