#include "tests/tests.h"

namespace Test {

TEST_F(GRAPH, NON_ORIENTED_GRAPH_5X5) {
  TestGraph(File::kNonOrientedMatrix5x5, File::kNonOrientedGraph5x5);
}

TEST_F(GRAPH, NON_ORIENTED_WEIGHTED_GRAPH_5X5) {
  TestGraph(File::kNonOrientedWeightedMatrix5x5,
            File::kNonOrientedWeightedGraph5x5);
}

TEST_F(GRAPH, NON_ORIENTED_GRAPH_10X10) {
  TestGraph(File::kNonOrientedMatrix10x10, File::kNonOrientedGraph10x10);
}

TEST_F(GRAPH, NON_ORIENTED_WEIGHTED_GRAPH_10X10) {
  TestGraph(File::kNonOrientedWeightedMatrix10x10,
            File::kNonOrientedWeightedGraph10x10);
}

TEST_F(GRAPH, ORIENTED_GRAPH_5X5) {
  TestGraph(File::kOrientedMatrix5x5, File::kOrientedGraph5x5);
}

TEST_F(GRAPH, ORIENTED_WEIGHTED_GRAPH_5X5) {
  TestGraph(File::kOrientedWeightedMatrix5x5, File::kOrientedWeightedGraph5x5);
}

TEST_F(GRAPH, ORIENTED_GRAPH_10X10) {
  TestGraph(File::kOrientedMatrix10x10, File::kOrientedGraph10x10);
}

TEST_F(GRAPH, ORIENTED_WEIGHTED_GRAPH_10X10) {
  TestGraph(File::kOrientedWeightedMatrix10x10,
            File::kOrientedWeightedGraph10x10);
}

TEST_F(GRAPH, INVALID_SIZE) {
  EXPECT_ANY_THROW(graph.LoadGraphFromFile(File::kInvalidMatrixFormat1));
}

TEST_F(GRAPH, INVALID_COLS1) {
  EXPECT_ANY_THROW(graph.LoadGraphFromFile(File::kInvalidMatrixFormat2));
}

TEST_F(GRAPH, INVALID_COLS2) {
  EXPECT_ANY_THROW(graph.LoadGraphFromFile(File::kInvalidMatrixFormat4));
}

TEST_F(GRAPH, INVALID_ROWS1) {
  EXPECT_ANY_THROW(graph.LoadGraphFromFile(File::kInvalidMatrixFormat3));
}

TEST_F(GRAPH, INVALID_ROWS2) {
  EXPECT_ANY_THROW(graph.LoadGraphFromFile(File::kInvalidMatrixFormat5));
}

TEST_F(GRAPH, EMPTY_FILE) {
  EXPECT_ANY_THROW(graph.LoadGraphFromFile(File::kEmptyFile));
}

TEST_F(GRAPH, GRAPH_WITHOUT_MATRIX) {
  EXPECT_ANY_THROW(graph.ExportGraphToDot(File::kGeneratedGraph));
}

TEST_F(GRAPH, INCORRECT_PATH_LOAD) {
  EXPECT_ANY_THROW(
      graph.LoadGraphFromFile("///hasfhh///sddgash//adsfhaddfhaddfhadfha//"));
}

TEST_F(GRAPH, INCORRECT_PATH_EXPORT) {
  graph.LoadGraphFromFile(File::kOrientedMatrix10x10);
  EXPECT_ANY_THROW(
      graph.ExportGraphToDot("///hasfhh///sddgash//adsfhaddfhaddfhadfha//"));
}

}  // namespace Test
