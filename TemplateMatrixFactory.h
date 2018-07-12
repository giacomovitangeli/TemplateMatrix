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

    Matrix<T>* createMatrix(std::string n = "Default", Mode inMode = Mode::stdauto) {
        result = new Matrix<T>;
        initMode = inMode;
        result->setName(n);

        try {
            initMatrix();
        } catch (const std::out_of_range& e) {
            std::cerr << e.what() << std::endl;
            std::cout << "...Generating a default matrix..." << std::endl;
            result->setWidth(3);
            result->setHeight(3);
            result->setBuffer(new T[result->getWidth()*result->getHeight()]);
            initNullMatrix();
        } catch (const std::invalid_argument& e) {
            e.what();
            std::cout << "...Generating a default matrix..." << std::endl;
            result->setWidth(3);
            result->setHeight(3);
            result->setBuffer(new T[result->getWidth()*result->getHeight()]);
            initNullMatrix();
        } catch (...) {}

        return result;
    }

    void insertAll() {
        int height, width;

        std::cout << "Initialization of " << result->getName() << " Matrix" << std::endl;

        std::cout << "Insert the number of " << result->getName() << "'s rows: ";
        std::cin >> height;
        result->setHeight(height);
        std::cout << std::endl;

        std::cout << "Insert the number of " << result->getName() << "'s columns: ";
        std::cin >> width;
        result->setWidth(width);
        std::cout << std::endl;

        if (initMode == Mode::manual)
            initMatrixManually();
        else
            initRandomMatrix();
    }

    void initMatrix() {
        if (initMode == Mode::manual)
            insertAll();
        else if (initMode == Mode::rauto)
            insertAll();
        else if (initMode == Mode::stdauto)
            initNullMatrix();
        else
            throw std::invalid_argument("Can't resolve the initialization mode selected!");
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
                result->setValue(i, (rand()%100));
            std::cout << result->getName() << " Random Matrix is completed succesfully!" << std::endl;
            result->printMatrix();
        }
    }

    void initNullMatrix() {
        result->setWidth(3);
        result->setHeight(3);
        result->setBuffer(new T[result->getWidth()*result->getHeight()]);
        for (int i = 0; i < (result->getWidth()*result->getHeight()); i++)
            result->setValue(i, 0);
        std::cout<<std::endl;
        std::cout << result->getName() << " Null Matrix is completed succesfully!" << std::endl;
        result->printMatrix();
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
        std::cout << result->getName() << " Manual setting is completed succesfully!" << std::endl;
        result->printMatrix();
    }
};

#endif //TEMPLATEMATRIX_TEMPLATEMATRIXFACTORY_H
