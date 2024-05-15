
#include <chrono>
#include <iostream>
#include <thread>

#include <iostream>

#include <sable.hpp>


void run_func()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void run_func2()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

int main()
{
    const size_t n = 64;

    auto test_results = static_cast<int>(
        sable::compare_runtime(run_func, run_func2, 0.05)
    );

    std::cout << "Test results: " << test_results << "\n";

    if (test_results == 0)
    {
        std::cout << "failed to reject null hypothesis\n";
    }

    if (test_results & sable::AlternateNEq == sable::AlternateNEq)
    {
        std::cout << "Alternate hypothesis not equal - pass\n";
    }

    if (test_results & sable::AlternateGt == sable::AlternateGt)
    {
        std::cout << "Alternate hypothesis greater than - pass\n";
    }

    if (test_results & sable::AlternateLt == sable::AlternateLt)
    {
        std::cout << "Alternate hypothesis less than - pass\n";
    }

    return 0;
}