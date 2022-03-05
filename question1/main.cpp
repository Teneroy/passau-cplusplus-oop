#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <queue>
#include <mutex>
#include <atomic>

inline std::mutex monitor;
std::atomic<bool> finished = false;

class WaitingRoomQueue
{
private:
    std::deque<int> elems;
    WaitingRoomQueue() = default;

public:
    void enqueue(int i) {
        elems.push_back(i);
    }
    int dequeue() {
        int i = elems.front();
        elems.pop_front();
        return i;
    }
    bool empty() {
        return elems.empty();
    }
    int size() {
        return static_cast<int> (elems.size());
    }
    static WaitingRoomQueue &getInstance() {
        static WaitingRoomQueue sharedQueue;
        return sharedQueue;
    }
};

class ThreadGroup {
public:
    ThreadGroup() = default;
    ThreadGroup(const ThreadGroup&) = delete;
    ThreadGroup& operator=(const ThreadGroup&) = delete;
    template <typename F> void add_thread(F& f, int id) {
        threads.emplace_back(std::ref(f), id); // Thread speichern und starten
    }
    void join_all() { // Auf Beendigung aller Threads warten
        for (auto& t : threads) {
            t.join();
        }
    }
    std::size_t size() const { return threads.size(); }
private:
    std::vector<std::thread> threads;
};

void treatPatient()
{
    monitor.lock();
    int i = WaitingRoomQueue::getInstance().dequeue();
    monitor.unlock();
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1, 5); //range is 20 to 22
    int time_treat = static_cast<int>(dist(mt));
    //int time_treat = 5;
    std::cout << "treating a patient with id: " << i << " for " << time_treat << " seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(time_treat));
}

void getRest()
{
    std::cout << "Doctor is taking a rest before patients arrive" << std::endl;
    while (!finished || !WaitingRoomQueue::getInstance().empty()) {
        monitor.lock();
        bool hasPatients = WaitingRoomQueue::getInstance().empty();
        monitor.unlock();
        if(!hasPatients) {
            treatPatient();
        }
    }
    std::cout << "doctor's day is finished" << std::endl;
}

void waitingRoom(int i)
{
    std::lock_guard<std::mutex> lock(monitor);
    if(WaitingRoomQueue::getInstance().size() == 5) {
        std::cout << "waiting room is full, patient with id: " << i << " left home" << std::endl;
        return;
    }

    WaitingRoomQueue::getInstance().enqueue(i);
    std::cout << "patient with id: " << i << " is waiting for treatment" << std::endl;
}

int main() {
    ThreadGroup threadGroup;
    std::thread doctor(getRest);

    for(int i = 0; i < 40; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        threadGroup.add_thread(waitingRoom, i);
    }
    finished = true;

    threadGroup.join_all();
    std::cout << threadGroup.size() << std::endl;
    doctor.join();

    return 0;
}