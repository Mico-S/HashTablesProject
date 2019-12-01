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
    insertItemHelper(key, key, 0);
    return true;
}

// Inserts a key into hash table and does cuckoo hashing displacement recursively
bool hashTableCH::insertItemHelper(int key, int originalKey, int counter)
{
    if(searchItem(key) != -1)
    {
        cout << "Value already exists!" << endl;
        return false;
    }

    // If the key to be inserted is the same key as the original key that we were trying to insert and the counter > 0
    // (meaning recursion has happened), then a cycle is occuring, so rehash the table 
    if(key == originalKey && counter > 0)
    {
        insertedItems.push_back(key);
        cout << "Rehashing..." << endl;
        rehash();
        // insertItemHelper(key, 0);
        return true;
        // cout << "Changed size of tables to: " << tableSize << endl;
        // cout << "Placement failed. Rehashing required" << endl;
        // return false;
    }

    // Calculate indices using hash functions 1 & 2 and attempt
    // to insert the key value into a slot
    int index = hashFunction1(key);

    if(table1[index] == -1)
    {
        cout << "Inserting: " << key << " with hash function 1" << endl;
        table1[index] = key;
        insertedItems.push_back(key);
        numRecords++;
        return true;
    }

    int displacedValue1 = table1[index];
    table1[index] = key; 
    index = hashFunction2(displacedValue1);
    
    // If the key to be inserted is the same key as the original key that we were trying to insert and the counter > 0
    // (meaning recursion has happened), then a cycle is occuring, so rehash the table 
    if(displacedValue1 == originalKey && counter > 0)
    {
        insertedItems.push_back(key);
        cout << "Rehashing..." << endl;
        rehash();
        // insertItemHelper(key, 0);
        return true;
        // cout << "Changed size of tables to: " << tableSize << endl;
        // cout << "Placement failed. Rehashing required" << endl;
        // return false;
    }

    if(table2[index] == -1)
    {
        cout << "Inserting: " << displacedValue1 << " with hash function 2" << endl;
        table2[index] = displacedValue1;
        insertedItems.push_back(displacedValue1);
        numRecords++;
        return true;
    }

    int displacedValue2 = table2[index];
    table2[index] = displacedValue1;
    counter++;
    insertItemHelper(displacedValue2, originalKey, counter);

    // If both locations are full, then we displace the current value at the element
    // from hash function 1 and store that displaced value, then replace the current element's
    // value with the key value and recursively call insertItemHelper to attempt to insert the 
    // displaced value
    // index = hashFunction1(key);
    // int displacedValue = table1[index];
    // table1[index] = key;
    // counter++;
    // insertItemHelper(displacedValue, counter);
}

// Rehashes (rebuilds) the current hash table with a new size
void hashTableCH::rehash()
{
    // Declare a new hash table
    // srand(time(NULL));
    // int randNum = rand() % tableSize + 1; 
    tableSize = tableSize * 2;
    int* newTable1 = new int[tableSize];
    int* newTable2 = new int[tableSize];
    for(int i = 0; i < tableSize; i++)
    {
        newTable1[i] = -1;
        newTable2[i] = -1;
    }

    // Place all the values from the current hash table into the new hash table
    // for(int i = 0; i < tableSize; i++)
    // {
    //     newTable1[i] = table1[i];
    //     newTable2[i] = table2[i];
    // }
    // for(int i = 0; i < tableSize - 175; i++)
    // {
    //     if(table1[i] != -1)
    //     {
    //         rehashHelper(newTable1, newTable2, table1[i], 0);  
    //     }
    //     else if(table2[i] != -1)
    //     {
    //         rehashHelper(newTable1, newTable2, table2[i], 0);
    //     }
    // }
    for(int j = 0; j < insertedItems.size(); j++)
    {
        rehashHelper(newTable1, newTable2, insertedItems[j], 0);
    }

    delete [] table1;
    delete [] table2;
    table1 = newTable1;
    table2 = newTable2;
}

bool hashTableCH::rehashHelper(int* newTable1, int* newTable2, int key, int counter)
{
    if(counter >= tableSize)
    {
        // cout << "Rehashing of " << key << " failed." << endl;
        // return false;
        // rehash();
        counter = 0;
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

    if(newTable2[index] == -1)
    {
        // cout << "Inserting: " << displaced << " with hash function 2" << endl;
        newTable2[index] = displacedValue1;
        return true;
    }

    int displacedValue2 = newTable2[index];
    newTable2[index] = displacedValue1;
    counter++;
    rehashHelper(newTable1, newTable2, displacedValue2, counter);
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
            cout << table1[i];
        }
        else
        {
            cout << "------";
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