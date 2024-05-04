#ifndef SABLE_CORE_FUNC_HPP
#define SABLE_CORE_FUNC_HPP

#include <functional>
#include <tuple>
#include <utility>

#include <iostream>

namespace sable
{
namespace core
{

/**
 * @brief Stores a function and arguments
 * 
 * @tparam Func the function type
 * @tparam Args the argument types
 */
template<typename Func, typename... Args>
class FunctionHandler
{
    std::function<void(Args...)> eval_func;
    std::tuple<Args...> args;

public:
    FunctionHandler(Func&& f, Args&&... a) : 
        eval_func(std::forward<Func>(f)),
        args(std::forward<Args...>(a)...) { }

    void operator() ()
    {
        std::apply(eval_func, args);
    }


};

} // core
} // sable

#endif // SABLE_CORE_FUNC_HPP
