//
// Created by giacomo on 09/07/18.
//

#include "gtest/gtest.h"

#include "../Matrix.h"

TEST(Matrix, DefaultConstructor) {
    Matrix<int> m;
    ASSERT_EQ(3, m.getWidth());
    ASSERT_EQ(3, m.getHeight());
}

TEST(Matrix, Constructor){
    Matrix<int> m(4, 5);
    ASSERT_EQ(4, m.getWidth());
    ASSERT_EQ(5, m.getHeight());
}

