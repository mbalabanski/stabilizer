#include <chrono>
#include <iostream>
#include <thread>

#include <iostream>

#include <sable.hpp>

// comparing to function

const size_t duration = 40;
const size_t half_duration = duration / 2;

void run_func()
{
     // change between compilations
    std::this_thread::sleep_for(std::chrono::microseconds(duration));
}

void faster_func()
{
    std::this_thread::sleep_for(std::chrono::microseconds(half_duration));
}

int main()
{
    const size_t trials = 1000;
    const size_t n_runs = 100;

    std::vector<size_t> conf_matrix(4, 0);

    // test with equal function
    for (int i = 0; i < trials / 2; i++)
    {
        auto result = sable::compare_runtime(run_func, run_func, 0.05, n_runs);
        if (result.hypotheses == 0) // failed to reject null
        {
            conf_matrix[0]++;
        }
        else // rejected null
        {
            conf_matrix[1]++;
        }
    }

    for (int i = 0; i < trials / 2; i++)
    {
        auto result = sable::compare_runtime(run_func, faster_func, 0.05, n_runs);
        if (result.hypotheses == 0) // failed to reject null
        {
            conf_matrix[2]++;
        }
        else // rejected null
        {
            conf_matrix[3]++;
        }
    }

    // output confusion matrix

    std::cout << "Confusion Matrix:\n\n";
    std::cout << "  " << std::setw(4) << conf_matrix[0] << " | " << conf_matrix[1] << "\n";
    std::cout << "   ---------\n";
    std::cout << "  " << std::setw(4) << conf_matrix[2] << " | " << conf_matrix[3] << "\n\n";

    return 0;
}