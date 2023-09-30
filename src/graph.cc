#include "graph.h"
#include <iostream>

void Graph::LoadGraphFromFile(std::string filename)
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        unsigned int number_of_vertices = 0;

        file >> number_of_vertices;
        Matrix<unsigned int> matrix(number_of_vertices);

        for (auto& i : matrix.DataVector())
        {
            file >> i;
        }

        adjacency = matrix;
        file.close();
    }
}

void Graph::ExportGraphToDot(std::string filename)
{
    std::ofstream file(filename);

    if (file.is_open())
    {
        file << "graph graphname {" << "\n";

        for (int i = 0; i < adjacency.GetRows(); ++i)
        {
            for (int j = 0; j < adjacency.GetCols(); ++j)
            {
                if (i != j)
                {
                    if (PathExists(i, j))
                    {
                        std::pair<bool, std::size_t> path = IsOrientedPath(i, j);

                        file << "\t" << i;
                        if (path.first)
                        {
                            if (path.second == j)
                            {
                                file << " -> ";
                            }
                        }
                        else
                        {
                            file << " -- ";
                        }
                        file << j << ";" << "\n";
                    }
                }
            }
        }

        file << "}" << "\n";
        file.close();
    }
}

bool Graph::IsWeighted()
{
    for (int i = 0; i < adjacency.GetRows(); ++i)
    {
        for (int j = 0; j < adjacency.GetCols(); ++j)
        {
            if (i != j && adjacency[i][j] > 1)
            {
                return true;
            }
        }
    }

    return false;
}

std::pair<bool, std::size_t> Graph::IsOrientedPath(std::size_t first_point, std::size_t second_point)
{
    if (adjacency[first_point][second_point] != adjacency[second_point][first_point])
    {
        if (adjacency[first_point][second_point] == 0)
        {
            return { true, first_point };
        }
        else
        {
            return { true, second_point };
        }
    }

    return { false, 0 };
}

bool Graph::PathExists(std::size_t first_point, std::size_t second_point)
{
    return static_cast<bool>(adjacency[first_point][second_point]);
}
