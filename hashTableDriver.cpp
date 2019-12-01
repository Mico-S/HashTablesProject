#include <iostream>
#include "hashTable.hpp"
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <cstdlib> 
#include <iomanip>
#include <numeric>

int main(int argc, char *argv[])
{
    hashTable ht(10009);

    if(argc != 2)
    {
        cout << "You need 2 arguments in order to execute this program: the .exe file to execute the program and the .csv file for the values." << endl;
    }

    ifstream inStream;
    inStream.open(argv[1]);
    string lineFromFile = "";
    string stringNum;
    int number;
    int numElementsInserted = 0;
    vector<int> elementsInserted;

    if(inStream.is_open())
    {
        while(getline(inStream, lineFromFile))
        {
            stringstream line(lineFromFile);
            while(getline(line, stringNum, ','))
            {
                number = stoi(stringNum);
                // USING HASH FUNCTION 1: REMEMBER TO CHANGE FOR NEXT TEST
                ht.insertItem(number, 1);
                numElementsInserted++;
                if(ht.loadFactor() >= 0.8)
                {
                    elementsInserted.push_back(number);
                }
                if(ht.loadFactor() >= 1.0)
                    break;
                if(numElementsInserted >= ht.hashTableSize())
                    break;
            }
            break;
        }
    }
    else
    {
        cout << "Failed to open the file." << endl;
    }

    // ht.printTable();
    cout << "Load factor is currently: " << ht.loadFactor() << endl;
    
    // 100 inserts, lookups, and deletes

    int counter = 0;
    vector<int> insertedItems;
    vector<double> times;
    srand(time(NULL));
    double insertTime, searchTime, deleteTime;

    for(int i = 0; i < 100; i++)
    {
        auto start = chrono::high_resolution_clock::now();
        int randNum = rand() % 100000 + 1;
        ht.insertItem(randNum, 2);
        insertedItems.push_back(randNum);
        auto end = chrono::high_resolution_clock::now();
        double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        times.push_back(time_taken);
    }
    insertTime = accumulate(times.begin(), times.end(), 0) / times.size();
    times.clear();

    for(int i = 0; i < 100; i++)
    {
        auto start = chrono::high_resolution_clock::now();
        ht.searchItem(insertedItems[i], 2);
        // ht.searchItem(elementsInserted[i], 2);
        auto end = chrono::high_resolution_clock::now();
        double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        times.push_back(time_taken);
    }
    searchTime = accumulate(times.begin(), times.end(), 0) / times.size();
    times.clear();

    for(int i = 0; i < 100; i++)
    {
        auto start = chrono::high_resolution_clock::now();
        ht.deleteItem(insertedItems[i], 2);
        // ht.deleteItem(elementsInserted[i], 2);
        auto end = chrono::high_resolution_clock::now();
        double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        times.push_back(time_taken);
    }
    deleteTime = accumulate(times.begin(), times.end(), 0) / times.size();
    times.clear();

    cout << "Insert Time: " << insertTime << endl;
    cout << "Search Time: " << searchTime << endl;
    cout << "Delete Time: " << deleteTime << endl;
}