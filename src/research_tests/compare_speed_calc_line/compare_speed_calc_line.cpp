#include "compare_speed_calc_line.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>

void compare_speed_calc_line(const std::string &fileName) {
  std::ifstream input{fileName};
  if (!input.is_open()) {
    throw std::runtime_error(std::string("Failed to open file ") + fileName);
  }

  std::cout << "========== Start compare_speed_calc_line ======== " << '\n';

  //============== 1 ==============
  auto start = std::chrono::high_resolution_clock::now();
  FILE *file = fopen(fileName.data(), "r");
  char ch;
  int numLines = 0;

  while ((ch = getc(file)) != EOF) {
    if (ch == '\n')
      numLines++;
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed_ms =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
  std::cout << "numLines " << numLines << '\n';

  //============== 2 ==============
  input.clear();
  input.seekg(0);
  start = std::chrono::high_resolution_clock::now();
  numLines = 0;
  std::string unused;
  while (std::getline(input, unused))
    ++numLines;

  //    char buf[256];
  //    while (input.getline(buf, 256))
  //      numLines++;

  end = std::chrono::high_resolution_clock::now();
  elapsed_ms =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
  std::cout << "numLines " << numLines << '\n';

  //============== 3 ==============
  input.clear();
  input.seekg(0);
  start = std::chrono::high_resolution_clock::now();
  numLines = std::count(std::istreambuf_iterator<char>(input),
                        std::istreambuf_iterator<char>(), '\n');
  if (input.tellg() != 0) {
    input.unget();
    if (input.get() != '\n') {
      ++numLines;
    }
  }
  end = std::chrono::high_resolution_clock::now();
  elapsed_ms =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
  std::cout << "numLines " << numLines << '\n';
}