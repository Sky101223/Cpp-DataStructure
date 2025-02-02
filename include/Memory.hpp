#ifndef __MEMORY_HPP_
#define __MEMORY_HPP_

#include <limits>
#include <stdexcept>

#include "Owe.h"

OWE_NAMESPACE_BEGIN

/// @brief 分配器
/// @tparam _Type 
/// @link https://zh.cppreference.com/w/cpp/memory/allocator @endlink
template <typename _Type>
class Allocator
{
public:
    using value_type = _Type;
    using pointer = _Type*;
    using const_pointer = const _Type*;
    using reference = _Type&;
    using const_reference = const _Type&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::true_type;

    template <typename U>
    class rebind
    {
    public:
        using other = Allocator<U>;
    };
public:
    Allocator(void) noexcept = default;

    Allocator(const Allocator& _another) noexcept = default;

    template <typename U>
    Allocator(const Allocator<U>& _another) noexcept
    {
    };

    ~Allocator() = default;
public:
    /// @brief 分配_n个元素的内存
    /// @param _n 元素个数
    /// @param _hint 会在_hint附近分配内存，忽略
    /// @exception std::bad_array_new_length 超出最大尺寸
    /// @exception std::bad_alloc 内存分配失败
    /// @return 
    pointer allocate(size_type _n, const void* _hint = nullptr)
    {
        const_cast<void>(_hint);
        if (_n > max_size())
            throw std::bad_array_new_length();

        if (_n == 0)
            return nullptr;

        return static_cast<pointer>(::operator new(_n * sizeof(value_type)));
    }

    /// @brief 释放由allocate分配的内存
    /// @param _ptr 要释放的内存指针
    /// @param _n 元素个数，忽略
    void deallocate(pointer _ptr, size_type _n = 0)
    {
        static_cast<void>(_n);
        if (_ptr == nullptr)
            return;

        ::operator delete(_ptr);
    }

    /// @brief 构造对象
    /// @tparam U 
    /// @tparam ...Args 
    /// @param _ptr 要构造的内存指针
    /// @param ..._args 构造函数参数包
    template <typename U, typename... Args>
    void construct(U* _ptr, Args&&... _args)
    {
        ::new(_ptr) U(std::forward<Args>(_args)...);
    }

    /// @brief 销毁对象
    /// @tparam U 
    /// @param _ptr 要销毁的内存指针
    template <typename U>
    void destroy(U* _ptr)
    {
        _ptr->~U();
    }

    size_type max_size() const noexcept
    {
        return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
    }

    pointer address(reference _r) const noexcept
    {
        return &_r;
    }

    const_pointer address(const_reference _r) const noexcept
    {
        return &_r;
    }

    bool operator==(const Allocator& _another) const noexcept
    {
        return true;
    }

    bool operator!=(const Allocator& _another) const noexcept
    {
        return false;
    }
};

/// @brief void类型特化
/// @details 为void类型的分配器提供类型支持，但不提供实现
template <>
class Allocator<void>
{
public:
    using value_type = void;
    using pointer = void*;
    using const_pointer = const void*;
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::true_type;
};

OWE_NAMESPACE_END
#endif