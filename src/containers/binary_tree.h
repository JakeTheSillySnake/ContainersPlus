#ifndef BinaryTree_H
#define BinaryTree_H

#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

namespace s21 {
template <typename Key, typename T>
class BinaryTree {
 protected:
  struct Node;
  Node* root = nullptr;
  Node* end_ = nullptr;
  size_t size_ = 0;

 public:
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  class Iterator {
   protected:
    Node* node = nullptr;
    Node* end = nullptr;

   public:
    friend class BinaryTree<Key, T>;
    Iterator(){};
    Iterator(Node* node) : node(node) {}

    const_reference operator*() { return node->key_; }
    iterator operator++();
    iterator operator--();
    bool operator==(const iterator& another_it) {
      return node == another_it.node;
    }
    bool operator!=(const iterator& another_it) {
      return node != another_it.node;
    }
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};
    ConstIterator(Iterator it) {
      Iterator::node = it.node;
      Iterator::end = it.end;
    }
  };

  BinaryTree() = default;
  BinaryTree(const BinaryTree& other) {
    root = copy_(other.root, NULL);
    size_ = other.size_;
  }
  BinaryTree(BinaryTree&& other) {
    root = other.root;
    other.root = nullptr;
    size_ = other.size_;
    other.size_ = 0;
    end_ = other.end_;
    other.end_ = nullptr;
  }
  BinaryTree& operator=(BinaryTree&& other) {
    if (&other == this) return *this;
    clear();
    root = other.root;
    other.root = nullptr;
    size_ = other.size_;
    end_ = other.end_;
    other.end_ = nullptr;
    other.size_ = 0;

    return *this;
  }
  ~BinaryTree() { clear(); };
  iterator begin() const;
  iterator end() const;
  void clear();
  std::pair<iterator, bool> insert(const Key& key);
  void erase(iterator pos);
  void swap(BinaryTree& other);
  void merge(BinaryTree& other);
  iterator find(const Key& key);
  bool contains(const Key& key);
  bool empty();
  size_type size();
  size_type max_size();

 protected:
  struct Node {
    Key key_ = 0U;
    value_type value_ = 0U;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    bool color = true;
    int blackBalance = 0;
    int highBlack = 0;
    Node(Key key, value_type value) : key_(key), value_(value){};
    Node(Key key, value_type value, bool color)
        : key_(key), value_(value), color(color){};
    Node(Key key) : key_(key), color(false){};
  };

  // checks
  Node* find_(const Key& key, Node* node);
  int getHigh_(Node* node);
  Node* whoIsUncle_(Node* node);
  static bool isRightChild_(const Node* node);

  // modifiers
  Node* copy_(Node* node, Node* parent);
  Node* delete_(Node* node, Key key);
  std::pair<Node*, bool> insert_(Key key, Node* node, bool color);
  Node* multi_insert_(Key key, Node* node, bool color);
  void recolorNode_(Node* node);

  // limits
  static Node* maxNode_(Node* node);
  static Node* minNode_(Node* node);

  // balance
  void insertRebalance_(Node* node);
  void lineBalance_(Node* node);
  void triangleBalance_(Node* node);
  Node* checkHighBalance_(Node* node);

  // rotation
  void rightRotation_(Node* rotateNode);
  void leftRotation_(Node* rotateNode);

  // iterators
  static Node* iteratorUp_(Node* node);
  static Node* iteratorDown_(Node* node);

  void clear_(Node* node);
};
#include "binary_tree.ipp"
}  // namespace s21

#endif