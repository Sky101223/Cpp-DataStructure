#ifndef __REVERSR_ITERATOR_HPP_
#define __REVERSR_ITERATOR_HPP_

template <typename _Iterator>
class ReverseIterator
{
public:
    using iterator_type = _Iterator;
    using iterator_category = typename _Iterator::iterator_category;
    using value_type = typename _Iterator::value_type;
    using difference_type = typename _Iterator::difference_type;
    using pointer = typename _Iterator::pointer;
    using reference = typename _Iterator::reference;

    using self = ReverseIterator<_Iterator>;
public:
    ReverseIterator(void)
        : m_current()
    {
    }

    explicit ReverseIterator(iterator_type _x)
        : m_current(_x)
    {
    }

    template <typename U>
    ReverseIterator(const ReverseIterator<U>& _u)
        : m_current(_u.m_current)
    {
    }
public:
    template <typename U>
    self& operator=(const ReverseIterator<U>& _u)
    {
        this->m_current = _u.m_current;
        return *this;
    }

    iterator_type base(void) const
    {
        return m_current;
    }

    reference operator*(void) const
    {
        iterator_type tmp = m_current;
        return *--tmp;
    }

    pointer operator->(void) const
    {
        return &(operator*());
    }

    reference operator[](difference_type _n) const
    {
        return m_current[-_n - 1];
    }

    self& operator++(void)
    {
        --m_current;
        return *this;
    }

    self operator++(int)
    {
        self tmp = *this;
        --m_current;
        return tmp;
    }

    self& operator--(void)
    {
        ++m_current;
        return *this;
    }

    self operator--(int)
    {
        self tmp = *this;
        ++m_current;
        return tmp;
    }

    self operator+(difference_type _n) const
    {
        return self(m_current - _n);
    }

    self& operator+=(difference_type _n)
    {
        m_current -= _n;
        return *this;
    }

    self operator-(difference_type _n) const
    {
        return self(m_current + _n);
    }

    self& operator-=(difference_type _n)
    {
        m_current += _n;
        return *this;
    }
private:
    iterator_type m_current;
};

#endif