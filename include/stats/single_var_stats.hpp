#ifndef SABLE_STATS_1_VAR_STATS_HPP
#define SABLE_STATS_1_VAR_STATS_HPP

#include <cmath>
#include <numeric>
#include <vector>

namespace sable
{
namespace stats
{

namespace
{

template<typename T>
auto calc_variance(const std::vector<T>& vec, const double mean, const size_t n) -> T
{
    if (n <= 1) { return static_cast<T>(0); }

    auto func = [&](const T& val)
    {
        return ((val - mean) * (val - mean) / (n - 1));
    };

    return static_cast<T>(sqrtl(std::transform_reduce(vec.begin(), vec.end(), 0.0, std::plus{}, func ) ));
}
   
template double calc_variance<double>(const std::vector<double>& vec, const double mean, const size_t );

}

struct SingleVarStats
{
    size_t n;
    double mean;
    double variance;
};

/**
 * @brief Calculates 1 variable stats for ```vec```
 */
template<typename T>
SingleVarStats calc_stats(const std::vector<T>& vec)
{
    size_t n = vec.size();
    T mean = std::reduce(vec.begin(), vec.end()) / n;
    T variance = calc_variance(vec, mean, n);
    return SingleVarStats{
        n, mean, variance
    };
}

} // namespace stats
} // namespace sable

#endif