# Assignment 8 — Heaps and Priority Queues

## Overview

In this assignment, you will implement a **max-priority queue** using a **binary heap** stored in a dynamically allocated array.

This assignment combines several important course ideas:

- Abstract Data Types;
- array-based tree representation;
- complete binary trees;
- heap ordering;
- dynamic memory ownership;
- iterative algorithm design;
- algorithmic complexity;
- invariant-based testing;
- interface versus implementation.

The central distinction for this assignment is:

> A **priority queue** is the ADT.  
> A **binary heap** is the data structure used to implement it.

Your implementation will use a **max-heap**, meaning that larger numeric priority values represent higher priority.

---

# Background and Required References

Before beginning the assignment, review the following course material:

- **Heaps and Priority Queues lecture and notes, Part 1**
- **Heaps and Priority Queues lecture and notes, Part 2**
- **Algorithm Analysis, Efficiency, Complexity, and Performance Analysis lecture and notes**
- the supplied starter code and tests

The previous Binary Search Tree assignment is also useful as a comparison:

- a BST is a pointer-linked tree whose algorithms are naturally recursive;
- this heap is logically a tree but physically represented as an array;
- heap operations in this assignment are therefore implemented **iteratively**.

---

# Files

The starter repository provides:

- `ASSIGNMENT.md`
- `ANALYSIS.md`
- `data.h`
- `main.cpp`
- `main.h`
- `test.cpp`
- `test.h`

You must create:

- `priorityqueue.h`
- `priorityqueue.cpp`
- `README.md`
- `.gitignore`

---

# Important: The Starter Project Will Not Compile at First

The starter repository is intentionally incomplete.

That is not an error.

Your first development milestone should be:

1. inspect the supplied files;
2. determine the required `PriorityQueue` interface;
3. create `priorityqueue.h` and `priorityqueue.cpp`;
4. write the required declarations;
5. create simple method stubs;
6. compile the complete project successfully;
7. **only then begin implementing the heap algorithms.**

Continue using the interface-first development process used throughout the course.

Your Git history will be inspected and should show that you established the interface and achieved a complete compile before implementing the full algorithms.

---

# Course Coding Standards

All normal course coding standards remain in effect.

In particular:

- use one return statement in ordinary functions;
- do not use `while (true)`;
- avoid unnecessary `break` and `continue`;
- do not use unexplained numeric literals other than obvious values such as `-1`, `0`, and `1`;
- use named constants for meaningful numeric values;
- header files define the public interface and required module dependencies;
- implementation belongs in the corresponding `.cpp` file;
- use the established course comment style.

Student-created source files must begin with the current-semester file header format:

```cpp
/**
 * Name: Your Name
 * Assignment: Assignment 8 - Heaps
 * Purpose: Briefly describes the purpose of this file.
 */
```

---

# Supplied Data Types

The supplied `data.h` defines:

```cpp
struct Data {
    int id;
    std::string information;
};

struct Entry {
    Data data;
    int priority;
};
```

Each heap element is therefore an `Entry`.

The fields have different purposes:

- `id` identifies the record;
- `information` stores its payload;
- `priority` determines heap ordering.

The heap is ordered by `priority`, **not by `id`**.

---

# Valid Entry Data

A valid Entry requires:

```text
id > 0
information is not empty
priority > 0
```

Invalid input must cause `enqueue()` to return `false` without modifying the queue.

---

# Duplicate Values

This assignment allows:

- duplicate IDs;
- duplicate priorities.

There is no uniqueness requirement.

Do not scan the heap to reject duplicate IDs.

Equal priorities satisfy the heap invariant normally.

---

# Priority Semantics

This assignment implements a **max-priority queue**.

Larger numeric values mean higher priority.

The max-heap invariant is:

```text
parent.priority >= child.priority
```

Therefore the highest-priority Entry is always stored at:

```cpp
heap[0]
```

---

# Stability

This priority queue is **not stable**.

If two Entries have the same priority, no external ordering is guaranteed between them.

For example, if:

```text
Entry A priority = 10
Entry B priority = 10
```

the queue is not required to return A before B merely because A was inserted first.

Your tests must not assume FIFO behavior among equal-priority Entries.

---

# Required `PriorityQueue` Interface

Your class must provide the following public interface:

```cpp
PriorityQueue(int = DEFAULT_CAPACITY);
~PriorityQueue();

bool isEmpty() const;
bool isFull() const;
int getCount() const;
int getCapacity() const;

bool enqueue(int, const std::string&, int);
bool peek(Entry&) const;
bool dequeue(Entry&);

void clear();
bool validate() const;
void printQueue() const;
```

Do not add additional public methods.

---

# Default Capacity

The default capacity is:

```text
15
```

---

# Required Private Representation

The `PriorityQueue` class must have exactly these persistent attributes:

```cpp
Entry* heap;
int capacity;
int count;
```

Do not add additional persistent state.

Do not use:

- STL containers;
- linked Nodes;
- parent pointers;
- stored tree height;
- a second array;
- dynamic resizing.

The constructor must dynamically allocate:

```cpp
new Entry[capacity]
```

The destructor must release it using:

```cpp
delete[] heap;
```

---

# Required Private Helpers

The private section must include:

```cpp
int parent(int) const;
int leftChild(int) const;
int rightChild(int) const;

void siftUp(int);
void siftDown(int);
void swapEntries(int, int);
```

These helpers must be used to implement the heap behavior.

---

# Array Representation of the Complete Binary Tree

The heap uses a zero-based array.

For an Entry at index `i`:

```text
parent(i)     = (i - 1) / 2
leftChild(i)  = 2 * i + 1
rightChild(i) = 2 * i + 2
```

Do not call `parent()` for index `0`.

The occupied portion of the logical heap is always:

```text
heap[0] through heap[count - 1]
```

New Entries are initially inserted at:

```cpp
heap[count]
```

This automatically preserves the **complete binary tree shape**.

---

# No Recursion

Heap operations in this assignment must be implemented **iteratively**.

In particular:

- `siftUp()`;
- `siftDown()`;
- `validate()`;
- all other heap-processing logic

must use loops rather than recursion.

This is intentional.

A heap is logically a tree, but because this heap is stored in an array, moving through the structure using index arithmetic is more direct than recursive subtree processing.

---

# Construction and Destruction

## Constructor

```cpp
PriorityQueue(int = DEFAULT_CAPACITY);
```

The constructor must:

1. determine the correct capacity;
2. set `count` to `0`;
3. dynamically allocate the `Entry` array.

If the requested capacity is less than `1`, use `DEFAULT_CAPACITY`.

---

## Destructor

```cpp
~PriorityQueue();
```

The destructor must release the dynamically allocated heap array using:

```cpp
delete[] heap;
```

The queue owns the array for its entire lifetime.

---

# Basic Accessors

## `isEmpty()`

```cpp
bool isEmpty() const;
```

Return:

```text
count == 0
```

---

## `isFull()`

```cpp
bool isFull() const;
```

Return:

```text
count == capacity
```

---

## `getCount()`

```cpp
int getCount() const;
```

Return the stored logical Entry count.

Do not calculate the count by inspecting the array.

---

## `getCapacity()`

```cpp
int getCapacity() const;
```

Return the fixed queue capacity.

---

# `enqueue()`

```cpp
bool enqueue(int, const std::string&, int);
```

The parameters represent:

```text
id
information
priority
```

The method must:

1. validate the input;
2. verify that the queue is not full;
3. place the new Entry at `heap[count]`;
4. increment `count`;
5. call `siftUp()` on the newly inserted index;
6. return `true`.

Return `false` when:

- `id <= 0`;
- `information` is empty;
- `priority <= 0`;
- the queue is full.

A failed insertion must leave the queue unchanged.

Duplicate IDs and duplicate priorities are valid.

Worst-case time complexity:

```text
O(log n)
```

---

# `siftUp()`

```cpp
void siftUp(int);
```

After insertion, the new Entry may have a higher priority than its parent.

Repeatedly compare the Entry with its parent.

If:

```text
child.priority > parent.priority
```

swap them and continue upward.

Stop when:

- the Entry reaches the root; or
- its priority is no longer greater than its parent's priority.

Entries with equal priority must **not** be swapped.

---

# `peek()`

```cpp
bool peek(Entry&) const;
```

If the queue is not empty:

1. copy `heap[0]` into the caller-owned output Entry;
2. return `true`.

If the queue is empty:

- return `false`;
- leave the caller's output Entry unchanged.

`peek()` must not change `count` or the heap.

Time complexity:

```text
O(1)
```

---

# `dequeue()`

```cpp
bool dequeue(Entry&);
```

If the queue is empty:

- return `false`;
- leave the caller's output Entry unchanged.

Otherwise:

1. copy the root Entry into the caller-owned output object;
2. move the last logical Entry into `heap[0]`;
3. decrement `count`;
4. if the queue is still non-empty, call `siftDown(0)`;
5. return `true`.

A successful call removes exactly one Entry.

Worst-case time complexity:

```text
O(log n)
```

---

# `siftDown()`

```cpp
void siftDown(int);
```

After `dequeue()`, the replacement root may violate the max-heap invariant.

At each step:

1. determine whether the current Entry has children;
2. if both children exist, select the child with the higher priority;
3. if both children have equal priority, select the **left child**;
4. compare the selected child against the current Entry;
5. swap only when the child's priority is strictly greater;
6. continue downward from the new index.

Stop when:

- there are no children; or
- the current Entry is already greater than or equal to its children.

---

# `swapEntries()`

```cpp
void swapEntries(int, int);
```

Swap the two complete `Entry` objects stored at the supplied indices.

Do not swap only the priorities.

Each `Entry` must remain intact as a record.

---

# `clear()`

```cpp
void clear();
```

This assignment uses a **logical clear**.

Set:

```cpp
count = 0;
```

Do not:

- delete the heap array;
- allocate a new heap array;
- change capacity.

The existing `PriorityQueue` object must be immediately reusable.

Time complexity:

```text
O(1)
```

Values that remain physically present in unused array positions are no longer part of the logical heap.

---

# `validate()`

```cpp
bool validate() const;
```

This method verifies the actual max-heap invariant.

It must verify:

```text
0 <= count <= capacity
```

and for every occupied child index from `1` through `count - 1`:

```text
heap[parent(i)].priority >= heap[i].priority
```

Return `true` only when the logical heap is valid.

Do not inspect unused array positions.

Time complexity:

```text
O(n)
```

---

# `printQueue()`

```cpp
void printQueue() const;
```

Display the logical heap in **array order**.

For each occupied Entry, use this exact format:

```text
[index] id=ID priority=PRIORITY information=INFORMATION
```

Example:

```text
[0] id=20 priority=10 information=bravo
[1] id=10 priority=6 information=alpha
```

Only print:

```text
heap[0] through heap[count - 1]
```

If the queue is empty, print exactly:

```text
Queue is empty.
```

The supplied tests check this output format.

---

# Fixed Capacity

This assignment intentionally uses a fixed-capacity heap.

Do not resize the array.

If the queue is full:

```cpp
enqueue(...)
```

returns `false`.

Dynamic resizing is outside the scope of this assignment.

---

# No `buildHeap()`

Do **not** implement:

```cpp
buildHeap()
```

or any equivalent bulk-construction method.

In this assignment, a heap is created incrementally through repeated calls to:

```cpp
enqueue(...)
```

Do not attempt to replace that design with a different bulk-construction algorithm.

---

# No Heapsort

Do not implement heapsort as part of this assignment.

Heapsort is an algorithm that uses heap behavior; it is not part of the required `PriorityQueue` ADT.

---

# Copying `PriorityQueue` Objects

This class owns a dynamically allocated array.

Do not copy or assign `PriorityQueue` objects.

Copy constructors and assignment operators are outside the scope of this assignment and will not be tested.

---

# Testing

There are **no hidden autograding tests** because testing is part of the assignment.

The starter repository includes a substantial supplied test suite.

The supplied tests cover:

- constructor and capacity behavior;
- empty-state behavior;
- enqueue and peek;
- invalid insertion;
- full-capacity behavior;
- duplicate IDs;
- duplicate priorities;
- dequeue and reuse;
- clear and reuse;
- exact `printQueue()` output;
- deterministic large-scale stress behavior;
- repeated validation of the heap invariant.

---

# Student-Written Tests

You must complete these two functions in `test.cpp`:

```cpp
void testSiftBehavior(PriorityQueue&, TestResult&);
void testPriorityOrdering(PriorityQueue&, TestResult&);
```

Their declarations are already provided in `test.h`.

---

## `testSiftBehavior()`

Write meaningful tests that force both directions of heap repair.

Your tests must include:

- an insertion that causes an Entry to sift upward through multiple levels;
- a removal that causes the replacement root to sift downward through multiple levels;
- a case that requires correct selection between two children;
- repeated calls to `validate()` to verify that the heap invariant remains true.

Establish all required queue state inside this test function.

Do not depend on state left by an earlier test.

---

## `testPriorityOrdering()`

Write meaningful tests that:

- insert Entries in deliberately scrambled priority order;
- include at least two equal priorities;
- repeatedly dequeue until the queue becomes empty;
- verify that the returned priority sequence is **nonincreasing**.

In other words, each returned priority must be less than or equal to the previously returned priority.

Do not assume FIFO ordering among Entries with equal priority.

Establish all required queue state inside this test function.

---

# Student Test Rules

For both student-written functions:

- initialize the supplied `TestResult&`;
- use the provided `recordTest()` helper;
- establish your own queue state;
- do not print test results from `test.cpp`;
- write the required function comment block;
- remove the starter instructional comments when complete.

The supplied `main.cpp` reports:

```text
INCOMPLETE
```

when a required student test records zero test conditions.

If either required student test is incomplete, the final summary reports:

```text
Overall: INCOMPLETE
```

Passing all supplied tests does **not** make the assignment complete if either required student-written test is unfinished.

---

# Analysis

Complete `ANALYSIS.md`.

There are ten questions.

Each question is worth **1 point**, for a total of **10 points**.

Partial credit may be awarded for incomplete answers that demonstrate correct understanding.

Your answers must analyze the actual Priority Queue and heap implementation used in this assignment.

---

# Memory Verification

After the program works normally, build and run it with AddressSanitizer.

Example:

```bash
g++ -Wall -Wextra -pedantic -g -fsanitize=address \
    main.cpp test.cpp priorityqueue.cpp -o priorityqueue
```

Then run:

```bash
./priorityqueue
```

The completed program must not produce:

- memory leaks;
- use-after-free errors;
- invalid reads;
- invalid writes;
- double deletes.

Passing the functional tests does not prove that dynamic memory ownership is correct.

---

# Git Requirements

Use Git throughout the assignment.

Your history should show meaningful incremental development rather than one final bulk commit.

Your repository must contain at least **16 meaningful commits made during development**.

Commits must represent real development milestones.

Artificial commits created only to reach the minimum will not satisfy this requirement.

Commit as you reach real milestones: **small, smart, often**.

A reasonable development history may include:

- creation of the interface;
- first complete compile with method stubs;
- constructor/destructor and accessors;
- array index helpers;
- `enqueue()` and `siftUp()`;
- `peek()`;
- `dequeue()` and `siftDown()`;
- `validate()`;
- `clear()` and `printQueue()`;
- debugging;
- completion of `testSiftBehavior()`;
- completion of `testPriorityOrdering()`;
- completion of `ANALYSIS.md`;
- final cleanup and memory verification.

Do not manufacture meaningless commits merely to increase the count.

---

# Final Verification

Before submitting, verify all of the following:

- `priorityqueue.h` exists;
- `priorityqueue.cpp` exists;
- `README.md` exists;
- `.gitignore` exists;
- the project builds with the required compiler warnings enabled;
- all supplied tests pass;
- `testSiftBehavior()` is complete and meaningful;
- `testPriorityOrdering()` is complete and meaningful;
- the final test status is not `INCOMPLETE`;
- `PriorityQueue` contains only the required persistent attributes;
- the heap uses a dynamically allocated `Entry` array;
- the queue is fixed-capacity;
- invalid Entries are rejected;
- duplicate IDs are allowed;
- duplicate priorities are allowed;
- larger numeric priority means higher priority;
- `enqueue()` uses iterative `siftUp()`;
- `dequeue()` uses iterative `siftDown()`;
- equal-priority Entries are not treated as stable;
- `clear()` preserves capacity;
- `validate()` correctly checks the heap invariant;
- `printQueue()` uses the required format;
- no `buildHeap()` or equivalent bulk-construction method was added;
- no heapsort implementation was added;
- AddressSanitizer reports no memory errors;
- `ANALYSIS.md` is complete;
- Git history contains at least 16 meaningful commits.

---

# Submission

Submit the URL of your completed GitHub repository in Blackboard.

Do not submit individual source files separately unless instructed to do so.
