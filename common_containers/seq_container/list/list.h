#ifndef CPP2_S21_CONTAINERS_SRC_COMMON_CONTAINERS_SEQ_CONTAINER_VECTOR_VECTOR_H_
#define CPP2_S21_CONTAINERS_SRC_COMMON_CONTAINERS_SEQ_CONTAINER_VECTOR_VECTOR_H_

#include <memory>

namespace s21
{
template <typename T, typename Allocator = std::allocator<T>>
class List {
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = value_type&;
    using const_reference = const value_type&;

    


private:
    struct BaseNode{
        BaseNode* prev;
        BaseNode* next;
    };

    struct Node : BaseNode {
        value_type value;
    };

    BaseNode* fake_node_;
    size_type sz_;
};

} // namespace s21


#endif // CPP2_S21_CONTAINERS_SRC_COMMON_CONTAINERS_SEQ_CONTAINER_VECTOR_VECTOR_H_