/**
 * Name: Alexander Katrompas
 * Assignment: Assignment 8 - Heaps
 * Purpose: Declares the PriorityQueue testing module.
 */

#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <sstream>
#include <string>
#include "priorityqueue.h"

// test constants
constexpr int TEST_DEFAULT_CAPACITY = 15;
constexpr int TEST_SMALL_CAPACITY = 3;
constexpr int TEST_MEDIUM_CAPACITY = 7;
constexpr int TEST_STRESS_CAPACITY = 257;
constexpr int TEST_STRESS_COUNT = 200;
constexpr int TEST_STRESS_MULTIPLIER = 73;

constexpr int TEST_COUNT_TWO = 2;
constexpr int TEST_COUNT_THREE = 3;
constexpr int TEST_COUNT_FOUR = 4;
constexpr int TEST_COUNT_FIVE = 5;
constexpr int TEST_COUNT_SIX = 6;

constexpr int TEST_ID_A = 10;
constexpr int TEST_ID_B = 20;
constexpr int TEST_ID_C = 30;
constexpr int TEST_ID_D = 40;
constexpr int TEST_ID_E = 50;
constexpr int TEST_ID_F = 60;
constexpr int TEST_ID_G = 70;
constexpr int TEST_ID_H = 80;

constexpr int TEST_PRIORITY_LOW = 2;
constexpr int TEST_PRIORITY_MEDIUM_LOW = 4;
constexpr int TEST_PRIORITY_MEDIUM = 6;
constexpr int TEST_PRIORITY_MEDIUM_HIGH = 8;
constexpr int TEST_PRIORITY_HIGH = 10;
constexpr int TEST_PRIORITY_HIGHER = 12;
constexpr int TEST_PRIORITY_HIGHEST = 14;

constexpr int TEST_INVALID_ID = -1;
constexpr int TEST_INVALID_PRIORITY = -1;

struct TestResult {
    int passed;
    int total;
};

// instructor test functions
void recordTest(bool, TestResult&);
bool matchesEntry(const Entry&, int, const std::string&, int);

void testConstruction(TestResult&);
void testInitialState(PriorityQueue&, TestResult&);
void testBasicEnqueueAndPeek(PriorityQueue&, TestResult&);
void testRejectedEnqueueAndCapacity(TestResult&);
void testDuplicateValues(PriorityQueue&, TestResult&);
void testDequeueAndReuse(PriorityQueue&, TestResult&);
void testClearAndReuse(PriorityQueue&, TestResult&);
void testPrintQueue(PriorityQueue&, TestResult&);
void testScaledStress(TestResult&);

// student test functions
// COMPLETE THE FOLLOWING TEST FUNCTIONS IN test.cpp
void testSiftBehavior(PriorityQueue&, TestResult&);
void testPriorityOrdering(PriorityQueue&, TestResult&);

#endif // TEST_H
