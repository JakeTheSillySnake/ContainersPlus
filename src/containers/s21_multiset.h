#ifndef MULTISET_H
#define MULTISET_H

#include <vector>

#include "s21_set.h"

namespace s21 {
template <typename Key>
class multiset : public set<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename set<Key>::iterator;
  using const_iterator = typename set<Key>::const_iterator;
  using size_type = size_t;
  using tree = BinaryTree<Key, Key>;

  multiset() : set<Key>() {}
  multiset(std::initializer_list<value_type> const& items) {
    for (auto i = items.begin(); i != items.end(); i++) {
      insert(*i);
    }
  }
  multiset(const multiset& ms) : set<Key>(ms) {}
  multiset(multiset&& ms) : set<Key>(std::move(ms)) {}
  multiset& operator=(multiset&& ms) {
    if (this != &ms) {
      set<Key>::operator=(std::move(ms));
    }
    return *this;
  }
  ~multiset() = default;

  // extra
  iterator insert(const value_type& value);
  size_type count(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
};
}  // namespace s21
#include "s21_multiset.ipp"

#endif