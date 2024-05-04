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
 */
class StackPadding
{
    // do not deallocate
    unsigned char* stack_ptr;
    const size_t size;

public:

    StackPadding(const size_t size);
    StackPadding(const StackPadding& other) = delete;

    StackPadding& operator= (const StackPadding& other) = delete;

};

/**
 * @brief Defines a padding on the heap of arbitrary size ```size```
 * 
 * 
 */
class HeapPadding
{
    std::unique_ptr<unsigned char> padding;
    const size_t size;

public:

    HeapPadding(const size_t size);
    HeapPadding(const HeapPadding& other) = delete;

    HeapPadding& operator= (const HeapPadding& other) = delete;

};

} // namespace core
} // namespace sable


#endif