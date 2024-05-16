#include <runtime.hpp>

namespace sable
{

TestResult compare_runtime(
    void (*func1)(), void (*func2)(), 
    const float alpha, const size_t n
)
{
    core::Runner run1(func1), run2(func2);

    run1.run(n);
    run2.run(n);

    auto rt1 = run1.runtime(), rt2 = run2.runtime();

    // run t test with two runtimes

    stats::TDistribution tdist_diff(
        rt1.mu, rt1.sigma, rt1.n,
        rt2.mu, rt2.sigma, rt2.n
    );

    double stat = tdist_diff.statistic(0.0);

    double prob = tdist_diff.cdf(stat);

    unsigned int result = HypothesisTest::Null;

    if (1 - prob < alpha / 2 || prob < alpha / 2) result |= HypothesisTest::AlternateNEq;
    if (prob < alpha)       result |= HypothesisTest::AlternateLt;
    if ((1 - prob) < alpha) result |= HypothesisTest::AlternateGt;

    return TestResult{
        rt1, rt2, // runtimes
        prob, // probability
        stat, // test statistic
        static_cast<HypothesisTest>(result) // hypotheses test result
    };
}

}