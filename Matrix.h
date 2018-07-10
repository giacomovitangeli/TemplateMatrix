//
// Created by giacomo on 09/07/18.
//

#ifndef TEMPLATEMATRIX_MATRIX_H
#define TEMPLATEMATRIX_MATRIX_H


#include <iostream>
#include <exception>

template<typename T>
class Matrix {
public:
    Matrix(int w = 3, int h = 3) : width(w), height(h) {
        try {
            initMatrix();
        } catch (const std::out_of_range& e) {
            std::cerr << e.what() << std::endl;
            std::cout << "...Generating a default matrix..." << std::endl;
            width = 3;
            height = 3;
            buffer = new T[width*height];
            setMatrixValues();
        } catch (...) {}
    }

    ~Matrix() {
        delete[] buffer;
    }

    void initMatrix() {
        if (width <= 0 || height <= 0)
            throw std::out_of_range("Out of Range");
        else {
            buffer = new T[width*height];
            setMatrixValues();
        }
    }

    explicit Matrix(const Matrix& o) {
        if (o.width > 0 && o.height > 0) {
            width = o.width;
            height = o.height;
            buffer = new T[width*height];
            for (int i = 0; i < (width*height); i++)
                buffer[i] = o.buffer[i];
        } else
            throw std::out_of_range("Out of Range");
    }

    Matrix& operator=(const Matrix& rhs) {
        if (this != &rhs) {
            if (buffer != nullptr)
                delete[] buffer;

            if (rhs.width > 0 && rhs.height > 0) {
                width = rhs.width;
                height = rhs.height;
                buffer = new T[width*height];
                for (int i = 0; i < (width*height); i++)
                    buffer[i] = rhs.buffer[i];
            } else
                throw std::out_of_range("Out of Range");
        }
        return *this;
    }

    void printMatrix() {
        std::cout << std::endl << "Print Matrix: ";
        for (int i = 0; i < (width*height); i++) {

            if (i%width == 0)
                std::cout << std::endl;
            std::cout << buffer[i] << " ";
        }
        std::cout << std::endl;
    }

    void setMatrixValues() {
        T value;
        std::cout << std::endl << "Setting the values of the matrix: " << std::endl;
        for (int i = 0; i < (height); i++) {
            for (int j = 0; j < width; j++) {
                std::cout << "Matrix[" << i << ", " << j << "]: ";
                std::cin >> value;
                std::cout << std::endl;
                setValue(i, j, value);
            }
        }
        std::cout << "Setting completed succesfully!" << std::endl;
        printMatrix();
    }

    void setValue(int x, int y, T& value) {
        buffer[x*width+y] = value;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    T* getBuffer() const {
        return buffer;
    }

private:
    int width, height;
    T* buffer;
};


#endif //TEMPLATEMATRIX_MATRIX_H
