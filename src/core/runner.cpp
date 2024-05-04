#include <core/runner.hpp>

#include <chrono>

namespace sable
{
namespace core
{

thread_local std::mt19937 rng;

template<typename Func, typename... Args>
Runner<Func, Args...>::Runner(Func&& f, Args&&... a) : 
        func_handler(f, a...),
        pool() { }


template<typename Func, typename... Args>
typename Runner<Func, Args...>::RunDuration Runner<Func, Args...>::run_task()
{
    // generate random padding for stack and heap
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 16);

    const size_t stack_size = dist(rng), heap_size = dist(rng);

    // create stack & heap buffer
    StackPadding stack_padding(stack_size);
    HeapPadding  heap_padding (heap_size);

    auto t1 = std::chrono::high_resolution_clock::now();
    func_handler();
    auto t2 = std::chrono::high_resolution_clock::now();

    auto ms = std::chrono::duration_cast<SpeedUnit>(t2 - t1);
    return static_cast<RunDuration>(ms);
}

template<typename Func, typename... Args>
void Runner<Func, Args...>::run(size_t n) 
{
    // push n number of runners

    for (size_t i = 0; i < n; i++)
    {
        pool.push(&run_task);
    }

    // sync back threads
    while (!pool.finished()) { }
}

template<typename Func, typename... Args>
float Runner<Func, Args...>::runtime()
{
    float sum = 0;
    float size = 0;
    ThreadSafeQueue<float> q = pool.get_outputs();

    float curr;

    while (!q.empty())
    {
        q.pop(curr);
        sum += curr;
        size += 1;
    }

    return sum / size;
}


} // namespace core
} // namespace sable
