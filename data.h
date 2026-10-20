/**
 * Name: Alexander Katrompas
 * Assignment: Assignment 8 - Heaps
 * Purpose: Defines the records stored by the priority queue.
 */

#ifndef DATA_H
#define DATA_H

#include <string>

struct Data {
    int id;
    std::string information;
};

struct Entry {
    Data data;
    int priority;
};

#endif // DATA_H
