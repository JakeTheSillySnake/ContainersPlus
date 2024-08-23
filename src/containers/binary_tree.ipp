#pragma once

using namespace s21;

template <typename Key, typename T>
size_t s21::BinaryTree<Key, T>::max_size() {
  std::allocator<Node> tmp;
  return tmp.max_size();
}

template <typename Key, typename T>
void s21::BinaryTree<Key, T>::merge(s21::BinaryTree<Key, T>& other) {
  typename s21::BinaryTree<Key, T>::Iterator b = other.begin();
  typename s21::BinaryTree<Key, T>::Iterator e = other.end();
  for (; b != e; ++b) {
    insert(*b);
  }
  other.clear();
}

template <typename Key, typename T>
void s21::BinaryTree<Key, T>::swap(s21::BinaryTree<Key, T>& other) {
  std::swap(root, other.root);
  std::swap(end_, other.end_);
  std::swap(size_, other.size_);
  return;
}

template <typename Key, typename T>
void s21::BinaryTree<Key, T>::clear() {
  clear_(root);
  delete root;
  root = nullptr;
  size_ = 0;
  return;
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Iterator s21::BinaryTree<Key, T>::begin()
    const {
  Iterator it(minNode_(root));
  return it;
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Iterator s21::BinaryTree<Key, T>::end()
    const {
  Iterator it;
  it.end = maxNode_(root);
  return it;
}

template <typename Key, typename T>
size_t s21::BinaryTree<Key, T>::size() {
  return size_;
}

template <typename Key, typename T>
std::pair<typename s21::BinaryTree<Key, T>::Iterator, bool>
s21::BinaryTree<Key, T>::insert(const Key& key) {
  std::pair<Iterator, bool> res;
  if (!root) {
    root = new Node(key, true);
    size_++;
    res.first = Iterator(root);
    res.second = true;
    return res;
  }
  std::pair<Node*, bool> tmp = insert_(key, root, false);
  res.first = Iterator(tmp.first);
  if (tmp.second) {
    res.second = true;
  } else {
    res.second = false;
  }
  return res;
}

template <typename Key, typename T>
bool s21::BinaryTree<Key, T>::contains(const Key& key) {
  if (find_(key, root)) return true;
  return false;
}

template <typename Key, typename T>
bool s21::BinaryTree<Key, T>::empty() {
  if ((size_ == 0) && (root == nullptr)) return true;
  return false;
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Iterator s21::BinaryTree<Key, T>::find(
    const Key& key) {
  return Iterator(find_(key, root));
}

template <typename Key, typename T>
void s21::BinaryTree<Key, T>::erase(iterator pos) {
  if (root && pos.node) {
    root = delete_(root, *pos);
    size_--;
  }
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::iterator
s21::BinaryTree<Key, T>::Iterator::operator++() {
  Node* tmp = iteratorUp_(node);
  if (tmp == node) {
    end = tmp;
    node = nullptr;
  } else
    node = tmp;
  return Iterator(node);
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::iterator
s21::BinaryTree<Key, T>::Iterator::operator--() {
  if (end) {
    node = end;
    end = nullptr;
  } else
    node = iteratorDown_(node);
  return Iterator(this->node);
};

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Node* s21::BinaryTree<Key, T>::copy_(
    Node* node, Node* parent) {
  if (node == NULL) return NULL;
  Node* tmp = new Node(node->key_, node->value_, node->color);
  tmp->parent = parent;
  tmp->left = copy_(node->left, tmp);
  tmp->right = copy_(node->right, tmp);
  return tmp;
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Node* s21::BinaryTree<Key, T>::delete_(
    Node* node, Key key) {
  if (!node) return nullptr;
  if (key < node->key_)
    node->left = delete_(node->left, key);
  else if (key > node->key_)
    node->right = delete_(node->right, key);
  else {
    if (!node->left || !node->right) {
      Node* right_ = node->right;
      Node* left_ = node->left;
      Node* parent_ = node->parent;
      Node* tmp = node;
      if (!node->left)
        node = right_;
      else
        node = left_;
      if (node) node->parent = parent_;
      delete tmp;
    } else {
      Node* min = minNode_(node->right);
      node->key_ = min->key_;
      node->value_ = min->value_;
      node->right = delete_(node->right, min->key_);
    }
  }
  if (node) {
    getHigh_(node);
    checkHighBalance_(node);
  }
  return node;
}

template <typename Key, typename T>
void s21::BinaryTree<Key, T>::clear_(Node* node) {
  if (node) {
    clear_(node->left);
    clear_(node->right);
    delete node->left;
    delete node->right;
    node->left = nullptr;
    node->right = nullptr;
  }
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Node* s21::BinaryTree<Key, T>::maxNode_(
    Node* node) {
  if (!node) return nullptr;
  Node* tmp = node;
  while (tmp->right) {
    tmp = tmp->right;
  }
  return tmp;
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Node* s21::BinaryTree<Key, T>::minNode_(
    Node* node) {
  if (!node) return nullptr;
  Node* tmp = node;
  while (tmp->left) {
    tmp = tmp->left;
  }
  return tmp;
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Node* s21::BinaryTree<Key, T>::iteratorDown_(
    Node* node) {
  Node* tmp = nullptr;
  if (node->left)
    tmp = maxNode_(node->left);
  else {
    if (isRightChild_(node)) {
      tmp = node->parent;
    } else {
      tmp = node;
      while ((tmp->parent) && !isRightChild_(tmp)) {
        tmp = tmp->parent;
      }
      if (tmp->parent) {
        tmp = tmp->parent;
      } else {
        tmp = node;
      }
    }
  }
  return tmp;
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Node* s21::BinaryTree<Key, T>::iteratorUp_(
    Node* node) {
  Node* tmp = nullptr;
  if (node->right)
    tmp = minNode_(node->right);
  else {
    if (isRightChild_(node)) {
      tmp = node;
      while ((tmp->parent) && isRightChild_(tmp)) {
        tmp = tmp->parent;
      }
      if (tmp->parent) {
        tmp = tmp->parent;
      } else {
        tmp = node;
      }
    } else {
      tmp = node->parent;
    }
  }
  return tmp;
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Node*
s21::BinaryTree<Key, T>::checkHighBalance_(Node* node) {
  if (!node) return nullptr;
  if (node->blackBalance != 0) {
    return node;
  }
  Node* tmp_left = checkHighBalance_(node->left);
  Node* tmp_right = checkHighBalance_(node->right);

  int tmp_high_left = (tmp_left) ? tmp_left->highBlack : 0;
  int tmp_high_right = (tmp_right) ? tmp_right->highBlack : 0;

  return (tmp_high_left > tmp_high_right) ? tmp_left : tmp_right;
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Node* s21::BinaryTree<Key, T>::find_(
    const Key& key, Node* node) {
  if (!node) return nullptr;
  if (node->key_ == key) return node;
  if (node->key_ < key) {
    if (node->right) {
      return find_(key, node->right);
    } else
      return nullptr;
  } else {
    if (node->left) {
      return find_(key, node->left);
    } else
      return nullptr;
  }
}

template <typename Key, typename T>
int s21::BinaryTree<Key, T>::getHigh_(Node* node) {
  if (!node) return 0;
  int left = getHigh_(node->left);
  int right = getHigh_(node->right);
  if (left > right)
    node->highBlack = (!node->color || !node->parent) ? left : left + 1;
  else
    node->highBlack = (!node->color || !node->parent) ? right : right + 1;
  node->blackBalance = right - left;
  return node->highBlack;
}

template <typename Key, typename T>
void s21::BinaryTree<Key, T>::insertRebalance_(Node* node) {
  if (node->parent->color) return;
  Node* uncle = nullptr;
  uncle = whoIsUncle_(node->parent);
  if (uncle && !uncle->color) {
    recolorNode_(uncle);
    recolorNode_(node->parent);
    recolorNode_(uncle->parent);
  } else {
    if (isRightChild_(node) ^ isRightChild_(node->parent)) {
      triangleBalance_(node);
    } else {
      lineBalance_(node);
    }
  }
  if (!root->color) root->color = true;
  if ((node != root) && node->parent->parent && (node->parent->parent != root))
    insertRebalance_(node->parent->parent);
}

template <typename Key, typename T>
void s21::BinaryTree<Key, T>::triangleBalance_(Node* node) {
  if (isRightChild_(node)) {
    leftRotation_(node->parent);
    recolorNode_(node->parent);  // nodeRecolor grand
    recolorNode_(node);          // nodeRecolor parent

    rightRotation_(node->parent);
  } else {
    rightRotation_(node->parent);
    recolorNode_(node->parent);  // nodeRecolor grand
    recolorNode_(node);          // nodeRecolor parent
    leftRotation_(node->parent);
  }
}

template <typename Key, typename T>
void s21::BinaryTree<Key, T>::lineBalance_(Node* node) {
  recolorNode_(node->parent->parent);  // nodeRecolor grand
  recolorNode_(node->parent);          // nodeRecolor parent
  if (isRightChild_(node->parent))
    leftRotation_(node->parent->parent);
  else
    rightRotation_(node->parent->parent);
}

template <typename Key, typename T>
bool s21::BinaryTree<Key, T>::isRightChild_(const Node* node) {
  if ((node->parent) && (node == node->parent->right))
    return true;
  else
    return false;
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Node* s21::BinaryTree<Key, T>::whoIsUncle_(
    Node* node) {
  Node* uncle = nullptr;
  if (node == node->parent->left) {
    uncle = (node->parent->right) ? node->parent->right : nullptr;
  } else {
    uncle = (node->parent->left) ? node->parent->left : nullptr;
  }
  return uncle;
}

template <typename Key, typename T>
void s21::BinaryTree<Key, T>::recolorNode_(Node* node) {
  if (node) node->color = (node->color) ? false : true;
}

template <typename Key, typename T>
std::pair<typename s21::BinaryTree<Key, T>::Node*, bool>
s21::BinaryTree<Key, T>::insert_(Key key, Node* node, bool color) {
  Node* tmp = nullptr;
  if (node->key_ == key) return std::pair<Node*, bool>(node, false);
  if (node->key_ < key) {
    if (node->right)
      return insert_(key, node->right, color);
    else {
      node->right = new Node(key);
      tmp = node->right;
      node->right->parent = node;
      size_++;
      insertRebalance_(node->right);
      getHigh_(root);
      return std::pair<Node*, bool>(tmp, true);
    }
  } else {
    if (node->left)
      return insert_(key, node->left, color);
    else {
      node->left = new Node(key);
      tmp = node->left;
      node->left->parent = node;
      size_++;
      insertRebalance_(node->left);
      getHigh_(root);
      return std::pair<Node*, bool>(tmp, true);
    }
  }
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::Node* s21::BinaryTree<Key, T>::multi_insert_(
    Key key, Node* node, bool color) {
  Node* tmp = nullptr;
  if (node->key_ < key) {
    if (node->right)
      tmp = multi_insert_(key, node->right, color);
    else {
      node->right = new Node(key);
      tmp = node->right;
      node->right->parent = node;
      size_++;
      insertRebalance_(node->right);
      getHigh_(root);
    }
  } else {
    if (node->left)
      tmp = multi_insert_(key, node->left, color);
    else {
      node->left = new Node(key);
      tmp = node->left;
      node->left->parent = node;
      size_++;
      insertRebalance_(node->left);
      getHigh_(root);
    }
  }
  return tmp;
}

template <typename Key, typename T>
void s21::BinaryTree<Key, T>::leftRotation_(Node* rotateNode) {
  if (!rotateNode) return;
  Node* tmp = nullptr;
  if (rotateNode->right->left) {
    tmp = rotateNode->right->left;
  }
  if (rotateNode->parent) {
    if (rotateNode->parent->right == rotateNode)
      rotateNode->parent->right = rotateNode->right;
    else
      rotateNode->parent->left = rotateNode->right;
    rotateNode->right->parent = rotateNode->parent;
  } else {
    rotateNode->right->parent = nullptr;
    root = rotateNode->right;
  }
  rotateNode->right->left = rotateNode;
  rotateNode->parent = rotateNode->right;
  if (tmp) {
    tmp->parent = rotateNode;
    rotateNode->right = tmp;
  } else
    rotateNode->right = nullptr;
}

template <typename Key, typename T>
void s21::BinaryTree<Key, T>::rightRotation_(Node* rotateNode) {
  if (!rotateNode) return;
  Node* tmp = nullptr;
  if ((rotateNode->left) && (rotateNode->left->right)) {
    tmp = rotateNode->left->right;
  }
  if (rotateNode->parent) {
    if (rotateNode->parent->left == rotateNode)
      rotateNode->parent->left = rotateNode->left;
    else
      rotateNode->parent->right = rotateNode->left;
    rotateNode->left->parent = rotateNode->parent;
  } else {
    rotateNode->left->parent = nullptr;
    root = rotateNode->left;
  }
  rotateNode->left->right = rotateNode;
  rotateNode->parent = rotateNode->left;
  if (tmp) {
    tmp->parent = rotateNode;
    rotateNode->left = tmp;
  } else
    rotateNode->left = nullptr;
}