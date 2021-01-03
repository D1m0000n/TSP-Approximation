#pragma once

#include <vector>

class BruteForce {
 public:
  BruteForce(std::vector<std::vector<int>> start_graph, int vertex_count)
      : graph_(start_graph), vertex_count_(vertex_count) {
  }

  std::vector<std::vector<int>> GetAnswer();
  void FindMinCycle(int current_value, std::vector<int> vertex_oreder);

 private:
  std::vector<std::vector<int>> graph_;
  std::vector<int> min_vertex_order;
  int vertex_count_;
  const int INF = 1e9;
  int min_value_ = INF;
};
