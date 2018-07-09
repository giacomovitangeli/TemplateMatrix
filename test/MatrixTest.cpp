//
// Created by giacomo on 09/07/18.
//

#include "gtest/gtest.h"

#include "../Matrix.h"

TEST(Matrix, DefaultConstructor) {

    Matrix m;
    ASSERT_EQ(0, m.getWidth());
    ASSERT_EQ(0, m.getHeight());
    ASSERT_EQ(nullptr, m.getBuffer());
}

