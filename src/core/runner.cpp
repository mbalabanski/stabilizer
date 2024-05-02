#include <core/runner.hpp>

#include <chrono>

namespace sable
{
namespace core
{


template<typename Func, typename... Args>
Runner<Func, Args...>::Runner(Func f, Args... a) : eval_func(f), args(a) { }

template<typename Func, typename... Args>
Runner<Func, Args...>::RunDuration Runner<Func, Args...>::run_task()
{
    auto t1 = std::chrono::high_resolution_clock::now();
    eval_func(args...);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto ms = std::chrono::duration_cast<SpeedUnit>(t2 - t1);
    return static_cast<RunDuration>(ms);
}

template<typename Func, typename... Args>
void Runner<Func, Args...>::run() 
{
    throw std::exception("Not implemented");
}


} // namespace core
} // namespace sable
