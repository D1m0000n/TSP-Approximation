#include <iostream>
#include <vector>
#include <random>

int main() {
  std::random_device dev;
  std::mt19937 rng(dev());
  int vertex_count = 6;
  int max_number = 1 << (vertex_count * (vertex_count - 1) / 2);
  std::uniform_int_distribution<std::mt19937::result_type> distr(0, max_number - 1);

  int seed = distr(rng);
  std::vector<std::vector<int>> graph(vertex_count, std::vector<int>(vertex_count, 0));
  for (int i = 0; i < vertex_count; ++i) {
    for (int j = i + 1; j < vertex_count; ++j) {
      graph[i][j] = seed % 2;
      graph[j][i] = seed % 2;
      seed /= 2;
    }
  }

  std::cout << vertex_count << "\n";
  for (int i = 0; i < vertex_count; ++i) {
    for (int j = 0; j < vertex_count; ++j) {
      std::cout << graph[i][j] << " ";
    }
    std::cout << "\n";
  }
}