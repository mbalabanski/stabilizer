#ifndef SABLE_WATCH_FUNCTION_HPP
#define SABLE_WATCH_FUNCTION_HPP

#include <filesystem>
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
 * Evaluates to nullopt if there is no previous function data, or if it is unable to read from the `sable/{name}.csv` file.
 * 
 * @param name name of the function alias
 * @param func function to evaluate
 * @param trials number of samples to collect (instances of running function)
 * @param alpha significance 
 */
std::optional<TestResult> watch_function(
    const std::string& name, 
    void (*func)(), 
    size_t trials,
    float alpha
);


/**
 * @brief Evaluates runtime performance on a function and compares it to the last time it ran. 
 * 
 * Evaluates to nullopt if there is no previous function data, or if it is unable to read from the `sable/{name}.csv` file.
 * 
 * @param name name of the function alias
 * @param func function to evaluate
 * @param trials number of samples to collect (instances of running function)
 * @param alpha significance 
 */
std::optional<TestResult> watch_function(
    const char* name,
    void (*func)(),
    size_t trials,
    float alpha
);


} // namespace sable


#endif