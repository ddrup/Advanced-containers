namespace s21
{

template <typename T>    
RawMemory<T>::RawMemory(size_t n) : buf_(Allocate(n)), cap_(n) {}

template <typename T>
RawMemory<T>::RawMemory(RawMemory&& other) noexcept {
    swap(other);
}

template <typename T>
RawMemory<T>& RawMemory<T>::operator=(RawMemory&& other) noexcept {
    swap(other);
    return *this;
}

template <typename T>
RawMemory<T>::~RawMemory(){
    Deallocate(buf_);
}

template <typename T>
const T& RawMemory<T>::operator[](size_t pos) const {
    return buf_[pos];
}

template <typename T>
T& RawMemory<T>::operator[](size_t pos) {
    return buf_[pos];
}

template <typename T>
T* RawMemory<T>::operator+(size_t index){
    return (buf_ + index);
}

template <typename T>
const T* RawMemory<T>::operator+(size_t index) const {
    return (buf_ + index);
}

template <typename T>
void RawMemory<T>::swap(RawMemory& other) noexcept{
    std::swap(buf_, other.buf_);
    std::swap(cap_, other.cap_);
}

template <typename T>
T* RawMemory<T>::Allocate(size_t n) {
    return static_cast<T*>(operator new(n * sizeof(T)));
}

template <typename T>
void RawMemory<T>::Deallocate(T* buf) {
    operator delete(buf);
}

} // namespace s21