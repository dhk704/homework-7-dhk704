#ifndef STRINGQUEUE_H
#define STRINGQUEUE_H
#include <string>

class StringQueue {
    // An array in dynamic memory that stores the elements of the queue.
    std::string* m_data;
    // The length of the currently-used m_data array, initially 8.
    size_t m_dataSize;
    // The number of elements that are still in the queue, initially 0
    size_t m_count = {0};
    // The index of where the "front" element is stored, initially 0.
    size_t m_front = {0};
    // The index of where the next element to be enqueued will be placed; changed to int type and -1 to account for having empty queue
    int m_rear = {-1};

public:
    // Default constructor
    StringQueue();

    // Destructor that frees the m_data array
    ~StringQueue();

    // Copy constructor that performs a deep copy of its parameter
    StringQueue(const StringQueue& other);

    // Move Constructor
    StringQueue(StringQueue&& other);

    // Copy assignment operator
    StringQueue& operator=(const StringQueue& rhs);

    // Move assignment operator
    StringQueue& operator=(StringQueue&& rhs);

    // Returns the number of elements in the queue
    size_t size() const;
    // Returns the number of elements that could be added to the queue without requiring it to resize.
    size_t capacity() const;

    // Getter Functions to satisfy Test 3
    size_t get_front() const { return m_front; }
    int get_rear() const { return m_rear; }

    // Reset values
    void clear();
    // First resizes the queue if its capacity is 0; and then moves the value into m_data at the index specified by m_rear. m_rear is incremented, resetting back to 0 if it has reached the end of the data array
    void enqueue(std::string value);
    // Moves the element at the front of the queue into a temporary string, increments m_front (wrapping back to 0 if necessary), and returns the temporary
    std::string dequeue();

    friend std::ostream& operator<<(std::ostream& lhs, const StringQueue& rhs);
};

#endif //STRINGQUEUE_H
