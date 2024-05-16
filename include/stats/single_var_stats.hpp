#ifndef SABLE_STATS_1_VAR_STATS_HPP
#define SABLE_STATS_1_VAR_STATS_HPP

#include <numeric>
#include <vector>



namespace sable
{
namespace stats
{

namespace
{

template<typename T>
T calc_variance(const std::vector<T>& vec, const double mu, const size_t n)
{
    if (n <= 1) { return static_cast<T>(0); }

    auto func = [&](const T& val)
    {
        return ((val - mu) * (val - mu) / (n - 1));
    };

    return static_cast<T>(sqrtl(std::transform_reduce(vec.begin(), vec.end(), 0, std::plus{}, func ) / n));
}
   
template double calc_variance<double>(const std::vector<double>& vec, const double mu, const size_t );

}

struct SingleVarStats
{
    size_t n;
    double sum;
    double mu;
    double sigma;
};

/**
 * @brief Calculates 1 variable stats for ```vec```
 */
template<typename T>
SingleVarStats calc_stats(const std::vector<T>& vec)
{
    size_t n = vec.size();
    T sum = std::reduce(vec.begin(), vec.end());
    T mean = sum / n;
    T variance = calc_variance(vec, mean, n);
    return SingleVarStats{
        n, sum, mean, variance
    };
}

} // namespace stats
} // namespace sable

#endif