#ifndef CPP2_S21_CONTAINERS_2_SRC_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_2_SRC_VECTOR_S21_VECTOR_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  class VectorIterator;
  class VectorConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator_ptr = T *;
  using const_iterator_ptr = const T *;
  using iterator = vector<T>::VectorIterator;
  using const_iterator = vector<T>::VectorConstIterator;
  using size_type = std::size_t;

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v) noexcept;
  ~vector();
  vector &operator=(vector &&v) noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin(void) const noexcept;
  const_iterator cend(void) const noexcept;

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference front();
  reference back();
  const_reference front() const;
  const_reference back() const;
  T *data() noexcept;

  bool empty() const noexcept;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();
  void resize(size_type size);

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  iterator_ptr data_;
  size_type size_;
  size_type capacity_;
};

template <typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
vector<T>::vector(size_type n)
    : data_(new value_type[n]), size_(n), capacity_(n) {
  std::fill_n(data_, n, value_type());
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : data_(new value_type[items.size()]),
      size_(items.size()),
      capacity_(items.size()) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>
vector<T>::vector(const vector<T> &v)
    : data_(new value_type[v.capacity_]),
      size_(v.size_),
      capacity_(v.capacity_) {
  std::copy(v.data_, v.data_ + v.capacity_, data_);
}

template <typename T>
vector<T>::vector(vector &&v) noexcept
    : data_(new value_type[v.capacity_]),
      size_(v.size_),
      capacity_(v.capacity_) {
  std::move(v.data_, v.data_ + v.capacity_, data_);
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
vector<T>::~vector() {
  size_ = 0;
  capacity_ = 0;
  if (data_) delete[] data_;
}

template <typename T>
vector<T> &vector<T>::operator=(vector<T> &&v) noexcept {
  if (this != &v) {
    this->swap(v);

    delete[] v.data_;
    v.size_ = 0;
    v.capacity_ = 0;
    v.data_ = nullptr;
  }

  return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() noexcept {
  return iterator(data_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() noexcept {
  return iterator(data_ + size_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
  return const_iterator(data_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const noexcept {
  return const_iterator(data_ + size_);
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Out of bounds");
  return (*this)[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
  if (pos >= size_) throw std::out_of_range("Out of bounds");
  return (*this)[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::back() {
  return data_[size_ - 1];
}

template <typename T>
typename vector<T>::reference vector<T>::front() {
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  return data_[size_ - 1];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  return data_[0];
}

template <class T>
T *s21::vector<T>::data() noexcept {
  return data_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (!this->capacity_)
    this->reserve(1);
  else if (this->capacity_ < (this->size_ + 1))
    this->reserve(capacity_ * 2);
  data_[size_] = value;
  size_++;
}

template <typename T>
bool vector<T>::empty() const noexcept {
  return !size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<std::size_t>::max() / sizeof(int) / 2;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ == capacity_) return;
  iterator_ptr new_data = new value_type[size_];
  std::move(data_, data_ + size_, new_data);
  delete[] data_;
  capacity_ = size_;
  data_ = new_data;
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  return data_[pos];
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size <= capacity_) return;
  iterator_ptr new_data = new value_type[size];
  std::move(data_, data_ + capacity_, new_data);
  delete[] data_;
  capacity_ = size;
  data_ = new_data;
}

template <typename T>
void vector<T>::resize(size_type size) {
  if (size <= capacity_) {
    size_ = size;
    return;
  }
  iterator_ptr new_data = new value_type[size];
  std::move(data_, data_ + capacity_, new_data);
  delete[] data_;
  capacity_ = size;
  size_ = size;
  data_ = new_data;
}

template <typename T>
void vector<T>::clear() noexcept {
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type idx = pos - begin();

  if (idx > size_) {
    throw std::out_of_range(
        "InsertError: The insertion position is out of range of the vector "
        "memory");
  }

  if (size_ == capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }

  iterator new_pos = begin() + idx;

  for (iterator it = end(); it != new_pos; --it) {
    *it = *(it - 1);
  }
  *new_pos = value;
  ++size_;

  return new_pos;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type position = pos - data_;

  if (position > size_) {
    throw std::out_of_range("EraseError: Index out of range");
  }

  for (iterator it = pos; it != end() - 1; ++it) {
    *it = *(it + 1);
  }
  --size_;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    --size_;
  }
}

template <typename T>
void vector<T>::swap(vector<T> &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  vector<value_type> tmp{args...};
  iterator cur_pos = begin() + (pos - cbegin());
  for (size_t i = 0; i < tmp.size(); ++i) {
    cur_pos = insert(cur_pos, tmp[i]);
    ++cur_pos;
  }

  return cur_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  insert_many(cend(), args...);
}

}  // namespace s21

#include "s21_vector_iterator.h"

#endif  // CPP2_S21_CONTAINERS_2_SRC_VECTOR_S21_VECTOR_H_