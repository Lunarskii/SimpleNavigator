#include "matrix.h"

int main()
{
    s21::Matrix<int> matrix(2, 2, {1, 2, 3, 4});

    std::cout << matrix[0][1] << std::endl;
}