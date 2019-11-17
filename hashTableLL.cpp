#include <iostream>
#include "hashTableLL.hpp"
#include <math.h>

using namespace std;

// Creates and returns a new node
node* hashTableLL::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}

// Parameterized constructor to create hash table with given size 
hashTableLL::hashTableLL(int bsize)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}

// Function to calculate index in the hash table for a given key
unsigned int hashTableLL::hashFunction1(int key)
{
    return (key % tableSize);
}

// Function to calculate index in the hash table for a given key
unsigned int hashTableLL::hashFunction2(int key)
{
    return floor(key / tableSize);
}

// Function to search for a key in the hash table and returns the node in
// the hash table at the index of the key
node* hashTableLL::searchItem(int key, int hashFunction)
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

    // Search the list at that specific index and return the node if found
    node* hashLLNode= table[index];
    while(hashLLNode!= NULL && hashLLNode->key != key)
    {
        hashLLNode= hashLLNode->next;
    }

    return hashLLNode;
}

//TODO Complete this function
//function to insert
bool hashTableLL::insertItem(int key, int hashFunction)
{
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

    node* newNode = createNode(key, NULL);
    if(table[index] == NULL)
    {
        table[index] = newNode;
    }
    else
    {
        // COLLISION RESOLUTION: LINKED LIST CHAINING
        // If the element at the index in the hash table is not an empty list, go
        // to the end of the linked list and then insert the new node at the end
        node* hashLLNode= table[index];
        while(hashLLNode->next != NULL)
        {
            hashLLNode= hashLLNode->next;
        }
        hashLLNode->next = newNode;
    }
}

// Function to display hash table
void hashTableLL::printTable()
{
    for (int i = 0; i < tableSize; i++) 
    {
        cout << i <<"|| ";
        if(table[i] != NULL)
        {
            node* hashLLNode= table[i];
            while(hashLLNode!= NULL)
            {
                cout << hashLLNode->key << " -> ";
                hashLLNode= hashLLNode->next; 
            }
            cout << "END";
        }
        cout << endl;
    }
 }