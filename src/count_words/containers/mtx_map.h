#pragma once
#include "IMap.h"
#include <iostream>
#include <mutex>
#include <string>
#include <unordered_map>

class MtxMap : public IMap {
public:
  MtxMap() = default;
  ~MtxMap() override = default;

  void add_word(const std::string &word) override {
    std::lock_guard lock{mtx_};
    //    std::cout << "TID: " << std::this_thread::get_id() << '\n';
    //    std::cout << "MtxMap::add_word:: " << word << '\n';
    ++map_[word];
  }

  size_t size() const override { return map_.size(); }

  std::unordered_map<std::string, std::size_t>::iterator begin() {
    return std::begin(map_);
  }
  std::unordered_map<std::string, std::size_t>::const_iterator begin() const {
    return std::cbegin(map_);
  }
  std::unordered_map<std::string, std::size_t>::iterator end() {
    return std::end(map_);
  }
  std::unordered_map<std::string, std::size_t>::const_iterator end() const {
    return std::cend(map_);
  }

  typedef std::unordered_map<std::string, std::size_t>::const_iterator
      const_iterator;

private:
  std::mutex mtx_;
  std::unordered_map<std::string, std::size_t> map_;
};