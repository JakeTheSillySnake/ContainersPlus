#pragma once

using namespace s21;

template <typename Key>
typename std::pair<typename s21::multiset<Key>::iterator,
                   typename s21::multiset<Key>::iterator>
s21::multiset<Key>::equal_range(const_reference key) {
  std::pair<iterator, iterator> res;
  res.first = lower_bound(key);
  res.second = upper_bound(key);
  return res;
}

template <typename Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::upper_bound(
    const_reference key) {
  typename tree::Node* node = tree::root;
  if (tree::root->key_ <= key) {
    typename tree::Node* max = tree::maxNode_(tree::root);
    while (node->key_ <= key && node->key_ != max->key_) {
      node = tree::iteratorUp_(node);
    }
  } else {
    typename tree::Node* min = tree::minNode_(tree::root);
    while (node->key_ > key && node->key_ != min->key_) {
      node = tree::iteratorDown_(node);
    }
    node =
        ((node == min) && (min->key_ == key)) ? tree::iteratorUp_(node) : node;
  }
  return iterator(node);
}

template <typename Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::lower_bound(
    const_reference key) {
  if (tree::root->key_ == key) return iterator(tree::root);

  typename tree::Node* node = tree::root;

  if (tree::root->key_ > key) {
    typename tree::Node* min = tree::minNode_(tree::root);
    while (node->key_ >= key && node->key_ != min->key_) {
      node = tree::iteratorDown_(node);
    }
    if (node->key_ < key) node = tree::iteratorUp_(node);
  } else {
    typename tree::Node* max = tree::maxNode_(tree::root);

    while (node->key_ != key && node->key_ != max->key_) {
      node = tree::iteratorUp_(node);
    }
  }
  return iterator(node);
}

template <typename Key>
size_t s21::multiset<Key>::count(const_reference key) {
  size_t res = 0;
  for (auto it = set<Key>::begin(); it != set<Key>::end(); ++it) {
    if (*it == key) res++;
  }
  return res;
}

template <typename Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::insert(
    const Key& key) {
  if (!tree::root) {
    tree::root = new typename tree::Node(key, true);
    tree::size_++;
    return iterator(tree::root);
  }
  return iterator(tree::multi_insert_(key, tree::root, false));
}