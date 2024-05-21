#include <core/runner.hpp>

namespace sable
{
namespace core
{


Runner::RunDuration Runner::run_task()
{
    // generate random padding for stack and heap
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 512);

    const size_t stack_size = dist(rng), heap_size = dist(rng);

    // create stack & heap buffer
    size_t* stack_padding = (size_t*) alloca(sizeof(size_t) * stack_size);
    std::unique_ptr<size_t> heap_padding(new size_t[heap_size]);

    auto t1 = std::chrono::high_resolution_clock::now();
    func_handler();
    auto t2 = std::chrono::high_resolution_clock::now();

    auto ms = std::chrono::duration_cast<SpeedUnit>(t2 - t1);

    return static_cast<RunDuration>(ms);
}


void Runner::run(size_t n)
{
    // push n number of runners

    // for (size_t i = 0; i < n; i++)
    // {
    //     pool.push([&]() { return run_task(); });
    // }

    // single threaded

    RunDuration r;

    for (size_t i = 0; i < n; i++)
    {
        r = run_task();
        runtimes.push_back(r);
    }

    // sync back threads
}

stats::SingleVarStats Runner::runtime()
{
    std::vector<double> runtimes_as_double(runtimes.size());
    std::transform(
        runtimes.begin(), runtimes.end(), 
        runtimes_as_double.begin(), 
        [](RunDuration item) {return item.count(); }
    );

    return stats::calc_stats(runtimes_as_double);
}



} // namespace core
} // namespace sable
