//
// Created by benedict on 1/20/24.
//

#include <iostream>
#include <vector>
#include <cmath>
#include "dynamicTimeWarping.h"
#include <float.h>
#include <stdexcept>

#include "Matrix.h"

#define LOG(x) std::cout << x << std::endl;


Matrix buildDistanceMatrix(std::vector<double> &x, std::vector<double> &y) {
    unsigned const int m = static_cast<int>(x.size());
    unsigned const int n = static_cast<int>(y.size());
    auto distanceMatrix = Matrix(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            distanceMatrix(i, j) = std::abs(x[i] - y[j]);
        }
    }
    return distanceMatrix;
};


Matrix initCostMatrix(unsigned const int m, unsigned const int n) {
    auto costMatrix = Matrix(m+1, n+1);
    for (int i = 1; i < costMatrix.m; i++) {
        costMatrix(i, 0) = DBL_MAX;
    }
    for (int i = 1; i < costMatrix.n; i++) {
        costMatrix(0, i) = DBL_MAX;
    }
    return costMatrix;
}


std::pair<int, double> calculatePenalty(Matrix &costMatrix, int i, int j) {
    std::vector<double> const penalty = {
        costMatrix(i-1, j-1), costMatrix(i-1, j), costMatrix(i, j-1)
    };
    int minIdx = -1;
    auto minVal = DBL_MAX;
    for (int k = 0; k < penalty.size(); k++) {
        if (penalty[k] < minVal) {
            minIdx = k;
            minVal = penalty[k];
        }
    }
    std::pair<int, double> p(minIdx, minVal);
    return p;
}


std::vector<std::pair<unsigned int, unsigned int>> tracePath(Matrix &tracebackMatrix) {
    unsigned int i = tracebackMatrix.m - 1;
    unsigned int j = tracebackMatrix.n - 1;
    std::pair<unsigned int, unsigned int> p(i, j);
    std::vector<std::pair<unsigned int, unsigned int>> path = {p};

    while (i > 0 || j > 0) {
        switch(static_cast<int>(tracebackMatrix(i, j))) {
            case 0:
                i--;
                j--;
                break;
            case 1:
                i--;
                break;
            case 2:
                j--;
                break;
            default:
                throw std::invalid_argument("Traceback matrix value error.");
        }
        p.first = i;
        p.second = j;
        path.insert(path.begin(), p);  // prepend
    }
    return path;
}


Matrix dynamicTimeWarping(std::vector<double> &x, std::vector<double> &y) {
    Matrix distanceMatrix = buildDistanceMatrix(x, y);

    unsigned const int m = x.size();
    unsigned const int n = y.size();

    Matrix costMatrix = initCostMatrix(m, n);
    Matrix tracebackMatrix = Matrix(m, n);

    std::pair<int, double> p;

    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            p = calculatePenalty(costMatrix, i, j);
            costMatrix(i, j) = distanceMatrix(i-1, j-1) + p.second;
            tracebackMatrix(i-1, j-1) = p.first;
        }
    }

    std::vector<std::pair<unsigned int, unsigned int>> path = tracePath(tracebackMatrix);

    for (auto p: path) {
        std::cout << "(" << p.first << ", " << p.second << "), ";
    }
    std::cout << "\n";

    return costMatrix;
}


