#include "add_word_in_map.h"
#include "../filter/filter.h"
#include "../to_lower/to_lower.h"

void add_word_in_map(const std::string &word, IMap &map, const size_t min_len,
                     const bool use_filter) {

  std::string filtered_word = word;
  if (use_filter) {
    filtered_word = filter(filtered_word);
  }
  if (filtered_word.size() >= min_len) {
    filtered_word = to_lower(filtered_word);
    map.add_word(filtered_word);
  }
}
