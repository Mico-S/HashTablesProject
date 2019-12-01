#ifndef HASHTABLECH_HPP
#define HASHTABLECH_HPP

#include <string>
using namespace std;
#include <vector>

class hashTableCH
{
    private:
        int tableSize;  // No. of buckets (linked lists)
        int *table1; // Pointer to an array containing buckets for the first hash function
        int *table2; // Pointer to an array containing buckets for the second hash function
        vector<int> insertedItems; // Vector containing all items ever inserted into the hash tables
        int numRecords; // Number of values in the hash table
    public:
        hashTableCH(int bsize);  // Parameterized constructor to create hash table with given size 
        bool insertItem(int key); // Inserts a key into hash table
        bool insertItemHelper(int key, int originalKey, int counter); // Inserts a key into hash table and does cuckoo hashing displacement recursively
        int hashFunction1(int key); // Function to calculate index in the hash table for a given key
        int hashFunction2(int key); // Function to calculate index in the hash table for a given key
        void printTable(); // Function that prints out the hash table
        int searchItem(int key); // Function that searches for a key in the hash table
        void rehash(); // Rehashes (rebuilds) the current hash table with a new size
        bool deleteValue(int key); // Deletes a given key value from the hash table
        bool rehashHelper(int* newTable1, int* newTable2, int key, int counter); // Modified insert function to insert values into the new hash table
        double loadFactor(); // Function that returns the load factor
};
// void rehashHelper(int table[], int key); // Modified insert function to insert values into the new hash table

#endif