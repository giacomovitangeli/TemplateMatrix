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
    Matrix(int h = 3, int w = 3, std::string n = "Default", std::string im = "auto") : height(h), width(w), name(n),
                                                                                       initMode(im) {
        try {
            initMatrix();
        } catch (const std::out_of_range& e) {
            std::cerr << e.what() << std::endl;
            std::cout << "...Generating a default matrix..." << std::endl;
            width = 3;
            height = 3;
            buffer = new T[width*height];
            initNullMatrix();
        } catch (const std::invalid_argument& e) {
            e.what();
            std::cout << "...Generating a default matrix..." << std::endl;
            width = 3;
            height = 3;
            buffer = new T[width*height];
            initNullMatrix();
        } catch (...) {}
    }

    ~Matrix() {
        delete[] buffer;
    }

    void initMatrix() {
        if (initMode == "manual")
            initMatrixManually();
        else if (initMode == "rauto")
            initRandomMatrix();
        else if (initMode == "auto")
            initNullMatrix();
        else
            throw std::invalid_argument("Can't resolve the initialization mode selected!");
    }

    void initMatrixManually() {
        if (width <= 0 || height <= 0)
            throw std::out_of_range("Out of Range");
        else {
            buffer = new T[width*height];
            setMatrixValues();
        }
    }

    void initRandomMatrix() {
        if (width <= 0 || height <= 0)
            throw std::out_of_range("Out of Range");
        else {
            srand(time(NULL));
            buffer = new T[width*height];
            for (int i = 0; i < (height*width); i++)
                buffer[i] = rand()%100; //Init in the range 0 to 99
        }
    }

    void initNullMatrix() {
        if (width <= 0 || height <= 0)
            throw std::out_of_range("Out of Range");
        else {
            buffer = new T[width*height];
            for (int i = 0; i < (height*width); i++)
                buffer[i] = 0;
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

    Matrix<T>& product(Matrix<T>& A, Matrix<T>& B) { //Product operator overloading to use it with template matrices
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

    void printMatrix() {
        std::cout << std::endl << "Print " << name << " Matrix: ";
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
        for (int i = 0; i < height; i++) {
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
    std::string name, initMode;
};


#endif //TEMPLATEMATRIX_MATRIX_H
