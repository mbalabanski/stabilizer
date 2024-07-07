#include <core/runner.hpp>

#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>

namespace sable
{
namespace core
{


Runner::RunDuration Runner::run_task()
{
    // generate random padding for stack and heap
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 2048);

    const size_t stack_size = dist(rng), heap_size = dist(rng);

    // create stack & heap buffer
    size_t* stack_padding = (size_t*) alloca(sizeof(size_t) * stack_size); // - clears out when loses scope
    std::unique_ptr<size_t> heap_padding(new size_t[heap_size]);

    auto t1 = std::chrono::high_resolution_clock::now();
    func_handler();
    auto t2 = std::chrono::high_resolution_clock::now();

    auto ms = std::chrono::duration_cast<SpeedUnit>(t2 - t1);

    return static_cast<RunDuration>(ms);
}

void Runner::run_single_thread(size_t n)
{
    runtimes.resize(n);

    for (size_t i = 0; i < n; i++)
    {
        runtimes[i] = run_task();
    }
}

void Runner::run_multi_thread(size_t n, size_t threads)
{
    runtimes.resize(n);

    // create multithreaded scope
    boost::asio::thread_pool pool(threads);

    for (int i = 0; i < n; i++)
    {
        boost::asio::post(pool, 
        [&]{
            runtimes[i] = run_task();
        });
    }
    
    pool.join();
}

void Runner::run(size_t n, bool multithreaded)
{
    // single threaded

    if (!multithreaded)
    {
        run_single_thread(n);
    }
    else
    {
        run_multi_thread(n);
    }
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
