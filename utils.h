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

std::string formatTime(long long milliseconds) {
  std::ostringstream oss;

  if (milliseconds < 1000) {
      oss << milliseconds << " ms";
  } else {
      double seconds = milliseconds / 1000.0;
      oss << std::fixed << std::setprecision(2) << seconds << " s";
  }

  return oss.str();
}

auto runTask = [](int i,
                      Test& test,
                      const std::string& name,
                      auto func
                      ) -> Result {
    auto start = std::chrono::high_resolution_clock::now();

    try {
        func(test);
    } catch (...) {
        std::cerr << "Algorithm " << name << " has thrown\n";
        return { name, -1 };
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    return { name, duration };
};