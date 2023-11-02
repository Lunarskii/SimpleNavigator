#ifndef A2_SIMPLENAVIGATOR_GRAPH_S21_GRAPH_H_
#define A2_SIMPLENAVIGATOR_GRAPH_S21_GRAPH_H_

#include <filesystem>
#include <fstream>
#include <limits>
#include <memory>

#include "matrix/matrix.h"

namespace s21 {

class Graph {
 public:
  using size_type = std::size_t;
  using AdjacencyMatrix = Matrix<size_type>;
  using Edge = std::pair<size_type, size_type>;
  using AdjacencyList = std::vector<std::vector<Edge>>;
  static constexpr size_type size_type_max =
      std::numeric_limits<size_type>::max();

  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename) const;
  // Can be exception in proxy [], but if so it breaks class invariant with
  // GetSize
  [[nodiscard]] bool IsComplete() const noexcept;
  [[nodiscard]] bool IsWeighted() const noexcept;
  [[nodiscard]] bool IsOriented() const noexcept;
  [[nodiscard]] bool IsLoaded() const noexcept;
  [[nodiscard]] AdjacencyMatrix GetAdjacencyMatrix() const noexcept;
  [[nodiscard]] AdjacencyList GetAdjacencyList() const;
  [[nodiscard]] size_type GetWeight(size_type vertex_a,
                                    size_type vertex_b) const;
  [[nodiscard]] size_type GetSize() const noexcept;

 private:
  AdjacencyMatrix adjacency_matrix;
  bool loaded_ = false;
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_GRAPH_S21_GRAPH_H_
