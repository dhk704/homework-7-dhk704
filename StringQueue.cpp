#include "StringQueue.h"
#include <iostream>

// Default constructor
StringQueue::StringQueue()
    : m_data(nullptr), m_dataSize{8} {
    std::cout << "Default construct queue" << std::endl;
}

// Destructor
StringQueue::~StringQueue() {
    std::cout << "Destruct queue" << std::endl;
    delete[] m_data;
}


size_t StringQueue::size() const {
    return m_count;
}

size_t StringQueue::capacity() const {
    return m_dataSize;
}

void StringQueue::clear() {
    m_count = 0;
    m_front = 0;
    m_rear = 0;
}

std::string StringQueue::dequeue() {
    // NEEDS WORK: Move element at front of queue to temp string, increment m_front if end is reached
    if (m_count > 0) {
        --m_count;
        // Return temp string
        return m_data[m_count];
    }
    else {
        throw std::runtime_error("Can't dequeue an empty queue");
    }
}

