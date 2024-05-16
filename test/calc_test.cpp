
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
}

int main()
{
    const size_t n = 1028;

    auto test_results = static_cast<int>(
        sable::compare_runtime(run_func, run_func_unroll_dependency, 0.05, n)
    );

    std::cout << "Test results: \n";

    if (test_results == 0)
    {
        std::cout << "failed to reject null hypothesis\n";
    }

    if (test_results & 0b001 == 0b001)
    {
        std::cout << "Alternate hypothesis not equal - pass\n";
    }

    if (test_results & 0b010 == 0b010)
    {
        std::cout << "Alternate hypothesis greater than - pass\n";
    }

    if (test_results & 0b100 == 0b100)
    {
        std::cout << "Alternate hypothesis less than - pass\n";
    }

    return 0;
}