#ifndef MAP_H
#define MAP_H

#include <vector>

#include "binary_tree.h"

using namespace std;

namespace s21 {
template <typename Key, typename T>
class map : public BinaryTree<Key, T> {
 public:
  class MapIterator;
  class MapConstIterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;
  using size_type = size_t;

  map() = default;
  map(std::initializer_list<value_type> const& items) {
    for (auto i = items.begin(); i != items.end(); i++) insert(*i);
  }
  map(const map& m) : BinaryTree<Key, T>(m) {}
  map(map&& m) : BinaryTree<Key, T>(std::move(m)) {}
  ~map() = default;
  map& operator=(map&& m) {
    if (this != &m) BinaryTree<Key, T>::std::move(m);
    return *this;
  }

  // overwrite from BinaryTree
  iterator begin();
  iterator end();
  void erase(iterator pos);
  void merge(map& other);
  iterator find(const Key& key);

  // special methods
  T& at(const Key& key);
  T& operator[](const Key& key);
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  class MapIterator : public BinaryTree<Key, T>::Iterator {
   public:
    friend class map;
    MapIterator() : BinaryTree<Key, T>::Iterator() {}
    MapIterator(typename BinaryTree<Key, T>::Node* node)
        : BinaryTree<Key, T>::Iterator(node) {}
    std::pair<Key, T> operator*();

   private:
    T& val() {
      if (BinaryTree<Key, T>::Iterator::node == NULL) {
        static T tmp{};
        return tmp;
      }
      return BinaryTree<Key, T>::Iterator::node->value_;
    }
  };

  class MapConstIterator : public MapIterator {
   public:
    MapConstIterator() : MapIterator() {}
    MapConstIterator(typename BinaryTree<Key, T>::Node* node)
        : MapIterator(node) {}
    const_reference operator*() const { return MapIterator::operator*(); }
  };
};
#include "s21_map.ipp"
}  // namespace s21

#endif