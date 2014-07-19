#include <iostream>
#include <algorithm>
#include <queue>

#include <functional>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <ctime>

class Schedule {
    public:
        Schedule() {}
        Schedule(std::function<void()> func_, std::chrono::system_clock::time_point timestamp_) : timestamp(timestamp_), func(func_) {}

        bool operator<(const Schedule& other) const {
            return timestamp > other.timestamp;
        }

    public:
        std::chrono::system_clock::time_point timestamp;
        std::function<void()> func;
};

class Scheduler {
    public:
        Scheduler() : running(true) {
            thread.reset(new std::thread([this](){ this->loop(); }));
        }

        ~Scheduler() {
            running = false;
            Schedule schedule([](){}, std::chrono::system_clock::now());
            thread->join();
        }

        void loop() {
            while (running) {
                std::function<void()> todo;

                {
                    std::unique_lock<std::mutex> mlock(mutex_);
                    auto now = std::chrono::system_clock::now();

                    if (!queue_.empty() && queue_.top().timestamp <= now) {
                        todo = queue_.top().func;
                        queue_.pop();
                    }
                }

                if (todo)
                    todo();

                {
                    std::unique_lock<std::mutex> mlock(mutex_);
                    if (queue_.empty())
                        cond_.wait(mlock);
                    else
                        cond_.wait_until(mlock, queue_.top().timestamp);
                }
            }
        }

        void add(const Schedule& item) {
            std::unique_lock<std::mutex> mlock(mutex_);
            queue_.push(item);

            if (queue_.top().timestamp == item.timestamp) 
                cond_.notify_one();
        }

    private:
        std::unique_ptr<std::thread> thread;
        std::priority_queue<Schedule> queue_;
        std::mutex mutex_;
        std::condition_variable cond_;
        bool running;
};

void test() {
    std::time_t t2 = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "NOW       " << std::ctime(&t2) << std::endl;
}

void Task1(Scheduler & sch)
{
    std::cout << "OK1! " << std::endl;

    auto now = std::chrono::system_clock::now();

    {
        auto time1 = now + std::chrono::seconds(1);
        std::time_t t1 = std::chrono::system_clock::to_time_t(time1);
        std::cout << "SCHEDULED " << std::ctime(&t1) << std::endl;
        sch.add(Schedule(test, time1));
    }

    {
        auto time1 = now + std::chrono::seconds(3);
        std::time_t t1 = std::chrono::system_clock::to_time_t(time1);
        std::cout << "SCHEDULED " << std::ctime(&t1) << std::endl;
        sch.add(Schedule(test, time1));
    }

    {
        auto time1 = now + std::chrono::seconds(5);
        std::time_t t1 = std::chrono::system_clock::to_time_t(time1);
        std::cout << "SCHEDULED " << std::ctime(&t1) << std::endl;
        sch.add(Schedule(test, time1));
    }
}

int main() {
    auto now = std::chrono::system_clock::now();

    Scheduler sch;

    sch.add(Schedule([&sch](){ Task1(sch); }, now + std::chrono::seconds(5)));
    sch.add(Schedule([&sch](){ Task1(sch); }, now + std::chrono::seconds(15)));
    sch.add(Schedule([&sch](){ Task1(sch); }, now + std::chrono::seconds(20)));
    sch.add(Schedule(test, now + std::chrono::seconds(2)));

    getchar();

    return 0;
}

