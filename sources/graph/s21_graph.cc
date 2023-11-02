#include "graph/s21_graph.h"

namespace s21 {

void Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream file(filename);

  if (file.is_open()) {
    adjacency_matrix.ReadFull(file);
    file.close();
    loaded_ = true;
  } else {
    throw std::runtime_error("The file cannot be opened");
  }
}

void Graph::ExportGraphToDot(const std::string& filename) const {
  if (!loaded_) {
    throw std::runtime_error("An empty graph cannot be exported");
  }

  std::ofstream file(filename);

  if (file.is_open()) {
    AdjacencyList adjacency_list = GetAdjacencyList();
    std::string separator;
    bool is_oriented = IsOriented();
    bool is_weighted = IsWeighted();

    if (is_oriented) {
      file << "digraph ";
      separator = " -> ";
    } else {
      file << "graph ";
      separator = " -- ";
    }
    file << std::filesystem::path(filename).stem().string() << " {\n";

    for (size_type i = 0; i < adjacency_list.size(); ++i) {
      for (auto& edge : adjacency_list[i]) {
        if (is_oriented || i < edge.first) {
          file << i + 1 << separator << edge.first + 1;
          if (is_weighted) {
            file << " [label=\"" << edge.second << "\"]";
          }
          file << ";" << std::endl;
        }
      }
    }

    file << "}"
         << "\n";
    file.close();
  } else {
    throw std::runtime_error("The file cannot be opened");
  }
}

bool Graph::IsComplete() const noexcept {
  for (size_type i = 0; i < adjacency_matrix.GetSize(); ++i) {
    for (size_type j = 0; j < adjacency_matrix.GetSize(); ++j) {
      if (adjacency_matrix[i][j] == size_type_max) {
        return false;
      }
    }
  }

  return true;
}

bool Graph::IsOriented() const noexcept {
  for (size_type i = 0; i < adjacency_matrix.GetSize(); ++i) {
    for (size_type j = i + 1; j < adjacency_matrix.GetSize(); ++j) {
      if (adjacency_matrix[i][j] != adjacency_matrix[j][i]) {
        return true;
      }
    }
  }

  return false;
}

bool Graph::IsWeighted() const noexcept {
  for (size_type i = 0; i < adjacency_matrix.GetSize(); ++i) {
    for (size_type j = 0; j < adjacency_matrix.GetSize(); ++j) {
      if (i != j && adjacency_matrix[i][j] > 1 &&
          adjacency_matrix[i][j] != size_type_max) {
        return true;
      }
    }
  }

  return false;
}

Graph::size_type Graph::GetWeight(size_type vertex_a,
                                  size_type vertex_b) const {
  return adjacency_matrix[vertex_a][vertex_b];
}

bool Graph::IsLoaded() const noexcept { return loaded_; }

Graph::AdjacencyMatrix Graph::GetAdjacencyMatrix() const noexcept {
  return adjacency_matrix;
}

Graph::AdjacencyList Graph::GetAdjacencyList() const {
  AdjacencyList adjacency_list(adjacency_matrix.GetSize());

  for (size_type i = 0; i < adjacency_matrix.GetSize(); ++i) {
    for (size_type j = 0; j < adjacency_matrix.GetSize(); ++j) {
      if (i != j && adjacency_matrix[i][j] != size_type_max) {
        adjacency_list[i].emplace_back(j, adjacency_matrix[i][j]);
      }
    }
  }

  return adjacency_list;
}

Graph::size_type Graph::GetSize() const noexcept {
  return adjacency_matrix.GetSize();
}

}  // namespace s21
