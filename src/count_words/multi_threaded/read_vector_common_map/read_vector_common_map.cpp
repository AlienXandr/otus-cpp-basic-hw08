#include "read_vector_common_map.h"
#include "../../helpers/add_word_in_map/add_word_in_map.h"
#include "../../helpers/print_top_words/print_top_words.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <thread>
#include <unordered_map>

void task1(const std::vector<std::string> &words, MtxMap &mtx_map,
           const size_t min_len, const bool use_filter, size_t step,
           size_t iter_shift) {

  //  std::cout << "TID: " << std::this_thread::get_id() << " started\n";

  //  auto it = std::begin(words);
  //  auto itEnd = std::end(words);
  //  std::advance(it, iter_shift); // Start shift
  //  int count = 0;
  //  for (; it != itEnd; std::advance(it, step), count++) {
  //    const std::string &word = *it;
  //    if (word.size() >= min_len) {
  //      add_word_in_map(word, mtx_map, min_len, use_filter);
  //    }
  //    //    std::this_thread::sleep_for(std::chrono::seconds(1));
  //  }

  size_t i = 0;
  i += iter_shift; // Start shift

  for (; i < words.size(); i += step) {
    const std::string &word = words[i];
    if (word.size() >= min_len) {
      add_word_in_map(word, mtx_map, min_len, use_filter);
    }
    //    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  //  std::cout << "TID: " << std::this_thread::get_id() << " is finishing\n";
}

void read_vector_common_map(const std::vector<std::string> &list_files,
                            const size_t min_len, const bool use_filter,
                            size_t n_threads) {

  auto start = std::chrono::high_resolution_clock::now();

  //  size_t word_count = 0;
  //  for (size_t i = 0; i < list_files.size(); ++i) {
  //    std::ifstream input{list_files[i]};
  //    if (!input.is_open()) {
  //      throw std::runtime_error(std::string("Failed to open file ") +
  //                               list_files[i]);
  //    }
  //    auto itStart = std::istream_iterator<std::string>(input);
  //    auto itEnd = std::istream_iterator<std::string>();
  //    word_count += std::distance(itStart, itEnd);
  //    input.close();
  //  }

  std::vector<std::string> words;
  //  words.reserve(word_count);
  for (size_t i = 0; i < list_files.size(); ++i) {
    std::ifstream input{list_files[i]};
    if (!input.is_open()) {
      throw std::runtime_error(std::string("Failed to open file ") +
                               list_files[i]);
    }
    auto it = std::istream_iterator<std::string>(input);
    auto itEnd = std::istream_iterator<std::string>();

    for (; it != itEnd; it++) {
      words.push_back(*it);
    }

    input.close();
  }

  MtxMap mtx_map;

  std::vector<std::thread> workers;
  size_t iter_shift = 0;
  std::generate_n(std::back_inserter(workers), n_threads, [&]() {
    return std::thread{task1,      std::ref(words), std::ref(mtx_map), min_len,
                       use_filter, n_threads,       iter_shift++};
  });

  std::for_each(workers.begin(), workers.end(),
                [](std::thread &th) { th.join(); });

  print_top_words(std::cout, mtx_map, 10);

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed_ms =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}