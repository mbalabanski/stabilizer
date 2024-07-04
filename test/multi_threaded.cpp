
#include <chrono>
#include <iostream>
#include <thread>

#include <iostream>

#include <sable.hpp>

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
    sable::Flag flag;
    
    sable::start_flag(flag);

    auto test_results = sable::compare_runtime_multithreaded(run_func, run_func2, 0.05, trials);

    sable::end_flag(flag);

    std::cout << "Elapsed time: " << flag.elapsed_time().count() << "ns.\n";
    
    sable::output_test_result(test_results);

    return 0;
}