#ifndef SABLE_CORE_TASK_HPP
#define SABLE_CORE_TASK_HPP

#include <core/thread.hpp>

namespace sable
{
namespace core
{
    

template<typename Func, typename... Args>
class Runner
{
    typedef std::chrono::milliseconds SpeedUnit;
    typedef std::chrono::duration<double, std::milli> RunDuration;

    ThreadPool<float> pool;

    Func eval_func;
    Args args;

    RunDuration run_task();

public:
    Runner(Func func, Args... arg);

    void run();
};



} // namespace core
} // namespace sable


#endif