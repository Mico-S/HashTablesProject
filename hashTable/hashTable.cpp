#include <iostream>
#include "hashTable.hpp"
#include <math.h>

using namespace std;

// Parameterized constructor to create hash table with given size 
hashTable::hashTable(int bsize)
{
    this->tableSize= bsize;
    table = new int[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = -1;
    numRecords = 0;
}

// Returns the size of the hash table
int hashTable::hashTableSize()
{
    return tableSize;
}

// Function to calculate index in the hash table for a given key
unsigned int hashTable::hashFunction1(int key)
{
    return (key % tableSize);
}

// Function to calculate index in the hash table for a given key
unsigned int hashTable::hashFunction2(int key)
{
    return (int)floor(key / tableSize) % tableSize;
}

// Function to search for a key in the hash table and returns the number in
// the hash table at the index of the key
int hashTable::searchItem(int key, int hashFunction)
{
    // Compute the index by using either the 1st or 2nd hash function
    int index;
    if(hashFunction == 1)
    {
        index = hashFunction1(key);
    }
    else
    {
        index = hashFunction2(key);
    }

    // Linearly probe the hash table until the value is found.
    // If the number of times searched for an item equals the length of the hash table,
    // return -1 as the key wasn't found
    int numTimesSearched = 0;
    while(table[index] != key)
    {
        index++;
        numTimesSearched++;
        // Loop back to the front of the hash table if the size is reached and keep searching
        if(index == tableSize)
            index = 0;
        if(numTimesSearched == tableSize)
            return -1;
    }

    return table[index];
}

// Function that deletes a key in the hash table
bool hashTable::deleteItem(int key, int hashFunction)
{
    // Compute the index by using either the 1st or 2nd hash function
    int index;
    if(hashFunction == 1)
    {
        index = hashFunction1(key);
    }
    else
    {
        index = hashFunction2(key);
    }

    // Linearly probe the hash table until the value is found.
    // If the number of times searched for an item equals the length of the hash table,
    // return false as the key wasn't found and couldn't be deleted
    int numTimesSearched = 0;
    while(table[index] != key)
    {
        index++;
        numTimesSearched++;
        // Loop back to the front of the hash table if the size is reached and keep searching
        if(index == tableSize)
            index = 0;
        if(numTimesSearched == tableSize)
            return false;
    }

    table[index] = -1;
    return true;
}

// Inserts a key into hash table
bool hashTable::insertItem(int key, int hashFunction)
{
    if(numRecords >= tableSize)
    {
        return false;
    }
    // Use the hash function on the key to get the index/slot,
    // create a new node with the key and insert it in this slot's list
    int index;
    if(hashFunction == 1)
    {
        index = hashFunction1(key);
    }
    else
    {
        index = hashFunction2(key);
    }

    if(table[index] == -1)
    {
        table[index] = key;
        // cout << "Inserted: " << key << " into slot w/ index: " << index << endl;
        numRecords++;
    }
    else
    {
        // COLLISION RESOLUTION: LINEAR PROBING W/ STEP SIZE 1
        // If the element at the index in the hash table is not -1 (not empty),
        // keep scanning through the hash table with step size 1 until an empty
        // element is reached
        bool found = false;
        int i = index;
        while(true)
        {
            // If the end of the table is reached, loop back to the front of the
            // table and keep searching for an empty slot
            if(i == tableSize)
            {
                i = 0;
            }
            if(table[i] == -1)
            {
                table[i] = key;
                // found = true;
                // cout << "Inserted: " << key << " into slot w/ index: " << i << endl;
                numRecords++;
                break;
            }
            i++;
        }
    }
}

// Function to display hash table
void hashTable::printTable()
{
    for (int i = 0; i < tableSize; i++) 
    {
        cout << i <<"|| ";
        if(table[i] != -1)
        {
            cout << table[i];
        }
        cout << endl;
    }
 }

// Function that returns the load factor
double hashTable::loadFactor()
{
    return (numRecords / (double)tableSize);
}