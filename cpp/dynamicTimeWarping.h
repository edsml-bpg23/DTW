//
// Created by benedict on 1/19/24.
//

#pragma once
#include <vector>
#include "Matrix.h"

Matrix dynamicTimeWarping(std::vector<double> &x, std::vector<double> &y);
Matrix initCostMatrix(unsigned int m, unsigned int n);
std::pair<int, double> calculatePenalty(Matrix &costMatrix, int i, int j);
std::vector<std::pair<unsigned int, unsigned int>> tracePath(Matrix &tracebackMatrix);
Matrix buildDistanceMatrix(std::vector<double> &x, std::vector<double> &y);

