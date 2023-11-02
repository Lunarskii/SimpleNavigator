#ifndef A2_SIMPLENAVIGATOR_V1_0_1_FILES_H
#define A2_SIMPLENAVIGATOR_V1_0_1_FILES_H

namespace Test {
struct File {
  static constexpr const char* kOrientedMatrix5x5 =
      "./tests/materials/oriented_matrix_5x5.txt";
  static constexpr const char* kOrientedMatrix10x10 =
      "./tests/materials/oriented_matrix_10x10.txt";
  static constexpr const char* kOrientedWeightedMatrix5x5 =
      "./tests/materials/oriented_weighted_matrix_5x5.txt";
  static constexpr const char* kOrientedWeightedMatrix10x10 =
      "./tests/materials/oriented_weighted_matrix_10x10.txt";
  static constexpr const char* kNonOrientedMatrix5x5 =
      "./tests/materials/non_oriented_matrix_5x5.txt";
  static constexpr const char* kNonOrientedMatrix10x10 =
      "./tests/materials/non_oriented_matrix_10x10.txt";
  static constexpr const char* kNonOrientedWeightedMatrix5x5 =
      "./tests/materials/non_oriented_weighted_matrix_5x5.txt";
  static constexpr const char* kNonOrientedWeightedMatrix10x10 =
      "./tests/materials/non_oriented_weighted_matrix_10x10.txt";
  static constexpr const char* kOrientedGraph5x5 =
      "./tests/materials/oriented_graph_5x5.dot";
  static constexpr const char* kOrientedGraph10x10 =
      "./tests/materials/oriented_graph_10x10.dot";
  static constexpr const char* kOrientedWeightedGraph5x5 =
      "./tests/materials/oriented_weighted_graph_5x5.dot";
  static constexpr const char* kOrientedWeightedGraph10x10 =
      "./tests/materials/oriented_weighted_graph_10x10.dot";
  static constexpr const char* kNonOrientedGraph5x5 =
      "./tests/materials/non_oriented_graph_5x5.dot";
  static constexpr const char* kNonOrientedGraph10x10 =
      "./tests/materials/non_oriented_graph_10x10.dot";
  static constexpr const char* kNonOrientedWeightedGraph5x5 =
      "./tests/materials/non_oriented_weighted_graph_5x5.dot";
  static constexpr const char* kNonOrientedWeightedGraph10x10 =
      "./tests/materials/non_oriented_weighted_graph_10x10.dot";
  static constexpr const char* kInvalidMatrixFormat1 =
      "./tests/materials/invalid_matrix_format1.txt";  // Написаны строки и
                                                       // столбцы, вместо
                                                       // размера
  static constexpr const char* kInvalidMatrixFormat2 =
      "./tests/materials/invalid_matrix_format2.txt";  // Превышен размер
                                                       // матрицы по столбцам
  static constexpr const char* kInvalidMatrixFormat3 =
      "./tests/materials/invalid_matrix_format3.txt";  // Превышен размер
                                                       // матрицы по строкам
  static constexpr const char* kInvalidMatrixFormat4 =
      "./tests/materials/invalid_matrix_format4.txt";  // Уменьшен размер
                                                       // матрицы по столбцам
  static constexpr const char* kInvalidMatrixFormat5 =
      "./tests/materials/invalid_matrix_format5.txt";  // Уменьшен размер
                                                       // матрицы по строкам
  static constexpr const char* kEmptyFile = "./tests/materials/empty_file.txt";
  static constexpr const char* kGeneratedGraph =
      "./tests/materials/generated_graph.dot";
};
}  // namespace Test

#endif  // A2_SIMPLENAVIGATOR_V1_0_1_FILES_H
