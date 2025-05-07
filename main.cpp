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
        std::cout << "\n=== TEST 1: REAR WRAP-AROUND ===\n";
        StringQueue q1;
        for (int i = 0; i < 7; i++) {
            q1.enqueue(std::to_string(i));  // Fill queue to near capacity
        }
        printQueueState(q1);  // [0, 1, 2, 3, 4, 5, 6]

        // Force wrap-around by dequeuing 1 and enqueuing 1 more
        std::cout << "Dequeuing: " << q1.dequeue() << "\n";
        std::cout << "Enqueuing test value...\n";
        q1.enqueue("X");

        printQueueState(q1);  // [1, 2, 3, 4, 5, X]

        std::cout << "Dequeuing 3 more values: ";
        for (int i = 0; i < 3; i++) {
            std::cout << q1.dequeue() << " ";
        }
        std::cout << "\nEnqueuing test value...\n";
        q1.enqueue("Y");    // [4, 5, 6, X, Y]

        printQueueState(q1);
    }

    // Test 2: Resize Test
    {
        std::cout << "\n=== TEST 2: RESIZING ===\n";
        StringQueue q2;

        std::cout << "Queue over capacity:\n";
        for (int i = 0; i < 9; i++) {
            // Fill queue to near capacity
            q2.enqueue(std::to_string(i));
        }

        // Display current queue and front index
        printQueueState(q2);  // [0, 1, 2, 3, 4, 5, 6, 7, 8]
    }

    // Test 3: Resize Test
    {
        std::cout << "\n=== TEST 3: FRONT INDEX ===\n";
        StringQueue q3;

        std::cout << "Queue up to capacity:\n";
        for (int i = 0; i < 8; i++) {
            // Fill queue to capacity
            q3.enqueue(std::to_string(i));
        }
        printQueueState(q3);  // [0, 1, 2, 3, 4, 5, 6, 7]

        std::cout << "Dequeuing until no values are left:\n";
        // Force wrap-around by dequeuing 1 and enqueuing 1 more
        for (int i = 0; i < 8; i++) {
            std::cout << q3.dequeue() << " ";
        }

        std::cout << "\nEnqueuing test value...\n";
        q3.enqueue("X");
        printQueueState(q3);

    }

    // Test 4: Copy constructor
    {
        std::cout << "\n=== TEST 4: COPY CONSTRUCTOR ===\n";
        StringQueue q4;
        q4.enqueue("Alpha");
        q4.enqueue("Beta");

        std::string sky = "blue";
        if (sky == "blue") {
            StringQueue qT1 = q4;  // Copy constructor
            std::cout << "Copied ";
            printQueueState(qT1);  // [Alpha, Beta]
        }

        std::cout << "Copied Queue now out of scope. Checking Original Queue.\n";
        printQueueState(q4); // [Alpha, Beta]
    }

    // Test 5: Temporary Move assignment
    {
        std::cout << "\n=== TEST 5: MOVE ASSIGNMENT ===\n";
        StringQueue q5;

        std::string sky = "blue";

        if (sky == "blue") {
            StringQueue qT2;
            qT2.enqueue("Testing");
            qT2.enqueue("Temporary");
            qT2.enqueue("Queue");

            std::cout << "Displaying Temporary Queue.\n";
            printQueueState(qT2);

            q5 = std::move(qT2);     // Move assignment
            std::cout << "Move-Assigning temporary Queue to existing (q5):\nDisplaying state before going out of scope.\n";
            printQueueState(q5);    // [Testing, Temporary, Queue]
        }

        std::cout << "Temporary queue now out of scope. Testing if original queue remains:\n";
        printQueueState(q5);            // [Testing, Temporary, Queue]
    }

    return 0;
}