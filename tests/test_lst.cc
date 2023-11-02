#include "tests/tests.h"

namespace Test {

TEST_F(GRAPH_ALGS, LST_5X5) {
  graph.LoadGraphFromFile(File::kNonOrientedMatrix5x5);

  AdjacencyMatrix m1 = algs.GetLeastSpanningTree(graph);
  AdjacencyMatrix m2(5, {0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
                         1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0});
  EXPECT_TRUE(m1 == m2);
}

TEST_F(GRAPH_ALGS, LST_10X10) {
  graph.LoadGraphFromFile(File::kNonOrientedMatrix10x10);

  AdjacencyMatrix m1 = algs.GetLeastSpanningTree(graph);
  AdjacencyMatrix m2(
      10, {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
           1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
           0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
           0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0});
  EXPECT_TRUE(m1 == m2);
}

TEST_F(GRAPH_ALGS, LST_ORIENTED_GRAPH) {
  graph.LoadGraphFromFile(File::kOrientedMatrix10x10);
  EXPECT_ANY_THROW(algs.GetLeastSpanningTree(graph));
}

TEST_F(GRAPH_ALGS, LST_EMPTY_GRAPH) {
  EXPECT_ANY_THROW(algs.GetLeastSpanningTree(graph));
}

}  // namespace Test