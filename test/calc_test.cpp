
#include <chrono>
#include <iostream>
#include <thread>

#include <iostream>

#include <sable.hpp>


void run_func()
{
    int sum = 0;
    for (int i = 0; i < 250; i++)
    {
        sum += i * 300;
    }
}

int main()
{
    const size_t n = 64;

    sable::core::Runner runner(run_func);
    runner.run(n);

    std::cout << "Average runtime for " << n << " calls: " << runner.runtime().mu << "." << std::endl;

    return 0;
}