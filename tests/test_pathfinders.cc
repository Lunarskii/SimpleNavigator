#include "tests/tests.h"

namespace Test {

TEST_F(GRAPH_ALGS, SHORTEST_PATH_BETWEEN_VERTICES) {
  graph.LoadGraphFromFile(File::kNonOrientedWeightedMatrix5x5);
  EXPECT_EQ(algs.GetShortestPathBetweenVertices(graph, 1, 3), 4);
}

TEST_F(GRAPH_ALGS, SHORTEST_PATH_BETWEEN_VERTICES_EMPTY_GRAPH) {
  EXPECT_ANY_THROW(algs.GetShortestPathBetweenVertices(graph, 1, 3));
}

TEST_F(GRAPH_ALGS, SHORTEST_PATH_BETWEEN_VERTICES_NON_EXISTENT_VERTICES1) {
  graph.LoadGraphFromFile(File::kNonOrientedWeightedMatrix5x5);
  EXPECT_ANY_THROW(algs.GetShortestPathBetweenVertices(graph, 0, 0));
}

TEST_F(GRAPH_ALGS, SHORTEST_PATH_BETWEEN_VERTICES_NON_EXISTENT_VERTICES2) {
  graph.LoadGraphFromFile(File::kNonOrientedWeightedMatrix5x5);
  EXPECT_ANY_THROW(algs.GetShortestPathBetweenVertices(graph, 10, 10));
}

TEST_F(GRAPH_ALGS, SHORTEST_PATH_BETWEEN_VERTICES_NO_WAY) {
  graph.LoadGraphFromFile(File::kOrientedWeightedMatrix5x5);
  EXPECT_ANY_THROW(algs.GetShortestPathBetweenVertices(graph, 5, 4));
}

TEST_F(GRAPH_ALGS, SHORTEST_PATH_BETWEEN_ALL_VERTICES) {
  graph.LoadGraphFromFile(File::kNonOrientedWeightedMatrix5x5);
  AdjacencyMatrix m1 = algs.GetShortestPathsBetweenAllVertices(graph);
  AdjacencyMatrix m2(5, {0, 5, 4, 7, 2, 5, 0, 1, 4, 3, 4, 1, 0,
                         3, 2, 7, 4, 3, 0, 5, 2, 3, 2, 5, 0});

  EXPECT_EQ(m1, m2);
}

TEST_F(GRAPH_ALGS, SHORTEST_PATH_BETWEEN_ALL_VERTICES_EMPTY_GRAPH) {
  EXPECT_ANY_THROW(algs.GetShortestPathsBetweenAllVertices(graph));
}

}  // namespace Test
