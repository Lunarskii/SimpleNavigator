//
// Created by ruslan on 06.10.23.
//

#include "algorithms/s21_graph_algorithms.h"
#include "graph/s21_graph.h"
void PrintVector(const std::vector<s21::GraphAlgorithms::size_type>& vr);
int getChoice();
void PrintComparison(
    const std::vector<std::pair<std::string, std::chrono::microseconds>>& vr,
    int N);
bool ProcessMenu();

int main() {
  while (ProcessMenu()) {
  }

  return 0;
}

void PrintComparison(
    const std::vector<std::pair<std::string, std::chrono::microseconds>>& vr,
    int N) {
  std::cout << "For " << N << " iterations:\n";
  for (const auto& [name, duration] : vr) {
    std::cout << "Alg name: " << name << " \tTime: " << duration.count()
              << " microseconds\n";
  }
}
bool ProcessMenu() {
  static s21::Graph graph;
  static s21::GraphAlgorithms algs;
  unsigned chooser = getChoice();
  std::string filename;

  try {
    switch (chooser) {
      case 1:
        std::cout << "Enter path and filename\n";
        std::cin >> filename;
        graph.LoadGraphFromFile(filename);
        graph.GetAdjacencyMatrix().PrintFull();
        break;
      case 2: {
        std::cout << "Enter start vertex\n";
        int start;
        while (!(std::cin >> start))
          ;
        auto result = algs.BreadthFirstSearch(graph, start);
        PrintVector(result);
      } break;
      case 3: {
        std::cout << "Enter start vertex\n";
        int start;
        while (!(std::cin >> start))
          ;
        auto result = algs.DepthFirstSearch(graph, start);
        PrintVector(result);
      } break;
      case 4: {
        int vx1, vx2;
        std::cout << "Enter start and end vertices\n";
        while (!(std::cin >> vx1 >> vx2))
          ;
        auto result = algs.GetShortestPathBetweenVertices(graph, vx1, vx2);
        std::cout << "Distance is " << result << "\n";
      } break;
      case 5: {
        auto result = algs.GetShortestPathsBetweenAllVertices(graph);
        result.PrintFull();
      } break;
      case 6: {
        auto result = algs.GetLeastSpanningTree(graph);
        result.PrintFull();
      } break;
      case 7: {
        auto result =
            s21::GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
        result.PrintTour();
      } break;
      case 8: {
        std::cout << "Enter number of iterations\n";
        int iterations;
        while (!(std::cin >> iterations))
          ;
        auto result = algs.CompareAlgs(iterations, graph);
        PrintComparison(result, iterations);
      } break;
      case 9:
        std::cout << "Exiting...\n";
        return false;
      default:
        std::cout << "try again...\n";
    }
  } catch (std::exception& e) {
    std::cout << e.what() << "\n";
  }
  return true;
}
int getChoice() {
  int chooser = 0;
  std::cout
      << "1. loading the original graph from a file\n"
         "2. graph traversal in breadth\n"
         "3. graph traversal in depth\n"
         "4. searching for the shortest path between any two vertices\n"
         "5. searching for the shortest paths between all pairs of vertices in "
         "the graph\n"
         "6. searching for the minimal spanning tree in the graph\n"
         "7. solving the salesman problem\n"
         "8. comparison of methods for solving the traveling salesman problem\n"
         "9. exit\n";
  if (!(std::cin >> chooser)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  return chooser;
}

void PrintVector(const std::vector<s21::GraphAlgorithms::size_type>& vr) {
  for (const auto& elm : vr) {
    std::cout << elm << " ";
  }
  std::cout << "\n";
}