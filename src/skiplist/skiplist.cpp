#include "skiplist/skiplist.h"

#include <cstdlib>
template <typename K, typename V, typename Comp>
void SkipList<K, V, Comp>::init() {
    skip_list_level = 0;
    element_count   = 0;
    head_->next     = new Node *[ max_level_ + 1 ];
    for (int i = 0; i <= max_level_; i++) {
        head_->next[ i ] = tail_;
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
    for (int cur_level = max_level_; cur_level >= 0; cur_level--) {
        while (p->next_[ cur_level ] != tail_ &&
               comp(p->next_[ cur_level ]->key, key)) {
            p = p->next_[ cur_level ];
        }
        // it is used in insert mode
        if (update != nullptr) {
            update[ cur_level ] = p;
        }
    }
    p = p->next_[ 0 ];
    return 0;
}
// insert function

template <typename K, typename V, typename Comp>
void SkipList<K, V, Comp>::insert(const K &key, const V &value) {
    Node *update[ max_level_ + 1 ];
    Node *p = find(key, update);

    if (p->key_ == key) {  // update
        p->value_ = value;
        return;
    }
    int new_level_ = get_random_level();

    if (new_level_ > skip_list_level) {
        new_level_           = ++skip_list_level;
        update[ new_level_ ] = head_;
    }
    Node *new_node = new Node(key, value, new_level_);
    for (int i = new_level_; i > 0; i--) {
        p                    = update[ i ];
        new_node->next_[ i ] = p->next_[ i ];
        p->next_[ i ]        = new_node;
    }
    element_count++;
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
