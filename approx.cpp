#include "approx.h"

std::vector<std::vector<int>> Approx::GetApproximation() {

  bool flag = true; //// флаг проверки условий
  int counter = 0;
  auto edges = GenerateEdgesList();
  int edges_count = edges.size();
  int max_number = 1 << edges_count; //// количество всех возможных вариантов ребер
  while (flag) {
    auto C = GenerateImprovement(counter, edges);
    MakeXor(C);
    bool improvement_result = CheckImprovement(C);
    if (improvement_result) {
      current_ans_ = C;
      counter = 0;
    } else {
      ++counter;
    }
    if (counter == max_number - 1) {
      flag = false;
    }
  }

  std::cout << "Final path count " << current_path_count_ << "\n";
  std::cout << "Final vertex in cycles count " << current_cycle_vertex_count_ << "\n";
  return current_ans_;
}

std::vector<std::pair<int, int>> Approx::GenerateEdgesList() {
  std::vector<std::pair<int, int>> edges;
  for (int i = 0; i < vertex_count_; ++i) {
    for (int j = i + 1; j < vertex_count_; ++j) {
      if (graph_[i][j]) {
        edges.emplace_back(i, j);
      }
    }
  }
  return edges;
}

bool Approx::CheckImprovement(const std::vector<std::vector<int>> &C) {
  if (!CheckTwoMatching(C)) {
    return false;
  }
  return CheckPathsAndVertexes(C);
}

void Approx::MakeXor(std::vector<std::vector<int>> &C) {
  for (int i = 0; i < vertex_count_; ++i) {
    for (int j = 0; j < vertex_count_; ++j) {
      C[i][j] ^= current_ans_[i][j];
    }
  }
}

std::vector<std::vector<int>> Approx::GenerateImprovement(int number, const std::vector<std::pair<int, int>> &edges) {
  std::vector<std::vector<int>> result(vertex_count_, std::vector<int>(vertex_count_, 0));
  if (edges.size() <= 21) {
    int ind = 0;
    while (number > 0) {
      if (number % 2) {
        result[edges[ind].first][edges[ind].second] = 1;
        result[edges[ind].second][edges[ind].first] = 1;
      }
      ++ind;
      number /= 2;
    }
    return result;
  } else {
    int ind = 0;
    int edges_count = 0;
    while (number > 0) {
      if (number % 2) {
        ++edges_count;
        result[edges[ind].first][edges[ind].second] = 1;
        result[edges[ind].second][edges[ind].first] = 1;
      }
      ++ind;
      number /= 2;
      if (edges_count > 21) {
        break;
      }
    }
    return result;
  }
}

bool Approx::CheckTwoMatching(const std::vector<std::vector<int>> &C) {
  for (int i = 0; i < vertex_count_; ++i) {
    int vertex_degree = 0;
    for (int j = 0; j < vertex_count_; ++j) {
      vertex_degree += C[i][j];
    }
    if (vertex_degree > 2) {
      return false;
    }
  }
  return true;
}

bool Approx::CheckPathsAndVertexes(const std::vector<std::vector<int>> &C) {
  int paths_count = 0;
  int cycle_count = 0;
  int cycle_vertexes_count = 0;
  used_.clear();
  used_.resize(vertex_count_, 0);
  for (int i = 0; i < vertex_count_; ++i) {
    if (!used_[i]) {
      int counter = 0;
      int result = dfs(i, counter, -1, C);
      if (!result) { //// result.first == 0 means that path was found
      } else {
        ++cycle_count;
        cycle_vertexes_count += counter;
      }
      ++paths_count;
    }
  }

  if (paths_count < current_path_count_
      || (paths_count == current_path_count_ && cycle_vertexes_count < current_cycle_vertex_count_)) {
    current_path_count_ = paths_count;
    current_cycle_vertex_count_ = cycle_vertexes_count;
    current_cycle_count_ = cycle_count;
    return true;
  }
  return false;
}

int Approx::dfs(int vertex, int &count, int pred, const std::vector<std::vector<int>> &C) {
  used_[vertex] = true;
  ++count;
  for (int i = 0; i < vertex_count_; ++i) {
    if (i == pred) {
      continue;
    }

    if (!used_[i] && C[vertex][i]) {
      return dfs(i, count, vertex, C);
    }

    if (used_[i] && C[vertex][i]) {
      return true;
    }
  }

  return false;
}

int Approx::CountConnectionValue() {
  //// current_path_count_ contains paths and cycles
  return 2 * current_path_count_ - current_cycle_count_;
}

