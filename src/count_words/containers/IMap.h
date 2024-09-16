#pragma once
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <unordered_map>

class IMap {
public:
  virtual ~IMap() = default;
  virtual void add_word(const std::string &word) = 0;
  virtual size_t size() const = 0;
};