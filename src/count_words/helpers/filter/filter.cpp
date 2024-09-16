#include "filter.h"
#include <regex>

std::string filter(const std::string &word) {
  return std::regex_replace(word, std::regex(R"([^a-zA-Z])"), "");
};