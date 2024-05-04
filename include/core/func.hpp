#ifndef SABLE_CORE_FUNC_HPP
#define SABLE_CORE_FUNC_HPP

#include <functional>
#include <tuple>
#include <utility>

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
    FunctionHandler(Func&& f, Args&&... a);

    void operator() ();

};

} // core
} // sable

#endif // SABLE_CORE_FUNC_HPP
