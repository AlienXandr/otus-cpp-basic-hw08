#include "to_lower.h"
#include <algorithm>

std::string to_lower(const std::string &word) {
  std::string lower_word = word;
  std::transform(std::cbegin(word), std::cend(word), std::begin(lower_word),
                 [](unsigned char ch) { return std::tolower(ch); });
  return lower_word;
}