#ifndef SABLE_RUNTIME_HPP
#define SABLE_RUNTIME_HPP

#include <core/runner.hpp>

#include <stats/single_var_stats.hpp>
#include <stats/t_dist.hpp>

namespace sable
{

/**
 * @brief Stores the results of a hypothesis test as a bitflag.  
 * Contains four possible outcomes: 
 * - Null,
 * - Alternate Hypothesis: Not Equal, 
 * - Alternate Hypothesis: Greater Than,
 * - Alternate Hypothesis: Less Than
 * 
 * 
 */
enum HypothesisTest
{
    Null = 0,
    AlternateNEq = 1 << 0,
    AlternateGt  = 1 << 1,
    AlternateLt  = 1 << 2
};

/**
 * @brief Holds the result of a hypothesis test, including runtimes, the student's t test statistic, probability, and hypotheses flags.
 * 
 */
struct TestResult
{
    stats::SingleVarStats runtime1, runtime2;
    double prob;
    double test_statistic;
    HypothesisTest hypotheses;
};

/**
 * @brief Compares the means of two runtimes using a student's t-test.
 * 
 * @param rt1 Runtime 1
 * @param rt2 Runtime 2
 * @param alpha significance level
 * @return TestResult the test result for the two runtimes
 */
TestResult compare_runtime(
    const stats::SingleVarStats& rt1, 
    const stats::SingleVarStats& rt2,
    const float alpha
);

/**
 * @brief Compares the runtimes of two functions using a student's t-test
 * 
 * @note These functions must not take any arguments and must be pure -- i.e. must not rely or have an effect on any outside variables.
 * Doing so causes a dependency on an outside variable, which may skew the function's runtime on other factors.
 * 
 * @param func1 Function 1
 * @param func2 Function 2
 * @param alpha significance Level
 * @param n number of trials
 * @return TestResult the test result for the two functions
 */
TestResult compare_runtime(
    void (*func1)(), void (*func2)(),
    const float alpha, const size_t n = 64
);

/**
 * @brief Compares the runtimes of two functions in parallel using a student's t-test 
 * 
 * @note These functions must not take any arguments and must be pure -- i.e. must not rely or have an effect on any outside variables.
 * Doing so causes a dependency on an outside variable, which may skew the function's runtime on other factors and 
 * additionally could cause a race condition or deadalock.
 * 
 * @param func1 Function 1
 * @param func2 Function 2
 * @param alpha significance level
 * @param n number of trials
 * @param threads number of threads (defaults to `std::thread::hardware_concurrency()`)
 * @return TestResult the test result for the two functions
 */
TestResult compare_runtime_multithreaded(
    void (*func1)(), void (*func2)(),
    const float alpha, const size_t n = 64,
    const size_t threads = std::thread::hardware_concurrency()
);



/**
 * @brief Convenience displayer for printing a test result to stdout.
 * 
 * @param result the result to output
 */
void output_test_result(const TestResult& result);

} // namespace sable

#endif