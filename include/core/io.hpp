#ifndef SABLE_CORE_IO_HPP
#define SABLE_CORE_IO_HPP

#include <exception>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>

#include <stats/single_var_stats.hpp>

namespace sable
{

namespace core
{

/**
 * @brief Writes a new runtime data to a saved file
 * 
 * @param name function alias - determines where the data file is
 * @param runtime_data data to save
 */
void write_runtime_to_output(
    const std::string& name,
    const stats::SingleVarStats& runtime_data
);

std::optional<const stats::SingleVarStats> get_last_runtime(
    const std::string& name
);

} // namespace core
} // namespace sable

#endif