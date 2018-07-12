//
// Created by giacomo on 09/07/18.
//

#include "gtest/gtest.h"

#include "../Matrix.h"
#include "../TemplateMatrixFactory.h"

TEST(FactoryTest, createMatrix) {
    TemplateMatrixFactory<int> tmf;
    auto C = tmf.createMatrix("C", Mode::stdauto);
    ASSERT_EQ("C", C->getName());
    ASSERT_EQ(0, C->getValue(0));
}

TEST(MatrixProduct, product){
    TemplateMatrixFactory<int> tmf;
    auto A = tmf.createMatrix("A", Mode::stdauto);
    auto B = tmf.createMatrix("B", Mode::stdauto);
    auto C = tmf.createMatrix("C", Mode::stdauto);
    C->matrixProduct(*A, *B);

    ASSERT_EQ(0, C->getValue(2));
}


TEST(MatrixTransposed, TestTrasposedMatrix) {
    TemplateMatrixFactory<int> tmf;
    auto A = tmf.createMatrix("A", Mode::stdauto);
    auto At = tmf.createMatrix("At", Mode::stdauto);
    At->transposedMatrix(*A);

    ASSERT_EQ(A->getWidth(), At->getHeight());
    ASSERT_EQ(A->getHeight(), At->getWidth());
}
