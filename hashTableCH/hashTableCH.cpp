#include <iostream>
#include "hashTableCH.hpp"
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Parameterized constructor to create hash table with given size 
hashTableCH::hashTableCH(int bsize)
{
    tableSize = bsize;
    table1 = new int[tableSize];
    table2 = new int[tableSize];
    for(int i=0;i<bsize;i++)
    {
        table1[i] = -1;
        table2[i] = -1;
    }
    numRecords = 0;
    primeNumbers = new int[50];
    createListOfPrimes(primeNumbers);
    // Obtains the last value (the highest value) in the list of primeNumbers
    // that are greater than the beginning tableSize
    maxPossibleTableSize = primeNumbers[49];
}

// Function that creates an array of 50 prime numbers that are bigger than the given tableSize
// (Populates data member "int* primeNumbers" array) 
void hashTableCH::createListOfPrimes(int* arr)
{
    int numValuesInArr = 0;
    int numPastTableSize = tableSize + 1;
    bool isPrime;

    // While there are less than 50 prime numbers in the primeNumbers array
    while(numValuesInArr < 50)
    {
        isPrime = true;
        // For loop that checks if a number is only divisible by 1 & itself
        for(int i = 2; i <= numPastTableSize / 2; i++)
        {
            if(numPastTableSize % i == 0)
            {
                isPrime = false;
                break;
            }
        }

        // If the number is prime, add it to the end of the array
        if(isPrime)
        {
            arr[numValuesInArr] = numPastTableSize;
            numValuesInArr++;
        }
        // Increment to the next number greater than the current tableSize
        numPastTableSize++;
    }
}

// Function to calculate index in the 1st hash table for a given key
int hashTableCH::hashFunction1(int key)
{
    return (key % tableSize);
}

// Function to calculate index in the 2nd hash table for a given key
int hashTableCH::hashFunction2(int key)
{
    return (int)floor(key / tableSize) % tableSize;
}

// Function to search for a key in the hash table and returns the number in
// the hash table at the index of the key
int hashTableCH::searchItem(int key)
{
    int index = hashFunction1(key);

    // If the first hash function found the key at the calculated index, return the value,
    // else recalculate the index with the second hash function and check that as well
    if(table1[index] == key)
    {
        return table1[index];
    }

    index = hashFunction2(key);

    if(table2[index] == key)
    {
        return table2[index];
    }
    // Returning -1 means the value was not found at either index
    return -1;
}

// Inserts a key into hash table
bool hashTableCH::insertItem(int key)
{
    // If the current tableSize is the maximum possible table size (cannot be a bigger prime number in the array of primeNumbers),
    // no more insertions can be done into the table as rehashing is not possible
    if(tableSize == maxPossibleTableSize)
    {
        cout << "Sorry, cannot insert anymore values!" << endl;
        return false;
    }
    insertItemHelper(key, key, 0);
    return true;
}

// Inserts a key into hash table and does cuckoo hashing displacement recursively
bool hashTableCH::insertItemHelper(int key, int originalKey, int counter)
{
    bool successful;
    // If the counter is > 0 (recursion has occured) & the displaced value we are trying to insert is the
    // same as the original value we were trying to insert, then a cycle is occuring, so rehash the two tables
    if(key == originalKey && counter > 10)
    {
        insertedItems.push_back(key);
        cout << "Rehashing..." << endl;
        rehash();
        return true;
    }

    // Calculate indices using hash functions 1 & 2 and attempt
    // to insert the key value into a slot
    int index = hashFunction1(key);

    // If the hash element in table1 at the calculated index is empty
    if(table1[index] == -1)
    {
        cout << "Inserting: " << key << " with hash function 1 @ index " << index << endl;
        table1[index] = key;
        insertedItems.push_back(key);
        numRecords++;
        return true;
    }

    int displacedValue1 = table1[index];
    table1[index] = key; 
    index = hashFunction2(key);
    
    // If the counter is > 0 (recursion has occured) & the displaced value we are trying to insert is the
    // same as the original value we were trying to insert, then a cycle is occuring, so rehash the two tables
    if(displacedValue1 == originalKey && counter > 10)
    {
        insertedItems.push_back(key);
        cout << "Rehashing..." << endl;
        rehash();
        return true;
    }

    // If the hash element in table2 at the calculated index is empty
    if(table2[index] == -1)
    {
        cout << "Inserting: " << displacedValue1 << " with hash function 2 @ index " << index << endl;
        table2[index] = displacedValue1;
        insertedItems.push_back(displacedValue1);
        numRecords++;
        return true;
    }

    // Obtain another displaced value from table2 and recursively call insertItemHelper()
    int displacedValue2 = table2[index];
    table2[index] = displacedValue1;
    counter++;
    insertItemHelper(displacedValue2, originalKey, counter);
}

// Rehashes (rebuilds) the current hash table with a new size
void hashTableCH::rehash()
{
    int oldTableSize = tableSize;
    // Make the new tableSize a prime number that is larger than the current tableSize
    for(int i = 0; i < 50; i++)
    {
        if(primeNumbers[i] > tableSize)
        {
            tableSize = primeNumbers[i];
            cout << "New Table Size: " << tableSize << endl;
            break;
        }
    }
    bool successful;
    
    // If the tableSize did not change (meaning that all 50 prime numbers have been used to change the tableSize),
    // then we cannot rehash any further and have reached the max load factor
    if(oldTableSize == tableSize)
    {
        cout << "Cannot re-hash further. Max Load Factor hit for this data set." << endl;
        return;
    }

    // Create two new tables with the new tableSize and make them empty 
    int* newTable1 = new int[tableSize];
    int* newTable2 = new int[tableSize];
    for(int i = 0; i < tableSize; i++)
    {
        newTable1[i] = -1;
        newTable2[i] = -1;
    }

    // Re-hashing all the previously inserted values into the new tables
    for(int j = 0; j < insertedItems.size(); j++)
    {
        successful = rehashHelper(newTable1, newTable2, insertedItems[j], insertedItems[j], 0);
        if(!successful)
        {
            break;
        }
    }

    // Deallocating table1 & table2, then make table1 & table2 point to the new tables
    delete [] table1;
    delete [] table2;
    table1 = newTable1;
    table2 = newTable2;
}

// Modified insert function to insert values into the new hash table
bool hashTableCH::rehashHelper(int* newTable1, int* newTable2, int key, int originalKey, int counter)
{
    // If the counter is > 0 (recursion has occured) & the displaced value we are trying to insert is the
    // same as the original value we were trying to insert, then a cycle is occuring, so rehash the two tables 
    if(key == originalKey && counter > 10)
    {
        cout << "Re-Rehashing..." << endl;
        delete [] newTable1;
        delete [] newTable2;
        rehash();
        return false;
    }

    // Calculate indices using hash functions 1 & 2 and attempt
    // to insert the key value into a slot
    int index = hashFunction1(key);

    if(newTable1[index] == -1)
    {
        // cout << "Inserting: " << key << " with hash function 1" << endl;
        newTable1[index] = key;
        return true;
    }

    int displacedValue1 = newTable1[index];
    newTable1[index] = key; 
    index = hashFunction2(displacedValue1);

    // If the counter is > 0 (recursion has occured) & the displaced value we are trying to insert is the
    // same as the original value we were trying to insert, then a cycle is occuring, so rehash the two tables 
    if(displacedValue1 == originalKey && counter > 10)
    {
        cout << "Re-Rehashing..." << endl;
        delete [] newTable1;
        delete [] newTable2;
        rehash();
        return false;
    }

    if(newTable2[index] == -1)
    {
        // cout << "Inserting: " << displaced << " with hash function 2" << endl;
        newTable2[index] = displacedValue1;
        return true;
    }

    int displacedValue2 = newTable2[index];
    newTable2[index] = displacedValue1;
    counter++;
    rehashHelper(newTable1, newTable2, displacedValue2, originalKey, counter);
}

// Deletes a given key value from the hash table
bool hashTableCH::deleteValue(int key)
{
    int index = hashFunction1(key);

    // If the element at the calculated index is the key, delete it
    // by setting it to -1 and return true
    if(table1[index] == key)
    {
        table1[index] = -1;
        numRecords--;
        return true;
    }

    index = hashFunction2(key);

    if(table2[index] == key)
    {
        table2[index] = -1;
        numRecords--;
        return true;
    }

    // If both hash functions were not able to delete the value,
    // return false
    return false;
}

// Function to display hash table
void hashTableCH::printTable()
{
    for (int i = 0; i < tableSize; i++) 
    {
        cout << i <<"|| ";
        if(table1[i] != -1)
        {
            cout << table1[i] << " ";
        }
        else
        {
            cout << "------ ";
        }
        if(table2[i] != -1)
        {
            cout << table2[i];
        }
        else
        {
            cout << "------";
        }
        cout << endl;
    }
 }

// Function that returns the load factor
double hashTableCH::loadFactor()
{
    return (numRecords / (double)tableSize);
}