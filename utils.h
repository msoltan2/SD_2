#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <future>
#include <vector>
#include <iostream>
#include <chrono>

using SortFunc = void(*)(std::vector<long long>&, long long, long long);

struct Test {
    int numOp;

    std::vector <std::pair <int, int> > ops;
};

struct Result {
    std::string name;
    long long durationMs;
};

std::string formatNumber(long long number) {
  std::ostringstream oss;
  if (number >= 1'000'000'000'000) {
    oss << std::fixed << std::setprecision(1) << (number / 1'000'000'000'000.0) << "T";
  }
  else if (number >= 1'000'000'000) {
      oss << std::fixed << std::setprecision(1) << (number / 1'000'000'000.0) << "B";
  } else if (number >= 1'000'000) {
      oss << std::fixed << std::setprecision(1) << (number / 1'000'000.0) << "M";
  } else if (number >= 1'000) {
      oss << std::fixed << std::setprecision(1) << (number / 1'000.0) << "K";
  } else {
      oss << number;
  }

  std::string result = oss.str();

  if (result.find(".0") != std::string::npos)
      result.erase(result.find(".0"), 2);

  return result;
}