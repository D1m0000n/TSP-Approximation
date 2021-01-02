#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>
#include "approx.h"

std::vector <std::vector<int>> graph; //// исходный граф

int GetSum(const std::vector <std::vector<int>>& result) {
  int sum = 0;
  int vertex_count = result.size();
  for (int i = 0; i < vertex_count; ++i) {
    for (int j = 0; j < vertex_count; ++j) {
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

  for (int i = 0; i < vertex_count; ++i) {
    for (int j = 0; j < vertex_count; ++j) {
      std::cin >> graph[i][j];
    }
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
  std::cout << "Approx sum: " << approx_sum << "\n";
}
