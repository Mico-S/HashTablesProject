#include <iostream>
#include "hashTableCH.hpp"
#include <fstream>
#include <sstream>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <numeric>

int main(int argc, char *argv[])
{
    hashTableCH ht(10009);

    if(argc != 2)
    {
        cout << "You need 2 arguments in order to execute this program: the .exe file to execute the program and the .csv file for the values." << endl;
    }

    ifstream inStream;
    inStream.open(argv[1]);
    string lineFromFile = "";
    string stringNum;
    int number;

    // Reading in all the values from the given data set
    if(inStream.is_open())
    {
        while(getline(inStream, lineFromFile))
        {
            stringstream line(lineFromFile);
            while(getline(line, stringNum, ','))
            {
                number = stoi(stringNum);
                ht.insertItem(number);
                // if(ht.loadFactor() >= 0.1)
                // {
                //     break;
                // }
            }
        }
    }
    else
    {
        cout << "Failed to open the file." << endl;
    }

    ht.printTable();
    cout << "Done!" << endl;
    cout << "Load Factor is currently: " << ht.loadFactor() << endl;

    // Code below is for measuring execution times

    // vector<int> insertedItems;
    // vector<double> times;
    // srand(time(NULL));
    // double insertTime, searchTime, deleteTime;

    // // 100 inserts
    // for(int i = 0; i < 100; i++)
    // {
    //     // Start timer
    //     auto start = chrono::high_resolution_clock::now();
    //     // Create a random number between 1 & 100,000 and insert that number into the hash table
    //     int randNum = rand() % 100000 + 1;
    //     ht.insertItem(randNum);
    //     insertedItems.push_back(randNum);
    //     // End timer
    //     auto end = chrono::high_resolution_clock::now();
    //     // Calculate the time taken for 1 insertion operation in nanoseconds
    //     double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    //     times.push_back(time_taken);
    // }
    // // Take the average times of all 100 insertions by adding up all the insertion times and dividing by 100 (size of the vector)
    // insertTime = accumulate(times.begin(), times.end(), 0) / times.size();
    // // Clear all the times in the "times" vector
    // times.clear();

    // // 100 searches
    // for(int i = 0; i < 100; i++)
    // {
    //     auto start = chrono::high_resolution_clock::now();
    //     ht.searchItem(insertedItems[i]);
    //     auto end = chrono::high_resolution_clock::now();
    //     double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    //     times.push_back(time_taken);
    // }
    // searchTime = accumulate(times.begin(), times.end(), 0) / times.size();
    // times.clear();

    // // 100 deletes
    // for(int i = 0; i < 100; i++)
    // {
    //     auto start = chrono::high_resolution_clock::now();
    //     ht.deleteValue(insertedItems[i]);
    //     auto end = chrono::high_resolution_clock::now();
    //     double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    //     times.push_back(time_taken);
    // }
    // deleteTime = accumulate(times.begin(), times.end(), 0) / times.size();
    // times.clear();

    // cout << "Hash Function 2, Data Set C" << endl; 
    // cout << "Insert Time: " << insertTime << endl;
    // cout << "Search Time: " << searchTime << endl;
    // cout << "Delete Time: " << deleteTime << endl;
}