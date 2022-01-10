#include "queue.h"
#include <iostream>

int main()
{
    queue::Queue<int, 2> q;
    for (int i = 0; i < 3; i++)
    {
        try
        {
            q.enqueue(67+i);
        }
        catch (queue::QOverflow &e)
        {
            std::cout << "Queue overflow" << std::endl;
        }
    }
    for (int i = 0; i < 2; i++)
    {
        try
        {
            std::cout << q.dequeue() << std::endl;
        }
        catch (queue::QUnderflow &e)
        {
            std::cout << "Queue is empty" << std::endl;
        }
    }
    std::cout << q << std::endl;
    std::cout << q.size() << std::endl;

    q.enqueue(67);
    q.enqueue(68);
    // call the function here to cast the queue
    queue::Queue<float, 2> q1 = q.cast<float>();
    std::cout << q1.dequeue() / 2 << std::endl;

}