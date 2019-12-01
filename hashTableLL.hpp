#ifndef HASHTABLELL_HPP
#define HASHTABLELL_HPP

#include <string>
using namespace std;

// Node struct will be an element in the hash table. Allows for Linked List 
// collision resolution in hash table
struct node
{
    int key;
    struct node* next;
};

class hashTableLL
{
    private:
        int tableSize;  // No. of buckets (linked lists)
        node* *table; // Pointer to an array containing buckets
        node* createNode(int key, node* next); // Creates and returns a new node
        int numRecords; // Number of values in the hash table
    public:
        hashTableLL(int bsize);  // Parameterized constructor to create hash table with given size 
        bool insertItem(int key, int hashFunction); // Inserts a key into hash table
        unsigned int hashFunction1(int key); // Function to calculate index in the hash table for a given key
        unsigned int hashFunction2(int key); // Function to calculate index in the hash table for a given key
        void printTable(); // Function that prints out the hash table
        node* searchItem(int key, int hashFunction); // Function that searches for a key in the hash table
        bool deleteItem(int key, int hashFunction); // Function that deletes a key in the hash table
        double loadFactor(); // Function that returns the load factor
};

#endif
