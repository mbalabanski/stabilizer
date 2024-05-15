#include <runtime.hpp>

namespace sable
{

HypothesisTest compare_runtime(
    void (*func1)(), void (*func2)(), 
    const float alpha
)
{
    core::Runner run1(func1), run2(func2);

    run1.run(64);
    run2.run(64);

    auto rt1 = run1.runtime(), rt2 = run2.runtime();

    // run t test with two runtimes

    stats::TDistribution tdist_diff(
        rt1.mu, rt1.sigma, rt1.n,
        rt2.mu, rt2.sigma, rt2.n
    );

    double stat = tdist_diff.statistic(0.0);

    std::cout << "T-Test statistic: " << stat << "\n";

    double prob = tdist_diff.lt_cdf(stat);
    double gt_prob = tdist_diff.gt_cdf(stat);

    std::cout << "Probability: " << prob << "\n";

    unsigned int result = HypothesisTest::Null;

    if (1 - prob > alpha / 2) result |= HypothesisTest::AlternateNEq;
    if (prob > alpha)     result |= HypothesisTest::AlternateLt;
    if (1 - prob > alpha) result |= HypothesisTest::AlternateGt;

    return static_cast<HypothesisTest>(result);
}

}