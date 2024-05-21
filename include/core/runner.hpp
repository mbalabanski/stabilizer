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

    //ThreadPool<RunDuration> pool;
    std::vector<RunDuration> runtimes;

    FunctionHandler func_handler;

    RunDuration run_task();

public:
    Runner(void (*func)()) : func_handler(func) { }

    void run(size_t n);


    stats::SingleVarStats runtime();

};

} // namespace core
} // namespace sable


#endif