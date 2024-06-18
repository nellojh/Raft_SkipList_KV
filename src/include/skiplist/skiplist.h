#include <mutex>
#include <string>
template <typename T> struct Less {
  bool operator()(const T a, const T b) { return a < b; }
};

template <typename K, typename V, typename Comp = Less<K>> class SkipList {
private:
  struct Node {
    const K key_;
    V value_;
    Node **next_;
    int level_;
    Node() : key_(0), value_(0), level_(0), next_(nullptr) {}
    Node(const K &k, const V &v, const int level_, Node *nxt = nullptr)
        : key_(k), value_(v), level_(level_) {
      this->next_ = new Node *[level_ + 1];
      for (int i = 0; i <= level_; i++) {
        this->next_[i] = nxt;
      }
    }
    ~Node() { delete[] next_; }
  };
  void init();
  static constexpr int max_level_ = 32;
  int skip_list_level;
  int element_count;
  Node *head_, *tail_;
  Comp comp;
  std::mutex mtx_;
  Node *find(const K &key, Node **update);

public:
  SkipList();
  SkipList(Comp);
  ~SkipList();
  int get_random_level();
  void insert(const K &key, const V &value);
  bool erase(const K &key);
  Node *find(const K &key);
  void clear();
  int size();
  void display();
  void dump();
  void load();
  struct Iter {
    Node *p;
    Iter() : p(nullptr) {}
    Iter(Node *rhs) : p(rhs) {}
    // 避免值的改变
    Node &operator*() const { return *p; }
    Node *operator->() const { return (p); }
    bool operator==(const Iter &rhs) const { return p == rhs.p; }
    bool operator!=(const Iter &rhs) const { return p != rhs.p; }
    void operator++(int) { p = p->next_[0]; }
  };
  Iter begin();
  Iter end();
  Iter find_(const K &key);
  V &operator[](const K &key);
};

// files
bool file_exists(const std::string &filename);
void create_file(const std::string &filename);