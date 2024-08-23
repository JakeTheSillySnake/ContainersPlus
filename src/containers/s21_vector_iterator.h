#ifndef CPP2_S21_CONTAINERS_2_SRC_VECTOR_S21_VECTOR_ITERATOR_H_
#define CPP2_S21_CONTAINERS_2_SRC_VECTOR_S21_VECTOR_ITERATOR_H_

namespace s21 {

template <typename T>
class vector<T>::VectorIterator {
 public:
  VectorIterator() = default;
  VectorIterator(iterator_ptr ptr);

  iterator_ptr base() const;
  reference operator*();
  VectorIterator operator++(int);
  VectorIterator operator--(int);
  VectorIterator& operator++();
  VectorIterator& operator--();
  bool operator==(const VectorIterator& other) const;
  bool operator!=(const VectorIterator& other) const;
  VectorIterator operator+(int n) const;
  VectorIterator operator-(int n) const;
  ptrdiff_t operator-(const VectorIterator& other) const;

 private:
  iterator_ptr ptr_;
};

template <typename T>
class vector<T>::VectorConstIterator : public VectorIterator {
 public:
  VectorConstIterator() = default;
  VectorConstIterator(const_iterator_ptr ptr);

  const_iterator_ptr base() const;
  const_reference operator*() const;
  VectorConstIterator operator++(int);
  VectorConstIterator operator--(int);
  VectorConstIterator& operator++();
  VectorConstIterator& operator--();
  bool operator==(const VectorConstIterator& other) const;
  bool operator!=(const VectorConstIterator& other) const;
  VectorConstIterator operator+(int n) const;
  VectorConstIterator operator-(int n) const;
  ptrdiff_t operator-(const VectorConstIterator& other) const;

 private:
  const_iterator_ptr ptr_;
};

template <typename T>
vector<T>::VectorIterator::VectorIterator(iterator_ptr ptr) : ptr_(ptr) {}

template <typename T>
typename vector<T>::iterator_ptr vector<T>::VectorIterator::base() const {
  return ptr_;
}

template <typename T>
typename vector<T>::reference vector<T>::VectorIterator::operator*() {
  return *ptr_;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator++(int) {
  VectorIterator tmp(*this);
  ++ptr_;
  return tmp;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator--(int) {
  VectorIterator tmp(*this);
  --ptr_;
  return tmp;
}

template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T>
bool vector<T>::VectorIterator::operator==(const VectorIterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator!=(const VectorIterator& other) const {
  return ptr_ != other.ptr_;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator+(
    int n) const {
  VectorIterator tmp(*this);
  for (int i = 0; i < n; i++) {
    tmp++;
  };

  return tmp;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator-(
    int n) const {
  VectorIterator tmp(*this);
  for (int i = 0; i < n; i++) {
    tmp--;
  };

  return tmp;
}

template <typename T>
ptrdiff_t vector<T>::VectorIterator::operator-(
    const VectorIterator& other) const {
  return ptr_ - other.ptr_;
}

template <typename T>
typename vector<T>::const_iterator_ptr vector<T>::VectorConstIterator::base()
    const {
  return ptr_;
}

template <typename T>
vector<T>::VectorConstIterator::VectorConstIterator(const_iterator_ptr ptr)
    : ptr_(ptr) {}

template <typename T>
typename vector<T>::const_reference vector<T>::VectorConstIterator::operator*()
    const {
  return *ptr_;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator++(int) {
  VectorConstIterator tmp(*this);
  ++ptr_;
  return tmp;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator--(int) {
  VectorConstIterator tmp(*this);
  --ptr_;
  return tmp;
}

template <typename T>
typename vector<T>::VectorConstIterator&
vector<T>::VectorConstIterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorConstIterator&
vector<T>::VectorConstIterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator==(
    const VectorConstIterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator!=(
    const VectorConstIterator& other) const {
  return ptr_ != other.ptr_;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator+(int n) const {
  VectorConstIterator tmp(*this);
  for (int i = 0; i < n; i++) {
    tmp++;
  };

  return tmp;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator-(int n) const {
  VectorConstIterator tmp(*this);
  for (int i = 0; i < n; i++) {
    tmp--;
  };

  return tmp;
}

template <typename T>
ptrdiff_t vector<T>::VectorConstIterator::operator-(
    const VectorConstIterator& other) const {
  return ptr_ - other.ptr_;
}
};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_SRC_VECTOR_S21_VECTOR_ITERATOR_H_