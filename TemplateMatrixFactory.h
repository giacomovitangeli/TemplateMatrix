//
// Created by giacomo on 12/07/18.
//

#ifndef TEMPLATEMATRIX_TEMPLATEMATRIXFACTORY_H
#define TEMPLATEMATRIX_TEMPLATEMATRIXFACTORY_H

#include "Matrix.h"

enum Mode {
    stdauto, rauto, manual
};

template<typename T>
class TemplateMatrixFactory {
private:
    Mode initMode;
    Matrix<T>* result;


public:
    TemplateMatrixFactory<T>() : initMode(Mode::stdauto), result(nullptr) {};

    Matrix<T>* createMatrix(std::string n = "Default", Mode inMode = Mode::stdauto, int h = 3, int w = 3) {
        if (h <= 0 || w <= 0)
            throw std::out_of_range("Out of Range");

        result = new Matrix<T>;
        initMode = inMode;
        result->setName(n);
        result->setHeight(h);
        result->setWidth(w);

        try {
            if (initMode == Mode::manual)
                initMatrixManually();
            else if (initMode == Mode::rauto)
                initRandomMatrix();
            else if (initMode == Mode::stdauto)
                initNullMatrix();
            else
                throw std::invalid_argument("Can't resolve the initialization mode selected!");
        } catch (std::invalid_argument& e) {
            e.what();
            std::cout << "Incorrect initialization mode has been replaced with the default initialization";
            initMode = Mode::stdauto;
            initNullMatrix();
        } catch (...) {}

        return result;
    }

    void initMatrixManually() {
        if (result->getWidth() <= 0 || result->getHeight() <= 0)
            throw std::out_of_range("Out of Range");
        else {
            result->setBuffer(new T[result->getWidth()*result->getHeight()]);
            setMatrixValues();
        }
    }

    void initRandomMatrix() {
        if (result->getWidth() <= 0 || result->getHeight() <= 0)
            throw std::out_of_range("Out of Range");
        else {
            srand(time(NULL));
            result->setBuffer(new T[result->getWidth()*result->getHeight()]);
            for (int i = 0; i < (result->getWidth()*result->getHeight()); i++)
                result->setValue(i, (rand()%10));
            std::cout << std::endl << result->getName() << " Random Matrix is completed succesfully!" << std::endl;
            result->printMatrix();
        }
    }

    void initNullMatrix() {
        result->setBuffer(new T[result->getWidth()*result->getHeight()]);
        for (int i = 0; i < (result->getWidth()*result->getHeight()); i++)
            result->setValue(i, 0);
        std::cout << std::endl;
    }

    void setMatrixValues() {
        T value;
        std::cout << std::endl << "Setting the values of the matrix: " << std::endl;
        for (int i = 0; i < result->getHeight(); i++) {
            for (int j = 0; j < result->getWidth(); j++) {
                std::cout << "Matrix[" << i << ", " << j << "]: ";
                std::cin >> value;
                std::cout << std::endl;
                result->setValue(i, j, value);
            }
        }
        std::cout << std::endl << result->getName() << " Manual setting is completed succesfully!" << std::endl;
        result->printMatrix();
    }
};

#endif //TEMPLATEMATRIX_TEMPLATEMATRIXFACTORY_H
