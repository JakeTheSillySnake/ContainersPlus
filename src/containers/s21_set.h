#ifndef SET_H
#define SET_H

#include <vector>

#include "binary_tree.h"

namespace s21 {
template <typename T>
class set : public BinaryTree<T, T> {
 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<T, T>::Iterator;
  using const_iterator = typename BinaryTree<T, T>::ConstIterator;
  using size_type = size_t;

  set() : BinaryTree<T, T>() {}
  set(std::initializer_list<value_type> const& items) {
    for (auto i = items.begin(); i != items.end(); i++) {
      BinaryTree<T, T>::insert(*i);
    }
  }
  set(const set& other) : BinaryTree<T, T>(other) {}
  set(set&& other) : BinaryTree<T, T>(std::move(other)) {}
  set& operator=(set&& other) {
    if (this != &other) {
      BinaryTree<T, T>::operator=(std::move(other));
    }
    return *this;
  }
  ~set() = default;

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> res;
    for (auto x : {args...}) {
      if (!std::is_same<decltype(x), T>::value)
        throw std::out_of_range("wrong type of value");
      res.push_back(BinaryTree<T, T>::insert(x));
    }
    return res;
  }  // LCOV_EXCL_LINE
};
}  // namespace s21

#endif