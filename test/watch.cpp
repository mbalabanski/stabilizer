
#include <chrono>
#include <iostream>
#include <thread>

#include <iostream>

#include <sable.hpp>

const size_t runtime1 = 10, runtime2 = 90;
const size_t trials = 100;

void run_func()
{
    const size_t duration = 40; // change between compilations
    std::this_thread::sleep_for(std::chrono::microseconds(duration));
}

int main()
{

    auto test_results = sable::watch_function(std::string("WaitFunction"), run_func, trials, 0.05);

    if (test_results)
        sable::output_test_result(test_results.value());

    return 0;
}