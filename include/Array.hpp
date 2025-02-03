#ifndef __ARRAY_H_
#define __ARRAY_H_

#include <stdint.h>
#include <stdexcept>
#include <initializer_list>
#include <tuple>

#include "Owe.h"
#include "ReverseIterator.hpp"

OWE_NAMESPACE_BEGIN

/// @brief array常量迭代器类
/// @tparam _Type 
template <typename _Type>
class _Array_Const_Iterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = _Type;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = const value_type*;
    using reference = const value_type&;
    using self = _Array_Const_Iterator<value_type>;

    using _Ptr = value_type*;
public:
    _Array_Const_Iterator(void)
        : m_ptr(nullptr)
    {
    }

    explicit _Array_Const_Iterator(pointer m_ptr)
        : m_ptr(const_cast<_Ptr>(m_ptr))
    {
    }
public:
    reference operator*(void) const
    {
        return *m_ptr;
    }

    pointer operator->(void) const
    {
        return &(operator*());
    }

    self& operator++(void)
    {
        ++m_ptr;
        return *this;
    }

    self operator++(int32_t)
    {
        self temp = *this;
        ++*this;
        return temp;
    }

    self& operator--(void)
    {
        --m_ptr;
        return *this;
    }

    self operator--(int32_t)
    {
        self temp = *this;
        --*this;
        return temp;
    }

    bool operator==(const self& _another) const
    {
        return m_ptr == _another.m_ptr;
    }

    bool operator!=(const self& _another) const
    {
        return !(*this == _another);
    }

    bool operator<(const self& _another) const
    {
        return m_ptr < _another.m_ptr;
    }

    bool operator>(const self& _another) const
    {
        return _another < *this;
    }

    bool operator<=(const self& _another) const
    {
        return !(_another < *this);
    }

    bool operator>=(const self& _another) const
    {
        return !(*this < _another);
    }

    self& operator+=(const difference_type _number)
    {
        m_ptr += _number;
        return *this;
    }

    self& operator-=(const difference_type _number)
    {
        return *this += -_number;
    }

    self operator+(const difference_type _number) const
    {
        self temp = *this;
        return temp += _number;
    }

    self operator-(const difference_type _number) const
    {
        self temp = *this;
        return temp -= _number;
    }

    difference_type operator-(const self& _another) const
    {
        return m_ptr - _another.m_ptr;
    }

    reference operator[](const difference_type _number) const
    {
        return *(*this + _number);
    }
private:
    _Ptr m_ptr;
};

/// @brief array非常量的迭代器
/// @tparam _Type 
template <typename _Type>
class _Array_Inerator : public _Array_Const_Iterator<_Type>
{
public:
    using base = _Array_Const_Iterator<_Type>;      // 基类
    using iterator_category = std::random_access_iterator_tag;
    using value_type = _Type;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;
    using self = _Array_Inerator<value_type>;
public:
    _Array_Inerator(void)
        : base()
    {
    }

    explicit _Array_Inerator(pointer m_ptr)
        : base(m_ptr)
    {
    }
public:
    reference operator*(void) const
    {
        return const_cast<reference>(base::operator*());
    }

    pointer operator->(void) const
    {
        return const_cast<pointer>(base::operator->());
    }

    self& operator++(void)
    {
        ++*(base*)this;
        return *this;
    }

    self operator++(int32_t)
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    self& operator--(void)
    {
        --*(base*)this;
        return *this;
    }

    self operator--(int32_t)
    {
        self tmp = *this;
        --*this;
        return tmp;
    }

    self& operator+=(difference_type _number)
    {
        *(base*)this += _number;
        return *this;
    }

    self& operator-=(difference_type _number)
    {
        *(base*)this -= _number;
        return *this;
    }

    self operator+(difference_type _number) const
    {
        self temp = *this;
        return temp += _number;
    }

    self operator-(difference_type _number) const
    {
        self temp = *this;
        return temp -= _number;
    }

    difference_type operator-(const base& _another) const
    {
        return *(base*)this - _another;
    }

    reference operator[](difference_type _number) const
    {
        return *(*this + _number);
    }
};

/// @brief array
/// @link https://zh.cppreference.com/w/cpp/container/array
/// @tparam _Type 
/// @tparam _Size 
template <typename _Type, std::size_t _Size>
class Array
{
public:
    using value_type = _Type;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = _Array_Inerator<value_type>;
    using const_iterator = _Array_Const_Iterator<value_type>;
    using reverse_iterator = Owe::ReverseIterator<iterator>;
    using const_reverse_iterator = Owe::ReverseIterator<const_iterator>;
public:
    Array(std::initializer_list<_Type> _list)
    {
        std::copy(_list.begin(), _list.end(), m_data);
    }
public:
    // 元素访问

    /// @brief 带越界检查访问指定的元素
    /// @param _index 
    /// @return 
    reference at(size_type _index)
    {
        if (_index >= _Size)
            _throw_out_of_range();
        return m_data[_index];
    }

    /// @brief 带越界检查访问指定的元素
    /// @param _index 
    /// @return 
    const_iterator at(size_type _index) const
    {
        if (_index >= _Size)
            throw std::out_of_range("Array index out of range");
        return m_data[_index];
    }

    /// @brief 访问指定的元素
    /// @param _index 
    /// @return 
    reference operator[](size_type _index)
    {
        return m_data[_index];
    }

    /// @brief 访问指定的元素
    /// @param _index 
    /// @return 
    const_reference operator[](size_type _index) const
    {
        return m_data[_index];
    }

    /// @brief 访问第一个元素
    /// @param  
    /// @return
    reference front(void)
    {
        return m_data[0];
    }

    /// @brief 访问第一个元素
    /// @param  
    /// @return 
    const_reference front(void) const
    {
        return m_data[0];
    }

    /// @brief 访问最后一个元素
    /// @param  
    /// @return 
    reference back(void)
    {
        return m_data[_Size - 1];
    }

    /// @brief 访问最后一个元素
    /// @param  
    /// @return 
    const_reference back(void) const
    {
        return m_data[_Size - 1];
    }

    /// @brief 直接访问底层连续存储
    /// @param  
    /// @return 
    pointer data(void)
    {
        return m_data;
    }

    /// @brief 直接访问底层连续存储
    /// @param  
    /// @return 
    const_pointer data(void) const
    {
        return m_data;
    }

    // 迭代器

    /// @brief 返回指向起始的迭代器
    /// @param  
    /// @return 
    iterator begin(void) noexcept
    {
        return static_cast<iterator>(m_data);
    }

    /// @brief 返回指向起始的迭代器
    /// @param  
    /// @return 
    const_iterator begin(void) const noexcept
    {
        return const_cast<const_iterator>(m_data);
    }

    /// @brief 返回指向起始的迭代器
    /// @param  
    /// @return 
    const_iterator cbegin(void) const noexcept
    {
        return begin();
    }

    /// @brief 返回指向末尾的迭代器
    /// @param  
    /// @return 
    iterator end(void) noexcept
    {
        return static_cast<iterator>(m_data + _Size);
    }

    /// @brief 返回指向末尾的迭代器
    /// @param  
    /// @return 
    const_iterator end(void) const noexcept
    {
        return const_cast<const_iterator>(m_data + _Size);
    }

    /// @brief 返回指向末尾的迭代器
    /// @param  
    /// @return 
    const_iterator cend(void) const noexcept
    {
        return end();
    }

    /// @brief 返回指向起始的逆向迭代器
    /// @param  
    /// @return 
    reverse_iterator rbegin(void) noexcept
    {
        return static_cast<reverse_iterator>(end());
    }

    /// @brief 返回指向起始的逆向迭代器
    /// @param  
    /// @return 
    const_reverse_iterator rbegin(void) const noexcept
    {
        return const_cast<const_reverse_iterator>(end());
    }

    /// @brief 返回指向起始的逆向迭代器
    /// @param  
    /// @return 
    const_reverse_iterator crbegin(void) const noexcept
    {
        return rbegin();
    }

    reverse_iterator rend(void) noexcept
    {
        return static_cast<reverse_iterator>(begin());
    }

    const_reverse_iterator rend(void) const noexcept
    {
        return static_cast<const_reverse_iterator>(begin());
    }

    const_reverse_iterator crend(void) const noexcept
    {
        return rend();
    }

    // 容器

    /// @brief 检查容器是否为空
    /// @param  
    /// @return 
    constexpr bool empty(void) const noexcept
    {
        return false;
    }

    /// @brief 返回元素数
    /// @param  
    /// @return 
    constexpr size_type size(void) const noexcept
    {
        return _Size;
    }

    /// @brief 返回最大容量
    /// @param  
    /// @return 
    constexpr size_type max_size(void) const noexcept
    {
        return size();
    }

    // 操作

    /// @brief 以指定值填充容器
    /// @param _value 
    void fill(const value_type& _value)
    {
        std::fill_n(m_data, _Size, _value);
    }

    /// @brief 交换两个Array里的数据
    /// @param _another 
    void swap(Array<_Type, _Size>& _another)
    {
        std::swap(m_data, _another.m_data);
    }
public:
    /// @brief 越界：抛出out_of_range异常
    /// @param 
    [[noreturn]] void _throw_out_of_range(void) const
    {
        throw std::out_of_range("Array index out of range");
    }
private:
    value_type m_data[_Size];
};

// 非成员函数

template <typename _Type, std::size_t _Size>
bool operator==(const Array<_Type, _Size>& _first, const Array<_Type, _Size>& _second)
{
    return std::equal(_first.begin(), _first.end(), _second.begin(), _second.end());
}

template <typename _Type, std::size_t _Size>
bool operator!=(const Array<_Type, _Size>& _first, const Array<_Type, _Size>& _second)
{
    return !(_first == _second);
}

template <typename _Type, std::size_t _Size>
bool operator<(const Array<_Type, _Size>& _first, const Array<_Type, _Size>& _second)
{
    return std::lexicographical_compare(_first.begin(), _first.end(), _second.begin(), _second.end());
}

template <typename _Type, std::size_t _Size>
bool operator>(const Array<_Type, _Size>& _first, const Array<_Type, _Size>& _second)
{
    return _second < _first;
}

template <typename _Type, std::size_t _Size>
bool operator<=(const Array<_Type, _Size>& _first, const Array<_Type, _Size>& _second)
{
    return !(_first > _second);
}

template <typename _Type, std::size_t _Size>
bool operator>=(const Array<_Type, _Size>& _first, const Array<_Type, _Size>& _second)
{
    return !(_first < _second);
}

/// @brief 交换两个Array里的数据
/// @tparam _Type 
/// @tparam _Size 
/// @param _first 
/// @param _second 
template <typename _Type, std::size_t _Size>
void swap(Array<_Type, _Size>& _first, Array<_Type, _Size>& _second)
{
    _first.swap(_second);
}

/// @brief 获取Array中第_Index个元素
/// @tparam _Type 
/// @tparam _Index 
/// @tparam _Size 
/// @param _array 
/// @return 
template <std::size_t _Index, typename _Type, std::size_t _Size>
_Type&& get(Array<_Type, _Size>&& _array)
{
    return std::move(_array[_Index]);
}

/// @brief 获取Array中第_Index个元素
/// @tparam _Type 
/// @tparam _Index 
/// @tparam _Size 
/// @param _array 
/// @return 
template <std::size_t _Index, typename _Type, std::size_t _Size>
const _Type& get(const Array<_Type, _Size>& _array)
{
    return _array[_Index];
}

/// @brief 获取Array中第_Index个元素
/// @tparam _Type 
/// @tparam _Index 
/// @tparam _Size 
/// @param _array 
/// @return 
template <std::size_t _Index, typename _Type, std::size_t _Size>
const _Type&& get(const Array<_Type, _Size>&& _array)
{
    return std::move(_array[_Index]);
}
OWE_NAMESPACE_END

// 辅助
template <std::size_t _Index, typename _Type, std::size_t _Size>
class std::tuple_element<_Index, Owe::Array<_Type, _Size>>
{
public:
    using type = _Type;
};

template <typename _Type, std::size_t _Size>
class std::tuple_size<Owe::Array<_Type, _Size>> : public std::integral_constant<std::size_t, _Size>
{
};

OWE_NAMESPACE_BEGIN
/// @brief 对空Array的特化
/// @tparam _Type 
template <typename _Type>
class Array<_Type, 0>
{
public:
    using value_type = _Type;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = _Array_Inerator<value_type>;
    using const_iterator = _Array_Const_Iterator<value_type>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
public:
    // 元素访问

    [[noreturn]] reference at(size_type)
    {
        _throw_out_of_range();
    }

    [[noreturn]] const_reference at(size_type) const
    {
        _throw_out_of_range();
    }

    reference operator[](size_type) noexcept
    {
        return m_data[0];
    }

    const_reference operator[](size_type) const noexcept
    {
        return m_data[0];
    }

    reference front()
    {
        return m_data[0];
    }

    const_reference front() const
    {
        return m_data[0];
    }

    reference back()
    {
        return m_data[0];
    }

    const_reference back() const
    {
        return m_data[0];
    }

    pointer data()
    {
        return nullptr;
    }

    const_pointer data() const
    {
        return nullptr;
    }

    // 迭代器

    iterator begin() noexcept
    {
        return iterator();
    }

    const_iterator begin() const noexcept
    {
        return const_iterator();
    }

    const_iterator cbegin() const noexcept
    {
        return begin();
    }

    iterator end() noexcept
    {
        return iterator();
    }

    const_iterator end() const noexcept
    {
        return const_iterator();
    }

    const_iterator cend() const noexcept
    {
        return end();
    }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return rbegin();
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crend() const noexcept
    {
        return rend();
    }

    // 容量

    constexpr bool empty() const noexcept
    {
        return true;
    }

    constexpr size_type size() const noexcept
    {
        return 0;
    }

    constexpr size_type max_size() const noexcept
    {
        return 0;
    }

    // 操作

    void fill(const value_type&)
    { // do nothing        
    }

    void swap(const Array&)
    { // do nothing
    }
public:
    /// @brief 越界：抛出out_of_range异常
    /// @param 
    [[noreturn]] void _throw_out_of_range(void) const
    {
        throw std::out_of_range("Array index out of range");
    }
private:
    value_type m_data[1];
};

OWE_NAMESPACE_END
#endif