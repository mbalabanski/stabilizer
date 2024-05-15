#ifndef SABLE_STATS_T_DIST_HPP
#define SABLE_STATS_T_DIST_HPP

#include <random>

#include <boost/math/distributions/students_t.hpp>

namespace sable
{
namespace stats
{

// t test

/**
 * @brief Describes a t distribution. 
 * Assumes the following conditions are met:
 * 1. Random sample
 * 2. sampling normality
 * 3. population > 10n
 * 
 * The sampling distribution for a difference in means that abides by the conditions 
 * can be described as a t distribution with parameters μ = μ1 - μ2, σ = sqrt((s1^2 / n1) + (s2^2 / n2))
 */
class TDistribution
{
    float df;
    double mu, sigma;
    boost::math::students_t dist;

public:
    /**
     * @brief Construct a new t dist object for a difference in means
     */
    TDistribution(
        double mu1, double sigma1, size_t n1, 
        double mu2, double sigma2, size_t n2
    );
    /**
     * @brief Construct a new t dist object from parameters
     */
    TDistribution(double mu_, double sigma_, double df_);

    TDistribution(TDistribution&& other);
    TDistribution& operator=(TDistribution& other);

    double statistic(double val);

    double lt_cdf(double t_statistic);
    double gt_cdf(double t_statistic);
};


} // namespace stats
} // namespace sable


#endif