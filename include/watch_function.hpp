#ifndef SABLE_WATCH_FUNCTION_HPP
#define SABLE_WATCH_FUNCTION_HPP

#include <optional>
#include <string>

#include <core/io.hpp>
#include <core/runner.hpp>

#include <runtime.hpp>

namespace sable
{

/**
 * @brief Evaluates runtime performance on a function and compares it to the last time it ran. 
 * 
 * @param name name of the function alias
 * @param func function to evaluate
 */
std::optional<TestResult> watch_function(
    const std::string& name, 
    void (*func)(), 
    size_t trials,
    float alpha
);


} // namespace sable


#endif