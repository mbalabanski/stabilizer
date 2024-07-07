#ifndef SABLE_CORE_TASK_HPP
#define SABLE_CORE_TASK_HPP

#include <numeric>
#include <random>
#include <tuple>
#include <thread>
#include <vector>

#include <core/func.hpp>

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

/**
 * @brief Implements logic for measuring a function runtime.
 * 
 */
class Runner
{
    
public:
    typedef std::chrono::nanoseconds SpeedUnit;
    typedef std::chrono::duration<double, std::nano> RunDuration;

private:

    // Holds function runtimes
    std::vector<RunDuration> runtimes;

    // Handles a function pointer
    FunctionHandler func_handler;

    /**
     * @brief Runs and measures a single iteration of a function's runtime performance.
     * Implements stack and heap paddings.
     * 
     * @return RunDuration duration it took for function to be executed.
     */
    RunDuration run_task();

    void run_single_thread(size_t n);
    void run_multi_thread(size_t n, size_t threads=std::thread::hardware_concurrency());

public:
    Runner(void (*func)()) : func_handler(func) { }

    /**
     * @brief Measures function runtime, and writes data to `Runner::runtimes`
     * 
     * @param n number of iterations to test
     * @param multithreaded determines whether the functions run in parallel
     */
    void run(size_t n, bool multithreaded=false);

    /**
     * @brief Accessor for `Runner::runtimes`, and returns general stats (mean, stddev, ...) for runtime data
     * 
     * @return stats::SingleVarStats single variable stats for runtimes
     */
    stats::SingleVarStats runtime();

};

} // namespace core
} // namespace sable


#endif