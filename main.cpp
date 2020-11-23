#include <iostream>
#include <memory>
#include "gtest/gtest.h"
#include "TemplateMatrixFactory.h"
#include "Matrix.h"

int main() {
/*
     'manual' = Manual assignment of matrix values
     'stdauto' = Automatic assignment to a null matrix
     'rauto' = Automatic random assignment with values between 0 and 9
*/
    TemplateMatrixFactory<int> tmf;

    try {
        auto A = tmf.createMatrix("A", Mode::rauto, 3, 4);
        auto B = tmf.createMatrix("B", Mode::rauto, 4, 3);
        auto C = tmf.createMatrix("C", Mode::rauto, 3, 4);

        auto pM = A->product(*B);
        pM->printMatrix();

        auto At = A->transposedMatrix();
        At->printMatrix();

        auto S = A->sum(*C);
        S->printMatrix();

        int l = 2;
        auto pS = C->product(l);
        pS->printMatrix();

        delete A;
        delete B;
        delete C;
        delete pM;
        delete At;
        delete S;
        delete pS;

    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
        std::cout << "Retry to Insert the Windth and Height:" << std::endl;
        int height, width;

        std::cout << "Insert the number of rows: ";
        std::cin >> height;
        std::cout << std::endl;

        std::cout << "Insert the number of columns: ";
        std::cin >> width;
        std::cout << std::endl;
        auto A = tmf.createMatrix("A", Mode::rauto, height, width);
    } catch (std::invalid_argument e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {}

    return 0;
}