#pragma once
#include <cstring>
#include <iostream>
#include <regex>
#include <string>

void regex_test() {

  std::string sInput = "Release привет: May@ 1, 2005 [eBook #8172]; - Most "
                       "recently updated: $Сентябрь 8, 2014 | à | “just "
                       "you’ve” “didn’t” “we’ve”";
  std::string sOutput = std::regex_replace(sInput, std::regex(R"([^A-Za-z ’])"),
                                           ""); // R"([^a-zA-Zа-яёА-ЯЁ ])"
  std::cout << sOutput << "\n";

  std::string filtered_word;
  std::transform(
      std::cbegin(sOutput), std::cend(sOutput),
      std::back_inserter(filtered_word), [](unsigned char ch) {
        return (std::string(1, ch) == "“" || std::string(1, ch) == "”") ? char()
                                                                        : ch;
      });

  std::cout << filtered_word << "\n";

  std::string text = "“you’ve”";
  auto it = std::cbegin(text);
  auto itEnd = std::cend(text);
  for (; it != itEnd; it++) {
    std::cout << *it << "\n";
  }
}