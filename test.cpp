/**
 * Name: Alexander Katrompas
 * Assignment: Assignment 8 - Heaps
 * Purpose: Implements the PriorityQueue testing module.
 */

#include "test.h"

/**
 * @brief Records the result of one test condition.
 * @param condition The condition being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception none
 * @return none
 * @note This function does not print test results.
 */
void recordTest(bool condition, TestResult& result) {

    result.total++;

    if (condition) {
        result.passed++;
    }
}

/**
 * @brief Compares an Entry against expected field values.
 * @param entry The Entry being checked.
 * @param id The expected id.
 * @param information The expected information.
 * @param priority The expected priority.
 * @exception none
 * @return true when all Entry fields match the expected values.
 */
bool matchesEntry(const Entry& entry,
                  int id,
                  const std::string& information,
                  int priority) {

    bool matches = entry.data.id == id &&
                   entry.data.information == information &&
                   entry.priority == priority;

    return matches;
}

/**
 * @brief Tests constructor behavior and capacity rules.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 */
void testConstruction(TestResult& result) {

    result.passed = 0;
    result.total = 0;

    PriorityQueue defaultQueue;
    recordTest(defaultQueue.isEmpty(), result);
    recordTest(!defaultQueue.isFull(), result);
    recordTest(defaultQueue.getCount() == 0, result);
    recordTest(defaultQueue.getCapacity() == TEST_DEFAULT_CAPACITY, result);
    recordTest(defaultQueue.validate(), result);

    PriorityQueue fallbackZero(0);
    recordTest(fallbackZero.getCapacity() == TEST_DEFAULT_CAPACITY, result);
    recordTest(fallbackZero.isEmpty(), result);
    recordTest(fallbackZero.validate(), result);

    PriorityQueue fallbackNegative(TEST_INVALID_ID);
    recordTest(fallbackNegative.getCapacity() == TEST_DEFAULT_CAPACITY, result);
    recordTest(fallbackNegative.isEmpty(), result);

    PriorityQueue customQueue(TEST_MEDIUM_CAPACITY);
    recordTest(customQueue.getCapacity() == TEST_MEDIUM_CAPACITY, result);
    recordTest(customQueue.getCount() == 0, result);
    recordTest(customQueue.isEmpty(), result);
    recordTest(customQueue.validate(), result);
}

/**
 * @brief Tests empty-state accessors and failed retrieval operations.
 * @param queue A reference to the PriorityQueue being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception none
 * @return none
 * @note This test establishes its own empty starting state.
 */
void testInitialState(PriorityQueue& queue, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    queue.clear();

    Entry peekResult = {{TEST_INVALID_ID, "unchanged"}, TEST_INVALID_PRIORITY};
    Entry dequeueResult = {{TEST_INVALID_ID, "unchanged"}, TEST_INVALID_PRIORITY};

    recordTest(queue.isEmpty(), result);
    recordTest(!queue.isFull(), result);
    recordTest(queue.getCount() == 0, result);
    recordTest(queue.validate(), result);

    recordTest(!queue.peek(peekResult), result);
    recordTest(matchesEntry(peekResult,
                            TEST_INVALID_ID,
                            "unchanged",
                            TEST_INVALID_PRIORITY),
               result);

    recordTest(!queue.dequeue(dequeueResult), result);
    recordTest(matchesEntry(dequeueResult,
                            TEST_INVALID_ID,
                            "unchanged",
                            TEST_INVALID_PRIORITY),
               result);
}

/**
 * @brief Tests insertion, sift-up behavior, root access, count, and validation.
 * @param queue A reference to the PriorityQueue being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note This test leaves a known valid heap in the supplied queue.
 */
void testBasicEnqueueAndPeek(PriorityQueue& queue, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    queue.clear();

    recordTest(queue.enqueue(TEST_ID_A, "alpha", TEST_PRIORITY_MEDIUM), result);
    recordTest(queue.validate(), result);

    Entry top = {{TEST_INVALID_ID, "unchanged"}, TEST_INVALID_PRIORITY};
    recordTest(queue.peek(top), result);
    recordTest(matchesEntry(top, TEST_ID_A, "alpha", TEST_PRIORITY_MEDIUM), result);

    recordTest(queue.enqueue(TEST_ID_B, "bravo", TEST_PRIORITY_LOW), result);
    recordTest(queue.validate(), result);

    recordTest(queue.enqueue(TEST_ID_C, "charlie", TEST_PRIORITY_HIGH), result);
    recordTest(queue.validate(), result);

    recordTest(queue.enqueue(TEST_ID_D, "delta", TEST_PRIORITY_MEDIUM_HIGH), result);
    recordTest(queue.validate(), result);

    recordTest(queue.enqueue(TEST_ID_E, "echo", TEST_PRIORITY_HIGHEST), result);
    recordTest(queue.validate(), result);

    recordTest(queue.getCount() == TEST_COUNT_FIVE, result);
    recordTest(!queue.isEmpty(), result);
    recordTest(!queue.isFull(), result);

    top = {{TEST_INVALID_ID, "unchanged"}, TEST_INVALID_PRIORITY};
    recordTest(queue.peek(top), result);
    recordTest(matchesEntry(top, TEST_ID_E, "echo", TEST_PRIORITY_HIGHEST), result);

    recordTest(queue.getCount() == TEST_COUNT_FIVE, result);
}

/**
 * @brief Tests invalid insertion and fixed-capacity full-queue behavior.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note Failed enqueue operations must leave queue state unchanged.
 */
void testRejectedEnqueueAndCapacity(TestResult& result) {

    result.passed = 0;
    result.total = 0;

    PriorityQueue queue(TEST_SMALL_CAPACITY);

    recordTest(!queue.enqueue(0, "zero", TEST_PRIORITY_MEDIUM), result);
    recordTest(!queue.enqueue(TEST_INVALID_ID, "negative", TEST_PRIORITY_MEDIUM), result);
    recordTest(!queue.enqueue(TEST_ID_A, "", TEST_PRIORITY_MEDIUM), result);
    recordTest(!queue.enqueue(TEST_ID_A, "bad-priority", 0), result);
    recordTest(!queue.enqueue(TEST_ID_A, "bad-priority", TEST_INVALID_PRIORITY), result);
    recordTest(queue.getCount() == 0, result);
    recordTest(queue.validate(), result);

    recordTest(queue.enqueue(TEST_ID_A, "alpha", TEST_PRIORITY_LOW), result);
    recordTest(queue.enqueue(TEST_ID_B, "bravo", TEST_PRIORITY_HIGH), result);
    recordTest(queue.enqueue(TEST_ID_C, "charlie", TEST_PRIORITY_MEDIUM), result);

    recordTest(queue.isFull(), result);
    recordTest(queue.getCount() == TEST_SMALL_CAPACITY, result);
    recordTest(queue.validate(), result);

    recordTest(!queue.enqueue(TEST_ID_D, "delta", TEST_PRIORITY_HIGHEST), result);
    recordTest(queue.isFull(), result);
    recordTest(queue.getCount() == TEST_SMALL_CAPACITY, result);
    recordTest(queue.validate(), result);

    Entry top = {{TEST_INVALID_ID, "unchanged"}, TEST_INVALID_PRIORITY};
    recordTest(queue.peek(top), result);
    recordTest(matchesEntry(top, TEST_ID_B, "bravo", TEST_PRIORITY_HIGH), result);
}

/**
 * @brief Tests duplicate ids and duplicate priorities.
 * @param queue A reference to the PriorityQueue being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note Duplicate values are valid and equal priorities are not required to be stable.
 */
void testDuplicateValues(PriorityQueue& queue, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    queue.clear();

    recordTest(queue.enqueue(TEST_ID_A, "first", TEST_PRIORITY_HIGH), result);
    recordTest(queue.enqueue(TEST_ID_A, "same-id", TEST_PRIORITY_MEDIUM), result);
    recordTest(queue.enqueue(TEST_ID_B, "same-priority-a", TEST_PRIORITY_HIGH), result);
    recordTest(queue.enqueue(TEST_ID_C, "same-priority-b", TEST_PRIORITY_HIGH), result);

    recordTest(queue.getCount() == TEST_COUNT_FOUR, result);
    recordTest(queue.validate(), result);

    Entry resultEntry = {{TEST_INVALID_ID, "unchanged"}, TEST_INVALID_PRIORITY};

    recordTest(queue.dequeue(resultEntry), result);
    recordTest(resultEntry.priority == TEST_PRIORITY_HIGH, result);
    recordTest(queue.validate(), result);

    recordTest(queue.dequeue(resultEntry), result);
    recordTest(resultEntry.priority == TEST_PRIORITY_HIGH, result);
    recordTest(queue.validate(), result);

    recordTest(queue.dequeue(resultEntry), result);
    recordTest(resultEntry.priority == TEST_PRIORITY_HIGH, result);
    recordTest(queue.validate(), result);

    recordTest(queue.dequeue(resultEntry), result);
    recordTest(matchesEntry(resultEntry,
                            TEST_ID_A,
                            "same-id",
                            TEST_PRIORITY_MEDIUM),
               result);

    recordTest(queue.isEmpty(), result);
    recordTest(queue.getCount() == 0, result);
    recordTest(queue.validate(), result);
}

/**
 * @brief Tests repeated dequeue, sift-down behavior, failed dequeue, and reuse.
 * @param queue A reference to the PriorityQueue being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 */
void testDequeueAndReuse(PriorityQueue& queue, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    queue.clear();

    queue.enqueue(TEST_ID_A, "alpha", TEST_PRIORITY_MEDIUM_LOW);
    queue.enqueue(TEST_ID_B, "bravo", TEST_PRIORITY_HIGHEST);
    queue.enqueue(TEST_ID_C, "charlie", TEST_PRIORITY_LOW);
    queue.enqueue(TEST_ID_D, "delta", TEST_PRIORITY_HIGH);
    queue.enqueue(TEST_ID_E, "echo", TEST_PRIORITY_MEDIUM_HIGH);
    queue.enqueue(TEST_ID_F, "foxtrot", TEST_PRIORITY_HIGHER);

    recordTest(queue.getCount() == TEST_COUNT_SIX, result);
    recordTest(queue.validate(), result);

    const int expectedPriorities[] = {
        TEST_PRIORITY_HIGHEST,
        TEST_PRIORITY_HIGHER,
        TEST_PRIORITY_HIGH,
        TEST_PRIORITY_MEDIUM_HIGH,
        TEST_PRIORITY_MEDIUM_LOW,
        TEST_PRIORITY_LOW
    };

    Entry entry = {{TEST_INVALID_ID, "unchanged"}, TEST_INVALID_PRIORITY};

    for (int i = 0; i < TEST_COUNT_SIX; i++) {
        recordTest(queue.dequeue(entry), result);
        recordTest(entry.priority == expectedPriorities[i], result);
        recordTest(queue.validate(), result);
    }

    recordTest(queue.isEmpty(), result);
    recordTest(queue.getCount() == 0, result);

    Entry unchanged = {{TEST_INVALID_ID, "unchanged"}, TEST_INVALID_PRIORITY};
    recordTest(!queue.dequeue(unchanged), result);
    recordTest(matchesEntry(unchanged,
                            TEST_INVALID_ID,
                            "unchanged",
                            TEST_INVALID_PRIORITY),
               result);

    recordTest(queue.enqueue(TEST_ID_G, "golf", TEST_PRIORITY_HIGH), result);
    recordTest(queue.getCount() == 1, result);
    recordTest(queue.validate(), result);

    Entry top = {{TEST_INVALID_ID, "unchanged"}, TEST_INVALID_PRIORITY};
    recordTest(queue.peek(top), result);
    recordTest(matchesEntry(top, TEST_ID_G, "golf", TEST_PRIORITY_HIGH), result);
}

/**
 * @brief Tests logical clearing and reuse without changing capacity.
 * @param queue A reference to the PriorityQueue being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 */
void testClearAndReuse(PriorityQueue& queue, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    queue.clear();

    int originalCapacity = queue.getCapacity();

    queue.enqueue(TEST_ID_A, "alpha", TEST_PRIORITY_LOW);
    queue.enqueue(TEST_ID_B, "bravo", TEST_PRIORITY_HIGH);
    queue.enqueue(TEST_ID_C, "charlie", TEST_PRIORITY_MEDIUM);

    recordTest(queue.getCount() == TEST_COUNT_THREE, result);
    recordTest(queue.validate(), result);

    queue.clear();

    recordTest(queue.isEmpty(), result);
    recordTest(!queue.isFull(), result);
    recordTest(queue.getCount() == 0, result);
    recordTest(queue.getCapacity() == originalCapacity, result);
    recordTest(queue.validate(), result);

    Entry unchanged = {{TEST_INVALID_ID, "unchanged"}, TEST_INVALID_PRIORITY};
    recordTest(!queue.peek(unchanged), result);
    recordTest(matchesEntry(unchanged,
                            TEST_INVALID_ID,
                            "unchanged",
                            TEST_INVALID_PRIORITY),
               result);

    queue.clear();
    recordTest(queue.isEmpty(), result);
    recordTest(queue.getCapacity() == originalCapacity, result);

    recordTest(queue.enqueue(TEST_ID_D, "delta", TEST_PRIORITY_HIGHEST), result);
    recordTest(queue.getCount() == 1, result);
    recordTest(queue.validate(), result);

    Entry top = {{TEST_INVALID_ID, "unchanged"}, TEST_INVALID_PRIORITY};
    recordTest(queue.peek(top), result);
    recordTest(matchesEntry(top, TEST_ID_D, "delta", TEST_PRIORITY_HIGHEST), result);
}

/**
 * @brief Tests printQueue output for empty and populated queues.
 * @param queue A reference to the PriorityQueue being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note Output is captured so the test module does not report test results directly.
 */
void testPrintQueue(PriorityQueue& queue, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    queue.clear();

    std::ostringstream capture;
    std::streambuf* original = std::cout.rdbuf(capture.rdbuf());

    queue.printQueue();

    std::cout.rdbuf(original);

    recordTest(capture.str() == "Queue is empty.\n", result);

    queue.enqueue(TEST_ID_A, "alpha", TEST_PRIORITY_MEDIUM);
    queue.enqueue(TEST_ID_B, "bravo", TEST_PRIORITY_HIGH);
    queue.enqueue(TEST_ID_C, "charlie", TEST_PRIORITY_LOW);

    capture.str("");
    capture.clear();
    original = std::cout.rdbuf(capture.rdbuf());

    queue.printQueue();

    std::cout.rdbuf(original);

    std::string expected =
        "[0] id=20 priority=10 information=bravo\n"
        "[1] id=10 priority=6 information=alpha\n"
        "[2] id=30 priority=2 information=charlie\n";

    recordTest(capture.str() == expected, result);
    recordTest(queue.validate(), result);
}

/**
 * @brief Performs deterministic large-scale enqueue and dequeue testing.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note All generated ids and priorities are valid and deterministic.
 */
void testScaledStress(TestResult& result) {

    result.passed = 0;
    result.total = 0;

    PriorityQueue queue(TEST_STRESS_CAPACITY);

    recordTest(queue.isEmpty(), result);
    recordTest(queue.getCapacity() == TEST_STRESS_CAPACITY, result);

    for (int i = 0; i < TEST_STRESS_COUNT; i++) {

        int id = i + 1;
        int priority = ((i * TEST_STRESS_MULTIPLIER) % TEST_STRESS_COUNT) + 1;
        std::string information = "record-" + std::to_string(id);

        recordTest(queue.enqueue(id, information, priority), result);
        recordTest(queue.validate(), result);
    }

    recordTest(queue.getCount() == TEST_STRESS_COUNT, result);
    recordTest(!queue.isFull(), result);

    Entry current = {{TEST_INVALID_ID, "unchanged"}, TEST_INVALID_PRIORITY};
    Entry previous = {{TEST_INVALID_ID, "unchanged"}, TEST_STRESS_COUNT + 1};

    for (int i = 0; i < TEST_STRESS_COUNT; i++) {

        recordTest(queue.dequeue(current), result);
        recordTest(current.priority <= previous.priority, result);
        recordTest(queue.validate(), result);

        previous = current;
    }

    recordTest(queue.isEmpty(), result);
    recordTest(queue.getCount() == 0, result);
    recordTest(queue.validate(), result);
}


// write your comment function block here
void testSiftBehavior(PriorityQueue& queue, TestResult& result) {

    result.passed = 0;
    result.total = 0;

    // Write your own tests here. Establish all queue state inside this function.
    // Create insertions that require an Entry to sift upward through multiple
    // levels. Create removals that require the replacement root to sift downward
    // through multiple levels and choose correctly between two children.
    // Verify the resulting priorities and use validate() throughout.
    // Erase this comment when you are done.
}


// write your comment function block here
void testPriorityOrdering(PriorityQueue& queue, TestResult& result) {

    result.passed = 0;
    result.total = 0;

    // Write your own tests here. Establish all queue state inside this function.
    // Insert Entries in deliberately scrambled priority order, including at least
    // two equal priorities. Repeatedly dequeue until empty and verify that the
    // returned priority sequence never increases. Do not assume FIFO ordering
    // among Entries with equal priorities. Erase this comment when you are done.
}
