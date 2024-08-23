#ifndef CPP2_S21_CONTAINERS_2_SRC_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_2_SRC_ARRAY_S21_ARRAY_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a) noexcept;
  ~array() = default;

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

  bool empty() noexcept;
  size_type size() noexcept;
  size_type max_size() noexcept;

  void swap(array &a) noexcept;
  void fill(const_reference value);

  array &operator=(const array &a);
  array &operator=(array &&a) noexcept;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

 private:
  size_type size_ = N;
  value_type data_[N] = {};
};

template <typename T, std::size_t N>
array<T, N>::array() : size_(N) {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  if (items.size() > size()) throw std::out_of_range("Too many elements");
  std::copy(items.begin(), items.end(), data_);
}

template <typename T, std::size_t N>
array<T, N>::array(const array<T, N> &a) {
  std::copy(a.cbegin(), a.cend(), data_);
}

template <typename T, std::size_t N>
array<T, N>::array(array<T, N> &&a) noexcept {
  std::move(a.begin(), a.end(), data_);
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return data_ + size_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin(void) const noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cend(void) const noexcept {
  return data_ + size_;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos > size()) throw std::out_of_range("Out of bounds");
  return (*this)[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos > size_) throw std::out_of_range("Out of bounds");
  return (*this)[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::front() {
  return *begin();
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::back() {
  return *(this->end() - 1);
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return *this->cbegin();
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return *(this->cend() - 1);
}

template <typename T, std::size_t N>
bool array<T, N>::empty() noexcept {
  return !size_;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() noexcept {
  return size_;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() noexcept {
  return size_;
}

template <typename T, std::size_t N>
void array<T, N>::swap(array<T, N> &a) noexcept {
  if (this->begin() == a.begin()) return;
  std::swap_ranges(this->begin(), this->end(), a.data_);
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(this->begin(), this->end(), value);
}

template <typename T, std::size_t N>
typename array<T, N>::array &array<T, N>::operator=(const array<T, N> &a) {
  std::copy(a.data_, a.data_ + a.size_, data_);
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::array &array<T, N>::operator=(array<T, N> &&a) noexcept {
  std::copy(a.data_, a.data_ + a.size_, data_);
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  return data_[pos];
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_2_SRC_ARRAY_S21_ARRAY_H_