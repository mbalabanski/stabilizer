#include <stats/t_dist.hpp>

namespace sable
{
namespace stats
{

namespace 
{
template<typename T>
static inline T square(T x) { return x * x; }
}


// TDistribution constructors

TDistribution::TDistribution(
    double mu1, double s1, size_t n1, 
    double mu2, double s2, size_t n2
) : 
    mu(mu1 - mu2),
    sigma(sqrtf((s1 * s1 / n1) + (s2 * s2 / n2))),
    df( // using Welch-Satterthwaite approximation for unlike variances
        // sigma / (
        //     (square(s1 * s1 / n1) / (n1 - 1)) + 
        //     (square(s2 * s2 / n2) / (n2 - 1))
        // )
        n1 + n2 - 2
    ),
    dist(df)
{ }

TDistribution::TDistribution(double mu_, double sigma_, double df_) : 
    mu(mu_), sigma(sigma_), df(df_), dist(df)
{}

TDistribution::TDistribution(TDistribution&& other) = default;
TDistribution& TDistribution::operator= (TDistribution& other) = default;

// TDistribution methods

double TDistribution::statistic(double val)
{
    return (val - mu) / sigma;
}

double TDistribution::lt_cdf(double t_statistic)
{
    return boost::math::cdf(dist, t_statistic);
}

double TDistribution::gt_cdf(double t_statistic)
{
    return boost::math::cdf(boost::math::complement(dist, t_statistic));
}

} // namespace stats
} // namespace sable