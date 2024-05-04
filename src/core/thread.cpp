#include <core/thread.hpp>

namespace sable
{
namespace core
{

// RAII thread wrapper

Thread::Thread(std::thread&& t_) : t(std::move(t_)) { }

Thread::~Thread() 
{
    if (t.joinable())
    {
        t.join();
    }
}


// ThreadSafeQueue

template<typename T>
void ThreadSafeQueue<T>::push(T val)
{
    std::lock_guard<std::mutex> lock(mut);
    queue.push(val);
    cond.notify_one();
}

template<typename T>
void ThreadSafeQueue<T>::pop(T& out)
{
    std::unique_lock<std::mutex> lock(mut);
    cond.wait(lock, [&] { return !queue.empty(); });
    out = std::move(queue.front());
    queue.pop();
}

template<typename T>
bool ThreadSafeQueue<T>::empty()
{
    return queue.empty();
}

// ThreadPool

template<typename T>
ThreadPool<T>::ThreadPool(const size_t size) : done(false) 
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

template<typename T>
void ThreadPool<T>::run_task()
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

template<typename T>
template<typename FunctionType>
void ThreadPool<T>::push(FunctionType& f)
{
    tasks.push(std::function<T()>(f));
}

template<typename T>
ThreadSafeQueue<T> ThreadPool<T>::get_outputs()
{
    return out;
}

template<typename T>
std::atomic<bool> ThreadPool<T>::finished()
{
    return done;
}

template<typename T>
ThreadPool<T>::~ThreadPool()
{
    done = true;
}



} // namespace core
} // namespace sable
