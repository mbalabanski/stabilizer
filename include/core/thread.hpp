#ifndef SABLE_CORE_THREAD_HPP
#define SABLE_CORE_THREAD_HPP

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include <iostream>

namespace sable
{
namespace core
{
    
/**
 * @brief RAII wrapper for std::thread
 */
class ThreadJoiner
{
    std::vector<std::thread>& vec;

public:

    explicit ThreadJoiner(std::vector<std::thread>& ts) : vec(ts) { }
    ThreadJoiner(const ThreadJoiner& other) = delete;

    ThreadJoiner operator= (const ThreadJoiner& other) = delete;

    ~ThreadJoiner()
    {
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i].joinable())
            {
                vec[i].join();
            }
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

    ThreadJoiner joiner;
    std::vector<std::thread> threads;

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

    ThreadPool(const size_t size = std::thread::hardware_concurrency()) : threads(), joiner(threads)
    {
        // initialize threads
        try
        {
            for (size_t i = 0; i < size; i++)
            {
                threads.push_back(
                    std::thread(&ThreadPool::run_task, this)
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

    void push(std::function<T()> f)
    {
        tasks.push(f);
    }

    std::vector<T> get_outputs()
    {
        // pop all items in queue and add to vector
        std::vector<T> out_vec;

        T curr;

        while (!out.empty())
        {
            out.pop(curr);
            out_vec.push_back(curr);
        }

        return out_vec;
    }

    ThreadPool& operator=(const ThreadPool& other) = delete;

    bool finished()
    {
        return done.load(std::memory_order_acquire);
    }


    ~ThreadPool()
    {
        done = true;
    }
};





} // namespace core
} // namespace sable



#endif