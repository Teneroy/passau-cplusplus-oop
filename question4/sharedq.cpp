#include "sharedq.h"
#include <stdexcept>

unsigned int SharedQueue::reference_count;

void SharedQueue::enqueue(int i)
{
    elems.push_back(i);
}

int SharedQueue::dequeue()
{
    int i = elems.front();
    elems.pop_front();
    return i;
}

bool SharedQueue::empty()
{
    return elems.empty();
}

int SharedQueue::size()
{
    return elems.size();
}

unsigned int SharedQueue::num_references()
{
    return reference_count;
}

SharedQueue::~SharedQueue()
{
    reference_count--;
}

SharedQueue &SharedQueue::getInstance()
{
    static SharedQueue sharedQueue;
    return sharedQueue;
}

SharedQueue::SharedQueue(const SharedQueue &other)
{
    if(reference_count + 1 > 10) {
        throw std::runtime_error("At a given time, no more than 10 variables can share the queue");
    }
    reference_count++;
}

SharedQueue &SharedQueue::operator=(const SharedQueue &rhs)
{
    return *this;
}

std::ostream &operator<<(std::ostream &os, const SharedQueue &sq)
{
    for (auto &i : sq.elems)
    {
        os << i << " ";
    }
    os << std::endl;
    return os;
}