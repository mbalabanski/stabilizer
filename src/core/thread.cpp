#include <core/thread.hpp>

namespace sable
{
namespace core
{

// RAII thread wrapper

Thread::Thread(std::thread&& t_) : t(std::move(t_)) { }

Thread::Thread(const Thread& other) = delete;
Thread Thread::operator=(const Thread& other) = delete;

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
T ThreadSafeQueue<T>::pop()
{
    std::unique_lock<std::mutex> lock(mut);
    cond.wait(lock, [&] { return !queue.empty(); });
    T val(std::move(queue.front()));
    queue.pop();
    return val;
}




} // namespace core
} // namespace sable
