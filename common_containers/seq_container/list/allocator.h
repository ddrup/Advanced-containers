#ifndef CPP2_S21_CONTAINERS_SRC_COMMON_CONTAINERS_SEQ_CONTAINER_ALLOCATOR_ALLOCATOR_H_
#define CPP2_S21_CONTAINERS_SRC_COMMON_CONTAINERS_SEQ_CONTAINER_ALLOCATOR_ALLOCATOR_H_

#include <memory>

namespace s21 {

template <size_t N> 
class StackStorage {
private:
  char buf_[N];
  size_t reserved_ = 0;

public:
  StackStorage() = default;
  StackStorage(const StackStorage &) = delete;
  StackStorage(StackStorage &&) = delete;
  void reserve(size_t n) {
    reserved_ += n;
  }
  size_t get_reserved() const {
    return reserved_;
  }
  char* get_buf() {
    return buf_;
  }
};

template <typename T, size_t N> 
class StackAllocator {
public:
  using value_type = T;
  using pointer = T*;
  using size_type = std::size_t;
  
  template <size_t U>
  explicit StackAllocator(StackStorage<U>& storage)
    : storage_(&storage) {}

  template <typename U>
  StackAllocator(const StackAllocator<U,N>& other) noexcept
    : storage_(other.storage_) {}

  template <typename U>
  StackAllocator& operator=(const StackAllocator<U,N>& other) noexcept {
    if(this != &other) {
      storage_ = other.storage_;
    }
    return *this;
  } 

  [[nodiscard]] pointer allocate(size_type n) {
    size_type available_space = N - storage_->get_reserved();
    void* ptr = static_cast<void*>(storage_->get_buf() + storage_->get_reserved());
    void* aligned_ptr = std::align(alignof(T), n * sizeof(T), ptr, available_space);
    
    if(aligned_ptr == nullptr) {
        throw std::bad_alloc();
    }

    storage_->reserve(n);

    return static_cast<T*>(aligned_ptr);
  }

  void deallocate(pointer ptr, size_type n){
    std::ignore = ptr;
    std::ignore = n;
  }

  template <typename U>
	StackAllocator(StackAllocator<U, N>) {}
	
	template <typename U>
	struct rebind {
		using other = StackAllocator<U, N>; 
	};

private:
  StackStorage<N>* storage_;
};

} // namespace s21

#endif // CPP2_S21_CONTAINERS_SRC_COMMON_CONTAINERS_SEQ_CONTAINER_ALLOCATOR_ALLOCATOR_H_