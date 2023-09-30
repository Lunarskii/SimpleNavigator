#include "matrix.h"
#include <fstream>

using namespace s21;



class Graph
{
public:
    void LoadGraphFromFile(std::string filename);
    void ExportGraphToDot(std::string filename);
    bool IsWeighted();
    std::pair<bool, std::size_t> IsOrientedPath(std::size_t first_point, std::size_t second_point);
    bool PathExists(std::size_t first_point, std::size_t second_point);

private:
    Matrix<unsigned int> adjacency;
};

