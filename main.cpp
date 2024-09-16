#include "src/count_words/containers/mtx_map.h"
#include "src/count_words/multi_threaded/read_file_common_map/read_file_common_map.h"
#include "src/count_words/multi_threaded/read_file_local_map/read_file_local_map.h"
#include "src/count_words/multi_threaded/read_vector_common_map/read_vector_common_map.h"
#include "src/count_words/multi_threaded/read_vector_local_map/read_vector_local_map.h"
#include "src/research_tests/compare_speed_calc_line/compare_speed_calc_line.h"
#include "src/research_tests/regex_test/regex.hpp"
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <regex>
#include <thread>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: topk_words [FILES...] -minLen N\n";
    return EXIT_FAILURE;
  }

  // =========== Parce arguments ===========
  size_t min_len = 1;
  bool use_filter = false;
  std::vector<std::string> list_files;
  for (int i = 1; i < argc; i++) {
    if (std::filesystem::exists(argv[i])) {
      list_files.emplace_back(argv[i]);
    }
    if (std::string(argv[i]) == "-minLen") {
      try {
        if (i + 1 < argc) {
          min_len = std::stoi(argv[i + 1]);
        } else {
          throw std::runtime_error("requires some value");
        }
      } catch (std::exception &ex) {
        std::cerr << ex.what() << '\n';
        std::cerr << "Wrong usage! The argument '-minLen' requires some value!"
                  << '\n';
      }
    }
    if (std::string(argv[i]) == "-useFilter") {
      use_filter = true;
    }
  }

  if (list_files.empty()) {
    std::cerr << "Wrong usage! The files weren't found!" << '\n';
    return EXIT_FAILURE;
  }

  std::cout << "-minLen: " << min_len << " \n";
  std::cout << "-useFilter: " << use_filter << " \n";
  std::cout << "The following files were found: \n";
  for (auto &file : list_files) {
    std::cout << file << "\n";
  }

  // =========== Research_tests ===========
  //  regex_test();
  //  compare_speed_calc_line(list_files[0]);

  size_t n_threads = std::thread::hardware_concurrency();

  // =========== Tests read_file_common_map ===========
  std::cout << "========== Start read_file_common_map ========" << "\n";
  std::cout << "========== " << 1 << " threads" << "\n";
  read_file_common_map(list_files, min_len, use_filter, 1);

  std::cout << "========== Start read_file_common_map ========" << "\n";
  std::cout << "========== " << n_threads << " threads" << "\n";
  read_file_common_map(list_files, min_len, use_filter, n_threads);

  // =========== Tests read_file_local_map ===========
  std::cout << "========== Start read_file_local_map ========" << "\n";
  std::cout << "========== " << 1 << " threads" << "\n";
  read_file_local_map(list_files, min_len, use_filter, 1);

  std::cout << "========== Start read_file_local_map ========" << "\n";
  std::cout << "========== " << n_threads << " threads" << "\n";
  read_file_local_map(list_files, min_len, use_filter, n_threads);

  // =========== Tests read_vector_common_map ===========
  std::cout << "========== Start read_vector_common_map ========" << "\n";
  std::cout << "========== " << 1 << " threads" << "\n";
  read_vector_common_map(list_files, min_len, use_filter, 1);

  std::cout << "========== Start read_vector_common_map ========" << "\n";
  std::cout << "========== " << n_threads << " threads" << "\n";
  read_vector_common_map(list_files, min_len, use_filter, n_threads);

  // =========== Tests read_vector_local_map ===========
  std::cout << "========== Start read_vector_local_map ========" << "\n";
  std::cout << "========== " << 1 << " threads" << "\n";
  read_vector_local_map(list_files, min_len, use_filter, 1);

  std::cout << "========== Start read_vector_local_map ========" << "\n";
  std::cout << "========== " << n_threads << " threads" << "\n";
  read_vector_local_map(list_files, min_len, use_filter, n_threads);
}
