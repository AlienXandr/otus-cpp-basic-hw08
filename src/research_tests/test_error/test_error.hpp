#pragma once

#include <string>
#include <vector>

void foo(const std::string &word, size_t count) {};

void test_error() {

  std::vector<std::string> words(10);
  size_t count = 0;
  foo(words[count], count++);
}
