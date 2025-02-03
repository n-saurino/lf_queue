Problem Statement

High-Frequency Trading (HFT) systems require ultra-low-latency data structures to handle large volumes of financial data in real time. Your task is to implement a lock-free queue using C++ atomic operations that supports multiple producers and multiple consumers.

The queue must allow:
	1.	Non-blocking enqueue() and dequeue() operations without using locks (std::mutex).
	2.	FIFO (First-In-First-Out) ordering of elements.
	3.	Thread safety, allowing multiple threads to enqueue and dequeue simultaneously.
	4.	Bounded capacity: The queue should have a fixed size (e.g., N elements), and enqueue() should fail if the queue is full.
	5.	Wait-free behavior: Each operation should complete in a finite number of steps.

Class Declaration:
template<typename T>
class LockFreeQueue {
public:
    explicit LockFreeQueue(size_t capacity);
    
    bool enqueue(const T& value);  // Returns true if enqueued successfully, false if queue is full
    std::optional<T> dequeue();    // Returns std::nullopt if queue is empty, otherwise the dequeued value
};

Constraints
	•	The queue should use non-blocking synchronization (std::atomic, std::memory_order).
	•	You CANNOT use std::mutex, std::condition_variable, or spinlocks.
	•	Multiple producers and consumers must work simultaneously without race conditions.
	•	The queue must be bounded with a fixed capacity defined at initialization.
	•	Enqueue and dequeue operations must run in O(1) time.

Follow-Up Questions
	1.	How would you optimize this queue for low-latency scenarios in HFT?
	2.	How can you avoid memory contention between CPU cores when enqueuing/dequeuing?
	3.	How can this design be extended to support dynamic resizing without locks?
	4.	What memory ordering guarantees (std::memory_order) are necessary for correctness?
	5.	What are the trade-offs of using a lock-free queue versus a lock-based queue in a real trading system?