#include <watch_function.hpp>

namespace sable
{


std::optional<TestResult> watch_function(
    const std::string& name, 
    void (*func)(),
    size_t trials,
    float alpha
)
{

    // get last function result

    auto prev_run = core::get_last_runtime(name);

    core::Runner runner(func);
    runner.run(trials);

    const stats::SingleVarStats curr_run = runner.runtime();

    core::write_runtime_to_output(name, curr_run);

    if (!prev_run.has_value())
    {
        return {};
    }

    const stats::SingleVarStats& prev = prev_run.value();

    return compare_runtime(prev, curr_run, alpha);
}

} // namespace sable
