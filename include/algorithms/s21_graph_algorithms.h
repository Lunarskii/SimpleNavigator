#ifndef A2_SIMPLENAVIGATOR_V1_0_1_S21_GRAPH_ALGORITHMS_H
#define A2_SIMPLENAVIGATOR_V1_0_1_S21_GRAPH_ALGORITHMS_H

#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>
#include <vector>

#include "containers/queue/s21_queue.h"
#include "containers/stack/s21_stack.h"
#include "graph/s21_graph.h"
#include "matrix/matrix.h"

namespace s21 {

class GraphAlgorithms {
 private:
  class ACO;
  struct Edge;

 public:
  using size_type = Graph::size_type;
  using AdjacencyMatrix = Graph::AdjacencyMatrix;
  using AdjacencyList = Graph::AdjacencyList;
  using pq_t = std::priority_queue<std::pair<size_type, size_type>,
                                   std::vector<std::pair<size_type, size_type>>,
                                   std::greater<>>;
  using tour_t = std::vector<size_type>;
  static constexpr size_type size_type_max = Graph::size_type_max;

  struct TsmResult {
    tour_t vertices;
    double distance{};
    void PrintTour() {
      std::cout << "Tour: ";
      for (const auto& vx : vertices) {
        std::cout << vx << " ";
      }
      std::cout << "\ndistance: " << distance << std::endl;
    }
  };

  std::vector<std::pair<std::string, std::chrono::microseconds>> CompareAlgs(
      int N, Graph& graph);
  AdjacencyMatrix GetLeastSpanningTree(Graph& graph);
  std::vector<size_type> DepthFirstSearch(Graph& graph, int start_vertex);
  std::vector<size_type> BreadthFirstSearch(Graph& graph, int start_vertex);

  TsmResult GreedyTSP(Graph& graph);
  size_type GetShortestPathBetweenVertices(Graph& graph, int vertex1,
                                           int vertex2);

  Matrix<size_type> GetShortestPathsBetweenAllVertices(Graph& graph);
  static TsmResult SolveTravelingSalesmanProblem(Graph& graph);
  TsmResult SolveTspWithInsertion(Graph& graph);

 private:
  std::chrono::microseconds RunAlg(
      const std::function<TsmResult(Graph& graph)>& func, int n);
  std::pair<size_type, size_type> FindMinUnvisitedNeighbour(
      Graph& graph, std::vector<bool>& visited, size_type current_vertex) const;
  [[nodiscard]] pq_t FindUnvisitedNeighbours(
      size_type vertex1, const std::vector<size_type>& visited) const;
  void FindRoutesRecursively(std::vector<size_type> visited,
                             GraphAlgorithms::size_type* routes,
                             unsigned long weight,
                             unsigned long current_vx) const;
  void FindTheShortestRoutes(Matrix<GraphAlgorithms::size_type>& result) const;

 private:
  Graph graph_;
  size_type CalculateTotalDistance(tour_t& tour);
};

class GraphAlgorithms::ACO {
 public:
  explicit ACO(Graph graph, size_type num_of_ants = 10,
               size_type num_of_iterations = 100);
  TsmResult Solve();

 private:
  tour_t ConstructTour();
  void UpdatePheromone();
  size_type CalculateTotalDistance(const tour_t& tour);

 private:
  constexpr static double alpha = 1.0;  // Вес феромона
  constexpr static double beta = 2.0;   // Вес эвристики
  constexpr static double evaporation_rate =
      0.5;  // Скорость испарения феромона
 private:
  Graph graph_;
  size_type number_of_ants;
  size_type max_iterations;
  Matrix<double> pheromone_mx_;
};

struct GraphAlgorithms::Edge {
  Edge(const size_type& s, const size_type& d, const size_type& w)
      : src(s), dest(d), weight(w) {}

  bool operator<(const Edge& other) const { return weight < other.weight; }

  bool operator>(const Edge& other) const { return weight > other.weight; }

  size_type src;
  size_type dest;
  size_type weight;
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V1_0_1_S21_GRAPH_ALGORITHMS_H
