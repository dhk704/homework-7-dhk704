#include "StringQueue.h"

#include <algorithm>
#include <iostream>

// DEFAULT CONSTRUCTOR
StringQueue::StringQueue()
    : m_data(nullptr), m_dataSize{8} {
    std::cout << "Default construct queue" << std::endl;
}

// DESTRUCTOR
StringQueue::~StringQueue() {
    std::cout << "Destruct queue" << std::endl;
    delete[] m_data;
}

// COPY CONSTRUCTOR
StringQueue::StringQueue(const StringQueue& other)
    : m_data{new std::string[other.m_dataSize]}, m_dataSize{other.m_dataSize}, m_count{other.m_count}, m_front{other.m_front}, m_rear{other.m_rear}
{
    for (size_t i = 0; i < m_count; ++i) {
        m_data[i] = other.m_data[i];
    }
}

// COPY ASSIGNMENT OPERATOR
StringQueue& StringQueue::operator=(const StringQueue& rhs) {
    // Check if copy-assigning to oneself.
    if (this == &rhs) {
        return *this;
    }

    // Free m_data array
    delete[] m_data;
    m_data = new std::string[m_dataSize];
    m_count = rhs.m_count;
    m_dataSize = rhs.m_dataSize;
    m_front = rhs.m_front;
    m_rear = rhs.m_rear;

    // Override lhs with deep copy of rhs
    for (size_t i = 0; i < m_dataSize; ++i) {
        m_data[i] = rhs.m_data[i];
    }
    return *this;
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
    other.clear();
}

// MOVE ASSIGNMENT OPERATOR
StringQueue& StringQueue::operator=(StringQueue &&rhs) {
    if (this == &rhs) {
        return *this;
    }

    // Delete current array
    delete[] m_data;

    // Take over rhs array via shallow copy
    m_data = rhs.m_data;
    m_dataSize = rhs.m_dataSize;
    m_count = rhs.m_count;
    m_front = rhs.m_front;
    m_rear = rhs.m_rear;

    // Reset rhs' values without making it delete array
    rhs.m_data = nullptr;
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
    std::string *newData{new std::string[m_dataSize * 2]};

    if (capacity() == 0) {
        for (size_t i = 0; i < m_dataSize; ++i) {
            newData[i] = m_data[i];
        }
        // Sort old data from
        std::sort(newData->begin(), newData->end());
        m_dataSize *= 2;

        delete[] m_data;
        m_data = newData;
    }

    // Come back to this...would this overwrite the last value within queue?
    m_data[m_count] = std::move(value);
    m_rear = m_count;
    ++m_count;
}
std::string StringQueue::dequeue() {
    // NEEDS WORK: Move element at front of queue to temp string, increment m_front if end is reached
    if (m_count > 0) {
        --m_count;
        std::string temp = m_data[m_front];

        if (m_front != m_rear) {
            ++m_front;
        }
        // Return temp string
        return temp;
    }
    else {
        throw std::runtime_error("Can't dequeue an empty queue");
    }
}

std::ostream& operator<<(std::ostream& os, const StringQueue& rhs) {

}
