#pragma once

#include <vector>

class Approx {
 public:
  Approx(std::vector<std::vector<int>> start_graph, int vertex_count)
      : graph_(start_graph), vertex_count_(vertex_count) {}

  //// change function type
  std::vector<std::vector<int>> GetApproximation();
  std::vector<std::vector<int>> GenerateImprovement(int& number);
  void MakeXor(std::vector<std::vector<int>>& C);
  bool CheckImprovement(const std::vector<std::vector<int>> &C);
  bool CheckTwoMatching(const std::vector<std::vector<int>> &C);
  bool CheckPathsAndVertexes(const std::vector<std::vector<int>> &C);
  int dfs(int vertex, int& count, int pred, const std::vector<std::vector<int>> &C);

 private:
  std::vector<std::vector<int>> graph_;
  std::vector<std::vector<int>> current_ans_;
  int vertex_count_;
  const int INF = 1e9;
  int current_path_count_ = INF;
  int current_cycle_vertex_count_ = INF;
  std::vector <int> used_;
};