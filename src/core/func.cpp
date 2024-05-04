#include <core/func.hpp>

namespace sable
{
namespace core
{

template<typename Func, typename... Args>
FunctionHandler<Func, Args...>::FunctionHandler(Func&& f, Args&&... a) : 
        eval_func(std::forward<Func>(f)),
        args(std::forward<Args...>(a...))
{ }


template<typename Func, typename... Args>
void FunctionHandler<Func, Args...>::operator()()
{
    std::apply(eval_func, args);
}

}
}