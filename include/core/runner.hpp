#ifndef SABLE_CORE_TASK_HPP
#define SABLE_CORE_TASK_HPP

#include <numeric>
#include <random>
#include <tuple>
#include <vector>

#include <core/func.hpp>
#include <core/thread.hpp>

#include <iostream>

#include <stats/single_var_stats.hpp>

namespace sable
{
namespace core
{

namespace
{

thread_local std::mt19937 rng;

}

class Runner
{
    
public:
    typedef std::chrono::nanoseconds SpeedUnit;
    typedef std::chrono::duration<double, std::nano> RunDuration;

private:

    std::vector<RunDuration> runtimes;
    std::mutex runtimes_accessor;

    FunctionHandler func_handler;

    RunDuration run_task();

    void run_single_thread(size_t n);
    void run_multi_thread(size_t n, size_t threads=std::thread::hardware_concurrency());

public:
    Runner(void (*func)()) : func_handler(func) { }

    void run(size_t n, bool multithreaded=false);


    stats::SingleVarStats runtime();

};

} // namespace core
} // namespace sable


#endif