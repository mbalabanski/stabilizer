
#include <chrono>
#include <iostream>
#include <thread>

#include <sable.hpp>


void run_func(int n)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(n));
}

int main()
{
    const size_t n = 64;

    sable::core::Runner<void(int), int> runner(run_func, 1000);
    runner.run(n);

    std::cout << "Average runtime for " << n << " calls: " << runner.runtime() << "." << std::endl;

    return 0;
}