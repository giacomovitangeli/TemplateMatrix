#include <iostream>
#include <memory>
#include "Matrix.h"

int main() {
    std::unique_ptr<Matrix<char>> m1(new Matrix<char>(2, 2));

    return 0;
}