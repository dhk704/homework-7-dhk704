#include "StringQueue.h"
#include <iostream>
#include <string>

void printQueueState(const StringQueue& q) {
    std::cout << "Queue: " << q << "\n";
    std::cout << "Size: " << q.size() << ", Capacity: " << q.capacity() << "\n";
    std::cout << "Current index for front element: " << q.get_front() << "\n";
    std::cout << "Current index for rear element: " << q.get_rear() << "\n\n";
}

int main() {
    // Test 1: Circular behavior (wrap-around)
    {
        std::cout << "\n=== TEST 1: REAR WRAP-AROUND===\n";
        StringQueue q;
        for (int i = 0; i < 6; ++i) {
            q.enqueue(std::to_string(i));  // Fill queue to near capacity
        }
        printQueueState(q);  // [0, 1, 2, 3, 4, 5]

        // Force wrap-around by dequeuing 1 and enqueuing 1 more
        std::cout << "Dequeuing: " << q.dequeue() << "\n";
        std::cout << "Enqueuing test value...\n";
        q.enqueue("X");

        printQueueState(q);  // [1, 2, 3, 4, 5, X]
    }

    // Test 2: Resize Test
    {
        std::cout << "\n=== TEST 2: RESIZING ===\n";
        StringQueue q;

        std::cout << "Queue up to capacity:\n";
        for (int i = 0; i < 8; ++i) {
            // Fill queue to near capacity
            q.enqueue(std::to_string(i));
        }

        // Display current queue and front index
        printQueueState(q);  // [0, 1, 2, 3, 4, 5, 6, 7]
    }

    // Test 3: Resize Test
    {
        std::cout << "\n=== TEST 3: FRONT INDEX ===\n";
        StringQueue q;

        std::cout << "Queue up to capacity:\n";
        for (int i = 0; i < 8; ++i) {
            // Fill queue to near capacity
            q.enqueue(std::to_string(i));
        }
        printQueueState(q);  // [0, 1, 2, 3, 4, 5, 6, 7]

        std::cout << "Dequeue until no values are left:\n";
        // Force wrap-around by dequeuing 1 and enqueuing 1 more
        for (int i = 0; i < 8; ++i) {
            q.dequeue();
        }

        std::cout << "Enqueuing test value...\n";
        q.enqueue("X");
        printQueueState(q);

    }

    // Test 4: Copy constructor
    {
        std::cout << "\n=== TEST 4: COPY CONSTRUCTOR ===\n";
        StringQueue q1;
        q1.enqueue("Alpha");
        q1.enqueue("Beta");

        std::string sky = "blue";
        if (sky == "blue") {
            StringQueue q2 = q1;  // Copy constructor
            std::cout << "Copied Queue:\n";
            printQueueState(q2);  // [Alpha, Beta]
        }

        std::cout << "Copied Queue now out of scope. Checking Original Queue:\n";
        printQueueState(q1);
    }

    // Test 5: Temporary Move assignment
    {
        std::cout << "\n=== TEST 5: MOVE ASSIGNMENT ===\n";
        StringQueue q1;

        std::string sky = "blue";

        if (sky == "blue") {
            StringQueue temp_q;
            temp_q.enqueue("Testing");
            temp_q.enqueue("Temporary");
            temp_q.enqueue("Queue");

            q1 = std::move(temp_q);     // Move assignment
            std::cout << "Move-Assign Queue (temp_q):\n";
            printQueueState(temp_q);    // [Testing, Temporary, Queue]
        }

        std::cout << "(temp_q) Queue now out of scope. Testing if (q1) remains:\n";
        printQueueState(q1);            // [Testing, Temporary, Queue]
    }

    return 0;
}