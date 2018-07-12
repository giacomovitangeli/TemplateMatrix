//
// Created by giacomo on 09/07/18.
//

#ifndef TEMPLATEMATRIX_MATRIX_H
#define TEMPLATEMATRIX_MATRIX_H


#include <iostream>
#include <exception>
#include <vector>
#include <ctime>

template<typename T>
class Matrix {
public:
    Matrix<T>(){};

    ~Matrix() {
        delete[] buffer;
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

    Matrix<T>& operator=(const Matrix& rhs) {
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

    Matrix<T>& matrixProduct(Matrix<T>& A, Matrix<T>& B) { //Product with template matrices
        if (A.width == B.height) {
            width = B.width;
            height = A.height;
            delete[] buffer;
            buffer = new T[width*height];

            int r = 0;
            std::vector<T> rowA = A.getRow(A, r);
            int c = 0;
            std::vector<T> colB = B.getColumn(B, c);

            for (int i = 0; i < (width*height); i++) {
                if (c == A.height) {
                    r++;
                    rowA = A.getRow(A, r);
                    c = 0;
                    colB = B.getColumn(B, c);
                }

                for (int j = 0; j < A.width; j++)
                    buffer[i] += rowA[j]*colB[j];

                c++;
                colB = B.getColumn(B, c);
            }

        } else
            throw std::invalid_argument("Impossible to run the product between these two matrices");

        return *this;
    }

    std::vector<T> getRow(const Matrix<T>& m, int r) { //Return a row of a matrix
        std::vector<T> v;
        for (int j = 0; j < m.width; j++) {
            v.push_back(m.buffer[r*width+j]);
        }
        return v;
    }

    std::vector<T> getColumn(const Matrix<T>& m, int c) {  //Return a column of a matrix
        std::vector<T> v;
        for (int i = 0; i < height; i++) {
            v.push_back(m.buffer[i*width+c]);
        }
        return v;
    }

    Matrix<T>& transposedMatrix(Matrix<T>& m) {   //Change row with columns
        height = m.width;
        width = m.height;
        if (buffer != 0)
            delete[] buffer;
        buffer = new T[height*width];
        std::vector<T> rowM;

        for (int i = 0; i < width; i++) {
            rowM = m.getRow(m, i);
            int k = i;
            for (int j = 0; j < height; j++) {
                buffer[k] = rowM[j];
                k += width;
            }
        }
        return *this;
    }

    void printMatrix() {
        std::cout << std::endl << "Print " << name << " Matrix: ";
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

    void setValue(int i, T value) {
        buffer[i] = value;
    }

    T& getValue(int i) const {
        return buffer[i];
    }

    T& getValue(int x, int y) const {
        return buffer[x*width+y];
    }


    int getWidth() const {
        return width;
    }

    void setWidth(int width) {
        Matrix::width = width;
    }

    void setHeight(int height) {
        Matrix::height = height;
    }

    void setBuffer(T* buffer) {
        Matrix::buffer = buffer;
    }

    int getHeight() const {
        return height;
    }

    T* getBuffer() const {
        return buffer;
    }

    const std::string& getName() const {
        return name;
    }

    void setName(const std::string& name) {
        Matrix::name = name;
    }

private:
    int width, height;
    T* buffer;
    std::string name;
};


#endif //TEMPLATEMATRIX_MATRIX_H
