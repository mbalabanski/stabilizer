#ifndef SABLE_PADDING_HPP
#define SABLE_PADDING_HPP

#include <memory>

namespace sable
{

namespace core
{

/**
 * @brief Defines a padding on the stack of arbitrary size ```size```
 * 
 * @tparam size the size of the padding block in bytes
 */
template<const size_t size>
class StackPadding
{
    std::unique_ptr<unsigned char> padding;
    
public:

    StackPadding();
    StackPadding(const StackPadding& other);

    StackPadding& operator= (const StackPadding<size>& other);

};

/**
 * @brief Defines a padding on the heap of arbitrary size ```size```
 * 
 * @tparam size the size of the padding block in bytes
 */
template<const size_t size>
class HeapPadding
{
    std::unique_ptr<unsigned char> padding;

public:

    HeapPadding();
    HeapPadding(const HeapPadding<size>& other);

    HeapPadding& operator= (const HeapPadding<size>& other);

};

} // namespace core
} // namespace sable


#endif