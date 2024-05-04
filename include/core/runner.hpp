#ifndef SABLE_CORE_TASK_HPP
#define SABLE_CORE_TASK_HPP

#include <random>
#include <tuple>
#include <vector>

#include <core/func.hpp>
#include <core/padding.hpp>
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

    FunctionHandler<Func, Args...> func_handler;

    RunDuration run_task();

public:
    Runner(Func&& func, Args&&... arg);

    void run(size_t n);

    float runtime();
};



} // namespace core
} // namespace sable


#endif