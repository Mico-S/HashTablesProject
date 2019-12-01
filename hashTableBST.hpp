#ifndef HASHTABLEBST_HPP
#define HASHTABLEBST_HPP

#include <string>
using namespace std;

// Node struct will be an element in the hash table. Allows for BST 
// collision resolution in hash table
struct node
{
    int key;
    node* leftChild = NULL;
    node* rightChild = NULL;
};

class hashTableBST
{
    private:
        int tableSize;  // No. of buckets (linked lists)
        node* *table; // Pointer to an array containing buckets
        node* createNode(int key); // Creates and returns a new node
        int numRecords; // Number of values in the hash table
    public:
        hashTableBST(int bsize);  // Parameterized constructor to create hash table with given size 
        bool insertItem(int key, int hashFunction); // Inserts a key into hash table
        unsigned int hashFunction1(int key); // Function to calculate index in the hash table for a given key
        unsigned int hashFunction2(int key); // Function to calculate index in the hash table for a given key
        void printTable(); // Function that prints out the hash table
        node* searchItem(int key, int hashFunction); // Function that searches for a key in the hash table
        bool deleteItem(int key, int hashFunction); // Function that deletes a key in the hash table
        double loadFactor(); // Function that returns the load factor
};
node* searchItemHelper(node* crawler, int value); // Helper function to search at the hash table element's BST recursively for a specific value
node* insertItemHelper(node* crawler, node* newNode); // Helper function to insert an item into the hash table element's BST when a collision happens
void printHelper(node* crawler); // Helper function to print out the BST of a hash table element in a pre-order traversal (root, left, right)
node* deleteItemHelper(node* crawler, int key); // Helper function to delete a specific node in a BST of a hash table element
node* minOfRightSubtree(node* crawler); // Helper function to return the smallest node in the right subtree of a given node

#endif