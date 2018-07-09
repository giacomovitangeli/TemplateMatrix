//
// Created by giacomo on 09/07/18.
//

#ifndef TEMPLATEMATRIX_MATRIX_H
#define TEMPLATEMATRIX_MATRIX_H


#include <iostream>

template<typename T>
class Matrix {
public:
    Matrix(int w = 0, int h = 0) : width(w), height(h) {
        if (width == 0 && height == 0)
            buffer = nullptr;
        else
            buffer = new T[width*height];
    }

    ~Matrix() {
        delete[] buffer;
    }

    void initMatrix() {
        for (int i = 0; i < (width*height); i++)
            buffer[i] = 0;
    }

    explicit Matrix(const T& o) {
        width = o.width;
        height = o.height;

        if (o.buffer != nullptr) {
            buffer = new T[width*height];
            for (int i = 0; i < (width*height); i++)
                buffer[i] = o.buffer[i];
        } else
            buffer = nullptr;
    }

    Matrix& operator=(const Matrix& rhs) {
        if (this != &rhs) {
            if (buffer != nullptr)
                delete[] buffer;

            width = rhs.width;
            height = rhs.height;
            if (rhs.buffer != nullptr) {
                buffer = new T[width*height];
                for (int i = 0; i < (width*height); i++)
                    buffer[i] = rhs.buffer[i];
            } else
                buffer = nullptr;
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
