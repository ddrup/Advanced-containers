namespace s21{

template <typename T>
Vector<T>::Vector(size_type n) : arr_(n), sz_(n)
{
    std::uninitialized_value_construct_n(arr_.buf_,n);
}

template <typename T>
Vector<T>::Vector(size_type n, const T& value) : arr_(n), sz_(n)
{
    std::uninitialized_fill_n(arr_.buf_, n, value);
}

// При копирование capacity не копируется
template <typename T>
Vector<T>::Vector(const Vector& other) : arr_(other.sz_), sz_(other.sz_)
{
    std::uninitialized_copy_n(other.arr_.buf_, other.sz_, arr_.buf_);
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
{
    swap(other);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init) : arr_(init.size()), sz_(init.size())
{
    std::uninitialized_copy(
        init.begin(), init.end(), arr_.buf_
    );
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other){
    if(other.sz_ < arr_.cap_) {
        for(size_t i = 0;i < sz_ && i < other.sz_; ++i){
            arr_[i] = other[i];
        }

        if(other.sz_ > sz_) {
            std::uninitialized_copy_n(
                other.arr_ + sz_, other.sz_ - sz_, arr_ + sz_
            );
        }else if (other.sz_ < sz_) {
            std::destroy_n(
                arr_ + other.sz_, sz_ - other.sz_
            );
        }
        sz_ = other.sz_;
    }else {
        Vector tmp(other);
        swap(tmp);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept{
    swap(other);
    return *this;
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos){
    return arr_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type pos) const {
    return arr_[pos];
}

template <typename T>
Vector<T>::~Vector() {
    std::destroy_n(arr_.buf_, sz_);
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept{
    return sz_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept{
    return arr_.cap_;
}

template <typename T>
void Vector<T>::reserve(size_type new_cap){
    if(new_cap > arr_.cap_){
        RawMemory<T> tmp_arr(new_cap);

        std::uninitialized_move_n(arr_.buf_, sz_, tmp_arr.buf_);
        std::destroy_n(arr_.buf_, sz_);

        arr_.swap(tmp_arr);
    }
}

template <typename T>
void Vector<T>::resize(size_type count){
    if(count > sz_){
        reserve(count);
        
        std::uninitialized_value_construct_n(
            arr_ + sz_, count - sz_
        );
    } else if(count < sz_){
        std::destroy_n(
            arr_ + count - 1, sz_ - count
        );
    }
    sz_ = count;
}

template <typename T>
void Vector<T>::resize(size_type count, const T& value){
    if(count > sz_){
        reserve(count);
        
        std::uninitialized_fill_n(
            arr_ + sz_, count - sz_, value
        );
    } else if(count < sz_){
        std::destroy_n(
            arr_ + count - 1, sz_ - count
        );
    }
    sz_ = count;
}

template <typename T>
void Vector<T>::pop_back(){
    resize(size() - 1);
}

template <typename T>
void Vector<T>::push_back(const T& value){
    if(arr_.cap_ == sz_){
        reserve(sz_ > 0 ? sz_ * 2 : 1);
    }
    Construct(arr_ + sz_, value);
    ++sz_;
}

template <typename T>
void Vector<T>::push_back(T&& value){
    if(arr_.cap_ == sz_){
        reserve(sz_ > 0 ? sz_ * 2 : 1);
    }
    Construct(arr_ + sz_, std::move(value));
    ++sz_;
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos){
    if(pos >= sz_) {
        throw std::out_of_range("The position is not included in the range");
    }
    return arr_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const{
    if(pos >= sz_) {
        throw std::out_of_range("The position is not included in the range");
    }
    return arr_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::front(){
    return arr_[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const{
    return arr_[0];
}

template <typename T>
typename Vector<T>::reference Vector<T>::back(){
    return arr_[sz_ - 1];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
    return arr_[sz_ - 1];
}

template <typename T>
T* Vector<T>::data() noexcept {
    return arr_.buf_;
}

template <typename T>
const T* Vector<T>::data() const noexcept {
    return arr_.buf_;
}

template <typename T>
bool Vector<T>::empty() noexcept{
    return (!sz_);
}

template <typename T>
void Vector<T>::shrink_to_fit(){
    if(arr_.cap_ > sz_){
        RawMemory<T> tmp(sz_);

        std::uninitialized_copy_n(
            arr_.buf_, sz_, tmp.buf_
        );
        std::destroy_n(
            arr_.buf_, sz_
        );

        arr_.swap(tmp);
    }
}

template <typename T>
void Vector<T>::clear() noexcept {
    std::destroy_n(
        arr_.buf_, sz_
    );
    sz_ = 0;
}

template <typename T>
template <typename... Args>
typename Vector<T>::reference Vector<T>::emplace_back(Args&&... args){
    if(sz_ == arr_.cap_){
        reserve(sz_ == 0 ? 1 : sz_ * 2);
    }
    auto elem = new(arr_ + sz_) T(std::forward<Args>(args)...);
    ++sz_;
    return *elem;
}


template <typename T>
template <class... Args>
typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos, Args&&... args){
    size_type idx = pos - cbegin();

    if(idx > sz_) {
        throw std::out_of_range("Incorrect iterator for insert");
    }

    size_type new_sz = (sz_ == arr_.cap_) ? (sz_ == 0 ? 1 : sz_ * 2) : arr_.cap_;
    RawMemory<T> tmp(new_sz);

    std::uninitialized_move_n(arr_.buf_, idx, tmp.buf_);
    new(tmp + idx) T(std::forward<Args>(args)...);
    std::uninitialized_move_n(arr_.buf_ + idx, sz_ - idx, tmp.buf_ + idx + 1);
    
    tmp.swap(arr_);
    ++sz_;

    return arr_ + idx;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, const T& value){
    size_type idx = pos - cbegin();
    T copy_value(value);

    if(idx > sz_) {
        throw std::out_of_range("Incorrect iterator for insert");
    }

    size_type new_sz = (sz_ == arr_.cap_) ? (sz_ == 0 ? 1 : sz_ * 2) : arr_.cap_;
    RawMemory<T> tmp(new_sz);

    std::uninitialized_move_n(arr_.buf_, idx, tmp.buf_);
    Construct(tmp.buf_ + idx, std::move(copy_value));
    std::uninitialized_move_n(arr_.buf_ + idx, sz_ - idx, tmp.buf_ + idx + 1);
    
    tmp.swap(arr_);
    ++sz_;

    return arr_ + idx;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, T&& value) {
    size_type idx = pos - cbegin();

    if(idx > sz_) {
        throw std::out_of_range("Incorrect iterator for insert");
    }

    size_type new_sz = (sz_ == arr_.cap_) ? (sz_ == 0 ? 1 : sz_ * 2) : arr_.cap_;
    RawMemory<T> tmp(new_sz);

    std::uninitialized_move_n(arr_.buf_, idx, tmp.buf_);
    Construct(tmp.buf_ + idx, std::move(value));
    std::uninitialized_move_n(arr_.buf_ + idx, sz_ - idx, tmp.buf_ + idx + 1);
    
    tmp.swap(arr_);
    ++sz_;

    return arr_ + idx;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, size_type count, const T& value) {
    size_type idx = pos - cbegin();

    if(idx > sz_) {
        throw std::out_of_range("Incorrect iterator for insert");
    }

    size_type new_sz = (sz_ + count > arr_.cap_) ? std::max(sz_ * 2, sz_ + count) : arr_.cap_;
    RawMemory<T> tmp(new_sz);

    std::uninitialized_copy_n(
        arr_.buf_, idx, tmp.buf_
    );

    try {
        std::uninitialized_fill_n(
            tmp + idx, count, value
        );
    }catch(...) {
        std::destroy_n(
            tmp.buf_, idx
        );
    }

    std::uninitialized_move_n(
        arr_ + idx, sz_ - idx, tmp + idx + count
    );
    std::destroy_n(
        arr_.buf_, idx
    );

    tmp.swap(arr_);
    sz_ += count;
    return arr_ + idx;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator pos){
    size_type idx = pos - cbegin();

    if(idx >= sz_) {
        throw std::out_of_range("Incorrect iterator for insert");
    }

    std::move(
        arr_ + idx + 1, arr_ + sz_, arr_ + idx
    );

    Destroy(arr_ + sz_ - 1);
    --sz_;

    return arr_ + idx;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator first, const_iterator second){
    size_type idx_first = first - cbegin();
    size_type idx_second = second - cbegin();

    if (idx_first >= sz_ || idx_second > sz_) {
        throw std::out_of_range("Incorrect iterator range for erase");
    }   

    if(first == second) {
        return arr_ + idx_second;
    }

    if (second != cend()) {
        std::move(arr_ + idx_second, arr_ + sz_, arr_ + idx_first);
    }

    size_type num_elements_to_destroy = idx_second - idx_first;
    std::destroy_n(arr_ + sz_ - num_elements_to_destroy, num_elements_to_destroy);
    sz_ -= num_elements_to_destroy;

    return arr_ + idx_first;
}



template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
    return iterator(arr_.buf_);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const{
    return const_iterator(arr_.buf_);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept{
    return const_iterator(arr_.buf_);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
    return iterator(arr_ + sz_);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const{
    return const_iterator(arr_ + sz_);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept{
    return const_iterator(arr_ + sz_);
}

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() {
    return reverse_iterator(end());
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const{
    return const_reverse_iterator(end());
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const noexcept{
    return const_reverse_iterator(end());
}

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() {
    return reverse_iterator(begin());
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend() const{
    return const_reverse_iterator(begin());
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crend() const noexcept{
    return const_reverse_iterator(begin());
}

template <typename T>
void Vector<T>::swap(Vector& other) noexcept {
    arr_.swap(other.arr_);
    std::swap(sz_, other.sz_);
}

    template <typename T>
    void Vector<T>::Construct(T* buf) {
        new(buf) T();
    }

    template <typename T>
    void Vector<T>::Construct(T* buf, const T& elem) {
        new(buf) T(elem);
    }

    template <typename T>
    void Vector<T>::Construct(T* buf, T&& elem) {
        new(buf) T(std::move(elem));
    }

template <typename T>
void Vector<T>::Destroy(T* buf) {
    buf->~T();
}

} // namespace s21