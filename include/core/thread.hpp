#ifndef SABLE_CORE_THREAD_HPP
#define SABLE_CORE_THREAD_HPP

#include <atomic>
#include <condition_variable>
#include <mutex>
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

    Thread(std::thread&& t_);
    Thread(const Thread& other);

    Thread operator= (const Thread& other);

    ~Thread();

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

    void push(T val);
    void pop(T& out);

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
     * 
     */
    void run_task();

public:

    ThreadPool(const size_t size = std::thread::hardware_concurrency());
    ThreadPool(const ThreadPool& other);

    template<typename FunctionType>
    void push(FunctionType& t);

    ThreadSafeQueue<T> get_outputs();

    ThreadPool& operator=(const ThreadPool& other);

    ~ThreadPool();
};



} // namespace core
} // namespace sable



#endif