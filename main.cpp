/**
 * Name: Alexander Katrompas
 * Assignment: Assignment 8 - Heaps
 * Purpose: Runs and reports the PriorityQueue test suite.
 */

#include "main.h"

int main() {

    int status = 0;
    bool incomplete = false;
    TestResult result = {0, 0};
    TestResult overall = {0, 0};
    PriorityQueue queue;

    std::cout << "Heap Priority Queue Tests" << std::endl;
    std::cout << "=========================" << std::endl;

    testConstruction(result);
    std::cout << "Construction: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testInitialState(queue, result);
    std::cout << "Initial state: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testBasicEnqueueAndPeek(queue, result);
    std::cout << "Enqueue and peek: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testRejectedEnqueueAndCapacity(result);
    std::cout << "Rejected enqueue and capacity: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testDuplicateValues(queue, result);
    std::cout << "Duplicate values: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testDequeueAndReuse(queue, result);
    std::cout << "Dequeue and reuse: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testClearAndReuse(queue, result);
    std::cout << "Clear and reuse: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testPrintQueue(queue, result);
    std::cout << "Print queue: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testSiftBehavior(queue, result);

    if (result.total == 0) {
        std::cout << "Sift behavior: INCOMPLETE" << std::endl;
        incomplete = true;
        status = 1;
    } else {
        std::cout << "Sift behavior: "
                  << result.passed << "/" << result.total
                  << " passed" << std::endl;
        overall.passed += result.passed;
        overall.total += result.total;
    }

    testPriorityOrdering(queue, result);

    if (result.total == 0) {
        std::cout << "Priority ordering: INCOMPLETE" << std::endl;
        incomplete = true;
        status = 1;
    } else {
        std::cout << "Priority ordering: "
                  << result.passed << "/" << result.total
                  << " passed" << std::endl;
        overall.passed += result.passed;
        overall.total += result.total;
    }

    testScaledStress(result);
    std::cout << "Scaled stress: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    std::cout << std::endl;

    if (incomplete) {
        std::cout << "Overall: INCOMPLETE" << std::endl;
        std::cout << "Completed tests: "
                  << overall.passed << "/" << overall.total
                  << " passed" << std::endl;
    } else {
        std::cout << "Overall: "
                  << overall.passed << "/" << overall.total
                  << " passed" << std::endl;
    }

    if (overall.passed != overall.total) {
        status = 1;
    }

    return status;
}
