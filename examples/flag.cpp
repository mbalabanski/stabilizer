
#include <chrono>
#include <iostream>
#include <thread>

#include <iostream>

#include <sable.hpp>

void run_func()
{
    std::this_thread::sleep_for(std::chrono::microseconds(500));
}

int main()
{
    sable::Flag flag;

    sable::start_flag(flag);

    run_func();

    sable::end_flag(flag);

    std::cout << "Elapsed time: " << flag.elapsed_time().count() << "\n";


    return 0;
}