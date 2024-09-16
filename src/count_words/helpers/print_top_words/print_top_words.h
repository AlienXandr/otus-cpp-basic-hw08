#pragma once
#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename T>
void print_top_words(std::ostream &stream, const T &map, const size_t n_top) {

  std::vector<typename T::const_iterator> words;
  words.reserve(map.size());
  for (auto it = std::cbegin(map); it != std::cend(map); ++it) {
    words.push_back(it);
  }

  std::partial_sort(
      std::begin(words), std::begin(words) + n_top, std::end(words),
      [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

  std::for_each(std::begin(words), std::begin(words) + n_top,
                [&stream](const typename T::const_iterator &pair) {
                  stream << std::setw(4) << pair->second << " " << pair->first
                         << '\n';
                });
};
