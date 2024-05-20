#include <flag.hpp>

namespace sable
{

inline void start_flag(core::Flag& flag)
{
    flag.started = true;
    flag.t1 = std::chrono::high_resolution_clock::now();
    
}

inline void end_flag(core::Flag& flag)
{
    flag.t2 = std::chrono::high_resolution_clock::now();
    flag.ended = true;
}


} // namespace sable
