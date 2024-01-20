//
// Created by benedict on 1/19/24.
//

#include <iostream>
#include <string>
#include "Matrix.h"

#define LOG(x) std::cout << x << std::endl;
#define EPS 1e-10;

/*
Constructors
*/

Matrix::Matrix(unsigned int rows, unsigned int cols) : m(rows), n(cols) {
    alloc();  // initialise 2D array
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            pointers[i][j] = 0;
        }
    }
}

/*
Desctuctor
*/
Matrix::~Matrix() {
    for (int i = 0; i < m; i++) {
        delete[] pointers[i];  // delete the array of pointers at each row
    }
    delete[] pointers;  // finally delete the whole empty data sctructure
}


double& Matrix::operator()(int x, int y) const {
    return pointers[x][y];
}


// allocate the memory required for the matrix by initialising the double pointer (pointer to a pointer)
void Matrix::alloc() {
    pointers = new double*[m];
    for (int i = 0; i < m; i++) {
        pointers[i] = new double[n];
    }
}


void Matrix::print() const {
    for (int i = 0; i < m; i++) {
        std::string suffix;
        for (int j = 0; j < n; j++) {
            if (j != n-1) {suffix = ", ";}
            else {suffix = "";}
            std::cout << pointers[i][j] << suffix;
        }
        std::cout << "\n";
    }
}
