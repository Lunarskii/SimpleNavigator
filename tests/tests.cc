#include "../include/tests/tests.h"

namespace Test {

bool GRAPH::CompareGraphs(const std::string& f1, const std::string& f2) {
  std::ifstream file1(f1);
  std::ifstream file2(f2);
  std::string line1;
  std::string line2;

  if (file1.is_open() && file2.is_open()) {
    while (std::getline(file1, line1) && std::getline(file2, line2)) {
      EXPECT_EQ(line1, line2);
    }

    EXPECT_TRUE(file1.eof());
    EXPECT_TRUE(file2.eof());
  } else {
    return false;
  }

  return true;
}

void GRAPH::TestGraph(const std::string& m, const std::string& g) {
  graph.LoadGraphFromFile(m);
  graph.ExportGraphToDot(File::kGeneratedGraph);
  EXPECT_TRUE(CompareGraphs(File::kGeneratedGraph, g));
}

bool GRAPH_ALGS::IsUnique(const std::vector<size_type> vector) {
  std::unordered_set<size_type> unique;

  for (auto it = vector.begin(); it != --vector.end(); ++it) {
    if (unique.find(*it) != unique.end()) {
      return false;
    }
    unique.insert(*it);
  }

  return true;
}

size_type GRAPH_ALGS::CalculateTheRouteDistance(std::vector<size_type> vector) {
  AdjacencyMatrix adjacency_matrix = graph.GetAdjacencyMatrix();
  auto it = vector.begin();
  size_type vertex1 = *(it++) - 1;
  size_type vertex2 = 0;
  size_type distance = 0;

  for (; it != vector.end(); vertex1 = vertex2) {
    vertex2 = *(it++) - 1;
    distance += adjacency_matrix[vertex1][vertex2];
  }

  return distance;
}

}  // namespace Test