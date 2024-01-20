//
// Created by benedict on 1/19/24.
//

#include <iostream>
#include <vector>
#include <cmath>
#include "cpp/Matrix.h"
#include "cpp/dynamicTimeWarping.h"

#define LOG(x) std::cout << x << std::endl;


int main(int argc, char* argv[]) {
    std::vector<double> x = {0, 0, 1, 1, 0, 0, -1, 0, 0, 0, 0};
    std::vector<double> y = {0, 0, 0, 0, 1, 1, 0, 0, 0, -1, -0.5, 0, 0};
    Matrix costMatrix = dynamicTimeWarping(x, y);

    // costMatrix.print();
    double alignmentCost = costMatrix(costMatrix.m-1, costMatrix.n-1);
    LOG("Alignment cost = " << alignmentCost);

}

