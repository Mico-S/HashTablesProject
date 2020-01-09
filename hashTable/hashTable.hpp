#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>
using namespace std;

class hashTable
{
    private:
        int tableSize;  // No. of buckets (linked lists)
        int *table; // Pointer to an array containing buckets
        int numRecords; // Number of values in the hash table
    public:
        hashTable(int bsize);  // Parameterized constructor to create hash table with given size 
        int hashTableSize(); // Returns the size of the hash table
        bool insertItem(int key, int hashFunction); // Inserts a key into hash table
        unsigned int hashFunction1(int key); // Function to calculate index in the hash table for a given key
        unsigned int hashFunction2(int key); // Function to calculate index in the hash table for a given key
        void printTable(); // Function that prints out the hash table
        int searchItem(int key, int hashFunction); // Function that searches for a key in the hash table
        bool deleteItem(int key, int hashFunction); // Function that deletes a key in the hash table
        double loadFactor(); // Function that returns the load factor
};

#endif