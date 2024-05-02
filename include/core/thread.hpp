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
    T pop();

};

template<typename T>
class ThreadPool
{
    std::atomic<bool> done;
    std::mutex queue_accessor;
    ThreadSafeQueue<std::function<T()>> tasks;
    std::vector<Thread> threads;

    std::vector<T> out;

    void run_task();

public:

    ThreadPool(const size_t size = std::thread::hardware_concurrency());

    template<typename FunctionType>
    void push(FunctionType& t);

    std::vector<T> get_outputs();

    ~ThreadPool();
};



} // namespace core
} // namespace sable



#endif