
#include <chrono>
#include <iostream>
#include <thread>

#include <iostream>

#include <sable.hpp>


void run_func()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main()
{
    const size_t n = 64;

    sable::core::Runner<void()> runner(run_func);
    runner.run(n);

    std::cout << "Average runtime for " << n << " calls: " << runner.runtime() << "." << std::endl;

    return 0;
}