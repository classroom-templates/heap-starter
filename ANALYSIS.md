# Assignment 8 — Heaps and Priority Queues Analysis

## Instructions

Complete all ten questions.

Each question is worth **1 point** for a total of **10 points**.

Partial credit may be awarded for answers that are incomplete but demonstrate correct understanding.

Your answers must be based on the **actual `PriorityQueue` design and implementation used in this assignment**, not generic definitions copied from another source.

Use your code, the supplied tests, and the Heaps and Priority Queues lectures and notes as references.

Answer directly below each question.

---

## 1. Priority Queue ADT vs. Heap Implementation — 1 point

Explain the difference between a **priority queue** and a **binary heap**.

Your answer should make clear which one is the ADT and which one is the implementation used in this assignment.

Then explain why the distinction matters when designing software.

### Answer



---

## 2. The Two Heap Invariants — 1 point

A binary max-heap depends on two separate structural rules:

1. the **complete binary tree shape invariant**;
2. the **max-heap ordering invariant**.

Explain both invariants.

Then explain why the array representation automatically preserves the complete-tree shape when new Entries are inserted at `heap[count]`.

### Answer



---

## 3. Array Index Relationships — 1 point

This assignment represents the heap as a zero-based array.

For an Entry stored at index `i`, explain the formulas used to locate:

- its parent;
- its left child;
- its right child.

Then explain why no Node pointers are required even though a heap is logically a tree.

### Answer



---

## 4. Why `peek()` Is `O(1)` but Arbitrary Search Is `O(n)` — 1 point

Explain why the highest-priority Entry can be retrieved in constant time.

Then explain why the heap-order invariant does **not** provide enough ordering information to efficiently search for an arbitrary `id` or arbitrary priority value.

Your answer should distinguish **local parent-child ordering** from the stronger ordering used by a Binary Search Tree.

### Answer



---

## 5. Why `enqueue()` Is `O(log n)` — 1 point

Describe the steps performed by `enqueue()` after a valid Entry is placed at the next available array position.

Explain:

- why the new Entry may violate the heap-order invariant;
- how `siftUp()` repairs the heap;
- why only one path toward the root is examined; and
- why the worst-case time complexity is `O(log n)`.

### Answer



---

## 6. Why `dequeue()` Is `O(log n)` — 1 point

Describe the steps performed when the highest-priority Entry is removed.

Your answer must explain:

- why the last Entry is moved to index `0`;
- why this preserves the complete-tree shape;
- why the replacement root may violate heap order;
- how `siftDown()` repairs the heap; and
- why the worst-case time complexity is `O(log n)`.

### Answer



---

## 7. Choosing the Correct Child During `siftDown()` — 1 point

For a max-heap, `siftDown()` must compare the current Entry with its children.

Explain why the algorithm must choose the **higher-priority child** when both children exist.

Then explain what can go wrong if the implementation swaps with whichever child it happens to check first.

Also explain the tie rule used in this assignment when both children have the same priority.

### Answer



---

## 8. Duplicate IDs, Duplicate Priorities, and Stability — 1 point

This assignment allows:

- duplicate IDs;
- duplicate priorities.

Explain why neither type of duplicate violates the heap invariant.

Then explain why this priority queue is **not stable**, and what that means for Entries that have equal priority.

Why should your tests avoid assuming FIFO order among equal-priority Entries?

### Answer



---

## 9. Why `clear()` Is `O(1)` — 1 point

The `clear()` method in this assignment sets the logical count back to zero but does not delete and recreate the array.

Explain why that is sufficient to make the queue logically empty.

Then explain:

- why the capacity does not change;
- why old Entry values remaining in unused array positions are not part of the logical heap;
- why this is not a memory leak; and
- why `clear()` is `O(1)`.

### Answer



---

## 10. Why Heap Operations Are Iterative Here — 1 point

The previous Binary Search Tree assignment used recursion heavily.

This heap assignment requires iterative heap operations.

Explain why iteration is a natural fit for this implementation.

Your answer should compare:

- the pointer-linked recursive structure of the BST; and
- the array-indexed representation of the heap.

Then explain why using recursion here would add complexity without improving the basic algorithm.

### Answer
