//
// Created by studone on 12/26/21.
//

#ifndef PASSAU_CPLUSPLUS_OOP_QUEUE_H
#define PASSAU_CPLUSPLUS_OOP_QUEUE_H

#include <vector>
#include <iostream>

namespace queue {

    class QOverflow : public std::exception {
        const char * what () const throw ()
        {
            return "Queue overflow occurred";
        }
    };

    class QUnderflow : public std::exception {
        const char * what () const throw ()
        {
            return "Queue underflow occurred";
        }
    };

    template<typename T, int N>
    class Queue
    {
    private:
        std::vector<T> elems;

    public:
        Queue() {
            elems.reserve(N);
        }

        template<typename U>
        Queue(Queue<U, N>& obj) {
            std::vector<U> el = obj.getElems();
            std::vector<T> vec(el.begin(), el.end());
            elems = vec;
        }

        std::vector<T> getElems() {
            return elems;
        }

        ~Queue()
        {
            elems.clear();
        }

        void enqueue(T value)
        {
            if(elems.size() == N) {
                throw QOverflow();
            }
            elems.push_back(value);
        }

        T dequeue()
        {
            if(elems.size() == 0) {
                throw QUnderflow();
            }
            T value = elems.front();
            elems.erase(elems.begin());
            return value;
        }

        size_t size()
        {
            return elems.size();
        }

        bool isEmpty()
        {
            return elems.empty();
        }

        friend std::ostream& operator<<(std::ostream& os, const Queue<T, N>& q)
        {
            for (auto& i : q.elems)
            {
                std::cout << i << " ";
            }
            return os;
        }

        template<typename U>
        Queue<U, N> cast(void) {
            return Queue<U, N>(*this);
        }
    };
}

#endif //PASSAU_CPLUSPLUS_OOP_QUEUE_H
