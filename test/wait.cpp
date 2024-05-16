
#include <chrono>
#include <iostream>
#include <thread>

#include <iostream>

#include <sable.hpp>


const size_t runtime1 = 10, runtime2 = 90;
const size_t trials = 2000;

void run_func()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void run_func2()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(11));
}

int main()
{

    auto test_results = static_cast<int>(
        sable::compare_runtime(run_func, run_func2, 0.05, trials)
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