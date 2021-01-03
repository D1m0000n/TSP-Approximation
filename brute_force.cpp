#include "brute_force.h"
#include <iostream>

std::vector<std::vector<int>> BruteForce::GetAnswer() {
  FindMinCycle(0, std::vector<int>(1, 0));

  std::cout << "Brute force vertex order: ";
  for (int i = 0; i < vertex_count_; ++i) {
    std::cout << min_vertex_order[i] << " ";
  }
  std::cout << "\n";

  std::vector<std::vector<int>> result(vertex_count_, std::vector<int>(vertex_count_, 0));

  for (int i = 1; i < vertex_count_; ++i) {
    result[min_vertex_order[i - 1]][min_vertex_order[i]] = 1;
    result[min_vertex_order[i]][min_vertex_order[i - 1]] = 1;
  }
  result[0][min_vertex_order.back()] = 1;
  result[min_vertex_order.back()][0] = 1;


  return result;
}

void BruteForce::FindMinCycle(int current_value, std::vector<int> vertex_oreder) {
  if (vertex_oreder.size() == 6) {
    current_value += graph_[vertex_oreder[0]][vertex_oreder.back()] == 1 ? 1 : 2;
    if (current_value < min_value_) {
      min_value_ = current_value;
      min_vertex_order = vertex_oreder;
    }
    return;
  }

  for (int i = 0; i < vertex_count_; ++i) {
    if (std::find(vertex_oreder.begin(), vertex_oreder.end(), i) == vertex_oreder.end()) {
      int add = graph_[vertex_oreder.back()][i] == 1 ? 1 : 2;
      std::vector<int> tmp_order = vertex_oreder;
      tmp_order.push_back(i);
      FindMinCycle(current_value + add, tmp_order);
    }
  }
}
