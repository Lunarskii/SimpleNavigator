#include "tests/tests.h"

namespace Test {

TEST_F(GRAPH_ALGS, GREEDY_TSP_NON_ORIENTED_WEIGHTED_COMPLETE_GRAPH) {
  graph.LoadGraphFromFile(File::kNonOrientedWeightedMatrix5x5);
  GraphAlgorithms::TsmResult tsp = algs.GreedyTSP(graph);
  EXPECT_TRUE(IsUnique(tsp.vertices));
  EXPECT_EQ(CalculateTheRouteDistance(tsp.vertices), tsp.distance);
}

TEST_F(GRAPH_ALGS, GREEDY_TSP_EMPTY_GRAPH) {
  EXPECT_ANY_THROW(algs.GreedyTSP(graph));
}

TEST_F(GRAPH_ALGS, GREEDY_TSP_NON_COMPLETE_GRAPH) {
  graph.LoadGraphFromFile(File::kNonOrientedWeightedMatrix10x10);
  EXPECT_ANY_THROW(algs.GreedyTSP(graph));
}

TEST_F(GRAPH_ALGS, ANT_TSP_NON_ORIENTED_WEIGHTED_COMPLETE_GRAPH) {
  graph.LoadGraphFromFile(File::kNonOrientedWeightedMatrix5x5);
  GraphAlgorithms::TsmResult tsp = algs.SolveTravelingSalesmanProblem(graph);
  EXPECT_TRUE(IsUnique(tsp.vertices));
  EXPECT_EQ(CalculateTheRouteDistance(tsp.vertices), tsp.distance);
}

TEST_F(GRAPH_ALGS, ANT_TSP_EMPTY_GRAPH) {
  EXPECT_ANY_THROW(algs.SolveTravelingSalesmanProblem(graph));
}

TEST_F(GRAPH_ALGS, ANT_TSP_NON_COMPLETE_GRAPH) {
  graph.LoadGraphFromFile(File::kNonOrientedWeightedMatrix10x10);
  EXPECT_ANY_THROW(algs.SolveTravelingSalesmanProblem(graph));
}

TEST_F(GRAPH_ALGS, INSERTION_TSP_NON_ORIENTED_WEIGHTED_COMPLETE_GRAPH) {
  graph.LoadGraphFromFile(File::kNonOrientedWeightedMatrix5x5);
  GraphAlgorithms::TsmResult tsp = algs.SolveTspWithInsertion(graph);
  EXPECT_TRUE(IsUnique(tsp.vertices));
  EXPECT_EQ(CalculateTheRouteDistance(tsp.vertices), tsp.distance);
}

TEST_F(GRAPH_ALGS, INSERTION_TSP_EMPTY_GRAPH) {
  EXPECT_ANY_THROW(algs.SolveTspWithInsertion(graph));
}

TEST_F(GRAPH_ALGS, INSERTION_TSP_NON_COMPLETE_GRAPH) {
  graph.LoadGraphFromFile(File::kNonOrientedWeightedMatrix10x10);
  EXPECT_ANY_THROW(algs.SolveTspWithInsertion(graph));
}

}  // namespace Test
