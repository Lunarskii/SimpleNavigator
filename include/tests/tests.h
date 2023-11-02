#ifndef A2_SIMPLENAVIGATOR_V1_0_1_TESTS_H
#define A2_SIMPLENAVIGATOR_V1_0_1_TESTS_H

#include <gtest/gtest.h>

#include <unordered_set>

#include "../algorithms/s21_graph_algorithms.h"
#include "../graph/s21_graph.h"
#include "files.h"

namespace Test {
using namespace s21;
using AdjacencyMatrix = Graph::AdjacencyMatrix;
using size_type = Graph::size_type;
// namespace Test

class GRAPH_ALGS : public ::testing::Test {
 protected:
  void SetUp() override {}

  void TearDown() override {}

  bool IsUnique(std::vector<size_type> vector);
  size_type CalculateTheRouteDistance(std::vector<size_type> vector);

  s21::Graph graph;
  s21::GraphAlgorithms algs;
};

class GRAPH : public ::testing::Test {
 protected:
  void SetUp() override {}

  void TearDown() override {}

  bool CompareGraphs(const std::string& f1, const std::string& f2);
  void TestGraph(const std::string& m, const std::string& g);

  s21::Graph graph;
};

}  // namespace Test

#endif  // A2_SIMPLENAVIGATOR_V1_0_1_TESTS_H
