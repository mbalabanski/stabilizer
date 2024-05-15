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
    AlternateNEq = 1 << 1,
    AlternateGt  = 1 << 2,
    AlternateLt  = 1 << 3
};

HypothesisTest compare_runtime(
    void (*func1)(), void (*func2)(),
    const float alpha
);


} // namespace sable



#endif