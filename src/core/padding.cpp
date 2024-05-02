#include <core/padding.hpp>

namespace sable
{
namespace core
{

template<const size_t size>
StackPadding<size>::StackPadding() : padding((unsigned char) alloca(size)) { }

template<const size_t size>
StackPadding<size>::StackPadding(const StackPadding& other) = delete;

template<const size_t size>
StackPadding<size>& StackPadding<size>::operator= (const StackPadding& other) = delete;


template<const size_t size>
HeapPadding<size>::HeapPadding() : padding(new unsigned char[size]) { }

template<const size_t size>
HeapPadding<size>::HeapPadding(const HeapPadding& other) = delete;

template<const size_t size>
HeapPadding<size>& HeapPadding<size>::operator= (const HeapPadding& other) = delete;

} // namespace core
} // namespace sable
