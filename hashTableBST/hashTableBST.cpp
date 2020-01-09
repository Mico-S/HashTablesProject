#include <iostream>
#include "hashTableBST.hpp"
#include <math.h>

using namespace std;

// Creates and returns a new node
node* hashTableBST::createNode(int key)
{
    node* nw = new node;
    nw->key = key;
    nw->leftChild = NULL;
    nw->rightChild = NULL;
    return nw;
}

// Parameterized constructor to create hash table with given size 
hashTableBST::hashTableBST(int bsize)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
    numRecords = 0;
}

// Function to calculate index in the hash table for a given key
unsigned int hashTableBST::hashFunction1(int key)
{
    return (key % tableSize);
}

// Function to calculate index in the hash table for a given key
unsigned int hashTableBST::hashFunction2(int key)
{
    return (int)floor(key / tableSize) % tableSize;
}

// Function to search for a key in the hash table and returns the node in
// the hash table at the index of the key
node* hashTableBST::searchItem(int key, int hashFunction)
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
    node* hashBSTNode = table[index];
    hashBSTNode = searchItemHelper(hashBSTNode, key);

    return hashBSTNode;
}

// Helper function to search at the hash table element's BST recursively for a specific value
node* searchItemHelper(node* crawler, int value)
{
    // If the value is found, return it
    if(crawler->key == value)
    {
        return crawler;
    }
    if(crawler == NULL)
    {
        return NULL;
    }

    // Recursively go down the left or right subtrees depending on the current crawler's value
    // and the key value
    if(value > crawler->key)
    {
        return searchItemHelper(crawler->rightChild, value);
    }
    else if(value < crawler->key)
    {
        return searchItemHelper(crawler->leftChild, value);
    }
}

// Inserts a key into hash table
bool hashTableBST::insertItem(int key, int hashFunction)
{
    // Use the hash function on the key to get the index/slot,
    // create a new node with the key and insert it in this slot's BST
    int index;
    if(hashFunction == 1)
    {
        index = hashFunction1(key);
    }
    else
    {
        index = hashFunction2(key);
    }

    // If there is currently no node at the current index, just insert the node as the root of the index
    node* newNode = createNode(key);
    if(table[index] == NULL)
    {
        table[index] = newNode;
    }
    else
    {
        // COLLISION RESOLUTION: BINARY SEARCH TREE CHAINING
        insertItemHelper(table[index], newNode);
    }
    numRecords++;
}

// Helper function to insert an item into the hash table element's BST when a collision happens
node* insertItemHelper(node* crawler, node* newNode)
{
    // Base case
    if(crawler == NULL)
    {
        return newNode;
    }

    // Recursively go down the left and right subtrees until below a leaf is reached, then insert the new node
    if(newNode->key < crawler->key)
    {
        crawler->leftChild = insertItemHelper(crawler->leftChild, newNode);
    }
    else if(newNode->key > crawler->key)
    {
        crawler->rightChild = insertItemHelper(crawler->rightChild, newNode);
    }

    return crawler;
}

// Function to display hash table
void hashTableBST::printTable()
{
    for (int i = 0; i < tableSize; i++) 
    {
        cout << i <<"|| ";
        if(table[i] != NULL)
        {
            printHelper(table[i]);
            cout << "END";
        }
        cout << endl;
    }
 }

// Helper function to print out the BST of a hash table element in a pre-order traversal (root, left, right)
void printHelper(node* crawler)
{
    if(crawler == NULL)
    {
        return;
    }

    cout << crawler->key << ", ";
    printHelper(crawler->leftChild);
    printHelper(crawler->rightChild);
}

// Function that deletes a key in the hash table
bool hashTableBST::deleteItem(int key, int hashFunction)
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

    table[index] = deleteItemHelper(table[index], key);
    numRecords--;
}

// Helper function to delete a specific node in a BST of a hash table element
node* deleteItemHelper(node* crawler, int key)
{
    // Base case: if the crawler reached past a leaf node, return NULL
    if(crawler == NULL)
    {
        return crawler;
    }
    // If the key is smaller than the current node's value, then go down the left subtree
    if(key < crawler->key)
    {
        crawler->leftChild = deleteItemHelper(crawler->leftChild, key);
    }
    // If the key is greater than the current node's value, then go down the right subtree
    else if(key > crawler->key)
    {
        crawler->rightChild = deleteItemHelper(crawler->rightChild, key);
    }
    // At this point, the current node's value is equal to the key, so perform a delete on the current node
    else
    {
        // If the node has no children
        if(crawler->leftChild == NULL && crawler->rightChild == NULL)
        {
            delete crawler;
            crawler = NULL;
        }
        // If the node has a right child but not a left child
        else if(crawler->leftChild == NULL && crawler->rightChild != NULL)
        {
            node* temp = crawler;
            crawler = crawler->rightChild;
            delete temp;
        }
        // If the node has a left child but not a right child
        else if(crawler->leftChild != NULL && crawler->rightChild == NULL)
        {
            node* temp = crawler;
            crawler = crawler->leftChild;
            delete temp;
        }
        // At this point, the node has a left and a right child
        else
        {
            // Take the min node of the right subtree and make the value of that node the current node's
            // new value
            node* temp = minOfRightSubtree(crawler->rightChild);
            crawler->key = temp->key;
            // Then delete the min of the right subtree's node
            crawler->rightChild = deleteItemHelper(crawler->rightChild, temp->key);
        }
    }
    return crawler;
}

// Helper function to return the smallest node in the right subtree of a given node
node* minOfRightSubtree(node* crawler)
{
    node* temp = crawler;

    // While the left child of the node exists, keep traversing down the left subtree
    // until the min value is hit, then return that node
    while(temp->leftChild != NULL)
    {
        temp = temp->leftChild;
    }

    return temp;
}

// Function that returns the load factor
double hashTableBST::loadFactor()
{
    return (numRecords / (double)tableSize);
}