
#include <chrono>
#include <iostream>
#include <thread>

#include <iostream>

#include <sable.hpp>

const size_t runtime1 = 10, runtime2 = 90;
const size_t trials = 2560;

void run_func()
{
    std::this_thread::sleep_for(std::chrono::microseconds(10));
}

void run_func2()
{
    std::this_thread::sleep_for(std::chrono::microseconds(14));
}

int main()
{

    auto test_results = sable::watch_function(std::string("WaitFunction"), run_func, trials, 0.05);

    if (test_results)
        sable::output_test_result(test_results.value());

    return 0;
}