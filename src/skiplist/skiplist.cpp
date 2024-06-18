#include "skiplist/skiplist.h"

#include <cstdlib>
#include <iostream>
template <typename K, typename V, typename Comp>
void SkipList<K, V, Comp>::init() {
  skip_list_level = 0;
  element_count = 0;
  head_->next_ = new Node *[max_level_ + 1];
  for (int i = 0; i <= max_level_; i++) {
    head_->next_[i] = tail_;
  }
}

// define constructor
template <typename K, typename V, typename Comp>
SkipList<K, V, Comp>::SkipList()
    : head_(new Node()), tail_(new Node()), comp{Comp()} {
  init();
}

// define destructor
template <typename K, typename V, typename Comp>
SkipList<K, V, Comp>::~SkipList() {

  // free ptr
  delete head_;
  delete tail_;
}

template <typename K, typename V, typename Comp>
int SkipList<K, V, Comp>::get_random_level() {
  int level_random;
  for (level_random = 0;; level_random++) {
    if (rand() & 1) {
      break;
    }
  }
  if (level_random > max_level_) {
    level_random = max_level_;
  }
  return level_random;
}
// find function
template <typename K, typename V, typename Comp>
typename SkipList<K, V, Comp>::Node *SkipList<K, V, Comp>::find(const K &key,
                                                                Node **update) {
  Node *p = head_;
  for (int cur_level = skip_list_level; cur_level >= 0; cur_level--) {
    while (p->next_[cur_level] != tail_ &&
           comp(p->next_[cur_level]->key_, key)) {
      p = p->next_[cur_level];
    }
    // it is used in insert mode
    if (update != nullptr) {
      update[cur_level] = p;
    }
  }
  p = p->next_[0];
  return p;
}
// insert function

template <typename K, typename V, typename Comp>
void SkipList<K, V, Comp>::insert(const K &key, const V &value) {
  mtx_.lock();
  Node *update[max_level_ + 1];
  Node *p = find(key, update);
  if (p != nullptr && p->key_ == key) { // update
    p->value_ = value;
    mtx_.unlock();
    return;
  }
  int new_level_ = get_random_level();
  if (new_level_ > skip_list_level) {
    new_level_ = ++skip_list_level;
    update[new_level_] = head_;
  }
  Node *new_node = new Node(key, value, new_level_);
  for (int i = new_level_; i >= 0; i--) {
    p = update[i];
    new_node->next_[i] = p->next_[i];
    p->next_[i] = new_node;
  }
  element_count++;
  mtx_.unlock();
}

template <typename K, typename V, typename Comp>
typename SkipList<K, V, Comp>::Node *SkipList<K, V, Comp>::find(const K &key) {
  Node *p = find(key, nullptr);
  if (p == tail_) {

    return tail_;
  }
  if (p->key_ == key) {
    return p;
  } else {
    return tail_;
  }
}
template <typename K, typename V, typename Comp>
bool SkipList<K, V, Comp>::erase(const K &key) {
  mtx_.lock();
  Node *find_ = nullptr;
  for (int cur_level = skip_list_level; cur_level >= 0; cur_level--) {
    Node *p = head_;

    while (p->next_[cur_level] != tail_) {
      if (p->next_[cur_level]->key_ == key) {
        if (cur_level == 0) {
          find_ = std::move(p->next_[cur_level]);
          p->next_[cur_level] = find_->next_[cur_level];
        } else {
          p->next_[cur_level] = p->next_[cur_level]->next_[cur_level];
        }
        break;
      }
      p = p->next_[cur_level];
    }
  }

  if (find_ == nullptr) {
    mtx_.unlock();
    return false;
  } else {
    if (head_->next_[skip_list_level] == tail_) {
      skip_list_level--;
    }
    delete find_;
    mtx_.unlock();
    return true;
  }
}

template <typename K, typename V, typename Comp>
void SkipList<K, V, Comp>::display() {
  for (int cur_level = skip_list_level; cur_level >= 0; cur_level--) {
    Node *p = head_;
    std::cout << "level " << cur_level << ": ";
    while (p->next_[cur_level] != tail_) {
      std::cout << p->next_[cur_level]->value_ << " ";
      p = p->next_[cur_level];
    }
    std::cout << "\n";
  }
}
template <typename K, typename V, typename Comp>
int SkipList<K, V, Comp>::size() {
  return element_count;
}

template <typename K, typename V, typename Comp>
void SkipList<K, V, Comp>::clear() {
  Node *p = head_->next_[0];
  while (p != tail_) {
    Node *tmp = p;
    p = p->next_[0];
    delete tmp;
  }
  skip_list_level = 0;
  head_->next_[skip_list_level] = tail_;
}

// Iterator
template <typename K, typename V, typename Comp>
typename SkipList<K, V, Comp>::Iter SkipList<K, V, Comp>::begin() {
  return Iter(head_->next_[0]);
}

template <typename K, typename V, typename Comp>
typename SkipList<K, V, Comp>::Iter SkipList<K, V, Comp>::end() {
  return Iter(tail_);
}

template <typename K, typename V, typename Comp>
V &SkipList<K, V, Comp>::operator[](const K &key) {
  Node *p = find(key);
  if (p != tail_ && p->key_ == key) {
    return p->value_;
  }
  throw std::out_of_range("Key not found in SkipList");
}

// template class SkipList<int, int>; // 显式实例化
template class SkipList<int, int>;
