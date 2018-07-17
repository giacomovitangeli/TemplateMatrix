//
// Created by giacomo on 09/07/18.
//

#include "gtest/gtest.h"

#include "../TemplateMatrixFactory.h"
#include "../Matrix.h"

TEST(Matrix, createMatrix) {
    TemplateMatrixFactory<int> tmf;
    auto A = tmf.createMatrix("A", Mode::stdauto, 2, 3);

    ASSERT_EQ("A", A->getName());

    for (int i = 0; i < (A->getHeight()*A->getWidth()); i++)
        ASSERT_EQ(0, A->getValue(0));
    delete A;
}

TEST(Matrix, matrixProduct) {
    TemplateMatrixFactory<int> tmf;
    auto A = tmf.createMatrix("A", Mode::rauto, 2, 3);
    auto B = tmf.createMatrix("B", Mode::rauto, 3, 2);
    auto pM = A->product(*B);

    ASSERT_EQ("MatrixProduct", pM->getName());
    ASSERT_EQ(2, pM->getWidth());
    ASSERT_EQ(2, pM->getHeight());

    delete A;
    delete B;
    delete pM;
}

TEST(Matrix, trasposedMatrix) {
    TemplateMatrixFactory<int> tmf;
    auto A = tmf.createMatrix("A", Mode::rauto, 2, 3);
    auto At = A->transposedMatrix();

    ASSERT_EQ(A->getWidth(), At->getHeight());
    ASSERT_EQ(A->getHeight(), At->getWidth());
    ASSERT_EQ(A->getValue(1, 2), At->getValue(2, 1));

    delete A;
    delete At;
}


TEST(Matrix, sumMatrix) {
    TemplateMatrixFactory<int> tmf;
    auto A = tmf.createMatrix("A", Mode::rauto, 2, 3);
    auto C = tmf.createMatrix("C", Mode::rauto, 2, 3);
    auto S = A->sum(*C);

    ASSERT_EQ(A->getWidth(), C->getWidth());
    ASSERT_EQ(A->getHeight(), S->getHeight());
    for (int i = 0; i < (S->getWidth()*S->getHeight()); i++)
        ASSERT_EQ(S->getValue(i), (A->getValue(i)+C->getValue(i)));

    delete A;
    delete C;
}

TEST(Matrix, scalarProductMatrix) {
    TemplateMatrixFactory<int> tmf;
    auto C = tmf.createMatrix("C", Mode::rauto, 2, 3);
    int l = 2;
    auto pS = C->product(l);
    pS->printMatrix();

    ASSERT_EQ(pS->getWidth(), C->getWidth());
    ASSERT_EQ(pS->getHeight(), C->getHeight());
    for (int i = 0; i < (pS->getWidth()*pS->getHeight()); i++)
        ASSERT_EQ(pS->getValue(i), (C->getValue(i)*l));

    delete C;
}

