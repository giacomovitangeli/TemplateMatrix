#include <iostream>
#include <memory>
#include "Matrix.h"

int main() {
//    std::unique_ptr<Matrix<int>> A(new Matrix<int>(2, 2));
/*DYNAMIC INIT
    Matrix<int>* A = new Matrix<int>(2, 3, "A", "rauto");
    A->printMatrix();
    Matrix<int>* B = new Matrix<int>(3, 2, "B", "rauto");
    B->printMatrix();
    Matrix<int>* C = new Matrix<int>(2, 2, "C", "auto");
    C->printMatrix();
*/
    //STATIC INIT
    Matrix<int> A(2, 3, "A", "manual");
    // A.printMatrix();
    Matrix<int> B(3, 2, "B", "manual");
    // B.printMatrix();
    Matrix<int> C(10, 10, "C", "auto");
    C.printMatrix();

    C.product(A, B);
    C.printMatrix();

    return 0;
}