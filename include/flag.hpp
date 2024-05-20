#ifndef SABLE_FLAG_HPP
#define SABLE_FLAG_HPP

#include <chrono>
#include <map>
#include <string>

#include <core/flag.hpp>

namespace sable
{

typedef core::Flag Flag;

inline void start_flag(Flag& flag)
{
    flag.started = true;
    flag.t1 = std::chrono::high_resolution_clock::now();
}

inline void end_flag(Flag& flag)
{
    flag.t2 = std::chrono::high_resolution_clock::now();
    flag.ended = true;
}
   
} // namespace sable



#endif