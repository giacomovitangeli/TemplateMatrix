#include <iostream>
#include <memory>
#include "gtest/gtest.h"
#include "TemplateMatrixFactory.h"
#include "Matrix.h"

int main() {
/*
     'manual' = Manual assignment of matrix values
     'stdauto' = Automatic assignment to a null matrix
     'rauto' = Automatic random assignment with values between 0 and 99
*/
    TemplateMatrixFactory<int> tmf;

    auto A = tmf.createMatrix("A", Mode::manual);
    auto B = tmf.createMatrix("B", Mode::manual);
    auto C = tmf.createMatrix("C", Mode::stdauto);
    C->matrixProduct(*A, *B);
    C->printMatrix();

    auto At = tmf.createMatrix("At", Mode::stdauto);
    At->transposedMatrix(*A);
    At->printMatrix();
    A->printMatrix();

    return 0;
}