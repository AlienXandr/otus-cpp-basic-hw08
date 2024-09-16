#pragma once
#include "../../containers/mtx_map.h"
#include <string>
#include <vector>

void read_file_local_map(const std::vector<std::string> &list_files,
                         const size_t min_len, const bool use_filter,
                         size_t n_threads);