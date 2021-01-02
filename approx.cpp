#include "approx.h"

std::vector<std::vector<int>> Approx::GetApproximation() {

  bool flag = true; //// флаг проверки условий
  int counter = 0;
  int max_number = 1 << (vertex_count_ * (vertex_count_ - 1) / 2); //// количество всех возможных вариантов ребер
  while (flag) {
    auto C = GenerateImprovement(counter);
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

  return current_ans_;
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

std::vector<std::vector<int>> Approx::GenerateImprovement(int& number) {
  //// check if power less than 21 4L

  return std::vector<std::vector<int>>();
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
  int cycle_vertexes_count = 0;
  used_.clear();
  used_.resize(vertex_count_, 0);
  for (int i = 0; i < vertex_count_; ++i) {
    if (!used_[i]) {
      int counter = 0;
      int result = dfs(i, counter, -1, C);
      if (!result) { //// result.first == 0 means that path was found
        ++paths_count;
      } else {
        cycle_vertexes_count += counter;
      }
    }
  }

  if (paths_count < current_path_count_
      || (paths_count == current_path_count_ && cycle_vertexes_count < current_cycle_vertex_count_)) {
    current_path_count_ = paths_count;
    current_cycle_vertex_count_ = cycle_vertexes_count;
    return true;
  }
  return false;
}

int Approx::dfs(int vertex, int& count, int pred, const std::vector<std::vector<int>> &C) {
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
