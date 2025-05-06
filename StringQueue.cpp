#include "StringQueue.h"

#include <algorithm>
#include <iostream>
#include <utility>

// DEFAULT CONSTRUCTOR
StringQueue::StringQueue()
    : m_data(new std::string[8]),
      m_dataSize(8) {
    clear();
}

// DESTRUCTOR
StringQueue::~StringQueue() {
    delete[] m_data;
}

// COPY CONSTRUCTOR
StringQueue::StringQueue(const StringQueue& other)
    : m_data{new std::string[other.m_dataSize]},
      m_dataSize{other.m_dataSize},
      m_count{other.m_count},
      m_front{other.m_front},
      m_rear{other.m_rear}  {
    for (size_t i = 0; i < m_count; ++i) {
        m_data[i] = other.m_data[i];
    }
}

// MOVE CONSTRUCTOR
StringQueue::StringQueue(StringQueue &&other)
    : m_data{other.m_data},
      m_dataSize{other.m_dataSize},
      m_count{other.m_count},
      m_front{other.m_front},
      m_rear{other.m_rear} {
    other.m_data = nullptr;
    other.m_dataSize = 0;
    // FIX: Bryan mentioned don't use clear function? But assignment requires usage?
    other.clear();
}

// COPY ASSIGNMENT OPERATOR
StringQueue& StringQueue::operator=(const StringQueue& rhs) {
    // Check if copy-assigning to oneself.
    if (this == &rhs) {
        return *this;
    }

    // Free m_data array
    m_count = rhs.m_count;
    m_dataSize = rhs.m_dataSize;
    m_front = rhs.m_front;
    m_rear = rhs.m_rear;

    delete[] m_data;
    m_data = new std::string[m_dataSize];


    // Override lhs with deep copy of rhs
    for (size_t i = 0; i < m_dataSize; ++i) {
        m_data[i] = rhs.m_data[i];
    }
    return *this;
}

// MOVE ASSIGNMENT OPERATOR
StringQueue& StringQueue::operator=(StringQueue &&rhs) {
    if (this == &rhs) {
        return *this;
    }

    // Delete current lhs array
    delete[] m_data;

    // Take over rhs array via shallow copy
    m_count = rhs.m_count;
    m_dataSize = rhs.m_dataSize;
    m_front = rhs.m_front;
    m_rear = rhs.m_rear;

    // Reset rhs' values without making it delete array
    rhs.m_data = nullptr;
    rhs.m_dataSize = 0;
    rhs.m_dataSize = 0;
    rhs.clear();

    return *this;
}

// Return number of elements in the queue
size_t StringQueue::size() const {
    return m_count;
}

// Return number of elements that COULD be added to queue without needing to resize
size_t StringQueue::capacity() const {
    return m_dataSize - m_count;
}

void StringQueue::clear() {
    m_count = 0;
    m_front = 0;
    m_rear = 0;
}

void StringQueue::enqueue(std::string value) {
    // Resize with doubled capacity if full
    if (capacity() == 0) {
        std::string *newData{new std::string[m_dataSize * 2]};

        for (size_t i = 0; i < m_dataSize; ++i) {
            newData[i] = m_data[i];
        }
        // Sort old data from
        std::sort(newData, newData + m_dataSize);
        m_dataSize *= 2;

        delete[] m_data;
        m_data = newData;
        m_front = 0;
        ++m_count;
        m_rear = m_count - 1;
    }

    // Use modulus to account for m_rear reaching capacity of queue, and loop back to 0.
    if (m_count == 0)
    {
        clear();
    }
    else
    {
        m_rear = (m_rear + 1) % m_dataSize;
    }
    m_data[m_rear] = std::move(value);
    // Increment m_count as # of elements have increased
    ++m_count;
}

std::string StringQueue::dequeue() {
    if (m_count == 0) {
        // Throw error if queue is empty
        throw std::runtime_error("Can't dequeue an empty queue");
    }

    // Move front element into temp string and reassign m_front index (similar case to m_rear)
    std::string temp = std::move(m_data[m_front]);
    m_front = (m_front + 1) % m_dataSize;
    // Decrement m_count to account for element being dequeued
    --m_count;

    // Return dequeued string element
    return temp;
}

std::ostream& operator<<(std::ostream& os, const StringQueue& rhs) {
    // ERROR HANDLE FOR EMPTY QUEUE
    if (rhs.m_count == 0)
    {
        // Indicate if queue is empty
        throw std::runtime_error("Queue is empty.");
    }
    for (size_t i = 0; i < rhs.m_count; ++i) {
        if (i != 0) {
            os << ", ";
        }
        // Iterate using modulus operand as m_count doesn't account for index values of front and rear
        os << rhs.m_data[(rhs.m_front + i) % rhs.m_dataSize];
    }

    return os;
}
