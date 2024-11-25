#ifndef CPP2_S21_CONTAINERS_SRC_COMMON_CONTAINERS_SEQ_CONTAINER_VECTOR_VECTOR_H_
#define CPP2_S21_CONTAINERS_SRC_COMMON_CONTAINERS_SEQ_CONTAINER_VECTOR_VECTOR_H_

#include <utility>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cstddef>
#include <compare>
#include <iostream>

namespace s21 {

template <typename T>
struct RawMemory {
    T* buf_ = nullptr;
    size_t cap_ = 0;
    
    RawMemory() = default;

    explicit RawMemory(size_t n);
    ~RawMemory();

    RawMemory(const RawMemory&) = delete;
    RawMemory(RawMemory&& other) noexcept;

    RawMemory& operator=(const RawMemory& other) = delete;
    RawMemory& operator=(RawMemory&& other) noexcept;

    const T& operator[](size_t pos) const;
    T& operator[](size_t pos);
    
    const T* operator+(size_t index) const;
    T* operator+(size_t index);

    void swap(RawMemory& other) noexcept;

    static T* Allocate(size_t n);
    static void Deallocate(T* buf);
};

template <typename T>
class Vector{
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = value_type&;
    using const_reference = const value_type&;

    template <bool IsConst>
    class BaseIterator;

    using iterator               = BaseIterator<false>;
    using const_iterator         = BaseIterator<true>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Vector() = default;
    explicit Vector(size_type n);
    Vector(size_type n, const T& value);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector(std::initializer_list<T> init);

    ~Vector();

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;

    size_type size() const noexcept;
    size_type capacity() const noexcept;

    void reserve(size_type new_cap);
    void resize(size_type count);
    void resize(size_type count, const T& value);

    void pop_back();
    void push_back(const T& value);
    void push_back(T&& value);

    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    T* data() noexcept;
    const T* data() const noexcept;
    bool empty() noexcept;
    void shrink_to_fit();
    void clear() noexcept;

    template <typename... Args>
    reference emplace_back(Args&&... args);
    template <class... Args>
    iterator emplace(const_iterator pos, Args&&... args);

    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, T&& value);
    iterator insert(const_iterator pos,
                 size_type count, const T& value);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const noexcept;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const noexcept;
    
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const noexcept;
    
    void swap(Vector& other) noexcept;

    friend std::strong_ordering operator<=>(const Vector<T>& lhs, const Vector<T>& rhs) {
        if (lhs.size() != rhs.size()) {
            return lhs.size() <=> rhs.size();
        }

        for (size_t i = 0; i < lhs.size(); ++i) {
            if (auto cmp = lhs[i] <=> rhs[i]; cmp != 0) {
                return cmp;
            }
        }

        return std::strong_ordering::equal;
    }

    friend bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
        return (lhs <=> rhs) == 0;
    }

private:
    RawMemory<T> arr_;
    size_type sz_ = 0;

    static void Construct(T* buf);
    static void Construct(T* buf, const T& elem);
    static void Construct(T* buf, T&& elem);
    static void Destroy(T* buf); 
};

template<>
class Vector<bool> {
    // Implemetation here ...
};


template <typename T>
template <bool IsConst>
class Vector<T>::BaseIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using pointer_type      = std::conditional_t<IsConst, const T*, T*>;
	using reference_type    = std::conditional_t<IsConst,const T&,T&>;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    
    BaseIterator(pointer_type ptr);

    BaseIterator(const BaseIterator&) = default;
    BaseIterator& operator=(const BaseIterator&) = default;

    BaseIterator(BaseIterator&&) noexcept = default;
    BaseIterator& operator=(BaseIterator&&) noexcept = default;

    reference_type operator*() const;
    pointer_type operator->() const;

    BaseIterator& operator++();
    BaseIterator operator++(int);

    BaseIterator& operator--();
    BaseIterator operator--(int);

    BaseIterator& operator+=(difference_type n);
    BaseIterator operator+(difference_type n);

    friend BaseIterator operator+(difference_type n, const BaseIterator& it){
        return BaseIterator(it.ptr_ + n);
    }

    BaseIterator& operator-=(difference_type n);
    BaseIterator operator-(difference_type n);
    difference_type operator-(const BaseIterator& other);

    reference_type operator[](size_type n);

    operator BaseIterator<true>() const;

    friend bool operator<(const BaseIterator& lhs, const BaseIterator& rhs) {
        return lhs.ptr_ < rhs.ptr_;
    }
    friend bool operator>(const BaseIterator& lhs, const BaseIterator& rhs) {
        return lhs.ptr_ > rhs.ptr_;
    }
    friend bool operator==(const BaseIterator& lhs, const BaseIterator& rhs) {
        return lhs.ptr_ == rhs.ptr_;
    }
    friend bool operator!=(const BaseIterator& lhs, const BaseIterator& rhs) {
        return lhs.ptr_ != rhs.ptr_;
    }
    friend bool operator<=(const BaseIterator& lhs, const BaseIterator& rhs) {
        return lhs.ptr_ <= rhs.ptr_;
    }
    friend bool operator>=(const BaseIterator& lhs, const BaseIterator& rhs) {
        return lhs.ptr_ >= rhs.ptr_;
    }

private:
    pointer_type ptr_;
};

} // namespace s21

#include "vector.tpp"
#include "raw_memory.tpp"
#include "base_iterator.tpp"

#endif // CPP2_S21_CONTAINERS_SRC_COMMON_CONTAINERS_SEQ_CONTAINER_VECTOR_VECTOR_H_