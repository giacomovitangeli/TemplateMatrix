#include <iostream>
#include "Matrix.h"

int main() {
    Matrix<int> matrix1(3, 3);

    matrix1.initMatrix();
    matrix1.printMatrix();

    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            matrix1.setValue(j, i, i);



    matrix1.printMatrix();

    return 0;
}