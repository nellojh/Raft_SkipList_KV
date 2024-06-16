#include "skiplist/skiplist.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

constexpr std::string STORE_FILE = "store/dumpFile";

bool file_exists(const std::string &filename) {
  struct stat buffer {};
  return (stat(filename.c_str(), &buffer) == 0);
}

void create_file(const std::string &filename) {
  std::ofstream file(filename);
  file.close();
}

template <typename K, typename V, typename Comp>
void SkipList<K, V, Comp>::dump() {
  if (!file_exists(STORE_FILE)) {
    std::cout << "文件不存在，新建文件ing...\n";
    create_file(STORE_FILE);
    std::cout << "文件创建成功！\n";
  }
  std::ofstream file_writer(STORE_FILE,
                            std::ofstream::out | std::ofstream::trunc);
  for (typename SkipList<K, V, Comp>::Iter it = begin(); it != end(); it++) {
    file_writer << it->key_ << " " << it->value_ << std::endl;
    std::cout << it->key_ << " " << it->value_ << std::endl;
  }
  file_writer.flush();
  file_writer.close();
  std::cout << "-------落盘成功-------\n";
}

template <typename K, typename V, typename Comp>
void SkipList<K, V, Comp>::load() {
  std::ifstream file_reader(STORE_FILE, std::ifstream::in);
  if (!file_reader.is_open()) {
    std::cout << "ERROR!!!文件打开失败！\n";
    return;
  }
  K key;
  V value;
  std::cout << "-------开始读取本地文件-------\n";
  while (file_reader >> key >> value) {
    std::cout << key << " " << value << std::endl;
    insert(key, value);
  }
  std::cout << "-------读盘成功-------\n";
  file_reader.close();
}

template class SkipList<int, int>;