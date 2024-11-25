namespace s21
{

template <typename T>
template <bool IsConst>
Vector<T>::BaseIterator<IsConst>::BaseIterator(pointer_type ptr) : ptr_(ptr) {}

template <typename T>
template <bool IsConst>
typename Vector<T>::template BaseIterator<IsConst>& Vector<T>::BaseIterator<IsConst>::operator++() {
    ++ptr_;
    return *this;
}

template <typename T>
template <bool IsConst>
typename Vector<T>::template BaseIterator<IsConst> Vector<T>::BaseIterator<IsConst>::operator++(int) {
    BaseIterator copy = *this;
    ++ptr_;
    return copy;
}

template <typename T>
template <bool IsConst>
typename Vector<T>::template BaseIterator<IsConst>::reference_type Vector<T>::BaseIterator<IsConst>::operator*() const {
    return *ptr_;
}

template <typename T>
template <bool IsConst>
typename Vector<T>::template BaseIterator<IsConst>::pointer_type Vector<T>::BaseIterator<IsConst>::operator->() const {
    return ptr_;
}

template <typename T>
template <bool IsConst>
typename Vector<T>::template BaseIterator<IsConst>& Vector<T>::BaseIterator<IsConst>::operator--() {
    --ptr_;
    return *this;
}

template <typename T>
template <bool IsConst>
typename Vector<T>::template BaseIterator<IsConst> Vector<T>::BaseIterator<IsConst>::operator--(int){
    Vector<T>::BaseIterator copy = *this;
    --ptr_;
    return copy;
}

template <typename T>
template <bool IsConst>
typename Vector<T>::template BaseIterator<IsConst>& Vector<T>::BaseIterator<IsConst>::operator+=(difference_type n){
    ptr_ += n;
    return *this;
}

template <typename T>
template <bool IsConst>
typename Vector<T>::template BaseIterator<IsConst> Vector<T>::BaseIterator<IsConst>::operator+(difference_type n){
    return BaseIterator(ptr_ + n);
}

template <typename T>
template <bool IsConst>
typename Vector<T>::template BaseIterator<IsConst>& Vector<T>::BaseIterator<IsConst>::operator-=(difference_type n){
    ptr_ -= n;
    return *this;
}

template <typename T>
template <bool IsConst>
typename Vector<T>::template BaseIterator<IsConst> Vector<T>::BaseIterator<IsConst>::operator-(difference_type n){
    return BaseIterator(ptr_ - n);
}

template <typename T>
template <bool IsConst>
typename Vector<T>::template BaseIterator<IsConst>::difference_type Vector<T>::BaseIterator<IsConst>::operator-(const BaseIterator& other){
    return ptr_ - other.ptr_;    
}

template <typename T>
template <bool IsConst>
typename Vector<T>::template BaseIterator<IsConst>::reference_type Vector<T>::BaseIterator<IsConst>::operator[](size_type n){
    return *(ptr_ + n);
}

// convert iterator -> const iterator 
template <typename T>
template <bool IsConst>
Vector<T>::BaseIterator<IsConst>::operator BaseIterator<true>() const {
    return {ptr_};
}

} // namespace s21
