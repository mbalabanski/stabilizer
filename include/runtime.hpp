#ifndef SABLE_RUNTIME_HPP
#define SABLE_RUNTIME_HPP

#include <core/runner.hpp>

#include <stats/single_var_stats.hpp>
#include <stats/t_dist.hpp>

namespace sable
{

enum HypothesisTest
{
    Null = 0,
    AlternateNEq = 1 << 0,
    AlternateGt  = 1 << 1,
    AlternateLt  = 1 << 2
};

struct TestResult
{
    stats::SingleVarStats runtime1, runtime2;
    double prob;
    double test_statistic;
    HypothesisTest hypotheses;
};

TestResult compare_runtime(
    void (*func1)(), void (*func2)(),
    const float alpha, const size_t n = 64
);

TestResult compare_runtime_multithreaded(
    void (*func1)(), void (*func2)(),
    const float alpha, const size_t n = 64,
    const size_t threads = std::thread::hardware_concurrency()
);

TestResult compare_runtime(
    const stats::SingleVarStats& rt1, 
    const stats::SingleVarStats& rt2,
    const float alpha
);

void output_test_result(const TestResult& result);


} // namespace sable



#endif