//
// Created by giacomo on 09/07/18.
//

#ifndef TEMPLATEMATRIX_MATRIX_H
#define TEMPLATEMATRIX_MATRIX_H


#include <iostream>
#include <exception>
#include <vector>
#include <ctime>
#include "TemplateMatrixFactory.h"

template<typename T>
class Matrix {
public:
    Matrix<T>() {};

    ~Matrix() {
        delete[] buffer;
    }

    Matrix<T>(const Matrix& o) {
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

    Matrix<T>* product(Matrix<T>& B) { //Product between two template matrices
        if (width == B.height) {
            Matrix<T>* result = new Matrix<T>;
            result->height = height;
            result->width = B.width;
            result->name = "MatrixProduct";
            result->buffer = new T[height*width];

            int r = 0;
            std::vector<T> rowA = getRow(*this, r);
            int c = 0;
            std::vector<T> colB = B.getColumn(B, c);

            for (int i = 0; i < (width*height); i++) {
                if (c == height) {
                    r++;
                    rowA = getRow(*this, r);
                    c = 0;
                    colB = B.getColumn(B, c);
                }

                for (int j = 0; j < width; j++)
                    result->buffer[i] += rowA[j]*colB[j];

                c++;
                colB = B.getColumn(B, c);
            }
            return result;

        } else
            throw std::invalid_argument("Impossible to run the product between these two matrices");
    }

    Matrix<T>* product(int lambda) { //Product between template matrix and template lambda
        Matrix<T>* result = new Matrix<T>;
        result->height = height;
        result->width = width;
        result->name = "ScalarProduct";
        result->buffer = new T[height*width];


        for (int i = 0; i < (width*height); i++)
            result->buffer[i] = buffer[i] * lambda;

        return result;
    }

    Matrix<T>* sum(Matrix<T>& B) { //Sum with template matrices
        if (width == B.width && height == B.height) {
            Matrix<T>* result = new Matrix<T>;
            result->height = height;
            result->width = width;
            result->name = "Sum";
            result->buffer = new T[height*width];

            for (int i = 0; i < (width*height); i++)
                result->buffer[i] = buffer[i]+B.buffer[i];

            return result;
        } else
            throw std::invalid_argument("Impossible to run the sum between these two matrices");
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

    Matrix<T>* transposedMatrix() {   //Change row with columns
        Matrix<T>* result = new Matrix<T>;
        result->height = width;
        result->width = height;
        result->name = "Transpose";
        result->buffer = new T[height*width];

        std::vector<T> rowM;

        for (int i = 0; i < height; i++) {
            rowM = getRow(*this, i);
            int k = i;
            for (int j = 0; j < width; j++) {
                result->buffer[k] = rowM[j];
                k += height;
            }
        }
        return result;
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
