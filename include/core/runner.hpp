#ifndef SABLE_CORE_TASK_HPP
#define SABLE_CORE_TASK_HPP

#include <numeric>
#include <random>
#include <tuple>
#include <vector>

#include <core/func.hpp>
#include <core/thread.hpp>

#include <iostream>

namespace sable
{
namespace core
{

thread_local std::mt19937 rng;

template<typename Func, typename... Args>
class Runner
{
    typedef std::chrono::milliseconds SpeedUnit;
    typedef std::chrono::duration<double, std::milli> RunDuration;

    ThreadPool<RunDuration> pool;

    FunctionHandler<Func, Args...> func_handler;

    RunDuration run_task()
    {
        // generate random padding for stack and heap
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, 16);

        const size_t stack_size = dist(rng), heap_size = dist(rng);

        // create stack & heap buffer
        size_t* stack_padding = (size_t*) alloca(sizeof(size_t) * stack_size);
        std::unique_ptr<size_t> heap_padding(new size_t[heap_size]);
        
        
        //HeapPadding  heap_padding (heap_size);

        auto t1 = std::chrono::high_resolution_clock::now();
        func_handler();
        auto t2 = std::chrono::high_resolution_clock::now();

        auto ms = std::chrono::duration_cast<SpeedUnit>(t2 - t1);

        return static_cast<RunDuration>(ms);
    }

public:
    Runner(Func&& func, Args&&... args) : pool(),
        func_handler(func, args...)
        { }

    void run(size_t n)
    {
        // push n number of runners

        for (size_t i = 0; i < n; i++)
        {
            pool.push([&]() { return run_task(); });
        }

        // sync back threads
    }


    float runtime()
    {
        auto q = pool.get_outputs();

        for (auto item : q)
        {
            std::cout << item.count() << "\n";
        }

        return std::reduce(q.begin(), q.end()).count() / q.size();
    }

};

} // namespace core
} // namespace sable


#endif