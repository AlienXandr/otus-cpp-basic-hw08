#pragma once
#include "../../containers/IMap.h"
#include <string>

void add_word_in_map(const std::string &word, IMap &map, const size_t min_len,
                     const bool use_filter);
