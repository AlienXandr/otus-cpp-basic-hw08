#include "read_file_local_map.h"
#include "../../helpers/add_word_in_map/add_word_in_map.h"
#include "../../helpers/print_top_words/print_top_words.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <unordered_map>

void task(const std::vector<std::string> &list_files, MtxMap &mtx_map,
          const size_t min_len, const bool use_filter, size_t step,
          size_t iter_shift);

void read_file_local_map(const std::vector<std::string> &list_files,
                         const size_t min_len, const bool use_filter,
                         size_t n_threads) {

  auto start = std::chrono::high_resolution_clock::now();

  std::vector<MtxMap> maps(n_threads);
  std::vector<std::thread> workers;
  size_t iter_shift = 0;
  size_t count = 0;
  std::generate_n(std::back_inserter(workers), n_threads, [&]() {
    return std::thread{
        task,        std::ref(list_files), std::ref(maps[count++]),
        min_len,     use_filter,           n_threads,
        iter_shift++};
  });

  std::for_each(workers.begin(), workers.end(),
                [](std::thread &th) { th.join(); });

  std::unordered_map<std::string, size_t> finish_map;
  for (auto &map : maps) {
    for (auto it = std::cbegin(map); it != std::cend(map); ++it) {
      finish_map[it->first] += it->second;
    }
  }

  print_top_words(std::cout, finish_map, 10);

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed_ms =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}