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

HypothesisTest compare_runtime(
    void (*func1)(), void (*func2)(),
    const float alpha, const size_t n = 64
);


} // namespace sable



#endif