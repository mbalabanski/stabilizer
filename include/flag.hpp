#ifndef SABLE_FLAG_HPP
#define SABLE_FLAG_HPP

#include <chrono>
#include <map>
#include <string>

#include <core/flag.hpp>

namespace sable
{

inline core::Flag start_flag();

inline void end_flag(core::Flag& flag);
   
} // namespace sable



#endif