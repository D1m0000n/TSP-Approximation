#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>
#include "approx.h"
#include "brute_force.h"

const double EPS = 1e-9;

std::vector <std::vector<int>> graph; //// исходный граф

int GetSum(const std::vector <std::vector<int>>& result) {
  int sum = 0;
  int vertex_count = result.size();
  for (int i = 0; i < vertex_count; ++i) {
    for (int j = i + 1; j < vertex_count; ++j) {
      if (result[i][j]) {
        sum += (graph[i][j] == 1) ? 1 : 2;
      }
    }
  }
  return sum;
}

int main() {
  //// будем хранить граф в виде матрицы смежности, потому что тестировать на больших графах не планируется

  int vertex_count; //// количество вершин в графе
  std::cin >> vertex_count;
  graph.resize(vertex_count, std::vector<int>(vertex_count));

  std::cout << "Original graph\n";
  for (int i = 0; i < vertex_count; ++i) {
    for (int j = 0; j < vertex_count; ++j) {
      std::cin >> graph[i][j];
      std::cout << graph[i][j] << " ";
    }
    std::cout << "\n";
  }

  Approx approx = Approx(graph, vertex_count);
  auto approx_ans = approx.GetApproximation();
  int approx_sum = GetSum(approx_ans);
  std::cout << "Approximation result:\n";
  for (int i = 0; i < vertex_count; ++i) {
    for (int j = 0; j < vertex_count; ++j) {
      std::cout << approx_ans[i][j] << " ";
    }
    std::cout << "\n";
  }
  approx_sum += approx.CountConnectionValue();
  std::cout << "Approx sum: " << approx_sum << "\n";

  BruteForce brute_force = BruteForce(graph, vertex_count);
  auto brute_force_ans = brute_force.GetAnswer();
  int brute_force_sum = GetSum(brute_force_ans);
  std::cout << "Brute force result:\n";
  for (int i = 0; i < vertex_count; ++i) {
    for (int j = 0; j < vertex_count; ++j) {
      std::cout << brute_force_ans[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "Brute force sum: " << brute_force_sum << "\n";

  double ap_ans = static_cast<double>(approx_sum);
  double bf_ans = static_cast<double>(brute_force_sum);
  if (ap_ans < bf_ans * 8 / 7) {
    std::cout << "Correct result!!!\n";
  } else {
    std::cout << "Something went wrong =(\n";
  }
}
