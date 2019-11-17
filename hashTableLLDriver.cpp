#include <iostream>
#include "HashTableLL.hpp"

int main()
{
    hashTableLL ht(5);

    ht.insertItem(20, 1);
    ht.insertItem(20, 2);
    ht.insertItem(30, 1);

    ht.printTable();
}