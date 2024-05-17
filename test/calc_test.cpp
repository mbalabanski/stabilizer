
#include <chrono>
#include <iostream>
#include <thread>

#include <iostream>

#include <sable.hpp>


void run_func()
{
    int sum = 0;
    for (int i = 0; i < 1028; i++)
    {
        sum += i;
    }
}

void run_func_unroll_dependency()
{
    int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;

    for (int i = 0; i < 1028; i += 4)
    {
        sum1 += i;
        sum2 += i + 1;
        sum3 += i + 2;
        sum4 += i + 3;
    }

    sum1 + sum2 + sum3 + sum4;
}

int main()
{
    const size_t n = 500;

    auto test_results = sable::compare_runtime(run_func, run_func_unroll_dependency, 0.05, n);

    sable::output_test_result(test_results);

    return 0;
}