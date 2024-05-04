#ifndef SABLE_CORE_THREAD_HPP
#define SABLE_CORE_THREAD_HPP

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace sable
{
namespace core
{
    
/**
 * @brief RAII wrapper for std::thread
 */
class Thread
{
    std::thread t;

public:

    Thread(std::thread&& t_) : t(std::move(t_)) { }
    Thread(const Thread& other) = delete;

    Thread operator= (const Thread& other) = delete;

    ~Thread()
    {
        if (t.joinable())
        {
            t.join();
        }
    }

};

/**
 * @brief Threadsafe wrapper for queue
 * 
 * @tparam T data type
 */
template<typename T>
class ThreadSafeQueue
{
    std::mutex mut;
    std::queue<T> queue;
    std::condition_variable cond;

public:

    void push(T val)
    {
        std::lock_guard<std::mutex> lock(mut);
        queue.push(val);
        cond.notify_one();
    }

    void pop(T& out)
    {
        std::unique_lock<std::mutex> lock(mut);
        cond.wait(lock, [&] { return !queue.empty(); });
        out = std::move(queue.front());
        queue.pop();
    }

    bool empty()
    {
        return queue.empty();
    }
};

template<typename T>
class ThreadSafeVector
{
    std::mutex mut;
    std::vector<T> vec;
    std::condition_variable cond;

public:

};

/**
 * @brief Implements a thread pool structure
 * 
 * @tparam T return type of thread action
 */
template<typename T>
class ThreadPool
{
    std::atomic<bool> done;
    std::mutex queue_accessor;
    ThreadSafeQueue<std::function<T()>> tasks;
    std::vector<Thread> threads;

    ThreadSafeQueue<T> out;

    /**
     * @brief Run task for each thread in ```ThreadPool::threads```
     */
    void run_task()
    {
        while (!done)
        {
            // while not done, keep trying to perform tasks
            std::function<T()> task;
            tasks.pop(task);

            if (task)
            {
                T task_out(task());
                out.push(task_out);
            }
            else
            {
                // all tasks are taken
                std::this_thread::yield();
            }
        }
    }


public:

    ThreadPool(const size_t size = std::thread::hardware_concurrency())
    {
        // initialize threads
        try
        {
            for (size_t i = 0; i < size; i++)
            {
                threads.push_back(
                    Thread(std::thread(&ThreadPool::run_task, this))
                );
            }
        }
        catch(const std::exception& e)
        {
            done = true;
            throw;
        }
    }


    ThreadPool(const ThreadPool& other) = delete;

    template<typename FunctionType>
    void push(FunctionType&& t)
    {
        tasks.push(std::function<T()>(f));
    }

    ThreadSafeQueue<T> get_outputs()
    {
        return out;
    }

    ThreadPool& operator=(const ThreadPool& other) = delete;

    std::atomic<bool> finished()
    {
        return done;
    }


    ~ThreadPool()
    {
        done = true;
    }
};





} // namespace core
} // namespace sable



#endif