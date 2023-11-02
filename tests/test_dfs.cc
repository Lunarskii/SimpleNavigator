#include "tests/tests.h"

namespace Test {

TEST_F(GRAPH_ALGS, DFS_NON_ORIENTED_5X5) {
  graph.LoadGraphFromFile(File::kNonOrientedMatrix5x5);
  std::vector<size_type> v1 = algs.DepthFirstSearch(graph, 1);
  std::vector<size_type> v2 = {1, 5, 4, 3, 2};

  EXPECT_TRUE(v1 == v2);
}

TEST_F(GRAPH_ALGS, DFS_NON_ORIENTED_10x10) {
  graph.LoadGraphFromFile(File::kNonOrientedMatrix10x10);
  std::vector<size_type> v1 = algs.DepthFirstSearch(graph, 1);
  std::vector<size_type> v2 = {1, 3, 4, 5, 7, 9, 10, 8, 6, 2};

  EXPECT_TRUE(v1 == v2);
}

TEST_F(GRAPH_ALGS, DFS_NON_ORIENTED_WEIGHTED_5X5) {
  graph.LoadGraphFromFile(File::kNonOrientedWeightedMatrix5x5);
  std::vector<size_type> v1 = algs.DepthFirstSearch(graph, 1);
  std::vector<size_type> v2 = {1, 5, 4, 3, 2};

  EXPECT_TRUE(v1 == v2);
}

TEST_F(GRAPH_ALGS, DFS_NON_ORIENTED_WEIGHTED_10X10) {
  graph.LoadGraphFromFile(File::kNonOrientedWeightedMatrix10x10);
  std::vector<size_type> v1 = algs.DepthFirstSearch(graph, 1);
  std::vector<size_type> v2 = {1, 4, 5, 7, 9, 10, 8, 6, 3, 2};

  EXPECT_TRUE(v1 == v2);
}

TEST_F(GRAPH_ALGS, DFS_ORIENTED_5X5) {
  graph.LoadGraphFromFile(File::kOrientedMatrix5x5);
  std::vector<size_type> v1 = algs.DepthFirstSearch(graph, 1);
  std::vector<size_type> v2 = {1, 2, 3, 4, 5};

  EXPECT_TRUE(v1 == v2);
}

TEST_F(GRAPH_ALGS, DFS_ORIENTED_10X10) {
  graph.LoadGraphFromFile(File::kOrientedMatrix10x10);
  std::vector<size_type> v1 = algs.DepthFirstSearch(graph, 1);
  std::vector<size_type> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_TRUE(v1 == v2);
}

TEST_F(GRAPH_ALGS, DFS_ORIENTED_WEIGHTED_5X5) {
  graph.LoadGraphFromFile(File::kOrientedWeightedMatrix5x5);
  std::vector<size_type> v1 = algs.DepthFirstSearch(graph, 1);
  std::vector<size_type> v2 = {1, 2, 3, 4, 5};

  EXPECT_TRUE(v1 == v2);
}

TEST_F(GRAPH_ALGS, DFS_ORIENTED_WEIGHTED_10X10) {
  graph.LoadGraphFromFile(File::kOrientedWeightedMatrix10x10);
  std::vector<size_type> v1 = algs.DepthFirstSearch(graph, 1);
  std::vector<size_type> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_TRUE(v1 == v2);
}

TEST_F(GRAPH_ALGS, DFS_INVALID_VERTEX) {
  graph.LoadGraphFromFile(File::kOrientedWeightedMatrix10x10);
  EXPECT_ANY_THROW(algs.DepthFirstSearch(graph, 0));
}

TEST_F(GRAPH_ALGS, DFS_EMPTY_GRAPH) {
  EXPECT_ANY_THROW(algs.DepthFirstSearch(graph, 1));
}

}  // namespace Test