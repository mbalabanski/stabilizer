#ifndef SABLE_CORE_FLAG_HPP
#define SABLE_CORE_FLAG_HPP

#include <chrono>
#include <map>
#include <string>
#include <vector>

#include <core/runner.hpp>

namespace sable
{
namespace core
{

/**
 * @brief Stores data for a single runtime flag
 * 
 */
struct Flag
{
    std::chrono::system_clock::time_point t1, t2;
    bool started, ended;

    inline Runner::RunDuration elapsed_time()
    {
        if (!ended) { return Runner::RunDuration(0); }
        auto ms = std::chrono::duration_cast<Runner::SpeedUnit>(t2 - t1);

        return static_cast<Runner::RunDuration>(ms);
    }
};

} // core
} // sable

#endif // SABLE_CORE_FUNC_HPP
