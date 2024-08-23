#pragma once

using namespace s21;

template <typename Key, typename T>
std::pair<Key, T> s21::map<Key, T>::iterator::operator*() {
  if (!BinaryTree<Key, T>::Iterator::node) {
    std::pair<Key, T> tmp{0U, 0U};
    return tmp;
  }
  Key key = BinaryTree<Key, T>::Iterator::node->key_;
  T value = BinaryTree<Key, T>::Iterator::node->value_;
  std::pair<Key, T> tmp{key, value};
  return tmp;
}

template <typename Key, typename T>
typename s21::map<Key, T>::iterator s21::map<Key, T>::find(const Key& key) {
  return iterator(BinaryTree<Key, T>::find_(key, BinaryTree<Key, T>::root));
}

template <typename Key, typename T>
std::pair<typename s21::map<Key, T>::iterator, bool> s21::map<Key, T>::insert(
    const value_type& value) {
  return insert(value.first, value.second);
}

template <typename Key, typename T>
std::pair<typename s21::map<Key, T>::iterator, bool> s21::map<Key, T>::insert(
    const Key& key, const T& obj) {
  std::pair<iterator, bool> res;
  if (!BinaryTree<Key, T>::root) {
    BinaryTree<Key, T>::root = new typename BinaryTree<Key, T>::Node(key, obj);
    res.first = iterator(BinaryTree<Key, T>::root);
    res.second = true;
    BinaryTree<Key, T>::size_++;
  } else {
    auto check =
        BinaryTree<Key, T>::insert_(key, BinaryTree<Key, T>::root, false);
    res.first = iterator(check.first);
    res.second = check.second;
    if (res.second) check.first->value_ = obj;
  }
  return res;
}

template <typename Key, typename T>
std::pair<typename s21::map<Key, T>::iterator, bool>
s21::map<Key, T>::insert_or_assign(const Key& key, const T& obj) {
  auto it = find(key);
  if (it != NULL) {
    erase(it);
    auto tmp = insert(key, obj);
    tmp.second = false;
    return tmp;
  }
  return insert(key, obj);
}

template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename s21::map<Key, T>::iterator, bool>>
s21::map<Key, T>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> res;
  for (auto i : {args...}) res.push_back(insert(*i));
  return res;
}

template <typename Key, typename T>
typename s21::map<Key, T>::iterator s21::map<Key, T>::begin() {
  iterator it(BinaryTree<Key, T>::minNode_(BinaryTree<Key, T>::root));
  return it;
}

template <typename Key, typename T>
typename s21::map<Key, T>::iterator s21::map<Key, T>::end() {
  return NULL;
}

template <typename Key, typename T>
void s21::map<Key, T>::erase(iterator pos) {
  if (BinaryTree<Key, T>::root && pos.node) {
    BinaryTree<Key, T>::root =
        BinaryTree<Key, T>::delete_(BinaryTree<Key, T>::root, (*pos).first);
    BinaryTree<Key, T>::size_--;
  }
}

template <typename Key, typename T>
void s21::map<Key, T>::merge(map& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    auto key = (*it).first;
    auto obj = (*it).second;
    insert(key, obj);
  }
  other.clear();
}

template <typename Key, typename T>
T& s21::map<Key, T>::at(const Key& key) {
  auto it = find(key);
  if (it == NULL) throw std::out_of_range("Key not in container.");
  return it.val();
}

template <typename Key, typename T>
T& s21::map<Key, T>::operator[](const Key& key) {
  auto it = find(key);
  if (it == NULL) {
    auto tmp = insert(key, T());
    it = tmp.first;
  }
  return it.val();
}