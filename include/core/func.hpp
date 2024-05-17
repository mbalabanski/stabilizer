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
 * @brief Stores a function and arguments, where Function is a pure function
 */
class FunctionHandler
{
    void (*eval_func)();

public:
    FunctionHandler(void (*func)()) : 
        eval_func(func) { }

    inline void operator() ()
    {
        eval_func();
    }
};

} // core
} // sable

#endif // SABLE_CORE_FUNC_HPP
