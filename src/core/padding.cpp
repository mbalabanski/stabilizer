#include <core/padding.hpp>

namespace sable
{
namespace core
{

StackPadding::StackPadding(const size_t size_) : size(size_) 
{
    stack_ptr = (unsigned char*) alloca(size * sizeof(unsigned char));
}

HeapPadding::HeapPadding(const size_t size_) : size(size_), padding(new unsigned char[size]) { }

} // namespace core
} // namespace sable
