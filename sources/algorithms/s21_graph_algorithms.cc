#include "algorithms/s21_graph_algorithms.h"

#include <random>

namespace s21 {

GraphAlgorithms::AdjacencyMatrix GraphAlgorithms::GetLeastSpanningTree(
    Graph& graph) {
  if (graph.GetSize() == 0) {
    throw std::runtime_error("Please load the graph");
  }
  if (graph.IsOriented()) {
    throw std::invalid_argument("Graph should be non-oriented");
  }

  AdjacencyList adjacency_list = graph.GetAdjacencyList();
  AdjacencyMatrix adjacency_matrix(adjacency_list.size());
  std::vector<bool> visited(adjacency_list.size(), false);
  std::priority_queue<Edge, std::vector<Edge>, std::greater<>> pq;

  visited[0] = true;
  for (auto& edge : adjacency_list[0]) {
    pq.emplace(0, edge.first, edge.second);
  }

  while (!pq.empty()) {
    auto [src, dest, weight] = pq.top();
    pq.pop();

    if (!visited[dest]) {
      adjacency_matrix[src][dest] = weight;
      adjacency_matrix[dest][src] = weight;
      visited[dest] = true;

      for (auto& edge : adjacency_list[dest]) {
        if (!visited[edge.first]) {
          pq.emplace(dest, edge.first, edge.second);
        }
      }
    }
  }

  return adjacency_matrix;
}

std::vector<GraphAlgorithms::size_type> GraphAlgorithms::DepthFirstSearch(
    Graph& graph, int start_vertex) {
  if (graph.GetSize() == 0) {
    throw std::runtime_error("Please load the graph");
  }
  if (start_vertex <= 0 ||
      static_cast<size_type>(start_vertex) > graph.GetSize()) {
    throw std::invalid_argument("The vertex does not exist");
  }

  AdjacencyList adjacency_list = graph.GetAdjacencyList();
  std::vector<size_type> visited_vertices;
  stack<size_type> s;

  --start_vertex;
  visited_vertices.push_back(start_vertex + 1);
  for (auto& edge : adjacency_list[start_vertex]) {
    s.push(edge.first);
  }

  while (!s.empty()) {
    if (std::find(visited_vertices.begin(), visited_vertices.end(),
                  s.top() + 1) == visited_vertices.end()) {
      size_type vertex = s.top();

      s.pop();
      visited_vertices.push_back(vertex + 1);
      for (auto& edge : adjacency_list[vertex]) {
        s.push(edge.first);
      }
    } else {
      s.pop();
    }
  }

  return visited_vertices;
}

std::vector<GraphAlgorithms::size_type> GraphAlgorithms::BreadthFirstSearch(
    Graph& graph, int start_vertex) {
  if (graph.GetSize() == 0) {
    throw std::runtime_error("Please load the graph");
  }
  if (start_vertex <= 0 ||
      static_cast<size_type>(start_vertex) > graph.GetSize()) {
    throw std::invalid_argument("The vertex does not exist");
  }

  AdjacencyList adjacency_list = graph.GetAdjacencyList();
  std::vector<size_type> visited_vertices;
  queue<size_type> q;

  --start_vertex;
  visited_vertices.push_back(start_vertex + 1);
  for (auto& edge : adjacency_list[start_vertex]) {
    q.push(edge.first);
  }

  while (!q.empty()) {
    if (std::find(visited_vertices.begin(), visited_vertices.end(),
                  q.front() + 1) == visited_vertices.end()) {
      size_type vertex = q.front();

      q.pop();
      visited_vertices.push_back(vertex + 1);
      for (auto& edge : adjacency_list[vertex]) {
        q.push(edge.first);
      }
    } else {
      q.pop();
    }
  }

  return visited_vertices;
}

GraphAlgorithms::TsmResult GraphAlgorithms::GreedyTSP(Graph& graph) {
  if (graph.GetSize() == 0) {
    throw std::runtime_error("Please load the graph");
  }
  if (!graph.IsComplete()) {
    throw std::runtime_error("Not a complete graph");
  }

  AdjacencyList adjacency_list = graph.GetAdjacencyList();
  std::vector<bool> visited(adjacency_list.size(), false);
  TsmResult tour{{}, 0};
  size_type current_vertex = 0;

  tour.vertices.push_back(current_vertex + 1);
  visited[current_vertex] = true;

  std::pair<size_type, size_type> path =
      FindMinUnvisitedNeighbour(graph, visited, current_vertex);
  while (path.first != size_type_max) {
    tour.vertices.push_back(path.first + 1);
    tour.distance += path.second;
    visited[path.first] = true;
    current_vertex = path.first;
    path = FindMinUnvisitedNeighbour(graph, visited, current_vertex);
  }

  tour.distance += graph.GetWeight(tour.vertices.back() - 1, 0);
  tour.vertices.push_back(1);

  return tour;
}

std::pair<GraphAlgorithms::size_type, GraphAlgorithms::size_type>
GraphAlgorithms::FindMinUnvisitedNeighbour(Graph& graph,
                                           std::vector<bool>& visited,
                                           size_type current_vertex) const {
  AdjacencyList adjacency_list = graph.GetAdjacencyList();
  size_type distance = size_type_max;
  size_type nearest_vertex = size_type_max;

  for (auto& edge : adjacency_list[current_vertex]) {
    if (!visited[edge.first] && edge.second < distance) {
      distance = edge.second;
      nearest_vertex = edge.first;
    }
  }

  return {nearest_vertex, distance};
}

GraphAlgorithms::size_type GraphAlgorithms::GetShortestPathBetweenVertices(
    s21::Graph& graph, int vertex1, int vertex2) {
  if (graph.GetSize() == 0) {
    throw std::runtime_error("Please load the graph");
  }
  if (vertex1 < 1 || vertex2 < 1 ||
      static_cast<size_type>(vertex1) > graph.GetSize() ||
      static_cast<size_type>(vertex2) > graph.GetSize())
    throw std::invalid_argument("The vertex does not exist");
  graph_ = graph;
  --vertex1;
  --vertex2;

  std::vector<size_type> visited;
  visited.push_back(vertex1);
  auto routes = new size_type[graph.GetSize()];
  std::fill_n(routes, graph_.GetSize(), size_type_max);
  FindRoutesRecursively(visited, routes, 0, vertex1);
  size_type result = routes[vertex2];
  delete[] routes;
  if (result == size_type_max) throw std::runtime_error("No way in this graph");
  return result;
}

void GraphAlgorithms::FindRoutesRecursively(std::vector<size_type> visited,
                                            GraphAlgorithms::size_type* routes,
                                            size_type weight,
                                            size_type current_vx) const {
  pq_t neighbours = FindUnvisitedNeighbours(current_vx, visited);
  while (!neighbours.empty()) {
    auto [neighbours_weight, neighbours_vertex] = neighbours.top();
    neighbours.pop();
    neighbours_weight += weight;
    if (routes[neighbours_vertex] > neighbours_weight)
      routes[neighbours_vertex] = neighbours_weight;
    visited.push_back(neighbours_vertex);
    FindRoutesRecursively(visited, routes, neighbours_weight,
                          neighbours_vertex);
  }
}

GraphAlgorithms::pq_t GraphAlgorithms::FindUnvisitedNeighbours(
    size_type vertex1, const std::vector<size_type>& visited) const {
  pq_t result;
  size_type weight;
  for (size_type i = 0; i < graph_.GetSize(); ++i) {
    if (!std::any_of(visited.begin(), visited.end(),
                     [&i](size_type vx) { return vx == i; }) &&
        (weight = graph_.GetWeight(vertex1, i)) != size_type_max) {
      result.emplace(weight, i);
    }
  }
  return result;
}

Matrix<GraphAlgorithms::size_type>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph& graph) {
  if (graph.GetSize() == 0) {
    throw std::runtime_error("Please load the graph");
  }
  graph_ = graph;
  Matrix<GraphAlgorithms::size_type> result = graph.GetAdjacencyMatrix();
  FindTheShortestRoutes(result);
  return result;
}

void GraphAlgorithms::FindTheShortestRoutes(
    Matrix<GraphAlgorithms::size_type>& result) const {
  for (size_type k = 0; k < graph_.GetSize(); ++k) {
    for (size_type i = 0; i < graph_.GetSize(); ++i) {
      for (size_type j = 0; j < graph_.GetSize(); ++j) {
        result[i][j] =
            std::min(result[i][j], result[i][k] >= size_type_max / 2 ||
                                           result[k][j] >= size_type_max / 2
                                       ? size_type_max
                                       : result[i][k] + result[k][j]);
      }
    }
  }
}

GraphAlgorithms::TsmResult GraphAlgorithms::SolveTspWithInsertion(
    Graph& graph) {
  if (graph.GetSize() == 0) {
    throw std::runtime_error("Please load the graph");
  }
  if (!graph.IsComplete()) throw std::runtime_error("Not a complete graph");
  graph_ = graph;
  size_type size = graph.GetSize();
  tour_t tour;
  tour.reserve(size);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<size_type> dist(0, size - 1);
  auto start_point = dist(gen);

  tour.push_back(start_point);
  std::vector<bool> visited(size, false);
  visited[start_point] = true;

  for (size_type i = 1; i < size; ++i) {
    size_type best_vertex, best_position;
    size_type best_cost = size_type_max;

    for (size_type j = 0; j < size; ++j) {
      if (!visited[j]) {
        for (size_type k = 0; k < tour.size(); ++k) {
          auto next = (k + 1) % tour.size();
          auto cost =
              graph_.GetWeight(tour[k], j) + graph_.GetWeight(j, tour[next]);

          if (cost < best_cost) {
            best_cost = cost;
            best_vertex = j;
            best_position = k;
          }
        }
      }
    }
    tour.insert(tour.begin() + tour_t::difference_type(best_position + 1),
                best_vertex);
    visited[best_vertex] = true;
  }
  tour.push_back(tour[0]);
  auto distance = CalculateTotalDistance(tour);
  return TsmResult{tour, double(distance)};
}

GraphAlgorithms::size_type GraphAlgorithms::CalculateTotalDistance(
    GraphAlgorithms::tour_t& tour) {
  size_type total = 0;
  for (size_type i = 0; i < tour.size() - 1; ++i) {
    total += graph_.GetWeight(tour[i], tour[i + 1]);
    ++tour[i];
  }
  ++tour.back();
  return total;
}

std::vector<std::pair<std::string, std::chrono::microseconds>>
GraphAlgorithms::CompareAlgs(int N, Graph& graph) {
  graph_ = graph;
  std::vector<std::pair<std::string, std::chrono::microseconds>> result;
  result.emplace_back("Ant", RunAlg(SolveTravelingSalesmanProblem, N));
  result.emplace_back(
      "Insertion",
      RunAlg(
          [this](Graph& graph) { return this->SolveTspWithInsertion(graph); },
          N));
  result.emplace_back(
      "Greedy",
      RunAlg([this](Graph& graph) { return this->GreedyTSP(graph); }, N));
  return result;
}

std::chrono::microseconds GraphAlgorithms::RunAlg(
    const std::function<TsmResult(Graph& graph)>& func, int n) {
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < n; ++i) {
    func(graph_);
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  return duration;
}

}  // namespace s21