#include <random>
#include <utility>

#include "algorithms/s21_graph_algorithms.h"

namespace s21 {
GraphAlgorithms::TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
    Graph& graph) {
  if (!graph.IsLoaded()) throw std::runtime_error("Graph not loaded");
  if (!graph.IsComplete()) throw std::runtime_error("Not a complete graph");
  ACO aco(graph);
  return aco.Solve();
}

GraphAlgorithms::tour_t GraphAlgorithms::ACO::ConstructTour() {
  tour_t tour;
  std::vector<bool> visited(graph_.GetSize(), false);
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<size_type> dist(0, graph_.GetSize() - 1);
  std::uniform_real_distribution<double> real_dist(0.0, 1.0);
  auto start_city = dist(gen);

  tour.push_back(start_city);
  visited[start_city] = true;

  for (size_type step = 1; step < graph_.GetSize(); ++step) {
    auto current_city = tour.back();
    double total_probability = 0.0;
    std::vector<double> probabilities(graph_.GetSize(), 0.0);

    for (size_type next_city = 0; next_city < graph_.GetSize(); ++next_city) {
      if (!visited[next_city]) {
        auto pheromone = pheromone_mx_[current_city][next_city];
        auto distance = graph_.GetWeight(current_city, next_city);
        probabilities[next_city] =
            pow(pheromone, alpha) * pow(1.0 / double(distance), beta);
        total_probability += probabilities[next_city];
      }
    }

    auto random_probability = real_dist(gen);
    double cumulative_probability = 0.0;
    for (size_type next_city = 0; next_city < graph_.GetSize(); ++next_city) {
      if (!visited[next_city]) {
        cumulative_probability += probabilities[next_city] / total_probability;
        if (random_probability <= cumulative_probability) {
          tour.push_back(next_city);
          visited[next_city] = true;
          break;
        }
      }
    }
  }

  return tour;
}

void GraphAlgorithms::ACO::UpdatePheromone() {
  for (size_type i = 0; i < graph_.GetSize(); ++i) {
    for (size_type j = 0; j < graph_.GetSize(); ++j) {
      pheromone_mx_[i][j] *= (1.0 - evaporation_rate);
    }
  }

  for (size_type ant = 0; ant < number_of_ants; ++ant) {
    auto tour = ConstructTour();
    auto tourDistance = double(CalculateTotalDistance(tour));

    for (size_type i = 0; i < graph_.GetSize() - 1; ++i) {
      auto city1 = tour[i];
      auto city2 = tour[i + 1];
      pheromone_mx_[city1][city2] += (1.0 / tourDistance);
    }
    auto lastCity = tour[graph_.GetSize() - 1];
    auto firstCity = tour[0];
    pheromone_mx_[lastCity][firstCity] += (1.0 / tourDistance);
  }
}

GraphAlgorithms::size_type GraphAlgorithms::ACO::CalculateTotalDistance(
    const tour_t& tour) {
  size_type totalDistance = 0.0;
  for (size_type i = 0; i < graph_.GetSize() - 1; ++i) {
    auto city1 = tour[i];
    auto city2 = tour[i + 1];
    totalDistance += graph_.GetWeight(city1, city2);
  }
  auto lastCity = tour[graph_.GetSize() - 1];
  auto firstCity = tour[0];
  totalDistance += graph_.GetWeight(lastCity, firstCity);
  return totalDistance;
}
GraphAlgorithms::ACO::ACO(Graph graph, GraphAlgorithms::size_type num_of_ants,
                          GraphAlgorithms::size_type num_of_iterations)
    : graph_(std::move(graph)),
      number_of_ants(num_of_ants),
      max_iterations(num_of_iterations) {}
GraphAlgorithms::TsmResult GraphAlgorithms::ACO::Solve() {
  tour_t best_tour;
  size_type best_tour_distance = size_type_max;
  pheromone_mx_ = Matrix<double>{graph_.GetSize(), 1.0};

  for (size_type iteration = 0; iteration < max_iterations; ++iteration) {
    UpdatePheromone();
    auto tour = ConstructTour();
    auto tour_distance = CalculateTotalDistance(tour);

    if (tour_distance < best_tour_distance) {
      best_tour = tour;
      best_tour_distance = tour_distance;
    }
  }
  for (auto& elm : best_tour) {
    ++elm;
  }
  best_tour.push_back(best_tour[0]);
  return {best_tour, double(best_tour_distance)};
}
}  // namespace s21
